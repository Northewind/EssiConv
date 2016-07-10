#include <stdio.h>
#include <stdlib.h>
#include "gen.h"
#include "err.h"


enum markers {
	offset_number = 8
};


/* Kerf compensation: G40/G41/G42 */
enum kerf_comp {
	kc_disable,
	kc_left,
	kc_right
};


/* Incremental or absolute mode: G90/G91 */
enum inc_abs {
	ia_absolute,
	ia_incremental
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

	gen_mode_inc();
}


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


void gen_program_stop()
{
	puts("M0");
}


void gen_comment(enum enabl val)
{
	s.comment = val;
}


enum enabl gen_iscomment()
{
	return s.comment;
}


void gen_rapid(enum enabl val)
{
	s.rapid = val;
}


void gen_cutting(enum enabl val)
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


void gen_marker1(enum enabl val)
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


void gen_marker_offset(int idx, enum enabl val)
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


void gen_marker2(enum enabl val)
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


static void comp(enum kerf_comp val)
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


void gen_kerf_comp_left()
{
	comp(kc_left);
}


void gen_kerf_comp_right()
{
	comp(kc_right);
}


void gen_kerf_comp_disable()
{
	comp(kc_disable);
}


void gen_feed(unsigned val)
{
	printf("F%u\n", val);
}


void gen_reset_func()
{
	puts("M31");
}


void gen_program_end()
{
	puts("M2");
}


static void mode(enum inc_abs val)
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


void gen_mode_inc()
{
	mode(ia_incremental);
}


void gen_mode_abs()
{
	mode(ia_absolute);
}
