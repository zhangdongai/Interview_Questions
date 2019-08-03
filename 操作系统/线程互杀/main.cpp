#include <iostream>
#include <chrono>
#include <pthread.h>

pthread_t main_tid = -1;

void* entry_f(void*) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    auto t_start = std::chrono::system_clock::now();
    int loop_num = 0;
    while (1) {
        auto tmp_time = std::chrono::system_clock::now();
        if (tmp_time > t_start + std::chrono::seconds(1)) {
            std::cout << "child thread running" << std::endl;
            t_start = tmp_time;
            ++loop_num;
        }
        pthread_testcancel();
//        if (loop_num >= 5)
//            pthread_cancel(main_tid);
    }
}

int main(int, char**) {
    pthread_t t_id;
    pthread_create(&t_id, nullptr, entry_f, nullptr);
    auto main_t_start = std::chrono::system_clock::now();
    int loop_num = 0;
    main_tid = pthread_self();
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    while (1) {
        auto tmp_time = std::chrono::system_clock::now();
        if (tmp_time > main_t_start + std::chrono::seconds(1)) {
            std::cout << "main thread running, " << pthread_self() << std::endl;
            main_t_start = tmp_time;
            ++loop_num;
        }
        pthread_testcancel();
        if (loop_num > 5)
//            pthread_cancel(t_id);
            pthread_exit(nullptr);
    }
    std::cout << "####main loop end####" << std::endl;
    return 0;
}
