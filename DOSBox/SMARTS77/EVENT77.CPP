/**************************************************************/
/* A Small Real Time System for the Real-Time laboratory      */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum        */
/* Jerusalem College of Technology, 5759-64 (1999)            */
/* update Tishrey  5777     	                              */
/* EVENT77.CPP, events handling	                              */
/**************************************************************/
#include "smarts77.h"

Event::Event()
{
	reset();
}

void Event::send(char name, void *param, int synch)
{
	int i;
	while(testAndSet( ))
		SMARTS.callScheduler( );

	source = SMARTS.getCurrentName( );
	data = param;

	for (i=SMARTS.getTotalTasks()-1; i>=0; --i)
		if (SMARTS.getName(i) == name)
			break;

	if (i>=0) 
	{
		if (SMARTS.getStatus(i)==SUSPENDED && SMARTS.getExpectedEvent(i)==this)
			SMARTS.resume(i);
		if (synch) 
		{
			senderWait = SMARTS.getCurrentTask( );
			dest = name;
			SMARTS.suspended();
		}
		else
			dest = name;
	}
}

void *Event::wait(char &sourceP)
{
	void *param;
	if (!flag || dest!=SMARTS.getCurrentName()) 
	{
		SMARTS.setCurrentExpectedEvent(this);
		SMARTS.suspended();
	}

	sourceP = source;
	param = data;
	if (senderWait >= 0)
		SMARTS.resume(senderWait);
	reset();
	return (param);
}

int Event::arrived(char &sourceP)
{
	if (flag)
		sourceP = source;
	return flag;
}

void Event::reset()
{
	flag=false;
	data = NULL;
	source = dest = ' ';
	senderWait = -1;
}

int Event::testAndSet()
{
	int tmp;
	SMARTS.contextSwitchOff( );
	tmp = flag;
	flag = true;
	SMARTS.contextSwitchOn( );
	return tmp;
}


