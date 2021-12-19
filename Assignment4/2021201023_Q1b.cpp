
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include<vector>
using namespace std;

#define MAX_N 100010          
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
{ 
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
            break; // nice optimization trick
    }
    computeLCP(n);
    return;
}
class deque{
    struct node{
        int data;
        struct node *next;
        struct node *prev;
        public:
        node(int d){
            data = d;
            next = NULL;
            prev = NULL;
        }
    };
    typedef struct node Node;
    Node *ffront,*rear;
    int size;
    public:
    deque(){
        ffront = rear =NULL;
        size =0;
    }
    void push_back(int d){
        if(rear==NULL){
            rear = new Node(d);
            ffront = rear;
        }
        else{
            Node* temp = new Node(d);
            temp->prev = rear;
            rear->next =temp;
            rear = temp;
        }
        size++;
    }
    void push_front(int d){
        if(ffront==NULL){
            ffront = new Node(d);
            rear=ffront;
        }
        else{
            Node* temp = new Node(d);
            temp->next = ffront;
            ffront->prev =temp;
            ffront = temp;
        }
        size++;
    }
    void pop_back(){
        if(ffront != rear){
            Node *temp = rear;
            temp->prev->next =NULL;
            rear = temp->prev;
            delete temp;
        }
        else{
            Node *temp = rear;
            ffront = rear = NULL;
            delete temp;
        }
        size--;
    }
    void pop_front(){
        if(ffront != rear){
            Node *temp = ffront;
            temp->next->prev =NULL;
            ffront = temp->next;
            delete temp;
        }
        else{
            Node *temp = ffront;
            ffront = rear = NULL;
            delete temp;
        }
        size--;
    }
    int front(){
        return ffront->data;
    }
    int back(){
        return rear->data;
    }
    bool empty(){
        return size == 0;
    }
};

int longestString(int n, int k) 
{ 
	deque myQueue; 
	int i;
    int maxLen=-1; 
	for (i = 0; i < k; ++i) { 
		
		while ((!myQueue.empty()) && LCP[i] <= LCP[myQueue.back()]) 
			myQueue.pop_back(); 

		myQueue.push_back(i); 
	} 

	for (; i < n; ++i) { 
		maxLen = max(maxLen,LCP[myQueue.front()]);

		while ((!myQueue.empty()) && myQueue.front() <= i - k) 
			myQueue.pop_front(); 

		while ((!myQueue.empty()) && LCP[i] <= LCP[myQueue.back()]) 
			myQueue.pop_back(); 

		myQueue.push_back(i); 
	} 

	maxLen = max(maxLen,LCP[myQueue.front()]);
    return maxLen==0?-1:maxLen;
} 

int main()
{
    int k;
    cin >> T;
    cin>>k;
    int n = strlen(T);
    T[n++] = '$';
    constructSA(n);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << SA[i] << "\t" << (T + SA[i]) << "\t" << LCP[i] << endl;
    // }
    T[n-1]='\0';
    if(k==1){
        cout<<strlen(T);
    }
    else{
        cout<<longestString(n,k-1);
    }
    return 0;
}
