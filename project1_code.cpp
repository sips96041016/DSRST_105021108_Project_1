#include <iostream>
#include <fstream>
using namespace std;
int main(void){
    int i,j,n,m,pos,posd,posu,value_d,*A;
    fstream fs;

    fs.open("matrix.data", ios::in );
    if(!fs) return 1;

    fs>>m>>n;

    A = new int[3*(n+2)];
    for(j=0;j<n+2;j++) { A[(n+2)+j] = -2147483648; A[2*(n+2)+j] = -2147483648; }
    A[0] = -2147483648;
    for(j=1;j<=n;j++) fs>>A[j];
    A[n+1] = -2147483648;

    for(i=1;i<m;i++){
        for(j=1;j<=n;j++){
            pos = (n+2)*(i%3)+j;
            posd = (n+2)*((i+2)%3)+j;
            posu = (n+2)*((i+1)%3)+j;
            value_d = A[posd];
            fs>>A[pos];
            if( value_d>=A[posu] && value_d>=A[posd-1] && value_d>=A[posd+1] && value_d>=A[pos] )
                cout<<i-1<<" "<<j-1<<endl;
        }
    }
    //last
    for(j=1;j<=n;j++){
        posd = (n+2)*((i+2)%3)+j;
        posu = (n+2)*((i+1)%3)+j;
        value_d = A[posd];
        if( value_d>=A[posu] && value_d>=A[posd-1] && value_d>=A[posd+1] ) cout<<i-1<<" "<<j-1<<endl;
    }
    fs.close();
    return 0;
}
