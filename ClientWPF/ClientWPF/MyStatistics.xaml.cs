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
    /// Interaction logic for MyStatistics.xaml
    /// </summary>
    public partial class MyStatistics : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow; 
        public MyStatistics(NetworkStream clientStream, MainWindow mainWindow, UserStats userStats)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;

            // Displaying each statistic in its own text box.
            displayNumOfGames.Text = "Games Played: " + userStats.NumOfGames;
            displayNumOfCorrectAns.Text = "Correct Answers: " + userStats.CorrectAnswers.ToString();
            displayNumOfAns.Text = "Total Answers: " + userStats.TotalAnswers.ToString();
            displayAvgTime.Text = "Average Answer Time: " + userStats.AvgAnswerTime.ToString();
        }

        private void backToMainWindow_Click(object sender, RoutedEventArgs e)
        {
            this.mainWindow.Show();
            this.Close();
        }
    }
}
