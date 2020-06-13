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
    public partial class RoomAdmin : Window
    {
        private MainWindow mainWindow;
        private RoomData roomData;
        private bool isAdmin;
        private NetworkStream clientStream;
        private bool stopUpdatingUsers;

        
        public RoomAdmin(MainWindow mainWindow, RoomData data, NetworkStream clientStream, bool isAdmin)
        {
            InitializeComponent();
            this.mainWindow = mainWindow;
            this.roomData= data;
            this.clientStream = clientStream;
            this.isAdmin = isAdmin;
            this.stopUpdatingUsers = false;

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
            displayMaxNumPlayers.Text = roomData.MaxPlayers.ToString();
            displayNumOfQuestions.Text = roomData.NumOfQuesstions.ToString();
            displayRoomName.Text = roomData.Name;
            displayRoomName.Text = roomData.Name;

            List<string> roomPlayers = new List<string>();
            playersInRoom.ItemsSource = roomPlayers;

            Thread updateList = new Thread(() => updateRoomPlayers(roomPlayers));
            updateList.IsBackground = true;
            updateList.Start();
            // Creating a background worker that will update the players connected to the room (into the listBox).
            /*updatePlayersWorker = new BackgroundWorker();
            updatePlayersWorker.DoWork += updateRoomPlayers;
            updatePlayersWorker.ProgressChanged += updateListBox;
            updatePlayersWorker.RunWorkerAsync();*/


        }

        private void closeRoom_Click(object sender, RoutedEventArgs e)
        {
            stopUpdatingUsers = true;
        }

        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            stopUpdatingUsers = true;
        }

        private void startGame_Click(object sender, RoutedEventArgs e)
        {
            stopUpdatingUsers = true;
        }

        public void updateRoomPlayers(List<string> roomPlayers)
        {
            // Refreshing while the room hasn't been closed or the game hasn't started.
            while (!stopUpdatingUsers)
            {
                // Getting the players connected to the room
                GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { RoomId = this.roomData.Id };

                GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(
                    JsonConvert.SerializeObject(request),
                    clientStream,
                    Codes.GET_PLAYERS_IN_ROOM_CODE);

                roomPlayers = resp.Players;
            }
        }
    }
}
