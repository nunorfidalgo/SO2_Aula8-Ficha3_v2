#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <time.h>

//DWORD WINAPI ThreadPrincipal(LPVOID param);
DWORD WINAPI ThreadAuxiliar(LPVOID param);

DWORD instante;
bool terminar;

int _tmain(int argc, LPTSTR argv[]) {
	DWORD threadId;
	/*HANDLE hThreadPrinc, hThreadAux;*/
	HANDLE hThreadAux;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif


	/*hThreadPrinc = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPrincipal, NULL, 0, &threadId);
	if (hThreadPrinc != NULL)
		_tprintf(TEXT("Lancei uma thread com id %d\n"), threadId);
	else {
		_tprintf(TEXT("Erro ao criar Thread\n"));
		return -1;
	}*/

	SYSTEMTIME st;
	FILETIME ft, ftUTC;
	LARGE_INTEGER li;
	HANDLE hTimer;
	long int intervalo;

	// Código não relacionado
	// validação de argumentos

	ZeroMemory(&st, sizeof(SYSTEMTIME));

	GetSystemTime(&st);
	if (_stscanf_s(argv[1], TEXT("%hd:%hd:%hd"), &st.wHour, &st.wMinute, &st.wSecond))
	{
		_tprintf(TEXT("Erro no 1º argumento: formato esperado HH:MM:SS\n"));
	}

	// mais código
	intervalo = _ttoi(argv[1]);

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

	// if hTimer == null  blah

	SystemTimeToFileTime(&st, &ft);
	LocalFileTimeToFileTime(&ft, &ftUTC);

	li.HighPart = ftUTC.dwHighDateTime;
	li.LowPart = ftUTC.dwLowDateTime;

	if (!SetWaitableTimer(hTimer, &li, 0, NULL, NULL, TRUE)) {
		_tprintf(TEXT("erro..."));
		return -1;
	}

	hThreadAux = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadAuxiliar, NULL, 0, &threadId);
	if (hThreadAux != NULL) {
		_tprintf(TEXT("Lancei uma thread com id %d\n"), threadId);

		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(TEXT("[Thread%d] Despertei, tempo que dormi: %ld\n"), GetCurrentThreadId(), GetTickCount() - instante);
		terminar = TRUE;
	}
	else {
		_tprintf(TEXT("Erro ao criar Thread\n"));
		return -1;
	}

	//WaitForSingleObject(hThreadPrinc, INFINITE);
	WaitForSingleObject(hThreadAux, INFINITE);

	_tprintf(TEXT("[Thread Principal %d] Finalmente vou terminar..."), GetCurrentThreadId());

	return 0;
}

DWORD WINAPI ThreadAuxiliar(LPVOID param) {

	_tprintf(TEXT("[Consumidor]Sou a thread %d e vou começar a trabalhar ...\n"), GetCurrentThreadId());

	/*DWORD instante;*/

	while (!terminar) {
		instante = GetTickCount();
		//Esperar o intervalo tempo
		terminar = FALSE;
		/*_tprintf(TEXT("[Thread%d] Despertei, tempo que dormi: %ld\n"), GetCurrentThreadId(), GetTickCount() - instante);*/
		return 0;
	}

	//Ciclo interno da thread
	//DWORD instante;
	//while (/*condição de término*/) {
	//	instante = GetTickCount();
	//	//Esperar o intervalo tempo
	//
	//	_tprintf(TEXT("[Thread%d] Despertei, tempo que dormi: %ld\n",
	//		GetCurrentThreadId(), GetTickCount() - instante);
	//}



	// CreateWaitableTimerW(NULL, , TEXT("nome"));
	// SetWaitbleTimer(hTimer, );
	// Ptimerapcroutine



	// O seguinte codigo foi passado da aula...
	//SYSTEMTIME st;
	//FILETIME ft, ftUTC;
	//LARGE_INTEGER li;
	//
	//// Código não relacionado
	//
	//ZeroMemory(&st, sizeof(SYSTEMTIME));
	//
	//GetSystemTime(&st);
	//if (_stscanf_s(argv[1]), TEXT("%hd:%hd:%hd"), &st.wHour, &st.wMinute, &st.wSecond) )
	//{
	//	_tprintf(TEXT("Erro no 1º argumento: formato esperado HH:MM:SS\n"));
	//}
	//
	//// mais código
	//
	//SystemTimeToFileTime(&st, &ft);
	//LocalFileTimeToFileTime(&ft, &ftUTC);
	//
	//li.HighPart = ftUTC.dwHighDateTime;
	//li.LowPart = ftUTC.dwLowDateTime;

}


