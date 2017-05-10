const double PI = acos(-1.0);
typedef complex<double> Complex;

#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x) >> (i)) & 1)
#define LOG  17
Complex fftRoot[MASK(LOG)], invRoot[MASK(LOG)];

#define REP(i, n) for (int i = 0, _n = (n); i < _n; i = i + 1)
void initFFT(void) {
	REP(i, MASK(LOG)) {
		double alpha = 2 * PI / MASK(LOG) * i;
		fftRoot[i] = Complex(cos(alpha), sin(alpha));
		invRoot[i] = Complex(cos(-alpha), sin(-alpha));
	}
}

unsigned roundUp(unsigned v) {
    --v;
    REP(i, 5) v |= v >> MASK(i);
    return v + 1;
}

int reverse(int num, int lg) {
    int res = 0;
    REP(i, lg) if (BIT(num, i)) res |= MASK(lg - i - 1);
    return res;
}

vector<Complex> fft(vector<Complex> a, bool invert) {
    int n = a.size(), lg = 0;
    while (MASK(lg) < n) lg++;

    vector<Complex> roots(n);
    REP(i, n) roots[i] = invert ? invRoot[MASK(LOG) / n * i] : fftRoot[MASK(LOG) / n * i];

    REP(i, n) {
        int rev = reverse(i, lg);
        if (i < rev) swap(a[i], a[rev]);
    }

    for (int len = 2; len <= n; len <<= 1)
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < (len >> 1); j++) {
                Complex u = a[ i + j], v = a[i + j + (len >> 1)] * roots[n / len * j];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }

    if (invert) REP(i, n) a[i] /= n;
    return a;
}

vector<long long> multiply(const vector<int> &a, const vector<int> &b) {
    int n = roundUp(size(a) + size(b) - 1);
    vector<Complex> pa (n), pb (n);
    for(int i = 0; i < size(a); ++i) pa[i] = a[i];
    for(int i = 0; i < size(b); ++i) pb[i] = b[i];
    pa = fft(pa, false); pb = fft(pb, false);
    for(int i = 0; i < n; ++i) pa[i] *= pb[i];
    pa = fft(pa, true);
    vector<long long> res (n);
    for(int i = 0; i < n; ++i) res[i] = round(real(pa[i]));
    return res;
}
