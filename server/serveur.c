#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
typedef struct Score{
	int s2;
	int s1;
	int choix;
}score;


void traitement(int i,int j, score *s)
{
	if(((i-j)!=-2 && i-j<0) || i-j==2)
		(*s).s1++;
	else if(i!=j)
		(*s).s2++;
}


int main(void)
{
	score s1;
	score s2;

	s1.s1=0;
	s1.s2=0;
	int i,j,k;
	int socketServer = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addrServer;
	addrServer.sin_addr.s_addr=inet_addr("127.0.0.1");
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(30000);
	bind(socketServer,(const struct sockaddr *)&addrServer,sizeof(addrServer));
	printf("bind : %d\n",socketServer);

	listen(socketServer, 5);
	printf("listen\n");

	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	int socketClient=accept(socketServer,(struct sockaddr*)& addrClient, &csize);
	printf("accept\n");
	printf("client :%d\n",socketClient);

	struct sockaddr_in addrClient1;
        csize = sizeof(addrClient1);
       	int socketClient1=accept(socketServer,(struct sockaddr*)& addrClient1, &csize);
        printf("accept\n");
	printf("client :%d\n",socketClient1);
	
	while(s1.s1!=2 && s1.s2!=2)
	{
		i=-1;
		j=-1;
		while(recv(socketClient, &i, sizeof(int), 0)==0 && 
				recv(socketClient1, &j, sizeof(int), 0)==0);
		if(i==-1)
			while(recv(socketClient, &i, sizeof(int), 0)==0);
		else if(j==-1)
			while(recv(socketClient1, &j, sizeof(int), 0)==0);

		printf("a%d",i);
		printf("b%d",j);
		traitement(i,j,&s1);
		s2.s1=s1.s2;
		s2.s2=s1.s1;
		s2.choix=j;
		s1.choix=i;
		printf("\ns1.s1 = %d\n",s1.s1);
                printf("s1.s2 = %d\n",s1.s2);
                printf("s1.choix = %d\n",s1.choix);
		printf("s2.s1 = %d\n",s2.s1);
                printf("s2.s2 = %d\n",s2.s2);
                printf("s2.choix = %d\n",s2.choix);
		while(s1.choix!=1 && s1.choix!=2 && s1.choix!=3);
		send(socketClient,&s2,sizeof(score),0);
		send(socketClient1,&s1,sizeof(score),0);
	}
	close(socketClient);
	close(socketClient1);
	close(socketServer);
	printf("close\n");

	return 0;
}

