import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 1050
MAX_LEN = 1024
HELLO_MSG = "Hello"

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

    sign_up_req = sign_up_req.dumps()  # Getting the json as a string
    str_packet = Codes["SIGN_UP_CODE"] + str(len(sign_up_req)) + sign_up_req  # Building the packet according to the protocol
    sock.sendall(bytes(str_packet, encoding="utf-8"))


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
                 "password": password }

    login_req = login_req.dumps()  # Getting the json as a string
    str_packet = Codes["LOGIN_CODE"] + str(len(login_req)) + login_req  # Building the packet according to the protocol
    sock.sendall(bytes(str_packet, encoding="utf-8"))


def receive_response(sock):
    """
    Receives the response from the server, and prints it.
    :param sock: The socket connecting the server and the client
    :return: None.
    """
    packet = sock.recv(MAX_LEN)
    j = json.load(packet.decode('utf-8'))
    print("Received from server: " + j.dumps)


def main():
    sock = make_socket()                         # Creating a listening socket
    msg = receive_information(sock)  # Getting the first "Hello" message from the server
    print("Message from server: " + msg)

    if msg == HELLO_MSG:                               # Checking message's content
        send_information(listening_socket, HELLO_MSG)  # Responding to the server

    send_sign_up_request(sock)  # Sending a Sign up request
    receive_response(sock)      # Getting server's response

    send_login_request(sock)    # Sending a Log in request
    receive_response(sock)      # Getting server's response

    sock.close()


if __name__ == "__main__":
    main()
