#ifdef TEST_IR

#include <assert.h>
#include "../ir.h"

int main(int argc, char *argv[])
{
	struct ir_prog *p = ir_init();
	void fill_block_seq(struct ir_prog *);
	void read_block_seq(struct ir_prog *);
	fill_block_seq(p);
	read_block_seq(p);
	ir_free(p);
	return 0;
}


void fill_block_seq(struct ir_prog *p)
{
	struct block b;
	/* 1 */
	b.type = bt_move_lin;
	b.g = 0;
	b.x = 1;
	b.y = 2;
	ir_insert(p, b);
	/* 2 */
	b.type = bt_move_lin;
	b.g = 1;
	b.x = 2.0;
	b.y = -3.0;
	ir_insert(p, b);
	/* 3 */
	b.type = bt_move_circ;
	b.g = 2;
	b.x = 3.0;
	b.y = -4.0;
	b.i = 5;
	b.j = -6.0;
	ir_insert(p, b);
	/* 4 */
	b.type = bt_gcode;
	b.g = 4;
	ir_insert(p, b);
	/* 5 */
	b.type = bt_mcode;
	b.m = 5;
	ir_insert(p, b);
	/* 6 */
	b.type = bt_feed;
	b.f = 6.0;
	ir_insert(p, b);
}


void read_block_seq(struct ir_prog *p)
{
	struct block b;
	ir_begin(p);
	/* 1 */
	b = ir_read(p);
	assert(b.type == bt_move_lin);
	assert(b.g == 0);
	assert(b.x == 1);
	assert(b.y == 2);
	/* 2 */
	b = ir_read(p);
	assert(b.type == bt_move_lin);
	assert(b.g == 1);
	assert(b.x == 2.0);
	assert(b.y == -3.0);
	/* 3 */
	b = ir_read(p);
	assert(b.type == bt_move_circ);
	assert(b.g == 2);
	assert(b.x == 3.0);
	assert(b.y == -4.0);
	assert(b.i == 5);
	assert(b.j == -6.0);
	/* 4 */
	b = ir_read(p);
	assert(b.type == bt_gcode);
	assert(b.g == 4);
	/* 5 */
	b = ir_read(p);
	assert(b.type == bt_mcode);
	assert(b.m == 5);
	/* 6 */
	b = ir_read(p);
	assert(b.type == bt_feed);
	assert(b.f == 6.0);
}

#endif

