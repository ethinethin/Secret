#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inter.h"

extern void use(char *words[8])
{
	int i;
	for (i = 0; i < 8; i++) {
		printf("%s ",*(words+i));
		putchar('\n');
	}
}