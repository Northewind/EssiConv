#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "err.h"


static int is_move_line = 1;
static int is_move_arcCW = 0;
static int is_move_arcCCW = 0;

static int is_comment = 0;
static int is_rapid = 0;
static int is_cutting = 0;
static int is_marker1 = 0;


static void program_end()
{
	puts("M2");
}

static void comment_on()
{
	is_comment = 1;
	putchar('(');
}

static void comment_off()
{
	is_comment = 0;
	sw_comment(NULL);
	puts(")");
}

static void rapid_on()
{
	is_rapid = 1;
	puts("G0");
}

static void rapid_off()
{
	is_rapid = 0;
}

static void cutting_on()
{
	is_cutting = 1;
	puts("M7");
}

static void cutting_off()
{
	is_cutting = 0;
	puts("M8");
}

static void marker1_on()
{
	is_marker1 = 1;
	puts("M9");
}

static void marker1_off()
{
	is_marker1 = 0;
	puts("M10");
}

static void comp_left_on()
{
	puts("G41");
}

static void comp_right_on()
{
	puts("G42");
}

static void comp_off()
{
	puts("G40");
}

static void reset_func()
{
	puts("M31");
}


static char* rm_newline(char *s)
{
	int n = strlen(s);
	if (s[n-1] == '\n') {
		s[n-1] = '\0';
	}
	return s;
}


int sw_comment(char *s)
{
	static int first_line = 1;
	if (is_comment) {
		if (s) {
			if (! first_line) putchar('\n');
			printf("%s", rm_newline(s));
			first_line = 0;
		}
		return 1;
	} else {
		first_line = 1;
		return 0;
	}
}


void sw_code(int n)
{
	switch (n) {
	case 0:
		program_end();
		break;
	case 3:
		comment_on();
		break;
	case 4:
		comment_off();
		break;
	case 5:
		rapid_on();
		break;
	case 6:
		rapid_off();
		break;
	case 7:
		cutting_on();
		break;
	case 8:
		cutting_off();
		break;
	case 9:
		marker1_on();
		break;
	case 10:
		marker1_off();
		break;

	case 29:
		comp_left_on();
		break;
	case 30:
		comp_right_on();
		break;
	case 38:
		comp_off();
		break;

	case 63:
		reset_func();
		break;

	case 292:
		break;
	case 293:
		break;
	default:
		err_proc(ER_UNSUPPORTED_CODE);
	}
}

void sw_prs(char *s)
{
	sw_code(atoi(s));
}

