#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "err.h"
#include "gen.h"


int line_no = 0;


static int move(char *s)
{
	double coords[4];
	char *s_next = s;
	int i;
	for (i = 0; i < 4; i++) {
		s = s_next;
		coords[i] = strtod(s, &s_next)/10;
		if (s == s_next) break;
	}
	switch (i) {
	case 2:
		gen_lineto(coords[0], coords[1]);
		return 1;
	case 4:
		if (*s == '+') {
			gen_arcCW(coords[0], coords[1], coords[2], coords[3]);
			return 2;
		} else if (*s == '-') {
			gen_arcCCW(coords[0], coords[1], coords[2], coords[3]);
			return 3;
		}
	default:
		err_proc(ER_SYNTAX);
	}
	return 0;
}


static void proc_str(char *s)
{
	if (s[0] == '%') {
		return;
	} else if (s[0] == '\n') {
		return;
	} else if (s[0] == '+' || s[0] == '-') {
		move(s);
	} else if (isdigit(s[0])) {		
		gen_code(s);
	} else if (gen_comment(s)) {
		return;
	} else {
		err_proc(ER_SYNTAX);
	}
}


int main (int argc, char* argv[])
{
	char s[STR_SZ] = "";
	gen_init();
	while (!feof(stdin)) {
		line_no++;
		fgets(s, STR_SZ, stdin);
		proc_str(s);
	}
	return EX_NORM;
}

