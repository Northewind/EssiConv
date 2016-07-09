#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen.h"
#include "err.h"


enum moves { /* Moving types: G1/G2/G3/unknown */
	m_straight,
	m_arcCW,
	m_arcCCW,
	m_unknown
};


enum enabl {
	off, on
};


enum kerf_comp { /* Kerf compensation: G40/G41/G42 */
	kc_disable,
	kc_left,
	kc_right
};


enum inc_abs { /* Incremental or absolute mode: G90/G91 */
	ia_incremental,
	ia_absolute
};


static struct state {
	enum moves move_type;
	enum enabl comment;
	enum enabl rapid;
	enum enabl cutting;
	enum enabl marker1;

	enum kerf_comp comp;

	enum inc_abs mode;
} s;




static void program_stop()
{
	puts("M0");
}

static void comment(enum enabl val)
{
	switch (s.comment = val) {
	case on:
		putchar('(');
		break;
	case off:
		gen_comment(NULL);
		puts(")");
		break;
	}
}

static void rapid(enum enabl val)
{
	switch (s.rapid = val) {
	case on:
		s.move_type = m_straight;
		break;
	case off:
		s.move_type = m_unknown;
		break;
	}
}

static void cutting(enum enabl val)
{
	switch (s.cutting = val) {
	case on:
		puts("M7");
		break;
	case off:
		puts("M8");
		break;
	}
}

static void marker1(enum enabl val)
{
	switch (s.marker1 = val) {
	case on:
		puts("M9");
		break;
	case off:
		puts("M10");
		break;
	}
}

static void kerf_comp(enum kerf_comp val)
{
	switch (s.comp = val) {
	case kc_disable:
		puts("G40");
		break;
	case kc_left:
		puts("G41");
		break;
	case kc_right:
		puts("G42");
		break;
	}
}

static void reset_func()
{
	puts("M31");
}

static void program_end()
{
	puts("M2");
}

static void mode_inc_abs(enum inc_abs val)
{
	switch (s.mode = val) {
	case ia_incremental:
		puts("G91");
		break;
	case ia_absolute:
		puts("G90");
		break;
	}
}



void gen_init()
{	
	s.move_type = m_unknown;
	s.comment = off;
	s.rapid = off;
	s.cutting = off;
	s.marker1 = off;

	s.comp = kc_disable;

	mode_inc_abs(s.mode = ia_incremental);
}


void gen_code(char *s)
{
	int n = atoi(s);
	switch (n) {
	case 0:
		program_stop();
		break;
	case 3:
		comment(on);
		break;
	case 4:
		comment(off);
		break;
	case 5:
		rapid(on);
		break;
	case 6:
		rapid(off);
		break;
	case 7:
		cutting(on);
		break;
	case 8:
		cutting(off);
		break;
	case 9:
		marker1(on);
		break;
	case 10:
		marker1(off);
		break;

	case 29:
		kerf_comp(kc_left);
		break;
	case 30:
		kerf_comp(kc_right);
		break;
	case 38:
		kerf_comp(kc_disable);
		break;

	case 63:
		reset_func();
		break;
	case 64:
		program_end();
		break;
	
	case 81:
		mode_inc_abs(ia_incremental);
		break;
	case 82:
		mode_inc_abs(ia_absolute);
		break;

	case 99:
		program_end();
		break;

	case 292:
		break;
	case 293:
		break;
	default:
		err_proc(ER_UNSUPPORTED_CODE);
	}
}


void gen_lineto(double x, double y)
{
	s.move_type = m_straight;
	if (s.rapid) {
		printf("G0 ");
	} else {
		printf("G1 ");
	}
	printf("X%g Y%g\n", x, y);
}


void gen_arcCW(double x, double y, double i, double j)
{
	s.move_type = m_arcCW;
	s.rapid = 0;
	printf("G2 X%g Y%g I%g J%g\n", x, y, i, j);
}


void gen_arcCCW(double x, double y, double i, double j)
{
	s.move_type = m_arcCW;
	s.rapid = 0;
	printf("G3 X%g Y%g I%g J%g\n", x, y, i, j);
}


int gen_comment(char *str)
{
	static int first_line = 1;
	if (s.comment) {
		if (! first_line) putchar('\n');
		{ /* Remove trailing '\n' */
			int n = strlen(str);
			if (str[n-1] == '\n') str[n-1] = '\0';
		}
		printf("%s", str);
		first_line = 0;
	} else {
		first_line = 1;
	}
	return s.comment;
}

