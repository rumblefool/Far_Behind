/*getchar_unlocked and putchar_unlocked doesn't work in windows (Codeforces);replace them with getchar and putchar
inline ll read() 
{
    ll n = 0;
    char c = getchar_unlocked();
    while (!('0' <= c && c <= '9')) 
    {
        c = getchar_unlocked();
    }
    while ('0' <= c && c <= '9') 
    {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}
inline void write(ll a)
{
    register char c;
    char snum[20];
    ll i=0;
    do
    {
        snum[i++]=a%10+48;
        a=a/10;
    }
    while(a!=0);
    i=i-1;
    while(i>=0)
        putchar_unlocked(snum[i--]);
    putchar_unlocked('\n');
}
