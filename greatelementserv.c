#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ntohs(6011);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == 0 ? printf("Done Binding\n") : printf("Error While Binding\n");

    struct sockaddr_in tempSendAddr;

    int buf[100];
    int len = sizeof(struct sockaddr);

    recvfrom(serverSocket, &buf, 100, 0, (struct sockaddr *)&tempSendAddr, &len);
     
    int largest = -99999;
    for (int i = 0 ; i < 7 ; i++){
        if (largest < *(buf + i)){
            largest = *(buf + i);
        }
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6009);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(serverSocket, &largest, sizeof(largest), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));

    return 0;
    
}
