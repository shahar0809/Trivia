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

        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            var MainWindow = new MainWindow();
            MainWindow.Show();
            this.Close();
        }
        private void MyButton2_Click(object sender, RoutedEventArgs e)
        {
            LoginRequest login = new LoginRequest { password = password.Text, username = userName.Text };
            string json = JsonConvert.SerializeObject(login, Formatting.Indented);
            json = MainWindow.EditRequest((int)MainWindow.Codes.LOGIN_CODE, json);
            byte[] buffer = new ASCIIEncoding().GetBytes(json);
            clientStream.Write(buffer, 0, buffer.Length);

            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            string s  =  Encoding.ASCII.GetString(buffer);
            string x = MainWindow.GetBytesFromBinaryString(s);
            Console.WriteLine(x.Substring(5, 14));
            MainWindow.Response d = JsonConvert.DeserializeObject<MainWindow.Response>(x.Substring(5,14));
            if(d.status == 0)
            {
                MessageBox.Show("Sorry! There is no such user\n please sign up");
               
            }
            var MainWindowMenu = new MainWindow();
            MainWindowMenu.Show();
            this.Close();
        }
    }
}
