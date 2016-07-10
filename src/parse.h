/*
 * Parser for ESSI CNC-programs
 */
#ifndef PARSE_H
#define PARSE_H

#include "main.h"


/** Current processing line number */
int prs_lineno();

/** Start reading stdin and parse it */
enum exit_status prs_start();


#endif /* PARSE_H */
