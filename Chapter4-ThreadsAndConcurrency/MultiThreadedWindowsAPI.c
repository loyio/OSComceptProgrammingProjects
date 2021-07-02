#include<windows.h>
#include<stdio.h>
DWORD Sum;

/* The thread will execute in this function */
DWORD WINAPI Summation(LPVOID Param)
{
    DWORD Upper = *(DWORD*)Param;
    for(DWORD i = 1; i<=Upper; i++)
        Sum += i;
    return 0;
}

int main(int argc, char *argv[])
{
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int Param;

    Param = atoi(argv[1]);
    /* create the thread */
    ThreadHandle = CreateThread(
        NULL, // default secutiry attributes 
        0, // default stack size
        Summation, // thread function
        &Param, // Parameter to thread function
        0, // default creation flags
        &ThreadId // return the thread identifier
    );

    WaitForSingleObject(ThreadHandle, INFINITE);

    CloseHandle(ThreadHandle);
    printf("sum = %d\n", Sum);
}