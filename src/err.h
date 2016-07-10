/*
 * Error processing unit
 */
#ifndef ERR_H
#define ERR_H


enum err_type {
	er_syntax = 1,
	er_intern,
	er_unsupport_code
};


int err_proc(enum err_type);


#endif /* ERR_H */
