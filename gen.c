#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "err.h"


/** Generate movement */
static int gen_mov(char *s)
{
	double coords[4];
	char *s_next = s;
	int i, dir=-1;
	for (i = 0; i < 4; i++) {
		s = s_next;
		coords[i] = strtod(s, &s_next)/10;
		if (s == s_next) break;
	}
	switch (i) {
	case 1:
	case 3:
		err_proc(ER_SYNTAX);
		break;
	case 2:
		printf("G1 X%g Y%g\n", coords[0], coords[1]);
		break;
	case 4:
		if (*s == '-')
			dir = 2;
		else if (*s == '+')
			dir = 3;
		else
			err_proc(ER_SYNTAX);
		printf("G%d X%g Y%g I%g J%g\n",
		       dir, coords[0], coords[1], coords[2], coords[3]);
		break;
	default:
		return 1;
	}
	return 0;
}


static void switch_code(char *s)
{
}


void gen_procstr(char *s)
{
	if (s[0] == '%') {
		return;
	} else if (s[0] == '+' || s[0] == '-') {
		gen_mov(s);
	} else if (isdigit(s[0])) {
		switch_code(s);
	} else {
		err_proc(ER_SYNTAX);
	}
}

