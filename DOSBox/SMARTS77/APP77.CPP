/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */

#include "smarts77.h"

Mutex ioMutex(false), joMutex(false), koMutex(false);
// D -> A
// E -> B
// F -> C
Event AtoC, AtoB;
Event DtoF, DtoE;
FILE *myOutput = fopen("test.txt", "w");
// user Functions
void a()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   A Start    *********************";
	fprintf(myOutput, "\n *************   A Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "A"; // cout in atomic
		fprintf(myOutput, "A");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	printf("A acquire joMutex\n");
	fprintf(myOutput, " A acquire joMutex\n");
	joMutex.acquire();

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "A"; // cout in atomic
		fprintf(myOutput, "A");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" A send to C\n");
	fprintf(myOutput, " A send to C\n");
	AtoC.send('C', NULL, 0);
	printf(" A send to B\n");
	fprintf(myOutput, " A send to B\n");
	AtoB.send('B', NULL, 0);

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "A"; // cout in atomic
		fprintf(myOutput, "A");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" A release joMutex\n");
	fprintf(myOutput, " A release joMutex\n");
	joMutex.release();

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "A"; // cout in atomic
		fprintf(myOutput, "A");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   A Finish   *********************";
	fprintf(myOutput, "\n *************   A Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void b()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   B Start    *********************";
	fprintf(myOutput, "\n *************   B Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "B";
		fprintf(myOutput, "B");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	char s;
	printf(" B wait to A\n");
	fprintf(myOutput, " B wait to A\n");
	AtoB.wait(s);

	for (j = 0; j < 26; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "B";
		fprintf(myOutput, "B");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   B Finish   *********************";
	fprintf(myOutput, "\n *************   B Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void c()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   C Start    *********************";
	fprintf(myOutput, "\n *************   C Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "C";
		fprintf(myOutput, "C");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	char s;
	printf(" C wait to A\n");
	fprintf(myOutput, " C wait to A\n");
	AtoC.wait(s);

	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "C";
		fprintf(myOutput, "C");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" C acquire joMutex\n");
	fprintf(myOutput, " C acquire joMutex\n");
	joMutex.acquire();

	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "C";
		fprintf(myOutput, "C");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	printf(" C release joMutex\n");
	fprintf(myOutput, " C release joMutex\n");
	joMutex.release();
	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   C Finish   *********************";
	fprintf(myOutput, "\n *************   C Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void d()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   D Start    *********************";
	fprintf(myOutput, "\n *************   D Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "D"; // cout in atomic
		fprintf(myOutput, "D");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	printf("D acquire koMutex\n");
	fprintf(myOutput, " D acquire koMutex\n");
	koMutex.acquire();

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "D"; // cout in atomic
		fprintf(myOutput, "D");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" D send to F\n");
	fprintf(myOutput, " D send to F\n");
	DtoF.send('F', NULL, 0);
	printf(" D send to E\n");
	fprintf(myOutput, " D send to E\n");
	DtoE.send('E', NULL, 0);

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "D"; // cout in atomic
		fprintf(myOutput, "D");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" D release koMutex\n");
	fprintf(myOutput, " D release koMutex\n");
	koMutex.release();

	for (j = 0; j < 6; j++) //
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "D"; // cout in atomic
		fprintf(myOutput, "D");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   D Finish   *********************";
	fprintf(myOutput, "\n *************   D Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void e()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   E Start    *********************";
	fprintf(myOutput, "\n *************   E Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "E";
		fprintf(myOutput, "E");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	char s;
	printf(" E wait to D\n");
	fprintf(myOutput, " E wait to D\n");
	DtoE.wait(s);

	for (j = 0; j < 26; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "E";
		fprintf(myOutput, "E");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   E Finish   *********************";
	fprintf(myOutput, "\n *************   E Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void f()
{
	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   F Start    *********************";
	fprintf(myOutput, "\n *************   F Start    *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
	int j;
	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "F";
		fprintf(myOutput, "F");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}

	char s;
	printf(" F wait to D\n");
	fprintf(myOutput, " F wait to D\n");
	DtoF.wait(s);

	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "F";
		fprintf(myOutput, "F");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" F acquire koMutex\n");
	fprintf(myOutput, " F acquire koMutex\n");
	koMutex.acquire();

	for (j = 0; j < 6; j++)
	{
		for (long i = 0; i < 600000; i++)
			;
		// SMARTS.contextSwitchOff();
		ioMutex.acquire();
		cout << "F";
		fprintf(myOutput, "F");
		// SMARTS.contextSwitchOn();
		ioMutex.release();
	}
	printf(" F release koMutex\n");
	fprintf(myOutput, " F release koMutex\n");
	koMutex.release();
	// destroy

	// SMARTS.contextSwitchOff();
	ioMutex.acquire();
	cout << "\n *************   F Finish   *********************";
	fprintf(myOutput, "\n *************   F Finish   *********************");
	// SMARTS.contextSwitchOn();
	ioMutex.release();
}

void main()
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
	SMARTS.declareTask(a, 'A', 402, 3);
	SMARTS.declareTask(b, 'B', 401, 3);
	SMARTS.declareTask(c, 'C', 400, 3);
	//SMARTS.declareTask(d, 'D', 402, 3);
	//SMARTS.declareTask(e, 'E', 401, 3);
	//SMARTS.declareTask(f, 'F', 400, 3);
	SMARTS.runTheTasks();
}

