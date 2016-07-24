/**
\file
\brief Error processing unit
\copyright GNU General Public License v3
*/
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "err.h"


void err_proc(enum err_status e)
{
	switch (e) {
	case er_noerr:
		break;
	case er_syntax:
		fprintf(stderr, "Syntax error in line %d\n", prs_lineno());
		exit(er_syntax);
	case er_unsupport_code:
		fprintf(stderr, "Unsupported code in line %d\n", prs_lineno());
		break;
	case er_cmdline_opt:
		fputs("Unknown command line option", stderr);
		exit(er_cmdline_opt);
	case er_nomem:
		fputs("Not enough memory", stderr);
		exit(er_nomem);
	case er_intern:
	default:
		fputs("Internal error", stderr);
		exit(er_intern);
	}
}

