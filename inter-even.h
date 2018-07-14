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
#define STORY 3

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

static struct event interactions[] = {
	/* lever to hidden temple */
	{0,11,-1,32,YES,OPEN,NORTH,32,33,1,YES,
		"You put all your strength into moving the lever. It finally moves and the large\n"
		"gate clanks and rumbles loudly as it slides opens. You can now travel north!"},
	{1,11,-1,32,NO,OPEN,NORTH,32,-1,0,YES,
		"The lever is surprisingly easy to move. As soon as you touch it, the large gate\n"
		"quickly crashes down with a clatter. The way north is blocked!"},

	/* hammer breaking wall in cave */
	{2,18,-1,12,YES,BREAK,WEST,18,-1,3,NO,
		"You smash the hammer against the west wall. It opened up a path you can crawl\n"
		"through! But the hammer is now broken and useless. You throw it away."},
	{3,18,-1,12,NO,OPEN,WEST,12,13,-1,YES,NULL},

	/* ladder used for climbing rockslide */
	{4,19,-1,20,YES,BREAK,EAST,19,-1,5,NO,
		"You unfold the ladder and place it on the steep rockslide to the east. It looks\n"
		"like you can climb up it, but you give it a shake to make sure it is secure\n"
		"enough to climb. You can now travel east!"},
	{5,19,-1,20,NO,CREATE,EAST,8,20,6,NO,NULL},
	{6,19,-1,20,NO,OPEN,EAST,20,30,-1,YES,NULL},

	/* open gate east side */
	{7,20,9,29,YES,BREAK,WEST,20,-1,8,NO,
		"You slide the key into the keyhole in the gate. As you turn it, it clicks\n"
		"loudly. The gate swings open, allowing you to ascend the tower to the west!"},
	{8,20,9,29,NO,BREAK,WEST,9,-1,9,NO,NULL},
	{9,20,9,29,NO,OPEN,WEST,29,30,10,NO,NULL},
	{10,20,9,29,NO,OPEN,EAST,30,29,11,NO,NULL},
	{11,20,9,29,NO,BREAK,WEST,10,-1,-1,YES,NULL},

	/* open gate west side */
	{12,20,10,30,YES,BREAK,WEST,20,-1,13,NO,
		"You slide the key into the keyhole in the gate. As you turn it, it clicks\n"
		"loudly. The gate swings open, allowing you to ascend the tower to the east!"},
	{13,20,10,30,NO,BREAK,WEST,10,-1,14,NO,NULL},
	{14,20,10,30,NO,OPEN,WEST,29,30,15,NO,NULL},
	{15,20,10,30,NO,OPEN,EAST,30,29,16,NO,NULL},
	{16,20,10,30,NO,BREAK,WEST,9,-1,-1,YES,NULL},

	/* sword breaks statue */
	{17,17,3,24,YES,BREAK,EAST,3,-1,18,NO,
		"You swing the giant sword at the statue. As you slice the stone shield, the\n"
		"statue begins to collapse. You keep attacking it until it completely falls\n"
		"apart. As the statue lies in ruin, the path to the east is now open."},
	{18,17,3,24,NO,OPEN,EAST,24,25,-1,YES},

	/* open blue kiosk with coins */
	{19,13,4,18,YES,BREAK,NORTH,13,0,20,NO,
		"You slide the blue coin into the slot at the top of the kiosk. The kiosk slowly\n"
		"rumbles, and its inner stone workings begin to shift around. The blue pyramid\n"
		"slides away beneath a hidden compartment and a stone, green sphere shifts into\n"
		"the same position."},
	{20,13,4,18,NO,BREAK,NORTH,4,0,21,NO,NULL},
	{21,13,4,18,NO,CREATE,NORTH,5,18,-1,YES,NULL},

	/* open green kiosk with coins */
	{22,14,5,18,YES,BREAK,NORTH,14,1,23,NO,
		"You slip the green coin into the slot in the kiosk. Once again, the kiosk starts\n"
		"rumbling loudly as its inner workings come to life. The green sphere disappears\n"
		"into a hidden panel and a rectangular red stone takes its place."},
	{23,14,5,18,NO,BREAK,NORTH,5,1,24,NO,NULL},
	{24,14,5,18,NO,CREATE,NORTH,6,18,-1,YES,NULL},

	/* open red kiosk with coins */
	{25,15,6,18,YES,BREAK,NORTH,15,0,26,NO,
		"Once again, the kiosk comes to life as soon as you slide the red coin into the\n"
		"slot. As the red stone slides into the inside, you hear a haunting melody come\n"
		"from within the kiosk. As the song slowly fades away, the kiosk slides into a\n"
		"hidden panel in the stone on which it sat. The hole in the stone slab remains,\n"
		"revealing a ladder down into an underground tunnel that leads north."},
	{26,15,6,18,NO,BREAK,NORTH,6,0,27,NO,NULL},
	{27,15,6,18,NO,OPEN,NORTH,18,19,28,NO,NULL},
	{28,15,6,18,NO,CREATE,NORTH,7,18,-1,YES,NULL},

	/* buy sword with statuette */
	{29,16,0,6,YES,BREAK,EAST,16,-1,30,NO,
		"The blacksmith sees the statuette and his eyes get wide.\n\n"
		"\"Please! I must have that! Take this sword! I crafted it myself! It is the most\n"
		"finely made sword you will ever see!\"\n"},
	{30,16,0,6,NO,CREATE,EAST,17,6,31,NO,
		"You are impressed with the quality of the sword and think it is an even trade.\n"
		"The blacksmith takes the statuette and places the sword on the counter."},
	{31,16,0,6,NO,BREAK,EAST,0,6,32,NO,NULL},
	{32,16,0,6,NO,CREATE,EAST,1,6,-1,YES,NULL},
	
	/* trying to use the wrong coins */
	{33,14,4,18,YES,STORY,NORTH,0,-1,33,YES,"The green coin does not fit into the blue slot."},
	{34,15,4,18,YES,STORY,NORTH,0,-1,34,YES,"The red coin does not fit into the blue slot."},
	{35,15,5,18,YES,STORY,NORTH,0,-1,35,YES,"The red coin does not fit into the green slot."},
	
	/* attacking the blacksmith */
	{36,17,1,6,YES,STORY,EAST,0,-1,36,YES,"You shouldn't do that."},
	{37,18,0,6,YES,STORY,EAST,0,-1,37,YES,"You shouldn't do that."},

	/* bad ending - give scepter to bird-man statue */
	{38,22,12,33,YES,OPEN,SOUTH,33,-1,40,YES,
		"As you approach the bird-man statue with the scepter, you see his eyes gleam red\n"
		"for a moment - a warning? A loud crashing is heard behind you and the gate has\n"
		"closed! You are still holding the scepter... are you sure this is a good idea?"},
	{39,22,12,33,YES,STORY,SOUTH,-2,-1,-1,YES,
		"You place the scepter into the empty hand of the statue. As soon as you do, his\n"
		"eyes and the gem in the scepter gleam bright red. Supernaturally fast, he stands\n"
		"up, knocking you back.\n\n"
		"\"AT LAST, I HAVE BEEN RELEASED FROM MY SLUMBER. THE WORLD WILL NOW SUFFER. THE\n"
		"WORLD WILL NOW BE MINE!\"\n\n"
		"He walks towards the western wall and climbs over it in a quick motion, leaving\n"
		"you behind in the Hidden Temple."},

	/* good ending - use sword on bird-man statue */
	{40,17,12,33,YES,OPEN,SOUTH,33,-1,38,YES,
		"You approach the bird-man statue, brandishing the sword. His eyes gleam red for\n"
		"a moment - a warning? A loud crashing is heard behind you and the gate has\n"
		"closed! You are still holding the sword... Are you sure this is a good idea?"},
	{41,17,12,33,YES,STORY,SOUTH,-3,-1,-1,YES,
		"You raise the sword and lower it with a crash onto the statue. As you are about\n"
		"to strike, the statue supernaturally moves to defend itself, resulting in you\n"
		"accidentally striking the ruby in its right hand. Both the sword and the ruby\n"
		"explode into a million pieces!\n\n"
		"As soon as the ruby is destroyed, the statue crumbles to the floor and melts\n"
		"away before your eyes. A hidden chamber behind the throne slowly opens to reveal\n"
		"mountains of gold and treasure, and the large gate to the temple opens!"},

	/* hamburger */
	{42,21,0,6,YES,STORY,NORTH,0,-1,42,YES,"He doesn't want to eat that."},
	{43,21,1,6,YES,STORY,NORTH,0,-1,43,YES,"He doesn't want to eat that."},
	{44,21,12,33,YES,STORY,NORTH,0,-1,44,YES,"He doesn't want to eat that."},
	{45,21,3,24,YES,STORY,NORTH,0,-1,45,YES,"He doesn't want to eat that."},
	/* keep this to signal no more interactions: */
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,NULL}
};
