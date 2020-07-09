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
using System.ComponentModel;
using System.Threading;
using ClientWPF.Requests;
using ClientWPF.Responses;
using System.Windows.Threading;

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
        public double TimeForQuestion { set; get; }
        public int IsActive { set; get; }
    };

    public struct Room
    {
        public int RoomId { set; get; }
        public string Name { set; get; }
    }

    public partial class JoinRoom : Window
    {
        private List<Room> roomsList = new List<Room>();
        private NetworkStream clientStream;
        private BackgroundWorker worker = new BackgroundWorker();
        private bool stopUpdating = false;
        public JoinRoom(NetworkStream clientStream)
        {
            InitializeComponent();
            availableRooms.ItemsSource = roomsList;
            this.clientStream = clientStream;

            // Creating a background worker that constantly updates the available rooms.
            worker.WorkerReportsProgress = true;
            worker.DoWork += updateAvailableRooms;
            worker.ProgressChanged += roomsChanged;
            worker.RunWorkerAsync();
        }

        private void availableRooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (availableRooms.SelectedItem == null)
                return;

            /* Getting the data about the room selected */
            int idIndex = ((Room)availableRooms.SelectedItem).RoomId;
            GetPlayersInRoomRequest req = new GetPlayersInRoomRequest { RoomId = ((Room)availableRooms.SelectedItem).RoomId };
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

            int idIndex = ((Room)availableRooms.SelectedItem).RoomId;
            JoinRoomRequest req = new JoinRoomRequest { RoomId = ((Room)availableRooms.SelectedItem).RoomId };
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
                stopUpdating = true;
                RoomData roomData = new RoomData
                {
                    RoomId = resp.RoomId,
                    RoomName = resp.RoomName,
                    NumOfplayers = resp.NumOfplayers,
                    NumOfQuestions = resp.NumOfQuestions,
                    TimeForQuestion = resp.TimeForQuestion,
                    IsActive = resp.IsActive
                };

                WaitInRoom obj = new WaitInRoom(roomData, clientStream, false);
                obj.Show();
                this.Close();
            }
        }

        public void updateAvailableRooms(object sender, DoWorkEventArgs e) 
        {
            while (!stopUpdating)
            {
                // Requesting available rooms from the server
                GetRoomsResponse resp = Communicator.ManageSendAndGetData<GetRoomsResponse>(clientStream, Codes.GET_ROOMS_CODE);
                WorkerParameter param = new WorkerParameter { list = resp.Rooms };
                worker.ReportProgress(0, param);

                Thread.Sleep(3000);
            }
        }

        // Updating list on screen
        void roomsChanged(object sender, ProgressChangedEventArgs e)
        {
            WorkerParameter param = (WorkerParameter)e.UserState;
            roomsList = getRoomsNames(param.list);
            availableRooms.ItemsSource = roomsList;
        }

        // Going back to the main menu
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            stopUpdating = true;
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }

        private List<Room> getRoomsNames(List<string> rooms)
        {
            //List<string> roomsNames = new List<string>();
            List<Room> availRooms = new List<Room>();

            if (rooms != null)
            {
                foreach (string room in rooms)
                {
                    var splitted = room.Split(',');
                    availRooms.Add(new Room { Name = splitted[0], RoomId = Int32.Parse(splitted[1]) });
                }
            }
            return availRooms;
        }
    }
}
