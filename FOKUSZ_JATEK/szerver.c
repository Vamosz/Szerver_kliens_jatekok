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

//*****JÁTÉK******************************************************
//Jaték előtti beszélgetés
	char msg_udv[256] = "A kapcsolat sikeresen letrejott a szerverrel.\n";
	send(socket1, msg_udv, sizeof(msg_udv), 0);

	char msg_nev[32] = "Kezdődhet a játék? ";
	char nev[30];
 	send(socket1, msg_nev, sizeof(msg_nev), 0);
	recv(socket1, nev, sizeof(nev), 0);

	//printf("%s\n", nev);
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

	
int db2=0,db1=0;
//char msg_vege[40]="A szerver nyert!";
//char msg_vege2[5]="";

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if(tabla[i][j]=='2')
				db2++;
		}
	}
	if(db2==0)//1es nyert
		{
			printf("A szerver nyert!");
			exit(-1); }
			
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
	exit(-1); }

	//else
		//send(socket1, msg_vege2, sizeof(msg_vege2), 0);
		
		/*char vege[40];
		recv(socket1, vege, sizeof(vege), 0);
		printf(" %s", vege); */	


	char honnan[10];
	char hova[10];

	printf("Honnan: ");
	scanf("%s", honnan);
		if(honnan[0]=='P' && honnan[1]=='a' && honnan[2]=='s' && honnan[3]=='s' && honnan[4]=='z')
			{char msg_vege[30]="A szerver kilépett cs!\n";
 			send(socket1, msg_vege, sizeof(msg_vege), 0);
			exit(-1);
			}
			else
				{char msg_vege2[30]="\n";
 			send(socket1, msg_vege2, sizeof(msg_vege2), 0);
			
			}

		for(;;){
		if(tabla[(int)honnan[0]-'0'][(int)honnan[1]-'0']=='2')
		{
			printf("Nem léphetsz ezzel, ez a kliensé.Honnan: ");
			scanf("%s", honnan);
		}
		else
			break;
			}


	printf("Hova: ");
	scanf("%s", 	hova);
		if(hova[0]=='P' && hova[1]=='a' && hova[2]=='s' && hova[3]=='s' && hova[4]=='z')
			exit(-1);
		if((int)honnan[0]!=(int)hova[0] && (int)honnan[1]!=(int)hova[1])
					{printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova);}
		
		
	for(;;)
	{	
				if((int)honnan[0]!=(int)hova[0] && (int)honnan[1]!=(int)hova[1])
					{printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova);}
		
				if(((int)honnan[0]-(int)hova[0]<=1 && (int)honnan[0]-(int)hova[0]>=-1) && ((int)honnan[1]-(int)hova[1]<=1 && (int)honnan[1]-(int)hova[1]>=-1))
					break;

				else
				{
				printf("Nem sikerült, ujra. ");
				printf("Hova: ");
				scanf("%s", 	hova);
					if(hova[0]=='P' && hova[1]=='a' && hova[2]=='s' && hova[3]=='s' && hova[4]=='z')
						exit(-1);
						}

			}
			
	
	char mesg[10];
	mesg[0] = honnan[0];
	mesg[1] = honnan[1];
	mesg[2] = hova[0];
	mesg[3] = hova[1];
	mesg[4] = '\n';

	tabla[(int)(hova[0]-'0')][(int)(hova[1]-'0')] = tabla[(int)(honnan[0]-'0')][(int)(honnan[1]-'0')];
	tabla[(int)(honnan[0]-'0')][(int)(honnan[1]-'0')] = '0';

	send(socket1, mesg, sizeof(mesg), 0);

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
	char mesg1[10];
	recv(socket1, &mesg1, sizeof(mesg1), 0);

	tabla[(int)(mesg1[2]-'0')][(int)(mesg1[3]-'0')] = tabla[(int)(mesg1[0]-'0')][(int)(mesg1[1]-'0')];
	tabla[(int)(mesg1[0]-'0')][(int)(mesg1[1]-'0')] = '0';
	


}

	close(server_socket);

	return 0;
}
