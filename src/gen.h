#ifndef GEN__H
#define GEN__H


/** Initialize automaton state */
void gen_init();

/** Code string processing */
void gen_str(char *str);

/** Generate straight movement */
void gen_lineto(double x, double y);

/** Generate clockwise arc  movement */
void gen_arcCW(double x, double y, double i, double j);

/** Generate counter-clockwise arc  movement */
void gen_arcCCW(double x, double y, double i, double j);

#endif /* GEN__H */
