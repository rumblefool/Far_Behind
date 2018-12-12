const int N=1000000, // set it more than 2*(len. of string)
string str;       // input string for which the suffix tree is being built
int chi[N][26],   
lef[N],   // left...
rig[N],   // ...and right boundaries of the substring of a which correspond to incoming edge
par[N],   // parent of the node
sfli[N],   // suffix link
tv,tp,la,     
ts;     // the number of nodes
     

void ukkadd(int c) { 
    suff:;      
    if (rig[tv]<tp) { 
        if (chi[tv][c]==-1) {chi[tv][c]=ts;lef[ts]=la;par[ts++]=tv;tv=sfli[tv];tp=rig[tv]+1;goto suff;}
        tv=chi[tv][c];tp=lef[tv];
    } 
    if (tp==-1 || c==str[tp]-'a')
        tp++; 
    else { 
        lef[ts]=lef[tv]; rig[ts]=tp-1; par[ts]=par[tv]; chi[ts][str[tp]-'a']=tv;
        chi[ts][c]=ts+1; lef[ts+1]=la; par[ts+1]=ts;
        lef[tv]=tp; par[tv]=ts; chi[par[ts]][str[lef[ts]]-'a']=ts; ts+=2;
        tv=sfli[par[ts-2]]; tp=lef[ts-2];
        while (tp <= rig[ts-2]) {tv=chi[tv][str[tp]-'a']; tp+=rig[tv]-lef[tv]+1;}
        if (tp == rig[ts-2]+1) sfli[ts-2]=tv; else sfli[ts-2]=ts; 
        tp=rig[tv]-(tp-rig[ts-2])+2;goto suff;
    }
}

void build() {
    ts=2;
    tv=0;
    tp=0;
    ll ss = str.size();ss*=2;ss+=15;
    fill(rig,rig+ss,(int)str.size()-1);
    // initialize data for the root of the tree
    sfli[0]=1;lef[0]=-1;
    rig[0]=-1;lef[1]=-1;rig[1]=-1;
    for(ll i=0;i<ss;i++)
        fill (chi[i], chi[i]+27, -1);
    fill(chi[1],chi[1]+26,0);
    // add the text to the tree, letter by letter
    for (la=0; la<(int)str.size(); ++la)
        ukkadd (str[la]-'a');
}