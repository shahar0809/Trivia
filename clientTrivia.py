import socket
import json


SERVER_IP = "127.0.0.1"
SERVER_PORT = 1050
MAX_LEN = 1024
HELLO_MSG = "Hello"
DATA_LEN_IN_BYTES = 4
BIN_BASE = 2
DECIMAL_BASE = 10
BITS_IS_BYTE = 8

# Codes for different types of requests
Codes = {"LOGIN_CODE": "1", "SIGN_UP_CODE": "2"}


def make_socket():
    """
    Creates a socket.
    :return: sock
    :rtype: socket.socket
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, SERVER_PORT))
    return sock


def receive_information(sock):
    """
    Receives data from the client.
    :param sock: the conversation socket
    :type sock: socket.socket.
    :return: server_msg
    :rtype: str
    """
    server_msg = sock.recv(MAX_LEN)
    return server_msg.decode()


def send_information(sock, msg):
    """
    Sends data to the client.
    :param sock: the conversation socket
    :type sock: socket.socket.
    :param msg: the message to send
    :type msg: str
    """
    sock.sendall(msg.encode())


def send_sign_up_request(sock):
    """
    Inputs the parameters for the sign-up request, and sends the request to the server.
    :param sock: The socket connecting the server and the client
    :return: None
    """

    # Getting sign up information from the user
    print("Enter username: ")
    username = input()
    print("Enter password: ")
    password = input()
    print("Enter email: ")
    email = input()

    # Creating a json object from the information
    sign_up_req = {"username": username,
                   "password": password,
                   "email": email}
    edit_request(sock, sign_up_req, Codes["SIGN_UP_CODE"])


def send_login_request(sock):
    """
    Inputs the parameters for the login request, and sends the request to the server.
    :param sock: The socket connecting the server and the client
    :return: None
    """

    # Getting sign up information from the user
    print("Enter username: ")
    username = input()
    print("Enter password: ")
    password = input()

    # Creating a json object from the information
    login_req = {"username": username,
                 "password": password}
    edit_request(sock, login_req, Codes["LOGIN_CODE"])


def edit_request(sock, json_request, code):
    json_request = json.dumps(json_request)  # Getting the json as a string
    json_length = str(len(json_request))
    json_length = json_length.zfill(DATA_LEN_IN_BYTES)

    str_packet = code + json_length + json_request  # Building the packet according to the protocol
    str_packet = ''.join(format(ord(i), 'b').zfill(8) for i in code)
    str_packet += ''.join(format(ord(i), 'b').zfill(8) for i in json_length)
    str_packet += ''.join(format(ord(i), 'b').zfill(8) for i in json_request)
    # binary_request = ''.join(format(ord(i), 'b') for i in json_request)  # Converting the packet to binary values
    send_information(sock, str_packet)


def receive_response(sock):
    """
    Receives the response from the server, and prints it.
    :param sock: The socket connecting the server and the client
    :return: None.
    """
    packet = sock.recv(MAX_LEN)
    bin_data = int(packet.decode(),BIN_BASE)
    data = bin_data.to_bytes((bin_data.bit_length() + BITS_IS_BYTE-1) // BITS_IS_BYTE, 'big').decode()
    print("Received from server: " + data)


def main():
    sock = make_socket()                         # Creating a listening socket

    send_sign_up_request(sock)  # Sending a Sign up request
    receive_response(sock)      # Getting server's response

    send_login_request(sock)    # Sending a Log in request
    receive_response(sock)      # Getting server's response

    sock.close()


if __name__ == "__main__":
    main()
