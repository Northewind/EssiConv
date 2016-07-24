/**
\file
\brief internal representation of EIA program
*/
#include <stdlib.h>
#include "err.h"
#include "ir.h"


/** List data structure for blocks sequence */
struct block_list {
	struct block b;
	struct block_list *next;
};


/** Program representation */
struct ir_prog {
	struct block_list *head;
	struct block_list *current;
	struct block_list *end;
};


struct ir_prog *ir_init()
{
	struct ir_prog *res = malloc(sizeof *res);
	if (!res) err_proc(er_nomem);
	res->head = res->end = NULL;
	return res;
}


enum err_status ir_insert(struct ir_prog *p, struct block b)
{
	p->current = malloc(sizeof * p->current);
	if (! p->current) {
		err_proc(er_nomem);
	}
	p->current->b = b;
	p->current->next = NULL;
	if (p->end) {
		p->end->next = p->current;
	} else {
		p->head = p->current;
	}
	p->end = p->current;
	return er_noerr;
}


void ir_begin(struct ir_prog *p)
{
	if (p) p->current = p->head;
}


struct block ir_read(struct ir_prog *p)
{
	struct block res;
	if (! p->current) {
		res.type = bt_last_block;
	} else {
		res = p->current->b;
		p->current = p->current->next;
	}
	return res;
}


void ir_free(struct ir_prog *p)
{
	if (p) {
		while (p->head) {
			ir_begin(p);
			p->head = p->current->next;
			free(p->current);
		}
		free(p);
	}
}

