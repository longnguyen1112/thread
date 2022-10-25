#define WIN32_LEAN_AND_MEAN 


#pragma warning(disable : 4996)

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <io.h>
#include <WinSock2.h>

#if !defined(_Wp64)
#define DWORD_PTR DWORD
#define LONG_PTR LONG
#define INT_PTR INT
#endif

typedef struct info
{
	int num;
	char message[20];
}info_rec,*pinfo_rec;

char data[100];  // Static global data
char* data2; // Dynamic global data
HANDLE STDInput, mapHandle;
LARGE_INTEGER FileSize;
HANDLE* threadHandle;
int* result;
char* globalText;
int size;

WORD WINAPI DoWork(pinfo_rec);



int _tmain(int argc, LPTSTR argv[])
{
	SECURITY_ATTRIBUTES stdOutSA = /* SA for inheritable handle. */
	{ sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	GetFileSizeEx(STDInput, &FileSize);

	STDInput = GetStdHandle(STD_INPUT_HANDLE);
	mapHandle = CreateFileMapping(STDInput, &stdOutSA, PAGE_READONLY, 0, 0, NULL);
	char* textFile = MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, FileSize.QuadPart);
	globalText = textFile;
	size = (FileSize.QuadPart) / 64;


	if (argc <= 1)
	{
		printf("not enough command");
	}

	/*HANDLE worker1, worker2;
	int sizeoffile = 1000;
	data2 = malloc(sizeoffile);
	strcpy(data, "jdsfkljsdalfkj;sldfjsldafjlafjlsdakfjl;sdafj;sldafj;lsdafj;sldafj");
	strcpy(data2, "Kast is great");
	info_rec rec1;
	rec1.num = 1;
	strcpy(rec1.message, "Help me!");

	info_rec rec2;
	rec2.num = 2;
	strcpy(rec2.message, "Help me2!");

	worker1 = (HANDLE)_beginthreadex(NULL, 0, DoWork, &rec1, 0, NULL);

	if (worker1 == NULL)
		printf("Could not start up thread!");

	worker2 = (HANDLE)_beginthreadex(NULL, 0, DoWork, &rec2, 0, NULL);

	if (worker2 == NULL)
		printf("Could not start up thread!");


	WaitForSingleObject(worker1, INFINITE);
	WaitForSingleObject(worker2, INFINITE);

	free(data2);
	system("pause");
	return 0;*/
}

WORD WINAPI DoWork(pinfo_rec data)
{
	int len = strlen(data);
	data->num = 0;
	for (int i = 0; i <= (size - len); i++)
	{
		if (strncmp(data->message, globalText[i], len)==0)
		{
			data->num += 1;
		}
	}

	/*printf("Thread #%d Message ->%s\n", who->num,who->message);
	printf("data ->%s\n", data);
	printf("data ->%s\n", data2);
	if (who->num == 1)
	{
		who->num = 22;
	}
	else
	{
		who->num = 33;
		Sleep(500);
		strcpy(data, "");
	}*/
}