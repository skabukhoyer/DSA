#include <iostream>
#include<string>
using namespace std;
#define MAX_SIZE 5000

template<class T>
class deque
{
    T a[MAX_SIZE];
    int curr_size=0;
    int frontt=0, rear=0;

public:
    deque()
    {
        curr_size = 0;
        frontt = -1;
        rear = -1;
    }

    deque(int n, T x)
    {
        curr_size = n;
        for (int i = 0; i < n; i++)
            a[i] = x;
        frontt = -1;
        rear = n - 1;
    }

    void push_back(T x)
    {
        rear = (rear + 1) % MAX_SIZE;
        a[rear] = x;
        curr_size++;
    }
    void pop_back()
    {
        if (curr_size!=0)
            {
                rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
                curr_size--;
            }
    }
    void push_front(T x)
    {
        if (frontt == -1)
        {
            frontt = MAX_SIZE - 1;
            a[frontt] = x;
            frontt = (frontt - 1 + MAX_SIZE) % MAX_SIZE;
        }
        else
        {
            a[frontt] = x;
            frontt = (frontt - 1 + MAX_SIZE) % MAX_SIZE;
        }
        curr_size++;
    }

    void pop_front()
    {
        if(curr_size!=0){
        frontt = (frontt + 1) % MAX_SIZE;
        curr_size--;
        }
    }

    T front()
    {
        if (curr_size!=0)
                return a[(frontt+1)%MAX_SIZE];
    }

    T back()
    {
        if (curr_size!=0)
                return a[rear];
    }

    bool empty()
    {
        return curr_size == 0;
    }

    int size()
    {
        return curr_size;
    }

    void resize(int x, T d){
       if(x>=curr_size){
           curr_size=x;
           for(int i=curr_size+1;i<=x;i++){
               rear=(rear+1)%MAX_SIZE;
               a[rear]=d;
           }
       }
       else{
           rear=(rear+curr_size-x+MAX_SIZE)%MAX_SIZE;
           curr_size=x;

       }
    }

    void clear(){
        curr_size=0;
    }
    T operator []( int x){
        if(x<=curr_size)
        return a[(frontt+x)%MAX_SIZE];
    }
    void print(){
        int x=(frontt+1)%MAX_SIZE;
        for(int i=1;i<= curr_size;i++){
            cout<<"a["<<x<<"] ="<<a[x]<<endl;
            x=(x+1)%MAX_SIZE;
        }
    }
};

// int main(){
//     deque<string> dq;
//     dq.push_back("a");
//     dq.push_front("b");
//     dq.push_back("c");
//     dq.push_front("d");
//     dq.push_back("e");
//     dq.push_front("f");
//     dq.print();
//     cout<<dq.size()<<endl;
//     cout<<dq[4]<<endl;
//     dq.resize(4,"");
//     dq.print();
//     return 0;
// }
int main()
{
    deque<int>deq ;
    for(int i=0;i<1000;i++){
        deq.push_back(i);
        cout<<deq.back()<<" ";
    }
    cout<<endl;
    for(int i=0;i<100;i++){
        deq.push_front(i*2);
        cout<<deq.front()<<" ";
    }
    cout<<endl;
    cout<<deq.size()<<endl;
    for(int i=0;i<deq.size();i++){
        cout<<deq[i]<<" ";
    }
    deq.clear();
    cout<<endl;
    cout<<deq.size()<<endl;
    cout<<deq.empty()<<endl;
    deq.resize(10,4);
    cout<<deq.size()<<endl;
    cout<<deq.empty()<<endl;
    cout<<deq.size()<<endl;
    for(int i=0;i<deq.size();i++){
        cout<<deq[i]<<" ";
    }
    return 0;

}

