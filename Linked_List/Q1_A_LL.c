//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// 새 노드를 생성한다. 
	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
	if (new_node == NULL) // 메모리 할당 실패시 
	{
		return -1;  // 반환값 타입은 int 형이어야 하는데 0과 1은 인덱스 위치 정보일 수 있음. 그래서 -1 반환
	}

	// 새 노드를 초기화한다.
	new_node -> item = item;
	new_node -> next = NULL;  	

	// 리스트가 비어 있는 경우 
	if (ll -> head == NULL)
	{
		ll -> head = new_node; // 리스트의 head를 새 노드로 변경 
		ll -> size = 1; // 리스트 크기 증가
		return 0;
	}
	// 새로운 항목이 첫번째 노드보다 작은 경우 
	else if (item < ll -> head -> item)
	{
		new_node -> next = ll -> head; // 리스트의 head를 새 노드의 다음 포인터로 변경 
		ll -> head = new_node; // 리스트의 head를 새 노드로 변경
		ll -> size++; // 리스트 크기 증가
		return 0;
	}
	
	// 리스트를 순회하면서 새 항목을 삽입할 적절한 위치를 찾는다. 
	// 연결 리스트는 배열과 달리 인덱스로 접근할 수 없다. 
	// 노드간의 이동은 현재 노드의 next 포인터를 따라 이동한다. 
	
	// 현재 노드와 이전 노드 변수, 인덱스 변수를 선언한다. 
	ListNode *current_node = ll -> head; 
	ListNode *previous_node = NULL;
	int index = 0; // 인덱스 정보 초기화 (while문 돌면서 1씩 증가 )

	// 삽입 위치를 찾을 때까지 
	while ( current_node != NULL && current_node -> item < item ) 
	{	
		previous_node = current_node; // 현재 노드는 이전 노드가 된다. 
		current_node = previous_node -> next; // 이전 노드의 다음 포인터는 현재 노드가 된다. 
		index++; // 인덱스 카운트 
 	}

	// 새 노드를 삽입한다.
	// 리스트의 맨 앞에 삽입되는 경우 
	if (previous_node == NULL)
	{
		new_node -> next = ll -> head; // 새 노드의 다음 포인터는 리스트의 헤드를 가리킨다. 
		ll -> head = new_node; // 리스트의 헤드는 새로운 노드가 된다. 
	}
	// 리스트의 중간에 삽입되는 경우 
	else if (current_node != NULL && current_node -> item >= item)
	{
		previous_node -> next = new_node; // 이전 노드의 다음 포인터는 새 노드를 가리킨다.
		new_node -> next = current_node; // 새 노드의 다음 포인터는 현재 노드를 가리킨다. 
	}
	// 리스트의 맨 마지막에 삽입되는 경우 
	else
	{
		previous_node -> next = new_node; // 이전 노드의 다음 포인터는 새 노드를 가리킨다.
		new_node -> next = NULL; // 새 노드의 다음 포인터는 널값이다. 
	}

	// 리스트의 크기를 증가 시킨다. 
	ll -> size++; 

	// 삽입된 인덱스를 반환한다. 
	return index;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
