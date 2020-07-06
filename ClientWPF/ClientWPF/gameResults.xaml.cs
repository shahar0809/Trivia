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
        public double averageAnswerTime { get; set; }
    }

    public struct GetGameResultsResponse
    {
        public int status { get; set; }
        public List<string> Results { set; get; }
    }

    public partial class GameResults : Window
    {
        private NetworkStream clientStream;
        public GameResults(NetworkStream clientStream)
        {
            this.clientStream = clientStream;
            InitializeComponent();

            // Requesting game results from the server
            GetGameResultsResponse resp = 
                Communicator.ManageSendAndGetData<GetGameResultsResponse>("", clientStream, Codes.GET_GAME_RESULTS_CODE);

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
                 winnerUsername.Text = (string)resp.Results[0].Split(',')[0] ;
                List<PlayerResults> results = new List<PlayerResults>();
                foreach (string playerResult in resp.Results)
                {
                    PlayerResults player = new PlayerResults
                    {
                        username = playerResult.Split(',')[0],
                        correctAnswersCount = int.Parse(playerResult.Split(',')[1]),
                        wrongAnswersCount = int.Parse(playerResult.Split(',')[2]),
                        averageAnswerTime = double.Parse(playerResult.Split(',')[3])
                    };
                    results.Add(player);
                }

                // Displaying all the results in the data grid
                playersResult.ItemsSource = results;
            }
        }

        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }
    }
}
