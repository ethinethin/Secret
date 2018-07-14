#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inter.h"
#include "inter-even.h"
#include "items.h"
#include "rooms.h"
static void interact(int room, int item1, int item2);
extern int GAME_STATUS;

/* use item word parsing:
 *	I have simplified this. It's still a little gross to look at, but it
 *	should make a lot more sense now!
 */
extern void use(char *input[8])
{
	int i;
	int j;
	int room;
	int items[2];
	int cur_phrase;
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

	/* Make sure something was used */
	if (words[0] == NULL) {
		printf("Use what?\n");
		return;
	}

	/* room id for item information */
	room = room_id();

	/* process word by word */
	for (j = 0, i = 0; i < 3 && j < 2; i++) {
		if (words[i] == NULL) { 
			items[j] = -1;
			break;
		}
		if ((cur_phrase = unique_item(room, NULL, words[i])) == -2) {
			printf("Which %s?\n",words[i]);
			return;
		} else if (cur_phrase == -1) {
			if ((cur_phrase = unique_item(room, words[i], words[i+1])) == -1) {
				printf("There is no %s here.\n",words[i]);
				return;
			}
			i++;
		}
		items[j++] = cur_phrase;
	}

	/* parsed items, now use them */
	interact(room, items[0], items[1]);
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
			} else if (interactions[i].event_type == STORY) {
				GAME_STATUS = interactions[i].event_attr1;
			}

			/* print description */
			if (interactions[i].event_desc != NULL)
				printf("%s\n",interactions[i].event_desc);
			/* deactivate current event, and activate linked event if necessary */
			interactions[i].triggerable = NO;
			if (interactions[i].event_link != -1) {
				if (interactions[interactions[i].event_link].triggerable == YES)
					interactions[interactions[i].event_link].triggerable = NO;
				else
					interactions[interactions[i].event_link].triggerable = YES;
			}

			/* if you don't want to chain together events, quit now */
			if (interactions[i].quit == YES) return;
		}
	}
	/* got to the end with nothing happening */
	printf("You can't do that.\n");
}
