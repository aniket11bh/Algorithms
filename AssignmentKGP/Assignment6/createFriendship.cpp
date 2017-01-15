#include <bits/stdc++.h>
using namespace std;

typedef vector< pair<int, int> > v1;
typedef vector< vector< bool> > v2;

void printv(v1 &A){
    for(int i=0; i<A.size(); i++){
        cout << A[i].second << " ";
    }
    cout << "\n";
}

void printvT(v1 &A){
    for(int i=0; i<A.size(); i++){
        cout << A[i].first << " ";
    }
    cout << "\n";
}

void printM(v2 M){
    for(int i=0; i<M.size(); i++){
        for(int j=0; j<M[0].size(); j++){
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
}

void swapf(pair<int ,int> &a, pair<int, int> &b){
    pair<int ,int> temp = a;
    a = b;
    b = temp;
}

v1 cSort(v1 &A){
    vector<int> count(A.size(), 0);
    v1 arr(A.size());

    for(int i=0; i<A.size(); i++){
        count[A[i].second]++;
    }

    for(int i=1; i<A.size(); i++){
        count[i] += count[i-1];
    }

    for(int i=0; i<A.size(); i++){
        arr[count[A[i].second]-1] = A[i];
        count[A[i].second]--;
    }

    return arr;
}

bool friendship(v1 &A, v2 &M){

    // delete zeros
    v1::iterator b = A.begin();
    for(v1::iterator a=A.begin(); a!=A.end(); a++){
        if(a->second != 0){
            if(a->first != b->first)
                swapf(*a, *b);
            b++;
        }
    }
    if(b->first == 0) return true;

    // do counting sort & find max
    A = cSort(A);
    printv(A);
    printvT(A);
    cout << "\n";

    // loop
    for(int i=A.size()-1; i>=0; i--){
        for(int j=i; j>=i-A[i].second; j--){
            M[A[i].first][A[j].first] = 1;
            M[A[j].first][A[i].first] = 1;
            A[j].second--;
        }
    }
    return 0;
}

int main(){
    int n;
    cin >> n;

    v1 A;
    v2 M(n, vector<bool> (n,0));

    for(int i=0; i<n; i++){
        int f;
        cin >> f;
        A.push_back(make_pair(i, f));
    }
    friendship(A, M);
    printM(M);

    return 0;
}
