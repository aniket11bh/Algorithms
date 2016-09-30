#include <iostream>

using namespace std;

struct node{
  int data;
  struct node* next;
};

struct node* NewNode(int key){
  struct node* temp = new(struct node);

  temp->data = key;
  temp->next = NULL;

  return temp;
}

struct node* InsertKey(struct node* root, int key){
  if (root == NULL) return NewNode(key);

  root->next = InsertKey(root->next, key);

  return root;
}

struct node* AddTheLoop(struct node* root, int X){

    struct node* temp = root;
    struct node* tempX = NULL;

    if (temp == NULL) return NULL;

    // traverse to last node
    while(temp->next != NULL){
        temp = temp->next;
    }

    for(int i=0; i<X; i++){
      if(i == 0) tempX = root;
      else tempX = tempX->next;
    }
    temp->next = tempX;

    return temp;
}

bool search(struct node* A[], int size, struct node* temp){

    bool address = 0;
    
    if (temp == NULL) return 1;
    for(int i=0; i<size; i++){
        if (A[i] == temp)
        {
            address = 1;
            return address;
        }
        else address = 0;
    }
    return address;
}

void removeTheLoop(struct node *list)
{
    struct node * temp = list;
    struct node * tempParent = list;
    struct node * A[300];
    int i = 0;
    int address = 0;

    while (! address){
        A[i] = temp;
	    tempParent = temp;
        temp = temp->next;
        i = i+1;
        address = search(A, i, temp);
    }

     tempParent->next = NULL;
}

int main(){

  unsigned int T, N, X;
  int key;
  struct node* A[300];

  cin >> T;

  for(int i=0; i<T; i++){
    cin >> N;
    struct node* A[N];

    for(int j=0; j<N; j++){
      cin >> key;
      A[i] = InsertKey(A[i], key);
    }

    cin >> X;
    A[i] = AddTheLoop(A[i], X);
  }

  for(int i=0; i<T; i++)
    removeTheLoop(A[i]);

  return 0;
}
