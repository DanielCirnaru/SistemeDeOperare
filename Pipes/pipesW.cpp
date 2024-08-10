#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

// Functie pentru a verifica daca un numar este prim
bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}

int main()
{
    HANDLE p[10][2]; // Array de pipe-uri

    // Crearea a 10 pipe-uri
    for (int i = 0; i < 10; i++)
    {
        SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
        CreatePipe(&p[i][0], &p[i][1], &sa, 0);
    }

    // Crearea a 10 procese copil
    for (int i = 0; i < 10; i++)
    {
        PROCESS_INFORMATION pi;
        STARTUPINFO si = { sizeof(STARTUPINFO) };
        si.hStdInput = p[i][0];
        si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        si.dwFlags |= STARTF_USESTDHANDLES;

        // Calculeaza intervalul de cautare a numerelor prime
        int start = i * 1000 + 1;
        int end = (i + 1) * 1000;

        char cmd[100];
        sprintf(cmd, "child_process.exe %d %d", start, end);

        CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

        // Inchide handle-urile din procesul parinte
        CloseHandle(p[i][0]);
        CloseHandle(p[i][1]);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    return 0;
}
