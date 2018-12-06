    
vpll v[MAX];vll cap(1,0),capI(1,0);ll vis[MAX];ll cue=0;
ll prev1[MAX];ll psi[MAX];
void dfs(ll x){
    if(vis[x]==cue)return;
    vis[x]=cue;if(x==N){return;}
    ll a,b,c,i,j;
    for(j=0;j<5;j++){
        a=rand()%(v[x].size());
        b=v[x][a].F;if(vis[b]==cue)continue;
        c=v[x][a].S;
        if(c<0&&capI[-c]==0)continue;else if(c>0&&cap[c]==0)continue;
        prev1[b]=x;
        psi[b]=v[x][a].S;
        dfs(b);if(vis[N]==cue)return;
    }
    for(auto z:v[x]){
        b=z.F;if(vis[b]==cue)continue;
        c=z.S;//trace(b,c);
        if(c<0&&capI[-c]==0)continue;else if(c>0&&cap[c]==0)continue;
        prev1[b]=x;
        psi[b]=z.S;
        dfs(b);if(vis[N]==cue)return;
    }
}
for(i=1;i<=n;i++){
    ++D;v[0].pb({i,D});v[i].pb({0,-D});
    cap.pb(1);capI.pb(0);
}
for(j=n+1;j<=n+m;j++){
    ++D;v[j].pb({N,D});v[N].pb({j,-D});
    cap.pb(1);capI.pb(0); 
}    
ll maxf=0;
while(true){
    cue++;dfs(0);
    if(vis[N]!=cue)break;
    a=N;  maxf++;
    while(a!=0){
        c=psi[a];//trace(a,c);
        if(c>0){cap[c]--;capI[c]++;}
        else {capI[-c]--;cap[-c]++;}
        a=prev1[a];
    }
}
cout<<maxf<<"\n";