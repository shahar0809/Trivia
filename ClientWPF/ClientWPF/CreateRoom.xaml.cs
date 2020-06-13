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

        public struct CreateRoomRequest
        {
            public string roomName { set; get; }
            public int numOfPlayers { set; get; }
            public int numOfQuestions { set; get; }
            public int timePerQuestion { set; get; }
        }

        private struct CreateRoomResponse
        {
            public int status { set; get; }
            public int RoomId { set; get; }
        }
        public CreateRoom(NetworkStream clientStream,MainWindow mainWindow)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;
        }

        private void Submit_Button_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(roomName.Text) || string.IsNullOrWhiteSpace(numOfPlayers.Text)
                || string.IsNullOrWhiteSpace(numOfQuestions.Text) || string.IsNullOrWhiteSpace(timeout.Text))
            {
                MessageBox.Show("Please fill all the fields!");
                return;
            }

            CreateRoomRequest createRoom = new CreateRoomRequest 
            {
                roomName = roomName.Text,
                numOfPlayers = int.Parse(numOfPlayers.Text),
                numOfQuestions = int.Parse(numOfQuestions.Text),
                timePerQuestion = int.Parse(timeout.Text),
            };

            string json = JsonConvert.SerializeObject(createRoom, Formatting.Indented);
            CreateRoomResponse createRoomResponse = Communicator.ManageSendAndGetData<CreateRoomResponse>(json, clientStream, Codes.CREATE_ROOM_CODE);

            if (createRoomResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Error! , can't create room");
            }
            int roomId = createRoomResponse.RoomId;
            //Show the room details.
            var roomAdmin = new RoomAdmin(mainWindow);
            roomAdmin.Show();
            Close();
        }
    }
}
