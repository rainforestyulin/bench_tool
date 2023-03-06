// #ifndef WIN32
// #include <sys/time.h>
// #else
// #include <chrono>
// struct
// {
//     __int64 tv_sec;
//     __int64 tv_usec;
// }timeval;
// int gettimeofday(struct timeval *tv, void )
// {
//     auto time_now = std::chrono::system_clock::now();
//     std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
//     auto duration_in_s = std::chrono::duration_cast<std::chrono::seconds>(time_now.time_since_epoch()).count();
//     auto duration_in_us = std::chrono::duration_cast<std::chrono::microseconds>(time_now.time_since_epoch()).count();
//     tv->tv_sec = duration_in_s;
//     tv->tv_usec = duration_in_us;
//     return 0;
// }
// #endif
#include <sys/time.h>

