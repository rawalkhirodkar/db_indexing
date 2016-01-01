/* test3.c: tests deletion and scan. */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "am.h"
#include "pf.h"
#include "testam.h"

//#define MAXRECS	10000	/* max # of records to insert */
#define FNAME_LENGTH 80	/* file name size */

char* conc(int val, int rec){
	char res[5] = {'0','0','0','0','_','0'};
	int digits = 3;
	while(val != 0){
		int q = val % 10;
		res[digits] = (char) 48+q;
		digits--;
		val = val/10;
	}

	res[5] = (char) 48+rec;
	return &res;
}


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
double t1,t2, itime = 0, dtime = 0, itime2 = 0, dtime2 = 0;	
	
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

	/* first, make sure that simple deletions work */
	printf("inserting into index\n");
	for (recnum=0; recnum < 20; recnum++){
		AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,
				recnum);
	}

	printf("deleting odd number records\n");
	for (recnum=1; recnum < 20; recnum += 2)
		AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,
					recnum);

	printf("retrieving even number records\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	printf("deleting even number records\n");
	for (recnum=0; recnum < 20; recnum += 2)
		AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,
					recnum);

	printf("retrieving from empty index\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	///// MAIN TESTING HERE FOR MULTIPLE RECORDS /////

	/* insert into index */
	int maxrecs = atoi(argc[1]);
	int rec = 0;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			gettimeofday(&tim1, NULL);
			AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,rec);
			gettimeofday(&tim2, NULL);

			t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
			t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
			itime = itime + (t2 - t1);
			rec++;
		}
	}

	/* delete everything */
	rec = 0;
	printf("deleting everything\n");
	for (recnum=0; recnum < maxrecs; recnum +=1){
		for(i=0;i<10;i++){
			gettimeofday(&tim3, NULL);
			AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,rec);
			gettimeofday(&tim4, NULL);

			t1=tim3.tv_sec+(tim3.tv_usec/1000000.0);
			t2=tim4.tv_sec+(tim4.tv_usec/1000000.0);
			dtime = dtime + (t2 - t1);
			rec++;
		}
	}

	printf("retrieving from empty index\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
	
	AM_BTreeDestroyIndex(RELNAME,0);
	printf("test3 multiple values done!\n");


	//// BTREE PERFORMANCE ANALYSIS FOR CONCAT RECORDS ////
	
	/* create index */
	printf("creating index\n");
	AM_BTreeCreateIndex(NRLNAME,0,INT_TYPE,sizeof(int));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",NRLNAME);
	fd = PF_OpenFile(fname);
	int tmp;

	/* first, make sure that simple deletions work */
	printf("inserting into index\n");
	for (recnum=0; recnum < 10; recnum++){
		tmp = (recnum*10 + recnum);
		AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,
				recnum);
	}

	printf("deleting odd number records\n");
	for (recnum=1; recnum < 10; recnum += 2){
		tmp = (recnum*10 + recnum);
		AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,
					recnum);
	}

	printf("retrieving even number records\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	printf("deleting even number records\n");
	for (recnum=0; recnum < 10; recnum += 2){
		tmp = (recnum*10 + recnum);
		AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,
					recnum);
	}

	printf("retrieving from empty index\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);


	///// MAIN TESTING HERE FOR CONCATENATED RECORDS /////

	/* insert into index */
	maxrecs = atoi(argc[1]);
	rec = 0;

	printf("begin test of performance analysis\n");
	printf("inserting into index\n");
	for (recnum=0; recnum < maxrecs; recnum+=1){
		for(i=0; i<10; i++){
			gettimeofday(&tim1, NULL);

			tmp = (recnum*10 + i);
			AM_BTreeInsertEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,rec);
			
			gettimeofday(&tim2, NULL);

			t1=tim1.tv_sec+(tim1.tv_usec/1000000.0);
			t2=tim2.tv_sec+(tim2.tv_usec/1000000.0);
			itime2 = itime2 + (t2 - t1);
			rec++;
		}
	}

	/* delete everything */
	rec = 0;
	printf("deleting everything\n");
	for (recnum=0; recnum < maxrecs; recnum +=1){
		for(i=0;i<10;i++){

			gettimeofday(&tim3, NULL);
			
			tmp = (recnum*10 + i);
			AM_BTreeDeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&tmp,rec);
			
			gettimeofday(&tim4, NULL);

			t1=tim3.tv_sec+(tim3.tv_usec/1000000.0);
			t2=tim4.tv_sec+(tim4.tv_usec/1000000.0);
			dtime2 = dtime2 + (t2 - t1);
			rec++;
		}
	}

	printf("retrieving from empty index\n");
	numrec= 0;
	sd = AM_BTreeOpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_BTreeFindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_BTreeCloseIndexScan(sd);

	/* destroy everything */
	printf("closing down\n");
	PF_CloseFile(fd);
		AM_BTreeDestroyIndex(NRLNAME,0);
	printf("test3 done!\n");

	printf("INSERTION TIME : %.8lf\n",itime);
	printf("DELETION TIME : %.8lf\n",dtime);
	printf("INSERTION TIME : %.8lf\n",itime2);
	printf("DELETION TIME : %.8lf\n",dtime2);
}
