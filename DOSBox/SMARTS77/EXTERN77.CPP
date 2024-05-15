/*****************************************************************/
/* A Small Real Time System for the Real-Time laboratory         */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum           */
/* Jerusalem College of Technology, 5759-64 (1999)               */
/* update Tishrey  5777                                          */
/* EXTERN77.CPP, holds all external functions                    */
/*****************************************************************/
#include "smarts77.h"

/**********    GLOBAL Variables    **********/
Parallelism SMARTS;
static unsigned StackSegAct, StackPtrAct;

/**********    EXTERNAL FUNCTION     **********/
void far interrupt timerInterruptHandler(...)
// This function is called 18.2 times per second ( every ~~ 55 millisec).
{
	asm	mov	StackPtrAct,sp; 	// get the stack addr of the task interrupted
	asm	mov	ax,ss;		// by the clock or by a Program interrupt
	asm	mov	StackSegAct,ax;

	SMARTS.timerClocksEnd = getTimerClocks( );

			// if it was called by the timer interrupt (hardware source),
			// it calls the original BIOS routine. not to change the PC work.
	if (!SMARTS.getProgInt( ))
	{
		asm	int userInt;
		SMARTS.handleTimers();
	}
	else	
		SMARTS.resetProgInt( );  //else it is a software "prog interrupt". reset this flag

			// if the 'context switch' flag=true, save the current task variables
			// and call the 'scheduler'
	if (SMARTS.getContextSwitch( ))   // save stack addr of interrupted task in current stack
	{
		SMARTS.setCurrentStack(StackSegAct,StackPtrAct);
		SMARTS.restoreSchedStack( );	      // prepare activation of the task "scheduler"
		SMARTS.getSchedStack(StackSegAct,StackPtrAct);
		asm	mov	ax,StackSegAct;
		asm	mov	ss,ax
		asm	mov	sp,StackPtrAct
	}
			// else if 'context switch' flag=false set 'end of time slice' flag
//	else 
//	{
//		SMARTS.setEndOfTimeSlice();
//		++SMARTS.TScount;	// increment Time Share count
//	}
}
/**********    EXTERNAL FUNCTION     **********/
void scheduler( )	// this also a parallel task
		// This function is called by hardware called 'timerInterruptHandler' function
		// or by software SMARTS system's functions
		// It selects & switches the next task to be run.
{
	int nextTask, i;

		// calling to the 'short term scheduler' algorithm
	nextTask = SMARTS.algorithm( );

		// checking for 'deadlock' : not found task to run and tasks remain suspended
	if (nextTask == SMARTS.getTotalTasks() && 
		SMARTS.sleepTasks==0 && SMARTS.activeTasks>0)
	{
		for (i=SMARTS.getTotalTasks()-1; i >= 0 ; --i)
			if (SMARTS.getStatus(i) == SUSPENDED) 
			{
				cprintf("\ntask %c  is suspended",SMARTS.getName(i)) ;
				SMARTS.setDeadlock();
			}
	}
		// ok to run a next task
	SMARTS.setCurrentTask(nextTask);

		//  'dispatcher' to restore the next task stack addr and registers
	SMARTS.getCurrentStack(StackSegAct,StackPtrAct);
	asm	mov	ax,StackSegAct;
	asm	mov	ss,ax
	asm	mov	sp,StackPtrAct

	asm	pop	bp;
	asm	pop	di;
	asm	pop	si;
	asm	pop	ds;
	asm	pop	es;
	asm	pop	dx;
	asm	pop	cx;
	asm	pop	bx;
	asm	pop	ax;
	asm	iret;	// return from interrupt 
}

/**********    EXTERNAL FUNCTION     **********/
void myTaskEnd( )
{
	SMARTS.taskEnd();	
}



