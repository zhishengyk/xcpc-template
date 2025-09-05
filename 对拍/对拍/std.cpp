#include<iostream>
using namespace std;
long long tree[400005][7];//四倍空间
char a[100005];
void push_up(int i)
{
    tree[i][1]=tree[i*2][1]+tree[i*2+1][1];
    tree[i][2]=tree[i*2][2]+tree[i*2+1][2];
    tree[i][3]=tree[i*2][3]+tree[i*2+1][3];
    tree[i][4]=min(tree[i*2][1]+tree[i*2+1][4],tree[i*2][4]+tree[i*2+1][2]);
    tree[i][5]=min(tree[i*2][2]+tree[i*2+1][5],tree[i*2][5]+tree[i*2+1][3]);
    tree[i][6]=min(tree[i*2][6]+tree[i*2+1][3],min(tree[i*2][4]+tree[i*2+1][5],tree[i*2][1]+tree[i*2+1][6]));
}
void build(int l,int r,int i)//建树
{
    if(l==r)
    {
        tree[i][(int)(a[l-1]-'a'+1)]=1;
    }
    else
    {
        int mid=(l+r)/2;
        build(l,mid,i*2);
        build(mid+1,r,i*2+1);
        push_up(i);
    }
}
void set(int l,int r,int k,int i,char s)//单点修改
{
    if(k<l||r<k)
    {
        return;
    }
    else if(l!=r)
    {
        int mid=(l+r)/2;
        set(l,mid,k,i*2,s);
        set(mid+1,r,k,i*2+1,s);
        push_up(i);
    }
    else
    {
        tree[i][1]=0;
        tree[i][2]=0;
        tree[i][3]=0;
        tree[i][(int)(s-'a'+1)]=1;
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    cin>>a;
    build(1,n,1);
    while(m--)
    {
        int x;
        char ch;
        cin>>x>>ch;
        set(1,n,x,1,ch);
        cout<<tree[1][6]<<endl;//反正都知道是1~n的区间，懒的再写函数了
    } 
    return 0;
}
