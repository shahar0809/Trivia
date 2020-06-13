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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow;
        public const int ERROR_CODE = 0;
        private struct LoginRequest
        {
            public string Username { set; get; }
            public string Password { set; get; }  
        }
        public Login(NetworkStream clientStream, MainWindow mainWindow)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            mainWindow.Show();
            this.Close();
        }
        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            LoginRequest login = new LoginRequest 
            { 
                Password = passwordBox.Text,
                Username = usernameBox.Text
            };

            // Edit and send login request.
            string json = JsonConvert.SerializeObject(login, Formatting.Indented);
            Response loginResponse = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.LOGIN_CODE);

            if (loginResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Login Failed. Please make sure you're signed up!");
            }

            // Closing the Log in window and returing to the menu.
            this.mainWindow.Show();
            this.Close();
        }
    }
}
