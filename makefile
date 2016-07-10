DIR_TEST=tests
DIR_RES=${DIR_TEST}/result
OUTF=bin/essi2eia
OUTF_OPT=-c
T1=115_039.esi
T2=115_046.esi
T3=115_065.esi
T4=115_117.esi
Tc1=comment1
Tc2=comment2
Tg1=geom1
COMP_OPT=-Wall -g --pedantic -std=c89 -o ${OUTF} src/*.c

all:
	gcc ${COMP_OPT}

clang:
	clang ${COMP_OPT}


t1:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${T1} > ${DIR_RES}/${T1}
	cat ${DIR_RES}/${T1}
t2:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${T2} > ${DIR_RES}/${T2}
	cat ${DIR_RES}/${T2}
t3:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${T3} > ${DIR_RES}/${T3}
	cat ${DIR_RES}/${T3}
t4:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${T4} > ${DIR_RES}/${T4}
	cat ${DIR_RES}/${T4}
tc1:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${Tc1} > ${DIR_RES}/${Tc1}
	cat ${DIR_RES}/${Tc1}
tc2:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${Tc2} > ${DIR_RES}/${Tc2}
	cat ${DIR_RES}/${Tc2}
tg1:
	${OUTF} ${OUTF_OPT} < ${DIR_TEST}/${Tg1} > ${DIR_RES}/${Tg1}
	cat ${DIR_RES}/${Tg1}

clean:
	rm -f ${OUTF}
	rm -f ${DIR_RES}/*

