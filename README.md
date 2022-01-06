# BattleOfTerra

## Introduction
This is a program I made for my c++class, essentially we were allowed to create whatever we wanted as long as we implemented everything we learned from the course into the project. I decided to make a game that essentially utilizes a grid similar to tic tac toe but instead of having three x to win, you move a unit to a location on the grid which will cause buffs or debuffs. While you are moving your unit, the opponent computer will move their unit to a random spot on the grid. If both Units are on the same spot, combat will commence. This was a program I wanted to make since I wanted to make something different, but also challenging.

# The Games rules

This program essentially utilizes rules that are similar to a card game, I mostly took inspiration from the game franchise fire emblem and old tcg known as choatic.

The game would operate under the following rules:

1. Each player will be given a character known as a unit, this unit will have randomized stats in health, attack and defense.
2. The user will be in the preview phase where they can provide coordinates to then be given a preview of the location. The user will be given information about the location and the potential buff or debuff
3. The user will then enter the moving phase where they will move their unit to a specefied location
4. What occurs next is the areas blessing phase where the user is told what buff or debuff occured to their unit, these buffs / debuffs are once per game meaning they do not stack to ensure some form of balance in the game.
5. Then the computers turn will occur where the computer wil go through the following phases but the location it selects is randomized.
6. If the two units are on the same location and same area within that location then the battle phase will commence 
7. This is where the blessing phase occurs where the units gain a boost in health based on their defense stat
8. The unit that attacks first is based upon who commenced the battle phase, if it is your turn and you chose a location that your opponent is on, then you attack first and vice versa.
9. The combat is simple automated turn absed combat but the unit whose HP is 0 or less first loses.

# The game in action

## The preview location Phase

The Preview location phase is where the user can provide an input to then be given a sneak peak of a location. As you can see randomized stats for the units are provided to the user so the user can have an understanding between their unit and its differences to the computers randomized unit.

![rules](https://user-images.githubusercontent.com/49813790/148456832-d20dc9a8-6939-4c27-bf13-be28446fdc76.png)

There are 5 locations in total:

- Abyss Cavern : This location provides a health debuff to your unit
- Skeletal Dungeon : This location provides a health debuff to your unit
- Fortress of Nullification : This location provides no buff or debuff to the unit
- Dark Forest : This location provides a defense debuff 
- Drake Mountain : This location provides an attack buff to your unit

As you can see, these five locations have very generic names since I just wanted to focus on the coding rather than naming of the locations.

![prevloc](https://user-images.githubusercontent.com/49813790/148457068-b16e2fb1-3c66-4a8a-9a1f-f623b1562432.png)

## Selecting Location Phase

This is the Selecting Location Phase where the user can provide the location number (0-4) and the area nunber(0-2) to then place their unit into that location. Each location has three areas, this is done so the user can try and place their unit in a specefic area to try and ensure the chances of landing on the same location are tiher high or low depending on your current stats.

![selloc](https://user-images.githubusercontent.com/49813790/148458159-9f9cad10-27c2-4c4a-a197-db93a5bd0506.png)

After you enter a location, the computer will then randomly select a location and area, once again the areas are made to ensure that the game is not long nor very easy to predict.

![enemyturn](https://user-images.githubusercontent.com/49813790/148458277-38588f99-25a4-4901-ad23-f3a6aaa01b31.png)



As you can see below, I then select a location and area number based on the given information, which somehow led me to accurately predict the location which will lead to the battle phase
![image](https://user-images.githubusercontent.com/49813790/148458457-b8e627a7-d3af-4982-9d24-37d8ddbe624a.png)

## Blessing Phase

The user will then be displayed the blessing phase, where their unit will then have their heakth increased, this is done to ensure that their issome way to counter the health debuffs in the game since they can be very detrimental.

![image](https://user-images.githubusercontent.com/49813790/148458645-8505e72e-17bd-4b19-ac60-90d52ec52a0b.png)

## The Battle Phase

The Battle Phase is very easy to explain, it is simple automated turn based combat similar to that of fire emblem but sadly lacking in visuals or complexity. As you see my unit was able to beat my opponents unit mostly based on its attack stat, if it went lower I may have been in trouble.

![image](https://user-images.githubusercontent.com/49813790/148458878-ffb27943-0096-448e-ac2f-2c765a862014.png)

# Important aspects of the program

Within this section i will delve into the important aspects of my program

## The Grid
The grid was one of the important aspects of the program since without it nothing else would work, this is why I created the following:

```
//This is the array that is utilized throughout the game. [SIZE] is corresponding to the locations while [3] is for the areas within the location
int location[SIZE][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}, {13,14,15}};
```

## Randomizing units

It was important to ensure that the units had randomized stats so that is why I did the following.

```
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
```

## Selecting location

To ensure that we could easily select a location, I made a switch statement which did a good portion of the work necessray for the other phases of the game

```
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
```

## Setting the locations

It was important to ensure that we can have the location for the user and computer to be set every time they selected a new location.

```
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
```

## Checking location

This is where we checked both locations to see if we need to commence the battle phase

```
//This is the most important function since this checks if the players location is the same as the enemys location. If the condition is met, combat will be initiated
void checkinglocation(int loc1, int loc2){
	//We first check if they are on the same location which is a vlue indicated by the two dimensional array with the two inputs given by the uer or randomy generated by the computer.
	if(loc1 == loc2){
		printf("\n Both Units are on the same location, Combat will now commence!");
		//We then call the battle function with all the necessray information to to commence the battle.
		battle( &h1, &atk1, &def1, &h2, &atk2, &def2, &turn_count);
	}
}
```

## Battle Phase & checking

The battle phase was simple but it was a little tricky initially to code since it required some understanding of the flow of the combat to ensure it was balanced. After he battle phase we ask the user if they want to continue or not.

```
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
```


## Enemy Turn

This is where we have the computer have its turn by ensuring the location and area values are randomized, while also doing everything necessray for the game to proceed.
```
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
```







