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
using Newtonsoft.Json;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for Questions.xaml
    /// </summary>
    public partial class Questions : Window
    {
        private struct Answers
        {
            public int index;
            public string answer;
        }
        private struct GetQuestionResponse
        {
            public int Status;
            public string Question;
            public List<Answers> Answers;
        }
        private struct SubmitAnswerRequest
        {
            public int answerId { set; get; }
        }

        private struct SubmitAnswerResponse
        {
            public int status { set; get; }
            public int correctAnswerId { set; get; }
        }

        private NetworkStream clientStream;
        public Questions(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            GetQuestionResponse getQuestion =
                Communicator.ManageSendAndGetData<GetQuestionResponse>("", clientStream, (int)Codes.GET_QUESTION_CODE);
            QuestionText.Text = getQuestion.Question;
            answer1.Content = getQuestion.Answers[1];
            answer2.Content = getQuestion.Answers[2];
            answer3.Content = getQuestion.Answers[3];
            answer4.Content = getQuestion.Answers[4];
        }
        private void firstAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(1);
        }

        private void secondAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(2);
        }

        private void thirdAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(3);
        }

        private void fourthAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(4);
        }

        private bool sendSubmitAnswer(int answerId)
        {
            SubmitAnswerRequest submitAns = new SubmitAnswerRequest
            {
                answerId = answerId
            };

            // Edit and send question request.
            string json = JsonConvert.SerializeObject(submitAns, Formatting.Indented);
            SubmitAnswerResponse sendAns = 
                Communicator.ManageSendAndGetData<SubmitAnswerResponse>(json, clientStream, (int)Codes.LOGIN_CODE);
            return sendAns.correctAnswerId == answerId;
        }
    }
}
