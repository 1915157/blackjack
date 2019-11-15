#include <stdio.h>
#include <stdlib.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


// betting info
int dollar[N_MAX_USER];
int bet[N_MAX_USER];	

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

// play yard information
int n_round = 1;
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
int cardSum[N_MAX_USER]; 					// sum of the cards
int bet[N_MAX_USER];						//current betting
int gameEnd = 0;							//game end flag


int getIntegerInput(void) {
    
	int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    
	if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

//set the number of players
int configUser(void){
	
	int input;
	
	do{
		printf("input the number of players (MAX : 5) : ");
		
		input = getIntegerInput(); 
		n_user = input;
		
		if (input > 5)
			printf("Too many players!\n");
		else if (input < 0)
			printf("invalid input players (%d)\n", input);	
		
	} while (n_user > 5 || n_user < 1 );	

	printf("--> card is mixed and put into the tray\n");
	printf("\n");
	
	return;
		
	}
	
// error : total dollar doesn't change. 
int betDollar(void){
	
	int i ;
			
	for (i=0; i<=n_user; i++){
		
		dollar[i] = 50;
	}		
			
	printf(" ----------- BETTING STEP -------\n");
	printf("-> your betting (total : &%d) : ", dollar[n_user]);
	scanf("%d", &bet[n_user] );
	
	
	for (i=0; i<n_user-1; i++){
		
		bet[i] = 1+rand()%N_MAX_BET;
	
		printf("-> player %d bets &%d (out of &%d)\n", i+1, bet[i], dollar[i]);
		
	}
	
	printf("------------------------------\n");
	
	return;
}


int mixCardTray(void){
	
	int i;
	
	int CardTray[N_CARDSET*N_CARD] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10,
	1,2,3,4,5,6,7,8,9,10,10,10,10};
	// 각각의 카드를 모양별 숫자에 대응시킴. -> ?? 
	char CardNum;
	
	char HRT[13] = {'HRT A','HRT 2','HRT 3','HRT 4','HRT 5','HRT 6','HRT 7','HRT 8','HRT 9','HRT 10','HRT J','HRT Q','HRT K'};
	char SPD[13] = {'SPD A','SPD 2','SPD 3','SPD 4','SPD 5','SPD 6','SPD 7','SPD 8','SPD 9','SPD 10','SPD J','SPD Q','SPD K'};
	char CLV[13] = {'CLV A','CLV 2','CLV 3','CLV 4','CLV 5','CLV 6','CLV 7','CLV 8','CLV 9','CLV 10','CLV J','CLV Q','CLV K'};
	char DIA[13] = {'DIA A','DIA 2','DIA 3','DIA 4','DIA 5','DIA 6','DIA 7','DIA 8','DIA 9','DIA 10','DIA J','DIA Q','DIA K'};
	
	for (i=0; i<13; i++){
		
		CardTray[i] = CardNum;
		CardNum = HRT[i];
	
	}
	
		for (i=13; i<26; i++){
		
		CardTray[i] = CardNum;
		CardNum = SPD[i];
	
	}
	
		for (i=26; i<39; i++){
		
		CardTray[i] = CardNum;
		CardNum = CLV[i];
		
	}
	
		for (i=39; i<52; i++){
		
		CardTray[i] = CardNum;
		CardNum = DIA[i];
	}
	
	for (i=0; i<N_CARDSET*N_CARD; i++) // card shake.
		{
			int randNum1 = rand() % N_CARDSET*N_CARD;
			int randNum2 = rand() % N_CARDSET*N_CARD;
			
			int temp;
			
			temp = CardTray[randNum1];
			CardTray[randNum1] = CardTray[randNum2];
			CardTray[randNum2] = temp;	
		
		}

}

int pullCard(void){ // 카드를 뽑아야 함. 
	
	CardTray[cardIndex];
	cardIndex++;

	return;
}
	

//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	//3. give two card for the dealer
	cardhold[n_user+1][0] = pullCard();
	cardhold[n_user+1][1] = pullCard();	

	return;
}


// print initial card status
void printCardInitialStatus(void){
	
	int i;
	
	printf(" --- server \t : X %d \n",cardhold[n_user+1][0] );
	printf("  -> you \t : %d %d\n",cardhold[n_user][0], cardhold[n_user][1] );
	
	for (i=0; i<n_user-1; i++){
			
		printf("  -> player %d \t : %d %d\n", i+1, cardhold[i][0] ,cardhold[i][1] );
		
	}

}

void printCard(int cardnum) {
	
	
	printf(" %d ", cardnum);
	
	return;
}

void printUserCardStatus(int user, int cardcnt){
	
	int i;
	
	printf("       -> card : ");
	for(i=0; i<cardcnt; i++)
		printCard(cardhold[user][i]);
	printf("\t  :::\n");
}

int getAction(void) {
	// player의 현재 카드합이 17미만 - go 
	// player의 현재 카드합이 17이상이면 stop. 
	
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {

	// check the card status ::: calcStepResult() -> 아마 카드합을 계산하는 함수. 
		// 현재 카드합 계산 
		if // 카드의 합이 21이면 블랙잭 -> 바로 승리 - gameEnd == 0 
		else if  // 카드 합이 21이 넘으면 -> 바로 짐 - gameEnd == 0;
		else if // 카드 합이 1이상 21미만 이면 -> ge, stop을 받음 
			// 만약에 go를 받음 -> pullcard, printcard.
			 
}

int checkResult() {
	
}

int checkWinner() {
	
}





int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();

	//Game initialization --------
	//1. players' dollar
	//2. card tray
	mixCardTray();

	//Game start --------
	do {
		printf("----------------------------------------------------\n");
		printf("----------- Round %d (cardIndex : %d) ---------------------\n", n_round, cardIndex );
		printf("----------------------------------------------------\n");
		printf("\n");
		
		betDollar();
		printf("\n");
		offerCards(); //1. give cards to all the players
		
		printf("-------CARD OFFERING -------\n");
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		printf(">>> my turn! ----------\n");
		printUserCardStatus(n_user, 2);
		
		// check the card status ::: calcStepResult() -> 아마 카드합을 계산하는 함수. 
		if // 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남 , 배팅금액 2배 얻음 
		else if  // 카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남 , 배팅금액 잃음 
		else if // 카드 합이 1이상 21미만 이면 -> ge, stop을 받음 
			// 만약에 go를 받음 -> pullcard, printcard.
			 
	
		for (i=0; i<n_user; i++) // each player  
		{
			printf(">>> player %d turn! ------------ \n ", i);
			printUserCardStatus(i, 2);
			if // 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남, 배팅금액 2배 얻음 
			else if  // 카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남  
			else if // 카드 합이 1이상 21미만 이면 getAction();
					
		}
	
		if (i=n_user+1) // dealer turn
		{
			// 같은 과정 반복 
			// * server의 카드합계 표시. 
		}
		
		checkResult(); // turn 종료 후 player의 최종 결과 출력 (승패결과 및 승패 이유, 배팅금액증감) 
		// 여기서 만약 한명이 파산 -> gameEnd == 0 , cardtray의 카드가 다 소진 -> gameEnd==0;  
		
	}
		n_round++;
		
		
	
	} while (gameEnd == 0);
	
	
	checkWinner();
	
	
	return 0;
}
