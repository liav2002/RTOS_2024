/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/
#include "smarts77.h"
#define NUM_OF_ITERATIONS_a 5
#define NUM_OF_ITERATIONS_b 7
#define NUM_OF_ITERATIONS_c 9

/*
Case1 (Both of them working): 5, 7, 9
Case2 (Both of them not working): 600, 600, 600
Case3 (Only EDF working): 8, 12, 10
*/

/*
Liav Ariel (212830871)
Meir Ariche (324043728)
*/

// user Functions
void a( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j < NUM_OF_ITERATIONS_a; j++)
	{
		for (long i=0; i < 600000; i++);
		SMARTS.contextSwitchOff();
		cout << "A";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Finish   *********************";
	SMARTS.contextSwitchOn();
}

void b( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j < NUM_OF_ITERATIONS_b; j++)
	{
		for (long i=0; i < 600000; i++);
		SMARTS.contextSwitchOff();
		cout << "B";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Finish   *********************";
	SMARTS.contextSwitchOn();
}

void c( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j < NUM_OF_ITERATIONS_c; j++)
	{
		for (long i=0; i < 600000; i++);
		SMARTS.contextSwitchOff();
		cout << "C";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Finish   *********************";
	SMARTS.contextSwitchOn();
}

void main( )
{
	textcolor(WHITE);
	clrscr();
	
	// Round Rubin
	// SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, roundRobin);
	
	// EDF
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, EDF);
	
	//Parameters are: char name, int cycleTime, int cycles
	SMARTS.declareTask(a, 'A', 50, 3);
    SMARTS.declareTask(b, 'B', 70, 4);
    SMARTS.declareTask(c, 'C', 100, 5);
	SMARTS.runTheTasks();
	printf("Press any key for continue...");
	getch();
}



