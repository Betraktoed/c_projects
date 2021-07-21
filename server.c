

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
        int server_sockfd, client_sockfd;
        int server_len, client_len;
        FILE * dfile = fopen("logs", "w");
        struct sockaddr_in server_address;
        struct sockaddr_in client_address;
        server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(server_sockfd < 0){
                fprintf(dfile, "socket");
                exit(1);
        }
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = 9734;
        server_len = sizeof(server_address);
        if(bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0){
                fprintf(dfile,"bind");
                exit(1);
        }
        listen(server_sockfd, 5);
        while(1) {
                char msg[100];
                printf("server waiting\n");
                client_len = sizeof(client_address);
                client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
                while(recv(client_sockfd, &msg, 128, 0) != 0){
                        fprintf(dfile, "%s ", msg);
                        send(client_sockfd, &msg, 128, 0);
                }
                close(client_sockfd);
        }
        fclose(dfile);
}
