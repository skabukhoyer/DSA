
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include<vector>
using namespace std;

#define MAX_N 200010         
char T[MAX_N];                
int n;                        
int RA[MAX_N], tempRA[MAX_N]; 
int SA[MAX_N], tempSA[MAX_N]; 
int c[MAX_N];
int Phi[MAX_N], PLCP[MAX_N], LCP[MAX_N];

void computeLCP(int n)
{
    int i, L;
    Phi[SA[0]] = -1;            
    for (i = 1; i < n; i++)     
        Phi[SA[i]] = SA[i - 1]; 
    for (i = L = 0; i < n; i++)
    { 
        if (Phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        } // special case
        while (T[i + L] == T[Phi[i] + L])
            L++; 
        PLCP[i] = L;
        L = max(L - 1, 0); 
    }
    for (i = 0; i < n; i++)   
        LCP[i] = PLCP[SA[i]]; 
    return;
}


void countingSort(int k, int n)
{                                      
    int i, sum, maxi = max(300, n);   
    memset(c, 0, MAX_N * sizeof(int)); 
    for (i = 0; i < n; i++)            
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++)
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) 
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++) 
        SA[i] = tempSA[i];

    return;
}

void constructSA(int n)
{ // this version can go up to 100000 characters
    int r;
    for (int i = 0; i < n; i++)
    {
        RA[i] = T[i];
    }

    for (int i = 0; i < n; i++)
    {
        SA[i] = i;
    }

    for (int k = 1; k < n; k <<= 1)
    { 
       
        countingSort(k, n);
        countingSort(0, n);        
        tempRA[SA[0]] = r = 0;      
        for (int i = 1; i < n; i++) 
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (int i = 0; i < n; i++) 
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break; 
    }
    computeLCP(n);
    return;
}
int main()
{
    string s;
    cin>>s;
    string sm = s;
    reverse(sm.begin(),sm.end());
    int len = s.size();
    string res = s+"$"+sm+"#";
   
    strcpy(T,res.c_str());
    n = strlen(T);
    constructSA(n);
    string inp = T;
    string ans;
    int maxlen = 0;
    int t=0,index=-1;
    for(int i=1;i<n;i++){
        if((SA[i]<len && SA[i-1]>len)||(SA[i]>len && SA[i-1]<len)){
            ans = "";
            ans = inp.substr(SA[i],LCP[i]);
            int sk = ans.size();
            int flag =0;
            for(int i=0;i<sk/2;i++){
                if(ans[i]!=ans[sk-i-1]){
                    flag = 1;
                }
            }
            
            if(flag !=1){
                t =max(maxlen,LCP[i]);
                if(t!=maxlen) {
                    maxlen = t;
                    index = SA[i];

                }
            }
          
        }
    }
    char result[MAX_N] ;
    memset(result,'\0',sizeof(result));
    strncpy(result,T+index,maxlen);
    cout<<result;
    return 0;
}