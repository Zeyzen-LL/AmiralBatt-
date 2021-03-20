#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

int alan[10][10];
int sira=0;

void alanOlustur(){
	for(int i=0; i<10; i++) for(int j = 0; j<10; j++) alan[i][j]=0;
}

void alanyaz(){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%d ",alan[i][j]);
		}
		printf("\n");
	}
}

void gemiBoyut(int dizi[3][4]){
		dizi[0][3]=1;
		dizi[1][3]=2;
		dizi[2][3]=3;
}

int uygunmu(int gemi[3][4], int i){
	
	int k1 = gemi[i][0], k2 = gemi[i][1];
	int gBoyut = gemi[i][3], bayrak=1;
	
	for(int j=0;j<gemi[i][3];j++){
		bayrak=1;
		if(gemi[i][2]==0){
			if(alan[k1][k2]!=0 || (10-gBoyut<gemi[i][0] || 10-gBoyut<gemi[i][1] )){
				bayrak=0;
				break;
			}
			else{
				alan[k1][k2]=1;
			}
			k2++;
		}
		else{
			if(alan[k1][k2]!=0 || (10-gBoyut<gemi[i][0]  || 10-gBoyut<gemi[i][1] )){
				bayrak=0;
				break;
			}
			else{
				alan[k1][k2]=1;
			}
			k1++;
		}
	}
	return bayrak;
}

int gelensaldiri(int x, int y){
	if(alan[x][y]==1){
		alan[x][y]=0;
		return 1;
	}
	else{
		return 0;
	}
}

int Kontrol(){
	
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(alan[i][j]==1){
				return 0;
			}				
		}
	}
	return 1;
}


void *Server(void *){
	
	int port = 40000;
	
	WSADATA WsaDat;
	WSAStartup(MAKEWORD(2, 2), &WsaDat);
	SOCKET s;

	s = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN SAddr;
	SAddr.sin_port = port;
	SAddr.sin_family = AF_INET;
	
	SAddr.sin_addr.S_un.S_un_b.s_b1 = 127; 
	
	SAddr.sin_addr.S_un.S_un_b.s_b2 = 0; 
	
	SAddr.sin_addr.S_un.S_un_b.s_b3 = 0; 
	
	SAddr.sin_addr.S_un.S_un_b.s_b4 = 1;
	 
	bind(s, (SOCKADDR *)&SAddr, sizeof(SAddr));
	
	SAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	listen(s, 1);
	while(1)
	{
		SOCKET tmpS = accept(s, NULL, NULL);
		int buffer[2];
		recv(tmpS, (char *)buffer, 2*sizeof(int), 0);
		int a[1] = {0};
		int b[1] = {1};
		int c[1] = {2};
		if(sira == 0){
			if(gelensaldiri(buffer[0], buffer[1])){
				printf("\nSaldýrý geldi, yedin.\n");
				if(Kontrol())
					send(tmpS, (char *)b, 4, 0);
				else
					send(tmpS, (char *)a, 4, 0);
				sira = 1;
			}
			
			else{
				printf("\nSaldýrý Geldi Iska.\n");
				send(tmpS, (char *)c, 4, 0);
				sira = 1;
			}
		}
	}
}

int client(int port, int x, int y){
	
	WSADATA WsaDat;
	WSAStartup(MAKEWORD(1, 1), &WsaDat);
	
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	
	
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = port; 
	SockAddr.sin_family = AF_INET; 
	
	SockAddr.sin_addr.S_un.S_un_b.s_b1 = 127; 
	SockAddr.sin_addr.S_un.S_un_b.s_b2 = 0; 
	SockAddr.sin_addr.S_un.S_un_b.s_b3 = 0; 
	SockAddr.sin_addr.S_un.S_un_b.s_b4 = 1;
	
	connect(s, (SOCKADDR *)(&SockAddr), sizeof(SockAddr));
	
	int dizi[2] = {x, y};
	send(s, (char*)dizi, sizeof(dizi), 0);
	int a[1];
	recv(s, (char*)a, 4, 0);
	if(a[0]==0) printf("Atýþ baþarýlý...\n");
	else if(a[0]==1) printf("Oyun bitti...\n");
	else if(a[0]==2) printf("Iska...\n");
	sira = 0;
	return 1;
}


