#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

struct packet{
        char name[16];
        char msg[64];
        int length;
};


int main() {
 int sockfd;
 int len;
 struct packet pac;
 struct sockaddr_in address;
 int result, i;
 char msg[64];
 FILE *fp;
 FILE *log = fopen("logs", "w");
 char name[] = "source.txt";
 char nickname[98][16];

 if ((fp2 = fopen("names.txt", "r")) != NULL)
 {
        int i;
        for (i = 0; i < 98; i++){
                fgets(nickname[i], 16, fp2);
                int l = strlen(nickname[i])-1;
                nickname[i][l]='\0';
        }
 }else{
        fprintf(log,"Can't open names.txt");
        getchar();
        return 0;
 }

 memcpy( pac.name, "Bob", (strlen("Bob") + 1)*sizeof(char));
 if ((fp = fopen(name, "r")) == NULL)
 {
    fprintf(log,"Не удалось открыть файл");
    getchar();
    return 0;
 }
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("192.168.2.4");
 address.sin_port = 9734;
 len = sizeof(address);
 result = connect(sockfd, (struct sockaddr *)&address, len);
 if (result == -1) {
  fprintf(log,"oops : client1");
  exit(1);
 }
 while(fscanf(fp, "%s", msg) != EOF){
        memcpy(pac.msg, msg, (strlen(msg) + 1)*sizeof(char));
        char message[128];
        pac.length = strlen(pac.msg) + strlen(pac.name) + 24;
        snprintf(message, sizeof(message)*sizeof(char), "{len:%d;name:%s;message:%s;}",pac.length,pac.name, pac.msg);
        printf("%s ", message);
        sleep(1);
        send(sockfd, &message, 128, 0);
        recv(sockfd, &message, 128, 0);
        fprintf(log,"%s", message);
 }
 fclose(log);
 fclose(fp);
 close(sockfd);
 exit(0);
}

