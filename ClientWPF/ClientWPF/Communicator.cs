using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using Newtonsoft.Json;


namespace ClientWPF
{
    class Communicator
    {
        public const int BIN_BASE = 2;
        public const int SIZE_OF_BYTE = 8;
        public const int SIZE_OF_DATA_LEN = 4;
        public const int MAX_LEN = 4096;
        public const int DATA_START_INDEX = 5;
        public const int DATA_END_INDEX = 14;

        private NetworkStream clientStream;

        public struct Response
        {
            public int status { set; get; }
        }
        public enum Codes
        {
            ERROR_CODE = 0, LOGIN_CODE, SIGN_UP_CODE, CREATE_ROOM_CODE,
            GET_ROOM_CODE, GET_PLAYERS_IN_ROOM_CODE,
            JOIN_ROOM_CODE, GET_STATISTICS_CODE, LOGOUT_CODE
        };

        public Communicator(NetworkStream clientStream)
        {
            this.clientStream = clientStream;
        }
        public static string ToBinary(string str)
        {
            //Convert the data to byte array.
            byte[] data = Encoding.ASCII.GetBytes(str);

            return string.Join("", data.Select(byt => Convert.ToString(byt, BIN_BASE).PadLeft(SIZE_OF_BYTE, '0')));
        }

        public static string EditRequest(int code, string request)
        {
            //Create the request acording to the protocol.
            return ToBinary(code.ToString()) +
                ToBinary((request.Length).ToString().PadLeft(SIZE_OF_DATA_LEN, '0')) +
                ToBinary(request);
        }

        public static void SendRequest(string json, NetworkStream clientStream)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(json);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }
        public static string GetAsciiValueFromBinaryString(string binary)
        {
            List<byte> list = new List<Byte>();

            for (int i = 0; binary[i] == '0' || binary[i] == '1'; i += SIZE_OF_BYTE)
            {
                string t = binary.Substring(i, SIZE_OF_BYTE);

                list.Add(Convert.ToByte(t, BIN_BASE));
            }
            return Encoding.ASCII.GetString(list.ToArray());
        }

        public static string GetData(NetworkStream clientStream)
        {
            byte[] buffer = new byte[MAX_LEN];
            int bytesRead = clientStream.Read(buffer, 0, MAX_LEN);

            //Convert the data to string with ascii values.
            string binStr = Encoding.ASCII.GetString(buffer);
            return GetAsciiValueFromBinaryString(binStr);
        }

        public static Response ManageSendAndGetData(string json, NetworkStream clientStream)
        {
            //Edit and send login request.
            json = EditRequest((int)Codes.LOGIN_CODE, json);
            SendRequest(json, clientStream);

            //Get login response.
            string textStrData = GetData(clientStream).Substring(DATA_START_INDEX, DATA_END_INDEX);
            Response response = JsonConvert.DeserializeObject<Response>(textStrData);
            return response;
        }
    }
}
