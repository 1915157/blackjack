#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "C:/Codes/blackjack/Mix_Pull_Card_Betting.c"

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
int dollar[N_MAX_USER]; // dollar of each player (including user to player_max)
int bet[N_MAX_USER];	// betting money of each player (including user to player_max)

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;	// total number of used card						
int Cardnum; // result of CardTray[];
int RealCardnum; // number of card, it is different from Cardnum. it is 1~10.
 

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

// play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
int cardSum[N_MAX_USER]; 					// sum of the cards
int bet[N_MAX_USER];						//current betting
int gameEnd = 0;							//game end flag

int n_morecard = 0;							// number of Go card of user 
int n_morecard_player =0;					// number of Go card of each player
int n_morecard_dealer = 0;					// number of Go card of dealer

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
		 
int getAction(void) {

	int i = 0; 
	int GoStopAnswer;						// answer of go or stop

	
	printf("\t ::: Action? (0 - go, 1 - stay)  : ");
	scanf("%d", &GoStopAnswer);

		
		if (GoStopAnswer == 0)
			{	
				
				cardhold[n_user][n_morecard + 2] = pullCard();
				printf("\t -> card : ");				
				 
				 for(i=0; i<= n_morecard + 2 ; i++)
					 printCard(cardhold[n_user][i]);
				
				printf(" \n");
				 	
				n_morecard++;
				calcStepResult(n_user,n_morecard); 
				if (cardSum[n_user] < 21)
					getAction();
				// 합계산하고 21안넘었으면 getAction을 반복.
			}
		
		else if (GoStopAnswer == 1)
			{
				printf("\t ::: STAY! \n");				
			}

	return (cardSum[n_user]);

}

int checkResult(int user) {
	
	if (cardSum[user] > 21 ) 
		{
		printf(" lose due to over flow! ($ %d)", dollar[user]);
		
		// if someone bankrupt, end round and game over.
		if (dollar[user] == 0)
			{
				printf("bankrupted! game will be ended");
				gameEnd++; 	
			}
		
		}
	
	else if (cardSum[user] == 21)
		printf("BlackJack! win (& %d)", dollar[n_user]);
	
	else if (cardSum[user] < 21)
		{
			// compare dealer's card sum and user's card sum 
			if (cardSum[user] >= cardSum[n_user + 1] ) 
				printf("win (sum : %d) --> $ %d", cardSum[user], dollar[user] );
			else if (cardSum[user] < cardSum[n_user + 1 ])
				printf("lose! (sum : %d) --> $ %d", cardSum[user], dollar[user] );
		}	
		
	return;	
}

int checkWinner(void) {
	
	int i,j,k;
	int max = 0;
	
	//user, player1~player max 까지의 dollar 금액 출력 
	printf("  -> game end! your money : $ %d", dollar[n_user] );
	
	for(i=0; i<n_user; i++)
		printf(" $ %d ", dollar[i]);
	printf("\n");
	
	// user, player1~ player max 들의 dollar 금액 비교 
	for(j=0; j<=n_user; j++)
	{
		if(dollar[j] > max)
		 max = dollar[j];
	}		
	
	// max에 해당하는 j값에 따른 승패 결정. (dollar가 가장많은자가 승자) 
	if (dollar[n_user] = max)
		printf(" you win");
	else if (dollar[j] = max)
		printf("player %d 's win", j);
	
	
}





int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i,j;

	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();

	//Game initialization --------
	//1. players' dollar
	//2. card tray
	mixCardTray();

	//Game start --------
	do 
	{	
		roundIndex++; 
		printf("----------------------------------------------------\n");
		printf("----------- Round %d (cardIndex : %d) ---------------------\n", roundIndex, cardIndex );
		printf("----------------------------------------------------\n");
		printf("\n");
		
		betDollar();
		printf("\n");
		offerCards(); //1. give cards to all the players
		
		printf("-------CARD OFFERING -------\n");
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
	// user turn	
		printf(">>> my turn! ----------\n");
		printUserCardStatus(n_user, 2); //현재 여기까지만 작동됨. 
		
		// check the card status ::: calcStepResult() -> 아마 카드합을 계산하는 함수. 
		 
		// n_user은 처음에 받음 값, n_morecard[5] = {0,0,0,0,0|으로 초기화된 상태. 
		
		calcStepResult(n_user,n_morecard); 
			// 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남 , 배팅금액 2배 얻음 
		 if (cardSum[n_user] == 21 )
		 	
			{
				printf("\t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[n_user], dollar[n_user] + 2*bet[n_user]);
		 		dollar[n_user] = dollar[n_user] + 2*bet[n_user];
			}
		 	//카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남 , 배팅금액 잃음
		 else if (cardSum[n_user] > 21)	 
		 	{
				printf("\t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[n_user], bet[n_user], dollar[n_user] - bet[n_user]);
		 		dollar[n_user] = dollar[n_user] - bet[n_user];
			}
		 //카드 합이 1이상 21미만 이면 -> go, stop을 받음
		 else 
			getAction(); // 여기서 Go햇을경우 위의 과정을 반복.	
			
			 
	// player turn
		for (i=1; i<n_user; i++) // each player  
		{
			printf(">>> player %d turn! ------------ \n ", i);
			printUserCardStatus(i-1, 2);
			
			// 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남 , 배팅금액 2배 얻음 
			 if (cardSum[i] == 21 )
		 	
				{
				printf("\t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[i], dollar[i] + 2*bet[i]);
		 		dollar[i] = dollar[i] + 2*bet[i];
				}
		 	
			 //카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남 , 배팅금액 잃음
			 else if (cardSum[i] > 21)	 
		 		{
				printf("\t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[i], bet[i], dollar[i] - bet[i]);
		 		dollar[i] = dollar[i] - bet[i];
				}
			 //카드 합이 1이상 21미만 이면 -> go, stop을 받음 (17이상이면 STAY, 17미만이면 Go) 
			 else 
		 		{
				 if (cardSum[i] >= 17)
		 			printf("\t ::: STAY!");
		 	
				 else if (cardSum[i] < 17)
		 			{
					 	do{
					 		printf("\t ::: GO!");
					 		
					 		
					 		cardhold[i][n_morecard_player + 2] = pullCard();
					 		printf("\t -> card : ");
					 		
					 		for(j=0; j<=n_morecard_player + 2; j++)
					 			printCard(cardhold[i][j]);
					 			
					 		printf("\n");
						 	n_morecard_player++;

						 } while (cardSum[i] < 17 );
					
						if (cardSum[i] >= 17 && cardSum[i]<21)
							printf("\t ::: STAY!");
					}
				}
				
		}
	
			
	// dealer turn
			printf(">>> server turn! ------------ \n ");
			printUserCardStatus(n_user+1, 2);
				
				//dealer 가 블랙잭일 경우 - 다른 플레이어가 블랙잭이 아닌 이상 모두 lose.  
			 if (cardSum[n_user + 1] == 21 )
				printf("\t ::: [[[[[[[  server result is Black Jack!  ]]]]]]] ");
				// blackjack일 경우 아직 미확정. 
				
				//dealer가 21을 넘음 -> 다른 플레이어가 21이 넘지 않는경우 모두 이김. 
			 else if (cardSum[n_user + 1] > 21)	 
		 		{
				  printf("\t ::: server DEAD (sum : %d) \n ", cardSum[n_user + 1]);
				  printf("[[[[[[[ server result is . . . . . . . . overflow!!]]]]]]]"); 
				}
				
				//dealer가 21미만 -> 17보다 작으면 Go, 17보다 크면 STAY. 
			 else 
		    	{
				 if (cardSum[n_user + 1] >= 17)
		 			printf("\t ::: ");
				
				 else if (cardSum[n_user + 1] < 17)
		 			{
					 	do{
					 		printf("\t ::: GO!");
					 		
					 		
					 		cardhold[n_user + 1 ][n_morecard_dealer + 2] = pullCard();
					 		printf("\t -> card : ");
					 		
					 		for(j=0; j<=n_morecard_player + 2; j++)
					 			printCard(cardhold[n_user + 1][j]);
					 			
					 		printf("\n");
						 	n_morecard_dealer++;

						 } while (cardSum[n_user + 1] < 17 );
					
					if (cardSum[n_user+1] >= 17 && cardSum[n_user+1]<21)
						printf("\t ::: ");
					}
					
				} printf("[[[[[[[ server result is . . . . %d ]]]]]]]", cardSum[n_user+1]);
			
	//print result of this round 
			
		printf(" ------------------ ROUND %d result . . . . \n", roundIndex);
		printf("  -> your result : ")
		checkResult(n_user); // turn 종료 후 player의 최종 결과 출력 (승패결과 및 승패 이유, 배팅금액증감) 
		
		for(i=0; i<n_user; i++)
		{
			printf("  -> %d 'th player's result : ", i+1);
			checkResult(i);
			
		}	
		
		// 여기서 만약 한명이 파산 -> gameEnd++   
		
	
		
	// game ends when running out of cardtray (cardindex)	
	if (cardIndex >= 51)
		gameEnd++;
	
	} while (gameEnd == 0);
	
	//printf result of total game. 	
	checkWinner();
	
	
	return 0;
}
