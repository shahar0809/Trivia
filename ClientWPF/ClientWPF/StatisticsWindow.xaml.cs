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

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>

    public struct Question
    {
        public string question;
        public string correctAns;
        public string ans2;
        public string ans3;
        public string ans4;
    }

    public struct UserStats
    {
        public float AvgAnswerTime;
        public int CorrectAnswers;
        public int TotalAnswers;
        public int NumOfGames;
    }

    public struct HighScore
    {
        public string name;
        public int score;
    }

    public struct Statistics
    {
        public UserStats userStats;
        public List<HighScore> highScore;
    }

    public partial class StatisticsWindow : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow;
        private Statistics stats;
        public StatisticsWindow(NetworkStream clientStream, MainWindow main)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = main;

            // Sending message.
            stats = Communicator.ManageSendAndGetData<Statistics>("", clientStream, Codes.GET_STATISTICS_CODE);
        }

        private void myStatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            var MyStatistics = new MyStatistics(clientStream, mainWindow, stats.userStats);
            MyStatistics.Show();
            this.Close();
        }

        private void highScoresButton_Click(object sender, RoutedEventArgs e)
        {
            var HighScores = new HighScores(clientStream, mainWindow, stats.highScore);
            HighScores.Show();
            this.Close();
        }

        private void backToMainWindow_Click(object sender, RoutedEventArgs e)
        {
            mainWindow.Show();
            this.Close();
        }
    }
}
