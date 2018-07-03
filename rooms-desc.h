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

struct room {
	const int room_id;
	const char *room_name;
	const char *room_desc;
	int walk_to[4];
	const char *walk_desc[4];
	const char *search_desc;
};

static struct room locations[] = {
	{
		0,
		"Village Entrance",
		"You stand at the entrance to a quiet village. To the north, you see a row of\n"
		"houses. To the east is a large field next to a forest.",
		{1,7,-1,-1},
		{"You walk north.","You walk east.",NULL,NULL},
		NULL
	},
	{
		1,
		"Edge of the Village",
		"You are near a row of small houses on the edge of a quiet village. More houses\n"
		"are to the north, while the village entrance is to the south.",
		{2,-1,0,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		2,
		"Quiet Neighborhood",
		"You are in a quiet, residential neighborhood. You see people lurking behind\n"
		"pulled curtains out of the corner of your eye - you're being watched. There\n"
		"is a row of trash bins near the street. The village stretches both north and\n"
		"south.",
		{3,-1,1,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		"You dig into the trash bins."
	},
	{
		3,
		"Shopping District",
		"You are outside of a row of shops. You can hear the banging of a hammer on an\n"
		"anvil from an blacksmith's shop to the east. Next to the shop is a pile of old\n"
		"metal junk. To the west is an inn called The Sleepy Woodsman.",
		{-1,6,2,4},
		{NULL,"You enter the blacksmith's shop.","You walk south.","You enter the inn."},
		"You rummage through the junk pile."
	},
	{
		4,
		"The Sleepy Woodsman",
		"The cozy inn has a welcome desk near the door. A staircase leads north to the\n"
		"rooms upstairs. The exit is to the east.",
		{5,3,-1,-1},
		{"You walk up the stairs.","You leave the inn.",NULL,NULL},
		NULL
	},
	{
		5,
		"Upstairs at the Inn",
		"You are in a hallway on the second floor of the inn. There are four rooms here.\n"
		"All the doors are currently closed. A staircase leads downstairs to the south.",
		{-1,-1,4,-1},
		{NULL,NULL,"You walk down the stairs.",NULL},
		NULL
	},
	{
		6,
		"The Blacksmith's Shop",
		"You are in a blacksmith's shop. An old blacksmith is shaping a sword on an\n"
		"anvil. There is a teenaged boy behind the counter. The exit is to the west.",
		{-1,-1,-1,3},
		{NULL,NULL,NULL,"You exit the shop."},
		"You browse around the shop, looking for merchandise."
	},
	{
		7,
		"The Field Near the Village",
		"You are in a field. There is an entrance to a village to the west. To the east\n"
		"is a path through a tall grass field that leads to a forest.",
		{-1,8,-1,0},
		{NULL,"You walk east.",NULL,"You walk west."},
		NULL
	},
	{
		8,
		"Tall Grass Field",
		"You walking on a path surrounded by dense, tall grass. There might be snakes\n"
		"lurking in the grass. A village can be seen in the distance to the west. A\n"
		"forest can be seen in the distance to the east.",
		{-1,9,-1,7},
		{NULL,"You walk east.",NULL,"You walk west."},
		"You crawl through the grass, carefully searching."

	},
	{
		9,
		"Field Near the Cave and Forest",
		"You are standing in a field. A path to the south leads into a dark cave. A path\n"
		"to the east leads to the outskirts of a forest.",
		{-1,15,10,8},
		{NULL,"You walk east.","You walk down the path into the cave.","You walk west."},
		NULL
	},
	{
		10,
		"Cave Entrance",
		"You are standing inside a dark cave. Bright light can be seen through the\n"
		"entrance to the north. The cave stretches into darkness south.",
		{9,-1,11,-1},
		{"You leave the cave.",NULL,"You walk deeper south into the cave.",NULL},
		NULL
	},
	{
		11,
		"Cave",
		"You are deep in a cave. It is dark here, but you can see light coming from the\n"
		"north. The cave stretches into darkness south.",
		{10,-1,12,-1},
		{"You walk north.",NULL,"You slowly walk deeper into the cave.",NULL},
		NULL
	},
	{
		12,
		"Cave-In",
		"You are deep in a cave.",
		{11,-1,-1,-1},
		{"You walk north.",NULL,NULL,"You walk west."},
		NULL
	},
	{
		13,
		"Cave",
		"Cave",
		{-1,12,14,-1},
		{NULL,"You walk east.","You walk south.",NULL},
		NULL
	},
	{
		14,
		"Cave",
		"Cave",
		{13,-1,-1,-1},
		{"You walk north.",NULL,NULL,NULL},
		NULL
	},
	{
		15,
		"Forest",
		"Forest",
		{16,21,-1,9},
		{"You walk north.","You walk east.",NULL,"You walk west."},
		NULL
	},
	{
		16,
		"Forest",
		"Forest",
		{17,-1,15,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		17,
		"Forest",
		"Forest",
		{18,-1,16,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		18,
		"Forest",
		"Forest",
		{19,-1,17,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		19,
		"Forest",
		"Forest",
		{20,-1,18,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		20,
		"Forest",
		"Forest",
		{-1,-1,19,-1},
		{NULL,"You climb the ladder up the rockslide.","You walk south",NULL},
		NULL
	},
	{
		21,
		"Forest",
		"Forest",
		{-1,22,-1,15},
		{NULL,"You walk east.",NULL,"You walk west."},
		NULL
	},
	{
		22,
		"Forest",
		"Forest",
		{23,-1,-1,21},
		{"You walk north.",NULL,NULL,"You walk west."},
		NULL
	},
	{
		23,
		"Forest",
		"Forest",
		{24,-1,22,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		24,
		"Forest",
		"Forest",
		{-1,25,23,-1},
		{NULL,"You walk east.","You walk south.",NULL},
		NULL
	},
	{
		25,
		"Forest",
		"Forest",
		{26,-1,-1,24},
		{"You walk north.",NULL,NULL,"You walk west."},
		NULL
	},
	{
		26,
		"Forest",
		"Forest",
		{27,-1,25,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		27,
		"Forest",
		"Forest",
		{28,-1,26,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		28,
		"Forest",
		"Forest",
		{-1,-1,27,29},
		{NULL,NULL,"You walk south.","You walk west."},
		NULL
	},
	{
		29,
		"Forest",
		"Forest",
		{-1,28,-1,-1},
		{NULL,"You walk east.",NULL,"You walk west."},
		NULL
	},
	{
		30,
		"Bluff Overlooking the Forest",
		"Forest",
		{31,-1,-1,20},
		{"You walk north.","You walk east.",NULL,
		"You try to climb down the rocky hill, but quickly lose control and slide to the\n"
		"bottom! It was a little steeper than you thought."},
		NULL
	},
	{
		31,
		"Twisting Path",
		"Twisting Path",
		{32,-1,30,-1},
		{"You walk north.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		32,
		"The Stone Gate",
		"The Stone Gate",
		{-1,-1,31,-1},
		{"You walk through the gate.",NULL,"You walk south.",NULL},
		NULL
	},
	{
		33,
		"Hidden Temple",
		"Hidden Temple",
		{-1,-1,32,-1},
		{NULL,NULL,"You exit through the gate.",NULL},
		NULL
	},
};