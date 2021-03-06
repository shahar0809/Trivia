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
using ClientWPF.Requests;
using ClientWPF.Responses;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        private NetworkStream clientStream;
        private string username;

        public CreateRoom(NetworkStream clientStream, string username)
        {
            InitializeComponent();
            this.username = username;
            usernameBox.Text = username;
            this.clientStream = clientStream;
        }

        private async void Submit_Button_Click(object sender, RoutedEventArgs e)
        {
            // Checking that the user has filled all of the data before creating the room.
            if (string.IsNullOrWhiteSpace(roomName.Text) || string.IsNullOrWhiteSpace(numOfPlayers.Text)
                || string.IsNullOrWhiteSpace(numOfQuestions.Text) || string.IsNullOrWhiteSpace(timeout.Text))
            {
                MessageBox.Show("Please fill all the fields!");
                return;
            }
            
            if (Int32.Parse(numOfPlayers.Text) < 1)
            {
                MessageBox.Show("The Number of players in the room must be at least 1!");
                return;
            }
            if (Int32.Parse(numOfQuestions.Text) < 1)
            {
                MessageBox.Show("The Number of questions in the game must be at least 1!");
                return;
            }
            if (Int32.Parse(timeout.Text) <= 0)
            {
                MessageBox.Show("The Number of players in the room must be bigger than 0!");
                return;
            }

            CreateRoomRequest createRoom = new CreateRoomRequest();
            try
            {
                createRoom.RoomName = roomName.Text;
                createRoom.NumOfPlayers = int.Parse(numOfPlayers.Text);
                createRoom.NumOfQuestions = int.Parse(numOfQuestions.Text);
                createRoom.TimeForQuestion = double.Parse(timeout.Text);
            }
            catch(FormatException)
            {
                MessageBox.Show("Invalid params");
                return;
            }
            string json = JsonConvert.SerializeObject(createRoom, Formatting.Indented);
                CreateRoomResponse createRoomResponse =
                    Communicator.ManageSendAndGetData<CreateRoomResponse>(json, clientStream, Codes.CREATE_ROOM_CODE);

                if (createRoomResponse.Status == (int)Codes.ERROR_CODE)
                {
                    ErrorBox.Visibility = Visibility.Visible;
                    await Task.Delay(1000);
                    var mainWindow = new MainWindow(clientStream, username);
                    mainWindow.Show();
                }
                else
                {
                    int roomId = createRoomResponse.RoomId;

                    RoomData roomData = new RoomData
                    {
                        RoomId = roomId,
                        NumOfplayers = createRoom.NumOfPlayers,
                        NumOfQuestions = createRoom.NumOfQuestions,
                        RoomName = createRoom.RoomName,
                        TimeForQuestion = createRoom.TimeForQuestion,
                        IsActive = 1
                    };

                    // Show the room details to the admin.
                    var waitInRoom = new WaitInRoom(roomData, clientStream, true, username);
                    waitInRoom.Show();
                }
                this.Close();

        }

        private void cancel_Click(object sender, RoutedEventArgs e)
        {
            // Closing the Log in window and returing to the menu.
            var mainWindow = new MainWindow(this.clientStream, username);
            mainWindow.Show();
            this.Close();
        }
    }
}
