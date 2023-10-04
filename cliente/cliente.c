#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 12345

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <IP do Servidor> <Nome do Arquivo>\n", argv[0]);
        exit(1);
    }

    char *serverIp = argv[1];
    char *fileName = argv[2];

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("Erro ao iniciar o Winsock");
    }

    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        error("Erro ao criar o socket");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        error("Erro ao converter o endereço IP");
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error("Erro ao conectar ao servidor");
    }

    printf("Conectado ao servidor. Enviando arquivo '%s'...\n", fileName);

    // Enviando o nome do arquivo para o servidor
    send(clientSocket, fileName, strlen(fileName) + 1, 0);

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        error("Erro ao abrir o arquivo");
    }

    char buffer[1024];
    int bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(clientSocket, buffer, bytesRead, 0);
    }

    fclose(file);
    closesocket(clientSocket);
    WSACleanup();

    printf("Transferencia concluida.\n");

    return 0;
}
