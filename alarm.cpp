#include <iostream>
#include <unistd.h>
#include <signal.h>

const int TIMESLICE = 2;

void sigalarm_handler(int signum) {
        std::cout << "got SIGALRM %d\n" << signum << std::endl;
}

int main() {
        signal(SIGALRM, sigalarm_handler);
        std::cout << "pid is %d\n" << getpid() << std::endl;

        while(true) {
                alarm(TIMESLICE);

                sleep(5);
                std::cout << "loop again\n";
        }

        return 0;
}
