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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    /// 

    public struct RoomData
    {
        public int Id { set; get; }
        public string Name { set; get; }
        public int MaxPlayers { set; get; }
        public int NumOfQuesstions { set; get; }
        public int TimeForQuestion { set; get; }
        public int IsActive { set; get; }
    };
    public struct GetRoomsResponse
    {
        public int Status;
        public List<RoomData> Rooms;
    }
    public struct GetPlayersInRoomResponse
    {
        public List<string> Players;
    }
    public struct JoinRoomRequest
    {
        public int RoomId;
    }
    public struct JoinRoomResponse
    {
        public int Status;
        public RoomData RoomData;
    }
    public struct GetPlayersInRoomRequest
    {
        public int RoomId;
    }
    public struct GetRoomRequest
    {
        public int RoomId;
    }

    public partial class JoinRoom : Window
    {

        private NetworkStream clientStream;
        private MainWindow mainWindow;
        public JoinRoom(NetworkStream clientStream,MainWindow mainWindow)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;

            // Getting the available rooms.
            GetRoomsResponse resp = Communicator.ManageSendAndGetData<GetRoomsResponse>("", clientStream, Codes.GET_ROOM_CODE);
            availableRooms.ItemsSource = resp.Rooms;
        }

        private void availableRooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            var rooms = (ListBox)sender;
            GetPlayersInRoomRequest req = new GetPlayersInRoomRequest { RoomId = ((RoomData)rooms.SelectedItem).Id };
            string json = JsonConvert.SerializeObject(req);

            // Getting the players in the room changed
            GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(json, clientStream, Codes.GET_PLAYERS_IN_ROOM_CODE);

            // Displaying the room players in a listBox
            playersInRoom.ItemsSource = resp.Players;
        }

        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            var rooms = (ListBox)sender;
            JoinRoomRequest req = new JoinRoomRequest{ RoomId = ((RoomData)rooms.SelectedItem).Id };
            string json = JsonConvert.SerializeObject(req);

            // Requesting to join the selected items
            JoinRoomResponse resp = Communicator.ManageSendAndGetData<JoinRoomResponse>(json, clientStream, Codes.JOIN_ROOM_CODE);

            if (resp.Status == 0)
            {
                MessageBox.Show("Couldn't join room! Please try again");
                return;
            }

            var roomAdmin = new RoomAdmin(mainWindow, resp.RoomData, clientStream, false);
            roomAdmin.Show();
            this.Close();
        }
    }
}
