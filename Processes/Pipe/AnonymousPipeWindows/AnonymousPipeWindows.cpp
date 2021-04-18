// AnonymousPipeWindows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
    HANDLE ReadHandle, WriteHandle;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char message[BUFFER_SIZE] = "Greeting";
    DWORD written;

    /* Set up security attributes allowing pipes to be inheriited */
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    /* allocate the pipe */
    ZeroMemory(&pi, sizeof(pi));

    /* create the pipe */
    if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0)) {
        fprintf(stderr, "Create Pipe Failed");
        return 1;
    }

    /* establish the START_INFO structure for teh child process */
    GetStartupInfo(&si);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    /* redirect stanard input to the read end of the pipe */
    si.hStdInput = ReadHandle;
    si.dwFlags = STARTF_USESTDHANDLES;

    /* don't allow the child to inherit the write end of pipe */
    SetHandleInformation(WriteHandle, HANDLE_FLAG_INHERIT, 0);

    /* create the child process */
    wchar_t process_name[10] = L"child.exe";
    CreateProcess(NULL, process_name, NULL, NULL, TRUE, /* inherit handles */ 0, NULL, NULL, &si, &pi);
    
    /* close the unused end of the pipe */
    CloseHandle(ReadHandle);

    /* the parent writes to the pipe */
    if (!WriteFile(WriteHandle, message, BUFFER_SIZE, &written, NULL))
        fprintf(stderr, "Error writing to pipe.");

    /* close the write end of the pipe */
    CloseHandle(WriteHandle);

    /* wait for the child to exit */
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
