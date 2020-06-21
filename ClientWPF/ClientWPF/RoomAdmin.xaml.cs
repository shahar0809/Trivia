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
        private bool isChange;
        private List<string> players;
        private BackgroundWorker worker = new BackgroundWorker();

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

            isChange = false;

            worker.WorkerReportsProgress = true;
            worker.DoWork += updateRoomPlayers;
            worker.ProgressChanged += playersChanged;
            worker.RunWorkerAsync();

        }

        private void closeRoom_Click(object sender, RoutedEventArgs e)
        {
            isChange = true;
            // Sends a Close Room request to the server.
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)RoomCodes.CLOSE_ROOM_CODE);

            if (resp.status != (int)Codes.ERROR_CODE)
            {
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
            isChange = true;
            Response resp = Communicator.ManageSendAndGetData<Response>("", this.clientStream, (int)RoomCodes.LEAVE_ROOM_CODE);

            if (resp.status != (int)Codes.ERROR_CODE)
            {
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
            isChange = true;
            // About to be updated in the next version.
        }

        public void updateRoomPlayers(object sender, DoWorkEventArgs e)
        {
            // Getting the players connected to the room
            GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { RoomId = this.roomData.RoomId };

            while(!isChange)
            {
                GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(
                    JsonConvert.SerializeObject(request),
                    clientStream,
                    (int)Codes.GET_PLAYERS_IN_ROOM_CODE);

                players = resp.PlayersInRoom;
                workerParameter param = new workerParameter{ roomPlayers = resp.PlayersInRoom };
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
