#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
using namespace std;
#define MAX_SLOT 997
template< class K, class V>
class unordered_map
{
    struct Node {
        K key;
        V value;
        struct Node *next;
        public:
        Node(K ke, V val){
            key=ke;
            value=val;
            next=NULL;
        }
    };
    typedef struct Node node;
    node* hashTable[MAX_SLOT];

    public:

    unordered_map()
    {
        for(int i=0;i<MAX_SLOT;i++)
            hashTable[i]=NULL;
    }
    void insert(K ke,V val){
        int x=hashValue(ke);
        node *newNode=new node(ke,val);
        node *temp=hashTable[x];
        if(temp==NULL){
            hashTable[x]=newNode;
        }
        else{
            while(temp!=NULL){
                if(temp->key==ke){
                    temp->value=val;
                    break;
                }
                temp=temp->next;
            }
            if(temp==NULL){
                newNode->next=hashTable[x];
                hashTable[x]=newNode;
            }
        }
    }
    void erase(K ke){
        int x=hashValue(ke);
        node *temp=hashTable[x];
        
        if(temp!=NULL){
            if(temp->key==ke){
                hashTable[x]=temp->next;
                delete temp;
                temp=NULL;
            }
            else{
                while(temp->next!= NULL){
                    if(temp->next->key==ke){
                        node *del=temp->next;
                        temp->next=del->next;
                        delete del;
                        del=NULL;
                        break;
                    }
                    temp=temp->next;
                }
            }
        }
    }
    bool find(K ke){
        int x=hashValue(ke);
        node *temp=hashTable[x];
        if(temp!=NULL){
            while(temp!=NULL){
                if(temp->key==ke){
                    return true;
                }
                temp=temp->next;
            }
        }
        return false;
    }

    V operator [](K ke){
        int x=hashValue(ke);
        node *temp=hashTable[x];
        if(temp!=NULL){
            while(temp!=NULL){
                if(temp->key==ke){
                    return temp->value;
                }
                temp=temp->next;
            }
        }
        insert(ke,V());
        return V();
    }

    private:
    int hashValue(K ke){
        stringstream ss;
        ss<<ke;
        string s;
        ss>>s;
        int len=s.size();
        int h=0;
        for(int i=len-1;i>=0;i--){
            h+=((int(pow(10,i))%MAX_SLOT)*((s[i]-'\0')%MAX_SLOT))%MAX_SLOT;
            h%=MAX_SLOT;
        }
        return h;
    }
};
template<class T>
vector<int> count_distinct_element(T a[],int n,int k){
    vector<int> v;
    if(n < k)
    { return v;}
    for(int lower_index=0;lower_index <= n-k;lower_index++){
        unordered_map <T,int> um;
        int upper_index=lower_index+k-1;
        int count=0;
        for(int i=lower_index;i<=upper_index;i++){
            if(um.find(a[i])){
            // um.erase(a[i]);
                if(um[a[i]]==1)
                {um.insert(a[i],2);}

            }
            else{
                um.insert(a[i],1);
                count++;
            }
        }
        v.push_back(count);
    }
    return v;
}

int main(){
    // unordered_map<string,int> um;
    // um.insert("A",190);
    // um.insert("C",257);
    // cout<<um.find("A")<<endl;
    // cout<<um["A"]<<endl;
    // um.erase("C");
    // cout<<um.find("C")<<endl;
    // um.insert("D",129);
    // cout<<um["C"]<<endl;
    // cout<<um["B"]<<endl;
    // cout<<um["D"]<<endl;

    int arr[] = {1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,4,5,9,8,10,15,68};
    int n = sizeof(arr)/sizeof(arr[0]);
    vector<int> res = count_distinct_element<int>(arr,n,7);
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<" ";
    }
    return 0;
}
