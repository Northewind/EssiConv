#ifndef ERR_H
#define ERR_H


enum err_type {
	ER_SYNTAX,
	ER_INTERNAL,
	ER_UNSUPPORTED_CODE
};


void err_proc(enum err_type);


#endif /* ERR_H */
