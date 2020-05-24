import socket
import json

# Connection Constants
SERVER_IP = "127.0.0.1"
SERVER_PORT = 1050
MAX_LEN = 1024

DATA_LEN_IN_BYTES = 4
BIN_BASE = 2
DECIMAL_BASE = 10
SIZE_OF_BYTE = 8

# Codes for different types of requests
Codes = {"LOGIN_CODE": "1", "SIGN_UP_CODE": "2"}
SUCCESS_CODE = "1"

""" ****** SOCKET RELATED ****** """


def make_socket():
    """
    Creates a socket.
    :return: sock
    :rtype: socket.socket
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, SERVER_PORT))
    return sock


def send_information(sock, msg):
    """
    Sends data to the client.
    :param sock: the socket that connects the client to the server.
    :param msg: the message to send
    :type msg: str
    """
    sock.sendall(msg.encode())


def receive_response(sock):
    """
    :param sock: the socket that connects the client to the server.
    Receives the response from the server, and prints it.
    :return: None.
    """
    packet = sock.recv(MAX_LEN)
    bin_data = int(packet.decode(), BIN_BASE)
    packet = bin_data.to_bytes((bin_data.bit_length() + SIZE_OF_BYTE - 1) // SIZE_OF_BYTE, 'big').decode()

    # Getting the result of the request from the json object
    j = json.loads(packet[DATA_LEN_IN_BYTES + 1 :])
    print("S E R V E R:\n" + j["status"] + "\n")
    return j["status"]


""" ****** SERVER COMMUNICATION ****** """


def send_sign_up_request(sock, username, password, email):
    """
    Inputs the parameters for the sign-up request, and sends the request to the server.
    :param sock: the socket that connects the client to the server.
    :param username: The username in the request
    :param password: The password in the request
    :param email: The email in the request
    :return: None
    """
    # Creating a json object from the information
    sign_up_req = {"username": username,
                   "password": password,
                   "email": email}

    edit_request(sock, sign_up_req, Codes["SIGN_UP_CODE"])


def send_login_request(sock, username, password):
    """
    Inputs the parameters for the login request, and sends the request to the server.
    :param sock: the socket that connects the client to the server.
    :param username: The username in the request
    :param password: The password in the request
    :return: None
    """

    # Creating a json object from the information
    login_req = {"username": username,
                 "password": password}

    edit_request(sock, login_req, Codes["LOGIN_CODE"])


def edit_request(sock, json_request, code):
    json_request = json.dumps(json_request)  # Getting the json as a string
    json_length = str(len(json_request))
    json_length = json_length.zfill(DATA_LEN_IN_BYTES)

    str_packet = code + json_length + json_request  # Building the packet according to the protocol
    str_packet = ''.join(format(ord(i), 'b').zfill(SIZE_OF_BYTE) for i in code)
    str_packet += ''.join(format(ord(i), 'b').zfill(SIZE_OF_BYTE) for i in json_length)
    str_packet += ''.join(format(ord(i), 'b').zfill(SIZE_OF_BYTE) for i in json_request)
    send_information(sock, str_packet)


""" ******* TESTS ******* """


def login_without_signup(sock):
    """
    Checking if the user can log in without signing up first.
    :param sock: the socket that connects the client to the server.
    :return: True / False according to the result.
    """
    # Trying to log in without signing up.
    send_login_request(sock, "randomUser", "randomPassword")

    if receive_response(sock) == SUCCESS_CODE:
        print("Test 1 failed. Succeeded to log in without signing up first.\n")
        return False

    else:
        print("Test 1 passed.")
        return True


def signup_with_same_username(sock):
    send_sign_up_request(sock, "randomUser", "randomPassword", "randomEmail")
    receive_response(sock)

    send_sign_up_request(sock, "randomUser", "randomPassword2", "randomEmail2")
    if receive_response(sock) == SUCCESS_CODE:
        print("Test 2 failed. Succeeded to sign up with the same username.\n")
        return False

    else:
        print("Test 2 passed.")
        return True


def login_when_already_connected(sock):
    send_login_request(sock, "randomUser", "randomPassword")
    receive_response(sock)

    send_login_request(sock, "randomUser", "randomPassword")
    if receive_response(sock) == SUCCESS_CODE:
        print("Test 3 failed. Succeeded to log in when the user is already connected.\n")
        return False

    else:
        print("Test 3 passed.")
        return True


def main():
    sock = make_socket()
    login_without_signup(sock)
    signup_with_same_username(sock)
    login_when_already_connected(sock)

    sock.close()


if __name__ == "__main__":
    main()


