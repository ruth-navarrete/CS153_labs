#include "types.h"
#include "stat.h"
#include "user.h"

int main (int argc, char* argv[]) {

	int pid1 = 0;
	int time1 = 0; 
	int pid2 = 0;
	int time2 = 0;

	printf(1, "\nStart timing test\n"); 

	pid1 = fork();
	
	//build a number of forks to show the wait/turnaround times
	//have children to do printing or anything (adding nop instructions)
	//print out the pid to know which child is running and show the waiting/turn time 



	if (pid1) {
		time1 = turnaroundTime(getpid());
		printf(1,"\nParent process: pid is %d, turnaround time is %d \n", getpid(),time1);
		
		time2 = waitingTime(getpid());
		printf(1,"\nthe waiting time for the process was %d \n", time2);
	}
	else 
	{
		time1 = turnaroundTime(getpid());
		printf(1,"\nChild process: pid is %d, turnaround time is %d \n", getpid(),time1);
		
		time2 = waitingTime(getpid());
		printf(1,"\nthe waiting time for this process is %d \n", time2);
		
	}




	return 0;

}
