#include<iostream>

using namespace std;
class Node{
    public:
        int r;
        int c;
        int v;
        Node *next;
        Node(int row,int col,int val){
                r=row;
                c=col;
                v=val;
                next=NULL;
        }
};

Node* addition(Node *head1, Node *head2)
{
    Node *a=head1->next;
    Node *b=head2->next;
    Node *r=new Node(head1->r,head1->c,-1);
    Node *temp=r;
    int count=0;
    while( a!=NULL and b!=NULL)
    {
            if(a->r==b->r){
                if(a->c==b->c){
                   Node *node=new Node(a->r,a->c,a->v+b->v);
                   temp->next=node;
                   temp=node;
                   a=a->next;
                   b=b->next;
                   count++;
                }
               else if(a->c < b->c){
                   Node *node=new Node(a->r,a->c,a->v);
                   temp->next=node;
                   temp=node;
                   a=a->next;
                   count++;
                }
                else{
                    Node *node=new Node(b->r,b->c,b->v);
                   temp->next=node;
                   temp=node;
                   b=b->next;
                   count++;
                }   
            }
            else if(a->r < b->r){
                Node *node=new Node(a->r,a->c,a->v);
                temp->next=node;
                temp=node;
                a=a->next;
                count++;
            }
            else{
                Node *node=new Node(b->r,b->c,b->v);
                temp->next=node;
                temp=node;
                b=b->next;
                count++;
            }
    }
    while(a!=NULL){
       Node *node=new Node(a->r,a->c,a->v);
        temp->next=node;
        temp=node;
        a=a->next;    
        count++;  
    }
    while(b!=NULL){
       Node *node=new Node(b->r,b->c,b->v);
        temp->next=node;
        temp=node;
        b=b->next;  
        count++;     
    }
    r->v=count;
    return r;
}

Node* transpose(Node *head1){
    Node *res=new Node(head1->c,head1->r,head1->v);
    int n=head1->c;
   // int total[n]={0};
    Node *temp=head1->next;
    Node *node=new Node(temp->c,temp->r,temp->v);
    res->next=node;
    temp=temp->next;
    Node *st;
    while(temp!=NULL){
        node=new Node(temp->c,temp->r,temp->v);
        st=res->next;
        while(st!=NULL){
            if(st->r == node->r){
                if(st->c < node->c){
                    //st=st->next;
                    if(st->next==NULL){
                        st->next=node;
                        break;
                    }
                    else{
                        st=st->next;
                    }
                }
                else{
                    if(res->next==st){
                        node->next=st;
                        res->next=node;
                    }
                    else{
                        node->next=st->next;
                        st->next=node;
                    }
                    break;
                }
            }
            else if(st->r < node->r){
               if(st->next==NULL){
                    st->next=node;
                    break;
                }
                else{
                    st=st->next;
                }
            }
            else{
                if(res->next==st){
                    node->next=st;
                    res->next=node;
                }
                else{
                    int x,y,z;
                    x=st->r;
                    y=st->c;
                    z=st->v;
                    st->r=node->r;
                    st->c=node->c;
                    st->v=node->v;
                    node->r=x;
                    node->c=y;
                    node->v=z;
                    node->next=st->next;
                    st->next=node;

                }
                break;
            }
        }
        temp=temp->next;

    }
    return res;
  
}
/*array multiply(int a[][3],int z[][3])
{
    //if(a[0][1]!=z[0][0]){
     //   return ;
    //}
    array r;
    array b1=transpose(z);
    r.m[0][0]=a[0][0];
    r.m[0][1]=b1.m[0][0];
    int k=1;
    for(int i=1;i<=a[0][2];i++){
        for(int j=1;j<=b1.m[0][2];j++){
            if(a[i][1]==b1.m[j][1]){
                r.m[k][0]=a[i][0];
                r.m[k][1]=b1.m[j][0];
                r.m[k][2]=a[i][2] * b1.m[j][2];
                k++;
            }
        }
    }
    k--;
    int i=1,l=1,row=0;
    while(i<=k){
        row=r.m[i][0];
        //l=i;
        while(r.m[l][0]==row and l<=k){
            int min=l;
            int j=l+1;
            while(r.m[j][0]==row and j<=k){
                if(r.m[j][1]<r.m[min][1]){
                    min=j;
                }
                j++;
            }
            //swap;
            if(min!=l){
                int temp=r.m[l][1];
                r.m[l][1]=r.m[min][1];
                r.m[min][1]=temp;
                temp=r.m[l][2];
                r.m[l][2]=r.m[min][2];
                r.m[min][2]=temp;              
            }
            l++;
        }
        i=l;
    }

    array result;
    result.m[0][0]=r.m[0][0];
    result.m[0][1]=r.m[0][1];
    i=1;
    int u=1;
    while(i<=k){
        int sum=r.m[i][2];
        int j=i+1;
        while(r.m[i][0]==r.m[j][0] and r.m[i][1]==r.m[j][1] and j<=k){
            sum+=r.m[j][2];
            j++;
        }
        result.m[u][0]=r.m[i][0];
        result.m[u][1]=r.m[i][1];
        result.m[u][2]=sum;
        u++;
        i=j;
    }
    result.m[0][2]=u-1;
    return result;

}*/
int main(){
    int row,col;
    cin>>row>>col;
    Node *head1=new Node(row,col,-1);
    Node *temp=head1;
    int count=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int num;
            cin>>num;
            if(num!=0){
                Node *node=new Node(i,j,num);
                temp->next=node;
                temp=node;
                count++;
            }
        }
    }
    head1->v=count;
    //2nd matrix input;
    cin>>row>>col;
    Node *head2=new Node(row,col,-1);
    temp=head2;
    count=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int num;
            cin>>num;
            if(num!=0){
                Node *node=new Node(i,j,num);
                temp->next=node;
                temp=node;
                count++;
            }
        }
    }
    head2->v=count;
    temp=head1;
    cout<<"1st list"<<endl;
    while(temp!=NULL){
        cout<<temp->r<<"\t"<<temp->c<<"\t"<<temp->v<<endl;
        temp=temp->next;
    }
    temp=head2;
    cout<<"2nd list:"<<endl;
    while(temp!=NULL){
        cout<<temp->r<<"\t"<<temp->c<<"\t"<<temp->v<<endl;
        temp=temp->next;
    }
    Node *add=addition(head1,head2);
    temp=add;
    //Node *trans=transpose(head1);
    //temp=trans;
    cout<<"row  column  value"<<endl;
    //cout<<"add:"<<endl;
    while(temp!=NULL){
        cout<<temp->r<<"\t"<<temp->c<<"\t"<<temp->v<<endl;
        temp=temp->next;
    }
    return 0;
}