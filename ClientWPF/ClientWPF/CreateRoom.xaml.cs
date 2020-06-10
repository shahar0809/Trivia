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
        public const int ERROR_CODE = 0;
        private struct CreateRoomRequest
        {
            public string roomName { set; get; }
            public int numOfPlayers { set; get; }
            public int numOfQuestions { set; get; }
            public int timePerQuestion { set; get; }
        }
        public CreateRoom(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }

        private void Submit_Button_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest createRoom = new CreateRoomRequest 
            {
                roomName = roomName.Text,
                numOfPlayers = int.Parse(numOfPlayers.Text),
                numOfQuestions = int.Parse(numOfQuestion.Text),
                timePerQuestion = int.Parse(timeout.Text),
            };


            string json = JsonConvert.SerializeObject(createRoom, Formatting.Indented);
            Communicator.Response createRoomResponse = Communicator.ManageSendAndGetData(json, clientStream);

            if (createRoomResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Error! , can't create room");
            }
            //Should show the room details.
            var MainWindowMenu = new MainWindow();
            MainWindowMenu.Show();
            Close();
        }
    }
}
