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
        public const int DATA_START_INDEX = 5;
        public const int DATA_END_INDEX = 14;
        public const int ERROR_CODE = 0;
        private struct LoginRequest
        {
            public string username { set; get; }
            public string password { set; get; }  
        }
        public Login(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            var MainWindow = new MainWindow();
            MainWindow.Show();
            this.Close();
        }
        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            LoginRequest login = new LoginRequest { password = password.Text, username = userName.Text };

            //Edit and send login request.
            string json = JsonConvert.SerializeObject(login, Formatting.Indented);
            json = MainWindow.EditRequest((int)MainWindow.Codes.LOGIN_CODE, json);
            MainWindow.SendRequest(json, this.clientStream);

            //Get login response.
            string textStrData = MainWindow.GetData(this.clientStream).Substring(DATA_START_INDEX ,DATA_END_INDEX);
            MainWindow.Response loginResponse = JsonConvert.DeserializeObject<MainWindow.Response>(textStrData);

            if (loginResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Sorry! There is no such user\n please sign up");
            }
            var MainWindowMenu = new MainWindow();
            MainWindowMenu.Show();
            this.Close();
        }
    }
}
