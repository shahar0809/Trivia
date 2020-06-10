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
using System.Net.Sockets;
using System.Net;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private NetworkStream clientStream;
        public MainWindow()
        {
            InitializeComponent();
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 1050);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
        }
        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            var Login = new Login(clientStream); //create the login form.
            Login.Show(); //show the form.
            this.Close(); 
        }
        private void MyButton2_Click(object sender, RoutedEventArgs e)
        {
            var SignUp = new SignUp(clientStream);
            SignUp.Show(); 
            this.Close();
        }

        private void MyButton3_Click(object sender, RoutedEventArgs e)
        {
            var CreateRoom = new CreateRoom(clientStream);
            CreateRoom.Show();
            this.Close();
        }

        private void MyButton4_Click(object sender, RoutedEventArgs e)
        {
            var JoinRoom = new JoinRoom(clientStream);
            JoinRoom.Show();
            this.Close();
        }

        private void MyButton5_Click(object sender, RoutedEventArgs e)
        {
            var Statistics = new Statistics(clientStream);
            Statistics.Show();
            this.Close();
        }

        private void MyButton6_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
