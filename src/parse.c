#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "err.h"
#include "gen.h"


enum buf_sizes {
	/** Maximum ESSI-program string length */
	essi_str_max_len = 128
};


/** ESSI-program codes */
enum essi_codes {
	es_program_stop = 0,
	es_comment_start = 3,
	es_comment_end,
	es_rapid_enable,
	es_rapid_disable,
	es_cutting_on,
	es_cutting_off,
	es_marker1_enable,
	es_marker1_disable,
	es_marker_offset1_on,
	es_marker_offset1_off,
	es_marker2_enable,
	es_marker2_disable,
	es_marker_offset2_on,
	es_marker_offset2_off,

	es_kerf_comp_left=29,
	es_kerf_comp_right,
	es_kerf_comp_disable=38,
	es_feed,

	es_cutting53_on = 53,
	es_cutting54_off,
	es_func_reset = 63,
	es_program_end,

	es_mode_inc = 81,
	es_mode_abs,

	es_program_end99 = 99,

	es_marker_offset3_on = 282,
	es_marker_offset3_off,
	es_marker_offset4_on,
	es_marker_offset4_off,
	es_marker_offset5_on,
	es_marker_offset5_off,
	es_marker_offset6_on,
	es_marker_offset6_off,
	es_marker_offset7_on,
	es_marker_offset7_off,
	es_marker_offset8_on,
	es_marker_offset8_off
};


/** Check if str is comment, then print it  */
static int is_comment(char *str, enum essi_codes n)
{
	if (gen_iscomment() == on  &&  n != es_comment_end) {
		str[strlen(str)-1] = '\0';
		printf("(%s)\n", str);
		return 1;
	}
	return 0;
}


static void code(char *str)
{
	char *endptr;
	enum essi_codes n = strtol(str, &endptr, 10);
	if (is_comment(str, n)) return;
	if (str == endptr) err_proc(er_syntax);
	switch (n) {
	case es_program_stop:
		gen_program_stop();
		break;
	case es_comment_start:
		gen_comment(on);
		break;
	case es_comment_end:
		gen_comment(off);
		break;
	case es_rapid_enable:
		gen_rapid(on);
		break;
	case es_rapid_disable:
		gen_rapid(off);
		break;
	case es_cutting_on:
		gen_cutting(on);
		break;
	case es_cutting_off:
		gen_cutting(off);
		break;
	case es_marker1_enable:
		gen_marker1(on);
		break;
	case es_marker1_disable:
		gen_marker1(off);
		break;
	case es_marker_offset1_on:
		gen_marker_offset(atoi(endptr), on);
		break;
	case es_marker_offset1_off:
		gen_marker_offset(atoi(endptr), off);
		break;
	case es_marker2_enable:
		gen_marker2(on);
		break;
	case es_marker2_disable:
		gen_marker2(off);
		break;
	case es_marker_offset2_on:
		gen_marker_offset(2, on);
		break;
	case es_marker_offset2_off:
		gen_marker_offset(2, off);
		break;

	case es_kerf_comp_left:
		gen_kerf_comp_left();
		break;
	case es_kerf_comp_right:
		gen_kerf_comp_right();
		break;
	case es_kerf_comp_disable:
		gen_kerf_comp_disable();
		break;
	case es_feed:
		gen_feed(atoi(endptr)*10);
		break;

	case es_cutting53_on:
		gen_cutting(on);
		break;
	case es_cutting54_off:
		gen_cutting(off);
		break;
	case es_func_reset:
		gen_reset_func();
		break;
	case es_program_end:
		gen_program_end();
		break;
	
	case es_mode_inc:
		gen_mode_inc();
		break;
	case es_mode_abs:
		gen_mode_abs();
		break;

	case es_program_end99:
		gen_program_end();
		break;

	case es_marker_offset3_on:
		gen_marker_offset(3, on);
		break;
	case es_marker_offset3_off:
		gen_marker_offset(3, off);
		break;
	case es_marker_offset4_on:
		gen_marker_offset(4, on);
		break;
	case es_marker_offset4_off:
		gen_marker_offset(4, off);
		break;
	case es_marker_offset5_on:
		gen_marker_offset(5, on);
		break;
	case es_marker_offset5_off:
		gen_marker_offset(5, off);
		break;
	case es_marker_offset6_on:
		gen_marker_offset(6, on);
		break;
	case es_marker_offset6_off:
		gen_marker_offset(6, off);
		break;
	case es_marker_offset7_on:
		gen_marker_offset(7, on);
		break;
	case es_marker_offset7_off:
		gen_marker_offset(7, off);
		break;
	case es_marker_offset8_on:
		gen_marker_offset(8, on);
		break;
	case es_marker_offset8_off:
		gen_marker_offset(8, off);
		break;
	default:
		err_proc(er_unsupport_code);
	}
}


static int move(char *s)
{
	double coords[4];
	char *s_next = s;
	int i;
	for (i = 0; i < 4; i++) {
		s = s_next;
		coords[i] = strtod(s, &s_next)/10;
		if (s == s_next) break;
	}
	switch (i) {
	case 2:
		gen_lineto(coords[0], coords[1]);
		return 1;
	case 4:
		if (*s == '+') {
			gen_arcCW(coords[0], coords[1], coords[2], coords[3]);
			return 2;
		} else if (*s == '-') {
			gen_arcCCW(coords[0], coords[1], coords[2], coords[3]);
			return 3;
		}
	default:
		err_proc(er_syntax);
	}
	return 0;
}


static void proc_str(char *s)
{
	if (s[0] == '%') {
		puts("%\n");
	} else if (s[0] == '\n') {
		putchar('\n');
		return;
	} else if (s[0] == '+' || s[0] == '-') {
		move(s);
	} else {
		code(s);
	}
}


static int line_no = 0;


enum exit_status prs_start()
{
	char s[essi_str_max_len] = "";
	gen_init();
	while (fgets(s, essi_str_max_len, stdin)) {
		line_no++;
		proc_str(s);
	}
	return ex_norm;
}


int prs_lineno()
{
	return line_no;
}

