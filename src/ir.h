/**
\file
\brief internal representation of EIA program
*/
#ifndef GPROG_H
#include "err.h"


/** Object for EIA program internal representation */
struct ir_prog;


enum block_type {
	bt_move_lin,     /** use fields: g, x, y  */
	bt_move_circ,    /** use fields: g, x, y, i, j */
	bt_gcode,        /** use fields: g */
	bt_mcode,        /** use fields: m */
	bt_feed,         /** use fields: f */
	bt_last_block    /** special for detecting end of block seq */
};


struct block {
	enum block_type type;
	unsigned g, m;
	double x, y, i, j, f;
};


struct ir_prog *gp_init();

/** Insert new command at the end of program */
enum err_status gp_insert(struct ir_prog *p, struct block b);

/** Seek begin of program for further reading blocks */
void gp_begin(struct ir_prog *p);

/** Read next block from current position in program*/
struct block gp_read(struct ir_prog *p);

void gp_free(struct ir_prog *p);

#endif

