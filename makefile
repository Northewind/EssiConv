DIR_TEST=tests
DIR_RES=${DIR_TEST}/result
OUTF=bin/essi2eia
COMP_OPT=-Wall -g --pedantic -std=c89 -o ${OUTF} src/*.c
COMP_OPT_TESTS=${COMP_OPT} -D TEST src/tests/*.c


EXEC_OPT=
T1=115_039.esi


all:
	gcc ${COMP_OPT}

clang:
	clang ${COMP_OPT}


test_ir:
	clang -D TEST_IR ${COMP_OPT_TESTS}
	${OUTF}


t1:
	${OUTF} ${EXEC_OPT} < ${DIR_TEST}/${T1} > ${DIR_RES}/${T1}
	cat ${DIR_RES}/${T1}


clean:
	rm -f ${OUTF}
	rm -f ${DIR_RES}/*
	rm -Rf docs/doxy/*

