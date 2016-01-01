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
struct timeval tim1, tim2;
double t1,t2, etime = 0, cetime = 0;	
	
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
	int maxrecs = atoi(argc[1]);
	int rec = 0;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,rec);
			rec++;
		}
	}

	gettimeofday(&tim1, NULL);
	for(i=0; i<maxrecs; i=i+50){
		int t = i;
		sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,(char *) &t);
		while((recnum=AM_BTreeFindNextEntry(sd))>= 0){}
		AM_BTreeCloseIndexScan(sd);
	}
	gettimeofday(&tim2, NULL);
	
	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	etime = etime + (t2 - t1);

	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
	
	AM_BTreeDestroyIndex(RELNAME,0);
	printf("test3 multiple values done!\n");


	/// List PERFORMANCE ANALYSIS FOR MULTIPLE RECORDS ///

	/* init */
	printf("initializing\n");
	PF_Init();

	/* create index */
	printf("creating index\n");
	AM_ListCreateIndex(RELNAME,0,INT_TYPE,sizeof(int));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);

	///// MAIN TESTING HERE FOR MULTIPLE RECORDS /////

	/* insert into index */
	maxrecs = atoi(argc[1]);
	rec = 0;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			AM_ListInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,rec);
			rec++;
		}
	}
	
	gettimeofday(&tim1, NULL);
	for(i=0; i<maxrecs; i=i+50){
		int t = i;
		sd = AM_ListOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,(char *) &t);
		while((recnum=AM_ListFindNextEntry(sd))>= 0){}
		AM_ListCloseIndexScan(sd);
	}
	gettimeofday(&tim2, NULL);
	
	t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
	t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
	cetime = cetime + (t2 - t1);

	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
	
	AM_ListDestroyIndex(RELNAME,0);
	printf("test3 multiple values done!\n");

	printf("EQQuery TIME : %.8lf\n",etime);
	printf("CEQQuery TIME : %.8lf\n",cetime);
}
