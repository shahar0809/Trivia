using Newtonsoft.Json;
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
using System.Windows.Threading;

namespace ClientWPF
{
    /// <summary>
    /// Interaction logic for DisplayQuestion.xaml
    /// </summary>
    /// 
    public partial class DisplayQuestion : Window
    {
        private const int timerWarning = 10;
        private const int numOfPossibleAnswers = 4;
        private TimeSpan m_time;
        private DispatcherTimer m_timer;
        private List<Tuple<Button, TextBlock>> m_answersButtons;
        private NetworkStream clientStream;

        private struct Answer
        {
            public int index;
            public string answer;
        }
        private struct GetQuestionResponse
        {
            public int Status;
            public string Question;
            public List<Answer> Answers;
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

        public DisplayQuestion(NetworkStream clientStream, TimeSpan timePerQuestion)
        {
            InitializeComponent();
            m_answersButtons = new List<Tuple<Button, TextBlock>>();
            m_answersButtons.Add( Tuple.Create( new Button(), new TextBlock()));
            m_answersButtons.Add(Tuple.Create(Answer1_button, Answer1_Box));
            m_answersButtons.Add(Tuple.Create(Answer2_button, Answer2_Box));
            m_answersButtons.Add(Tuple.Create(Answer3_button, Answer3_Box));
            m_answersButtons.Add(Tuple.Create(Answer4_button, Answer4_Box));
            updateQuestion();

            // Creating a timer for the question
            m_time = timePerQuestion;
            m_timer = new DispatcherTimer();
            m_timer.Interval = TimeSpan.FromSeconds(1);
            m_timer.Tick += tickTimer;
            m_timer.Start();
        }

        void tickTimer(object sender, EventArgs e)
        {
            if (m_time.TotalSeconds > 0)
            {
                if (m_time.TotalSeconds <= timerWarning)
                {
                    Timer.Foreground = Brushes.Red;
                    m_time = new TimeSpan(0, 0, (int)m_time.TotalSeconds - 1); // Updating countdown
                    Timer.Text = string.Format("{0} : 0{1}", (int)m_time.TotalMinutes, (int)m_time.Seconds); // Updating Timer text box
                }
                else
                {
                    m_time = new TimeSpan(0, 0, (int)m_time.TotalSeconds - 1); // Updating countdown
                    Timer.Text = string.Format("{0} : {1}", (int)m_time.TotalMinutes, (int)m_time.Seconds); // Updating Timer text box
                }
            }
            else
            {
                updateQuestion();
            }
        }

        void updateQuestion()
        {
            // Requesting the current question
            GetQuestionResponse resp = Communicator.ManageSendAndGetData<GetQuestionResponse>("", clientStream, Codes.GET_QUESTION_CODE);

            questionBox.Text = resp.Question;
            // Displaying the question and the possible answers on the screen.
            foreach (var answer in resp.Answers)
            {
                m_answersButtons[answer.index].Item2.Text = answer.answer;
            }
        }

        private void Answer4_Box_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(4);
        }

        private void Answer3_Box_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(3);
        }

        private void Answer2_Box_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(2);
        }

        private void Answer1_Box_Click(object sender, RoutedEventArgs e)
        {
            sendSubmitAnswer(1);
        }

        private void sendSubmitAnswer(int answerId)
        {
            updateButtons(false);
            SubmitAnswerRequest submitAns = new SubmitAnswerRequest
            {
                answerId = answerId
            };

            // Edit and send question request.
            string json = JsonConvert.SerializeObject(submitAns, Formatting.Indented);
            SubmitAnswerResponse sendAns = Communicator.ManageSendAndGetData<SubmitAnswerResponse>(json, clientStream, Codes.LOGIN_CODE);
           
            // Coloring the selected answer Green if correct, and Red if wrong.
            if (sendAns.correctAnswerId != answerId)
            {
                m_answersButtons[answerId].Item1.Background = Brushes.Red;
            }
            else
            {
                m_answersButtons[answerId].Item1.Background = Brushes.Green;
            }

            // Wait till everybody has answered, and call updateQuestion and update the buttons.
        }

        /* Releases / Locks the buttons so that the user won't be able to submit another answer */
        private void updateButtons(bool isEnabled)
        {
            foreach (var button in m_answersButtons)
            {
                button.Item1.IsHitTestVisible = isEnabled;
            }
        }
    }
}
