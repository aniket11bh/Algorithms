#include <iostream>

using namespace std;

struct indexPair{
    int i;
    int j;
};

void swap(int* A, int* B){
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
}
void swapQ(struct indexPair* A, struct indexPair* B){
    struct indexPair temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

void printArray(int *A, int size){
    for(int i=0; i<size; i++){
        cout << A[i] << " ";
    }
    cout << "\n";
}

void printIndexPair(struct indexPair A){
    cout << A.i << ", " << A.j;
}

void printArrayQ(struct indexPair* Q, int l){
    for(int i=0; i<l; i++){
        printIndexPair(Q[i]);
        cout << "\n";
    }
}

void buildheap(int* S, int l){

    for(int i=1; i<l; i++){
        int j = i;
        int parentIndex = (j-1)/2;
        while(S[parentIndex] > S[j]){
            swap( &S[parentIndex], &S[j]);
            j = parentIndex;
            parentIndex = (j-1)/2;
        }
    }
}

void buildheapQ(struct indexPair* Q, int* A, int* B, int l){

    for(int i=1; i<l; i++){
        int j = i;
        int parentIndex = (j-1)/2;
        while(A[Q[parentIndex].i-1]+B[Q[parentIndex].j-1] > A[Q[j].i-1]+B[Q[j].j-1]){
            swapQ( &Q[parentIndex], &Q[j]);
            j = parentIndex;
            parentIndex = (j-1)/2;
        }
    }
}

int extractmin(int* S, int* l){
    int min = S[0];
    int len = *l;
    (*l)--;
    swap(&S[0], &S[len-1]);
    buildheap(S, len-1);
    return min;
}

struct indexPair extractQ(struct indexPair* Q, int* A, int* B, int* l){
    struct indexPair min = Q[0];
    int len = *l;
    (*l)--;
    swapQ(&Q[0], &Q[len-1]);
    buildheapQ(Q, A, B, len-1);
    return min;
}

void method1(int* A, int* B, int m, int n, int k){

    // Create sum and build it's minheap
    int p = m*n;
    int Sum[p];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            Sum[i*n + j] =  A[i] + B[j];
        }
    }
    buildheap(Sum, p);

    for(int i=0; i<k; i++){
        cout << extractmin(Sum, &p) << " ";
    }
}

void insertQ(struct indexPair* Q, int* l, struct indexPair I){
    Q[(*l)++] = I;
}

void method2(int* A, int* B, int m, int n, int k){

    // convert A and B to corresponding min heaps
    buildheap(A, m);
    buildheap(B, n);
    struct indexPair Q[8*k+1];
    int l = 0; // size of Q

    struct indexPair I, J, Jprev; // doubt with new()
    I.i = 1; I.j = 1;

    insertQ(Q, &l, I);
    buildheapQ(Q, A, B, l);

    for(int i=0; i<k; i++){
        // extract
        J = extractQ(Q, A, B, &l);
        if (J.i == Jprev.i && J.j == Jprev.j){
            i--;
        }
        else {
            cout << A[J.i - 1] + B[J.j - 1] << " = A[" << J.i << "] + B[" << J.j << "] = " << A[J.i - 1] << " + " << B[J.j - 1] << "\n";
            Jprev = J;

            // Insert
            I.i = 2*J.i; I.j = J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = 2*J.i+1; I.j = J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = J.i; I.j = 2*J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = J.i; I.j = 2*J.j+1;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            buildheapQ(Q, A, B, l);
        }
    }

}

void method3(int* A, int* B, int m, int n, int k){

    // convert A and B to corresponding min heaps
    buildheap(A, m);
    buildheap(B, n);
    struct indexPair Q[8*k+1];
    int l = 0; // size of Q

    struct indexPair I, J, Jprev; // doubt with new()
    I.i = 1; I.j = 1;

    insertQ(Q, &l, I);
    buildheapQ(Q, A, B, l);

    for(int i=0; i<k; i++){
        // extract
        J = extractQ(Q, A, B, &l);
        if (J.i == Jprev.i && J.j == Jprev.j){
            i--;
        }
        else {
            cout << A[J.i - 1] + B[J.j - 1] << " = A[" << J.i << "] + B[" << J.j << "] = " << A[J.i - 1] << " + " << B[J.j - 1] << "\n";
            Jprev = J;

            // Insert
            I.i = 2*J.i; I.j = J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = 2*J.i+1; I.j = J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = J.i; I.j = 2*J.j;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            I.i = J.i; I.j = 2*J.j+1;
            if (I.i <= m && I.j <= n)   insertQ(Q, &l, I);

            buildheapQ(Q, A, B, l);
        }
    }

}

int main(){

    int m, n, k;

    cin >>  m;
    int A[m];
    cout << "++++ A : \n";
    for(int i=0; i<m; i++)
        cin >> A[i];

    cin >> n;
    cout << "++++ B : \n";
    int B[n];
    for(int i=0; i<n; i++)
        cin >> B[i];

    cin >> k;
    cout << "++++ Method1 :";
    method1(A, B, m, n, k);
    cout << "\n";
    /*


    cout << "++++ Method2 : \n";
    method2(A, B, m, n, k);
    */

    cout << "++++ Method3 : \n";
    method3(A, B, m, n, k);

    return 0;

    /* Test case :

    647 225 200 137 823 241 923 173 633 797 203 797 820 789 338 72 274 407
    577 306 167 928 40 417 86 751 384 697 144 986 665 468 225 121 372 143 86 737 86 4
    557 874 341 628 148 748 852 212 50 656 681 153 353 824 8 176 783 993 559 970 936 399 61 882

    206 354 757 547 700 623 14 623 514 646 194 444 414 849 125 566 202 948 292 96
    732 285 374 702 940 772 762 737 974 559 620 898 631 96 445 331 437 177 672 951
    822 866 395 955 715 520 240 636 187 532 731 637 535 823 339 475 314 819 931 7

    304 530 283 99 580 567 424 995 790 467 919 332 907 40 812 503 540 613 895 512
    320 550 174 859 780 702 492 196 894 261 16 916 510 298 15 808 864 438 804 373
    623 442 704 249 481 516 751 21 847 646 251 167 196 425 744 695 845 236 609 458
    216 624 374 725

    640 107 252 223 263 774 595 885 934 300 852 416 534 603 155 382 968 125 267 882
    268 12 296 113 247 904 570 462 247 662 905 886 487 876 827 749 650 142 353 585
    160 205 719 693 526 592 793 494 435 61 96 702 72 391 814 37 296 103 499 261
    */
}
