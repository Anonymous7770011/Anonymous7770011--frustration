#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <windows.h>
#include <wchar.h>
#include <time.h>
void writerfun(char *myPtr,int i)
{
	
	char array[256][256];
	int k = 0;
	int j = 0;
	time_t t;
	struct tm* tm_info;
	char timeString[9];
	time(&t);
	tm_info = localtime(&t);
	strftime(timeString, sizeof(timeString), "%H:%M:%S", tm_info);
	FILE* indexer;
	FILE* writer;
	indexer = fopen("test.txt", "r");
	while (fgets(array[k], 100, indexer) != NULL)
	{
		
		size_t len = strlen(array[k]);
		if (len > 0 && array[k][len - 1] == '\n') {
			array[k][len - 1] = '\0';
		}
		if (strlen(array[k]) > 0) {
			k++;
		}
	}
	fclose(indexer);
	
	writer = fopen("test.txt", "w");
	fclose(writer);
	writer = fopen("test.txt", "a");
	for(j;j<k;j++)
	{
		
		if (j == i)
		{
			fprintf(writer, "%s:%s\n", myPtr, timeString);
			printf("%s:%s\n", myPtr, timeString);
		}
		else
		{
			fprintf(writer, "%s\n", array[j]);
			printf("%s\n", array[j]);
		}		
	}
	fclose(writer);
	printf("Finished\n");
}
int test2(char* checker)
{
	char title[256];
	FILE* reader;
	FILE* writer;
	reader = fopen("test.txt", "r");
	if (reader == NULL)
	{
		printf("File not found rerun the program \n");
		reader = fopen("test.txt", "w");
		fclose(reader);
		return 0;

	}
	reader = fopen("test.txt", "r");
	while(1)
	{
		printf("1");
		if (fgets(title, 100, reader) != NULL)
		{
			printf("%s", title);
			size_t len = strlen(title);
			if (len > 0 && title[len - 1] == '\n')
			{
				title[len - 1] = '\0';
			}
			
			char* myPtr = strtok(title, ":");
			int i = 0;
			printf("%s", myPtr);
			while (myPtr != NULL)
			{
				if (strcmp(myPtr, checker) == 0)
				{
					printf("1");
					char* myPtr1 = strtok(NULL, "\n");
					fclose(reader);
					writerfun(myPtr, i);
					break;
				}i++;
			}
			printf("2");
			fclose(reader);
			fclose(reader);
			reader = fopen("test.txt", "a");
			fprintf(reader, "%s:0", checker);
			fclose(reader);
			break;
		}
		else
		{
			printf("3");
			fclose(reader);
			reader = fopen("test.txt", "a");
			fprintf(reader, "%s:0", checker);
			fclose(reader);
			break;
		}
	}
}
int main()
{
	wchar_t prevWindowTitle[256] = L""; 
	wchar_t currentWindowTitle[256];   
	char charWindowTitle[256];        
	while (1) {
		HWND foregroundWindow = GetForegroundWindow();
		if (foregroundWindow != NULL) {
			GetWindowTextW(foregroundWindow, currentWindowTitle, sizeof(currentWindowTitle) / sizeof(wchar_t));
			int len = WideCharToMultiByte(CP_UTF8, 0, currentWindowTitle, -1, charWindowTitle, sizeof(charWindowTitle), NULL, NULL);

			if (len > 0) {
				if (wcscmp(prevWindowTitle, currentWindowTitle) != 0) {
					wcscpy(prevWindowTitle, currentWindowTitle);
					test2(charWindowTitle+2);
				}
			}
		}
	}

	return 0;
}
