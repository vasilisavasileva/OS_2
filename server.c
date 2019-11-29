//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<Windows.h>
#include<tchar.h>

int _tmain(int argc, _TCHAR* argv[]) {
	HANDLE inH = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE outH = GetStdHandle(STD_OUTPUT_HANDLE);
	double l;
	DWORD ReadBytes, WriteBytes;
	BOOL isSuccess;
	int n;
	isSuccess = ReadFile(inH, &n, sizeof(double), &ReadBytes, NULL);
	if (!isSuccess)
		exit(1);
	for (int i = 0;i < n;i++) {
		ReadFile(inH, &l, sizeof(double), &ReadBytes, NULL);
		l = sqrt(l);
		WriteFile(outH, &l, sizeof(double), &WriteBytes, NULL);
	}
	CloseHandle(inH);
	CloseHandle(outH);
	return 0;
}