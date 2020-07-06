/*
Name: Chance lewis
date: 10/19/19
Description: 2 player game of Yahtzee
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

/*
Description: Prints menu
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_menu(void);


/*
Description: prompts user for input and returns it
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int get_option(void);


/*
Description: Determines if input option is acceptable, returns 1 if so and 0 otherwise
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int
Return Type:
Preconditions:
Postconditions:
*/
int evaluate_option(int option);


/*
Description: continuously displays menu until proper option is input. returns the option
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int menu_select(void);


/*
Description: displays rules of the game
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_rules(void);


/*
Description: handles the actual gameplay
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void play_game(void);


/*
Description: generates a random integer from 1 to 6, inclusively
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int roll_die(void);


/*
Description: handles a player's entire turn
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array
Return Type: void
Preconditions: none
Postconditions: int array updated accordingly
*/
void take_turn(int score_card[]);


/*
Description: adds up a player's score
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array
Return Type: int
Preconditions: none
Postconditions: none
*/
int tally_score(int score_card[]);


/*
Description: determines who won, or who ties, and displays it
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int, int
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_victor(int player_1_score, int player_2_score);


/*
Description: rolls dice. does not roll dice that the player keeps.
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: int array in actual dice are modified if rerolled
*/
void roll_and_print_dice(int actual_dice[], int reroll[]);


/*
Description: displays dice values
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array
Return Type: void
Preconditions: none
Postconditions: none
*/
void print_dice(int actual_dice[]);


/*
Description: determines the frequency of each die face
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int frequency
Return Type: void
Preconditions: none
Postconditions: frequency modified, actual unchanged
*/
void count_dice(int actual_dice[], int frequency[]);


/*
Description: if less than 3 rolls have been thrown, allows the user to reroll if they choose
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int, int array
Return Type: int
Preconditions: none
Postconditions: int reroll updated to contain a 0 for dice that should not be rerolled. rerolled dice remain 1 as initialized
*/
int roll_again_question(int rolls, int reroll[]);


/*
Description: Determines the score based on option selected and dice thrown, and updates score card accordingly
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array, int
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void calculate_score_for_option(int score_card[], int frequency[], int option);


/*
Description: Displays score card in current state to user
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_score_card(int score_card[]);


/*
Description: determines if score card option selected is acceptable. returns 1 if so, and 0 otherwise. also includes relevant print statements
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int, int array, int array
Return Type: int
Preconditions: none
Postconditions: none
*/
int evaluate_score_card_option(int option, int score_card[], int frequency[]);


/*
Description: Determines if a dice throw is a Yahtzee. Returns 1 if so, and 0 otherwise
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array
Return Type: int
Preconditions: none
Postconditions: none
*/
int will_be_a_yahtzee(int frequency[]);


/*
Description: sums the ones shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_ones(int score_card[], int frequency[]);


/*
Description: sums the twos shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_twos(int score_card[], int frequency[]);


/*
Description: sums the threes shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_threes(int score_card[], int frequency[]);


/*
Description: sums the fours shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_fours(int score_card[], int frequency[]);


/*
Description: sums the fives shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_fives(int score_card[], int frequency[]);


/*
Description: sums the sixes shown on dice. updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: updated score card
*/
void sum_sixes(int score_card[], int frequency[]);


/*
Description: if frequency array shows 3 of a kind, updates score card with sum of all dice. Otherwise, updates it with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void three_of_a_kind(int score_card[], int frequency[]);


/*
Description: if frequency array shows 4 of a kind, updates score card with sum of all dice. Otherwise, updates it with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void four_of_a_kind(int score_card[], int frequency[]);


/*
Description: if dice contain 3 of a kind and a pair, updates score card with 25 for full house. Otherwise, updates with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void full_house(int score_card[], int frequency[]);


/*
Description: if there is a sequence of 4 numbers in the dice, updates score card with 30 for small straight. Otherwise, updates with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void small_straight(int score_card[], int frequency[]);


/*
Description: if there is a sequence of 5 numbers in the dice, updates score card with 40 for small straight. Otherwise, updates with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void large_straight(int score_card[], int frequency[]);


/*
Description: if all 5 dice are the same, updates score card with 50. if this is not the first Yahtzee, adds 100 to previous Yahtzee box score. if not a Yahtzee, then updates with 0
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array,
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void yahtzee(int score_card[], int frequency[]);


/*
Description: adds up sum of all dice and updates score card
Date Created: 10/19/2019
Date Modified: 10/20/2019
Parameter Type: int array, int array
Return Type: void
Preconditions: none
Postconditions: score card updated
*/
void chance(int score_card[], int frequency[]);
