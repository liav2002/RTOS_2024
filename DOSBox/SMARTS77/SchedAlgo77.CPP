/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory                 */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum                  */
/* Jerusalem College of Technology, 5759-64 (1999)                            */
/* SchedAlgo64.CPP, short-term scheduler algorithms                */
/****************************************************************/


#include "smarts77.h"

int roundRobin( )
// Round Robin short-term algorithm 
{
	int count;
	int nextTask = (SMARTS.getCurrentTask()+1)%SMARTS.getTotalTasks( );
	for (count=0;
	     SMARTS.getStatus(nextTask)!=READY && count<SMARTS.getTotalTasks( );
	     count++)
	     nextTask=++nextTask%SMARTS.getTotalTasks( );
	if (count == SMARTS.getTotalTasks( ))	// no found READY task to run
		nextTask = SMARTS.getTotalTasks( );
	return nextTask;
}

int EDF()
// Earliest Deadline First short-term algorithm 
{
	int min = MAXINT;
	int nextTask = SMARTS.getTotalTasks();

	for (int i = 0; i < SMARTS.getTotalTasks(); i++)
		if (SMARTS.getStatus(i) == READY &&
			min > SMARTS.getLeftCycleTime(i))
		{
			nextTask = i;
			min = SMARTS.getLeftCycleTime(i);
		}

	return nextTask;
}

