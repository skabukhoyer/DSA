#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<limits>
//#include<bits/stdc++.h>

using namespace std;
 
class Trie{
    struct node{
        char data;
        int isWord;
        struct node* child[26];
        public:
        node(char ch){
            data=ch;
            isWord=0;
            for(int i=0;i<26;i++)
                child[i]=NULL;
        }
    };
    typedef struct node Node;
    Node *root;

    public:
    Trie(){
        root= new Node('\0');
    }
    void insertNode(string s){
        Node *temp=root;
        for(int i=0;i<s.size();i++){
            if(temp->child[s[i]-'a']==NULL){
                temp->child[s[i]-'a'] = new Node(s[i]);
            }
            temp=temp->child[s[i]-'a'];
        }
        temp->isWord +=1;
    }
    bool spellCheck(string s){
        Node *temp=root;
        for(int i=0;i<s.size();i++){
            if(temp->child[s[i]-'a']==NULL){
               return false;
            }
            temp=temp->child[s[i]-'a'];
        }
        if(temp->isWord >=1){
            return true;
        }
        return false;
    }
    vector<string> autocomplete(string s){
        vector<string> out;
        Node *temp=root;
        for(int i=0;i<s.size();i++){
            if(temp->child[s[i]-'a']==NULL){
               return out;
            }
            temp=temp->child[s[i]-'a']; 
        }
        if(temp->isWord>=1){
            out.push_back(s);
        }
       // string dup=s;
        for(int i=0;i<26;i++){
            if(temp->child[i] !=NULL){
                beginWith(out, temp->child[i], s);
            }
        }
        return out;
    }
    vector<string> autocorrect(string s){
        vector<string> out;
        Node *temp=root;
        string str;
        for(int i=0;i<26;i++){
            str="";
            if(temp->child[i] != NULL){
               traverse(temp->child[i],s,str,out);
            }
        }

        return out;
    }
    private:
    void traverse( Node *temp, string original, string str , vector<string> &out){
        str.push_back(temp->data);
        if(temp->isWord >= 1){
            if(levenshteinDistance(original, str) <= 3)
                out.push_back(str);
        }
        for(int i=0;i<26;i++){
            if(temp->child[i] !=NULL){
                traverse(temp->child[i], original, str , out);
            }
        }
    }
    void beginWith(vector<string> &out, Node *temp, string s){
        s.push_back(temp->data);
        if(temp->isWord >= 1){
            out.push_back(s);
        }
        for(int i=0;i<26;i++){
            if(temp->child[i] !=NULL){
                beginWith(out, temp->child[i], s);
            }
        }
    }
    int levenshteinDistance(string s1, string s2){
        int m = s2.size();
        int n = s1.size();
        vector< vector<int> >dp (m+1, vector<int>(n+1,0));
        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++){
                if(i==0){
                    dp[i][j]=j;
                }
                else if(j==0){
                    dp[i][j]=i;
                }
                else if(s2[i-1]==s1[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }
                else{
                    dp[i][j] = 1 + min( min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) ;
                }
            }
        }

        return dp[m][n];
    }
};

int main(){
    int n;
    cin>>n;
    string str="";
    Trie T;
    for(int i=0;i<n;i++){
        cin>>str;
        T.insertNode(str);
        
    }
    int ai;
    string ti;
    cin >>ai;
    cin>>ti;
    switch(ai){
        case 1:{
            if(T.spellCheck(ti))
                cout<<"1"<<endl;
            else
                cout<<"0"<<endl;
            break;
        }
        case 2:{
            vector <string> result = T.autocomplete(ti);
            cout<<result.size()<<endl;
            for(int i=0;i<result.size();i++)
                cout<<result[i]<<endl;
            break;
        }
        case 3:{
            vector <string> result = T.autocorrect(ti);
            cout<<result.size()<<endl;
            for(int i=0;i<result.size();i++)
                cout<<result[i]<<endl;
            break;
        }
        default:{
            cout<<"Invalid query !!!"<<endl;
        }
    }
    return 0;
}