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
        private string m_username;

        public MainWindow()
        {
            InitializeComponent();
            updateButtons(false);
            m_username = "";

            //Initiate the socket with all the details.
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 1050);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
        }

        public MainWindow(NetworkStream clientStream, string username)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            m_username = username;
            usernameBox.Text = username;

            if (m_username != "")
                updateButtons(true);
            else
                updateButtons(false);
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
            var CreateRoom = new CreateRoom(clientStream, m_username);
            CreateRoom.Show();
            this.Close();
        }

        private void joinRoomButtonClicked(object sender, RoutedEventArgs e)
        {
            var JoinRoom = new JoinRoom(clientStream, m_username);
            JoinRoom.Show();
            this.Close();
        }

        private void statsButtonClicked(object sender, RoutedEventArgs e)
        {
            var stats = new MyStatistics(clientStream, m_username);
            stats.Show();
            this.Close();
        }

        private void exitButtonClicked(object sender, RoutedEventArgs e)
        {
            this.clientStream.Close();
            this.Close();
        }

        private void updateButtons(bool val)
        {
            createRoomButton.IsEnabled = val;
            joinRoomButton.IsEnabled = val;
            MyStatisticsButton.IsEnabled = val;
            HighScoresButton.IsEnabled = val;
            loginButton.IsEnabled = !val;
            signupButton.IsEnabled = !val;
        }

        private void HighScoresButton_Click(object sender, RoutedEventArgs e)
        {
            var highScoresWindow = new HighScores(clientStream, m_username);
            highScoresWindow.Show();
            this.Close();
        }
    }
}