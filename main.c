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
int dollar[N_MAX_USER];
int bet[N_MAX_USER];	

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							
int Cardnum;
int RealCardnum; // number of card, it is different from Cardnum. it is 1~10.
 

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

// play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
int cardSum[N_MAX_USER]; 					// sum of the cards
int bet[N_MAX_USER];						//current betting
int GoStopAnswer;						// answer of go or stop
int gameEnd = 0;							//game end flag

int n_morecard[N_MAX_USER] = {0,0,0,0,0};


int mixCardTray(void){
	
	int i,j;
	int randNum1;
	int temp;
	
	for (i=0; i<(N_CARDSET*N_CARD); i++)
	{
		CardTray[i] = i+1;
		Cardnum = i+1;
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

int pullCard(void){ // 카드를 뽑아야 함. 
	
	CardTray[cardIndex];
	cardIndex++;

	return;
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
			printf(" CLV A");
		else if (Cardnum == 37)
			printf(" CLV K");
		else if (Cardnum == 38)
			printf(" CLV J");
		else if (Cardnum == 39)
			printf(" CLV Q");
		
		else 
			printf(" CLV %d", RealCardnum);
						
			
	else if (Cardnum/13 == 3 || Cardnum/13 == 4) 
		if (Cardnum == 40)
			printf(" CLV A");
		else if (Cardnum == 50)
			printf(" CLV K");
		else if (Cardnum == 51)
			printf(" CLV J");
		else if (Cardnum == 52)
			printf(" CLV Q");
		
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
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
// n_morecard means number of saying go! 

int calcStepResult(int user, int n_morecard[user]) { 
	// main에서 받은 n_user값 대입, 0 대입. 
	int sum = 0;
	int i;
	
	// check the card status ::: calcStepResult() -> 아마 카드합을 계산하는 함수. 
		// 현재 카드합 계산 
		// if  카드의 합이 21이면 블랙잭 -> 바로 승리 -  해당 round 가 끝남 
		// else if  카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남 
		// else if 카드 합이 1이상 21미만 이면 -> ge, stop을 받음 
			// 만약에 go를 받음 -> pullcard, printcard.
	for(i=0; i<n_morecard[user] + 2; i++)
	{
		// 실질적인 카드 숫자로 계산, cardNum은 1~52까지이므로.. 변환 필요!  
		
		if (Cardnum == 11 || Cardnum == 12 || Cardnum == 13 || Cardnum == 24 || Cardnum == 25 || Cardnum == 26  || Cardnum == 37 || Cardnum == 38 || Cardnum == 39 || Cardnum == 50  || Cardnum == 51  || Cardnum == 52 )
			{
				sum = sum + 10;
			// RealCardnum = 10; 실제카드값은 10이므로. 
			}
		else	
			sum = sum + (cardhold[user][i] % 13);
	}
	
	cardSum[user] = sum; 		
		 
	return;
}
		 
int getAction(void) {
	// player의 현재 카드합이 17미만 - go 
	// player의 현재 카드합이 17이상이면 stop. 
	printf("\t ::: Action? (0- - go, others - stay)  : \n");
	scanf("%d", &GoStopAnswer);
	printf(" %d", GoStopAnswer);	
		
		if (GoStopAnswer == 0)
			{
			 do{
			 	
				n_morecard[n_user]++;
						
				cardhold[n_user][(n_morecard[n_user] + 2 )] = pullCard();
				printf(" ");
				printCard(cardhold[n_user+1][n_morecard[n_user] + 2]);
				// 합계산하고 21안넘었으면 getAction을 반복.
				getAction(); 
				} while(cardSum[n_user] >= 21);
			
			}
		
		else
			{
				printf("\t ::: STAY! \n");				
			}

	return;
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
		printf("----------- Round %d (cardIndex : %d) ---------------------\n", roundIndex+1, cardIndex );
		printf("----------------------------------------------------\n");
		printf("\n");
		
		betDollar();
		printf("\n");
		offerCards(); //1. give cards to all the players
		
		printf("-------CARD OFFERING -------\n");
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		printf(">>> my turn! ----------\n");
		printUserCardStatus(n_user, 2); //현재 여기까지만 작동됨. 
		
		// check the card status ::: calcStepResult() -> 아마 카드합을 계산하는 함수. 
		 
		// n_user은 처음에 받음 값, n_morecard[5] = {0,0,0,0,0|으로 초기화된 상태. 
		calcStepResult(n_user,n_morecard[n_user]); 
		
		 if (cardSum[n_user] == 21 )
		 	printf("/t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[n_user], dollar[n_user] + 2*bet[n_user]);
		 else if (cardSum[n_user] > 21)	 
		 	printf("/t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[n_user], bet[n_user], dollar[n_user] - bet[n_user]);
		 else 
			getAction(); // 여기서 Go햇을경우 위의 과정을 반복.	
			
			
		
		
		//if 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남 , 배팅금액 2배 얻음 
		//else if  // 카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남 , 배팅금액 잃음 
		//else if // 카드 합이 1이상 21미만 이면 -> go, stop을 받음 
			// 만약에 go를 받음 -> pullcard, printcard.
			 
	
		for (i=1; i<n_user; i++) // each player  
		{
			printf(">>> player %d turn! ------------ \n ", i);
			printUserCardStatus(i-1, 2);
			//if // 카드의 합이 21이면 블랙잭 -> 바로 승리 - 해당 round가 끝남, 배팅금액 2배 얻음 
			//else if  // 카드 합이 21이 넘으면 -> 바로 짐 - 해당 round가 끝남  
			//else if // 카드 합이 1이상 21미만 이면 getAction();
					
		}
	
		//if (i=n_user+1) // dealer turn
		//{
			// 같은 과정 반복 
			// * server의 카드합계 표시. 
		//}
		
		checkResult(); // turn 종료 후 player의 최종 결과 출력 (승패결과 및 승패 이유, 배팅금액증감) 
		// 여기서 만약 한명이 파산 -> gameEnd == 0 , cardtray의 카드가 다 소진 -> gameEnd==0;  
		
	
		
	
	roundIndex++;
		
		
	
	} while (gameEnd == 0);
	
	
	checkWinner();
	
	
	return 0;
}
