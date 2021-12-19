
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<string.h>

using namespace std;

#define MAX_N 2000010                       
char T[MAX_N];                              
int n;                                      
int RA[MAX_N], tempRA[MAX_N];               
int SA[MAX_N], tempSA[MAX_N];              
int c[MAX_N];                               
void countingSort(int k,int n)
{                                           
    int i, sum, maxi = max(300, n);        
    memset(c, 0, MAX_N*sizeof(int));         
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
     
    return ;
}

void constructSA(int n)
{                                                      
    int r;
    for (int i = 0; i < n; i++){
        RA[i] = T[i];
    }  
                                
    for (int i = 0; i < n; i++){
        SA[i] = i; 
    } 
                                                 
    
    for (int k = 1; k < n; k <<= 1)
    {                                                   
        countingSort(k,n);   
        countingSort(0,n);                               
        tempRA[SA[0]] = r = 0;                          
        for (int i = 1; i < n; i++)                        
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (int i = 0; i < n; i++)                         
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break;                                      
    }
    return ;
}
int main()
{
    cin >> T;
    int len = strlen(T);
    char temp[1000010];
    strcpy(temp,T);
    strcat(T,temp);
    n = strlen(T);
    T[n++]='$';
    constructSA(n);
   
    for(int i=0;i<n;i++){
        if(SA[i]<len){
            strncpy(temp,T+SA[i],len);
            break;
        }
    }
    cout<<temp<<endl;
    return 0;
}