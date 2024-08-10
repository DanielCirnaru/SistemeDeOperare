#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork(); // Primul proces
    if (pid1 == 0) {
        sleep(1); // Așteaptă 1 secundă
        std::cout << "Procesul 1 a terminat." << std::endl;
        return 0;
    }

    pid_t pid2 = fork(); // Al doilea proces
    if (pid2 == 0) {
        // Cod executat doar în procesul copil (procesul 2)
        sleep(2); // Așteaptă 2 secunde
        std::cout << "Procesul 2 a terminat." << std::endl;
        return 0;
    }

    pid_t pid3 = fork(); // Al treilea proces
    if (pid3 == 0) {
        // Cod executat doar în procesul copil (procesul 3)
        sleep(3); // Așteaptă 3 secunde
        std::cout << "Procesul 3 a terminat." << std::endl;
        return 0;
    }

    // Cod executat doar în procesul părinte (procesul inițial)
    // Așteptăm ca toate cele trei procese să se termine
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);
    waitpid(pid3, nullptr, 0);

    std::cout << "Toate procesele au terminat." << std::endl;
    return 0;
}
