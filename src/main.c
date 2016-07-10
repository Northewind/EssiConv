#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parse.h"


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
    -v    Print version information.\n");
}


static void version()
{
	puts("essi2eia v0.1b\n");
	puts("Copyright (C) 2016 Alexander Loshkin");
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
	for (i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-c", cmd_line_arg_max_length) == 0) {
			opt_comments = 1;
		}
		if (strncmp(argv[i], "-t", cmd_line_arg_max_length) == 0) {
			opt_time = 1;
		}
		if (strncmp(argv[i], "-h", cmd_line_arg_max_length) == 0) {
			help();
			return ex_norm;
		}
		if (strncmp(argv[i], "-v", cmd_line_arg_max_length) == 0) {
			version();
			return ex_norm;
		}
	}
	return prs_start();
}

