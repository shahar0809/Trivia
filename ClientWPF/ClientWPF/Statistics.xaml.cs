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

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        private NetworkStream clientStream;
        public Statistics(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }
        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            var MyStatistics = new MyStatistics(clientStream); //create the login form.
            MyStatistics.Show(); //show the form.
            this.Close();
        }
        private void MyButton2_Click(object sender, RoutedEventArgs e)
        {
            var HighScores = new HighScores(clientStream);
            HighScores.Show();
            this.Close();
        }
    }
}
