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

struct event {
	const int event_id;
	const int item1;
	const int item2;
	const int room_id;
	int triggerable;
	const int event_type;
	const int event_dir;
	const int event_attr1;
	const int event_attr2;
	const int event_link;
	const int quit;
	const char *event_desc;
};

#define NO 0
#define YES 1

#define OPEN 0
#define BREAK 1
#define CREATE 2

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

static struct event interactions[] = {
	/* lever to hidden temple */
	{0,10,-1,32,YES,OPEN,NORTH,32,33,1,YES,
		"The large gate rumbles loudly as it opens."},
	{1,10,-1,32,NO,OPEN,NORTH,32,-1,0,YES,
		"The large gate quickly crashes down with a clatter. The way is blocked!"},

	/* hammer breaking wall in cave */
	{2,5,-1,12,YES,BREAK,WEST,5,-1,3,NO,
		"You smash the hammer against the west wall. It opened up a path you can crawl"},
	{3,5,-1,12,NO,OPEN,WEST,12,13,-1,YES,
		"through! But the hammer is now broken and useless. You throw it away."},

	/* ladder used for climbing rockslide */
	{4,6,-1,20,YES,BREAK,EAST,6,-1,5,NO,
		"You unfold the ladder and place it on the steep rockslide to the east. It looks"},
	{5,6,-1,20,NO,CREATE,EAST,11,-1,6,NO,
		"like you can climb up it, but you give it a shake to make sure it is secure"},
	{6,6,-1,20,NO,OPEN,EAST,20,30,-1,YES,
		"enough to climb. You can now travel east!"},

	/* open gate east side */
	{7,7,12,29,YES,BREAK,WEST,7,-1,8,NO,
		"You slide the key into the keyhole in the gate. As you turn, it clicks loudly."},
	{8,7,12,29,NO,BREAK,WEST,12,-1,9,NO,
		"The gate swings open, allowing you to ascend the tower to the west!"},
	{9,7,12,29,NO,OPEN,WEST,29,30,10,NO,NULL},
	{10,7,12,29,NO,OPEN,EAST,30,29,11,NO,NULL},
	{11,7,12,29,NO,BREAK,WEST,13,-1,-1,YES,NULL},

	/* open gate west side */
	{12,7,13,30,YES,BREAK,WEST,7,-1,13,NO,
		"You slide the key into the keyhole in the gate. As you turn, it clicks loudly."},
	{13,7,13,30,NO,BREAK,WEST,13,-1,14,NO,
		"The gate swings open, allowing you to descend the tower to the east!"},
	{14,7,13,30,NO,OPEN,WEST,29,30,15,NO,NULL},
	{15,7,13,30,NO,OPEN,EAST,30,29,16,NO,NULL},
	{16,7,13,30,NO,BREAK,WEST,12,-1,-1,YES,NULL},

	/* keep this to signal no more interactions: */
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,NULL}
};
