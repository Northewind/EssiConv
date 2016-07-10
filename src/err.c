#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "err.h"


int err_proc(enum err_type e)
{
	switch (e) {
	case er_syntax:
		fprintf(stderr, "Syntax error in line %d\n", line_no);
		exit(ex_syntax);
	case er_unsupport_code:
		fprintf(stderr, "Unsupported code in line %d\n", line_no);
		break;
	case er_intern:
	default:
		fputs("Internal error", stderr);
		exit(ex_intern);
	}
	return 1;
}

