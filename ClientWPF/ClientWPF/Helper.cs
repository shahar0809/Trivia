using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace ClientWPF
{
    public enum Codes
    {
        ERROR_CODE = 0, LOGIN_CODE, SIGN_UP_CODE, CREATE_ROOM_CODE,
        GET_ROOMS_CODE, GET_PLAYERS_IN_ROOM_CODE,
        JOIN_ROOM_CODE, GET_STATISTICS_CODE,
        LOGOUT_CODE ,LEAVE_ROOM_CODE , CLOSE_ROOM_CODE, START_GAME_CODE, GET_ROOM_STATE_CODE
    };
    class Helper
    {
        public const int BIN_BASE = 2;
        public const int SIZE_OF_BYTE = 8;
        public const int MAX_LEN = 4096;

        public static string GetAsciiValueFromBinaryString(string binary)
        {
            List<byte> list = new List<Byte>();

            for (int i = 0; binary[i] == '0' || binary[i] == '1'; i += SIZE_OF_BYTE)
            {
                list.Add(Convert.ToByte(binary.Substring(i, SIZE_OF_BYTE), BIN_BASE));
            }
            return Encoding.ASCII.GetString(list.ToArray());
        }

        public static string ToBinary(string str)
        {
            //Convert the data to byte array.
            byte[] data = Encoding.ASCII.GetBytes(str);

            return string.Join("", data.Select(byt => Convert.ToString(byt, BIN_BASE).PadLeft(SIZE_OF_BYTE, '0')));
        }

        public static string GetData(NetworkStream clientStream)
        {
            byte[] buffer = new byte[MAX_LEN];
            int bytesRead = clientStream.Read(buffer, 0, MAX_LEN);

            //Convert the data to string with ascii values.
            string binStr = Encoding.ASCII.GetString(buffer);
            return GetAsciiValueFromBinaryString(binStr);
        }
    }
}
