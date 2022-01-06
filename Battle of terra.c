#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define SIZE 5
//Battle Of Terra - Nelson Josue Alvarez

//The following list are all of the functions utilized, i will go into detail for each one when they are defined
void spaces();
void create_unit1(int *he1, int *atke1, int *defe1);
void create_unit2(int *he2, int *atke2, int *defe2);
void preview_location(int loc);
void selecting_location(int locn, int arean);
void enemyselecting_location(int locn, int arean);
void entering_preview();
void entering_selecting();
void setlocation(int a[4][3],int locsn, int areasn);
void enemysetlocation(int a[4][3],int locsn, int areasn);
void checkinglocation(int loc1, int loc2);
void enemyturn();
void turnc(int *turn);
void incrementturn(int *turn);
void health_decrease(int *he, int *check);
void attack_increase(int *at, int *check);
void defense_decrease(int *de, int *check);
void health_vastdecrease(int *he2, int *check);
void skeletal_count(int *location_counter, int *apply);
void Drake_count(int *location_counter, int *apply);
void Dark_count(int *location_counter, int *apply);
void Abyss_count(int *location_counter, int *apply);
void battle( int *plh, int *pla, int *pld, int *enh, int *ena, int *end, int *turns);
void checkgame();
void start();
void intro();


//These are all the variables utilized
//the following are the vairables for the hleath,attack, and defense for each respective unit. plocnum, locnum, and areanum are variables for the users input. plocnum is used when taking input for the preveiwing location stage
//locnum and areanum are used when the user selects the location they want to go to. Player_loc is specefically for the program to know the users current location which value given by locnum and areanum in the array  Location.
int h1,atk1,def1,h2,atk2,def2, plocnum, locnum, areanum, player_loc;

//The following variables are counters for the locations, while the vairables from sdc_two and onwards are vairables used to check if the enemy has gone to the location, and increments each time they go to that location
int sdc,dmc,dfc,acc, sdc_two,dmc_two, dfc_two, acc_two;

//These vairables are used to chek if the user has gone to the location for the first time which gives them the value of 1 while if it's more than the first time, it will be 0 which will indicate to not conduct the debuff / buff
int sdcc,dmcc,dfcc,accc, sdcc_two, dmcc_two, dfcc_two ,accc_two;

//enemy_loc is the value that is given by using the array location with enemy_lselection & enemy_aselection as the parameters.
int enemy_loc, enemy_aselection,enemy_lselection;

//This is a variable used to determine how many turns have passed, an event amount of turns means the enemys turn, while an odd amount of turns in the players turn.
int turn_count;

//game is used to determine if the game is over or not
int game;

//rety is used to determine if the user wants to play again or just close the game
int retry;

//This is the array that is utilized throughout the game. [SIZE] is correspodning to the locations while [3] is for the areas within the location
int location[SIZE][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}, {13,14,15}};

//Within the main method, we call start() to begin the program, and from there we leave it all up to the other functions.
int main(void) {
	start();
	return 0;	
}

//For the two create functions, the stats are pointers because these will be altered constantly throughout the game, so it's important to easily identify them
//This function creates the users unit, which has randomized stats
//To create the random values, I utilized this source: https://www.geeksforgeeks.org/generating-random-number-range-c/
//The source above allowed me to know how to utilize the random function.
void create_unit1(int *he1, int *atke1, int *defe1){
	//Here are creating the value for users health
	*he1 = (rand()%(25-20+1))+20;
	//Here are creating the value for users attack
	*atke1 = (rand()%(15-10+1))+10;
	//Here are creating the value for users defense
	*defe1 = (rand()%(15-10+1))+10;	
}

//This function creates the opponents unit, which also has random stats
void create_unit2(int *he2, int *atke2, int *defe2){
	//Here are creating the value for opponents health
	*he2 = (rand()%(25-20+1))+20;
	//Here are creating the value for opponents attack
	*atke2 = (rand()%(15-10+1))+10;
	//Here are creating the value for opponents defense
	*defe2 = (rand()%(15-10+1))+10;	
}

//This function allows the user to know where their unit will be entering, and this will call the debuff or buff functions. It uses previous functions to increment skeletal count and dtermine if the buff/debuff should be applied
void selecting_location(int locn, int arean){
	switch(locn){
		case 0:
			printf("\n Entering Skeletal Dungeon, your unit will have their health decreased by 13%% \n");
			//Here we are taking sdc which is the amount of times you visited skeletal dungeon, and sdcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			skeletal_count(&sdc, &sdcc);
			//Here we are applying the debuff only if sdcc is equal to 1 thanks to the function health_decrease
			health_decrease(&h1, &sdcc);
			break;
		case 1:
			printf("\n Entering Drake Mountain, your unit will have their attack increased by 25%% \n");
			//Here we are taking dmc which is the amount of times you visited Drake Mountain, and dmcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			Drake_count(&dmc, &dmcc);
			//Here we are applying the buff only if dmcc is equal to 1 thanks to the function attack_increase
			attack_increase(&atk1, &dmcc);
			break;
		case 2:
			printf("\n Entering Dark Forest, your unit will have their defense decreased by 25%% \n");
			//Here we are taking dfc which is the amount of times you visited Dark Forest, and dfcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			Dark_count(&dfc, &dfcc);
			//Here we are applying the debuff only if dfcc is equal to 1 thanks to the function defense_decrease
			defense_decrease(&def1, &dfcc);
			break;
		case 3:
			//Here we are taking acc which is the amount of times you visited Drake Mountain, and accc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			printf("\n Entering Abyss Cavern,  your unit will have their health decreased by 25%%  \n");
			Abyss_count(&acc,&accc);
			//Here we are applying the debuff only if accc is equal to 1 thanks to the function health_vastdecrease
			health_vastdecrease(&h1, &accc);
			break;
		case 4:
			printf("\n Entering Fortress of Nullification, your unit will not recieve any buffs or debuffs while in this location \n");
			break;
		default:
			printf("\n Invalid location \n");
			entering_selecting();
			break;
	}	
}

//This function does the same thing but for the enemy, this allows the user to use the knowledge they know so far to determine where their enemy is located.
void enemyselecting_location(int locsn, int areasn){
	switch(locsn){
		case 0:
			printf("\n Enemy Entering Skeletal Dungeon, their unit will have their health increased by 13%% \n");
			//Here we are taking sdc which is the amount of times the computer visited skeletal dungeon, and sdcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			skeletal_count(&sdc_two, &sdcc_two);
			//Here we are applying the debuff only if sdcc is equal to 1 thanks to the function health_decrease
			health_decrease(&h2, &sdcc_two);
			break;
		case 1:
			printf("\n Enemy Entering Drake Mountain, their unit will have their attack increased by 25%% \n");
			//Here we are taking dmc which is the amount of times the computer visited Drake Mountain, and dmcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			Drake_count(&dmc_two, &dmcc_two);
			//Here we are applying the buff only if dmcc is equal to 1 thanks to the function attack_increase
			attack_increase(&atk2, &dmcc_two);
			break;
		case 2:
			printf("\n Enemy Entering Dark Forest, their unit will have their defense decreased by 25%% \n");
			//Here we are taking dfc which is the amount of times the computer visited Dark Forest, and dfcc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			Dark_count(&dfc_two, &dfcc_two);
			//Here we are applying the debuff only if dfcc is equal to 1 thanks to the function defense_decrease
			defense_decrease(&def2, &dfcc_two);
			break;
		case 3:
			printf("\n Enemy Entering Abyss Cavern,  their unit will have their health decreased by 25%%  \n");
			//Here we are taking acc which is the amount of times the computer visited Drake Mountain, and accc which is the currrent value of the varibale to check if we should apply the buffs or debuffs
			Abyss_count(&acc_two,&accc_two);
			//Here we are applying the debuff only if accc is equal to 1 thanks to the function health_vastdecrease
			health_vastdecrease(&h2, &accc_two);
			break;
		case 4:
			printf("\n Enemy Entering Fortress of Nullification, their unit will not recieve any buffs or debuffs while in this location \n");
			break;
		default:
			printf("\n Enemy Invalid location \n");
			break;
	}	
}

//This function simply allows the user to put in a number ranging from 0-4 which allows the user to see the potential locations, and potential buffs or debuffs that can alter their un
void preview_location(int loc){
	switch(plocnum){
		case 0:
			printf("\n Your unit would enter Skeletal Dungeon, it will have its health decreased by 13%% \n");
			break;
		case 1:
			printf("\n Your unit would enter Drake Mountain, it will have its attack increased by 25%% \n");
			break;
		case 2:
			printf("\n Your unit would enter Dark Forest, it will have its defense decreased by 25%% \n");
			break;
		case 3:
			printf("\n Your unit would enter Abyss Cavern, it will have its health decreased by 25%% \n");
			break;
		case 4:
			printf("\n Your unit would enter Fortress of Nullification, it will not recieve any buffs or debuffs while in this location\n");
			break;
		default:
			printf("\n Invalid location \n");
			entering_preview();
			break;
	}	
}
//This function allows the user to be able to preview a location through a simple function call, the variable plocnum is a vairbale for the preveiew selection input.
void entering_preview(){
	//It prints out how many turns have passed and indicates whose turn it is, if it's even it's the opponents turn but if it's odd it's the users turn.
	printf("\n Turn: %d", turn_count);
	//This while look makes sure the inputs do not exceed or are less than the 0-4.
	while((plocnum<0 || plocnum>4)){
		printf("\n PREVIEW LOCATION STAGE: please enter a number ranging from 0-4 to see avaliable locations: \n");
		scanf("%d", &plocnum);
		fflush(stdin);
	}
	//Then we call the function to display the user a preview of the location they selected 
	preview_location(plocnum);
	//We then set plocnum which the preview location number to equal -1 so the while loop does not repeat itself if we retain the value the user inpuuted before.
	plocnum = -1;
}
//This function sets the players current location, this function is used in the function entering selection so the location will always be set to a valid value in the array.
void setlocation(int a[4][3],int locsn, int areasn){
	//locsn can have calues ranging from 0-4, while areasn can have values ranging from 0-2.
	player_loc = a[locsn][areasn];
}

//This functions sets the enemys current location, this function will be used during the function enemy turn
void enemysetlocation(int a[4][3],int locsn, int areasn){
	//locsn can have calues ranging from 0-4, while areasn can have values ranging from 0-2.
	enemy_loc = a[locsn][areasn];
}

//This is the most important function since this checks if the players location is the same as the enemys location. If the condition is met, combat will be initiated
void checkinglocation(int loc1, int loc2){
	//We first check if they are on the same location which is a vlue indicated by the two dimensional array with the two inputs given by the uer or randomy generated by the computer.
	if(loc1 == loc2){
		printf("\n Both Units are on the same location, Combat will now commence!");
		//We then call the battle function with all the necessray information to to commence the battle.
		battle( &h1, &atk1, &def1, &h2, &atk2, &def2, &turn_count);
	}
}

//This will be the function used constantly since this allows the user to select where their unit will be located.
//It also increments the variable turn to indicate the turn is over.
void entering_selecting(){
	if(turn_count!=1){
		printf("\n Turn: %d", turn_count);
	}
	//Here we have another while loop to ensue the vaues for locnum and areanum do not exceed 0-4, or 0-2 respectively.
	while((locnum<0 || locnum>4) || (areanum<0||areanum>2)){
		printf("\n SELECTING LOCATION STAGE: please enter a number ranging from 0-4 for your location, and where you want to be 0-2: (example input:0 2 = Skeletal Dungeoun area 3):  \n");
		scanf("%1d %1d", &locnum,&areanum);	
		fflush(stdin);
	}
	//We then call selecting_location to set the location and apply the buffs. then we ca;; setlocation to assign the users location to the number designated from the array using the users locnum and areanum
	selecting_location(locnum, areanum);
	setlocation(location, locnum, areanum);
	printf("\n Your Unit: health: %d , Attack: %d, Defense: %d \n", h1, atk1, def1);
	checkinglocation(enemy_loc, player_loc);
	spaces();
	//Then we increment turn to ensure the opponent will have a trun and we set locnum and areanum to -1 to esnure the while loop gets called again when it's the users turn again.
	incrementturn(&turn_count);
	locnum = -1;
	areanum = -1;
	
}

//This is the function that's called when turn is divisble by 2, this will allow the computer to set a location, set buffs / debuffs to the enemys unit, and checks if it's location is the same as the users.
//It also increments the variable turn to indicate the turn is over.
void enemyturn(){
	printf("\n Turn: %d", turn_count);
	//It randomly generates a value ranging from 0-4 for location
	enemy_lselection = (rand()%(4-0+1))+0;
	//It randomly generates a value ranging from 0-2 for Area
	enemy_aselection = (rand()%(2-0+1))+0;
	//We then call the following methods to set debuffs/buffs, set the enemys location, and to check if the opponent and user are on the same location.
	enemyselecting_location(enemy_lselection, enemy_aselection);
	enemysetlocation(location, enemy_lselection, enemy_aselection);
	checkinglocation(enemy_loc, player_loc);
	spaces();
	//We then increment turn to make it the players next turn
	incrementturn(&turn_count);
	
}

//This is the function that will check whose turn it is, and what will occur. If turn is divisble by 2, then it's the enmys turn while if it is odd, then it's the players turn.
void turnc(int *turn){
	//This simply checks if turnc(turn counter) is even it's the enemys turn but if it's odd it's the iusers turn. 
	if((*turn % 2) == 0){
		enemyturn();
		turnc(&turn_count);
	}
	else{
		entering_selecting();
		turnc(&turn_count);	
	}
}

//This just increments the variable turn which makes it eaasier to determine the current value of turn
void incrementturn(int *turn){
	*turn+=1;
}

//This functions check if the variable Check is 1(meaning this is their first time in the location, NOT area) which then causes the debuff to occur to the respective variable.
//The parameters he,at,de,and he2 can be swapped with the users units health or the opponents units health.
void health_decrease(int *he, int *check){
	if(*check == 1){
		//Then we apply the debuff to the respective unit
		*he = ( *he -  ((*he) * .13) );
	}
	else{
		printf("\n You already went to this location once, debuffs and buffs can only occur once! \n");
	}
}

void attack_increase(int *at, int *check){
	if(*check == 1){
		//Then we apply the buff to the respective  unit
		*at = ( *at +  ((*at) * .25) );
	}
	else{
		printf("\n You already went to this location once, debuffs and buffs can only occur once! \n");
	}
}

void defense_decrease(int *de, int *check){
	if(*check == 1){
		//Then we apply the debuff to the respective unit
		*de = ( *de -  ((*de) * .25) );
	}
	else{
		printf("\n You already went to this location once, debuffs and buffs can only occur once! \n");
	}
}

void health_vastdecrease(int *he2, int *check){
	if(*check == 1){
		//Then we apply the debuff to the respective unit
		*he2 = ( *he2 -  ((*he2) * .25) );
	}
	else{
		printf("\n You already went to this location once, debuffs and buffs can only occur once! \n");
	}
}


//These variables increment the counter for the respective location, and if it's not one the variable used in debuff/buff functions known as check will be set to 0
//The process is just increase the counter, if it's equal to 1, apply is set to 1, but anything else then apply is equal to 0, this is done to ensure  neither the player or opponent can stack the buffs or debuffs.
void skeletal_count(int *location_counter, int *apply){
	*location_counter+=1;
	if(*location_counter == 1) {
		*apply = 1;
	}
	else{
		*apply = 0;
	}
}

void Drake_count(int *location_counter, int *apply){
	*location_counter+=1;
	if( *location_counter == 1) {
		*apply = 1;
	}
	else{
		*apply = 0;
	}
}

void Dark_count(int *location_counter, int *apply){
	*location_counter+=1;
	if(*location_counter == 1) {
		*apply = 1;
	}
	else{
		*apply = 0;
	}
}

void Abyss_count(int *location_counter, int *apply){
	*location_counter+=1;
	if(*location_counter == 1) {
		*apply = 1;
	}
	else{
		*apply = 0;
	}
}

//This function just adds spaces to ensure that there is not too much information on the screen
void spaces(){
	int i;
	for( i = 0; i< 10; i++){
		printf("\n");
	}
}

//This is the function that will cause the two units to initiate in combat, the combat is very simple however to ensure the victor is decided correctly I implemented if statements to ensure there would be mixups.
//In addition i made it check whose turn it was when combat was initiated to give that unit the advantage
//Within this function, it calls checkgame to make the code look less busy but to esnure the variable game is not lost.
void battle( int *plh, int *pla, int *pld, int *enh, int *ena, int *end, int *turns){
	spaces();
	printf("\n \n UNITS PRIOR TO BLESSINGS: \n");
	printf("\n \n Player Units Health: %d \n", *plh);
	printf("\n Enemy Units Health: %d \n \n", *enh);
	//we add the units def to their health.
	*plh += (*pld/2);
	*enh += (*end/2);
	printf("UNITS HAVE BEEN BESTOWED THEIR BLESSINGS: \n");
	printf("\n Player Units Health: %d \n \n", *plh);
	printf("\n Enemy Units Health: %d \n \n", *enh);
	//This is the while loop that will conduct the combat until either unit has health less than or equa to 0.
	while(*plh >=0 && *enh>=0 ){
		//If turn counter is even, the opponent has the first strike but if it's odd, then the user will have the first strike.
		if(*turns%2 == 0){
			printf("\n ENEMY UNIT ATTACKS! \n");
			//Here we decrease the player units health
			*plh -= *ena;
			printf("\n Player Units Health: %d \n", *plh);
			printf("\n Enemy Units Health: %d \n \n", *enh);
			if(*plh <= 0){
				printf("YOUR UNIT HAS BEEN DEFEATED!\n GAME OVER");
				checkgame();
				break;
				}
			else if(*enh <= 0){
				printf("ENEMY UNIT HAS BEEN DEFEATED! \n VICTORY!!");
				checkgame();
				break;
				}
			printf("\n YOUR UNIT ATTACKS! \n");
			//Here we decrease the opponents units health
			*enh -= *pla;
			printf("\n Player Units Health: %d \n", *plh);
			printf("\n Enemy Units Health: %d \n \n", *enh);
			if(*enh <= 0){
				printf("ENEMY UNIT HAS BEEN DEFEATED!\n VICTORY!!");
				checkgame();
				break;
				}
			else if(*plh <= 0){
				printf("YOUR UNIT HAS BEEN DEFEATED! \n GAME OVER");
				checkgame();
				break;
				}
		}
		else if(*turns%2 != 0){
			printf("\n YOUR UNIT ATTACKS! \n");
			//Here we decrease the opponents units health
			*enh -= *pla;
			printf("\n Player Units Health: %d \n", *plh);
			printf("\n Enemy Units Health: %d \n \n", *enh);
			if(*enh <= 0){
				printf("ENEMY UNIT HAS BEEN DEFEATED! \n VICTORY!!");
				checkgame();
				break;
				}
			else if(*plh <= 0){
				printf("YOUR UNIT HAS BEEN DEFEATED! \n GAME OVER");
				checkgame();
				break;
				}
			printf("\n ENEMY UNIT ATTACKS! \n");
			//Here we decrease the player units health
			*plh -= *ena;
			printf("\n Player Units Health: %d \n", *plh);
			printf("\n Enemy Units Health: %d \n \n", *enh);
			if(*plh <= 0){
				printf("YOUR UNIT HAS BEEN DEFEATED! \n GAME OVER");
				checkgame();
				break;
				}
			else if(*enh <= 0){
				printf("ENEMY UNIT HAS BEEN DEFEATED! \n VICTORY!!");
				checkgame();
				break;
				}
		}	
	}
}

//This is the function to allow the player to decide if they want to play again or not, if they input 1, the program will call start() to start the game from the very start while 0 just exits for the program.
void checkgame(){
	spaces();
	printf("\n FINAL RESULTS: \n");
	printf("\n Player Units Health: %d \n", h1);
	printf("\n Enemy Units Health: %d \n", h2);
	printf("\n The game is over, Thank You For Playing!");
	//This is another while loop to ensure that the retry value is the either 1 or 0.
	while(retry!= 0 && retry!= 1 ){
		printf("\n Would like to try again? (enter 0 for No, enter 1 for yes) : \n");
		scanf("%d", &retry);
		fflush(stdin);
		if(retry == 0){
			exit(0);
		} 
		else if(retry ==1){
			spaces();
			start();
			}
		}
}

void intro(){
	printf("\n Welcome To BATTLE OF TERRA, The rules are very simple \n");
	printf("\n 1. On your first turn, you will be able to preview only 1 of the 5 locations you can enter, so choose wisely! \n");
	printf("\n 2. Each turn you will select a location to enter, if your on the same location as your opponent, combat will commence. You will either gain an advantage or disadvantage so be wary..\n");
	printf("\n 3. If your unit has 0 or less health points by the end of the battle, you lose but if your opponents unit has less than or equal to 0 health points by the end of the fight , you win!  \n");
	printf("\n Now that you know the rules, let the game commence! ");
	spaces();
}
//This is the function used at the start of the program, and during the end when the user decides to play again.
void start(){
	intro();
	//We se the following values to these numbers to ensure the game can be run without any issue 
	retry = -1;
	plocnum= -1;
	areanum = -1;
	locnum = -1;
	player_loc = 0;
	enemy_loc = -1;
	turn_count = 1;
	
	//The following variables are counters for the locations the player selects 
	sdc = 0;
	dmc = 0;
	dfc = 0;
	acc = 0;
	
	//These vairables are used to chek if the user has gone to the location for the first time which gives them the value of 1 while if it's more than the first time, it will be 0 which will indicate to not conduct the debuff / buff
	sdcc = 0;
	dmcc = 0;
	dfcc = 0;
	accc = 0;
	
	//The following variables are counters for the locations the computer selects
	sdc_two = 0;
	dmc_two = 0;
	dfc_two = 0;
	acc_two = 0;
	
	//These vairables are used to chek if the computer has gone to the location for the first time which gives them the value of 1 while if it's more than the first time, it will be 0 which will indicate to not conduct the debuff / buff
	sdcc_two = 0;
	dmcc_two = 0;
	dfcc_two = 0;
	accc_two = 0;
	
	
	time_t t;
	//This was actually something suggested by one of my classmates to ensure that the program does provide actual random results, the credit for this goes Christopher Dunne for the improved strand
	srand((unsigned) time(&t));
	//Here we create the units, print their stats, and then let the game commence!
	create_unit1(&h1, &atk1, &def1);
	create_unit2(&h2, &atk2, &def2);
	printf("\n Your Unit has been created: health: %d , Attack: %d, Defense: %d \n", h1, atk1, def1);
	printf("\n Enemy unit has been created: health %d, Attack: %d, Defense: %d \n", h2, atk2, def2);
	entering_preview();
	entering_selecting();
	turnc(&turn_count);
}

