#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10

extern int N_CARDSET;
extern int N_CARD;
extern int CardTray[];
extern int Cardnum;
extern int cardIndex;
extern int n_user;
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern int cardSum[N_MAX_USER]; 					// sum of the cards

int mixCardTray(void){
	
	int i,j;
	int randNum1;
	int temp;
	
	for (i=0; i<N_CARDSET*N_CARD; i++)
	{
		CardTray[i] = i+1;
		Cardnum = i+1;
	}
	

	for (j=0; j<N_CARDSET*N_CARD; j++) // error in card shake, it doesn't work
		{
			
			randNum1 = rand() % (N_CARDSET*N_CARD);
			
			temp = CardTray[j];
			CardTray[j] = CardTray[randNum1];
			CardTray[randNum1] = temp;	
		
		}
	
	return;
}

int pullCard(void){ // ī�带 �̾ƾ� ��. 
	
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


void printCard(int Cardnum) {
	
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
			printf(" HRT %d", Cardnum%13);
						
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
			printf(" CLV %d", Cardnum%13);
						
			
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
			printf(" CLV %d", Cardnum%13);
						
			
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
			printf(" CLV %d", Cardnum%13);
	

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
	
	int sum = 0;
	int i;
	
	// check the card status ::: calcStepResult() -> �Ƹ� ī������ ����ϴ� �Լ�. 
		// ���� ī���� ��� 
		// if  ī���� ���� 21�̸� ���� -> �ٷ� �¸� -  �ش� round �� ���� 
		// else if  ī�� ���� 21�� ������ -> �ٷ� �� - �ش� round�� ���� 
		// else if ī�� ���� 1�̻� 21�̸� �̸� -> ge, stop�� ���� 
			// ���࿡ go�� ���� -> pullcard, printcard.
	for(i=0; i<n_morecard[user] + 2; i++)
	{
		// �������� ī�� ���ڷ� ���, cardNum�� 1~52�����̹Ƿ�.. ��ȯ �ʿ�!  
		
		if (Cardnum == 11 || Cardnum == 12 || Cardnum == 13 )
			cardhold[user][i] = 10;
		else if (Cardnum == 24 || Cardnum == 25 || Cardnum == 26)
			cardhold[user][i] = 
		sum = sum + cardhold[user][i];
	}
	
	cardSum[user] = sum; 		
		 
}

