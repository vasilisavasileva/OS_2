#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<tchar.h>
#include<stdbool.h>

int _tmain(int argc, _TCHAR* argv[]) {

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	TCHAR SecondProcess[] = "server";

	HANDLE pipe1Read, pipe1Write, pipe2Read, pipe2Write;
	CreatePipe(&pipe1Read, &pipe1Write, &sa, 0);
	CreatePipe(&pipe2Read, &pipe2Write, &sa, 0);

	PROCESS_INFORMATION ProcessInfo;
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.dwFlags = STARTF_USESTDHANDLES;
	StartupInfo.hStdInput = pipe1Read;
	StartupInfo.hStdOutput = pipe2Write;


	BOOL process = CreateProcess(NULL,
		SecondProcess,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&StartupInfo,
		&ProcessInfo);

	CloseHandle(pipe1Read);
	CloseHandle(pipe2Write);

	DWORD WriteBytes, ReadBytes;
	double l;
	BOOL isSuccess;

	if (process == 1)
		printf("process true\n");
	else {
		printf("error\n");
		exit(1);
	}
	printf("Enter the count of number: ");
	int n;
	scanf("%d", &n);

	isSuccess = WriteFile(pipe1Write, &n, sizeof(int), &WriteBytes, NULL);
	for (int i = 0;i < n;i++) {
		scanf("%lf", &l);
		isSuccess = WriteFile(pipe1Write, &l, sizeof(double), &WriteBytes, NULL);
		isSuccess ? printf("Sended\n") : printf("Not send\n");
		isSuccess = ReadFile(pipe2Read, &l, sizeof(double), &ReadBytes, NULL);
		isSuccess ? printf("Received\n") : printf("Not received\n");
		printf("res: %f\n", l);
	}

	CloseHandle(pipe1Write);
	CloseHandle(pipe2Read);

	CloseHandle(ProcessInfo.hThread);
	CloseHandle(ProcessInfo.hProcess);

	system("pause");
	return 0;
} 