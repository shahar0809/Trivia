using System.Text;
using System.Net.Sockets;
using Newtonsoft.Json;


namespace ClientWPF
{
    public struct Response
    {
        public int status { set; get; }
    }
    class Communicator
    {
        public const int SIZE_OF_DATA_LEN = 4;
        public const int DATA_START_INDEX = 5;
        public const int DATA_END_INDEX = 14;

        private NetworkStream clientStream;

        public Communicator(NetworkStream clientStream)
        {
            this.clientStream = clientStream;
        }

        public static string EditRequest(int code, string request)
        {
            //Create the request acording to the protocol.
            return
                Helper.ToBinary(code.ToString()) +
                Helper.ToBinary((request.Length).ToString().PadLeft(SIZE_OF_DATA_LEN, '0')) +
                Helper.ToBinary(request);
        }

        public static void SendRequest(string json, NetworkStream clientStream)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(json);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }

        public static T ManageSendAndGetData<T>(string json, NetworkStream clientStream, Codes code)
        {
            // Edit and send login request.
            json = EditRequest((int)code, json);
            SendRequest(json, clientStream);

            // Get login response.
            string s = Helper.GetData(clientStream);
            string textStrData = s.Substring(DATA_START_INDEX);
            T response = JsonConvert.DeserializeObject<T>(textStrData);
            return response;
        }
    }
}
