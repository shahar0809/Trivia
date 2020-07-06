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
        public const int TIMER_WARNING = 10;
        public const int INDEX = 0;
        public const int ANSWER = 1;
        
       
        private RoomData m_roomData;
        private TimeSpan m_time;
        private DispatcherTimer m_timer;
        private List<Tuple<Button, TextBlock>> m_answersButtons;
        private NetworkStream m_clientStream;
        private int m_correctAnswers = 0;
        private int m_questionsLeft;

        private struct Answer
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
            public int answerId { set; get; }
        }
        private struct SubmitAnswerResponse
        {
            public int status { set; get; }
            public int CorrectAnswerId { set; get; }
        }

        public DisplayQuestion(NetworkStream clientStream,RoomData roomData)
        {
            m_clientStream = clientStream;
            m_questionsLeft = roomData.NumOfQuestions;
            m_roomData = roomData;
            InitializeComponent();
            m_answersButtons = new List<Tuple<Button, TextBlock>>();
            m_answersButtons.Add( Tuple.Create( new Button(), new TextBlock()));
            m_answersButtons.Add(Tuple.Create(Answer1_button, Answer1_Box));
            m_answersButtons.Add(Tuple.Create(Answer2_button, Answer2_Box));
            m_answersButtons.Add(Tuple.Create(Answer3_button, Answer3_Box));
            m_answersButtons.Add(Tuple.Create(Answer4_button, Answer4_Box));
            updateQuestion();

            // Creating a timer for the question
            m_time = TimeSpan.FromMinutes(m_roomData.TimeForQuestion);
            m_timer = new DispatcherTimer();
            m_timer.Interval = TimeSpan.FromSeconds(1);
            m_timer.Tick += tickTimer;
            m_timer.Start();
        }

        void tickTimer(object sender, EventArgs e)
        {
            if (m_time.TotalSeconds > 0)
            { 
                    if (m_time.TotalSeconds <= TIMER_WARNING)
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
            if (m_questionsLeft == 0)
            {
                m_timer.Stop();
                var results = new GameResults(m_clientStream);
                results.Show();
                Close();
            }
            else
            {
                // Requesting the current question
                GetQuestionResponse resp = Communicator.ManageSendAndGetData<GetQuestionResponse>("", m_clientStream, Codes.GET_QUESTION_CODE);

                questionsLeft.Text = m_questionsLeft.ToString();
                correctAnswers.Text = m_correctAnswers.ToString();

                questionBox.Text = resp.Question;
                // Displaying the question and the possible answers on the screen.
                foreach (var answer in resp.Answers)
                {
                    m_answersButtons[Convert.ToInt32(answer[INDEX])].Item2.Text = (string)answer[ANSWER];
                }
            
            
                m_time = TimeSpan.FromMinutes(m_roomData.TimeForQuestion);
                updateButtons(true);
                foreach (Tuple<Button, TextBlock> answer in m_answersButtons)
                {
                    answer.Item1.Background = Brushes.White;
                }
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
            SubmitAnswerResponse sendAns = Communicator.ManageSendAndGetData<SubmitAnswerResponse>(json, m_clientStream, Codes.SUBMIT_ANS_CODE);
           
            // Coloring the selected answer Green if correct, and Red if wrong.
            if (sendAns.CorrectAnswerId != answerId)
            {
                m_answersButtons[answerId].Item1.Background = Brushes.Red;
            }
            else
            {
                m_correctAnswers++;
                m_answersButtons[answerId].Item1.Background = Brushes.Green;
            }
            m_questionsLeft--;
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
