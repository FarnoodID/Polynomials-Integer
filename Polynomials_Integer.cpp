#include<iostream>
#define N 100
using namespace std;

class Term
{
    public:
        char mark;
        int a=0,n=0,isPlus=0;
        void checkPlus()
        {
            if (mark=='+')
                isPlus=1;
        }
};
class Polynomial
{
    public:
        friend Polynomial operator+(Polynomial poly1,Polynomial poly2);
        friend Polynomial operator-(Polynomial poly1,Polynomial poly2);
        friend Polynomial operator+=(Polynomial poly1,Polynomial poly2);
        friend Polynomial operator*(Polynomial poly1,Polynomial poly2);
        Polynomial(Term myTerm[N],int P)
        {
            pLen=P;
            aLen=P;
            for (int i=0;i<pLen;i++)
                term[i]=myTerm[i];
        }
        ~Polynomial(){}
        int makeSimple()
        {
            for (int i=0;i<(pLen-1);i++)
            {
                if (term[i].n<0)
                    continue;
                for (int j=i+1;j<pLen;j++)
                {
                    if (term[i].n==term[j].n)
                    {
                        term[i].a+=term[j].a;
                        if (term[i].a>=0)
                        {
                            term[i].isPlus=1;
                            term[i].mark='+';
                        }
                        else
                        {
                            term[i].isPlus=0;
                            term[i].mark='-';
                        }
                        term[j].n=-1;
                        aLen--;
                    }
                }
            }
            sorted();
            return aLen;
        }
        void sorted()
        {
            Term tmp;
            for (int i=0;i<pLen-1;i++)
                for (int j=i+1;j<pLen;j++)
                {
                    if (term[i].n<term[j].n)
                    {
                        tmp=term[j];
                        term[j]=term[i];
                        term[i]=tmp;
                    }
                }
        }
        void print()
        {
            int flag=0;
            for (int i=0;i<aLen;i++)
            {
                if (term[i].a==0)
                    continue;
                cout<<term[i].mark<<abs(term[i].a)<<"x^"<<term[i].n;
                flag=1;
            }
            if (flag==0)
               cout<<"+0x^0";
            cout<<endl;
        }
    private:
        Term term[N];
        int aLen=0,pLen=0;
};
Polynomial operator+(Polynomial poly1,Polynomial poly2)
{
    Polynomial tmp=poly1;
    tmp.pLen=poly1.aLen;
    for(int i=0;i<poly2.aLen;i++)
    {
        int flag=0;
        for(int j=0;j<tmp.pLen;j++)
        {
            if(tmp.term[j].n==poly2.term[i].n)
            {
                tmp.term[j].a+=poly2.term[i].a;
                flag=1;
                if (tmp.term[j].a>=0 )
                {
                    tmp.term[j].isPlus=1;
                    tmp.term[j].mark='+';
                }
                else if (tmp.term[j].a<0 )
                {
                    tmp.term[j].isPlus=0;
                    tmp.term[j].mark='-';
                }
                break;
            }
        }
        if (flag==0)
        {
            tmp.term[tmp.aLen]=poly2.term[i];
            tmp.aLen++;
            tmp.pLen++;
        }
    }
    tmp.makeSimple();
    return tmp;
}
Polynomial operator+=(Polynomial poly1,Polynomial poly2)
{
    Polynomial tmp=poly1;
    tmp.pLen=poly1.aLen;
    for(int i=0;i<poly2.aLen;i++)
    {
        int flag=0;
        for(int j=0;j<tmp.pLen;j++)
        {
            if(tmp.term[j].n==poly2.term[i].n)
            {
                tmp.term[j].a+=poly2.term[i].a;
                flag=1;
                if (tmp.term[j].a>=0 )
                {
                    tmp.term[j].isPlus=1;
                    tmp.term[j].mark='+';
                }
                else if (tmp.term[j].a<0 )
                {
                    tmp.term[j].isPlus=0;
                    tmp.term[j].mark='-';
                }
                break;
            }
        }
        if (flag==0)
        {
            tmp.term[tmp.aLen]=poly2.term[i];
            tmp.aLen++;
            tmp.pLen++;
        }
    }
    tmp.makeSimple();
    tmp.print();
    return tmp;
}
Polynomial operator-(Polynomial poly1,Polynomial poly2)
{
    Polynomial tmp=poly1;
    tmp.pLen=poly1.aLen;
    for(int i=0;i<poly2.aLen;i++)
    {
        int flag=0;
        for(int j=0;j<tmp.pLen;j++)
        {
            if(tmp.term[j].n==poly2.term[i].n)
            {
                tmp.term[j].a-=poly2.term[i].a;
                if (tmp.term[j].a>=0 )
                {
                    tmp.term[j].isPlus=1;
                    tmp.term[j].mark='+';
                }
                else if (tmp.term[j].a<0)
                {
                    tmp.term[j].isPlus=0;
                    tmp.term[j].mark='-';
                }
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            tmp.term[tmp.aLen]=poly2.term[i];
            if(tmp.term[tmp.aLen].isPlus==1)
            {
                tmp.term[tmp.aLen].isPlus=0;
                tmp.term[tmp.aLen].mark='-';
            }
            else
            {
                tmp.term[tmp.aLen].isPlus=1;
                tmp.term[tmp.aLen].mark='+';
            }
            tmp.aLen++;
            tmp.pLen++;
        }
    }
    tmp.makeSimple();
    return tmp;
}
Polynomial operator*(Polynomial poly1,Polynomial poly2)
{
    Polynomial tmp=poly1;
    tmp.aLen=0;
    tmp.pLen=0;
    for (int i=0;i<poly1.aLen;i++)
    {
        for (int j=0;j<poly2.aLen;j++)
        {
            tmp.term[tmp.aLen].a=poly1.term[i].a*poly2.term[j].a;
            tmp.term[tmp.aLen].n=poly1.term[i].n+poly2.term[j].n;
            if (tmp.term[tmp.aLen].a>=0)
            {
                tmp.term[tmp.aLen].mark='+';
                tmp.term[tmp.aLen].isPlus=1;
            }
            else if (tmp.term[tmp.aLen].a<0)
            {
                tmp.term[tmp.aLen].mark='-';
                tmp.term[tmp.aLen].isPlus=0;
            }
            tmp.aLen++;
            tmp.pLen++;
        }
    }
    tmp.makeSimple();
    return tmp;
}
int main()
{
    Term term1[N];
    Term term2[N];
    cout<<"Enter two polynomials in the next two lines:\t\t\t(like this;+9x^3-6x^4-3x^0)"<<endl;
    int P1=0,P2=0,A1=0,A2=0;
    string tmp;
    for (int i=0;i<N;i++)
    {
        term1[i].mark=getchar();
        if (term1[i].mark=='\n')             //check if end of line
            break;
        term1[i].checkPlus();                //check if +
        cin>>term1[i].a;
        if(term1[i].isPlus==0)
            term1[i].a*=-1;
        getchar();getchar();                 //passing x and ^
        cin>>term1[i].n;
        P1++;
    }
    Polynomial poly1(term1,P1);
    A1=poly1.makeSimple();
    for (int i=0;i<N;i++)
    {
        term2[i].mark=getchar();
        if (term2[i].mark=='\n')             //check if end of line
            break;
        term2[i].checkPlus();                //check if +
        cin>>term2[i].a;
        if(term2[i].isPlus==0)
            term2[i].a*=-1;
        getchar();getchar();                 //passing x and ^
        cin>>term2[i].n;
        P2++;
    }
    Polynomial poly2(term2,P2);
    A2=poly2.makeSimple();
    cout<<"now enter '+', '-', '*' or '+=' to see results:\t\t\t(for exit just type 'exit')"<<endl;
    while(1)
    {
        cin>>tmp;
        if(tmp=="exit")
            break;
        else if (tmp=="*")
        {
            Polynomial poly3=poly1*poly2;
            poly3.print();
        }
        else if (tmp=="+")
        {
            Polynomial poly3=poly1+poly2;
            poly3.print();
        }
        else if (tmp=="-")
        {
            Polynomial poly3=poly1-poly2;
            poly3.print();
        }
        else if (tmp=="+=")
        {
            Polynomial poly3=poly1+=poly2;
            poly1=poly3;
            poly3.print();
        }
    }
}
