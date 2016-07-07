#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "err.h"


int err_proc(enum err_type e)
{
	switch (e) {
	case ER_SYNTAX:
		fprintf(stderr, "Syntax error in line %d\n", line_no);
		exit(EX_SYNTAX);
	case ER_UNSUPPORTED_CODE:
		fprintf(stderr, "Unsupported code in line %d\n", line_no);
		break;
	case ER_INTERNAL:
	default:
		fputs("Internal error", stderr);
		exit(EX_INTERNAL);
	}
	return 1;
}

