#ifndef MAIN_H
#define MAIN_H


/** Maximum ESSI-program string length */
#define STR_SZ 128

enum exit_status {
	EX_NORM = 0,
	EX_NOMEMORY,
	EX_SYNTAX,
	EX_INTERNAL
};

/** Current processing line number */
extern int line_no;


#endif /* MAIN_H */
