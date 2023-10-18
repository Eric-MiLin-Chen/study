#include <immintrin.h>

void sinx(int N, int terms, float *x, float *result)
{
    float three_fact = 6; // 3!
    for (int i = 0; i < N; i += 8)
    {
        __m256 origx = _mm256_load_ps(&x[i]);
        __m256 value = origx;
        __m256 numer = _mm256_mul_ps(origx, _mm256_mul_ps(origx, origx));
        __m256 denom = _mm256_broadcast_ss(&three_fact);
        int sign = -1;
        for (int j = 1; j <= terms; j++)
        {
            // value +=  sign * numer / denom
            __m256 tmp = _mm256_div_ps(_mm256_mul_ps(_mm256_set1ps(sign), numer), denom);
            value = _mm256_add_ps(value, tmp);
            numer = _mm256_mul_ps(numer, _mm256_mul_ps(origx, origx));
            denom = _mm256_mul_ps(denom, _mm256_broadcast_ss((2.0 * j + 2.0) * (2.0 * j + 3.0)));
            sign *= -1;
        }
        _mm256_store_ps(&result[i], value);
    }
}