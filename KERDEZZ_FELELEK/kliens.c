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

	char msg_nev_valasz[20];
	scanf("%s", msg_nev_valasz);
	send(network_socket, msg_nev_valasz, sizeof(msg_nev_valasz), 0);

	char msg_kerdes[256];
	recv(network_socket, &msg_kerdes, sizeof(msg_kerdes), 0);
	printf("Szerver: %s", msg_kerdes);

	int msg_kerdes_valasz[2];
	scanf("%d", msg_kerdes_valasz);
	send(network_socket, msg_kerdes_valasz, sizeof(msg_kerdes_valasz), 0);


	char msg_eredmeny[50];
	recv(network_socket, &msg_eredmeny, sizeof(msg_eredmeny), 0);
	printf("Szerver: %s", msg_eredmeny);

	

	close(network_socket);

	return 0;
	}
