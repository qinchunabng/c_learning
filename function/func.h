#ifndef FUNC_H__

#define M 3
#define N 4

void print_2d_array(int *p, int n);

void test_n();

void print_2d_array1(int (*p)[N], int m, int n);

/**
 * 指针函数，返回一个指针
 */
int *find_num(int (*p)[N], int num);

int add(int a, int b);

int sub(int a, int b);

#endif