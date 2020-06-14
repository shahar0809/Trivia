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
        private RoomData roomData;
        private bool isAdmin;
        private NetworkStream clientStream;
        private bool stopUpdatingUsers;

        public RoomAdmin(RoomData data, NetworkStream clientStream, bool isAdmin)
        {
            InitializeComponent();
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
            displayTimePerQuestion.Text = roomData.TimeForQuestion.ToString();
            displayRoomName.Text = roomData.Name;
            roomName.Text = roomData.Name;
            playersInRoom.ItemsSource = updateRoomPlayers();
        }

        private void closeRoom_Click(object sender, RoutedEventArgs e)
        {
            //Should send close room request.
            stopUpdatingUsers = true;
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }

        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            stopUpdatingUsers = true;
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }

        private void startGame_Click(object sender, RoutedEventArgs e)
        {
            stopUpdatingUsers = true;
        }

        public List<string> updateRoomPlayers()
        {
            // Getting the players connected to the room
            GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { RoomId = this.roomData.Id };

            GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(
                    JsonConvert.SerializeObject(request),
                    clientStream,
                    Codes.GET_PLAYERS_IN_ROOM_CODE);

            return resp.PlayersInRoom;
        }

        private void refreshPlayers_Click(object sender, RoutedEventArgs e)
        {
            playersInRoom.ItemsSource = updateRoomPlayers();
        }
    }
}
