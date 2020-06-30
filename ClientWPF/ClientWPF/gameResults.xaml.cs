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
    /// Interaction logic for gameResults.xaml
    /// </summary>
    /// 

    public struct PlayerResults
    {
        public string username { get; set; }
        public int correctAnswersCount { get; set; }
        public int wrongAnswersCount { get; set; }
        public int averageAnswerTime { get; set; }
    }

    public struct GetGameResultsResponse
    { 
        public int status { get; set; }
        public List<PlayerResults> playerResults { set; get; }
    }

    public partial class GameResults : Window
    {
        private NetworkStream clientStream;
        public GameResults(NetworkStream clientStream)
        {
            InitializeComponent();
            /* GetGameResultsResponse resp = Communicator.ManageSendAndGetData<GetGameResultsResponse>("", clientStream, (int)Codes.GET_GAME_RESULTS_CODE);

             if (resp.status == (int)Codes.ERROR_CODE)
             {
                 MessageBox.Show("Couldn't load the scores!");
                 var mainWindow = new MainWindow(this.clientStream);
                 mainWindow.Show();
                 this.Close();
             }
             else
             {
                 // Displaying the winner's username 
                 winnerUsername.Text = resp.playerResults[0].username;

                 // Displaying all the results in the data grid
                 displayPlayersResults.ItemsSource = resp.playerResults;
             }*/
            PlayerResults r1 = new PlayerResults { username = "a", averageAnswerTime = 7, correctAnswersCount = 50, wrongAnswersCount = 6 };
            PlayerResults r2 = new PlayerResults { username = "b", averageAnswerTime = 2, correctAnswersCount = 4, wrongAnswersCount = 7 };
            PlayerResults r3 = new PlayerResults { username = "e", averageAnswerTime = 4, correctAnswersCount = 36, wrongAnswersCount = 3 };
            PlayerResults r4 = new PlayerResults { username = "c", averageAnswerTime = 9, correctAnswersCount = 1, wrongAnswersCount = 69 };
            PlayerResults r5 = new PlayerResults { username = "d", averageAnswerTime = 6, correctAnswersCount = 54, wrongAnswersCount = 420 };
            List<PlayerResults> l = new List<PlayerResults>();
            l.Add(r1);
            l.Add(r2);
            l.Add(r3);
            l.Add(r4);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            l.Add(r5);
            winnerUsername.Text = r1.username;
            playersResult.ItemsSource = l;
        }

        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }
    }
}
