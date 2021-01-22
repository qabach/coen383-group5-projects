#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linked.h"
//returns the end point of the list
int generateJob(struct head * n, int startpoint, int count)
{
	char num[10], s[10];
	int i;
	int arr, serv, pri;
	//generate the random values for a job.
	for(i = startpoint;  i <= startpoint+ count; ++i)
	{
		s[0] = 'P';
		arr = rand() %100;
		serv = (rand() % 11) + 1;
		pri = (rand() % 4) + 1;
		sprintf(num,"%d",i);
		strncat(s,num, (i/10)+1);
		insertDataWN(n,arr,serv,pri,s);
		memset(s, '\0', 10);
	}
	return i;
}

//The code that is going to run
int main()
{
	struct head *yay;
	int seed = 1;
	int count, count2;
	srand(time(NULL));
	yay = malloc(sizeof(struct head));
	//generate 10 jobs
	count = generateJob(yay,1,10);
	count2 = 2;
	//generatate more jobs if needed
	while(notIdle(yay))
	{
		count = generateJob(yay,count,count2);
		count2 *= 2;
	}
	printf("%d\n", yay->len);
	
	//print out list
	printList(yay);
	clr(yay);
	
	printf("%d\n", yay->len);
	printList(yay);
	
	free(yay);
	return 0;
}
