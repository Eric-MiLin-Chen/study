#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 100010 * 4;
const double pi = acos(-1);
string s;
int i, j, n, m, limit, ans, r[MAXN], Ans[MAXN], T;
char C[4] = {'A', 'T', 'C', 'G'};

struct complex
{
	double real, imag;
	complex(double _real = 0, double _imag = 0)
	{
		real = _real;
		imag = _imag;
	}
} a[MAXN], b[MAXN];

inline complex operator+(complex a, complex b) { return complex(a.real + b.real, a.imag + b.imag); }
inline complex operator-(complex a, complex b) { return complex(a.real - b.real, a.imag - b.imag); }
inline complex operator*(complex a, complex b) { return complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real); }

void FFT(ll limit, complex *a, ll op) // 迭代版
{
	for (ll i = 0; i < limit; i++)
	{
		if (i < r[i])
			swap(a[i], a[r[i]]);
	}
	for (ll mid = 1; mid < limit; mid <<= 1)
	{
		complex W(cos(pi / mid), op * sin(pi / mid));
		for (ll k = mid << 1, j = 0; j < limit; j += k)
		{
			complex w(1, 0);
			for (ll l = 0; l < mid; l++, w = w * W)
			{
				complex x = a[j + l], y = w * a[j + mid + l];
				a[j + l] = x + y;
				a[j + mid + l] = x - y;
			}
		}
	}
}

void Fast_Fast_TLE(string S, string T)
{
	for (j = 0; j < n; j++)
		a[j] = (complex){(double)(S[j] == C[i]), 0};
	for (j = 0; j < m; j++)
		b[m - j - 1] = (complex){(double)(T[j] == C[i]), 0};
	limit = 1;
	ll l = 0;
	while (limit <= n + m)
	{
		limit <<= 1;
		l++;
	}
	for (ll i = 0; i < limit; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	FFT(limit, a, 1);
	FFT(limit, b, 1);
	for (ll i = 0; i < limit; i++) //
		a[i] = a[i] * b[i];
	FFT(limit, a, -1);
}

int main()
{
	cin >> T;
	while (T--)
	{
		memset(Ans, 0, sizeof(Ans));
		ans = 0;
		string S, T;
		cin >> S >> T;
		n = S.size();
		m = T.size();
		for (i = 0; i < 4; i++)
		{
			Fast_Fast_TLE(S, T);
			// FFT板子
			for (j = m - 1; j <= m + n - 1; j++)
				Ans[j - (m - 1)] += ((int)(a[j].real / limit + 0.5));
			for (j = 0; j < limit; j++)
				a[j] = b[j] = (complex){0, 0};
		}
		for (i = 0; i < n - m + 1; i++)
			if (Ans[i] + 3 >= m)
				++ans;
		cout << ans << endl;
	}
	return 0;
}