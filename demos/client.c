#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/**
 * 1. socket() 创建套接字
 * 2. connect() 连接服务器,同样的，使用结构体 sockaddr_in来描述服务器的ip和端口
 * 3. send()/recv() 发送/接收数据
 * 4. close() 关闭套接字
*/
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    struct sockaddr_in server_addr; //存储要链接的服务器信息，服务器ip，服务器端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }
    // exit(EXIT_SUCCESS);

    char message[1024];
    scanf("%s", message);
    if (send(sockfd, message, strlen(message), 0) < 0) {
        perror("send");
        return 1;
    }

    close(sockfd);
    return 0;
}
