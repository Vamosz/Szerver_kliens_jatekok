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
	//szerver socket létrehozása
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//adress
	struct sockaddr_in server_adress;
	server_adress.sin_family = AF_INET;
	server_adress.sin_port = htons(9002);
	server_adress.sin_addr.s_addr = INADDR_ANY;

	//bind
	int binding = bind(server_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));	
	if(binding != 0){
		printf("Nem sikerult a porthoz csatlakozni!\n");
		exit(-1);
	}	

	listen(server_socket, 5);

	int socket1 = accept(server_socket, NULL, NULL);
	int socket2 = accept(server_socket, NULL, NULL);
//*****JÁTÉK******************************************************
//Jaték előtti beszélgetés
	char nev[20];
	char nev2[20];
	int megfejtes= 1998;
	char msg_udv[256] = "Sikeresen bejelentkezett. Add meg a neved: ";
	send(socket1, msg_udv, sizeof(msg_udv), 0);
	recv(socket1, nev, sizeof(nev), 0);
	send(socket2, msg_udv, sizeof(msg_udv), 0);
	recv(socket2, nev2, sizeof(nev2), 0);


	char msg_kerdes[256] = "Első és utolsó kérdés, jól figyelj.\nMikor született a méltán híres Vámosi (vp7) Patrik.(csak év)\n";
	int valasz1[2];
	int valasz2[2];

 	send(socket1, msg_kerdes, sizeof(msg_kerdes), 0);
	recv(socket1, valasz1, sizeof(valasz1), 0);
	int eredmeny1=megfejtes-valasz1[0];
		if(eredmeny1<0)
			eredmeny1=eredmeny1*(-1);
		printf("Az első játékos válasza: %d\n",valasz1[0]);

 	send(socket2, msg_kerdes, sizeof(msg_kerdes), 0);
	recv(socket2, valasz2, sizeof(valasz2), 0);
	int eredmeny2=megfejtes-valasz2[0];
		if(eredmeny2<0)
			eredmeny2=eredmeny2*(-1);
		printf("A második játékos válasza: %d\n",valasz2[0]);


		char msg_eredmeny[50]="A nyertes az első játékos.\n";
		
		char msg_eredmeny2[50]="A nyertes a második játékos.\n";

		
	if(eredmeny2>eredmeny1)
		{send(socket1, msg_eredmeny, sizeof(msg_eredmeny), 0);
		send(socket2, msg_eredmeny, sizeof(msg_eredmeny), 0);}

	if(eredmeny2<eredmeny1)
		{send(socket1, msg_eredmeny2, sizeof(msg_eredmeny2), 0);
		send(socket2, msg_eredmeny2, sizeof(msg_eredmeny2), 0);	}	
	





close(server_socket);

	return 0;
	}
