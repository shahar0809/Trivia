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
using ClientWPF.Requests;
using ClientWPF.Responses;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for MyStatistics.xaml
    /// </summary>
    public partial class MyStatistics : Window
    {
        private NetworkStream clientStream;
        private string m_usrename;
        private const char delimeter = ',';

        public MyStatistics(NetworkStream clientStream, string username)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            m_usrename = username;
            usernameBox.Text = username;
            getUserStats();
        }

        void getUserStats()
        {
            StatisticResponse resp = Communicator.ManageSendAndGetData<StatisticResponse>(clientStream, Codes.GET_STATISTICS_CODE);
            
            extractStats(resp.UserStatistics);
        }

        void extractStats(string buffer)
        {
            var stats = buffer.Split(delimeter);
            displayAvgTime.Text = stats[0];
            displayNumOfCorrectAns.Text = stats[1];
            displayNumOfAns.Text = stats[2];
            displayNumOfGames.Text = stats[3];
        }

        private void backToMainWindow_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream, m_usrename);
            mainWindow.Show();
            this.Close();
        }
    }
}
