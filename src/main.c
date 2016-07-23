/**
\file
\brief Main entry point
\copyright GNU General Public License v3
*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parse.h"
#include "err.h"


enum {
	cmd_line_arg_max_length = 2
};


static int opt_time = 0;
static int opt_comments = 0;


int cmd_opt_time()
{
	return opt_time;
}


int cmd_opt_comments()
{
	return opt_comments;
}


static void help()
{
	puts("EssiConv - a tool for converting CNC-program\n\
from ESSI format to EIA (G-code) format.\n\
Usage:\n\
    essi2eia [options] < essi_prog > eia_prog\n\
Options:\n\
    -c    Print comment for each exporting block.\n\
    -t    Print time CNC-program execution.\n\
    -h    This help message.\n\
    -v    Version information.\n");
}


static void version()
{
	puts("essi2eia v0.1b");
	puts("Copyright (C) 2016 Alexander Loshkin <1214160@gmail.com>\n");
	puts("    This program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.");
	puts("    This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.");
	puts("    You should have received a copy of the GNU General Public License\n\
along with this program.  If not, see <http://www.gnu.org/licenses/>.");
}


int main(int argc, char* argv[])
{
	int i;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') { /* Start of command line option */
			int j;
			for (j = 1;  argv[i][j];  j++) {
				switch (argv[i][j]) {
				case 'c':
					opt_comments = 1;
					break;
				case 't':
					opt_time = 1;
					break;
				case 'h':
					help();
					return ex_norm;
				case 'v':
					version();
					return ex_norm;
				default:
					err_proc(er_cmdline_opt);
				}
			}
		} else {
			err_proc(er_cmdline_opt);
		}
	}
	return prs_start();
}

