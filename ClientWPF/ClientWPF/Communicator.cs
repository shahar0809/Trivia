using System.Text;
using System.Net.Sockets;
using Newtonsoft.Json;
using System.Windows;
using System.Collections.Generic;

namespace ClientWPF
{
    public struct Response
    {
        public int status { set; get; }
    }
    class Communicator
    {
        public const int SIZE_OF_DATA_LEN = 4;
        public const int SIZE_OF_CODE = 2;
        public const char SIGN_FOR_TWO_BYTES_CODE = '9';
        public const int DATA_START_INDEX = 6;
        public const int DATA_END_INDEX = 14;

        private NetworkStream clientStream;

        public Communicator(NetworkStream clientStream)
        {
            this.clientStream = clientStream;
        }

        public static string EditRequest(Codes code, string request)
        {
            //Create the request acording to the protocol.
            return
                Helper.ToBinary(((int)code).ToString().PadLeft(SIZE_OF_CODE, '0')) +
                Helper.ToBinary((request.Length).ToString().PadLeft(SIZE_OF_DATA_LEN, '0')) +
                Helper.ToBinary(request);
        }

        public static void SendRequest(string json, NetworkStream clientStream)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(json);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }

        public static T ManageSendAndGetData<T>(NetworkStream clientStream, Codes code)
        {
            return ManageSendAndGetData<T>("", clientStream, code);
        }

        public static T ManageSendAndGetData<T>(string json, NetworkStream clientStream, Codes code)
        {
            // Edit and send request.
            json = EditRequest(code, json);
            SendRequest(json, clientStream);

            // Get response.
            string s = Helper.GetData(clientStream);
            string textStrData = s.Substring(DATA_START_INDEX);
         
            T response = JsonConvert.DeserializeObject<T>(textStrData);
            return response;
        }
    }
}
