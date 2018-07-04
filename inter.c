#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inter.h"
#include "inter-even.h"
#include "items.h"
#include "rooms.h"
static void one_word(int room, char *word);
static void two_words(int room, char *words[4]);
static void three_words(int room, char *words[4]);
static void four_words(int room, char *words[4]);
static void interact(int room, int item1, int item2);

/* use item function
 *	This is a disgusting function to read, because of the large number
 *	of possible ways a user can input a use command. I have split it up
 *	into chunks to make it slightly more readable.
 */
extern void use(char *input[8])
{
	int i;
	int j;
	int room;
	char *words[4];

	putchar('\n');

	/* initialize words to null */
	for (i = 0; i < 4; i++)
		words[i] = NULL;

	/* condense input to four words at most */
	for (j = 0, i = 1; i < 8; i++) {
		if (input[i] == NULL ||
			strcmp(input[i],"on") == 0 ||
			strcmp(input[i],"the") == 0) {
			continue;
		} else {
			words[j] = input[i];
			j++;
		}
	}

	/* room id for item information */
	room = room_id();

	if (words[0] == NULL) {
		/* no words given */
		printf("Use what?\n");
		return;
	} else if (words[1] == NULL) {
		/* one word given - WORKING */
		one_word(room, words[0]);
	} else if (words[2] == NULL) {
		/* two words given - WORKING */
		two_words(room, words);
	} else if (words[3] == NULL) {
		/* three words given - WORKING */
		three_words(room, words);
	} else {
		/* four words given - WORKING */
		four_words(room, words);
	}
}

static void one_word(int room, char *word)
{
	int items[2];
	if ((items[0] = in_inv(NULL,word)) == -2 ||
		(items[1] = in_room(room,NULL,word)) == -2 ||
		(items[0] >= 0 && items[1] >= 0)) {
		printf("Use which %s?\n",word);
		return;
	} else if (items[0] == -1 && items[1] == -1) {
		printf("There is no %s here.\n",word);
		return;
	} else {
		if (items[0] == -1) items[0] = items[1];
		/****************/
		/* USE ONE ITEM */
		/****************/
		interact(room,items[0],-1);
		return;
	}
}

static void two_words(int room, char *words[4])
{
	int items[3];
	/* first item */
	if ((items[0] = in_inv(words[0],words[1])) >= 0 ||
		(items[0] = in_room(room, words[0], words[1])) >= 0) {
		/****************/
		/* USE ONE ITEM */
		/****************/
		interact(room,items[0],-1);
		return;
	} else if ((items[0] = in_inv(NULL,words[0])) == -2 ||
		(items[1] = in_room(room,NULL,words[0])) == -2 ||
		(items[0] >= 0 && items[1] >= 0)) {
		printf("Use which %s?\n",words[0]);
		return;
	} else if (items[0] == -1 && items[1] == -1) {
		printf("There is no %s here.\n",words[0]);
		return;
	} else {
		if (items[0] == -1) items[0] = items[1];
	}
	/* second item */
	if ((items[1] = in_inv(NULL,words[1])) == -2 ||
		(items[2] = in_room(room,NULL,words[1])) == -2 ||
		(items[1] >= 0 && items[2] >= 0)) {
		printf("Use which %s?\n",words[1]);
		return;
	} else if (items[1] == -1 && items[2] == -1) {
		printf("There is no %s here.\n",words[1]);
		return;
	} else {
		if (items[1] == -1) items[1] = items[2];
		/*****************/
		/* USE TWO ITEMS */
		/*****************/
		interact(room,items[0],items[1]);
		return;
	}
}

static void three_words(int room, char *words[4])
{
	int items[3];
	if ((items[0] = in_inv(NULL,words[0])) == -2 ||
		(items[1] = in_room(room,NULL,words[0])) == -2 ||
		(items[0] >= 0 && items[1] >= 0)) {
		printf("Which %s?\n",words[0]);
		return;
	} else if (items[0] == -1 && items[1] == -1) {
		if ((items[0] = in_inv(words[0],words[1])) >= 0 ||
			(items[1] = in_room(room,words[0],words[1])) >= 0) {
			/* WORDS 1 AND 2 WERE ITEM 1 */
			if (items[0] == -1) items[0] = items[1];
			if ((items[1] = in_inv(NULL,words[2])) == -2 ||
				(items[2] = in_room(room,NULL,words[2])) == -2 ||
				(items[1] >= 0 && items[2] >= 0)) {
				printf("Which %s?\n",words[2]);
				return;
			} else if (items[1] == -1 && items[2] == -1) {
				printf("There is no %s here.\n",words[2]);
				return;
			} else {
				/* WORD 3 WAS ITEM 2 */
				if (items[1] == -1) items[1] = items[2];
				interact(room,items[0],items[1]);
				return;
			}
		} else {
			printf("There is no %s here.\n",words[0]);
			return;
		}
	} else {
		/* WORD 1 WAS ITEM 1 */
		if (items[0] == -1) items[0] = items[1];
		if ((items[1] = in_inv(NULL,words[1])) == -2 ||
			(items[2] = in_room(room,NULL,words[1])) == -2 ||
			(items[1] >= 0 && items[2] >= 0)) {
			printf("Which %s?\n",words[1]);
			return;
		} else if (items[1] == -1 && items[2] == -1) {
			if ((items[1] = in_inv(words[1],words[2])) >= 0 ||
				(items[1] = in_room(room,words[1],words[2])) >=0) {
				/* WORDS 2 AND 3 WERE ITEM 2 */
				if (items[1] == -1) items[1] = items[2];
				interact(room,items[0],items[1]);
			} else {
				printf("There is no %s here.\n",words[1]);
				return;
			}
		} else {
			/* WORD 2 WAS ITEM 2 */
			if (items[1] == -1) items[1] = items[2];
			interact(room,items[0],items[1]);
			return;
		}
	}
}

static void four_words(int room, char *words[4])
{
	int items[2];
	if (!((items[0] = in_inv(words[0],words[1])) != -1 ||
		(items[0] = in_room(room,words[0],words[1])) != -1)) {
		printf("There is no %s %s here.\n",words[0],words[1]);
		return;
	} else if (!((items[1] = in_inv(words[2],words[3])) != -1 ||
		(items[1] = in_room(room,words[2],words[3])) != -1)) {
		printf("There is no %s %s here.\n",words[2],words[3]);
		return;
	} else {
		interact(room,items[0],items[1]);
		return;
	}
}

static void interact(int room, int item1, int item2)
{
	int i;
	for (i = 0; interactions[i].event_id != -1; i++) {
		if (interactions[i].room_id == room &&
			interactions[i].item1 == item1 &&
			interactions[i].item2 == item2 &&
			interactions[i].triggerable == YES) {
			/* do the action */
			if (interactions[i].event_type == OPEN) {
				location_move(interactions[i].event_attr1,
					interactions[i].event_dir,
					interactions[i].event_attr2);
			} else if (interactions[i].event_type == BREAK) {
				break_item(interactions[i].event_attr1);
			} else if (interactions[i].event_type == CREATE) {
				create_item(interactions[i].event_attr1, interactions[i].event_attr2);
			} 	

			/* print description */
			if (interactions[i].event_desc != NULL)
				printf("%s\n",interactions[i].event_desc);
			/* deactivate current event, and activate linked event if necessary */
			interactions[i].triggerable = NO;
			if (interactions[i].event_link != -1) {
				interactions[interactions[i].event_link].triggerable = YES;
			}

			/* if you don't want to chain together events, quit now */
			if (interactions[i].quit == YES) return;
		}
	}
	/* got to the end with nothing happening */
	printf("You can't do that.\n");
}
