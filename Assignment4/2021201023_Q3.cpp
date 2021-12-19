#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;

class Trie{
    struct node{
        struct node *left;  //for 0 bit
        struct node *right; //for 1 bit
        public:
        node(){
            left = NULL;
            right = NULL;
        }
    };
    typedef struct node Node;

    Node *root;

    public:
        Trie(){
            root = new Node();
        }
        void insert(long long int val){
            Node *temp = root;
            for(int i=62;i>=0;i--){
                long long int mask = 1<<i;
                if(val & mask){
                    if(temp->right == NULL){
                        temp->right = new Node();
                       
                    }
                    temp = temp->right;
                }
                else{
                    if(temp->left == NULL){
                        temp->left = new Node();
                    }
                    temp =temp->left;
                }
            }
        }
        long long int findMaxXor(long long int val){
           long long int find = val ^ LLONG_MAX;
          
            Node *temp = root;
            long long int ans =0;
            int bit;
            for(int i=62;i>=0;i--){
              long long int  mask = 1<<i;
                bit = (find & mask)>0?1:0;
                if(bit == 0){
                    if(temp->left == NULL){
                        ans |= mask;
                        temp = temp->right;
                    }
                    else{
                        temp = temp->left;
                    }
                }
                else{
                    if(temp->right == NULL){
                        
                        temp = temp->left;
                    }
                    else{
                        ans |=mask;
                        temp = temp->right;
                    }  
                }
            }
            return ans;
        }
};


int main(){
    int n,q;
    cin>>n>>q;
    vector<long long int>arr(n);
    Trie T;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        T.insert(arr[i]);
    }
    vector<long long int>query(q);
    for(int i=0;i<q;i++){
        cin>>query[i];
    }

    for(int i=0;i<q;i++){
        long long int value = T.findMaxXor(query[i]);
        cout<<(value^query[i])<<endl;

    }
    return 0;
}