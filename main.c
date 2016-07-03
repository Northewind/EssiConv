#include <stdio.h>
#include "main.h"
#include "gen.h"


int line_no = 0;


int main (int argc, char* argv[])
{
	char s[STR_SZ];
	while (!feof(stdin)) {
		line_no++;
		fgets(s, STR_SZ, stdin);
		gen_procstr(s);
	}
	return EX_NORM;
}

