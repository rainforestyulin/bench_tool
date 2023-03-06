#include "simple_vector.cc"
 #include "../platform.h"

#include <memory>
#include <string>
#include <cstring>
#include <unistd.h>
#include <exception>

namespace memory_bench{
void print_result(double te, size_t mem_size)
{
    printf("Time_cost: %.5fs\t",te);
    printf("Memory_size: %.5fMiB\t",static_cast<double>(mem_size/1024/1024));
    printf("WR_speed: %.3f MiB/s\n" , mem_size/1024/1024/te);
    return;
}
void print_result2(double te, size_t mem_size)
{
    printf("Time_cost: %.5fs\t",te);
    printf("Memory_size: %.5fMiB\t",static_cast<double>(mem_size/1024/1024));
    printf("WR_speed: %.3f GiB/s\n" ,static_cast<double>(mem_size/1024/1024)/1024/te);
    return;
}

template <typename T>
double run_time_rand(size_t mem_size)
{
    // SimpleVedtor<T> mvector;
    // v2改动：跳过数据结构，直接对内存进行操作
    std::allocator<T> alloc;
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    auto mem_pool_p = alloc.allocate(mem_size/sizeof(T));
    auto mem_p_temp = mem_pool_p;
    for (size_t i = 0; i < mem_size/sizeof(T); ++i)
    {
        // mvector.push_back(0);
        alloc.construct(mem_pool_p + rand()%(mem_size/sizeof(T)), i);
    }
    // for (size_t i = 0; i < mem_size; ++i)
    // {
    //     mvector.pop_back();
    // }
    alloc.deallocate(mem_p_temp, mem_size/sizeof(T));
    gettimeofday(&endtime, 0);
    double te = (static_cast<double>(endtime.tv_sec*1000000 - starttime.tv_sec*1000000 + endtime.tv_usec - starttime.tv_usec))/1000000;
    return te;
}

template <typename T>
double run_time_seq(size_t mem_size)
{
    struct timeval starttime, endtime;
    T *a = (T*)malloc(mem_size);
    T *b = (T*)malloc(mem_size);
    if(!a || !b) return -1;
    memset(a, 0x10, mem_size);
    memset(b, 0x11, mem_size);
    gettimeofday(&starttime, 0);
    memcpy(a, b, mem_size);
    gettimeofday(&endtime, 0);
    free(a);
    free(b);
    double te = (static_cast<double>(endtime.tv_sec*1000000 - starttime.tv_sec*1000000 + endtime.tv_usec - starttime.tv_usec))/1000000;
    return te;
}

}

