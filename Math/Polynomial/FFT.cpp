typedef complex<double> Complex;

template<class T> int size(const T &a) {
    return a.size();
}

unsigned roundUp(unsigned v) {
    --v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return v + 1;
}

int reverse(int num, int lg) {
    int res = 0;
    for(int i = 0; i < lg; ++i) if(num & 1 << i)
        res |= 1 << (lg - i - 1);
    return res;
}

template<class T> ostream& operator << (ostream& out, const vector<T> &a) {
    for(int i = 0; i < size(a); ++i) {
        if(i > 0) out << ' ';
        out << a[i];
    }
    return out;
}

vector<Complex> fft(vector<Complex> a, bool invert) {
    int n = size(a), lg = 0;
    while(1 << lg < n) ++lg;
    vector<Complex> roots (n);
    for(int i = 0; i < n; ++i) {
        double alpha = 2 * M_PI / n * i * (invert ? -1 : 1);
        roots[i] = Complex(cos(alpha), sin(alpha));
    }
    for(int i = 0; i < n; ++i) {
        int rev = reverse(i, lg);
        if(i < rev) swap(a[i], a[rev]);
    }
    for(int len = 2; len <= n; len <<= 1)
        for(int i = 0; i < n; i += len)
            for(int j = 0; j < len >> 1; ++j) {
                Complex u = a[i + j], v = a[i + j + (len >> 1)] * roots[n / len * j];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }
    if(invert) for(int i = 0; i < n; ++i) a[i] /= n;
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
