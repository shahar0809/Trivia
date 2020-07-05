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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Net;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        private NetworkStream clientStream;
        public MainWindow()
        {

            InitializeComponent();

            //Initiate the socket with all the details.
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 1050);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();

            //var ques = new q(clientStream, new TimeSpan(0, 0, 20));
            //ques.Show();
            //this.Close();
        }


        public MainWindow(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }
        private void loginButtonClicked(object sender, RoutedEventArgs e)
        {
            var Login = new Login(clientStream); // Create the login form.
            Login.Show(); // Show the form.
            this.Close();
        }
        private void signupButtonClicked(object sender, RoutedEventArgs e)
        {
            var SignUp = new SignUp(clientStream);
            SignUp.Show();
            this.Close();
        }

        private void createRoomButtonClicked(object sender, RoutedEventArgs e)
        {
            var CreateRoom = new CreateRoom(clientStream);
            CreateRoom.Show();
            this.Close();
        }

        private void joinRoomButtonClicked(object sender, RoutedEventArgs e)
        {
            var JoinRoom = new JoinRoom(clientStream);
            JoinRoom.Show();
            this.Close();
        }

        private void statsButtonClicked(object sender, RoutedEventArgs e)
        {
            var StatisticsWindow = new StatisticsWindow(clientStream);
            StatisticsWindow.Show();
            this.Close();
        }

        private void exitButtonClicked(object sender, RoutedEventArgs e)
        {
            this.clientStream.Close();
            this.Close();
        }
    }
}