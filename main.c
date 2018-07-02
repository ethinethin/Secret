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
#include "input.h"
int main(void);
static void splash_screen(void);
static void exit_screen(void);

/* game information */
static const char *TITLE = "Secret in the Forest";
static const char *ENGINE = "nag-20180701";

/* main starting point for input loop */
int main(void)
{
	/* Welcome to the game */
	splash_screen();
	/* Go to input loop */
	input_loop();
	/* exiting */
	exit_screen();
	return 0;
}

/* Displayed upon execution of the program */
void splash_screen(void)
{
	printf("\n--------------------------------------------------------------------------------\n");
	printf("Welcome to %s (game engine %s)\n",TITLE,ENGINE);
	printf("--------------------------------------------------------------------------------\n");
	printf("What lies in the mysterious forest on the edge of a small village? Myths and\n");
	printf("legends have been told for centuries, but no-one has yet figured it out. Will\n");
	printf("you be the one to finally solve this riddle? Good luck!\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("To learn how to play, type: help\n");
	printf("--------------------------------------------------------------------------------\n");

}

/* Displayed upon exiting the game */
void exit_screen(void)
{
	printf("\nThe mystery of the forest remains unsolved!\n\n");
}