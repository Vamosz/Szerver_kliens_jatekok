#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h> 

#include <time.h>
#include <string.h>

int main(){
//*****SZERVER****************************************************
	//socket létrehozása
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	//adress
	struct sockaddr_in server_adress;
	server_adress.sin_family = AF_INET;
	server_adress.sin_port = htons(9002);
	server_adress.sin_addr.s_addr = INADDR_ANY;

	//connect
	int connection = connect(network_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));
	if(connection != 0){
		printf("%d", connection);
		printf("Valami elromlott..\n");
		exit(-1);
	}
//*****JÁTÉK******************************************************
//Jaték előtti beszélgetés
	char msg_udv[256];
	recv(network_socket, &msg_udv, sizeof(msg_udv), 0);
	printf("Szerver: %s", msg_udv);
	char msg_hanykor[256];
	recv(network_socket, &msg_hanykor, sizeof(msg_hanykor), 0);
	printf("Szerver: %s", msg_hanykor);
	char msg_kor_valasz[10];
	scanf("%s", msg_kor_valasz);
	send(network_socket, msg_kor_valasz, sizeof(msg_kor_valasz), 0);
			if(msg_kor_valasz[0]=='f' && msg_kor_valasz[1]=='e' && msg_kor_valasz[2]=='l' && msg_kor_valasz[3]=='a' && msg_kor_valasz[4]=='d' && msg_kor_valasz[5]=='o' && msg_kor_valasz[6]=='m')
					exit(-1);
	char msg_kor1[10];
	recv(network_socket, &msg_kor1, sizeof(msg_kor1), 0);

	int korokszama=((int) msg_kor1[0]-'0'+(int) msg_kor_valasz[0]-'0')/2;
	
	for (int i = 1; i <= korokszama; ++i)
	{
		system("clear");
		printf("1->kő\t2->papír\t3->olló\n");
		printf("%d. játszma következik.\n",i);
		char mitvalasztasz[50];
		recv(network_socket, &mitvalasztasz, sizeof(mitvalasztasz), 0);
		printf("Szerver: %s", mitvalasztasz);
		char valasztas[10];
		scanf("%s",valasztas);
		send(network_socket,valasztas,sizeof(valasztas),0);
				if(valasztas[0]=='f' && valasztas[1]=='e' && valasztas[2]=='l' && valasztas[3]=='a' && valasztas[4]=='d' && valasztas[5]=='o' && valasztas[6]=='m')
						exit(-1);
		char eredmeny[30];
		recv(network_socket, &eredmeny, sizeof(eredmeny), 0);
		printf("Szerver: %s", eredmeny);
	}
	system("clear");
	printf("A játéknak vége!\n");	

	close(network_socket);

	return 0;
	}
