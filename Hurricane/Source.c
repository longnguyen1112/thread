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
	

	STDInput = GetStdHandle(STD_INPUT_HANDLE);
	GetFileSizeEx(STDInput, &FileSize);
	mapHandle = CreateFileMapping(STDInput, &stdOutSA, PAGE_READONLY, 0, 0, NULL);
	char* textFile = MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, FileSize.QuadPart);
	size = (FileSize.QuadPart);
	globalText = malloc(size);
	for (int i = 0; i < size; i++)
	{
		globalText[i] = textFile[i];
	}
	
	if (argc <= 1)
	{
		printf("not enough command");
	}
	else
	{
		int numOfThread = argc - 1;
		pinfo_rec recArray = malloc(numOfThread);
		threadHandle = malloc(numOfThread);
		for (int i = 0; i < numOfThread; i++)
		{
			strcpy(recArray[i].message, argv[i + 1]);
		}
		for (int i = 0; i < numOfThread; i++)
		{
			threadHandle[i] = (HANDLE)_beginthreadex(NULL, 0, DoWork, &recArray[i], 0, NULL);
			if (threadHandle[i] == NULL)
			{
				printf("could not start up thread");
			}
		}

		for (int i = 0; i < numOfThread; i++)
		{
			WaitForSingleObject(threadHandle[i], INFINITE);
		}
	}
	free(data2);
	getch();
	return 0; 
}

WORD WINAPI DoWork(pinfo_rec data)
{
	int len = strlen(data->message+1);
	data->num = 0;
	for (int i = 0; i <= (size - len); i++)
	{
		if (strncmp(&data->message[0], &globalText[i], len)==0)
		{
			data->num += 1;
		}
	}
	printf("%s appears %d times \n", data->message, data->num);

}