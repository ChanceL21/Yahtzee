#include "PA5.h"


void display_menu(void)
{
	printf("Welcome to Yahtzee!\n");
	printf("1. Print Game Rules\n");
	printf("2. Start a Game of Yahtzee\n");
	printf("3. Exit\n");
}

int get_option(void) // prompts for option once
{
	int option = 0;
	printf("Please enter the number corresponding with the desired action: ");
	scanf("%d", &option);
	return option;
}

int evaluate_option(int option) // makes sure option is between 1 and 3, inclusively
{
	if (option < 1 || option > 3)
	{
		printf("That's not a valid option!\n");
		return 0; // not satisfied
	}
	else
	{
		return 1; // satisfied
	}
}

int menu_select(void) // continues to display menu until option requirements are satisfied
{
	int option = 0;
	do {
		display_menu();
		option = get_option();
		system("cls");
	} while (!evaluate_option(option));
	return option;
}


void display_rules(void) // shows rules
{
	printf("\nThis is a 2 player version of the dice game Yahtzee. The goal of the game is to score the most points.\n"
		"Points are obtained by rolling five 6-sided die across thirteen rounds. During each round, each player may \n"
		"roll the dice up to three times to make one of the possible scoring combinations.\n"
		"Once a combination has been achieved by the player, it may not be used again in future rounds, \n"
		"except for the Yahtzee, which may be used as many times as the player makes the combination, and extras are worth double.\n"
		"The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section.\n"
		"The upper section has six boxes that are scored by summing the value of the dice matching the faces of the box.\n"
		"For example, if a player rolls three 2's, then the score placed in the 2's box is the sum of the dice which is 6.\n"
		"If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the player's overall score as a bonus.\n"
		"If your roll cannot satisfy any box's requirements, or you would rather give up a box, then a zero can be taken in a box or 'scratched'.\n"
		"The seven lower boxes consist of poker-based combinations as follows:\n\n"
		"Name            | Combination                    | Score\n"
		"------------------------------------------------------------------------------------\n"
		"Three of a kind | Three dice with the same face  | Sum of all face values on 5 dice\n"
		"Four of a kind  | Four dice with the same face   | Sum of all face values on 5 dice\n"
		"Full house      | One pair and a three of a kind | 25\n"
		"Small straight  | A sequence of four dice        | 30\n"
		"Large straight  | A sequence of five dice        | 40\n"
		"Yahtzee         | Five dice with the same face   | 50 for first, 100 for extras\n"
		"Chance          | Catch-all combination          | Sum of all face values on 5 dice\n\n");

}

void play_game(void)
{
	int round = 1, player_1_score = 0, player_2_score = 0;
	int player_1_scorecard[14] = { -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1 }; // both players scores initialized to -1 because this score is impossible, where 0 represents a scratch
	int player_2_scorecard[14] = { -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1 };

	while (round < 14)
	{
		system("cls");
		printf("Round %d:\n", round); // round begins
		printf("\nIt's your turn, Player 1!\n"); // player 1 takes their turn
		take_turn(player_1_scorecard);
		system("cls");
		printf("It's your turn, Player 2!\n"); // player 2 takes their turn
		take_turn(player_2_scorecard);
		round++; // next round
	}
	
	system("cls"); // clearing screen to clean up output
	printf("Game finished.\n"); 
	printf("Final results:\n");
	player_1_score = tally_score(player_1_scorecard); // displaying end results
	player_2_score = tally_score(player_2_scorecard);
	display_victor(player_1_score, player_2_score);
}

int roll_die(void)
{
	return rand() % 6 + 1; // returns random integer between 1 and 6 inclusively
}

void take_turn(int score_card[])
{
	int roll_again = 1, option = 0;
	int actual_dice[6] = { 0, 0, 0, 0, 0, 0 }; 
	int reroll[6] = { 1, 1, 1, 1, 1, 1 }; // initialized to 1, because this represents a reroll, and all the dice need to be rolled on the first roll
	int frequency[7] = { 0, 0, 0, 0, 0, 0, 0 }; // set to 0 because these will be added to based on final 5 dice

	for (int rolls = 0; roll_again == 1; rolls++)
	{
		display_score_card(score_card); // showing user score card at beginning of round and after every roll
		roll_and_print_dice(actual_dice, reroll); // updating dice based on rerolls
		roll_again = roll_again_question(rolls, reroll); // offering reroll if less than 3 rolls
		system("cls");
	}

	count_dice(actual_dice, frequency);

	display_score_card(score_card); // displaying score card for final decision
	print_dice(actual_dice);

	do {
		option = get_option();
	} while (!evaluate_score_card_option(option, score_card, frequency)); // requesting a score card option until input is valid

	calculate_score_for_option(score_card, frequency, option); // calculating score card update
	system("cls");
	display_score_card(score_card); // showing the resulting scorecard
	char character = '\0';
	printf("Press any non-whitespace character to end your turn: ");
	scanf(" %c", &character); // letting player end their turn
}

int tally_score(int score_card[]) // adding up score on card
{
	int upper_sum = 0, lower_sum = 0, bonus = 0;

	for (int i = 1; i < 7; i++) // tallying upper sum
	{
		if (score_card[i] >= 0)
		{
			upper_sum += score_card[i];
		}
	}

	if (upper_sum >= 63)
	{
		bonus = 35; // if upper sum is 63 or greater, adding 35
	}

	for (int i = 7; i < 14; i++) // tallying lower sum
	{
		if (score_card[i] >= 0)
		{
			lower_sum += score_card[i];
		}
	}

	return upper_sum + bonus + lower_sum; // adding all together and returning
}

void display_victor(int player_1_score, int player_2_score) // displaying who won, or that there was a tie, depending on scores
{
	printf("Player 1 score: %d\n", player_1_score);
	printf("Player 2 score: %d\n", player_2_score);
	if (player_1_score > player_2_score)
	{
		printf("Player 1 wins!\n\n");
	}
	else if (player_1_score < player_2_score)
	{
		printf("Player 2 wins!\n\n");
	}
	else
	{
		printf("It's a tie!\n\n");
	}
}

void roll_and_print_dice(int actual_dice[], int reroll[])
{
	char character = '\0';
	printf("Press any non-whitespace character to roll: ");
	scanf(" %c", &character); // letting character interact and roll dice

	printf("Dice values:\n");
	for (int i = 1; i < 6; i++)
	{
		if (reroll[i])
		{
			actual_dice[i] = roll_die(); //updating only rerolls
		}
		printf("The value for die %d is %d.\n", i, actual_dice[i]); // printing the new values
	}
}

void print_dice(int actual_dice[])
{
	printf("Dice values:\n");
	for (int i = 1; i < 6; i++)
	{
		printf("The value for die %d is %d.\n", i, actual_dice[i]); // printing dice values
	}
}

void count_dice(int actual_dice[], int frequency[]) // tallying up the frequency of each face number
{
	for (int i = 1; i < 6; i++)
	{
		frequency[actual_dice[i]] += 1;
	}
}

int roll_again_question(int rolls, int reroll[])
{
	int roll_again = 0;
	char yes_no_dice = '\0';
	if (rolls < 2) // if more rolls are available
	{
		do {
			printf("Would you like to roll again? input 'y' for yes or 'n' for no: "); // asks user if they want to roll again. continuously prompts until yes or no
			scanf(" %c", &yes_no_dice);
		} while (yes_no_dice != 'y' && yes_no_dice != 'n');

		if (yes_no_dice == 'y')
		{
			for (int i = 1; i < 6; i++)
			{
				char yes_no_die = '\0';
				do {
					printf("Would you like to reroll die %d? input 'y' for yes or 'n' for no: ", i); // asks which dice specifically should be rerolled
					scanf(" %c", &yes_no_die);
				} while (yes_no_die != 'y' && yes_no_die != 'n');

				if (yes_no_die == 'n')
				{
					reroll[i] = 0; // changes reroll values to 0 for certain dice if they should be kept
				}
			}

			roll_again = 1;
		}
	}

	return roll_again; // returns 1 if the user wants another roll, 0 otherwise
}

void calculate_score_for_option(int score_card[], int frequency[], int option) // switch statement to channel to proper function to calculate score and update the score card
{
	switch (option)
	{
	case 1:
		sum_ones(score_card, frequency);
		break;
	case 2:
		sum_twos(score_card, frequency);
		break;
	case 3:
		sum_threes(score_card, frequency);
		break;
	case 4:
		sum_fours(score_card, frequency);
		break;
	case 5:
		sum_fives(score_card, frequency);
		break;
	case 6:
		sum_sixes(score_card, frequency);
		break;
	case 7:
		three_of_a_kind(score_card, frequency);
		break;
	case 8:
		four_of_a_kind(score_card, frequency);
		break;
	case 9:
		full_house(score_card, frequency);
		break;
	case 10:
		small_straight(score_card, frequency);
		break;
	case 11:
		large_straight(score_card, frequency);
		break;
	case 12:
		yahtzee(score_card, frequency);
		break;
	case 13:
		chance(score_card, frequency);
		break;
	}
}

void display_score_card(int score_card[]) // displays the score card. the box titles are kept in an array of strings that parallels the score card array, so that they both can be accessed in a single i for loop
{
	char slot_names[14][18] = { "0th slot", " Sum of 1's      ", " Sum of 2's      ", " Sum of 3's      ",  " Sum of 4's      ",  " Sum of 5's      ",  " Sum of 6's      ", " Three of a kind ", " Four of a kind  ", " Full House      ", "Small straight  ", "Large straight  ", "Yahtzee         ", "Chance          " };

	printf("\nYour Score Card:\n");
	printf(" _________________________\n");
	printf("|*************************|\n");
	printf("|         YAHTZEE         |\n");
	printf("|*************************|\n");
	for (int i = 1; i < 14; i++)
	{
		printf("| %d: %s:", i, slot_names[i]);
		if (score_card[i] < 10)
		{
			printf(" "); // adding a space for smaller digits so that the score card looks nice
		}
		if (score_card[i] < 100)
		{
			printf(" ");
		}
		if (score_card[i] >= 0) // only displays the score if it is 0 or greater, otherwise it will show a -1 for unused slots instead of being empty
		{
			printf("%d", score_card[i]);
		}
		else
		{
			printf(" ");
		}
		printf("|\n");
	}
	printf("|_________________________|\n\n");
}

int evaluate_score_card_option(int option, int score_card[], int frequency[]) // returns 1 if option's slot can be used, and 0 if not
{
	if (option < 1 || option > 13) // return 0 if that option isn't one of the 13
	{
		printf("That is not a valid option.\n");
		return 0;
	}
	else if (option == 12) // if Yahtzee is selected
	{
		if (score_card[option] < 0)
		{
			return 1; // Yahtzee can be used if the value is -1 (hasn't been used  or scratched yet)
		}
		else if (score_card[option] == 0) // if the value is 0, it can't be used or scratched because it already has been scratched
		{
			printf("You already used that slot!\n");
			return 0;
		}
		else if (will_be_a_yahtzee(frequency)) // if the value for yahtzee is greater than 0 (so there was a previous successful Yahtzee) then you aren't allowed to scratch, but you can add bonus Yahtzees
		{
			return 1;
		}
		else
		{
			printf("You can't scratch your bonus Yahtzee slots.\n");
			return 0;
		}
	}
	else if (score_card[option] >= 0) // for every other slot, if the value is less than 0, it can be used or scratched, but otherwise it can't be used
	{
		printf("You have already used that slot!\n");
		return 0;
	}
	else
	{
		return 1;
	}
}

int will_be_a_yahtzee(int frequency[]) // returns 1 if a roll will be a Yahtzee, 0 otherwise
{
	for (int i = 1; i < 7; i++)
	{
		if (frequency[i] == 5)
		{
			return 1;
		}
	}
	return 0;
}

void sum_ones(int score_card[], int frequency[]) // summing ones
{
	score_card[1] = frequency[1] * 1;
}

void sum_twos(int score_card[], int frequency[]) // summing twos
{
	score_card[2] = frequency[2] * 2;
}

void sum_threes(int score_card[], int frequency[]) // summing threes
{
	score_card[3] = frequency[3] * 3;
}

void sum_fours(int score_card[], int frequency[]) // summing fours
{
	score_card[4] = frequency[4] * 4;
}

void sum_fives(int score_card[], int frequency[]) // summing fives
{
	score_card[5] = frequency[5] * 5;
}

void sum_sixes(int score_card[], int frequency[]) // summing sixes
{
	score_card[6] = frequency[6] * 6;
}

void three_of_a_kind(int score_card[], int frequency[]) // if there's a 3 in the frequency array, then 3 of a kind is satisfied
{
	score_card[7] = 0;
	int three = 0, sum = 0;
	for (int i = 1; i < 7; i++)
	{
		sum += frequency[i] * i;
			if (frequency[i] >= 3)
			{
				three = 1;
			}
	}
	if (three)
	{
		score_card[7] = sum;
	}
}

void four_of_a_kind(int score_card[], int frequency[]) // if there's a 4 in the frequency array, then 3 of a kind is satisfied
{
	score_card[8] = 0;
	int four = 0, sum = 0;
	for (int i = 1; i < 7; i++)
	{
		sum += frequency[i] * i;
		if (frequency[i] >= 4)
		{
			four = 1;
		}
	}
	if (four)
	{
		score_card[8] = sum;
	}
}

void full_house(int score_card[], int frequency[])
{
	score_card[9] = 0;
	int two = 0, three = 0;
	for (int i = 1; i < 7; i++)
	{
		if (frequency[i] == 2)
		{
			two = 1;
		}
		if (frequency[i] == 3)
		{
			three = 1;
		}
	}

	if (two && three) // if there is a 3 and a 2 in the frequency array, then it's a full house
	{
		score_card[9] = 25;
	}
}

void small_straight(int score_card[], int frequency[]) // if theres a sequence of 4, then there's a small straight
{
	score_card[10] = 0;
	int sequence = 0;
	for (int i = 1; i < 7; i++)
	{
		if (frequency[i] > 0) // adding number to sequence if there's at least one of that die face
		{
			sequence += 1;
			if (sequence == 4) // checking if current sequence is great enough
			{
				score_card[10] = 30; // updating score card if so
			}
		}
		else
		{
			sequence = 0; // reseting sequence to 0 if there is none of that die face
		}
	}
}

void large_straight(int score_card[], int frequency[]) // if all 5 dice are sequential, then there's a large straight
{
	score_card[11] = 0;
	int sequence = 0;
	for (int i = 1; i < 7; i++)
	{
		if (frequency[i] > 0)
		{
			sequence += 1;
			if (sequence == 5)
			{
				score_card[11] = 40;
			}
		}
		else
		{
			sequence = 0;
		}
	}
}

void yahtzee(int score_card[], int frequency[])
{
	int yahtzee_found = 0;
	for (int i = 1; i < 7; i++)
	{
		if (frequency[i] == 5)
		{
			yahtzee_found = 1;
			if (score_card[12] == -1)
			{
				score_card[12] = 50; // if first yahtzee, its worth 50
			}
			else
			{
				score_card[12] += 100; // all subsequent yahtzees are worth 100
			}
		}
	}
	if (!yahtzee_found)
	{
		score_card[12] = 0; // scratched yahtzee
	}
}

void chance(int score_card[], int frequency[])
{
	score_card[13] = 0;
	int sum = 0;
	for (int i = 1; i < 7; i++)
	{
		sum += frequency[i] * i; // multiplying frequency by index  and summing them all
	}
	score_card[13] = sum;
}

