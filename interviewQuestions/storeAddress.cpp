#include <iostream>
using namespace std;

struct node{
    int key;
    struct node* next;
};

int main(){
    struct node* A[2];

    struct node* p = new(struct node);
    struct node* q = new(struct node);

    p->key = 0;
    q->key = 1;

    p->next = q;
    q->next = NULL;

    A[0] = p;
    A[1] = q;

    cout << p << " " << A[0] << "\n";

    return 0;

}
