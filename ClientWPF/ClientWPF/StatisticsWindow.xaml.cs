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
        public float avgAnswerTime;
        public int correctAnswers;
        public int totalAnswers;
        public int numOfGames;
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
        public StatisticsWindow(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
        }

        private void myStatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            UserStats userStats = new UserStats { };
            var MyStatistics = new MyStatistics(clientStream, userStats);
            MyStatistics.Show();
            this.Close();
        }

        private void highScoresButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void backToMainWindow_Click(object sender, RoutedEventArgs e)
        {
            var MainWindow = new MainWindow();
            MainWindow.Show();
            this.Close();
        }
    }
}
