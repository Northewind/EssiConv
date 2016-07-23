/**
\file
\brief Parser for ESSI CNC-programs
\copyright GNU General Public License v3
*/
#ifndef PARSE_H
#define PARSE_H

#include "main.h"


/** Current processing line number */
int prs_lineno();

/** Start reading stdin and parse it */
enum exit_status prs_start();


#endif

