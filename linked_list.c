/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;

headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * @brief 
 * 
 * 연결리스트에 노드 하나를 추가하는 작업이다.
 * 
 * 1. 새로운 노드를 초기화 시켜준다.
 * 	만약 노드를 처음 넣는 거라면 처음 노드에 넣어준다.
 * 2. 연결리스트의 처음 노드를 가리키는 n 과 trail을 만들어준다.
 * 3. 연결리스트를 순회하면서 (다음 값으로 가리킬 n이 비어있을 때 나가기)
 * 	현재 비교하는 연결리스트의 한 노드의 key 값이 넣을려는 key값보다 크거나 같으면 (넣을려는 Key 값이 더 작거나 같을 경우가 더 직관적일거라 생각이 되긴 함), 오름차순 정렬이니..
 * 		지금 비교하는 연결리스트의 노드가 첫(first) 노드이면 
 * 			현재 넣은 노드를 처음으로 지정해주고 넣는 노드의 다음 값을 비교하는 노드로 바꿔둔다.
 * 		아니라 두번째 순서 이상의 노드이면
 * 			넣는 노드의 다음 값으로 비교하는 노드를 넣어주고 이전 노드의 다음 노드를 현재 넣는 노드로 바꿔준다.
 *	비교하는 노드의 값이 더 작으면은 trail을 현재 노드 (다음 반복문으로 갔을 경우 이전 노드가 된다) n을 다음 노드(다음 반복문으로 갔을 경우 비교를 하는 현재 노드가 된다)로 바꿔준다.
 * 4. 바꿔지지 않은 경우 (return 0 이 안된 경우) 마지막 노드에 연결해줌으로써 넣는 노드가 제일 마지막에 있게끔 해준다.
 * 
 * @param h 연결리스트의 헤드노드를 가리키는 값으로 연결리스트를 구분해줌
 * @param key 추가할 값
 * @return int 왜 리턴해주는지 모르겠음
 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {
		if(n->key >= key) {
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	trail->link = node;
	return 0;
}

/**
 * @brief 
 * 
 * 연결리스트에 노드 하나를 추가하는 작업이다.
 * 
 * 1. 새로운 노드를 초기화 시켜준다.
 * 	만약 노드를 처음 넣는 거라면 처음 노드에 넣어준다.
 * 2. 연결리스트의 노드를 가리키는 n을 만들어준다.
 * 3. n을 마지막 노드로 바꿔준다.
 * 4. 마지막 노드의 다음 노드에 현재 노드를 연결해준다.
 * 
 * @param h 작업을 할 연결 리스트
 * @param key 넣을 노드의 값
 * @return int 왜 반환형이 Int 인지 모르겠음
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) {
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * @brief 
 * 
 * 처음 노드를 지워주는 함수
 * 
 * 1. 연결리스트가 비어 있으면 지울게 없다고 출력해준다.
 * 2. 처음 노드를 가리키는 n을 만들어주고
 * 3. 처음 노드를 가리키는 h->first가 다음 노드를 가리키게 하고
 * 4. 처음 노드를 할당 해제 해준다.
 * 
 * @param h 
 * @return int 
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

/**
 * @brief 
 * 
 * 연결리스트에서 값을 찾아서 지우는 함수이다.
 * 
 * 1. 연결리스트가 비어있는지 확인하고 비어있으면 아무 작업도 안하고 함수를 종료한다.
 * 2. 연결리스트의 처음 노드를 가리키는 n을 선언 (현재 노드로 비교), 이전 노드를 가리킬 null 값을 가지는 trail 선언
 * 3. 노드를 하나씩 넘겨 가면서 (하나씩 넘겼을 때 그 값이 Null 이면은 반복문 종료)
 * 	노드의 값이 지울려는 (찾는, 입력한) 값인지 확인하고
 * 		지울려는 값일 경우
 * 			그 노드가 첫 노드면 두번째 노드를 첫 노드로 바꿔주고(헤드노드가 가리키게 하고) free()로 지워준다.
 * 			그 노드가 첫 노드가 아닐 경우에는 이전 노드의 다음 노드가 현재 노드의 다음 노드를 가리키게 하고 free()로 지워준다.
 * 		지울려는 값이 아닌 경우
 * 			trail, 과 n의 값을 바꿔줌으로 다음 비교 연산 가능케 한다.
 * 4. 연결리스트 내에 찾는 값이 없을 경우 찾는 값이 없다고 출력해준다.
 * 
 * @param h 
 * @param key 
 * @return int 
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/**
 * @brief 
 * 
 * 마지막 노드를 지우는 함수이다.
 * 
 * 1. 연결리스트가 비어 있을 경우 지울게 없다고 출력
 * 2. 이전 노드 역할을 해줄 trail과 현재 노드를 가리켜줄 n을 만들어준다.
 * 3. 연결리스트에 노드가 하나밖에 없을 경우
 * 		처음 노드를 가리키는 값을 Null로 바꿔주고 노드를 free() 해준다.
 * 4. 연결리스트의 마지막 노드를 가리키게 while문으로 이동한 후
 * 이전 노드(마지막의 전 노드)의 다음 노드의 연결을 끊은 후
 * 현재노드를 지워준다.
 * 
 * @param h 
 * @return int 
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	trail->link = NULL;
	free(n);

	return 0;
}

int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
