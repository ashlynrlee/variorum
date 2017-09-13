#include <stdio.h>

#include <variorum.h>

#ifdef SECOND_RUN
inline double do_work(int input)
{
    int i;
    double result = (double)input;

    for (i = 0; i < 100000; i++)
    {
        result += i*result;
    }

    return result;
}
#endif

int main(int argc, char **argv)
{
    int ret;
#ifdef SECOND_RUN
    int i;
    int size = 1E3;
    double x = 0.0;
#endif

    ret = dump_power();
    if (ret != 0)
    {
        printf("Dump power failed!\n");
    }
#ifdef SECOND_RUN
    for (i = 0; i < size; i++)
    {
        x += do_work(i);
    }
    ret = dump_power();
    if (ret != 0)
    {
        printf("Dump power failed!\n");
    }
#endif
    return ret;
}