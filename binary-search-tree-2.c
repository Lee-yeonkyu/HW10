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
		printf(" [%d] ",ptr->key); //팝에서 나온 값 출력
		ptr=ptr->right;  //오른쪽 값으로 바꿔준다.
	}
}

void levelOrder(Node* ptr)
{
	front=rear=0;
	if(!ptr){return;} //ptr값이 비었을때 종료
	enQueue(ptr); //ptr의 값을 큐안에 삽입.

	while(1){//ptr이 NULL이 될때까지 반복
		ptr=deQueue(); //front의 위치를 올려준다.
		if(ptr){
			printf(" [%d] ",ptr->key);
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
	Node *tmp=head->left; //현재 노드 저장용
		Node *parent =tmp; //부모노드 저장용
		Node *del; //tmp트리 저장용.

		while(tmp->key !=key){ //현재 노드의 키값과 제거 대상의 키값이 같을때 까지 반복
			parent=tmp; //부모 노드 저장
			if(tmp->key<key) //현재 노드 보다 제거할 값이 더 크면
				tmp=tmp->right; // 오른쪽으로 옮겨준다.
			else //현재 노드 보다 제거할 값이 더 작으면
				tmp=tmp->left; // 왼쪽으로 옮겨준다.
		}
		del=tmp;// 제거하고자 한 키값을 가지고 있는 노드의 위치 저장.

		//1. 제거하고자 하는 노드가 리프 노드일 경우.
		if(tmp->left==NULL &&tmp->right==NULL){ // 제거하고자 하는 노드의 자식이 하나도 없을때.
			if(parent->left!=NULL){ //부모의 왼쪽 자식이 존재할때.
				if(tmp->key==parent->left->key){ //그 값과 제거 하고자하는 노드의 키값이 같다면
					parent->left=NULL; //왼쪽 노드를 NULL로 바꿔준다.
					free(tmp);
					return 0;
				}
			}
		parent->right=NULL; //왼쪽 자식이 존재 하지 않다면 오른쪽 자식을 NULL로 처리.
		free(del);
		return 0;
		}

		//2. 제거 하고자 하는 노드의 자식이 양쪽 모두 있을때.
		else if(tmp->left!=NULL && tmp->right!=NULL){
			tmp=tmp->right; //제거 하고자 하는 노드 오른쪽 자식으로 내려간다.
			if(tmp->left==NULL){ //오른쪽 자식의 왼쪽자식 없으면
				del->key=tmp->key; //제거하고자 하는 노드의 오른쪽 자식의 key를 복사.
				del->right=tmp->right; //제거하고자 하는 노드의 오른쪽 자식의 오른쪽 자식을 붙인다.
				free(tmp); //tmp 제거
				return 1;
			}
			while(1){
				if(tmp->left==NULL){ //제거하고자하는 노드의 오른쪽 서브트리에서 key값이 가장 작은 노드 발견시.
					del->key=tmp->key;//노드의 key를 복사한다.
					parent->left=tmp->right;//가장 작은 key를 가지는 노드의 오른쪽 자식을 부모의 왼쪽에 붙인다.
					free(tmp);
					return 1;
				}
				else{ //오른쪽 자식에 왼쪽자식이 있으면
					parent=tmp; //해당노드를 부모로 저장하고
					tmp=tmp->left; //왼쪽 자식으로 노드를 옮겨 재탐색
				}
			}
		}

		//3. 제거하고자 하는 노드의 자식이 왼쪽이나 올느쪽 둘 중 하나만 있을때.
		else{
			if(tmp->right!=NULL){ //제거하고자 하는 노드가 오른쪽 자식을 가지고있을때
				if(parent->left!=NULL){
					if(parent->left->key==key) //부모의 왼쪽에 달려있으면
						parent->left=tmp->right; //부모의 왼쪽에 제거하고자 하는 노드의 오른쪽 자식을 붙인다.
					else
						parent->right=tmp->right;//부모의 오른쪽에 제거하고자 하는 노드의 오른쪽 자식을 붙인다.
					return 1;
				}
				else {parent->right=tmp->right;}
				return 1;
			}
			if(tmp->left!=NULL){ //제거하고자 하는 노드가 왼쪽 자식을 가지고 있을때.
			if(parent->left!=NULL){
				if(parent->left->key==key) //부모의 왼쪽에 달려있으면
					parent->left=tmp->left; //부모의 왼쪽에 제거하고자 하는 노드의 왼쪽 자식을 붙인다.
				else
					parent->right=tmp->left;//부모의 오른쪽에 제거하고자 하는 노드의 왼쪽 자식을 붙인다.
				return 1;
			}
			else {parent->right=tmp->left;}
			return 1;
		}
		free(tmp);
		return 1;
}
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





