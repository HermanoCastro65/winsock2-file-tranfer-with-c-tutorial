#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <winsock2.h>

#define PORT 12345

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("Erro ao iniciar o Winsock");
    }

    SOCKET serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        error("Erro ao criar o socket");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error("Erro ao vincular o socket");
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        error("Erro ao ouvir a porta");
    }

    printf("Aguardando conexao do cliente...\n");

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        error("Erro ao aceitar a conexao do cliente");
    }

    printf("Cliente conectado. Recebendo arquivo...\n");

    char fileName[256];
    recv(clientSocket, fileName, sizeof(fileName), 0);
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        error("Erro ao criar o arquivo");
    }

    char buffer[1024];
    int bytesRead;
    long fileSize = 0;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        fileSize += bytesRead;
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    double transfer_rate = (fileSize * 8.0) / 1000000; // Calcula a taxa de transferência em Mbps
    printf("Transferencia concluida. Taxa de transferencia: %.2f Mbps\n", transfer_rate);

    return 0;
}

