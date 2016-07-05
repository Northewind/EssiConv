#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "err.h"


static void lineto(double x, double y)
{
	printf("G1 ");
	printf("X%g Y%g\n", x, y);
}


static void arcCW(double x, double y, double i, double j)
{
	printf("G2 ");
	printf("X%g Y%g I%g J%g\n", x, y, i, j);
}


static void arcCCW(double x, double y, double i, double j)
{
	printf("G3 ");
	printf("X%g Y%g I%g J%g\n", x, y, i, j);
}


int mv_prs(char *s)
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
		lineto(coords[0], coords[1]);
		return 1;
	case 4:
		if (*s == '+') {
			arcCW(coords[0], coords[1], coords[2], coords[3]);
			return 2;
		} else if (*s == '-') {
			arcCCW(coords[0], coords[1], coords[2], coords[3]);
			return 3;
		}
	default:
		err_proc(ER_SYNTAX);
	}
}

