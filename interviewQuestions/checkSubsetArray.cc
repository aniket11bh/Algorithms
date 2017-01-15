#include <iostream>
#include <map>

using namespace std;

void printArray(int* A, int size){
    for(int i=0; i<size; i++)
        cout << A[i] << " ";
    cout << "\n";
}

bool checkSubset(int* A, int* B, int m, int n){
    map<int, int> hashmap;

    for(int i=0; i<m; i++){
        hashmap[A[i]] = A[i];
    }
    if(n == 0)  return 0;
    for(int j=0; j<n; j++){
        if ( hashmap.find(B[j]) == hashmap.end() )
            return 0;
    }
    return 1;
}

int main(){

    int m, n;
    cin >> m >> n;

    int A[m], B[n];

    for(int i=0; i<m+n; i++){
        if(i<m){
            cin >> A[i];
        }
        else{
            cin >> B[i-m];
        }
    }

    cout << "Subarray : "<< checkSubset(A, B, m, n) << "\n";


    return 0;
}
