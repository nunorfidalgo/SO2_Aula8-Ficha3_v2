// http://techiethings.blogspot.com/2010/11/waitabletimer-in-c.html
#pragma once

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int count = 0;    // Iteration counter

	HANDLE hTimer = NULL;    // WaitableTimer handle
	hTimer = CreateWaitableTimer(    // Create waitable timer
		NULL,
		FALSE,    // Autoreset --> timer restarts counting after event fired
		NULL);

	SYSTEMTIME time;        // System time structure
	GetSystemTime(&time);    // Curren time
	time.wSecond += 3;        // Wait 3 sec

	FILETIME ftime;    // File time (expected by SetWaitableTimer)
	SystemTimeToFileTime(&time, &ftime);    // Convert system to file time


	if (!SetWaitableTimer(    // Set waitable timer
		hTimer,    // Timer handle
		reinterpret_cast<LARGE_INTEGER*>(&ftime),    // Convert file time to large integer
		2000,    // Period time, fire again after 2 sec
		NULL,
		NULL,
		0))
	{
		cout << "SetWaitableTimer failed" << GetLastError() << endl;
	};


	while (WaitForSingleObject(hTimer, 5000) == WAIT_OBJECT_0) {    // Wait for timer event
		cout << "CALLED " << ++count << endl;
		if (count + 1 > 5) {    // Exit after 5 events
			break;
		}
	}

	CancelWaitableTimer(hTimer);    // Stop timer
	CloseHandle(hTimer);            // Delete handle

	return 0;
}