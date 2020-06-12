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
        private struct GetStatisticsResponse
        {
            public int status;
            public string HighScores;
            public string UserStatistics;
        }

        private NetworkStream clientStream;
        private MainWindow mainWindow;
        private GetStatisticsResponse resp;
        public Statistics(NetworkStream clientStream,MainWindow mainWindow)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;

            // Getting the available rooms.
             resp = Communicator.ManageSendAndGetData<GetStatisticsResponse>("", clientStream, Codes.GET_STATISTICS_CODE);
            
        }

        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            var MyStatistics = new MyStatistics(clientStream,mainWindow,resp.UserStatistics); //create the login form.
            MyStatistics.Show(); //show the form.
            this.Close();
        }
        private void MyButton2_Click(object sender, RoutedEventArgs e)
        {
            var HighScores = new HighScores(clientStream,mainWindow,resp.HighScores);
            HighScores.Show();
            this.Close();
        }
    }
}
