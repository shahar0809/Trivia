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

    struct RoomData
    {
        public int id { set; get; }
        public string name { set; get; }
        public int maxPlayers { set; get; }
        public int timeForQuestion { set; get; }
        public int isActive { set; get; }
    };
    public partial class JoinRoom : Window
    {
        
        private struct GetRoomsResponse
        {
            public int status;
            public List<RoomData> rooms;
        }
        private struct GetPlayersInRoomResponse
        {
            public List<string> players;
        }
        private struct JoinRoomRequest
        {
            public int roomId;
        }
        
        private struct GetPlayersInRoomRequest
        {
            public int roomId;
        }

        private NetworkStream clientStream;
        public JoinRoom(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;

            // Getting the available rooms.
            GetRoomsResponse resp = Communicator.ManageSendAndGetData<GetRoomsResponse>("", clientStream, Codes.GET_ROOM_CODE);
            availableRooms.ItemsSource = resp.rooms;
        }

        private void availableRooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            var rooms = (ListBox)sender;
            GetPlayersInRoomRequest req = new GetPlayersInRoomRequest { roomId = ((RoomData)rooms.SelectedItem).id };
            string json = JsonConvert.SerializeObject(req);

            // Getting the players in the room changed
            GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(json, clientStream, Codes.GET_PLAYERS_IN_ROOM_CODE);

            // Displaying the room players in a listBox
            playersInRoom.ItemsSource = resp.players;
        }

        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            var rooms = (ListBox)sender;
            JoinRoomRequest req = new JoinRoomRequest{ roomId = ((RoomData)rooms.SelectedItem).id };
            string json = JsonConvert.SerializeObject(req);

            // Requesting to join the selected items
            Response resp = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.JOIN_ROOM_CODE);
        }
    }
}
