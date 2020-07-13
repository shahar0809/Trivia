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
using ClientWPF.Responses;
using ClientWPF.Requests;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for Login.xaml
    /// </summary>
    
    public partial class Login : Window
    {
        private NetworkStream clientStream;

        public Login(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream, "");
            mainWindow.Show();
            this.Close();
        }
        private async void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(passwordBox.Password) || string.IsNullOrWhiteSpace(usernameBox.Text))
            {
                MessageBox.Show("Please fill all the fields!");
                return;
            }
            LoginRequest login = new LoginRequest
            {
                Password = passwordBox.Password,
                Username = usernameBox.Text
            };

            // Edit and send login request.
            string json = JsonConvert.SerializeObject(login, Formatting.Indented);
            Response loginResponse = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.LOGIN_CODE);

            string userName;
            if (loginResponse.status == (int)Codes.ERROR_CODE)
            {
                ErrorBox.Visibility = Visibility.Visible;
                await Task.Delay(1000);
                userName = "";
            }
            else
            {
                userName = login.Username;
            }

            // Closing the Log in window and returing to the menu.
            var mainWindow = new MainWindow(this.clientStream, userName);
            mainWindow.Show();
            this.Close();
        }
    }
}
