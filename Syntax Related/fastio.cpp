/*getchar_unlocked and putchar_unlocked doesn't work in windows (Codeforces);replace them with getchar and putchar*/
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

inline void fastRead_string(char *str)
{
    char c = 0;
    int i = 0;

    while (c < 33)
        c = getchar_unlocked();

    while (c != '\n') {
        str[i] = c;
        c = getchar_unlocked();
        i = i + 1;
    }
    // getchar_unlocked returns -1 on EOF
    str[i] = '\0';
}
// use
char s[100];
fastRead_string(s);
printf("%s\n", s);
