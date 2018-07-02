#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inter.h"
#include "items.h"
#include "rooms.h"
static void one_word(int room, int items[2], char *word);

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
	int items[2];
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
		one_word(room, items, words[0]);
	} else if (words[2] == NULL) {
		/* two words given - UNFINISHED */
	} else if (words[3] == NULL) {
		/* three words given - UNFINISHED */
	} else {
		/* four words given - UNFINISHED */
	}
}

static void one_word(int room, int items[2], char *word)
{
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
		printf("Using #%d\n",items[0]);
		return;
	}
}