//WORKING WELL

#include<iostream>
#include<unordered_map>
using namespace std;

class Node {
  public:
  int key, value;
  Node *prev, *next;
  Node(int k, int v){
      key=k;
      value=v;
      prev=NULL;
      next=NULL;
  }
};	
class LRUCache {
	 unordered_map<int, Node*> um;
	 Node *head;
	 Node *tail;
	 int capacity;
public:
	 LRUCache( int cap) {
		capacity = cap;
		head =new Node(0, 0);
		tail =new Node(0, 0);
		head->next = tail;
		tail->prev = head;
	}
	 int get(int key) {
         if(um.find(key)==um.end()){
             return -1;
         }
		Node *node = um.at(key);
		removee(node);
		insertt(node);
		return node->value;
	}
    void set(int key, int value) {
		if (um.find(key)!=um.end()) {
			removee(um.at(key));
		}
		if (um.size() == capacity) {
			removee(tail->prev);
		}
		insertt( new Node(key, value));
	}
private:    
	void insertt(Node* node) {
		um.insert(make_pair(node->key, node));
		node->next = head->next;
		head->next->prev = node;
		node->prev = head;
		head->next = node;
	}	

	void removee(Node* node) {
		um.erase(node->key);
		node->prev->next = node->next;
		node->next->prev = node->prev;
        //delete node;
	}

};

/*
int main(){
    LRUCache lru(3);
    lru.set(1,2);
    lru.set(2,3);
    lru.set(4,2);
    lru.set(5,10);
    cout<<lru.get(1)<<endl;
    lru.set(1,40);
    lru.set(2,50);
    cout<<lru.get(4)<<endl;
    lru.set(4,60);
    lru.set(1,70);
    cout<<lru.get(2)<<endl;
    cout<<lru.get(4)<<endl;
     cout<<lru.get(1)<<endl;
    cout<<lru.get(3)<<endl;

    return 0;
}
*/
