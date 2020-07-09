using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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
using ClientWPF.Responses;
using ClientWPF.Requests;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>

    public struct UserStats
    {
        public float AvgAnswerTime;
        public int CorrectAnswers;
        public int TotalAnswers;
        public int NumOfGames;
    }

    public partial class StatisticsWindow : Window
    {
        private NetworkStream clientStream;
        private StatisticRequest stats;

        public StatisticsWindow(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;

            // Sending a GetStatistics request.
            stats = Communicator.ManageSendAndGetData<StatisticRequest>(clientStream, Codes.GET_STATISTICS_CODE);
        }

        private void myStatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            string[] userStats = stats.UserStatistics.Split(',');

            UserStats statistic = new UserStats
            {
                AvgAnswerTime = float.Parse(userStats[0]),
                CorrectAnswers = int.Parse(userStats[1]),
                TotalAnswers = int.Parse(userStats[2]),
                NumOfGames = int.Parse(userStats[3])
            };

            // Opening a My Statistics window.
            var MyStatistics = new MyStatistics(clientStream, statistic);
            MyStatistics.Show();
            this.Close();
        }

        private void highScoresButton_Click(object sender, RoutedEventArgs e)
        {
            var HighScores = new HighScores(clientStream, stats.HighScores);
            HighScores.Show();
            this.Close();
        }

        private void backToMainWindow_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }
    }
}
