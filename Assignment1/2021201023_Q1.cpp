//addition and subtraction working well ,multiplication is showing issue
//FACTORIAL WORKING FINE
//GCD, EXPONENT , CALCULATOR IS STILL SHWOING NOTHING 
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#define MAX 3000
using namespace std;
string add(string str1,string str2)
{
            string str="";
            int i=str1.length()-1;
            int j=str2.length()-1;
            int carry=0;
            while(i>=0 || j>=0)
            {
                int sum=carry;
                if(i>=0){
                    sum+=(str1[i--]-'0');
                }
                if(j>=0){
                    sum+=(str2[j--]-'0');
                }
                str.push_back(sum%10+'0');
                carry=sum/10;
                
            }
            if(carry!=0){
                str.push_back(carry+'0');
            }
            reverse(str.begin(),str.end());
            return str;
}
string subtract(string a, string b)
{
            reverse(a.begin(),a.end());
            reverse(b.begin(),b.end());
            int n1=a.length();
            int n2=b.length();
            for(int i=n2;i<n1;i++){
                b.push_back('0');
            }
            int carry=0;
            string sub="";
            for(int i=0;i<n1;i++){
                int res=0;
                res=(a[i]-'0')-(b[i]-'0')-carry;
                if(res<0){
                    res+=10;
                    carry=1;
                }
                else{
                    carry=0;
                }
                sub.push_back(res+'0');
            }
            reverse(sub.begin(),sub.end());
            return sub;
}
string multiply(string num1, string num2){
            int n1=num1.length();
            int n2=num2.length();
            int l=n1+n2;
            int a[l]={0};
            int carry,k,pf=0;
            for(int i=n1-1;i>=0;i--){
                carry=0;
                k=l-1-pf;
                for(int j=n2-1;j>=0;j--){
                    int p=(num1[i]-'0')*(num2[j]-'0')+carry+a[k];
                    a[k--]=p%10;
                    carry=p/10;
                }
                if(carry!=0){
                    a[k]+=carry;
                }
                pf++;
            }
            string str="";
            for(int i=0;i<l;i++){
                if(a[0]==0)
                    continue;
                str.push_back(a[i]+'0');
            }
            return str;

}
bool isLess(string a, string b){
    if(a.length()<b.length())
        return true;
    if(a.length()>b.length())
        return false;
    return (a<b);
}
string GCD(string a,string b){
    if(a=="0")
        return b;
    if(b=="0")
        return a;
    if(a==b)
        return a;
    if(isLess(a,b))
        return GCD(a,subtract(b,a));
    return GCD(subtract(a,b),b);
}

string toString(unsigned long long int i){
    string res="";
    while(i){
        res.push_back(i%10+'0');
        i/=10;
    }
    reverse(res.begin(),res.end());
    return res;
}
void factorial(int n)
{
	int fact[MAX];
	fact[0]= 1;
	int count= 1;
	for (int j=2; j<=n;j++){
        int carry = 0; 
        for (int i=0;i<count; i++)
        {
            int p= fact[i]*j + carry;
            fact[i]= p%10;
            carry= p/10;
        }
        while (carry)
        {
            fact[count]= carry%10;
            carry =carry/10;
            count++;
        }
    }
	for (int i=count-1;i>=0; i--)
		cout << fact[i];
}

void exponent(string a,long long int x){
    if(x==0){
        cout<<"1";
        return;
    }
    string exp=a;
    
    for(long long int i=2;i<=x;i++){
        //cout<<exp<<endl;
        exp=multiply(exp, a);
        //cout<< exp<<endl;
    }
    cout<< exp;
}

void calculator(string exp)
{
  string opr;
  string opd[100];
  int j=0;
  for(int i=0;i<exp.length();i++){
    if(exp[i]=='+'||exp[i]=='-'||exp[i]=='x'){
      opr.push_back(exp[i]);
      j++;
      continue;
    }
    opd[j].push_back(exp[i]);
  }
  for(int i=0;i<opr.length();i++){
    if(opr[i]=='x'){
      string str=multiply(opd[i],opd[i+1]);
      opd[i].erase();
      opd[i].append(str);
      for(int j=i+1;j<99;j++){
        opd[j]=opd[j+1];
      }
      opr.erase(opr.begin()+i);
      i--;
    }
  }
   for(int i=0;i<opr.length();i++){
    if(opr[i]=='-'){
      string str=subtract(opd[i],opd[i+1]);
      opd[i].erase();
      opd[i].append(str);
      for(int j=i+1;j<99;j++){
        opd[j]=opd[j+1];
      }
      opr.erase(opr.begin()+i);
      i--;
    }
    
  }
  for(int i=0;i<opr.length();i++){
    if(opr[i]=='+'){
      string str=add(opd[i],opd[i+1]);
      opd[i].erase();
      opd[i].append(str);
      for(int j=i+1;j<99;j++){
        opd[j]=opd[j+1];
      }
      opr.erase(opr.begin()+i);
      i--;
    }
  }
 
  cout<<opd[0]<<endl;
}



int main()
{
  int n;
   cin>>n;
   switch(n){
       case 1:
       {
           string s;long long int ll;
           cin>>s>>ll;
           exponent(s,ll);
           break;
       }
       case 2:
       {
           string a,b;
           cin>>a>>b;
           cout<<GCD(a,b);
           break;
       }
       case 3:
       {
           int ull;
           cin>>ull;
           factorial(ull);
           break;
       }
       case 4:
       {
           string s;
           cin>>s;
           calculator(s);
           break;
       }
   }
   return 0;
}

