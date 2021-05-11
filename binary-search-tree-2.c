/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


/*void printStack();*/



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [이연규] [2018038038] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			/*printStack();*/
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr) //재귀를 이용한 중위순회
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	Node* ptr;
	top= -1; //스택 초기화

	ptr =node; //node의 값을 ptr에 넣어준다.
	while(1){
		while(ptr !=NULL){ //ptr가 왼쪽 끝까지 갈때까지 반복
			push(ptr); //스택에 삽입
			ptr=ptr->left; //ptr을 왼쪽으로 옮겨준다.
		}
		ptr=pop();//스택에서 삭제
		if(ptr ==NULL){break;} //팝에서 나온 것이 공백일시 정지
		printf("[%d]\t",ptr->key); //팝에서 나온 값 출력
		ptr=ptr->right;  //오른쪽 값으로 바꿔준다.
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(!ptr){return;} //ptr값이 비었을때 종료
	enQueue(ptr); //ptr의 값을 큐안에 삽입.

	while(1){//ptr이 NULL이 될때까지 반복
		ptr=deQueue(); //front의 위치를 올려준다.
		if(ptr){
			printf("[%d]\t",ptr->key);
			if(ptr->left){enQueue(ptr->left);}//왼쪽이 NULL이 아니면 삽입
			if(ptr->right){(enQueue(ptr->right));} //오른쪽이 NULL이 아니면 삽입
		}
		else
			break;
	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node* node=NULL;
	if(top == -1) // 스택이 비었을 시에 종료
		return node;
	node=stack[top];//스택에 맨위에 node를 넣어준다.
	top--; //top을 내려준다.
	return node;
}

void push(Node* aNode)
{
	if(top >=MAX_STACK_SIZE-1) //스택이 꽉찼을때 종료
		return;
	top++; //top의 위치를 올려준다.
	stack[top]=aNode; //스택의 맨 위에 aNode값을 넣어준다.
}



Node* deQueue() //큐에서의 데이터 출력을 위한 함수.
{
	Node* node =NULL;
	if(front == rear){return node;} //비어있다면 종료
	front++; //front의 위치를 올려준다.
	node=queue[front];
	return node;
}

void enQueue(Node* aNode) //큐에서 데이터를 입력을 위한 함수
{
	if(rear == MAX_QUEUE_SIZE-1){return;} //큐가 꽉찼을때 종료

	rear++; //rear값을 올려준다.
	queue[rear]=aNode; //큐의 rear위치에 aNode를 넣어준다.
}





