int poly(int *coef, int terms, int x)
{
    int power = 1;
    int value = 0;
    for (int j = 0; j < terms; j++)
    {
        value += coef[j] * power;
        power *= x;
    }
    return value;
}

int main()
{
    return 0;
}