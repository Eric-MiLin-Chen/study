#include <thread>
#include <iostream>
#include <time.h>

const float PI = 3.1415926;

typedef struct
{
    int N;
    int terms;
    float *x;
    float *y;
} my_args;

void sinx(int N, int terms, float *x, float *y)
{
    for (int i = 0; i < N; i++)
    {
        float value = x[i];
        float numer = x[i] * x[i] * x[i];
        int denom = 6; // 3!
        int sign = -1;
        for (int j = 1; j <= terms; j++)
        {
            value += sign * numer / denom;
            numer *= x[i] * x[i];
            denom *= (2 * j + 2) * (2 * j + 3);
            sign *= -1;
        }
        y[i] = value;
    }
}

void my_thread_func(my_args *args)
{
    sinx(args->N, args->terms, args->x, args->y); // do work
}

void parallel_sinx(int N, int terms, float *x, float *y)
{
    std::thread my_thread;
    my_args args;
    args.N = N / 2;
    args.terms = terms;
    args.x = x;
    args.y = y;
    my_thread = std::thread(my_thread_func, &args);  // launch thread
    sinx(N - args.N, terms, x + args.N, y + args.N); // do work on main thread
    my_thread.join();                                // wait for thread to complete
}

int main()
{
    my_args args;
    args.N = 360;
    args.terms = 6;
    args.x = new float[args.N];
    args.y = new float[args.N];
    for (int i = 0; i < args.N; i++)
        args.x[i] = i * PI / 180;
    // for (int i = 0; i < args.N; i++)
    //     std::cout << *(args.x + i) << std::endl;
    clock_t start, end;
    // start = clock();
    // sinx(args.N, args.terms, args.x, args.y);
    // end = clock();
    // std::cout << "time of sinx = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    start = clock();
    parallel_sinx(args.N, args.terms, args.x, args.y);
    end = clock();
    std::cout << "time of parallel_sinx = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    // for (int i = 0; i < args.N; i++)
    //     std::cout << *(args.y + i) << std::endl;
    delete args.x;
    delete args.y;
    return 0;
}