#include<iostream>
#include<limits>
#include<string>
#include<cmath>
using namespace std;

class student {
    int roll_no;
    string name;
    public:
    student(){

    }
    student( int r, string n){
        roll_no=r;
        name=n;
    }
    //comparison according to roll number
    bool operator ==(student &b){
        return roll_no == b.roll_no;
    }
    bool operator <=(student &b){
        return roll_no <= b.roll_no;
    }
    bool operator >=(student &b){
        return roll_no >= b.roll_no;
    }
    bool operator > (student &b){
        return roll_no > b.roll_no;
    }
    bool operator < (student &b){
        return roll_no < b.roll_no;
    }
    int operator - (student &b){
        return roll_no - b.roll_no;
    }
    int operator -> (){
        return roll_no;
    }
     friend ostream &operator<<( ostream &output, const student &D ) {
      output<< D.roll_no;
      return output;
   }
   friend istream &operator>>( istream &input, student &D ) {
      input >> D.roll_no;
      return input;
   }

};

template<class T>
class AVLTree{
    struct Node{
        T data;
        struct Node *left;
        struct Node *right;
        int heightBalanceFactor;
        public:
       /* Node(){
            left=NULL;
            right=NULL;
            data=0;
            height=0;
        }*/
        Node(T d){
            left=NULL;
            right=NULL;
            data=d;
            heightBalanceFactor=0;
        }
    };
    typedef struct Node node;
    node *root;

    public:

    AVLTree(){
        root=NULL;
    }
    void insert(T val){
        root=addData(root,val);
    }
    void delet(T val){
        root=removeData(root,val);//delete all the ocurrences of the element
    }
    bool search(T val){
        return find(root, val);
    }
    int countOcurrencesOfElement(T val){
        return ocurrence(root, val);
    }
    T lowerBound( T val){
        return lb(root, val);
    }
    T upperBound(T val){
        return ub(root, val);
    }
    T closetElement(T val){
        int diff=1e9;
        node *result=closet(root, val,diff);
        if(result !=NULL)
            return result->data;
        
    }
    int countElementInRange(T val1 , T val2){
        return range(root,val1,val2);
    }
    T kthLargestElement(int k){
        int c=0;
        node *temp=largest(root,k,c);
        if(temp!=NULL){
            return temp->data;
        }
        
    }
    void printAVL(){
        if(root==NULL)
            cout<<"AVL is Empty!"<<endl;
        else{
            inorderTraversal(root);
        }
    }
    private:

    node* addData(node *head,T val){
        if(head==NULL){
        
            return new node(val);
        }
        else if(val<head->data){
            head->left=addData(head->left,val);
        }
        else{
            head->right=addData(head->right,val);
        }
        //head->height=findHeight(head);
        int heightDifference=findHeight(head->left)-findHeight(head->right);
        //head->heightBalanceFactor=heightDifference;
        node *temp;
        if(heightDifference>1){
            if(head->left->data <= val){
                head->left=leftRotation(head->left);
            }
            temp=rightRotation(head);
        }
        else if(heightDifference < -1){
            if(head->right->data > val){
                head->right=rightRotation(head->right);
            }
            temp=leftRotation(head);
        }
        else{
            temp=head;
            updateBalanceFactor(temp);
        }
        return temp;
    }
    node* removeData(node *head, T val){
        if(head==NULL) return head;

        if(val == head->data){
            node *temp=head;
            if(head->left==NULL and head->right==NULL){
                //temp=head;
                delete head;
                head=NULL;
                return head;
            }
            else if(head->left !=NULL and head->right==NULL){
                temp=head->left;
                delete head;
                head=temp;
            }
            else if(head->left ==NULL and head->right!=NULL){
                temp=head->right;
                delete head;
                head=temp;
            }
            else{
                temp=head->right;
                while(temp->left !=NULL)
                    temp=temp->left;
                //T x = head->data;
                head->data= temp->data;
                //temp->data= x;
                head->right= removeData(head->right, temp->data);
            }
           head=removeData(head, val);
        }
        else if(val < head->data){
            head->left=removeData(head->left, val);
        }
        else{
            head->right=removeData(head->right, val);
        }
        updateBalanceFactor(head);
        if(head->heightBalanceFactor > 1){
            if(head->left->heightBalanceFactor < 0)
                head->left=leftRotation(head->left);
            head=rightRotation(head);
        }
        else if(head->heightBalanceFactor < -1){
            if(head->right->heightBalanceFactor > 0)
                head->right=rightRotation(head->right);
            head=leftRotation(head);
        }
        
        return head;
    }
    bool find(node *head, T val){
        if(head==NULL) return false;
        else if(head->data==val) return true;
        else if(head->data < val) return find(head->right, val);
        else return find(head->left, val);
    }
    int ocurrence(node *head, T val){
        if(head==NULL) return 0;
        else if(head->data==val)
            return 1+ocurrence(head->left,val)+ocurrence(head->right,val);
        else if(head->data < val)
            return ocurrence(head->right, val);
        else
            return ocurrence(head->left, val);
    }
    T lb(node *head, T val){
        T x;
        //if(head==NULL) return ;
        if(head->data==val) return val;
        else if(head->data < val) {
            if(head->right !=NULL)
                x= lb(head->right, val);
            else 
                return head->data;
        }
        else {
            if(head->left!=NULL)
                x= lb(head->left, val);
            else 
                return head->data;
        }

        if(head->data < val){
            return x;
        }
        else {
            //if(x == val) return x;
            if(x>=val) return x;
            else return head->data;
        }
    }
    T ub(node *head, T val){
        T x=head->data;
       // if(head==NULL) {cout<<"NULL"<<endl; return 0;}
        if(head->data ==val){
            if(head->right ==NULL) return x;
            x=ub(head->right, val);
        }
        else if(head->data < val) {
            if(head->right !=NULL)
                x= ub(head->right, val);
            else 
                return x;
        }
        else {
            if(head->left!=NULL)
                x= ub(head->left, val);//lb->ub
            else 
                return x;
        }
        if(head->data < val){
            return x;
        }
        else {
            if(x > val) return x;
            else return head->data;
        }
    }
    node* closet(node *head, T val, int diff){
        if(head==NULL) return NULL;
        T x=head->data;
        if(diff > abs(x - val))
        {
            diff=abs(x-val);
            //closetNode=head;
        }
        node *temp1;
        if(x==val) {
            return head;
        }
        else if(val > x){
            if(head->right !=NULL)
                temp1=closet(head->right, val, diff);
            else
                temp1=head;
        }
        else {
            if(head->left !=NULL)
                temp1=closet(head->left, val, diff);
            else
                temp1=head;
        }

        if(diff > abs(temp1->data - val)){
            return temp1;
        }
        return head;
    }
    int range(Node *root, T l, T h)
    {
        // your code goes here   
        if(root==NULL) return 0;
        T x=root->data;
        if(x >= l and x<=h ){
            return 1+range(root->left,l,h)+range(root->right,l,h);
        }
        else if(x < l){
            return range(root->right,l,h);
        }
        else {
            return range(root->left,l,h);
        }
    }
    node* largest(node *head, int k, int &c){
        if(head==NULL ) return NULL;
        node *temp;
        if(head->right!=NULL){
            temp=largest(head->right,k,c);
            if(c==k){return temp;}
        }
        c++;
        if(c==k){
            return head;
        }
        else if(head->left !=NULL){
            temp=largest(head->left,k,c);
            if(k==c) {return temp;}
        }

    }
    int findHeight(node *head){
        if(head==NULL ) 
            return -1;
        else if(head->left==NULL and head->right==NULL)
            return 0;
        return (1 + max(findHeight(head->left) , findHeight(head->right)));
    }
    node* leftRotation(node *head){
        if(head==NULL ) return head;
        node *headRightChild=head->right;
        node *headRightLeftChild=headRightChild->left;
       // node *headRightRightChild=headRightChild->right;
        headRightChild->left=head;
        head->right=headRightLeftChild;
        updateBalanceFactor(head);
        updateBalanceFactor(headRightChild);
       // updateBalanceFactor(headRightRightChild);
        return headRightChild;
    }
    node* rightRotation(node *head){
        if(head==NULL ) return head;
        node *headLeftChild=head->left;
        node *headLeftRightChild=headLeftChild->right;
      //  node *headLeftLeftChild=headLeftChild->left;
        headLeftChild->right=head;
        head->left=headLeftRightChild;
        updateBalanceFactor(head);
        updateBalanceFactor(headLeftChild);
       // updateBalanceFactor(headLeftLeftChild);
        return headLeftChild;
    }
    void updateBalanceFactor(node *head){
        if(head==NULL) return ;
        head->heightBalanceFactor=findHeight(head->left)-findHeight(head->right);
    }
    void inorderTraversal(node *head){
        if(head!=NULL){
            inorderTraversal(head->left);
            cout<<head->data<<"  "<<head->heightBalanceFactor<<endl;
            inorderTraversal(head->right);
        }
    }
};


int main(){
    // cout<<"Selection menu: \n1- Insertion \n2- Deletion \n3- Search ";
    // cout<<"\n4- Count Occurences of element\n5- lower_bound\n6- upper_bound";
    // cout<<"\n7- Closet element to some value\n8- Kth largest element";
    // cout<<"\n9- Count the number of elements in the tree whose values fall into a given range";
    // cout<<"\n10- Exit\n";
    AVLTree <int> avl; // for int
    int choice;
    while(1){
        //cout<<"Enter your choice: ";
        cin>>choice;
        int a,b,ele,var;
        switch(choice){
            case 1:
                //cout<<"Enter a element: ";
                cin>>ele;
                avl.insert(ele);
                break;
            case 2:
                //cout<<"Enter a element: ";
                cin>>ele;
                avl.delet(ele);
                break;
            case 3:
               // cout<<"Enter a element: ";
                cin>>ele;
                cout<<avl.search(ele)<<endl;
                break;
            case 4:
                //cout<<"Enter a element: ";
                cin>>ele;
                cout<<avl.countOcurrencesOfElement(ele)<<endl;
                break;
            case 5:
                //cout<<"Enter a element: ";
                cin>>ele;
                var = avl.lowerBound(ele);
                if(var<ele){
                    cout<<"-1"<<endl;
                }
                else{
                    cout<<var<<endl;
                }
                break;
            case 6:
                //cout<<"Enter a element: ";
                cin>>ele;
                var = avl.upperBound(ele);
                if(var>ele){
                    cout<<var<<endl;
                }
                else{
                    cout<<"-1"<<endl;
                }
                break;
            case 7:
               // cout<<"Enter a element: ";
                cin>>ele;
                cout<<avl.closetElement(ele)<<endl;
                break;
            case 8:
               // cout<<"Enter k value: ";
                cin>>ele;
                cout<<avl.kthLargestElement(ele)<<endl;
                break;
            case 9:
                //cout<<"Enter two value for range space separated: ";
                cin>>a>>b;
                cout<<avl.countElementInRange(a,b)<<endl;
                break;
            case 10:
                return 0;
            default:
                cout<<"Invalid selection. "<<endl;
        }
    }
    return 0;
}
// int main()
// {
//    /* AVLTree <student> avl;
//     student x(10,"SK");
//     student y(20,"AK");
//     avl.insert(x);
//     avl.insert(y);
//    cout<< avl.search(x)<<" "<<avl.lowerBound(x)<<endl;
//    avl.printAVL();*/
// //avl.printAVL();
//    /* AVLTree <string>avl;
//     avl.insert("a");
//     avl.insert("f");
//     avl.insert("b");
//     avl.insert("c");
//     avl.insert("d");
//     avl.insert("x");
//     avl.insert("a");
//     avl.printAVL();
//     cout<<avl.countOcurrencesOfElement("a")<<endl;
//     cout<<avl.countElementInRange("a","d")<<endl;
//     cout<<avl.closetElement("f")<<endl;*/
//    AVLTree<int> avl;
//    // cout<<"INTIALLY: "<<endl;
//    // avl.printAVL();
//     avl.insert(10);
//     avl.insert(20);
//     avl.insert(30);
//    // cout<<"xxxxxxxxxxxxxx"<<endl;
//    // avl.printAVL();
//    avl.insert(60);
//     //cout<<"xxxxxxxxxxxxxx"<<endl;
//     //avl.printAVL();
//     avl.insert(12);
//     avl.insert(5);
//     avl.insert(1);
//     avl.insert(7);
//     // cout<<"xxxxxxxxxxxxxx"<<endl;
//     //avl.printAVL();
//     avl.insert(90);
//     avl.insert(10);
//     avl.insert(7);
//    //  cout<<"xxxxxxxxxxxxxx"<<endl;
//     //avl.printAVL();
//     avl.insert(7);
    
//     //cout<<"NOW: "<<endl;
//     avl.printAVL();
//    /* avl.delet(12);
//     avl.delet(1);
//     avl.delet(20);
//     avl.delet(7);
//     cout<<"after deleting 7: "<<endl;
//     avl.printAVL();
//     avl.delet(10);
//     cout<<"second deleting:"<<endl;
//     avl.printAVL();
//     cout<<"searching for 10: "<<avl.search(10)<<endl;
//     cout<<"seraching for 90: "<<avl.search(90)<<endl;*/
//     //cout<<"No of occurences of 20: "<<avl.countOcurrencesOfElement(20)<<endl;
//     //cout<<"lb of 25 : "<<avl.lowerBound(100)<<endl;
//     cout<<" ub of ele: "<<avl.upperBound(60)<<endl;
//    // avl.printAVL();
//     //cout<<avl.closetElement(100)<<endl;
//     //cout<<avl.countElementInRange(1,10)<<endl;
//     //cout<<avl.kthLargestElement(5)<<endl;
//     return 0;

// }