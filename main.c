#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "C:/Codes/blackjack/Card.c"

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
int CardTray[N_CARDSET*N_CARD]; // CardTray has max 52 cards.
int cardIndex;	// total number of used card						
int Cardnum; // result of CardTray[];
int RealCardnum; // number of card, it is different from Cardnum. it is 1~10.
 

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

// play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
int cardSum[N_MAX_USER]; 					// sum of the cards
int bet[N_MAX_USER];						//current betting
int gameEnd;								//game end flag

int n_morecard = 0; 							// number of Go card of user 
int n_morecard_player = 0;					// number of Go card of each player
int n_morecard_dealer = 0;					// number of Go card of dealer

// use instead of scanf because when I put another letter, it errors
int getIntegerInput(void) {
    
	int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    
	if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

//set the number of players (player settiing)
int configUser(void){
	
	int input; // variable that I input in getIntegerInput();
	
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

// betting 	
int betDollar(void){
	
	int i ;
			
	// betting my money		
	printf(" ----------- BETTING STEP -------\n");
	printf("-> your betting (total : &%d) : ", dollar[n_user]);
	scanf("%d", &bet[n_user] );
	
	// betting player's money
	for (i=0; i<n_user-1; i++){
		
		bet[i] = 1+rand()%N_MAX_BET;
	
		printf("-> player %d bets &%d (out of &%d)\n", i+1, bet[i], dollar[i]);
		
	}
	
	printf("------------------------------\n");
	
	return;
}

 


// calculate the card sum that user has until now 
int calcStepResult(int user, int n_morecard) { 
	// main에서 받은 n_user값을 user에 대입, n_morecard = 0 대입 
	// n_morecard 는 Go,Stop에서 go를 외쳤을 때의 카드 수 
	int sum = 0; 
	int i;
		
	for(i=0; i<n_morecard + 2; i++)
	{
		// 현재까지 뽑은 카드가 k,Q,J에 해당되는 숫자일 때, 10으로 생각.
		// when the card selected until now is K,Q,J,  Think of it as 10. (number)   
		if (cardhold[user][i] == 11 || cardhold[user][i] == 12 || cardhold[user][i] == 13 || cardhold[user][i] == 24 || cardhold[user][i] == 25 || cardhold[user][i] == 26  || cardhold[user][i] == 37 || cardhold[user][i] == 38 || cardhold[user][i] == 39 || cardhold[user][i] == 50  || cardhold[user][i] == 51  || cardhold[user][i] == 52 )
			{
				sum = sum + 10;		// because RealCardnum = 10;  
			}
		else	
			sum = sum + (cardhold[user][i] % 13); // cardhold[user][i] % 13 may appears RealCardnum.
	}
	
	cardSum[user] = sum; // total sum is cardSum[user]		
		 
	return;
}
		 
// when cardSum[user] < 21, decide GO? STOP? 		 
int getAction(int GoStopAnswer) {

	int i = 0; 
	
		if (GoStopAnswer == 0)
			{	
				
				cardhold[n_user][n_morecard + 2] = pullCard(); 
				printf("\t -> card : ");				
				 
				 for(i=0; i<= n_morecard + 2 ; i++)
					 printCard(cardhold[n_user][i]);
				
				printf(" \n");
				 	
				n_morecard++;
			// calculate cardSum, and if it is under 21, repeat.
				calcStepResult(n_user,n_morecard); 

			}
		
		else if (GoStopAnswer == 1)
			{
				printf("\t ::: STAY! \n");				
			}

	return (cardSum[n_user]);

}


// after the round, print result of player in the round (result of win or lose and the reason of that, plus or minus from each player's dollar) 
int checkResult(int user) {
	
	if (cardSum[user] > 21 ) 
		{
		printf(" lose due to over flow! ($ %d)\n", dollar[user]);
		
		// if someone bankrupt, end round and game over.
		if (dollar[user] == 0)
			{
				printf("bankrupted! game will be ended\n");
				gameEnd++; 	
			}
		
		}
	
	else if (cardSum[user] == 21)
		printf("BlackJack! win (& %d)\n", dollar[n_user]);
	
	else if (cardSum[user] < 21)
		{
			// compare dealer's card sum and user's card sum 
			if (cardSum[user] >= cardSum[n_user + 1] ) 
				{
					dollar[user] = dollar[user] + bet[user];
					printf("win (sum : %d) --> $ %d\n", cardSum[user], dollar[user] );
				}
				
			else if (cardSum[user] < cardSum[n_user + 1 ] && cardSum[n_user + 1 ] < 21)
				{
				
				dollar[user] = dollar[user] - bet[user];
				printf("lose! (sum : %d) --> $ %d\n", cardSum[user], dollar[user] );
					
					// if someone bankrupt, end round and game over.
					if (dollar[user] == 0)
					{
						printf("bankrupted! game will be ended\n");
						gameEnd++; 	
					}
				}
		}	
		
	return;	
}


int checkWinner(void) {
	
	int i,j,k;
	int max = 0;
	
	//print dollar of user and player1~player max 
	printf(" ---------------------------- \n");
	printf(" ---------------------------- \n");
	printf(" ---------------------------- \n");

	printf(" game end! your money : $ %d,", dollar[n_user] );
	printf(" players's money : ");
	
	for(i=0; i<n_user; i++)
		printf(" $ %d ", dollar[i]);
	printf("\n");
	
	// compare dollar of user and player1~ player max each other. 
	for(j=0; j<=n_user; j++)
	{
		if(dollar[j] > max)
		 max = dollar[j];
	}		
	
	// win and lose decide by j, makes max of dollar. 
	// winner is who has most dollar
	// 확실 x... 
	
	printf("player who has $ %d is win.", max);
	
	
}





int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i,j;
	int GoStopAnswer; 
	
	for(i=0; i<N_MAX_USER + 1 ; i++)
		cardSum[i] = 0;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();

	//Game initialization --------
	//1. players' dollar
	for (i=0; i<=n_user; i++){
		
		dollar[i] = 50;
	}		
	
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
		offerCards(); //1. give cards to all the players, including dealer
	
	// initial card offering
		printf("-------CARD OFFERING -------\n");
		
		printCardInitialStatus(); 
		printf("\n------------------ GAME start --------------------------\n");
		
	// user turn
		printf(">>> my turn! ----------\n");
		
	// print current card status : printUserCardStatus()	
		printUserCardStatus(n_user, 2); //현재 여기까지만 작동됨. 
			
		do
		{
	
		// check the card status ::: calcStepResult() 
			calcStepResult(n_user,n_morecard); 
		
		 
		// cardSum == 21,BlackJack! -> win! - end this round and get 2 * betting.
			 if (cardSum[n_user] == 21 ) 	
				{
					printf("\t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[n_user], dollar[n_user] + 2*bet[n_user]);
		 			dollar[n_user] = dollar[n_user] + 2*bet[n_user];
				}
		 		
		// cardSum > 21, lose -> end this round and lose betting.		
		 	else if (cardSum[n_user] > 21)	 
		 		{
					printf("\t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[n_user], bet[n_user], dollar[n_user] - bet[n_user]);
		 			dollar[n_user] = dollar[n_user] - bet[n_user];
				}
		 // 1< cardSum < 21, -> GO? STOP? ::: getAction()
		 	else 
				{
					do
					{
	
						printf("\t ::: Action? (0 - go, 1 - stay)  : ");
						scanf("%d", &GoStopAnswer);
	
					} while (GoStopAnswer != 0 && GoStopAnswer != 1 );
					
					getAction(GoStopAnswer); 

				}
					
		
		} while(cardSum[n_user] < 21 && GoStopAnswer == 0 ); // do until user dies or user says stop.
			 
	// player turn
		for (i=0; i<n_user-1; i++) // each player  
		{
			printf(">>> player %d turn! ------------ \n ", i+1);
			printUserCardStatus(i, 2);
			
			do
			{
			
			calcStepResult(i,n_morecard_player);
			
			// cardSum == 21,BlackJack! -> win! - end this round and get 2 * betting.
			 	if (cardSum[i] == 21 )
		 	
					{
					printf("\t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[i], dollar[i] + 2*bet[i]);
		 			dollar[i] = dollar[i] + 2*bet[i];
					}
		 	
			// cardSum > 21, lose -> end this round and lose betting.		
			 	else if (cardSum[i] > 21)	 
		 			{
					printf("\t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[i], bet[i], dollar[i] - bet[i]);
		 			dollar[i] = dollar[i] - bet[i];
					}
			 //카드 합이 1이상 21미만 이면 -> go, stop을 받음 (17이상이면 STAY, 17미만이면 Go)
			 // 1< cardSum < 21, -> (cardSum < 17) Go!, (cardSum>=17) STAY!
 
			 	else 
		 			{
				 	if (cardSum[i] >= 17)
		 				printf("\t ::: STAY!\n");
		 	
					 else if (cardSum[i] < 17)
		 				{
		
					 		printf("\t ::: GO!\n");
					 	
					 		cardhold[i][n_morecard_player + 2] = pullCard();
					 		printf("\t -> card : ");
					 		
					 		for(j=0; j<=n_morecard_player + 2; j++)
					 				printCard(cardhold[i][j]);
					 			
					 		printf("\n");
					 		n_morecard_player++;
						}
						
					}
				
			} while( cardSum[i] < 17 );
		
			n_morecard_player = 0; // initialize n_moreplayer for another player
		}
		
	// dealer turn
		printf(">>> server turn! ------------ \n ");
		printUserCardStatus( (n_user+1) , 2);
			
		do		
		{
			calcStepResult(n_user+1,n_morecard_dealer);
	
			// if dealer is BLACKJACK - other players lose except other players BLACKJACK.  
			 if (cardSum[n_user + 1] == 21 )
				printf("\t ::: [[[[[[[  server result is Black Jack!  ]]]]]]] \n");
				// blackjack일 경우 아직 미확정. 
				
			// cardSum of dealer > 21 -> other players win except cardsum of other players > 21  
			 else if (cardSum[n_user + 1] > 21)	 
		 		{
				  printf("\t ::: server DEAD (sum : %d) \n ", cardSum[n_user + 1]);
				  // 매번 dealer의 cardSum = 52로 나옴..? 
				  printf("[[[[[[[ server result is . . . . . . . . overflow!!]]]]]]]\n"); 
				}
				
				// cardSum of dealer < 21 -> cardSum of dealer < 17 - Go! , cardSum of dealer > 17 - STAY!
			 else 
		    	{
				 if (cardSum[n_user + 1] >= 17)
		 			printf("\t ::: \n");
				
				 else if (cardSum[n_user + 1] < 17)
		 			{
					 	
					 		printf("\t ::: GO!\n");
					 		
					 		
					 		cardhold[n_user + 1 ][n_morecard_dealer + 2] = pullCard();
					 		printf("\t -> card : ");
					 		
					 		for(j=0; j<=n_morecard_player + 2; j++)
					 			printCard(cardhold[n_user + 1][j]);
					 			
					 		printf("\n");
						 	n_morecard_dealer++;
					}
					
				} 
		} while(cardSum[n_user+1] < 17);
				
				printf("[[[[[[[ server result is . . . . %d ]]]]]]]\n", cardSum[n_user+1]); // location is unstable 위치 아직 미확정 
			
	//print result of this round 
			
		printf(" ------------------ ROUND %d result . . . . \n", roundIndex);
		printf("  -> your result : ");
		
		// after the round, print result of player in the round (result of win or lose and the reason of that, plus or minus from each player's dollar) 
		checkResult(n_user);
		
		for(i=0; i<n_user-1; i++)
		{
			printf("  -> %d 'th player's result : ", i+1);
			checkResult(i);
			
		}	
		
		// 여기서 만약 한명이 파산 -> gameEnd++   
		
			
	//initialize cardSum array after finish the round. 	
	for(i=0; i<n_user+1; i++)	
		cardSum[i] = 0;
		
	// game ends when running out of cardtray (cardindex)	
	if (cardIndex >= 51)
		{
			gameEnd++;
			printf("card ran out of the tray!! finishing the game ... \n");
		}
		
	} while (gameEnd == 0);
	
	//printf result of total game. 	
	checkWinner();
	
	
	return 0;
}
