#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
extern int dollar[N_MAX_USER]; // dollar of each player (including user to player_max)
extern int bet[N_MAX_USER];	// betting money of each player (including user to player_max)

//card tray object
extern int CardTray[N_CARDSET*N_CARD];
extern int cardIndex = 0;	// total number of used card						
extern int Cardnum; // result of CardTray[];
extern int RealCardnum; // number of card, it is different from Cardnum. it is 1~10.
 

//player info
extern int dollar[N_MAX_USER];						//dollars that each player has
extern int n_user;									//number of users

// play yard information
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
extern int cardSum[N_MAX_USER]; 					// sum of the cards
extern int bet[N_MAX_USER];						//current betting
extern int gameEnd = 0;							//game end flag

extern int n_morecard = 0;							// number of Go card of user 
extern int n_morecard_player =0;					// number of Go card of each player
extern int n_morecard_dealer = 0;					// number of Go card of dealer


int mixCardTray(void){
	
	int i,j;
	int randNum1;
	int temp;
	
	for (i=0; i<(N_CARDSET*N_CARD); i++)
	{
		CardTray[i] = i+1;
		Cardnum = CardTray[i];
	}
	
	

	for (j=0; j<(N_CARDSET*N_CARD); j++) // error in card shake, it doesn't work
		{
			randNum1 = rand() % (N_CARD * N_CARDSET);
						
			temp = CardTray[j];
			CardTray[j] = CardTray[randNum1];
			CardTray[randNum1] = temp;	
		
		}
	
	return;
}


int pullCard(void){ // 카드를 뽑아야 함. 
	
	CardTray[cardIndex];
	cardIndex++;
	
	if (cardIndex >= 51)
		gameEnd++;
		
	return (CardTray[cardIndex]);
	
}
	

//offering initial 2 cards
void offerCards(void) {
	int i;

	//1. give two card for the dealer
	cardhold[n_user+1][0] = pullCard();
	cardhold[n_user+1][1] = pullCard();	

	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();

	//3. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}

	return;
}	


void printCard(int Cardnum) {
	
	RealCardnum = Cardnum % 13;
	
	if (Cardnum/13 == 0)
		if (Cardnum == 1)
			printf(" HRT A");
		else if (Cardnum == 11 )
			printf(" HRT K");
		else if (Cardnum == 12 )
			printf(" HRT J");
		else if (Cardnum == 13)
			printf(" HRT Q");
		
		else 
			printf(" HRT %d", RealCardnum);
						
	else if (Cardnum/13 == 1)
		if (Cardnum == 14)
			printf(" CLV A");
		else if (Cardnum == 24)
			printf(" CLV K");
		else if (Cardnum == 25)
			printf(" CLV J");
		else if (Cardnum == 26)
			printf(" CLV Q");
		
		else 
			printf(" CLV %d", RealCardnum);
						
			
	else if (Cardnum/13 == 2)
		if (Cardnum == 27)
			printf(" SPD A");
		else if (Cardnum == 37)
			printf(" SPD K");
		else if (Cardnum == 38)
			printf(" SPD J");
		else if (Cardnum == 39)
			printf(" SPD Q");
		
		else 
			printf(" SPD %d", RealCardnum);
						
			
	else if (Cardnum/13 == 3 || Cardnum/13 == 4) 
		if (Cardnum == 40)
			printf(" DIA A");
		else if (Cardnum == 50)
			printf(" DIA K");
		else if (Cardnum == 51)
			printf(" DIA J");
		else if (Cardnum == 52)
			printf(" DIA Q");
		
		else 
			printf(" CLV %d", RealCardnum);
	

	return;
}

// print initial card status
void printCardInitialStatus(){
	
	int i;
	
	printf(" --- server \t : X  ");
	printCard(cardhold[n_user+1][0]);
	printf("\n");
	
	printf("  -> you \t : " );
	printCard(cardhold[n_user][0]);
	printf(" ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	for (i=0; i<n_user-1; i++){
			
		printf("  -> player %d \t : ", i+1);
		printCard(cardhold[i][0]);
		printf(" ");
		printCard(cardhold[i][1]);
		printf("\n");
		
	}
	
	return;
}


void printUserCardStatus(int user, int cardcnt){
	
	int i;
	
	printf("       -> card : ");
	for(i=0; i<cardcnt; i++)
		printCard(cardhold[user][i]);
		printf(" ");
	printf("\t  :::\n");
	return;
	
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
// n_morecard means number of saying go! 

// 카드합을 계산하는 함 -> user가 지금까지 가지고 있는 카드의 합을 구함.  
int calcStepResult(int user, int n_morecard) { 
	// main에서 받은 n_user값을 user에 대입, n_morecard = 0 대입 
	// n_morecard 는 Go,Stop에서 go를 외쳤을 때의 카드 수 
	int sum = 0;
	int i;
		
	for(i=0; i<n_morecard + 2; i++)
	{
		// 현재까지 뽑은 카드가 k,Q,J에 해당되는 숫자일 때, 10으로 생각.  
		if (cardhold[user][i] == 11 || cardhold[user][i] == 12 || cardhold[user][i] == 13 || cardhold[user][i] == 24 || cardhold[user][i] == 25 || cardhold[user][i] == 26  || cardhold[user][i] == 37 || cardhold[user][i] == 38 || cardhold[user][i] == 39 || cardhold[user][i] == 50  || cardhold[user][i] == 51  || cardhold[user][i] == 52 )
			{
				sum = sum + 10;		// RealCardnum = 10; 실제카드값은 10이므로. 
			}
		else	
			sum = sum + (cardhold[user][i] % 13);
	}
	
	cardSum[user] = sum; 		
		 
	return;
}
		 
