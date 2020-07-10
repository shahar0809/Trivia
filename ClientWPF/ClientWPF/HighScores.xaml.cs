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
    /// Interaction logic for HighScores.xaml
    /// </summary>

    public partial class HighScores : Window
    {
        private NetworkStream clientStream;
        private string m_username;
        private const char delimeter = ',';
        private const int numOfHighScores = 5;
        private List<Tuple<TextBlock, TextBlock>> table;

        private struct HighScore
        {
            public string Name { set; get; }
            public int Score { set; get; }
        }

        public HighScores(NetworkStream clientStream, string username)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            m_username = username;
            usernameBox.Text = username;

            // Initializing row tables to list
            table = new List<Tuple<TextBlock, TextBlock>>();
            table.Add(Tuple.Create(firstName, firstScore));
            table.Add(Tuple.Create(secondName, secondScore));
            table.Add(Tuple.Create(thirdName, thirdScore));
            table.Add(Tuple.Create(fourthName, fourthScore));
            table.Add(Tuple.Create(fifthName, fifthScore));

            getHighScores();
        }

        void getHighScores()
        {
            StatisticResponse resp = Communicator.ManageSendAndGetData<StatisticResponse>(clientStream, Codes.GET_STATISTICS_CODE);
            var highScores = extractHighScores(resp.HighScores);

            for(int i = 0; i < numOfHighScores; i++)
            {
                table[i].Item1.Text = highScores[i].Name;
                table[i].Item2.Text = highScores[i].Score.ToString();
            }
        }

        private void goBackButton_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream, m_username);
            mainWindow.Show();
            this.Close();
        }

        // Convert the highscores list from a list of strings into a List of HighScores
        private List<HighScore> extractHighScores(List<string> buffer)
        {
            List<HighScore> highScoresList = new List<HighScore>();

            foreach (var score in buffer)
            {
                var splitted = score.Split(delimeter);
                highScoresList.Add(new HighScore { Name = splitted[0], Score = Int32.Parse(splitted[1]) });
            }

            return highScoresList;
        }
    }
}
