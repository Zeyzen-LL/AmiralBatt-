#include <stdio.h>
#include <locale.h>
#include "amiralBatti.h"
#include <pthread.h>


void * thread2(void *){
	int koordinatlar[3][4];
	alanOlustur();
	gemiBoyut(koordinatlar);	
	for(int i=0;i<3;i++){
		printf("%d boyutlu geminin koordinatlarý(x,y) ve yönü(z)(sað için 0 , aþaðý için 1...) giriniz...\n",koordinatlar[i][3]);
		scanf("%d %d %d",&koordinatlar[i][0],&koordinatlar[i][1],&koordinatlar[i][2]);
		if(uygunmu(koordinatlar, i)==0){
			printf("buraya daha önce yerleþtirme yapmýþsýnýz lütfen yeniden koordinat seçin....\n");
			i--;
		}
	}

	while(true){
		int x, y;
		alanyaz();
		if(sira==1){
			printf("Saldýrmak istediðiniz koordinatlarý girin: ");
			scanf("%d %d", &x, &y);
			client(40001, x, y);
		}
		while(sira!=1){
			printf(".");
			sleep(1);
		}
		sleep(1.5);
		system("cls");
	}
}

int main(){
	setlocale(LC_ALL,"Turkish");
	
	
    pthread_t thread_id, tid; 
    pthread_create(&thread_id, NULL, Server, NULL); 
    
	pthread_create(&thread_id, NULL, thread2, NULL); 
    pthread_join(tid, NULL); 
	
	return 0;
}
