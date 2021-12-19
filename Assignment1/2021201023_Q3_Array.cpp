//IN ARRAY REPRESENTATION I HAVE DONE  ADDITION , TRANSPOSE, MULTIPLICATION FOR INT ONLY
//WITHOUT TEMPLATE 
//I DIDN'T KNOW ABOUT TEMPALTE VERY WELL BEFORE THIS 
//I COLUDN'T LEARN IN THIS SHORT OF TIME

#include<iostream>
using namespace std;

typedef struct
{
    int m[500][3];
    /* data */
}array;

array addition(int a[][3], int b[][3])
{
    array r;
    r.m[0][0]=a[0][0];
    r.m[0][1]=a[0][1];
    int i=1,j=1,k=1;
    while(i<=a[0][2] and j<=b[0][2])
    {
            if(a[i][0]==b[j][0]){
                if(a[i][1]==b[i][1]){
                    r.m[k][0]=b[j][0];
                    r.m[k][1]=b[j][1];
                    r.m[k][2]=a[i][2]+b[j][2];
                    k++;
                    i++;
                    j++;
                }
                else if(a[i][1]<b[i][1]){
                    r.m[k][0]=a[i][0];
                    r.m[k][1]=a[i][1];
                    r.m[k][2]=a[i][2];
                    k++;
                    i++;
                }
                else{
                    r.m[k][0]=b[j][0];
                    r.m[k][1]=b[j][1];
                    r.m[k][2]=b[j][2];
                    k++;
                    j++;
                }
            }
            else if(a[i][0]<b[j][0]){
                r.m[k][0]=a[i][0];
                r.m[k][1]=a[i][1];
                r.m[k][2]=a[i][2];
                k++;
                i++;
            }
            else{
                r.m[k][0]=b[j][0];
                r.m[k][1]=b[j][1];
                r.m[k][2]=b[j][2];
                k++;
                j++;
            }
    }
    while(i<=a[0][2]){
        r.m[k][0]=a[i][0];
        r.m[k][1]=a[i][1];
        r.m[k][2]=a[i][2];
        k++;
        i++;        
    }
    while(j<=b[0][2]){
        r.m[k][0]=b[j][0];
        r.m[k][1]=b[j][1];
        r.m[k][2]=b[j][2];
        k++;
        j++;        
    }
    r.m[0][2]=k-1;
    return r;
}

array transpose(int a[][3]){
    array r;
    int n;
    r.m[0][0]=n=a[0][1];
    r.m[0][1]=a[0][0];
    r.m[0][2]=a[0][2];
    int total[n]={0};
    for(int i=1;i<=a[0][2];i++){
        total[a[i][1]]++;
    }
    int index[n+1];
    index[0]=1;
    for(int i=1;i<n+1;i++){
        index[i]=index[i-1]+total[i-1];
    }
    for(int i=1;i<=a[0][2];i++){
        int pos;
        pos=index[a[i][1]]++;
        //index[a[i][1]]++;
        r.m[pos][0]=a[i][1];
        r.m[pos][1]=a[i][0];
        r.m[pos][2]=a[i][2];
    }
    return r;
}
array multiply(int a[][3],int z[][3])
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

}
int main(){
    int r,c;
    int sparse[500][3];
    cin>>r>>c;
    sparse[0][0]=r;
    sparse[0][1]=c;
    int k=1;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int num;
            cin>>num;
            if(num!=0){
                sparse[k][0]=i;
                sparse[k][1]=j;
                sparse[k][2]=num;
                k++;
            }
        }
    }
    sparse[0][2]=k-1;

    int sparse2[500][3];
    cin>>r>>c;
    sparse2[0][0]=r;
    sparse2[0][1]=c;
    k=1;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int num;
            cin>>num;
            if(num!=0){
                sparse2[k][0]=i;
                sparse2[k][1]=j;
                sparse2[k][2]=num;
                k++;
            }
        }
    }
    sparse2[0][2]=k-1;
   array res=addition(sparse,sparse2);
 // array res= multiply(sparse,sparse2); 
  // array res=transpose(sparse);
  cout<<"row"<<"\t"<<"column"<<"\t"<<"value"<<endl;
    for(int i=0;i<=res.m[0][2];i++){
        cout<<res.m[i][0]<<"\t"<<res.m[i][1]<<"\t"<<res.m[i][2]<<endl;
    }
    return 0;
}