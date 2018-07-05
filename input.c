/*
 * Copyright (c) 2018 Easter <ethinethin@gmail.com>
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise/linenoise.h"
#include "rooms.h"
#include "items.h"
#include "inter.h"
static void parse_input(char *line);
static int is_okay_quit(void);
static void completion(const char *buf, linenoiseCompletions *lc);
static void display_help(void);
static void quit_screen(void);
static void bad_ending(void);
static void good_ending(void);
int GAME_STATUS;

/* main input loop */
extern void input_loop(void)
{
	char *line;

	/* Start in room 0 and show it */
	room_name();
	look_room();
	GAME_STATUS = 0;

	/* set up tab completion */
	linenoiseSetCompletionCallback(completion);

	/* main input loop */
	while(putchar('\n') && (line = linenoise("command> ")) != NULL) {
		if (line[0] != '\0') {
			linenoiseHistoryAdd(line);
			parse_input(line);
			if (GAME_STATUS == -1) {
				quit_screen();
				break;
			} else if (GAME_STATUS == -2) {
				bad_ending();
				break;
			} else if (GAME_STATUS == -3) {
				good_ending();
				break;
			}
		}
		free(line);
	}
}

/* parse input and direct commands */
static void parse_input(char *line)
{
	int i;
	char allwords[100];
	char *words[8];

	/* copy the line and convert to lowercase */
	for (i = 0; i < 99 && line[i] != '\0'; i++) {
		allwords[i] = line[i];
		if (allwords[i] >= 'A' && allwords[i] <= 'Z')
			allwords[i] = allwords[i] + 'a' - 'A';
	}
	allwords[i] = '\0';

	/* split the line into separate words */
	*words = strtok(allwords, " \n");
	for(i = 1; i < 8; i++)
		*(words+i) = strtok(NULL, " \n");

	/* parse input */
	if (*words == NULL) {
		return;
	}
	
	/* user quit */
	else if (strcmp(*words,"quit") == 0 || strcmp(*words,"exit") == 0 || strcmp(*words,"q") == 0) {
		if (is_okay_quit()) GAME_STATUS = -1;
	}

	/* user help */
	else if (strcmp(*words, "help") == 0 || strcmp(*words, "h") == 0) {
		display_help();
	}

	/* look at room */
	else if (strcmp(*words, "look") == 0 && *(words+1) == NULL) {
		look_room();
	}

	/* move */
	else if (strcmp(*words, "go") == 0 || strcmp(*words, "walk") == 0 || strcmp(*words, "move") == 0) {
		move(*(words+1));
	} else if (strcmp(*words, "north") == 0 || strcmp(*words, "east") == 0 || strcmp(*words, "south") == 0 ||
		strcmp(*words, "west") == 0) {
		move(*words);
	} else if (strcmp(*words, "n") == 0) {
		move("north");
	} else if (strcmp(*words, "e") == 0) {
		move("east");
	} else if (strcmp(*words, "s") == 0) {
		move("south");
	} else if (strcmp(*words, "w") == 0) {
		move("west");
	}

	/* item functions */
	else if (strcmp(*words,"take") == 0 || strcmp(*words,"get") == 0) {
		if (*(words+1) != NULL && strcmp(*(words+1),"the") == 0) {
			take_item(room_id(), *(words+2), *(words+3));
		} else {
			take_item(room_id(), *(words+1), *(words+2));
		}
	} else if (strcmp(*words,"drop") == 0) {
		if (*(words+1) != NULL && strcmp(*(words+1),"the") == 0) {
			drop_item(room_id(), *(words+2), *(words+3));
		} else {
			drop_item(room_id(), *(words+1), *(words+2));
		}
	} else if (strcmp(*words,"search") == 0 || strcmp(*words,"find") == 0) {
		search(room_id());
	} else if (strcmp(*words,"i") == 0 || strcmp(*words,"inventory") == 0 || strcmp(*words,"inv") == 0) {
		list_inv();
	} else if (strcmp(*words,"look") == 0) {
		if (strcmp(*(words+1),"at") == 0) {
			if (*(words+2) != NULL && strcmp(*(words+2),"the") == 0) {
				look_item(room_id(), *(words+3), *(words+4));
			} else {
				look_item(room_id(), *(words+2), *(words+3));
			}
		} else {
			look_item(room_id(), *(words+1), *(words+2));
		}
	}

	/* interactions */
	else if (strcmp(*words,"use") == 0) {
		use(words);
	}

	/* unknown command given */
	else {
		printf("\nUnknown command '%s",*words);
		for (i = 1; i < 4; i++) {
			if (*(words+i) != NULL) printf(" %s",*(words+i));
		}
		printf("'.\n");
	}
}

static int is_okay_quit(void)
{
	int c;
	int d;

	printf("\nReally quit? (y/n) ");

	/* get input until user hits enter or EOF; only capture 1st char entered */
	d = getchar();
	while ((c = getchar()) != EOF && c != '\n');

	/* if last character was not \n, new line needs to be output */
	/* also necessary to clearerr here so quit can be called again - only seems
	 * to happen in FreeBSD, both with clang and gcc */
	if (c == EOF) {
		putchar('\n');
		clearerr(stdin);
	}

	/* if they entered 'y', quit */
	return d == 'y' || d == 'Y';

}


/* tab completion */
void completion(const char *buf, linenoiseCompletions *lc) {
	if (buf[0] == 'w') {
		linenoiseAddCompletion(lc,"walk ");
		linenoiseAddCompletion(lc,"west");
	} else if (buf[0] == 'g') {
		linenoiseAddCompletion(lc,"go ");
		linenoiseAddCompletion(lc,"get ");
	} else if (buf[0] == 'm') {
		linenoiseAddCompletion(lc,"move ");
	} else if (buf[0] == 'n') {
		linenoiseAddCompletion(lc,"north");
	} else if (buf[0] == 's') {
		linenoiseAddCompletion(lc,"south");
		linenoiseAddCompletion(lc,"search");
	} else if (buf[0] == 'l') {
		linenoiseAddCompletion(lc,"look");
	} else if (buf[0] == 't') {
		linenoiseAddCompletion(lc,"take ");
	} else if (buf[0] == 'd') {
		linenoiseAddCompletion(lc,"drop ");
	} else if (buf[0] == 'i') {
		linenoiseAddCompletion(lc,"inventory");
	} else if (buf[0] == 'u') {
		linenoiseAddCompletion(lc,"use ");
	} else if (buf[0] == 'q') {
		linenoiseAddCompletion(lc,"quit");
	} else if (buf[0] == 'h') {
		linenoiseAddCompletion(lc,"help");
	} else if (buf[0] == 'e') {
		linenoiseAddCompletion(lc,"exit");
		linenoiseAddCompletion(lc,"east");
	} else if (buf[0] == 'f') {
		linenoiseAddCompletion(lc,"find");
	}
}

static void display_help(void)
{
	printf("\n--------------------------------------------------------------------------------\n");
	printf("HOW TO PLAY\n");
	printf("\tExplore the world and solve the mystery of the forest!\n");
	printf("\tTo perform an action, use the following commands:\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("NAVIGATING THE WORLD\n");
	printf("\twalk direction (or just direction) - move in the direction specified\n");
	printf("\tlook - examine your surroundings\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("MANAGING ITEMS\n");
	printf("\tinventory - list your belongings\n");
	printf("\ttake - pick up an item\n");
	printf("\tdrop - drop an item\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("INTERACTING WITH THE WORLD\n");
	printf("\tsearch - look for hidden objects\n");
	printf("\tuse - use an item or items\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("TO QUIT\n");
	printf("\tquit - give up in your search and go home\n");
	printf("--------------------------------------------------------------------------------\n");
}

/* Displayed upon exiting the game */
static void quit_screen(void)
{
	printf("\n--------------------------------------------------------------------------------\n");
	printf("GAME OVER: The mystery of the forest remains unsolved!\n");
	printf("--------------------------------------------------------------------------------\n\n");
}

/* bad ending */
static void bad_ending(void)
{
	printf("\n--------------------------------------------------------------------------------\n");
	printf("YOU GOT THE BAD ENDING\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("How could you have known you were going to release an ancient horror upon the\n");
	printf("people of the world? Nobody can really blame you, but as the giant statue\n");
	printf("rampages across the world, killing all who oppose him, subjugating everyone\n");
	printf("else, you are trapped in the Hidden Temple with no way out.\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("GAME OVER: BETTER LUCK NEXT TIME!\n");
	printf("--------------------------------------------------------------------------------\n\n");
}

/* good ending */
static void good_ending(void)
{
	printf("\n--------------------------------------------------------------------------------\n");
	printf("YOU GOT THE GOOD ENDING\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("You have solved the secret of the Hidden Temple! By destroying the giant statue,\n");
	printf("you have uncovered a cache of riches beyond your wildest dreams! What will you\n");
	printf("do with your newfound wealth? Become a king? Become a god? The choice is up to\n");
	printf("you! But first, you need to find a cart...\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("CONGRATULATIONS!\n");
	printf("--------------------------------------------------------------------------------\n\n");
}
