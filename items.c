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
#include "items.h"
#include "items-desc.h"
#include "rooms.h"
static void assign_name(char **word1, char **word2, char **adj, char **name);

/* display items in room */
extern void room_items(int room_id)
{
	int i;
	for(i = 0; items[i].item_id != -1; i++) {
		if (items[i].location == room_id && items[i].hidden == NO)
			printf("%s\n",items[i].item_desc_floor);
	}
}

/* function for item grammar */
static void assign_name(char **word1, char **word2, char **adj, char **name)
{
	if (*word2 == NULL) {
		*adj = NULL;
		*name = *word1;
	} else {
		*adj = *word1;
		*name = *word2;
	}
}

/* search for hidden items */
extern void search(int room_id)
{
	int i;
	int count;

	putchar('\n');

	if (search_desc())
		printf("You carefully search the area. ");

	for (count = 0, i = 0; items[i].item_id != -1; i++) {
		if (items[i].location == room_id && items[i].hidden == YES) {
			if (count > 0)
				printf("You also found the ");
			else
				printf("You found the ");
			count++;
			if (items[i].item_adj != NULL)
				printf("%s ",items[i].item_adj);
			printf("%s! ",items[i].item_name);
			items[i].hidden = NO;
		}
	}
	if (count == 0)
		printf("You didn't find anything.\n");
	else
		putchar('\n');
}

/* inventory stuff */
static char inventory[100] = {NO};

/* display items in inventory */
extern void list_inv(void)
{
	int i;
	int count;

	printf("\nInventory:\n");
	for (count = 0, i = 0; items[i].item_id != -1; i++) {
		if (inventory[i] == YES) {
			count++;
			putchar('\t');
			if (items[i].item_adj != NULL)
				printf("%s ",items[i].item_adj);
			printf("%s\n",items[i].item_name);
		}
	}
	if (count == 0)
		printf("\tnothing.\n");
}

/* in inventory */
extern int in_room(int room_id, char *adj, char *name)
{
	int i;
	int item_num;
	int count;

	/* find out if given name is ambiguous */
	for (count = 0, i = 0; items[i].item_id != -1; i++) {
		if (strcmp(items[i].item_name,name) == 0 &&
			items[i].location == room_id && items[i].hidden == NO) {
			if (adj == NULL) {
				count++;
				item_num = i;
			} else if (items[i].item_adj != NULL &&
					strcmp(adj,items[i].item_adj) == 0) {
				count = 1;
				item_num = i;
				break;
			}
		}
	}

	/* return results */
	if (count == 0) {
		return -1;
	} else if (count > 1) {
		return -2;
	} else {
		return item_num;
	}
}

/* pick up item */
extern void take_item(int room_id, char *word1, char *word2)
{
	char *adj;
	char *name;
	int item_num;

	putchar('\n');

	if (word1 == NULL) {
		printf("Take what?\n");
		return;
	}
	
	/* assign an adjective if possible */
	assign_name(&word1, &word2, &adj, &name);
		
	/* find out if given name is ambiguous */
	item_num = in_room(room_id, adj, name);
	
	/* if none were found, the item is not present */
	/* if only one was found, it's not ambiguous */
	if (item_num == -1) {
		printf("There is no ");
		if (adj != NULL) printf("%s ",adj);
		printf("%s here.\n",name);
		return;
	} else if (item_num == -2) {
		printf("Which %s do you want to take?\n",name);
		return;
	}

	/* take item if possible */
	if (items[item_num].takeable == YES) {
		items[item_num].location = -1;
		inventory[item_num] = 1;
		printf("You took the ");
		if (items[item_num].item_adj != NULL)
			printf("%s ",items[item_num].item_adj);
		printf("%s.\n",name);
	} else {
		printf("You cannot take the %s!\n",name);
	}
}

extern int in_inv(char *adj, char *name)
{
	int i;
	int item_num;
	int count;
	
	/* find out if given name is ambiguous */
	for (count = 0, i = 0; items[i].item_id != -1; i++) {
		if (strcmp(items[i].item_name,name) == 0 &&
			inventory[i] == YES) {
			if (adj == NULL) {
				count++;
				item_num = i;
			} else if (items[i].item_adj != NULL &&
				strcmp(adj,items[i].item_adj) == 0) {
				count = 1;
				item_num = i;
				break;
			}
		}
	}

	/* return results */
	if (count == 0) {
		return -1;
	} else if (count > 1) {
		return -2;
	} else {
		return item_num;
	}
}

/* drop item */
extern void drop_item(int room_id, char *word1, char *word2)
{
	char *adj = NULL;
	char *name = NULL;
	int item_num;

	putchar('\n');

	if (word1 == NULL) {
		printf("Drop what?\n");
		return;
	}
	
	/* assign an adjective if possible */
	assign_name(&word1, &word2, &adj, &name);
	
	/* find out if given name is ambiguous */
	item_num = in_inv(adj, name);

	/* if none were found, the item is not in inventory */
	/* if only one was found, it's not ambiguous */
	if (item_num == -1) {
		printf("You do not have a ");
		if (adj != NULL) printf("%s ",adj);
		printf("%s.\n",name);
		return;
	} else if (item_num == -2) {
		printf("Which %s do you want to drop?\n",name);
		return;
	}

	/* drop item */
	items[item_num].location = room_id;
	inventory[item_num] = NO;
	printf("You dropped the ");
	if (items[item_num].item_adj != NULL)
		printf("%s ",items[item_num].item_adj);
	printf("%s.\n",name);
}

/* item in inventory? */
extern void look_item(int room_id, char *word1, char *word2)
{
	char *adj = NULL;
	char *name = NULL;
	int item_num1;
	int item_num2;

	putchar('\n');

	if (word1 == NULL) {
		printf("Look at what?\n");
		return;
	}
	
	/* assign an adjective if possible */
	assign_name(&word1, &word2, &adj, &name);

	/* in location or inventory? */
	item_num1 = in_room(room_id, adj, name);
	item_num2 = in_inv(adj, name);

	/* is it ambiguous? */
	if (item_num1 == -2 || item_num2 == -2 || (item_num1 >= 0 && item_num2 >= 0)) {
		printf("Which %s?\n",name);
		return;
	} else if (item_num1 == -1 && item_num2 == -1) {
		printf("There is no ");
		if (adj != NULL) printf("%s ",adj);
		printf("%s here.\n",name);
		return;
	} else if (item_num1 == -1) {
		item_num1 = item_num2;
	}

	printf("%s\n",items[item_num1].item_desc_exam);
}

extern void break_item(int item_id)
{
	inventory[item_id] = 0;
	items[item_id].location = -1;
}


extern void create_item(int item_id, int room_id)
{
	items[item_id].location = room_id;
}
