//WORKING WELL BUT PROBLEM WITH TIME COMPLEXITY

#include<iostream>
#include<unordered_map>
using namespace std;

class Node {
  public:
  int key, value,counter;
  Node *prev, *next;
  Node(int k, int v,int count){
      key=k;
      value=v;
      counter=count;
      prev=NULL;
      next=NULL;
  }
};	
class LFUCache {
	 unordered_map<int, Node*> um;
	 Node *head;
	 Node *tail;
	 int capacity;
public:
	 LFUCache( int cap) {
		capacity = cap;
		head =new Node(0, 0,0);
		tail =new Node(0, 0,0);
		head->next = tail;
		tail->prev = head;
	}
	int get(int key) {
         if(um.count(key)<=0){
             return -1;
         }
		Node *node = um.at(key);
        node->counter+=1;
		remov(node);
		insertt(node);
		return node->value;
	}
    void set(int key, int value) {
        int count=1;
		if (um.count(key)>0) {
            count+=um.at(key)->counter;
            remov(um.at(key));
		}
		if (um.size() == capacity) {
			Invalidate(tail->prev);
		}
		insertt( new Node(key, value,count));
	}
private:    
	void insertt(Node* node) {
		um.insert(make_pair(node->key, node));
		node->next = head->next;
		head->next->prev = node;
		node->prev = head;
		head->next = node;
	}	
    void remov(Node *node){
        um.erase(node->key);
		node->prev->next = node->next;
		node->next->prev = node->prev;
    }
	void Invalidate(Node *del) {
		int min=del->counter;
        Node *temp=del->prev;
        while(temp!=head){
            if(min>temp->counter){
                min=temp->counter;
                del=temp;
            }
            temp=temp->prev;
        }
        del->prev->next = del->next;
		del->next->prev = del->prev;
        um.erase(del->key);
        
        delete del;
	}

};

/*
int main(){
    LFUCache lfu(3);
    lfu.set(1,10);
    lfu.set(2,20);
    lfu.set(3,30);
    
    cout<<lfu.get(1)<<endl;
    lfu.set(4,40);
    lfu.set(5,50);
    lfu.set(1,100);
    cout<<lfu.get(1)<<endl;
    cout<<lfu.get(2)<<endl;
     cout<<lfu.get(3)<<endl;
    cout<<lfu.get(4)<<endl;
    cout<<lfu.get(5)<<endl;

    return 0;
}
*/