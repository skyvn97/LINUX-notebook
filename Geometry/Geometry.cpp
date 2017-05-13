#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)n;++i)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()
#define chmax(a,b) (a<b?(a=b,1):0)
#define chmin(a,b) (a>b?(a=b,1):0)
#define valid(y,x,h,w) (0<=y&&y<h&&0<=x&&x<w)
typedef long long ll;
typedef pair<int,int> pii;
const int INF = 1<<29;
const double PI = acos(-1);
const double EPS = 1e-8;

typedef complex<double> P;
namespace std {
    bool operator < (const P& a, const P& b) {
        // if (abs(a-b)<EPS) return 0;
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}

/* Notes
    norm(x) = x.real() ^ 2 + x.imag() * 2
    cross(a, b) = a.x * b.y - b.x * a.y    
    dot(a, b) = a.x * b.x + a.y * b.y
*/

double cross(const P& a, const P& b) {
    return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
    return real(conj(a)*b);
}
struct L : public vector<P> {
    L(const P &a, const P &b) {
        push_back(a); push_back(b);
    }
    L() {}
};
typedef vector<P> G;
#define curr(P, i) P[i]
#define next(P, i) P[(i+1)%P.size()]
struct C {
    P p; double r;
    C(const P &p, double r) : p(p), r(r) { }
};

int ccw(P a, P b, P c) {
    b -= a; c -= a;
    if (cross(b, c) > 0)   return +1;       // counter clockwise
    if (cross(b, c) < 0)   return -1;       // clockwise
    if (dot(b, c) < 0)     return +2;       // c--a--b on line
    if (norm(b) < norm(c)) return -2;       // a--b--c on line
    return 0;
}

bool intersectLL(const L &l, const L &m) {
    return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
        abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS(const L &l, const L &s) {
    return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
        cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const L &l, const P &p) {
    return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS(const L &s, const L &t) {
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSS2(const L &s, const L &t) { // 0 if touching
    REP(i, 2) {
        if (ccw(s[0], s[1], t[i]) == 0) {
            int c = ccw(s[0],s[1],t[!i]);
            if (s[0] == t[i]) {
                if (c!=-2&&c) return 0;
            } else if (s[1] == t[i]) {
                if (c!=2&&c) return 0;
            } else if (abs(c)==1) return 0;
        }
    }
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const L &s, const P &p) {
    return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

P projection(const L &l, const P &p) {
    double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
    return l[0] + t*(l[0]-l[1]);
}
P reflection(const L &l, const P &p) {
    return p + P(2,0) * (projection(l, p) - p);
}
double distanceLP(const L &l, const P &p) {
    return abs(p - projection(l, p));
}
double distanceLL(const L &l, const L &m) {
    return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double istanceLS(const L &l, const L &s) {
    if (intersectLS(l, s)) return 0;
    return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const L &s, const P &p) {
    const P r = projection(s, p);
    if (intersectSP(s, r)) return abs(r - p);
    return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const L &s, const L &t) {
    if (intersectSS(s, t)) return 0;
    return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
            min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
P crosspoint(const L &l, const L &m) {
    double A = cross(l[1] - l[0], m[1] - m[0]);
    double B = cross(l[1] - l[0], l[1] - m[0]);
    if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
    if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
    return m[0] + B / A * (m[1] - m[0]);
}
double area(const G& g) {
    double A = 0;
    for (int i = 0; i < g.size(); ++i) {
        A += cross(g[i], next(g, i));
    }
    return abs(A/2);
}

G convex_cut(const G& g, const L& l) {
    G Q;
    REP(i, g.size()) {
        P A = curr(g, i), B = next(g, i);
        if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
        if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0)
            Q.push_back(crosspoint(L(A, B), l));
    }
    return Q;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// Centroid of a polygon
P centroid(const vector<P> &v) {
    double S = 0;
    P res;
    REP(i,v.size()) {
        int j = i+1;
        if (j == v.size()) j = 0;
        double tmp = cross(v[i], v[j]);
        S += tmp;
        res += (v[i] + v[j]) * tmp;
    }
    S /= 2;
    res /= 6*S;
    return res;
}

double manDistanceSP(const L &l, const P &p) {
    double res = INF;
    L xl = L(p, p + P(1,0));
    if (intersectLS(xl, l)){
        P cp = crosspoint(xl, l);
        double d = abs(p-cp);
        res = min(res, d);
    }
    L yl = L(p, p + P(0,1));
    if (intersectLS(yl, l)) {
        P cp = crosspoint(yl, l);
        double d = abs(p-cp);
        res = min(res, d);
    }
    res = min(res, abs(l[0].real()-p.real()) + abs(l[0].imag()-p.imag()));
    res = min(res, abs(l[1].real()-p.real()) + abs(l[1].imag()-p.imag()));
    return res;
}

// Check if a (counter-clockwise) convex polygoncontains a point
bool convex_contain(const G &g, const P &p) {
    REP(i,g.size())
        if (ccw(g[i], next(g, i), p) == -1) return 0;
    return 1;
}
// Check if two polygons have common point
bool intersectGG(const G &g1, const G &g2) {
    if (convex_contain(g1, g2[0])) return 1;
    if (convex_contain(g2, g1[0])) return 1;
    REP(i,g1.size()) REP(j,g2.size()) {
        if (intersectSS(L(g1[i], next(g1, i)), L(g2[j],next(g2, j)))) return 1;
    }
    return 0;
}
// Distance between a point and a polygon
double distanceGP(const G &g, const P &p) {
    if (convex_contain(g, p)) return 0;
    double res = INF;
    REP(i, g.size()) {
        res = min(res, distanceSP(L(g[i], next(g, i)), p));
    }
    return res;
}
// Duong phan giac
L bisector(const P &a, const P &b) {
    P A = (a+b)*P(0.5,0);
    return L(A, A+(b-a)*P(0, PI/2));
}
// Voronoi
G voronoi_cell(G g, const vector<P> &v, int s) {
    REP(i, v.size())
        if (i!=s)
            g = convex_cut(g, bisector(v[s], v[i]));
    return g;
}
// Angle-related
double angle(const P &a, const P &b) { // Goc dinh huong a -> b [0,2pi)
    double ret = arg(b)-arg(a);
    return (ret>=0) ? ret : ret + 2*PI;
}
double angle2(const P &a, const P &b) { // Goc giua a va b
    return min(angle(a,b), angle(b,a));
}
double rtod(double rad) { // Radian to degree
    return rad*180/PI;
}
double dtor(double deg) { // Degree to radian
    return deg*PI/180;
}
// Rotation
P rotate(P p, double ang) {
    return p * P(cos(ang), sin(ang));
}
// Rotate a line around O
L rotate(L l, double ang) {
    return L(rotate(l[0], ang),rotate(l[1], ang));
}
