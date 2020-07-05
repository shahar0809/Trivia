using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for RoomAdmin.xaml
    /// </summary>
    /// 

    public struct WorkerParameter
    {
        public List<string> list;
    }

    public partial class WaitInRoom : Window
    {
        private RoomData roomData;
        private bool isAdmin;
        private NetworkStream clientStream;
        private BackgroundWorker worker = new BackgroundWorker();
        private bool stopUpdating;

        public WaitInRoom(RoomData data, NetworkStream clientStream, bool isAdmin)
        {
            InitializeComponent();
            this.roomData = data;
            this.clientStream = clientStream;
            this.isAdmin = isAdmin;
            stopUpdating = false;

            if (!isAdmin)
            {
                closeRoom.Visibility = Visibility.Collapsed;
                startGame.Visibility = Visibility.Collapsed;
            }
            else
            {
                leaveRoom.Visibility = Visibility.Collapsed;
            }

            // Displaying room data to the users
            displayMaxNumPlayers.Text = roomData.NumOfplayers.ToString();
            displayNumOfQuestions.Text = roomData.NumOfQuestions.ToString();
            displayTimePerQuestion.Text = roomData.TimeForQuestion.ToString();
            displayRoomName.Text = roomData.RoomName;
            roomName.Text = roomData.RoomName;

            // Creating a background worker that constantly updates the players in the room.
            worker.WorkerReportsProgress = true;
            worker.DoWork += updateRoomPlayers;
            worker.ProgressChanged += playersChanged;
            worker.RunWorkerAsync();
        }

        private void closeRoom_Click(object sender, RoutedEventArgs e)
        {
            // Sends a Close Room request to the server.
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, Codes.CLOSE_ROOM_CODE);

            // Terminating the thread that updates the players, and going back to the main menu.
            if (resp.status != (int)Codes.ERROR_CODE)
            {
                stopUpdating = true;
                var mainWindow = new MainWindow(this.clientStream);
                mainWindow.Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Couldn't close the room!");
            }
        }

        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            // Sending a Leave Room request to the server.
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, Codes.LEAVE_ROOM_CODE);

            // Terminating the thread that updates the players, and going back to the main menu.
            if (resp.status != (int)Codes.ERROR_CODE)
            {
                stopUpdating = true;
                var mainWindow = new MainWindow(this.clientStream);
                mainWindow.Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Couldn't leave the room!");
            }
        }

        private void startGame_Click(object sender, RoutedEventArgs e)
        {
            stopUpdating = true;
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, Codes.START_GAME_CODE);

            if (resp.status == (int)Codes.ERROR_CODE)
            {
                MessageBox.Show("Couldn't start the game! Try again");
            }
            else
            {
                DisplayQuestion question = new DisplayQuestion(this.clientStream, new TimeSpan(0, roomData.TimeForQuestion, 0), roomData.NumOfQuestions);
                question.Show();
                this.Close();
            }
        }

        /* A thread that constantly updates the players in the room */
        public void updateRoomPlayers(object sender, DoWorkEventArgs e)
        {
            // Getting the players connected to the room
            GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { RoomId = this.roomData.RoomId };

            while (!stopUpdating)
            {
                // Requesting the players in the room
                GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(
                    JsonConvert.SerializeObject(request),
                    clientStream,
                    Codes.GET_PLAYERS_IN_ROOM_CODE);

                // If the room was closed, then the player must leave (sending a leave room request)
                if (resp.PlayersInRoom == null || resp.PlayersInRoom.Count == 0)
                {
                    Response response = Communicator.ManageSendAndGetData<Response>("", this.clientStream, Codes.LEAVE_ROOM_CODE);
                    return;
                }

                // Updating list on the screen
                WorkerParameter param = new WorkerParameter { list = resp.PlayersInRoom };
                worker.ReportProgress(0, param);

                Thread.Sleep(3000);
            }
        }
        void playersChanged(object sender, ProgressChangedEventArgs e)
        {
            WorkerParameter param = (WorkerParameter)e.UserState;
            playersInRoom.ItemsSource = param.list;
        }
    }
}
