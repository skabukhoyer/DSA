#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>
#include<sstream>
using namespace std;
#define INF 101;


class MinHeap
{
    struct node{
	int vx;
	int dist;
	};

	vector<struct node> heap;
	int heap_size; 

	public:	
	MinHeap(){
		heap_size=0;
	}
	void buildHeap(int n,int src){
		struct node x;
		for (int i = 0; i < n; i++) {
			if(i==src){
				x.vx=i;
				x.dist=0;
			}
			else{
				x.vx=i;
				x.dist=101;
			}
			heap.push_back(x);
		}
		heap_size=n;
		for(int j= n/2 -1; j>=0 ; j--){
			MinHeapify(j);
		}
	}
	
	int parent(int i) { return (i-1)/2; }
	int left(int i) { return (2*i + 1); }
	int right(int i) { return (2*i + 2); }

	int extractMin(){
		
		if (heap_size <= 0)
			return -1;
		if (heap_size == 1)
		{
			heap_size--;
			return heap[0].vx;
		}

		struct node root = heap[0];
		heap[0] = heap[heap_size-1];
		heap_size--;
		MinHeapify(0);

		return root.vx;
	}

	void decreaseKey(int v, int new_val){
		int flag=0;
		for(int i=0;i<heap_size;i++){
			if(heap[i].vx==v){
				flag=i;
				break;
			}
		}
		heap[flag].dist = new_val;
		while (flag != 0 && heap[parent(flag)].dist > heap[flag].dist)
		{
			swap(heap[flag], heap[parent(flag)]);
			flag = parent(flag);
		}
	}
	bool empty(){
		return heap_size==0;
	}
   
	void print(){
		for(int i=0;i<heap_size;i++){
			cout<<"vertix: "<<heap[i].vx<<"\t dist: "<<heap[i].dist<<endl;
		}
	}
    void updateD(int v, int d){
        for(int i=0;i<heap_size;i++){
            if(heap[i].vx==v){
                heap[i].dist=d;
                return;
            }
        }
    }
	private:
	void swap(struct node &x, struct node &y){
		struct node temp=x;
		x=y;
		y=temp;
	}
	void MinHeapify(int i ){
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < heap_size && heap[l].dist < heap[i].dist)
			smallest = l;
		if (r < heap_size && heap[r].dist < heap[smallest].dist)
			smallest = r;
		if (smallest != i)
		{
			swap(heap[i], heap[smallest]);
			MinHeapify(smallest);
		}
	}

};



struct edge{
    int vertix;
    int weight;
    struct edge *nextEdge;
    public:
    edge(int v, int w){
        vertix=v;
        weight=w;
        nextEdge=NULL;
    }
};

void shortestPath(vector<struct edge*> &AL, int V, int E, int D){
    MinHeap h;
    h.buildHeap(V,D);
    vector<int> distance(V,101);
    vector<vector<string>> parentArray(V, vector<string>(1,""));
    parentArray[D][0]="-1";
    distance[D]=0;
    while( !h.empty()){
        int u= h.extractMin();
        struct edge *temp=AL[u];
        int v,w;
        while(temp != NULL){
            v=temp->vertix;
            w=temp->weight;
            if(distance[v] > distance[u]+w){
                distance[v]=distance[u]+w;
                h.decreaseKey(v,distance[v]);
                parentArray[v][0]=to_string(u);
            }
            else if(distance[v] == distance[u]+w){
                if(parentArray[v][0] > to_string(u)){
                    parentArray[v][0]=to_string(u);
                }
            }
            temp=temp->nextEdge;
        }
    }
    
    string x="";
    int d=0;
    for(int i=0;i<V;i++){
        if(i !=D){
            cout<<i<<" ";
            x=parentArray[i][0];
            while(x != "-1"){
                cout<<x<<" ";
                stringstream obj;  
                obj << x; 
                obj >> d; 
                x=parentArray[d][0];
            }
        }
        cout<<endl;
    }
}

int main()
{
    int V,E;
    cin>>V>>E;
    vector<struct edge*> adjacencyList(V,NULL);
    int v1,v2,w;
    struct edge *temp=NULL;
    for(int i=1;i <= E;i++){
        cin>>v1>>v2>>w;
        temp= new edge(v2,w);
        temp->nextEdge=adjacencyList[v1];
        adjacencyList[v1]=temp;
        temp=new edge(v1,w);
        temp->nextEdge=adjacencyList[v2];
        adjacencyList[v2]=temp;
    }
    int dest;
    cin>>dest;
  
   shortestPath(adjacencyList,V,E,dest);
    return 0;
}