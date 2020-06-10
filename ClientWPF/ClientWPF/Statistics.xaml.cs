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

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        public Statistics()
        {
            InitializeComponent();
        }
        private void MyButton_Click(object sender, RoutedEventArgs e)
        {
            var MyStatistics = new MyStatistics(); //create the login form.
            MyStatistics.Show(); //show the form.
            this.Close();
        }
        private void MyButton2_Click(object sender, RoutedEventArgs e)
        {
            var HighScores = new HighScores();
            HighScores.Show();
            this.Close();
        }
    }
}
