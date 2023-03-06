#include <stdio.h>

namespace io_bench {
/* 随机读取磁盘 */
void read_randomly(char *address, long size/* length */, int fd);

/* 顺序读取磁盘 */
void read_sequentially(char *address, long size, int fd);

/* 顺序写磁盘 */
bool write_sequentially(char* data, long size, int fd);

/* 随机写磁盘 */
void write_randomly(char *data, long size, int fd);

/* 准备缓冲区 */
int *prepare_data(long size);

/* 打印结果 */
void print_result(double te, size_t mem_size);

} // namespace io_bench
