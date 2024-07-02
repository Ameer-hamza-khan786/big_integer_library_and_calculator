//bismill..
#include "big_int_library.cpp"
#include<stack>
#include <unistd.h> // for sleep 1ction


int prec(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;  // Default, used for parentheses or unknown operators
}

string infixtopost(string exp){
    stack<char> s;
    string result="";
    for(int i=0;i<exp.length();i++)
    {
        char c=exp[i];
        if((c>='a' && c<='z') || (c>='A' && c<='Z') ||(c>='0' && c<='9'))
        result+=c;
        else if(c=='(')
        s.push(c);
        else if(c==')')
        {
            while(s.top()!='(')
            {
                result+=s.top();
                s.pop();
            }
            s.pop();// poping (
        }
        else {
            result+=" ";
            while(!s.empty() && (prec(s.top())>=prec(c))){
                result+=s.top();
                s.pop();
            }
            s.push(c);
        }

    }
    while(!s.empty())
    {
        result+=s.top();
        s.pop();
    }

    return result;
}

void two_number_calculator(){

    BigInt a,b;
    char c=1;
    while(c!='C'){
    cout<<"ENTER TWO NUMBERS\n";
    cin>>a>>b;
    cout<<"CHOOSE OPERATOR\n";
    cin>>c;
    switch (c)
    {
    case '+':
        cout<<a+b<<endl;
        break;
    case '-':
        cout<<a-b<<endl;
        break;
    case '*':
        cout<<a*b<<endl;
        break;
    case '/':
        cout<<a/b<<endl;
        break;
    case '%':
        cout<<a%b<<endl;
        break;
    case '^':
        cout<<(a^b)<<endl;
        break;
    default:
        break;
    }
    }
}

BigInt getvalue(BigInt a,BigInt b,char c){
    BigInt ans;
    switch (c)
    {
    case '+':ans= b+a;
        break;
    case '-':ans= b-a;
        break;
    case '*':ans= b*a;
        break;
    case '/':ans= b/a;
        break;
    case '^':ans= (b^a);
        break;
    default:ans= BigInt();
        break;
    }
    return ans;
}
BigInt evalutate(string& b){
    BigInt p,q,e;
    stack<BigInt> s;
    string num;
    for(int i=0;b[i]!='\0';i++)
    {
        char c=b[i];
        if(c>='0'&& c<='9')
        num+=c;
        else if(c==' ')
        {
            if(num!="")
            s.push(BigInt(num));
            num="";
        }
        else{
            if(num!="")
            s.push(BigInt(num));
            num="";
            p=s.top();
            s.pop();
            if(s.empty()){
                return p;
            }
            q=s.top();
            s.pop();
            e=getvalue(p,q,c);
            s.push(e);
        }
    }

    
    return s.top();
}
void expression(){
    string exp;
    cout<<"ENTER THE EXPRESSION IN INFIX FORM\n";
    cin>>exp;
    exp=infixtopost(exp);
    cout<<exp<<endl;
    cout<< "result of expression is --> "<<evalutate(exp)<<endl;
}


void display() {
    system("cls"); // Clear the console screen (for Windows); use "clear" for Unix-like systems
    printf("\t ___________________________\n"); sleep(.5);
    printf("\t|                          |\n"); sleep(.5);
    printf("\t|   WELCOME TO ZILLION     |\n"); sleep(1); 
    printf("\t|     !!CALCULATOR!!       |\n"); sleep(1); 
    printf("\t|__________________________|\n"); sleep(.5);
    printf("\t|  ______________________  |\n"); sleep(.5);
    printf("\t| |  7  |  8  |  9  |  * | |\n"); sleep(1); 
    printf("\t| |_____|_____|_____|____| |\n"); sleep(.5); 
    printf("\t| |  4  |  5  |  6  |  / | |\n"); sleep(.5); 
    printf("\t| |_____|_____|_____|____| |\n"); sleep(.5); 
    printf("\t| |  1  |  2  |  3  |  _ | |\n"); sleep(.5); 
    printf("\t| |_____|_____|_____|____| |\n"); sleep(.5); 
    printf("\t| |  0  |  .  |  =  |  + | |\n"); sleep(.5); 
    printf("\t| |_____|_____|_____|____| |\n"); sleep(.5); 
    printf("\t|__________________________|\n\n"); sleep(.5); 
}

int main()
{
    char c;
    display(); 
    cout<<"PRESS 1 FOR TWO CALCULATOR\nPRESS 2 FOR EXPRESSION EVALUATION\n";
    cin>>c;
    switch(c){
        case '1':
        two_number_calculator();
        break;
        case '2':
        expression();
        break;
    }
    return 0;
}

/*
karatssuba algorit
*/