#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "err.h"


void err_proc(enum err_type e)
{
	switch (e) {
	case ER_SYNTAX:
		fprintf(stderr, "Syntax error in line %d\n", line_no);
		exit(EX_SYNTAX);
	default:
		break;
	}
}

