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
        public int RoomId { set; get; }
        public string RoomName { set; get; }
        public int NumOfplayers { set; get; }
        public int NumOfQuestions { set; get; }
        public int TimeForQuestion { set; get; }
        public int IsActive { set; get; }
    };
    public struct GetRoomsResponse
    {
        public int Status;
        public List<string> Rooms;
    }
    public struct GetPlayersInRoomResponse
    {
        public List<string> PlayersInRoom;
    }
    public struct JoinRoomRequest
    {
        public int RoomId;
    }
    public struct JoinRoomResponse
    {
        public int Status;
        public int RoomId;
        public string RoomName;
        public int NumOfplayers;
        public int NumOfQuestions;
        public int TimeForQuestion;
        public int IsActive;
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
        public JoinRoom(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;

            // Getting the available rooms.
            availableRooms.ItemsSource = updateAvailableRooms();
        }

        private void availableRooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            var rooms = (ListBox)sender;
            int idIndex = rooms.SelectedItem.ToString().LastIndexOf(':');
            GetPlayersInRoomRequest req = new GetPlayersInRoomRequest { RoomId = int.Parse(rooms.SelectedItem.ToString().Substring(idIndex+2)) };
            string json = JsonConvert.SerializeObject(req);

            // Getting the players in the room changed
            GetPlayersInRoomResponse resp = Communicator.ManageSendAndGetData<GetPlayersInRoomResponse>(json, clientStream, Codes.GET_PLAYERS_IN_ROOM_CODE);

            // Displaying the room players in a listBox
            playersInRoom.ItemsSource = resp.PlayersInRoom;
        }

        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            //var rooms = (ListBox)sender;
            int idIndex = availableRooms.SelectedItem.ToString().LastIndexOf(':');
            JoinRoomRequest req = new JoinRoomRequest{ RoomId = int.Parse(availableRooms.SelectedItem.ToString().Substring(idIndex+2)) };
            string json = JsonConvert.SerializeObject(req);

            // Requesting to join the selected items
            JoinRoomResponse resp = Communicator.ManageSendAndGetData<JoinRoomResponse>(json, clientStream, Codes.JOIN_ROOM_CODE);

            if (resp.Status == 0)
            {
                MessageBox.Show("Couldn't join room! Please try again");
                return;
            }
            else
            {
                RoomData roomData = new RoomData
                {
                    RoomId = resp.RoomId,
                    RoomName = resp.RoomName,
                    NumOfplayers = resp.NumOfplayers,
                    NumOfQuestions = resp.NumOfQuestions,
                    TimeForQuestion = resp.TimeForQuestion,
                    IsActive = resp.IsActive
                };

                var roomAdmin = new RoomAdmin(roomData, clientStream, false);
                roomAdmin.Show();
                this.Close();
            }
        }
        private void refreshGames_Click(object sender, RoutedEventArgs e)
        {
            availableRooms.ItemsSource = updateAvailableRooms();
        }

        public List<string> updateAvailableRooms()
        {
            GetRoomsResponse resp = Communicator.ManageSendAndGetData<GetRoomsResponse>("",
                    clientStream,
                    Codes.GET_ROOM_CODE);
            List<string> rooms = new List<string>();
            foreach (string room in resp.Rooms)
            {
                var splitted = room.Split(',');
                int id = Int32.Parse(splitted[1]);
                string name = splitted[0];
                rooms.Add("Name: "+name+", Id: "+id.ToString());
            }
            return rooms;
        }
    }
}
