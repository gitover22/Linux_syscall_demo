#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <memory.h>
/**
 * 1. socket() 创建socketfd
 * 2. bind() 绑定地址和端口（结构体sockaddr_in描述）到socketfd上
 * 3. listen() 监听socketfd，创建监听队列存放待处理连接，等待客户端连接
 * 4. accept() 阻塞获取客户端连接，返回客户端连接的socketfd
 * 5. recv()/send() 读写数据
 * 5. close() 关闭socketfd
*/
int main(int argc,char* argv[])
{
    if(argc!=4){
        printf("Usage: %s <ip> <port> <backlog>\n",argv[0]);
        return 1;
    }
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)); // 把地址和端口（addr）绑定到sockfd上
    listen(sockfd,atoi(argv[3])); // 创建监听队列，存放待处理连接，backlog为队列可存储最大的连接数
    while(1){
        struct sockaddr_in client; //存储本次连接客户端信息
        bzero(&client,sizeof(client));
        socklen_t client_len = sizeof(client); 
        printf("等待客户端连接...\n");
        int client_sockfd=accept(sockfd,(struct sockaddr*)&client,&client_len);
        if(client_sockfd == -1){
            perror("accept error");
            exit(0);
        }
        printf("已连接client ip:%s,port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        sleep(10); //等待客户端发送信息
        do{
            char buf[1024];
            int len=recv(client_sockfd,buf,sizeof(buf),0);
            if(len<=0){
                break;
            }
            printf("服务器接收到客户端信息:%s\n",buf);
        }while(0);

    }
    close(sockfd);

    return 0;
}