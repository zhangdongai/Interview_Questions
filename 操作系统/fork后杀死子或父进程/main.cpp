#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

int main(int argc, char** argv) {
    for (int i = 0; i < argc; ++i)
        printf("argc %d = %s\n", i, argv[i]);
    int param_id = atoi(argv[1]);
    printf("%d\n", param_id);
    int l_value = 0;
    printf("before fork %d\n", l_value);
    if (param_id == -1) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            pid_t child_pid = getpid();
            printf("child process running, pid=%d, parent_id = %d\n", child_pid, getppid());
            ++l_value;
            char arg1[128] = {0};
            sprintf(arg1, "%d", child_pid);
            execlp("./fork_exec", "fork_exec", arg1, (char*)(0));
        }
        else if (pid > 0) {
            printf("parent process running, pid=%d\n", getpid());
        }
    }
    if (param_id != -1) {
        auto s_time = std::chrono::system_clock::now();
        printf("child process begin to loop\n");
        int loop_num = 0;
        while (true) {
            auto tmp_time = std::chrono::system_clock::now();
            if (tmp_time > s_time + std::chrono::seconds(1)) {
                ++loop_num;
                s_time = tmp_time;
                printf("child process run once####\n");
                if (loop_num > 15)
                    printf("parent processid = %d\n", getppid());
            }
        }
    }
    else {
        auto s_time = std::chrono::system_clock::now();
        printf("parent process begin to loop\n");
        int loop_num = 0;
        while (true) {
            auto tmp_time = std::chrono::system_clock::now();
            if (tmp_time > s_time + std::chrono::seconds(1)) {
                ++loop_num;
                printf("parent process run once####\n");
                s_time = tmp_time;
                if (loop_num > 10)
                    exit(0);
            }
        }
    }
    printf("finish running####\n");
    return 0;
}
