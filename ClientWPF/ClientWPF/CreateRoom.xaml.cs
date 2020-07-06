﻿using System;
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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        private NetworkStream clientStream;
        public const int ERROR_CODE = 0;

        public struct CreateRoomRequest
        {
            public string RoomName { set; get; }
            public int NumOfPlayers { set; get; }
            public int NumOfQuestions { set; get; }
            public double TimeForQuestion { set; get; }
        }

        private struct CreateRoomResponse
        {
            public int Status { set; get; }
            public int RoomId { set; get; }
        }
        public CreateRoom(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }

        private void Submit_Button_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(roomName.Text) || string.IsNullOrWhiteSpace(numOfPlayers.Text)
                || string.IsNullOrWhiteSpace(numOfQuestions.Text) || string.IsNullOrWhiteSpace(timeout.Text))
            {
                MessageBox.Show("Please fill all the fields!");
                return;
            }

            CreateRoomRequest createRoom = new CreateRoomRequest
            {
                RoomName = roomName.Text,
                NumOfPlayers = int.Parse(numOfPlayers.Text),
                NumOfQuestions = int.Parse(numOfQuestions.Text),
                TimeForQuestion = double.Parse(timeout.Text),
            };

            string json = JsonConvert.SerializeObject(createRoom, Formatting.Indented);
            CreateRoomResponse createRoomResponse = 
                Communicator.ManageSendAndGetData<CreateRoomResponse>(json, clientStream, Codes.CREATE_ROOM_CODE);

            if (createRoomResponse.Status == ERROR_CODE)
            {
                MessageBox.Show("Error! , can't create room");
                var mainWindow = new MainWindow(clientStream);
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

                MessageBox.Show("about to open room admin.");
                // Show the room details to the admin.
                var waitInRoom = new WaitInRoom(roomData, clientStream, true);
                waitInRoom.Show();
            }
            Close();
        }

        private void cancel_Click(object sender, RoutedEventArgs e)
        {
            // Closing the Log in window and returing to the menu.
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }
    }
}
