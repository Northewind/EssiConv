#ifndef GEN__H
#define GEN__H


/** Code string processing */
void gen_code(char *s);

/** Test if commenting now, then print */
int gen_comment(char *s);

/** Generate straigh movement */
void gen_lineto(double x, double y);

/** Generate clockwise arc  movement */
void gen_arcCW(double x, double y, double i, double j);

/** Generate counter-clockwise arc  movement */
void gen_arcCCW(double x, double y, double i, double j);

#endif /* GEN__H */
