import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 1050
MAX_LEN = 1024
HELLO_MSG = "Hello"


def make_socket():
    """:return: sock
    :rtype: socket.socket"""
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)
    return sock


def receive_information(sock):
    """:param sock: the conversation socket
    :type sock: socket.socket.
    :return: server_msg
    :rtype: str"""
    server_msg = sock.recv(MAX_LEN)
    return server_msg.decode()


def send_information(sock, msg):
    """:param sock: the conversation socket
    :type sock: socket.socket.
    :param msg: the message to send
    :type msg: str"""
    sock.sendall(msg.encode())


def main():
    sock = make_socket()
    msg = receive_information(sock)
    print(msg)
    if msg == HELLO_MSG:
        send_information(sock,HELLO_MSG)


if __name__ == "__main__":
    main()
