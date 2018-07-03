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

struct item {
	const int item_id;
	const char *item_name;
	const char *item_adj;
	const char *item_desc_floor;
	const char *item_desc_exam;
	int hidden;
	int takeable;
	int location;
};

#define NO 0
#define YES 1

struct item items[] = {
	{
		0,
		"coin","blue",
		"There is a blue coin here.",
		"The coin is carved out of stone and painted blue. There is a triangle-shaped\n"
		"hole in the center of it.",
		NO,
		YES,
		5
	},
	{
		1,
		"coin","green",
		"There is a green coin here.",
		"The coin is green.",
		NO,
		YES,
		28
	},
	{
		2,
		"coin","red",
		"There is a red coin here.",
		"The coin is red.",
		YES,
		YES,
		8
	},
	{
		3,
		"statuette","gold",
		"There is a gold statuette here.",
		"The gleaming statuette looks like a regal owl.",
		NO,
		YES,
		14
	},
	{
		4,
		"sword",NULL,
		"There is a sword here.",
		"The sword is finely crafted and extra sharp.",
		NO,
		YES,
		6
	},
	{
		5,
		"hammer","old",
		"There is an old hammer here.",
		"It is an old blacksmith's hammer that has seen better days.",
		YES,
		YES,
		3
	},
	{
		6,
		"ladder","collapsible",
		"There is a collapsible ladder here.",
		"The ladder can be folded to make it easier to carry.",
		NO,
		YES,
		2
	},
	{
		7,
		"key","ancient",
		"There is an ancient key here.",
		"The ancient skeleton key is carved with intricate patterns.",
		NO,
		YES,
		19
	},
	{
		8,
		"sign","wooden",
		"There is a wooden sign near the cave entrance.",
		"The sign says 'CAREFUL: DO NOT ENTER.'",
		NO,
		NO,
		9
	},
	{
		9,
		"hamburger","gross",
		"There's a gross hamburger lying on the ground.",
		"Old and dirty, it's probably best to not eat that.",
		YES,
		YES,
		2
	},
	{
		10,
		"lever","large",
		"There is a large lever near the gate.",
		"The lever looks large, heavy, and old.",
		NO,
		NO,
		32
	},
	{
		11,
		"ladder","extended",
		"There is an extended ladder propped up against the rockslide.",
		"The ladder is secure enough to climb.",
		NO,
		NO,
		-1
	},
	{
		12,
		"gate","locked",
		"There is a locked gate blocking entrance to tower.",
		"The gate is impassable, but there is a large keyhole in it.",
		NO,
		NO,
		29
	},
	{
		13,
		"gate","locked",
		"There is a locked gate blocking entrance to the tower.",
		"The gate is impassible, but there is a large keyhole in it.",
		NO,
		NO,
		30
	},

	/* keep this last as a signal for the last item */
	{-1,NULL,NULL,NULL,NULL,-1,-1,-1}
};