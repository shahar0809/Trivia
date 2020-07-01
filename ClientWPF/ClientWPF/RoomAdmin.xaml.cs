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

    public partial class RoomAdmin : Window
    {
        private RoomData roomData;
        private bool isAdmin;
        private NetworkStream clientStream;
        private BackgroundWorker worker = new BackgroundWorker();
        private bool stopUpdating;

        public struct workerParameter
        {
            public List<string> roomPlayers;
        }

        public RoomAdmin(RoomData data, NetworkStream clientStream, bool isAdmin)
        {
            InitializeComponent();
            this.roomData= data;
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

            // Showing room data to the admin
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
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)Codes.CLOSE_ROOM_CODE);

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
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)Codes.LEAVE_ROOM_CODE);

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
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)Codes.START_GAME_CODE);
            Questions q = new Questions(this.clientStream);
            q.Show();
            this.Close();
        }

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
                    (int)Codes.GET_PLAYERS_IN_ROOM_CODE);

                // Room was closed
                if (resp.PlayersInRoom == null || resp.PlayersInRoom.Count == 0)
                {
                    Response response = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)Codes.LEAVE_ROOM_CODE);
                    return;
                }

                workerParameter param = new workerParameter { roomPlayers = resp.PlayersInRoom };
                worker.ReportProgress(0, param);

                Thread.Sleep(600);
            }
        }

        void playersChanged(object sender, ProgressChangedEventArgs e)
        {
            workerParameter param = (workerParameter)e.UserState;
            List<string> roomPlayers = param.roomPlayers;
            playersInRoom.ItemsSource = roomPlayers;
        }
    }
}
