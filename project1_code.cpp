#include <fstream>
#include <string>
#include <queue>

using namespace std;
int main(int argc,char* argv[]){
    int i,j,n,m,pos,posd,tmp,count=0,value_d,*A;
    fstream fs;
    string str(argv[1]); 

    queue<int> ind;

    fs.open(str+"/matrix.data", ios::in );
    if(!fs) return 1;

    fs>>m>>n;

    A = new int[2*(n+1)+1];
    A[0] = -2147483648;
    for(j=n+1;j<2*(n+1)+1;j++) A[j] = -2147483648;
    for(j=1;j<=n;j++) fs>>A[j];

    for(i=1;i<m;i++){
        for(j=0;j<n;j++){
            pos = 1+(n+1)*(i%2)+j;
            posd = 1+(n+1)*((i+1)%2)+j;
            value_d = A[posd];
            fs>>tmp;
            if( value_d>=tmp && value_d>=A[posd-1] && value_d>=A[posd+1] && value_d>=A[pos] ){
                ind.push(i-1); ind.push(j);
                count++;
            }
            A[pos] = tmp;
        }
    }
    //last
    for(j=0;j<n;j++){
        pos = 1+(n+1)*(i%2)+j;
        posd = 1+(n+1)*((i+1)%2)+j;
        value_d = A[posd];
        if( value_d>=A[pos] && value_d>=A[posd-1] && value_d>=A[posd+1] ) {
            ind.push(i-1); ind.push(j);
            count++;
        }
    }
    fs.close();
    fs.open(str+"/final.peak", ios::out );
    fs<<count<<endl;
    while(!ind.empty()) {
        fs<<ind.front()<<" ";
        ind.pop();
        fs<<ind.front()<<endl;
        ind.pop();
    }
    fs.close();

    delete [] A;
    return 0;
}
