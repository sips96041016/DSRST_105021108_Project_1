#include <fstream>
#include <string>

#include <iostream>
#include <time.h>

using namespace std;
int main(int argc,char* argv[]){

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int i,j,n,m,pos,posd,posu,value_d,*A;
    int count = 0;
    fstream fs;
    string str(argv[1]); 

    fs.open(str+"/matrix.data", ios::in );
    if(!fs) return 1;

    fs>>m>>n;

    A = new int[(m+2)*(n+2)];
    for(j=0;j<n+2;j++) { A[j] = -2147483648; A[(m+1)*(n+2)+j] = -2147483648; }
    A[(n+2)] = -2147483648;
    for(j=1;j<=n;j++) fs>>A[(n+2)+j];
    A[(n+2)+j] = -2147483648;

    for(i=2;i<m+1;i++){
        A[(n+2)*i] = -2147483648;
        for(j=1;j<=n;j++){
            pos = (n+2)*i+j;
            posd = (n+2)*(i-1)+j;
            posu = (n+2)*(i-2)+j;
            value_d = A[posd];
            fs>>A[pos];
            if( value_d>=A[posu] && value_d>=A[posd-1] && value_d>=A[posd+1] && value_d>=A[pos] ) count++;
        }
        A[(n+2)*i+j] = -2147483648;
    }
    //last
    A[(n+2)*i] = -2147483648;
    for(j=1;j<=n;j++){
        posd = (n+2)*m+j;
        posu = (n+2)*(m-1)+j;
        value_d = A[posd];
        if( value_d>=A[posu] && value_d>=A[posd-1] && value_d>=A[posd+1] ) count++;
    }
    A[(n+2)*i+j] = -2147483648;
    fs.close();
    fs.open(str+"final.peak", ios::out );
    fs<<count<<endl;
    for(i=2;i<m+2;i++) for(j=1;j<n+1;j++){
        pos = (n+2)*i+j;
        posd = (n+2)*(i-1)+j;
        posu = (n+2)*(i-2)+j;
        value_d = A[posd];
        if( value_d>=A[posu] && value_d>=A[posd-1] && value_d>=A[posd+1] && value_d>=A[pos] ) fs<<i-2<<" "<<j-1<<endl;
    }
    fs.close();

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<cpu_time_used<<endl;

    delete [] A;
    return 0;
}
