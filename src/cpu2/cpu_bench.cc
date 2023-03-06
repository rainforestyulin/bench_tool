#include "cpu_bench.h"
#include "../platform.h"

#include <iostream>

namespace cpu_bench{

void runner(long num)
{
    int current_num = 0;
    unsigned long val = 2;
    while(current_num != num)
    {
        long i = 2;
        for (; i < val; ++i)
        {
            if( val%i==0 )
            {
                break;
            }
        }
        if(i == val)
        {
            ++current_num;
        }
        val++;
    }
}
double run_time(long num)
{
    struct timeval starttime, endtime;
    gettimeofday(&starttime, 0);
    runner(num);
    gettimeofday(&endtime, 0);
    double te = (static_cast<double>(endtime.tv_sec*1000000 - starttime.tv_sec*1000000 + endtime.tv_usec - starttime.tv_usec))/1000000;
    return te;
}
void print_result(double te, long numb)
{
    printf("Runtime: %.5f\t", te);
    printf("Primenumber: %ld\t",numb);
    printf("Calculatespeed: %.5f Prime/s\n",static_cast<double>(numb)/te);
}

}   // namespace cpu_bench

