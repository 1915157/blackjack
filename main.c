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
	
	for(i=0; i<N_CARDSET*N_CARD; i++)
		CardTray[i] = i;

	
	for (i=0; i<N_CARDSET*N_CARD; i++)
		{
			int randNum1 = rand() % N_CARDSET*N_CARD;
			int randNum2 = rand() % N_CARDSET*N_CARD;
			
			int temp;
			
			temp = CardTray[randNum1];
			CardTray[randNum1] = CardTray[randNum2];
			CardTray[randNum2] = temp;
			
		
		}

}

int pullCard(void){ //중복되지 않게 카드를 뽑아야 함. 
	
	int i = 1+rand()%N_CARDSET*N_CARD;
	
	CardTray[i];

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
	
	return;
}

void printCard(int cardnum){

	int i;

	// in cardtray[i], (or result of pulltray )
	if (0<=i && i<13){
		
		printf("HRT%d ", cardtray[i]);
	
	}
	
	if (0<=13 && i<26){
		
		printf("SPD%d ", cardtray[i]);
	
	}

	if (0<=26 && i<39){
		
		printf("DIA%d ", cardtray[i]);
	
	}
	
	if (0<=39 && i<52){
		
		printf("CLV%d ", cardtray[i]);
	
	}
}

// print initial card status
void printCardInitialStatus(void){
	
	printf(" --- server /t : X %d", );
	printf("  -> you \t : %d %d", );
	
	for (i=0; i<n_user-1; i++){
			
		printf("  -> player %d \t : %d %d", i+1, cardhold[i][0] ,cardhold[i][1] );
		
	}

}

int getAction(void) {
	
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
}

int checkWinner() {
	
}


void printUserCardStatus(int user, int cardcnt){
	int i;
	
	printf("      -> card : ");
	for (i=0; i<cardcnt; i++)
		printCard(cardhold[user][i]);
	printf("\t  ::: ");
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
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printf("-------CARD OFFERING -------\n");
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
	
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
