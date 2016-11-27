int roundCount(int round) {
    return (6*round);
}
int roundSum(int round) {
    return (6*round*(round+1)/2);
}
int findRound(int n) {
    int res=1;
    while (roundSum(res)<n) res++;
    return (res);
}
pair<int,int> cord(int n) {
    if (n==0) return (make_pair(0,0));
    int c=findRound(n);
    int prev=roundSum(c-1);
    if (n<=prev+c) return (make_pair(c,n-prev));
    if (n<=prev+2*c) return (make_pair(prev+2*c-n,c));
    if (n<=prev+3*c) return (make_pair(prev+2*c-n,prev+3*c-n));
    if (n<=prev+4*c) return (make_pair(-c,prev+3*c-n));
    if (n<=prev+5*c) return (make_pair(n-prev-5*c,-c));
    return (make_pair(n-prev-5*c,n-prev-6*c));
}
bool inRound(int x,int y,int c) {
    if (0<=y && y<=c && x==c) return (true);
    if (0<=x && x<=c && y==c) return (true);
    if (0<=y && y<=c && y-x==c) return (true);
    if (-c<=y && y<=0 && x==-c) return (true);
    if (-c<=x && x<=0 && y==-c) return (true);
    if (0<=x && x<=c && x-y==c) return (true);
    return (false);
}
int findRound(int x,int y) {
    int res=1;
    while (!inRound(x,y,res)) res++;
    return (res);
}
int number(int x,int y) {
    if (x==0 && y==0) return (0);
    int c=findRound(x,y);
    int prev=roundSum(c-1);
    if (1<=y && y<=c && x==c) return (prev+y);
    if (0<=x && x<=c && y==c) return (prev+2*c-x);
    if (0<=y && y<=c && y-x==c) return (prev+2*c-x);
    if (-c<=y && y<=0 && x==-c) return (prev+3*c-y);
    if (-c<=x && x<=0 && y==-c) return (prev+5*c+x);
    return (prev+5*c+x);
}
