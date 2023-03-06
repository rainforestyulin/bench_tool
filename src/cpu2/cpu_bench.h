namespace cpu_bench {

/* 素数运算，找到n个素数后退出 */
void runner(long num);

/* 指定需要找到的素数个数num，返回完成的时长/s */
double run_time(long num);

/* 打印结果 */
void print_result(double te, long numb);

} // namespace cpu_bench
