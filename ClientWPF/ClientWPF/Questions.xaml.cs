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
using System.Threading;

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
            public List<List<object>> Answers;
        }
        private struct SubmitAnswerRequest
        {
            public int CorrectAnswerId { set; get; }
        }

        private struct SubmitAnswerResponse
        {
            public int status { set; get; }
            public int CorrectAnswerId { set; get; }
        }

        private NetworkStream clientStream;
        public Questions(NetworkStream clientStream)
        {
            InitializeComponent();
            this.clientStream = clientStream;
            getQuestion();
        }
        public void getQuestion()
        {
            GetQuestionResponse getQuestion =
                Communicator.ManageSendAndGetData<GetQuestionResponse>("", clientStream, (int)Codes.GET_QUESTION_CODE);

            QuestionText.Text = getQuestion.Question;
            answer1.Content = getQuestion.Answers[0][1];
            answer2.Content = getQuestion.Answers[1][1];
            answer3.Content = getQuestion.Answers[2][1];
            answer4.Content = getQuestion.Answers[3][1];
        }
        private void firstAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(1);
            //colorButtons(correct, 1);
            //Thread.Sleep(2000);
            getQuestion();
        }

        private void secondAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(2);
            //colorButtons(correct, 2);
            //Thread.Sleep(2000);
            getQuestion();
        }

        private void thirdAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(3);
            //colorButtons(correct, 3);
            //Thread.Sleep(2000);
            getQuestion();
        }

        private void fourthAnswerButton_Click(object sender, RoutedEventArgs e)
        {
            int correct = sendSubmitAnswer(4);
            //colorButtons(correct, 4);
            //Thread.Sleep(2000);
            getQuestion();
        }

        private int sendSubmitAnswer(int answerId)
        {
            SubmitAnswerRequest submitAns = new SubmitAnswerRequest
            {
                CorrectAnswerId = answerId
            };

            // Edit and send question request.
            string json = JsonConvert.SerializeObject(submitAns, Formatting.Indented);
            SubmitAnswerResponse sendAns = 
                Communicator.ManageSendAndGetData<SubmitAnswerResponse>(json, clientStream, (int)Codes.SUBMIT_ANS_CODE);
            return sendAns.CorrectAnswerId;
        }
      
        //This function will color the right or wrong question.
        /*private int colorButtons(int correctAns,int ans)
        {
            if(correctAns == ans == 1)
            {
                answer1.Background = new SolidColorBrush(Colors.Green);
            }
            if (ans == 1)
            {
                answer1.Background = new SolidColorBrush(Colors.Red);
            }
            if (correctAns == 1 && ans == 1)
            {
                answer4.Background = new SolidColorBrush(Colors.Green);
            }
            if (correctAns == 1 && ans == 1)
            {
                answer4.Background = new SolidColorBrush(Colors.Green);
            }
            if (correctAns == 1 && ans == 1)
            {
                answer4.Background = new SolidColorBrush(Colors.Green);
            }
            if (correctAns == 1 && ans == 1)
            {
                answer4.Background = new SolidColorBrush(Colors.Green);
            }
        }*/
    }
}
