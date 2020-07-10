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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Window
    {
        private NetworkStream clientStream;
        public const int DATA_START_INDEX = 5;
        public const int DATA_END_INDEX = 14;
        
        public SignUp(NetworkStream clientStream)
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

        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            SignUpRequest signUp = new SignUpRequest
            {
                Password = passwordBox.Password,
                Username = usernameBox.Text,
                Email = emailBox.Text
            };
            
            // Edit and send signUp request.
            string json = JsonConvert.SerializeObject(signUp, Formatting.Indented);
            Response signUpResponse = Communicator.ManageSendAndGetData<Response>(json, clientStream, Codes.SIGN_UP_CODE);

            if (signUpResponse.status == (int)Codes.ERROR_CODE)
            {
                ErrorBox.Visibility = Visibility.Visible;
            }

            // Going back to the main menu
            var mainWindow = new MainWindow(this.clientStream, "");
            mainWindow.Show();
            Close();
        }
    }
}
