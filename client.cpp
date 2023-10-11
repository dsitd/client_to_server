#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

const char* FILE_PATH = "example.txt";
const int PORT = 1234;

int main() {
    // Создаем сокет
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create client socket" << std::endl;
        return 1;
    }

    // Устанавливаем адрес сервера и порт
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // Подключаемся к серверу
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to connect to the server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Читаем данные из консоли
    std::string message;
    std::cout << "Enter data to send to the server: ";
    std::getline(std::cin, message);

    // Отправляем данные серверу
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send data to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Закрываем сокет и завершаем процесс
    close(clientSocket);
    return 0;
}
