Btree : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o
	cc -g am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o 

List : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainList.o amscan.o amprint.o
	cc -g am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainList.o amscan.o amprint.o 

Query : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainquery.o amscan.o amprint.o
	cc -g am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainquery.o amscan.o amprint.o 

QueryList : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainqueryList.o amscan.o amprint.o
	cc -g am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o mainqueryList.o amscan.o amprint.o 

EQ : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o EQmain.o amscan.o amprint.o
	cc -g am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o EQmain.o amscan.o amprint.o 

amlayer.o : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o amscan.o amprint.o
	ld -r am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o amscan.o amprint.o  -o amlayer.o

am.o : am.c am.h pf.h
	cc -c am.c

amfns.o : amfns.c am.h pf.h
	cc -c amfns.c

amsearch.o : amsearch.c am.h pf.h
	cc -c amsearch.c

aminsert.o : aminsert.c am.h pf.h
	cc -c aminsert.c

amscan.o : amscan.c am.h pf.h
	cc -c amscan.c

amstack.o : amstack.c am.h pf.h
	cc -c amstack.c

amglobals.o : amglobals.c am.h
	cc -c amglobals.c

amprint.o : amprint.c am.h pf.h 
	cc -c amprint.c
	
main.o : main.c am.h pf.h 
	cc -c main.c

mainList.o : mainList.c am.h pf.h
	cc -c mainList.c

mainquery.o : mainquery.c am.h pf.h
	cc -c mainquery.c

mainqueryList.o : mainqueryList.c am.h pf.h
	cc -c mainqueryList.c

EQmain.o : EQmain.c am.h pf.h
	cc -c EQmain.c

clean :
	rm -f *.o
	rm -f a.out
	rm -f testrel.0
	rm -f ha.0