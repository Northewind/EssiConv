#include <stdio.h>
#include "main.h"
#include "move.h"
#include "err.h"
#include "switch.h"


int line_no = 0;


static void proc_str(char *s)
{
	if (s[0] == '%') {
		return;
	} else if (s[0] == '\n') {
		return;
	} else if (s[0] == '+' || s[0] == '-') {
		mv_prs(s);
	} else if (isdigit(s[0])) {		
		sw_prs(s);
	} else if (sw_comment(s)) {
		return;
	} else {
		err_proc(ER_SYNTAX);
	}
}


int main (int argc, char* argv[])
{
	char s[STR_SZ];
	while (!feof(stdin)) {
		line_no++;
		fgets(s, STR_SZ, stdin);
		proc_str(s);
	}
	return EX_NORM;
}

