using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientWPF
{
    namespace Requests
    {
        public struct LoginRequest
        {
            public string Username { set; get; }
            public string Password { set; get; }
        }

        public struct SignUpRequest
        {
            public string Username { set; get; }
            public string Password { set; get; }
            public string Email { set; get; }
        }

        public struct CreateRoomRequest
        {
            public string RoomName { set; get; }
            public int NumOfPlayers { set; get; }
            public int NumOfQuestions { set; get; }
            public double TimeForQuestion { set; get; }
        }

        public struct SubmitAnswerRequest
        {
            public int AnswerId { set; get; }
        }

        public struct JoinRoomRequest
        {
            public int RoomId;
        }

        public struct GetPlayersInRoomRequest
        {
            public int RoomId;
        }
        
        public struct GetRoomRequest
        {
            public int RoomId;
        }

        public struct StatisticRequest
        {
            public string UserStatistics;
            public string HighScores;
        }
    }

    namespace Responses
    {
        public struct CreateRoomResponse
        {
            public int Status { set; get; }
            public int RoomId { set; get; }
        }

        public struct GetRoomsResponse
        {
            public int Status;
            public List<string> Rooms;
        }

        public struct GetPlayersInRoomResponse
        {
            public int Status;
            public List<string> PlayersInRoom;
        }

        public struct JoinRoomResponse
        {
            public int Status;
            public int RoomId;
            public string RoomName;
            public int NumOfplayers;
            public int NumOfQuestions;
            public double TimeForQuestion;
            public int IsActive;
        }

        public struct GeneralResponse
        {
            public int Status { set; get; }
        }

        public struct GetQuestionResponse
        {
            public int Status;
            public string Question;
            public List<List<object>> Answers;
        }

        public struct SubmitAnswerResponse
        {
            public int Status { set; get; }
            public int CorrectAnswerId { set; get; }
        }

        public struct GetGameResultsResponse
        {
            public int Status { get; set; }
            public List<string> Results { set; get; }
        }

        public struct GetRoomStateResponse
        {
            public int Status;
            public bool HasGameBegun;
            public List<string> PlayersInRoom;
            public int QuestionsCount;
            public int AnswerTimeout;
        };
    }
}
