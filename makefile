OUTF=bin/essi2eia
T1=115_039.esi
T2=115_046.esi
T3=115_065.esi
COMP_OPT=--pedantic -std=c89 -o ${OUTF} src/*.c

all:
	gcc ${COMP_OPT}

clang:
	clang ${COMP_OPT}

test1:
	${OUTF} < tests/${T1} > tests/result/${T1}
test2:
	${OUTF} < tests/${T2} > tests/result/${T2}
test3:
	${OUTF} < tests/${T3} > tests/result/${T3}

clean:
	rm ${OUTF}
	rm tests/result/*

