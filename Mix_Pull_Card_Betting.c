#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mixCardTray(void){
	
	int CardTray[N_CARDSET*N_CARD] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10 }; 
	
	return;

}

/*

int i;
	
	int HRT[i];
	int SPD[i];
	int CLV[i];
	int DIA[i];
	
	for (i=0; i<13; i++){
		
		CardTray[i] = HRT[i];
	
	}
	
		for (i=13; i<26; i++){
		
		CardTray[i] = HRT[i];
	
	}
	
		for (i=26; i<39; i++){
		
		CardTray[i] = HRT[i];
	
	}
	
		for (i=39; i<52; i++){
		
		CardTray[i] = HRT[i];
	
	}
	
	srand((unsigned)time(NULL));
	
	int Per_1 = 1+rand()%10; */
	

int pullCard(void){
	
	int i = 1+rand()%N_CARDSET*N_CARD;
	
	int OneCard[i] = CardTray[i]; // one card from the tray

	
}

int betDollar(void){
	
	int dollar[N_MAX_USER];
	int bet[N_MAX_USER];
		
	printf(" ----------- BETTING STEP -------");
	printf("-> your betting (total : &%d) : ", dollar[n_user]);
	scanf("%d", &bet[n_user] );
	
	for (i=0; i<n_user; i++){
		
		bet[i] = 1+rand()%N_MAX_BET;
		dollar[i] = dollar[i] - bet[i];
		
		printf("-> player[%d] bets &%d (out of &%d)\n", i, bet[i], dollar[i]);	
	}
	
	printf("------------------------------")
	
	return;
}
