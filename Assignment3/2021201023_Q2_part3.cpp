
//NOT strong code

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
int min4(int a, int b, int c, int d){
    int x;
    x=min(a,min(b,min(c,d)));
    return x;
}
int mincost( vector<vector<int>> &graph,vector<vector<bool>>&p, int i , int j,int r, int c){
    p[i][j]=true;
    if(i==1 && j==0){
        return 0;
    }
    if(graph[i][j] == 0){
        int w,x,y,z;
        w=x=y=z=INT_MAX;
        if(j-1>=0 && !p[i][j-1]){
            x=mincost(graph,p,i,j-1,r,c);
            if(x==-1)
                x=INT_MAX;
        }
        if(i-1>=0 && !p[i-1][j]){
            y=mincost(graph,p,i-1,j,r,c);
            if(y==-1)
                y=INT_MAX;
        }
        if(i+1<r && !p[i+1][j]){
            z=mincost(graph,p,i+1,j,r,c);
            if(z==-1)
                z=INT_MAX;
        }
        if(j+1<c && !p[i][j+1]){
            w=mincost(graph,p,i,j+1,r,c);
            if(w==-1)
                w=INT_MAX;
        }
        int m=min4(w,x,y,z);
        if(m==INT_MAX){
            p[i][j]=false;
            return -1;
        }
        else{
            graph[i][j]=1+m;
        }
        
    }
    p[i][j]=false;
    return graph[i][j];
}
int main(){
    int r,c;
    cin>>r>>c;
    vector<vector<int>> graph(r,vector<int>(c));
    vector<vector<bool>> p(r,vector<bool>(c,false));
    char ch;
    vector<pair<int,int>> rider;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>ch;
            if(ch=='R'){
                rider.push_back(make_pair(i,j));
                graph[i][j]=0;
            }
            else if(ch=='#'){
                graph[i][j]=-1;
            }
            else{
                graph[i][j]=0;
            }
        }
    }
    
    graph[1][0]=0;
  
    int l=mincost(graph,p,r-2,c-2,r,c);
    
    int op=0;
    for(int i=0;i<rider.size();i++){
        op=mincost(graph,p,rider[i].first,rider[i].second,r,c);
        if(op>-1 && op<l){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
           cout<< graph[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"YES"<<endl;
    cout<<l<<endl;
    return 0;
}