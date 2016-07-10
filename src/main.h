/*
 * Main entry point and parser
 */
#ifndef MAIN_H
#define MAIN_H


/** Termination status */
enum exit_status {
	ex_norm = 0,
	ex_syntax,
	ex_intern
};


/** Current processing line number */
extern int line_no;


#endif /* MAIN_H */
