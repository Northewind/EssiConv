#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen.h"
#include "err.h"


enum enabl {
	off, on
};


enum kerf_comp { /* Kerf compensation: G40/G41/G42 */
	kc_disable,
	kc_left,
	kc_right
};


enum inc_abs { /* Incremental or absolute mode: G90/G91 */
	ia_absolute,
	ia_incremental
};


enum markers {
	offset_number = 8
};


static struct state {
	double x, y;
	enum enabl comment;
	enum enabl rapid;
	enum enabl cutting;
	enum enabl marker1;
	enum enabl marker_offset[offset_number];
	enum enabl marker2;

	enum kerf_comp comp;

	enum inc_abs mode;
} s;


static void move_xy(double x, double y)
{
	switch (s.mode) {
	case ia_absolute:
		s.x = x;
		s.y = y;
	case ia_incremental:
		s.x += x;
		s.y += y;
	}
}

static void program_stop()
{
	puts("M0");
}

static void comment(enum enabl val)
{
	s.comment = val;
}

static void rapid(enum enabl val)
{
	s.rapid = val;
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

static void marker_offset(int idx, enum enabl val)
{
	int m_on, m_off;
	if (idx == 0 || idx == 1) {
		idx = 1;
		m_on = 11;
		m_off = 12;
	} else if (idx == 2) {
		m_on = 73;
		m_off = 72;
	} else if (idx >= 3 && idx <= offset_number) {
		m_on = 275 + (idx - 3)*2;
		m_off = m_on - 1;
	}
	switch (s.marker_offset[idx-1] = val) {
	case on:
		printf("M%d\n", m_on);
		break;
	case off:
		printf("M%d\n", m_off);
		break;
	}
}

static void marker2(enum enabl val)
{
	switch (s.marker2 = val) {
	case on:
		puts("M13");
		break;
	case off:
		puts("M14");
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

static void feed(unsigned val)
{
	printf("F%u\n", val);
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
	s.x = s.y = 0.0;
	s.comment = off;
	s.rapid = off;
	s.cutting = off;
	s.marker1 = off;
	{
		int i;
		for (i = 0; i < offset_number; i++) {
			s.marker_offset[i] = off;
		}
	}
	s.marker2 = off;

	s.comp = kc_disable;

	mode_inc_abs(s.mode = ia_incremental);
}


void gen_str(char *str)
{
	char *endptr;
	int n = strtol(str, &endptr, 10);
	if (s.comment == on  &&  n != 4) {
		str[strlen(str)-1] = '\0';
		printf("(%s)\n", str);
		return;
	}
	if (str == endptr) err_proc(ER_SYNTAX);
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
	case 11:
		marker_offset(atoi(endptr), on);
		break;
	case 12:
		marker_offset(atoi(endptr), off);
		break;
	case 13:
		marker2(on);
		break;
	case 14:
		marker2(off);
		break;
	case 15:
		marker_offset(2, on);
		break;
	case 16:
		marker_offset(2, off);
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
	case 39:
		feed(atoi(endptr)*10);
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
	move_xy(x, y);
	if (s.rapid) {
		printf("G0 ");
	} else {
		printf("G1 ");
	}
	printf("X%g Y%g\n", x, y);
}


void gen_arcCW(double x, double y, double i, double j)
{
	if (s.mode == ia_absolute) {
		/* Make I & J always incremental in G-code */
		i = i - s.x;
		j = j - s.y;
	}
	move_xy(x, y);
	s.rapid = 0;
	printf("G2 X%g Y%g I%g J%g\n", x, y, i, j);
}


void gen_arcCCW(double x, double y, double i, double j)
{
	if (s.mode == ia_absolute) {
		/* Make I & J always incremental in G-code */
		i = i - s.x;
		j = j - s.y;
	}
	move_xy(x, y);
	s.rapid = 0;
	printf("G3 X%g Y%g I%g J%g\n", x, y, i, j);
}

