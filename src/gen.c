/**
\file
\brief G-code generation unit in automatum style
\copyright GNU General Public License v3
*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
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


enum buf_sizes {
	max_block_str_len = 64,
	max_block_comment_len = 128
};


enum speed {
	speed_rapid = 1000
};


static struct state {
	double time;
	double x, y;
	enum enabl comment;
	enum enabl rapid;
	enum enabl cutting;
	enum enabl marker1;
	enum enabl marker_offset[offset_number];
	enum enabl marker2;

	enum kerf_comp comp;
	unsigned feed;

	enum inc_abs mode;
} s;


void gen_init()
{
	s.time = 0.0;
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
	s.feed = 0;
	
	s.mode = ia_incremental;
}


/** Print G-code and optional comment */
static void print(char *x, char *y)
{
	fputs(x, stdout);
	if (cmd_opt_comments())
		printf("\t\t(%s)", y);
	putchar('\n');
}


/** Set x,y */
static void move_xy(double x, double y)
{
	switch (s.mode) {
	case ia_absolute:
		s.x = x;
		s.y = y;
		break;
	case ia_incremental:
		s.x += x;
		s.y += y;
		break;
	}
}


/** Linear interpolation generation */
void gen_lineto(double x, double y)
{
	char block_str[max_block_str_len];
	move_xy(x, y);
	if (s.rapid) {
		printf("G0 ");
	} else {
		printf("G1 ");
	}
	sprintf(block_str, "X%g Y%g", x, y);
	print(block_str, "linear interpolation");
}


/** Make I & J always incremental in G-code */
static void incIJ(double *i, double *j)
{
	if (s.mode == ia_absolute) {
		*i = *i - s.x;
		*j = *j - s.y;
	}
}


void gen_arcCW(double x, double y, double i, double j)
{
	char block_str[max_block_str_len];
	incIJ(&i, &j);
	move_xy(x, y);
	s.rapid = 0;
	sprintf(block_str, "G2 X%g Y%g I%g J%g", x, y, i, j);
	print(block_str, "circular clockwise interpolation");
}


void gen_arcCCW(double x, double y, double i, double j)
{
	char block_str[max_block_str_len];
	incIJ(&i, &j);
	move_xy(x, y);
	s.rapid = 0;
	sprintf(block_str, "G3 X%g Y%g I%g J%g", x, y, i, j);
	print(block_str, "circular counter-clockwise interpolation");
}


void gen_program_stop()
{
	print("M0", "stop");
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
		print("M7", "cutting device on");
		break;
	case off:
		print("M8", "cutting device off");
		break;
	}
}


void gen_marker1(enum enabl val)
{
	switch (s.marker1 = val) {
	case on:
		print("M9", "enable marker 1");
		break;
	case off:
		print("M10", "disable marker 1");
		break;
	}
}


void gen_marker_offset(int idx, enum enabl val)
{
	int m_on, m_off;
	char m_str[max_block_str_len], comm_str[max_block_comment_len];
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
		sprintf(m_str, "M%d", m_on);
		sprintf(comm_str, "marker offset %d on", idx);
		print(m_str, comm_str);
		break;
	case off:
		sprintf(m_str, "M%d", m_off);
		sprintf(comm_str, "marker offset %d off", idx);
		print(m_str, comm_str);
		break;
	}
}


void gen_marker2(enum enabl val)
{
	switch (s.marker2 = val) {
	case on:
		print("M13", "enable marker 2");
		break;
	case off:
		print("M14", "disable marker 2");
		break;
	}
}


static void comp(enum kerf_comp val)
{
	switch (s.comp = val) {
	case kc_disable:
		print("G40", "disable kerf");
		break;
	case kc_left:
		print("G41", "enable left kerf comp");
		break;
	case kc_right:
		print("G42", "enable right kerf comp");
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
	char block_str[max_block_str_len];
	s.feed = val;
	sprintf(block_str, "F%u", val);
	print(block_str, "machine speed");
}


void gen_reset_func()
{
	print("M31", "reset functions");
}


void gen_program_end()
{
	print("M2", "end program");
}


static void mode(enum inc_abs val)
{
	switch (s.mode = val) {
	case ia_incremental:
		print("G91", "incremental mode");
		break;
	case ia_absolute:
		print("G90", "absolute mode");
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

