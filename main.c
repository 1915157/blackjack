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
int dollar[N_MAX_USER];
int bet[N_MAX_USER];	

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							
int Cardnum;

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users

// play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //cards that currently the players hold
int cardSum[N_MAX_USER]; 					// sum of the cards
int bet[N_MAX_USER];						//current betting
int GoStopAnswer = 0;						// answer of go or stop
int gameEnd = 0;							//game end flag

extern int mixCardTray();


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



int getAction(void) {
	// player�� ���� ī������ 17�̸� - go 
	// player�� ���� ī������ 17�̻��̸� stop. 
	printf("\t ::: Action? (0- - go, others - stay)  : \n");
	scanf("%d", &GoStopAnswer);
	printf(" %d", GoStopAnswer);	
		
		if (GoStopAnswer == 0)
			{
				do
				{
					n_morecard[n_user]++;
						
					cardhold[n_user][(n_morecard[n_user] + 2 )] = pullCard();
					printf(" ");
					printCard(cardhold[n_user+1][n_morecard[n_user] + 2]);
						
					calcStepResult(n_user,n_morecard[n_user]);	
						
				} while (cardSum[n_user] >= 21); 

	
}


int checkResult() {
	
}

int checkWinner() {
	
}





int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	int n_morecard[n_user];
	n_morecard[n_user] = 0;
	
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
		printUserCardStatus(n_user, 2);
		
		// check the card status ::: calcStepResult() -> �Ƹ� ī������ ����ϴ� �Լ�. 
		calcStepResult(n_user,n_morecard[n_user]); 
		if (cardSum[n_user] == 21 )
			printf("/t ::: Black Jack! congratulation, you win!! --> + $ %d ($ %d)\n", 2* bet[n_user], dollar[n_user] + 2*bet[n_user]);
		else if (cardSum[n_user] > 21)
			printf("/t ::: DEAD (sum : %d) --> -$ %d ($ %d)\n", cardSum[n_user], bet[n_user], dollar[n_user] - bet[n_user]);
		else 
			getAction();
					
				}
		//if ī���� ���� 21�̸� ���� -> �ٷ� �¸� - �ش� round�� ���� , ���ñݾ� 2�� ���� 
		//else if  // ī�� ���� 21�� ������ -> �ٷ� �� - �ش� round�� ���� , ���ñݾ� ���� 
		//else if // ī�� ���� 1�̻� 21�̸� �̸� -> go, stop�� ���� 
			// ���࿡ go�� ���� -> pullcard, printcard.
			 
	
		for (i=0; i<n_user; i++) // each player  
		{
			printf(">>> player %d turn! ------------ \n ", i);
			printUserCardStatus(i, 2);
			//if // ī���� ���� 21�̸� ���� -> �ٷ� �¸� - �ش� round�� ����, ���ñݾ� 2�� ���� 
			//else if  // ī�� ���� 21�� ������ -> �ٷ� �� - �ش� round�� ����  
			//else if // ī�� ���� 1�̻� 21�̸� �̸� getAction();
					
		}
	
		//if (i=n_user+1) // dealer turn
		//{
			// ���� ���� �ݺ� 
			// * server�� ī���հ� ǥ��. 
		//}
		
		checkResult(); // turn ���� �� player�� ���� ��� ��� (���а�� �� ���� ����, ���ñݾ�����) 
		// ���⼭ ���� �Ѹ��� �Ļ� -> gameEnd == 0 , cardtray�� ī�尡 �� ���� -> gameEnd==0;  
		
	
		
	
	roundIndex++;
		
		
	
	} while (gameEnd == 0);
	
	
	checkWinner();
	
	
	return 0;
}
