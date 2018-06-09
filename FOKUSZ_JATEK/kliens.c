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

	char msg_nev[32];
	recv(network_socket, &msg_nev, sizeof(msg_nev), 0);
	printf("Szerver: %s", msg_nev);

	char msg_nev_valasz[30];
	scanf("%s", msg_nev_valasz);
	send(network_socket, msg_nev_valasz, sizeof(msg_nev_valasz), 0);

//Tábla létrehozása
	char tabla[8][8];

	for(int i = 0; i < 2; i++){
		tabla[i][0] = '-';
		tabla[i][1] = '-';
		tabla[i][6] = '-';
		tabla[i][7] = '-';

		tabla[7-i][0] = '-';
		tabla[7-i][1] = '-';
		tabla[7-i][6] = '-';
		tabla[7-i][7] = '-';}

		for (int i = 2; i < 6; ++i)
			{
				tabla[0][i] = '0';
				tabla[7][i] = '0';
				tabla[i][0] = '0';
				tabla[i][7] = '0';}

		for(int i = 1; i < 7; i++){
				for(int j = 1; j < 7; j++){
			tabla[i][j] = '1';
			//tabla[7-i][j] = '2';
		}
	}
	for (int i = 1; i < 7; i=i+2)
	{
		for (int j = 3; j < 5; j=j+1)
		{
			tabla[i][j]='2';
		}
	}
	for (int i = 2; i < 7; i=i+2)
	{
		for (int j = 1; j < 7; j=j+4)
		{
			tabla[i][j]='2';
			tabla[i][j+1]='2';
		}
	}
	/*for(int i = 2; i < 6; i++){
		for(int j = 0; j < 8; j++){
			tabla[i][j] = '0';
		}
	}*/
//ciklus
for(;;){
	system("clear");
	printf("    ");
	for(int i = 0; i < 8; i++){
		printf("%d ", i);
	}
	printf("\n");
	for(int i = 0; i < 8; i++){
		printf("%d - ", i);
		for(int j = 0; j < 8; j++){
			printf("%c ", tabla[i][j]);
		}
		printf("\n");
	}
	
	char msg_nev2[32];
	recv(network_socket, &msg_nev2, sizeof(msg_nev2), 0);
	printf("Szerver: %s", msg_nev2);
	if(msg_nev2[0]=='P' && msg_nev2[1]=='a' && msg_nev2[2]=='s' && msg_nev2[3]=='s' && msg_nev2[4]=='z')
			exit(-1);



	char mesg[10];
	recv(network_socket, &mesg, sizeof(mesg), 0);

	tabla[(int)(mesg[2]-'0')][(int)(mesg[3]-'0')] = tabla[(int)(mesg[0]-'0')][(int)(mesg[1]-'0')];
	tabla[(int)(mesg[0]-'0')][(int)(mesg[1]-'0')] = '0';


	system("clear");
	printf("    ");
	for(int i = 0; i < 8; i++){
		printf("%d ", i);
	}
	printf("\n");
	for(int i = 0; i < 8; i++){
		printf("%d - ", i);
		for(int j = 0; j < 8; j++){
			printf("%c ", tabla[i][j]);
		}
		printf("\n");
	}

	char honnan1[10];
	char hova1[10];

int db1=0,db2=0;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if(tabla[i][j]=='1')
				db1++;
		}
	}
	
	if(db1==0)//2es nyert
	{
	printf("A kliens nyert!");
	exit(-1);
	}
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if(tabla[i][j]=='2')
				db2++;
		}
	}
	if(db2==0)//1es nyert
		//{send(socket1, msg_vege, sizeof(msg_vege), 0);
			{printf("A szerver nyert!");
			exit(-1);}
			
	


	/*else
	{
		char msg_nev_v2[5]="";
	send(network_socket, msg_nev_v2, sizeof(msg_nev_v2), 0);
	}*/


	/*char msg_vege[40];
	recv(network_socket, &msg_vege, sizeof(msg_vege), 0);
	printf("Szerver: %s", msg_vege);*/
			


	printf("Honnan: ");
	scanf("%s", honnan1);
		if(honnan1[0]=='P' && honnan1[1]=='a' && honnan1[2]=='s' && honnan1[3]=='s' && honnan1[4]=='z')
			exit(-1);
		for(;;){
		if(tabla[(int)honnan1[0]-'0'][(int)honnan1[1]-'0']=='1')
		{
			printf("Nem léphetsz ezzel, ez a kliensé.Honnan: ");
			scanf("%s", honnan1);
		}
		else
			break;
			}
		
	printf("Hova: ");
	scanf("%s", 	hova1);
		if(hova1[0]=='P' && hova1[1]=='a' && hova1[2]=='s' && hova1[3]=='s' && hova1[4]=='z')
			exit(-1);
		if((int)honnan1[0]!=(int)hova1[0] && (int)honnan1[1]!=(int)hova1[1])
					{printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova1);}

for(;;)
	{
		if((int)honnan1[0]!=(int)hova1[0] && (int)honnan1[1]!=(int)hova1[1])
					{printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova1);
					if(hova1[0]=='P' && hova1[1]=='a' && hova1[2]=='s' && hova1[3]=='s' && hova1[4]=='z')
						exit(-1);}


		if(((int)honnan1[0]-(int)hova1[0]<=1 && (int)honnan1[0]-(int)hova1[0]>=-1) && ((int)honnan1[1]-(int)hova1[1]<=1 && (int)honnan1[1]-(int)hova1[1]>=-1))
					break;

				else
				{printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova1);
					if(hova1[0]=='P' && hova1[1]=='a' && hova1[2]=='s' && hova1[3]=='s' && hova1[4]=='z')
						exit(-1);}
					}


	char mesg1[10];
	mesg1[0] = honnan1[0];
	mesg1[1] = honnan1[1];
	mesg1[2] = hova1[0];
	mesg1[3] = hova1[1];
	mesg1[4] = '\n';

	send(network_socket, mesg1, sizeof(mesg1), 0);

	tabla[(int)(hova1[0]-'0')][(int)(hova1[1]-'0')] = tabla[(int)(honnan1[0]-'0')][(int)(honnan1[1]-'0')];
	tabla[(int)(honnan1[0]-'0')][(int)(honnan1[1]-'0')] = '0';
	}


	close(network_socket);

	return 0;
}
