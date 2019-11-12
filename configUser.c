#include <stdio.h>
#include <stdlib.h>



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
	
	int n_user; // main파일에서 전역으로 한 후 지워질 것.  
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

	printf("--> card is mixed and put into the tray");
	
	return;
		
	}
	
	int main(void){
		
		configUser();
		
	}
