#include <iostream>
#include <cstring>

using namespace std;

struct Node{
    bool EOSflag;
    struct Node* left_child;
    struct Node* right_child;
};

struct QNode{
    int key;
    struct QNode* next;
};

struct Packet{
    char str[100];
    struct Node* node;
    struct Packet* next;
};

void pushFront(struct QNode** headRef, int a){

	struct QNode* newHead = new(struct QNode);
	newHead->key = a;
	newHead->next = *headRef;
	*headRef = newHead;
}

int PopFront(struct QNode** headRef){
    int pop;
	struct QNode* temp = *headRef;

	if(temp != NULL){
        pop = (*headRef)->key;
		*headRef = temp->next;
	}
    return pop;
}

void Display(struct QNode* node)
{
     struct QNode* temp = node;

     if(temp != NULL)
     {
           cout << "Elements are : ";
           while(temp != NULL)
           {
                cout << temp->key << " ";
                temp = temp->next;
           }
     cout << "\n";
     }
     else
     cout << "\nQueue is Empty";
}

struct Node* NewNode(int key){

    struct Node* temp = new(struct Node);
    temp->EOSflag = key;
    temp->left_child = NULL;
    temp->right_child = NULL;

    return temp;
}

struct Packet* NewPacket(struct Node* node){

    struct Packet* temp = new(struct Packet);
    temp->node = node;
    temp->next = NULL;
    // temp->str = {};

    return temp;
}

void pushPacketInFront(struct Packet** headRef, struct Packet* packet){

	packet->next = *headRef;
	*headRef = packet;
}

struct Packet* PopPacketFromBack(struct Packet** packet){

    struct Packet* temp = *packet;
    struct Packet* prev = *packet;

    if(*packet == NULL) {
        cout << "packet Empty, Returning null\n";
        return NULL;
    }

    if((temp->next) == NULL){
        *packet = NULL;
        // cout << "Packet became empty\n";
        return temp;
    }

    while((temp->next) != NULL){
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;

    return temp;
}

void printString(char*s, int size){
    for(int i=0; i<size; i++){
        cout << s[i];
    }
    cout << " ";
}

void PreOrderTraversal(struct Node* node, int i, char* str){
    if (node == NULL)   return;

    if (node->EOSflag){
        // cout << node->EOSflag << " " << i << "\n";
        if (i < 0)
            cout << "e ";
        else
            printString(str, i+1);
    }

    i++;
    str[i] = '0';
    PreOrderTraversal(node->left_child, i, str);
    str[i] = '1';
    PreOrderTraversal(node->right_child, i, str);

}

void Insert(struct Node** root, struct QNode* head){
    // create a node
    if(*root == NULL)
        *root = NewNode(0);

    if(head == NULL){
        (*root)->EOSflag = 1;
        return;
    }

    int pop_flag = PopFront(&head);
    // cout << "Pop : " << pop_flag;

    if(pop_flag == 0){
        // cout << "left \n";
        Insert(&((*root)->left_child), head);
    }
    else if(pop_flag == 1){
        // cout << "right \n";
        Insert(&((*root)->right_child), head);
    }
    return;
}

struct Node* Find(struct Node* node, struct QNode* head){
    if(node == NULL) return NULL;
    if(head == NULL) return node;

    int pop_flag = PopFront(&head);
    if(pop_flag) {
        // cout << "Right , "<< node->EOSflag <<"\n";
        return Find(node->right_child, head);
    }
    else {
        // cout << "Left , "<< node->EOSflag <<"\n";
        return Find(node->left_child, head);
    }
}

struct Node* FindJoint(struct Node* root, struct QNode* head){
    struct Node* temp = root;
    struct Node* node = root;
    int pop_flag, direction;
    // if (root == NULL) return;
    while(head != NULL){
        pop_flag = PopFront(&head);
        if(pop_flag){
            // Right
            if((temp->left_child != NULL) || (temp->EOSflag == 1)){
                node = temp;
                direction = 1;
            }
            temp = temp->right_child;
        }
        else{
            // Left
            if((temp->right_child != NULL) || (temp->EOSflag == 1)){
                node = temp;
                direction = 0;
            }
            temp = temp->left_child;
        }
    }
    if(direction){
        node->right_child = NULL;
    }
    else{
        node->left_child = NULL;
    }
    return root;
}

struct Node* Delete(struct Node* node, struct QNode* head){
    struct Node* find_node;
    find_node = Find(node, head);

    if(find_node == NULL) return node;

    else if(find_node->EOSflag == 1)
    {
        if((find_node->left_child != NULL) || (find_node->right_child != NULL))
        {
            find_node->EOSflag = 0;
            return node;
        }
        else
        {
            // cout << "A leaf \n";
            return FindJoint(node, head);
        }
    }

    else
        return node;
}

void PrintTree(struct Node* node){
    char str[100];
    PreOrderTraversal(node, -1, str);
}

int NumberOfElements(struct Packet* packet){
    if(packet == NULL) return 0;
    int i=0;
    while (packet != NULL) {
        i++;
        packet = packet->next;
    }
    return i;
}

void StrToInt(char* str){
    // cout << str;
    int number = 1;
    for(int i = 0; i < strlen(str); i++){
        // cout << str[i] << " ";
        number = number*2 + ((int)str[i] - 48);
    }
    cout << number << " ";
}

void PrintInts(struct Node* node){

    if (node == NULL) return;

    struct Packet* packet = NewPacket(node);
    struct Packet* packetNode;
    struct Packet* temp_packet;
    struct Node* temp_node;

    // if(packet->next == NULL) cout<<"it's null \n";

    while (packet != NULL){
        packetNode = PopPacketFromBack(&packet);

        if ((packetNode->node->EOSflag) == 1){
            // cout << "Should print here : ";
            StrToInt(packetNode->str);
            // printString(packetNode->str, i+1);
        }

        temp_packet = new(struct Packet);
        temp_node = packetNode->node;
        if ((temp_node->left_child) != NULL){
            temp_packet->node = temp_node->left_child;
            temp_packet->next = NULL;
            strcpy(temp_packet->str, packetNode->str);
            temp_packet->str[strlen(temp_packet->str)] = '0';
            pushPacketInFront(&packet, temp_packet);
        }

        temp_packet = new(struct Packet);
        if ((temp_node->right_child) != NULL){
            temp_packet->node = temp_node->right_child;
            temp_packet->next = NULL;
            strcpy(temp_packet->str, packetNode->str);
            temp_packet->str[strlen(temp_packet->str)] = '1';
            pushPacketInFront(&packet, temp_packet);
        }


    }
}


int main(){

    int num_inpts, input;
    struct Node* root = new(struct Node);
    struct Node* find_node = new(struct Node);
    struct QNode* head = NULL;

    cout << "Enter Number of inputs : ";
    cin >> num_inpts;

    cout << "+++ Insert : ";
    for(int i=0; i<num_inpts; i++){
        cin >> input;
        while(input > 1){
            pushFront(&head, input%2);
            input = input/2;
        }
        // Display(head);
        Insert(&root, head);
        head = NULL;
    }

    cout << "+++ After Insertion :\n\n";
    PrintTree(root);

    cout << "\n Enter Number of Elements to delete : ";
    cin >> num_inpts;

    cout << "+++ Delete : ";
    for(int i=0; i<num_inpts; i++){
        cin >> input;
        while(input > 1){
            pushFront(&head, input%2);
            input = input/2;
        }

        root = Delete(root, head);
        head = NULL;
    }
    cout << "\n+++ After Deletion : \n";
    PrintTree(root);
    cout <<"\n";

    cout << "\n+++ Printing in sorted order : \n";
    PrintInts(root);
    cout << "\n";

    return 0;
}

//2 8 18 6 7 14 31
