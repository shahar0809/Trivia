using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using Newtonsoft.Json;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow;
        public const int ERROR_CODE = 0;

        private struct CreateRoomRequest
        {
            public string ROOM_NAME { set; get; }
            public int NUM_OF_PLAYERS { set; get; }
            public int NUM_OF_QUESTIONS { set; get; }
            public int TIME_PER_QUESTION { set; get; }
        }
        public CreateRoom(NetworkStream clientStream,MainWindow mainWindow)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;
        }

        private void Submit_Button_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest createRoom = new CreateRoomRequest 
            {
                ROOM_NAME = roomName.Text,
                NUM_OF_PLAYERS = int.Parse(numOfPlayers.Text),
                NUM_OF_QUESTIONS = int.Parse(numOfQuestion.Text),
                TIME_PER_QUESTION = int.Parse(timeout.Text),
            };

            string json = JsonConvert.SerializeObject(createRoom, Formatting.Indented);
            Response createRoomResponse = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.CREATE_ROOM_CODE);

            if (createRoomResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Error! , can't create room");
            }

            // Should show the room details.
            var roomAdmin = new RoomAdmin(mainWindow);
            roomAdmin.Show();
            Close();
        }
    }
}
