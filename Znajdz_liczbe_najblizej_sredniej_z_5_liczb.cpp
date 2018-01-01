#include <iostream>
#include <cmath>

using namespace std;

float a,b,c,d,e;
float sr,x,r;
float y=9989;

int main()
{
    cout << "Podaj 5 liczby rozdzielone spacja: ";
    cin>>a>>b>>c>>d>>e;

    sr=(a+b+c+d+e)/5;

    cout<<endl<<"Srednia: "<<sr<<endl;

    x=a;
    r=sr-a;

    if(abs(r)>=abs(sr-b))
        {
            x=b;
            if(abs(r)==abs(sr-b)) y=-r+sr;
            r=sr-b;
        }
    if(abs(r)>=abs(sr-c))
        {
            x=c;
            if(abs(r)==abs(sr-c)) y=-r+sr;
            r=sr-c;
        }
    if(abs(r)>=abs(sr-d))
        {
            x=d;
            if(abs(r)==abs(sr-d)) y=-r+sr;
            r=sr-d;
        }
    if(abs(r)>=abs(sr-e))
        {
            x=e;
            if(abs(r)==abs(sr-e)) y=-r+sr;
            r=sr-e;
        }
		
    cout<<endl<<"Liczba najblizsza sredniej: "<<x<<" ";
    
	if (y!=9989 && y!=x) cout<<y;
    
	cout<<endl;
    
	return 0;
}
