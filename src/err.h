/**
\file
\brief Error processing unit
\copyright GNU General Public License v3
*/
#ifndef ERR_H
#define ERR_H


enum err_status {
	er_noerr = 0,
	er_syntax,
	er_intern,
	er_unsupport_code,
	er_cmdline_opt,
	er_nomem
};


void err_proc(enum err_status);


#endif

