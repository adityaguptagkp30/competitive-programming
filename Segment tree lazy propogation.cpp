/*
Author : Aditya Gupta
Team : TechTurtle
Date : 02-06-2020
Time : 20:05:54
*/

 
#include<bits/stdc++.h>
#define ll long long int
#define ld long double
#define vll vector<ll>
#define vvll vector< vll >
#define vld vector< ld >
#define vvld vector< vld >
#define pll pair<ll ,ll >
#define vpll vector< pll >
#define mp make_pair
#define pb push_back
#define MOD 1000000007
#define endl "\n"
#define flash ios_base::sync_with_stdio(false);cin.tie(NULL);
#define test ll t;cin>>t;while(t--)
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define ff first
#define sec second
#define mk(arr,n,type)  type *arr=new type[n];

 
#define forn(i,n) for(ll (i) = 0 ; (i) < (n) ; ++(i))
#define for1(i,n) for(ll (i) = 1 ; (i) <= (n) ; ++(i))
#define forr(i,n) for(ll (i) = (n)-1 ; (i)>=0 ; --(i))
#define forab(i,a,b,c) for(ll (i) = a ; (i) <= (b) ; (i)+=(c))
 
using namespace std;
 
///////////////////////////////////////////////////////////////////////// Maths //////////////////////////////////////////////////////////////////////////////

//vll sieve;
//void Sieve(int N){  //smallest prime factor
//	const ll maxn = N;
//	sieve.resize(maxn);
//	forn(i,maxn) sieve[i] = i;
//	sieve[1] = -1;
//	sieve[0] = -1;
//	forab(i,2,maxn,1) if(i == sieve[i]) for(ll j = i*i ; j < maxn ; j+=i) if(sieve[j] == j) sieve[j] = i;
//	
////	for(auto i:sieve){
////		cout<<i<<" ";
////	}
//
//}
vll sieve;
vll* Sieve(int N){
	const ll maxn = N;
	sieve.resize(maxn);
	forn(i,maxn) sieve[i] = 1;
	sieve[1] = 0;
	sieve[0] = 0;
	forab(i,2,maxn,1) if(1 == sieve[i]) for(ll j = i*i ; j < maxn ; j+=i) sieve[j] = 0;
	
	vll* primes=new vll();
	primes->pb(2);
	for(int i=3;i<maxn;i+=2)
	if(sieve[i]){
		primes->pb(i);
	}
	return primes;
 
}
 
   
ll extended_GCD(ll a , ll b , ll &x , ll &y){
	if(a == 0){
		x = 0;
		y = 1;
		return b;
	}
	ll x1 , y1;
	ll gcd = extended_GCD(b%a , a , x1 , y1);
	x = y1 - (b/a)*x1; 
	y = x1;
	return gcd;
}
 
ll power(ll a, ll b, ll m = MOD) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
ll modinv(ll a , ll mod = MOD){
	ll x , y;
	extended_GCD(a , mod , x , y);
	if(x < 0) x += mod;
	return x;
}
  
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 bool prime(int n){
 	int c=0;
 	for(int i=2;(i*i)<=n;i++)
 	{
	 if(n%i==0)
 	{
	 c++;
	 return false;
}
}
 	if(c==0)
 	return true;
 }
// bool compareInterval(char i1, char i2) 
//{ 
//    return (i1 < i2); 
//}
// int countoperation(int n,m){
// 	vector<int> d<m+1,-1>;
// }

struct node{
	int a[3];
};

int lazy[4*100001];
node st[4*100001];


void build(int si,int ss,int se){
	if(ss==se){
		st[si].a[0]=1;
		st[si].a[1]=0;
		st[si].a[2]=0;
		return;
	}
	int mid=(ss+se)/2;
	build(2*si,ss,mid);
	build(2*si+1,mid+1,se);
	st[si].a[0]=st[2*si].a[0]+st[2*si+1].a[0];
	st[si].a[1]=st[2*si].a[1]+st[2*si+1].a[1];
	st[si].a[2]=st[2*si].a[2]+st[2*si+1].a[2];
}
void shift(int si){
	int t=st[si].a[2];
	st[si].a[2]=st[si].a[1];
	st[si].a[1]=st[si].a[0];
	st[si].a[0]=t;
}
void update(int si,int ss,int se,int qs,int qe){
	
	
	if(lazy[si]!=0){
		
		int add=lazy[si];
		lazy[si]=0;
		if(se!=ss){
		lazy[2*si]+=add;
		lazy[2*si+1]+=add;
	    }
		add%=3;
		forn(i,add){
			shift(si);
		}
		
	}
	
	if(qs>se||ss>qe)
	return;
	
	if(ss>=qs && se<=qe)
	{
		shift(si);
		
		if(ss!=se)
		{
			lazy[2*si]++;
			lazy[2*si+1]++;
		}
		return;
	}
	
	int mid=(ss+se)/2;
	
	update(2*si,ss,mid,qs,qe);
	update(2*si+1,mid+1,se,qs,qe);
	
	st[si].a[0]=st[2*si].a[0]+st[2*si+1].a[0];
	st[si].a[1]=st[2*si].a[1]+st[2*si+1].a[1];
	st[si].a[2]=st[2*si].a[2]+st[2*si+1].a[2];

	
}
int query(int si,int ss,int se,int qs,int qe){
	if(lazy[si]!=0){
		int add=lazy[si];
		lazy[si]=0;
		if(ss!=se){
		lazy[2*si]+=add;
		lazy[2*si+1]+=add;
	    }
		add%=3;
		forn(i,add){
			shift(si);
		}
		
	}
	
	if(qs>se||ss>qe)
	return 0;
	
	if(ss>=qs&&se<=qe)
	return st[si].a[0];
	
	int mid=(ss+se)/2;
	int l=query(2*si,ss,mid,qs,qe);
	int r=query(2*si+1,mid+1,se,qs,qe);
	
	return l+r;
}


void solve(){
	int n,q;
	cin>>n>>q;
	
	int c,l,r;
	
	build(1,1,n);
	
	while(q--){
		
			cin>>c>>l>>r;
			if(c==1)
			cout<<query(1,1,n,l+1,r+1)<<"\n";
			else
			if(c==0)
			update(1,1,n,l+1,r+1);
	}

}
	

int main()
{
	flash
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout); 

//  test
	 solve();
    return 0;
}

