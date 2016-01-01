/* test3.c: tests deletion and scan. */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "am.h"
#include "pf.h"
#include "testam.h"

//#define MAXRECS	10000	/* max # of records to insert */
#define FNAME_LENGTH 80	/* file name size */

main(int argv, char* argc[])
{
int fd;	/* file descriptor for the index */
char fname[FNAME_LENGTH];	/* file name */
int recnum;	/* record number */
int i;
int sd;	/* scan descriptor */
int numrec;	/* # of records retrieved */
int testval;
struct timeval tim1, tim2, tim3, tim4;
double t1,t2, r1time = 0, r2time = 0, r3time=0, r4time=0;
double cr1time = 0, cr2time = 0, cr3time = 0, cr4time = 0;	
	
	/// BTREE PERFORMANCE ANALYSIS FOR MULTIPLE RECORDS ///

	/* init */
	printf("initializing\n");
	PF_Init();

	/* create index */
	printf("creating index\n");
	AM_BTreeCreateIndex(RELNAME,0,INT_TYPE,sizeof(int));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);

	///// MAIN TESTING HERE FOR MULTIPLE RECORDS /////

	/* insert into index */
	int maxrecs = 1500;
	int rec = 0;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,rec);
			rec++;
		}
	}

	int val = atoi(argc[1]);

	/* LT_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),LT_OP,(char*) &val);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	r1time = r1time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* GT_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),GT_OP,(char*) &val);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	r2time = r2time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* LE_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),LE_OP,(char*) &val);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	r3time = r3time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* GE_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),GE_OP,(char*) &val);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	r4time = r4time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);


	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
	
	AM_BTreeDestroyIndex(RELNAME,0);
	printf("test3 multiple values done!\n");


	/// BTREE PERFORMANCE ANALYSIS FOR CONCAT RECORDS ///

	/* init */
	printf("initializing\n");
	PF_Init();

	/* create index */
	printf("creating index\n");
	AM_BTreeCreateIndex(RELNAME,0,INT_TYPE,sizeof(int));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);

	///// MAIN TESTING HERE FOR MULTIPLE RECORDS /////

	/* insert into index */
	maxrecs = 1500;
	rec = 0;
	int tmp;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			tmp = (recnum*10 + i);
			AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,rec);
			rec++;
		}
	}

	val = atoi(argc[1]);
	int val1 = val*10;
	int val2 = val*10 + 9;

	/* LT_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),LT_OP,(char*) &val1);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	cr1time = cr1time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* GT_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),GT_OP,(char*) &val2);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	cr2time = cr2time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* LE_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),LE_OP,(char*) &val2);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	cr3time = cr3time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* GE_OP range queries on BTREE MULTIPLE RECORDS */
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),GE_OP,(char*) &val1);
	gettimeofday(&tim1, NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		numrec++;
	}
	gettimeofday(&tim2, NULL);

	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	cr4time = cr4time + (t2 - t1);
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);


	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
	
	AM_BTreeDestroyIndex(RELNAME,0);
	printf("test3 multiple values done!\n");	


	printf("RANGE TIME LT_OP: %.8lf\n",r1time);
	printf("RANGE TIME GT_OP: %.8lf\n",r2time);
	printf("RANGE TIME LE_OP: %.8lf\n",r3time);
	printf("RANGE TIME GE_OP: %.8lf\n",r4time);
	printf("CONC RANGE TIME LT_OP: %.8lf\n",cr1time);
	printf("CONC RANGE TIME GT_OP: %.8lf\n",cr2time);
	printf("CONC RANGE TIME LE_OP: %.8lf\n",cr3time);
	printf("CONC RANGE TIME GE_OP: %.8lf\n",cr4time);
}