#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include "../platform.h"

namespace io_bench
{

inline double time_deal(struct timeval &s, struct timeval &e)
{
    return
     (static_cast<double>(e.tv_sec*1000000 -
                          s.tv_sec*1000000 + e.tv_usec - s.tv_usec))/1000000;
}

long randm(long size)
{
    return rand()%size;
}

double read_randomly(char *address, long size, int fd)
{
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    for (size_t i = 0; i < size; ++i)
    {
        lseek(fd, randm(size), SEEK_SET);
        read(fd, address+i, 1);
    }
    gettimeofday(&endtime, 0);
    return time_deal(starttime, endtime);

};

double read_sequnetially(char *address,long size, int fd)
{
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    for (size_t i = 0; i < size; ++i)
    {
        randm(size);
        continue;
    }
    gettimeofday(&endtime, 0);
    read(fd, address, size);
    return time_deal(starttime, endtime);
}

char *prepare_data(long size)
{
    char  *data = (char*)malloc(sizeof(char)*size);
    memset(data,0xe, size);
    return data;
}

double  write_randomly(char *data, long size, int fd)
{
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    for (size_t i = 0; i < size; ++i)
    {
        lseek(fd, i, SEEK_SET);
       // lseek(fd, randm(size), SEEK_SET);
       write(fd, data + i, 1);
    }
    gettimeofday(&endtime, 0);
    return time_deal(starttime, endtime);

}

double write_sequentially(char *data, long size, int fd)
{
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    for (size_t i = 0; i < size; ++i)
    {
        randm(size);
        continue;
    }
    write(fd, data, size);
    gettimeofday(&endtime, 0);
    return time_deal(starttime, endtime);
}

void print_result(double te, size_t mem_size)
{
    printf("Time_cost: %.5fs\t",te);
    printf("File_size: %.5fMiB\t",static_cast<double>(mem_size/1024/1024));
    printf("Speed: %.3f MiB/s\n" , mem_size/1024/1024/te);
    return;
}

} // namespace io_bench

