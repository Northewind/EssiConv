#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "parse.h"
#include "err.h"


int err_proc(enum err_type e)
{
	switch (e) {
	case er_syntax:
		fprintf(stderr, "Syntax error in line %d\n", prs_lineno());
		exit(ex_syntax);
	case er_unsupport_code:
		fprintf(stderr, "Unsupported code in line %d\n", prs_lineno());
		break;
	case er_intern:
	default:
		fputs("Internal error", stderr);
		exit(ex_intern);
	}
	return 1;
}

