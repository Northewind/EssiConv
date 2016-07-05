DIR_TEST=tests
DIR_RES=${DIR_TEST}/result
OUTF=bin/essi2eia
T1=115_039.esi
T2=115_046.esi
T3=115_065.esi
Tc1=comment1
Tc2=comment2
COMP_OPT=--pedantic -std=c89 -o ${OUTF} src/*.c

all:
	gcc ${COMP_OPT}

clang:
	clang ${COMP_OPT}


t1:
	${OUTF} < ${DIR_TEST}/${T1} > ${DIR_RES}/${T1}
	cat ${DIR_RES}/${T1}
t2:
	${OUTF} < ${DIR_TEST}/${T2} > ${DIR_RES}/${T2}
	cat ${DIR_RES}/${T2}
t3:
	${OUTF} < ${DIR_TEST}/${T3} > ${DIR_RES}/${T3}
	cat ${DIR_RES}/${T3}
tc1:
	${OUTF} < ${DIR_TEST}/${Tc1} > ${DIR_RES}/${Tc1}
	cat ${DIR_RES}/${Tc1}
tc2:
	${OUTF} < ${DIR_TEST}/${Tc2} > ${DIR_RES}/${Tc2}
	cat ${DIR_RES}/${Tc2}

clean:
	rm -f ${OUTF}
	rm -f ${DIR_RES}/*

