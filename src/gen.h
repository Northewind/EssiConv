/*
 * G-code generation unit in automatum style
 */
#ifndef GEN__H
#define GEN__H


/* Enable of disable any function*/
enum enabl {
	off, on
};

/** Initialize automaton state */
void gen_init();

/** Print current state */
void gen_print_state();

/** Generate straight movement */
void gen_lineto(double x, double y);

/** Generate clockwise arc  movement */
void gen_arcCW(double x, double y, double i, double j);

/** Generate counter-clockwise arc  movement */
void gen_arcCCW(double x, double y, double i, double j);

void gen_program_stop();

void gen_comment(enum enabl val);

enum enabl gen_iscomment();

void gen_rapid(enum enabl val);

void gen_cutting(enum enabl val);

void gen_marker1(enum enabl val);

void gen_marker_offset(int idx, enum enabl val);

void gen_marker2(enum enabl val);

void gen_kerf_comp_left();
void gen_kerf_comp_right();
void gen_kerf_comp_disable();

void gen_feed(unsigned val);

void gen_reset_func();

void gen_program_end();

void gen_mode_inc();
void gen_mode_abs();

#endif /* GEN__H */
