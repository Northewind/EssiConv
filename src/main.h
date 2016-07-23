/**
\file
\brief Main entry point
\copyright GNU General Public License v3
*/
#ifndef MAIN_H
#define MAIN_H


/** Termination status */
enum exit_status {
	ex_norm = 0,
	ex_syntax,
	ex_intern,
	ex_cmdline_opt
};

/** True, if command line option -t (time calc) is set */
int cmd_opt_time();

/** True, if command line option -c (commenting output) is set */
int cmd_opt_comments();


#endif

