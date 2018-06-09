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
	char kor[10];
	char kilepes[10];

	char msg_udv[256] = "Sikeresen bejelentkezett.\n";
	char msg_hanykor[256]="Add meg hány kört szeretnétek játszani(1-9): ";
	

	send(socket1, msg_udv, sizeof(msg_udv), 0);
	send(socket1, msg_hanykor, sizeof(msg_hanykor), 0);

	recv(socket1, kor, sizeof(kor), 0);
			//if(kor[0]=='f' && kor[1]=='e' && kor[2]=='l' && kor[3]=='a' && kor[4]=='d' && kor[5]=='o' && kor[6]=='m')
						//exit(-1);

	send(socket2, msg_udv, sizeof(msg_udv), 0);
	send(socket2, msg_hanykor, sizeof(msg_hanykor), 0);
	
	recv(socket2, kilepes, sizeof(kilepes), 0);
				//if(kilepes[0]=='f' && kilepes[1]=='e' && kilepes[2]=='l' && kilepes[3]=='a' && kilepes[4]=='d' && kilepes[5]=='o' && kilepes[6]=='m')
						//exit(-1);

	send(socket1, kilepes, sizeof(kilepes), 0);
	send(socket2, kor, sizeof(kor), 0);

	int korokszama=((int)kor[0]-'0'+(int)kilepes[0]-'0')/2;
	printf("A körök száma(a játékosok válaszainak átlaga): %d\n",korokszama);

	for (int i = 1; i <= korokszama; ++i)
	{
		printf("%d. játszma folyamatban.\n",i);
		char valasz1[10];
		char valasz2[10];
		char mitvalasztasz[50]="Mit választassz? ";
		send(socket1, mitvalasztasz, sizeof(mitvalasztasz), 0);
		recv(socket1, valasz1, sizeof(valasz1), 0);
				if(valasz1[0]=='f' && valasz1[1]=='e' && valasz1[2]=='l' && valasz1[3]=='a' && valasz1[4]=='d' && valasz1[5]=='o' && valasz1[6]=='m')
						exit(-1);
		send(socket2, mitvalasztasz, sizeof(mitvalasztasz), 0);
		recv(socket2, valasz2, sizeof(valasz2), 0);
				if(valasz2[0]=='f' && valasz2[1]=='e' && valasz2[2]=='l' && valasz2[3]=='a' && valasz2[4]=='d' && valasz2[5]=='o' && valasz2[6]=='m')
						exit(-1);



		char elso[30]="Az első játékos nyert!\n";
		char masodik[30]="A második játékos nyert!\n";
		char dontetlen[30]="Döntetlen lett\n";
		if(((int)valasz1[0]-'0'>(int)valasz2[0]-'0') && ((valasz1[0]!='1' && valasz2[0]!='3') && (valasz1[0]!='3'&& valasz2[0]!='1')))
			{printf("%s",elso);
				send(socket1, elso, sizeof(elso), 0);
				send(socket2, elso, sizeof(elso), 0);}
		if(((int)valasz1[0]-'0'<(int)valasz2[0]-'0') && ((valasz1[0]!='1' && valasz2[0]!='3') && (valasz1[0]!='3'&& valasz2[0]!='1')))
			{printf("%s",masodik);
				send(socket1, masodik, sizeof(masodik), 0);
				send(socket2, masodik, sizeof(masodik), 0);}
		if(valasz1[0]=='3'&& valasz2[0]=='1')
			{printf("%s",masodik);
				send(socket1, masodik, sizeof(masodik), 0);
				send(socket2, masodik, sizeof(masodik), 0);}
		if(valasz1[0]=='1'&& valasz2[0]=='3')
			{printf("%s",elso);
				send(socket1, elso, sizeof(elso), 0);
				send(socket2, elso, sizeof(elso), 0);}
		if((int)valasz1[0]-'0'==(int)valasz2[0]-'0')
			{printf("%s",dontetlen);
				send(socket1, dontetlen, sizeof(dontetlen), 0);
				send(socket2, dontetlen, sizeof(dontetlen), 0);}


	}


close(server_socket);

	return 0;
	}
