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
using System.Threading;
using System.ComponentModel;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for gameResults.xaml
    /// </summary>

    public struct PlayerResults
    {
        public string username { get; set; }
        public int correctAnswersCount { get; set; }
        public int wrongAnswersCount { get; set; }
        public string averageAnswerTime { get; set; }

        public PlayerResults(string result)
        {
            username = result.Split(',')[0];
            correctAnswersCount = int.Parse(result.Split(',')[1]);
            wrongAnswersCount = int.Parse(result.Split(',')[2]);
            averageAnswerTime = (double.Parse(result.Split(',')[3])).ToString("#.000");
        }
    }

    public partial class GameResults : Window
    {
        private NetworkStream clientStream;
        private string m_username;
        private BackgroundWorker m_worker;
        private GetGameResultsResponse resp;

        public GameResults(NetworkStream clientStream, string username)
        {
            InitializeComponent();

            this.clientStream = clientStream;
            m_username = username;

            m_worker = new BackgroundWorker();
            m_worker.DoWork += checkForResults;
            m_worker.RunWorkerCompleted += gotResults;
            m_worker.RunWorkerAsync();
        }

        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream, m_username);
            mainWindow.Show();
            this.Close();
        }

        private void checkForResults(object sender, DoWorkEventArgs e)
        {
            resp = Communicator.ManageSendAndGetData<GetGameResultsResponse>("", clientStream, Codes.GET_GAME_RESULTS_CODE);

            while (resp.Status == (int)Codes.ERROR_CODE)
            {
                resp = Communicator.ManageSendAndGetData<GetGameResultsResponse>("", clientStream, Codes.GET_GAME_RESULTS_CODE);
                Thread.Sleep(1000);
            }            
        }

        private void gotResults(object sender, RunWorkerCompletedEventArgs e)
        {
            TableGrid.Visibility = Visibility.Visible;
            UserMessage.Visibility = Visibility.Collapsed;
            winnerUsername.Visibility = Visibility.Visible;

            // Displaying the winner's username 
            winnerUsername.Text = (string)resp.Results[0].Split(',')[0];

            // Getting a list of the player results
            List<PlayerResults> results = new List<PlayerResults>();
            foreach (string playerResult in resp.Results)
            {
                results.Add(new PlayerResults(playerResult));
            }

            // Displaying all the results in the data grid
            playersResult.ItemsSource = results;
        }
    }
}
