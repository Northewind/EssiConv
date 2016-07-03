OUTF=bin/essi2eia
COMP_OPT=--pedantic -std=c89 -o ${OUTF} *.c

all:
	gcc ${COMP_OPT}

clang:
	clang ${COMP_OPT}

test1:
	${OUTF} < tests/115_039.esi

clean:
	rm ${OUTF}

