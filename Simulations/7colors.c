/* Template of the 7 wonders of the world of the 7 colors assigment. */

/* Cf. http://people.irisa.fr/Anne-Cecile.Orgerie/teaching2015.html  */

#include <stdio.h>  /* printf */
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "board.h"
#include "auxiliary.h"
#include "strategies.h"

#define NB_SIMULATIONS 1200

/** Program entry point */
int main() 
{
   printf("\n\n  Welcome to the 7 wonders of the world of the 7 colors\n"
	      "  *****************************************************\n\n"
	 "Current board state:\n");
   srand(time(NULL));
   print_board();

   int i = 0;
   int j = 0;
   
   int victories[5][5]; // victories[i][j] contains the number of victories of i over j
   for(i = 0 ; i < 5 ; i++){
	for(j = 0 ; j < 5 ; j++){
		victories[i][j] = 0;
	}
   }
   

   long int start = clock();

   void (*strats[5])(char) = {improved_random_play, spider, greedy, double_greedy, mix};
   char* names[5] = {"Improved Random","Spider","Greedy","Double Greedy","Mix"};
   int k = 0;
   float score1 = 0;
   float score2 = 0;


   for(i = 0 ; i < 4 ; i++){
	for(j = i+1 ; j < 5 ; j++){

		for(k = 0 ; k < NB_SIMULATIONS ; k++){
			printf("%s VS %s :\n", names[i], names[j]);
			random_filling();
			copy_board();
     		 	run_game(PLAYER1,strats[i],strats[j]);

			score1 = 100*score(PLAYER1)/((float) BOARD_SIZE*BOARD_SIZE);
			score2 = 100*score(PLAYER2)/((float) BOARD_SIZE*BOARD_SIZE);
			if(score1 > score2){(victories[i][j])++;}
			else{(victories[j][i])++;}

			get_saved_board();
			set_cell(0,BOARD_SIZE-1,PLAYER2);
			set_cell(BOARD_SIZE-1,0,PLAYER1);
			run_game(PLAYER2,strats[i],strats[j]);

			score1 = 100*score(PLAYER1)/((float) BOARD_SIZE*BOARD_SIZE);
			score2 = 100*score(PLAYER2)/((float) BOARD_SIZE*BOARD_SIZE);
			if(score1 > score2){(victories[i][j])++;}
			else{(victories[j][i])++;}
		}
	}
   }


   printf("Total execution time : %ld", (clock()-start)/CLOCKS_PER_SEC);
   printf("\n\n");

   for(i = 0 ; i < 4 ; i++){
	for(j = i+1 ; j < 5 ; j++){
		printf("%s VS %s :\n", names[i], names[j]);
		printf("%s : %d victories\n", names[i], victories[i][j]);
		printf("%s : %d victories\n", names[j], victories[j][i]);
		printf("\n\n");
	}
   }


   return 0; // Everything went well
}
