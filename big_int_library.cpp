#include<iostream>
#include<vector>
#include <cstring>

using namespace std;

class BigInt{
    bool is_negative=false;
    string digits;
    public:
    // constructors

    BigInt(long long n=0); // for this if no parameter is passed this constructor is called
    BigInt(const string &);
    BigInt(const char *);
    BigInt(const BigInt &);
    
    // Hellper function

    friend void divide_by_2(BigInt &a);
	friend bool Null(const BigInt &);
	friend int Length(const BigInt &);
    friend BigInt mod(const BigInt & a);

    /* * * * Operator Overloading * * * */

	//Direct assignment
	BigInt &operator=(const BigInt &);

	//Post/Pre - Incrementation/decrementation
	BigInt &operator++();
	BigInt operator++(int temp);
	BigInt &operator--();
	BigInt operator--(int temp);

    //sign flip operator
    BigInt &operator-();

    //Comparison operators
	friend bool operator==(const BigInt &, const BigInt &);
	friend bool operator!=(const BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
	friend bool operator>=(const BigInt &, const BigInt &);
	friend bool operator<(const BigInt &, const BigInt &);
	friend bool operator<=(const BigInt &, const BigInt &);

    //helper function for add/sub/mul/div/increament/dec.
    friend BigInt &helper_1(BigInt &a, const BigInt &b);
    friend BigInt &helper_2(BigInt &a, const BigInt &b);
    friend BigInt &helper_3(BigInt &a, const BigInt &b);
    friend BigInt &helper_4(BigInt &a, const BigInt &b);
    friend BigInt &helper_5(BigInt &a);
    friend BigInt &helper_6(BigInt &a);



	//Addition and Subtraction
	friend BigInt &operator+=(BigInt &, const BigInt &);
	friend BigInt operator+(const BigInt &, const BigInt &);
	friend BigInt &operator-=(BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);

    //Multiplication and Division
	friend BigInt &operator*=(BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);
	friend BigInt &operator/=(BigInt &, const BigInt &);
	friend BigInt operator/(const BigInt &, const BigInt &);

    //Modulo
	friend BigInt operator%(const BigInt &, const BigInt &);
	friend BigInt &operator%=(BigInt &, const BigInt &);

    //exponent
    friend BigInt &operator^=(BigInt &,const BigInt &);
    friend BigInt operator^(const BigInt &,const BigInt &);


    // function to read and write
    friend istream &operator>>(istream &,BigInt&);
    friend ostream &operator<<(ostream &,const BigInt &);

};

BigInt :: BigInt(long long nr){
    if(nr<0)
    {
        is_negative=true;
        nr-=2*nr;
    }
    do{
        digits.push_back(nr%10);
        nr/=10;
    }while(nr); 
}
//d
BigInt :: BigInt(const string &s){
    digits="";
    short int last_ind=0;
    if(s[0]=='-'){
    last_ind=1;
    is_negative=true;
    }

    for(int i=s.length()-1;i>=last_ind;i--)
    {
        if(s[i]<'0' || s[i]>'9')
        throw("ERROR");
        digits.push_back(s[i]-'0');
    }
}
//d
BigInt :: BigInt(const char* s){
    digits="";
    short int last_ind=0;
    if(s[0]=='-'){
    last_ind=1;
    is_negative=true;
    }
    for(int i=strlen(s)-1;i>=last_ind;i--)
    {
        if(s[i]<'0' || s[i]>'9')
        throw("ERROR");
        digits.push_back(s[i]-'0');
    }
}
//d
BigInt :: BigInt(const BigInt &b){
    this->digits=b.digits;
    this->is_negative=b.is_negative;
}
//d
bool Null(const BigInt& a){
    return (a.digits.size() == 1 && a.digits[0] == 0);
}
//d
int Length(const BigInt & a){
	return a.digits.size();
}
//d
BigInt mod(const BigInt & a){
     BigInt temp=a;
     temp.is_negative=false;
     return temp;
}

void divide_by_2(BigInt &a){
    int n=Length(a),t=0;
    for(int i=n-1;i>=0;i--)
    {
        int digit=(a.digits[i]>>1) + t;
        t=(a.digits[i]&1)*5;
        a.digits[i]=digit;
    }
    while(a.digits.size() > 1 && !a.digits.back())
	a.digits.pop_back();
}
//d
BigInt &BigInt::operator=(const BigInt& a){
    this->digits=a.digits;
    this->is_negative=a.is_negative;
    return *this;
}
//d
BigInt &helper_5(BigInt &a){
    int n=a.digits.length();
    int i=0;
    for(;i<n && a.digits[i] == 9;i++)
    a.digits[i]=0;
    if(i==n)
    a.digits.push_back(1);
    else
    a.digits[i]++;
    if(Null(a))
    a.is_negative=false;
    return a;

}
//d
BigInt &BigInt::operator++(){
    if(this->is_negative)
    {
        *this=helper_6(*this);
        if(Null(*this))
        this->is_negative=false;
        return *this;
    }
    return *this=helper_5(*this);
    
}
//d
BigInt &BigInt::operator-(){
    this->is_negative=!this->is_negative;
    return *this;
}
//d
BigInt BigInt::operator++(int temp){
   // The parameter int temp is not used within the function; it's just there to make the function signature unique.
   BigInt Aux(*this);
   ++(*this);
   return Aux;
}
//d
BigInt &helper_6(BigInt &a){
    int i=0,n=a.digits.length();
    for(;i<n && a.digits[i]==0;i++)
    a.digits[i]=9;

    a.digits[i]--;

    if(n>1 && a.digits[n-1]==0)
    a.digits.pop_back();

    return a;
}
//d
BigInt &BigInt::operator--(){
    if(Null(*this))
    {
        *this=helper_5(*this);
        this->is_negative=true;
        return *this;
    }
    if(this->is_negative)
    {
        return *this=helper_5(*this);
    }
    return *this=helper_6(*this);
}
//d
BigInt BigInt::operator--(int temp){
    BigInt Aux(*this);
    --(*this);
    return Aux;
}
//d
bool operator==(const BigInt& a, const BigInt& b){
    return (a.digits==b.digits && a.is_negative==b.is_negative);
}
//d
bool operator!=(const BigInt& a, const BigInt& b){
    return !(a.digits==b.digits);
}
//d
bool operator>(const BigInt &a, const BigInt &b){
    if(a.is_negative && !b.is_negative)
    return false;
    if(!a.is_negative && b.is_negative)
    return true;
    
    int n=Length(a),m=Length(b);
    bool ans;
    if(n!=m)
    {
        if(a.is_negative && b.is_negative)
        return n<m;
        return n>m;
    }
    int i;
    for(i=n-1;i>=0 && a.digits[i]==b.digits[i];i--);
    
    if(i<0)
    return false;

    if(a.digits[i]>b.digits[i])
    return (!a.is_negative && !b.is_negative);
    return (a.is_negative && b.is_negative);
    
}
//d
bool operator<(const BigInt &a, const BigInt &b){
    return b>a;
}
//d
bool operator>=(const BigInt& a,const BigInt& b){
    return !(a<b);
}
//d
bool operator<=(const BigInt& a,const BigInt& b){
    return  !(a>b);
}
//d
BigInt &helper_1(BigInt& a,const BigInt& b){

    int n=Length(a),m=Length(b);
    if(n<m)
    a.digits.append(m-n,0);
    n=Length(a);
    int t=0,carry=0;
    for(int i=0;i<n;i++)
    {
        if(i<m)
        t=a.digits[i]+b.digits[i]+carry;
        else
        t=a.digits[i]+carry;

        a.digits[i]=t%10;
        carry=t/10;
    }
    if(carry)
    a.digits.push_back(carry);
    return a;
}
//d
BigInt &operator+=(BigInt& a,const BigInt& b){
    BigInt a1=mod(a),b1=mod(b),ans;
    if((a.is_negative && b.is_negative) || (!a.is_negative && !b.is_negative))
    {
        ans=helper_1(a,b);
        ans.is_negative=a.is_negative;
        return a=ans;
    }
    if(a1>b1)
    {
       ans=helper_2(a1,b1);
       ans.is_negative=a.is_negative;
       return a=ans;
    }
    else if(a1<b1)
    {
       ans=helper_2(b1,a1);
       ans.is_negative=b.is_negative;
       return a=ans;
    }
    else
    {
        a=BigInt();
        return a; 
    }

}
//d
BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt ans;
    ans=a;
    ans+=b;
    return ans;
}
//d
BigInt &helper_2(BigInt &a, const BigInt &b){
    int borrow=0,curr,i,n=Length(a),m=Length(b);
    for(i=0;i<n;i++)
    {
        if(i<m)
        curr=a.digits[i]-b.digits[i]+borrow;
        else
        curr=a.digits[i]+borrow;

        if(curr<0)
        {
            curr+=10;
            borrow=-1;
        }
        else
            borrow=0;
        
        a.digits[i]=curr;
    }
    while(n > 1 && a.digits[n - 1] == 0)
		a.digits.pop_back(),
		n--;
    return a;

}
//d
BigInt &operator-=(BigInt &a, const BigInt &b){
    BigInt a1=mod(a),b1=mod(b),ans;
    if(!a.is_negative && !b.is_negative)
    {
        if(a1>=b1)
        ans=helper_2(a1,b1);
        else{
        ans=helper_2(b1,a1);
        ans.is_negative=true;
        }
    }
    else if(a.is_negative && b.is_negative)
    {
        if(a1>b1)
        {
            ans=helper_2(a1,b1);
            ans.is_negative=true;
        }
        else
        {
            ans=helper_2(b1,a1);
        }
    }
    else if(!a.is_negative && b.is_negative)
    {
        ans=helper_1(a1,b1);
    }
    else
    {
        ans=helper_1(a1,b1);
        ans.is_negative=true;
    }
    return a=ans;
}
//d
BigInt operator-(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp=a;
    temp-=b;
    return temp;
}
//d
BigInt &helper_3(BigInt& a,const BigInt& b){
    if(Null(a) || Null(b)){
		a = BigInt();
		return a;
	}
    int n=Length(a),m=Length(b),c=0,s;
    vector<int> ans(n+m,0);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            ans[i+j]+=a.digits[i]*b.digits[j];
        }
    }
    n+=m;
    a.digits.resize(n);

    for(int i=0;i<n;i++)
    {
        s=ans[i]+c;
        ans[i]=s%10;
        c=s/10;
        a.digits[i]=ans[i];
    }
    for (int i = n - 1; i >= 1 && !ans[i];i--)
			a.digits.pop_back();
	return a;

}
//d
BigInt &operator*=(BigInt &a, const BigInt &b){
    BigInt a1=mod(a),b1=mod(b),ans;
    ans=helper_3(a1,b1);
    if(Null(ans))
    return a=ans;
    if((a.is_negative && b.is_negative)|| (!a.is_negative && !b.is_negative))
    return a=ans;
    ans.is_negative=true;
    return a=ans;
}
//d
BigInt operator*(const BigInt&a ,const BigInt &b){
    BigInt ans;
    ans=a;
    ans*=b;
    return ans;
}
//d
BigInt &helper_4(BigInt& a,const BigInt& b){
    if(Null(b))
    throw("divide by zero error\n");
    if(a<b || Null(a))
    {
        a=BigInt(); // a=0.
        return a;
    }
    if(a==b)
    {
        a=BigInt(1);
        return a;
    }
  BigInt t;
  vector<int> question;
  int n=Length(a),cc,i;
  for(i=n-1;t*10+a.digits[i]<b;i--)
  t=t*10+a.digits[i];

  for(;i>=0;i--)
  {
    t=t*10+a.digits[i];
    for(cc=9;cc*b>t;cc--);

    t-=cc*b;
    question.push_back(cc);
  }
  n=question.size();
  a.digits.resize(n);
  for(i=0;i<n;i++)
  a.digits[i]=question[n-i-1];

  return a;

}
//d
BigInt &operator/=(BigInt& a,const BigInt& b){
    BigInt a1=mod(a),b1=mod(b),ans;
    ans=helper_4(a1,b1);
    if(Null(ans))
    return a=ans;
    if((a.is_negative && b.is_negative)|| (!a.is_negative && !b.is_negative))
    return a=ans;
    ans.is_negative=true;
    return a=ans;

}
//d
BigInt operator/(const BigInt&a , const BigInt& b){
    BigInt temp;
    temp=a;
    temp/=b;
    return temp;
}
// check operation
BigInt &operator%=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		return a;
	}
	if(a == b){
		a = BigInt();
		return a;
	}
	int i, lgcat = 0, cc;
	int n = Length(a), m = Length(b);
	vector<int> cat(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.digits[i] < b;i--){
		t *= 10;
		t += a.digits[i];
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a = t;
	return a;
}

BigInt operator%(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}
// update nth root 
BigInt &operator^=(BigInt& a,const BigInt &b){
  BigInt exp,base(a);
  exp=b;
  a=1;
  while(!Null(exp)){
    if(exp.digits[0] & 1)
    a*=base;
    base*=base;
    divide_by_2(exp);
  }
  return a;
}

BigInt operator^(const BigInt&a ,const BigInt&b){
    BigInt temp;
    temp=a;
    temp^=b;
    return temp;
}
//d
istream &operator>>(istream &in,BigInt&a){
  string s;
    in >> s; // Read input as string
    a.digits.clear(); // Clear existing digits
    a.is_negative=false;
    int last_ind=0;
    if(s[0]=='-')
    {
        a.is_negative=true;
        ++last_ind;
    }
    for (int i = s.size() - 1; i >= last_ind; i--) {
        if (!isdigit(s[i])) {
            // Invalid input format
            throw("INVALID NUMBER");
        }
        a.digits.push_back(s[i] - '0'); // Convert char to digit and store
    }
    return in;
}
//d
ostream &operator<<(ostream &out,const BigInt &a){
    if(a.is_negative)
    cout<<"-";
	for (int i = a.digits.size() - 1; i >= 0;i--)
		cout << (short)a.digits[i];
	return cout; // return cout allows for chaining of multiple << operations.
}
