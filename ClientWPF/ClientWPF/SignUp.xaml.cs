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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow;
        public const int DATA_START_INDEX = 5;
        public const int DATA_END_INDEX = 14;
        public const int ERROR_CODE = 0;
        private struct SignUpRequest
        {
            public string username { set; get; }
            public string password { set; get; }
            public string email { set; get; }
        }
        public SignUp(NetworkStream clientStream,MainWindow mainWindow)
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
            SignUpRequest signUp = new SignUpRequest 
            {
                password = password.Text,
                username = username.Text,
                email=email.Text
            };

            // Edit and send signUp request.
            string json = JsonConvert.SerializeObject(signUp, Formatting.Indented);
            Response signUpResponse = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.SIGN_UP_CODE);

            if (signUpResponse.status == ERROR_CODE)
            {
                MessageBox.Show("Sorry! Username was taken \n please change your username ");
            }
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            Close();
        }
    }
}
