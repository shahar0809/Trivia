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
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Window
    {
        private NetworkStream clientStream;
        private MainWindow mainWindow;
        public HighScores(NetworkStream clientStream,MainWindow mainWindow,string highScores)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            this.mainWindow = mainWindow;

            string[] highScoresArr = new string[10];
            highScoresArr = highScores.Split(',');
            firstName.Text = highScoresArr[0];
            firstScore.Text = highScoresArr[1];
            secondName.Text = highScoresArr[2];
            secondScore.Text = highScoresArr[3];
            thirdName.Text = highScoresArr[4];
            thirdScore.Text = highScoresArr[5];
            fourthName.Text = highScoresArr[6];
            fourthScore.Text = highScoresArr[7];
            fifthName.Text = highScoresArr[8];
            fifthScore.Text = highScoresArr[9];
        }
        private void goBackButton_Click(object sender, RoutedEventArgs e)
        {
            var mainWindow = new MainWindow(this.clientStream);
            mainWindow.Show();
            this.Close();
        }
        
    }
}
