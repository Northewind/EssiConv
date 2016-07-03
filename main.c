#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "nan.h"


static int issign(char c)
{
	return c == '+' || c == '-';
}


static char* read_coord(char *s, double *ans)
{
	char *start_idx, *numstr;
	int sz;
	*ans = strtod(s, &start_idx);
	return start_idx;
	if (issign(*s) || isdigit(*s)) {
		start_idx = s++;
		while (isdigit(*s)) s++;
		if (*s == '.') s++;
		while (isdigit(*s)) s++;
		if (start_idx == s-1) {
			puts("syntax error");
			exit(EX_SYNTAX);
		}
		/*sz = s - start_idx + 1;
		numstr = malloc(sz);
		if (!numstr) exit(EX_NOMEM);
		memcpy(numstr, start_idx, sz);
		numstr[sz-1] = '\0';*/
		*ans = atof(numstr);
		puts("double detected");
	} else {
		*ans = nan();
	}
	return s;
}


/** Generate movement */
static void gen_mov(char *s)
{
	double coord;
	char *s_next = s;
	do {
		s = s_next;
		s_next = read_coord(s, &coord);
		printf("%g ", coord);
	} while (s != s_next);
	puts("");
}


/** Process any string in ESSI program */
static void str_proc(char *s)
{
	if (s[0] == '%') {
		return;
	} else if (s[0] == '+' || s[0] == '-') {
		gen_mov(s);
	}
}


int main (int argc, char* argv[])
{
	char s[STR_SZ];
	while (!feof(stdin)) {
		fgets(s, STR_SZ, stdin);
		str_proc(s);
	}
	return EX_NORM;
}

