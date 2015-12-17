#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "label.h"
#include <string>

label_t *l = NULL;
std::string s;

#define ITER_NUM 10000

LARGE_INTEGER freq;
LARGE_INTEGER start, end;

struct test_data_t
{
    double mean;
};
typedef struct test_data_t test_data_t;

double one_test(void (*func)())
{
    QueryPerformanceCounter(&start);
    func();
    QueryPerformanceCounter(&end);
    return (end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}


test_data_t test(void (*func)())
{
    test_data_t data;

    double sum = 0.0;
    for (size_t i = 0; i < ITER_NUM; i++) {
        sum += one_test(func);
    }

    data.mean = sum / ITER_NUM;
    return data;
}

void test_1()
{
    l = label_create();
    label_set(l, ";asdjfa;lsf;lasjdf;alsjdf;lakjsd;fklasd;j");
    for (size_t i = 0; i < 1000; i++) {
        label_append_str(l, "zozozozofdjskjfljdflksjdflksjd");
    }
    label_kill(l);
}

void test_2()
{
    s = "";
    s = ";asdjfa;lsf;lasjdf;alsjdf;lakjsd;fklasd;j";
    for (size_t i = 0; i < 1000; i++) {
        s.append("zozozozofdjskjfljdflksjdflksjd");
    }
}

int main()
{
    test_data_t data;

    QueryPerformanceFrequency(&freq);

    data = test(test_1);
    printf("Mean: %e\n", data.mean);

    data = test(test_2);
    printf("Mean: %e\n", data.mean);


}