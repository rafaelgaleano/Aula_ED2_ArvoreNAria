#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
    int value;
    struct Node* firstChild;
    struct Node* nextSibling;
}Node;

Node* createNode(int val){
    Node* n = (Node*)malloc(sizeof(Node));
    if(!n){
        perror("ERRO: malloc");
        exit(EXIT_FAILURE);
    }
    n->value = val;
    n->firstChild = NULL;
    n->nextSibling = NULL;
    return n;
}

void insertChild(Node* parent, Node* child){
    if(!parent||!child) return;
    if(!parent->firstChild){
        parent->firstChild = child;
    } else {
        Node* aux = parent->firstChild;
        while(aux->nextSibling){
            aux = aux->nextSibling;
        }
        aux->nextSibling = child;
    }
}

int countNodes(const Node* root){
    if(!root) return 0;
    int total = 1;
    for(Node* c=root->firstChild; c;c = c->nextSibling){
        total +=countNodes(c);
    }
    return total;
}

int height(const Node* root){
    if(!root) return 0;
    int maxh = 0;
    for(Node* c = root->firstChild; c ;c=c->nextSibling){
        int h = height(c);
        if(h>maxh) maxh = h;
    }
    return 1+maxh;
}

Node* find(Node* root, int target){
    if(!root) return NULL;
    if(root->value == target) return root;
    for(Node* c = root->firstChild;c;c=c->nextSibling){
        Node* r = find(c,target);
        if(r) return r;
    }
    return NULL;
}

void preOrder(const Node* root){
    if(!root) return;
    printf("%d ",root->value);
    for(Node* c = root->firstChild;c;c=c->nextSibling){
        preOrder(c);
    }
}

void postOrder(const Node* root){
    if(!root) return;
    for(Node* c = root->firstChild;c;c=c->nextSibling){
        postOrder(c);
    }
    printf("%d ",root->value);
}

void freeTree(Node* root){
    if(!root) return;
    Node* c = root->firstChild;
    while(c){
        Node* next = c->nextSibling;
        freeTree(c);
        c = next;
    }
    printf("Matou: %d ",root->value);
    free(root);
}

int main(){
    Node* n1 = createNode(1);
    Node* n2 = createNode(2);
    Node* n3 = createNode(3);
    Node* n4 = createNode(4);
    Node* n5 = createNode(5);
    Node* n6 = createNode(6);
    Node* n7 = createNode(7);
    Node* n8 = createNode(8);

    insertChild(n1,n2);
    insertChild(n1,n3);
    insertChild(n1,n4);
    insertChild(n1,n8);

    insertChild(n3,n5);
    insertChild(n3,n6);

    insertChild(n4,n7);
    printf("Pre ordem: ");
    preOrder(n1);
    printf("\n");

    printf("Pos ordem: ");
    postOrder(n1);
    printf("\n");

    printf("Total de nos: %d\n",countNodes(n1));
    int altura = height(n1);
    printf("Altura: %d\n", altura);
    int v = 7;
    Node* achou = find(n1,v);
    if(achou){
       printf("Valor %d encontrado!!\n",v);
    } else {
        printf("Valor nao encontrado!\n");
    }
    freeTree(n1);
}
