/* A Generic representation of Linked List */
 struct node {
	void *data;
	struct node *next;
};
//Construct for the linked list
typedef struct{
	int size; //dataype size
	int count;//counting the element in the list
	struct node *head;//head of the linked list
}LinkedList;

void createList(LinkedList *,int );
void append(LinkedList *,void *);
void addafter(LinkedList *,int,void *);
void addbeg(LinkedList *,void *);
struct node * head(LinkedList *);
void del(LinkedList *,void *);
void arrange(LinkedList *);
void reverse(LinkedList *);
int isPresent(LinkedList *,void *data);
struct node* find(LinkedList *,void *);
void merge(LinkedList *,LinkedList *,LinkedList *);

static int compare(void  *first,void *second,int size) {
	return memcmp(first,second,size);

}

void dispose(LinkedList *list) {
	struct node *temp = (list->head);
	while(temp != NULL) {
		struct node *del_node = temp;
		(temp) = temp->next;
		free(del_node->data);
		free(del_node);
	}
	list->head = NULL;
}

int isEmpty(LinkedList *list){
	if(list->count == 0)
		return 1;
	return 0;
}


//A Generic swap function
void static swap(struct node *prev,struct node *after,int size) {
	void *temp = malloc(size);
	memcpy(temp,prev->data,size);
	memcpy(prev->data,after->data,size);
	memcpy(after->data,temp,size);
}

 int length(LinkedList *list){
	return list->count;
}

//search the data in the list using memcmp function it compare each byte of the two data
//if match it return the node which contains the particular data
static struct node* search(struct node **walk,int size,void *data){
	if(memcmp((*walk)->data,data,size) == 0)
		return *walk;
	while((*walk)->next != NULL) {
		if(memcmp(((*walk)->next)->data,data,size) == 0)
			return (*walk);
		walk = &((*walk)->next);
	}
	return NULL;
}
//Creating a linked list
void createList(LinkedList *list,int type) {
	list->size = type;
	list->count = 0;
	list->head = NULL;
}
//add the elment to the specified linked list
void append(LinkedList *list,void *data){
	struct node *attach = malloc(sizeof(struct node));
	attach->data  = malloc(list->size);
	memcpy(attach->data,data,list->size);
	attach->next = NULL;
	if((list->head) == NULL){
		(list->head) = attach;
		list->count++;
		return;
	}
	struct node *walk = list->head;
	while((walk)->next != NULL)
		walk = (walk)->next;
	(walk)->next = attach;
	list->count++;
	return;

}

struct node * head(LinkedList *list) {
	return list->head;
}

void addbeg(LinkedList *list,void *data) {
	struct node *attach = malloc(sizeof(struct node));
	attach->data = malloc(list->size);
	memcpy(attach->data,data,list->size);
	attach->next = list->head;
	list->head= attach;
	list->count++;

}

void addafter(LinkedList *list,int loc,void *data) {
	//return if the element count of the linked list is smaller then the specified location
	if(list->count < loc) {
		printf("List element are less than the specifed location");
		return;
	}
	struct node* walk = list->head;
	for(int i=0 ; i<loc ;i++)
		walk = (walk->next);
	struct node *attach = malloc(sizeof(struct node));
	attach->data = malloc(sizeof(list->size));
	memcpy(attach->data,data,list->size);
	attach->next = (walk)->next;
	(walk)->next = attach;
	list->count++; //incrementing list count after every addition of linked list
}

void del(LinkedList *list,void *data) {
	if(list->count == 0){
		printf("List is empty\n");
		return;
	}
	struct node *temp = search(&(list->head),list->size,data);
	if(temp == NULL) {
		printf("Element not found\n");
		return;
	}
	if(temp == list->head){
		struct node *del_node = temp;
		list->head = temp->next;
		free(del_node->data); //Releasing the memory of the elemnt which is in the node
		free(del_node);// releading the node
		list->count--;//decrementing the count
		return ;
	}
	struct node *del_node = temp->next;
	temp->next = (temp->next)->next;
	free(del_node->data);
	free(del_node);
	list->count--;


}

void arrange(LinkedList *list) {
	int len = length(list);
	const int size = list->size;
	for(int i = 0; i<len-1 ;i++) {
	struct node *trav = list->head;
		for(int j = 0; j < len -1 ; j++) {
			if(memcmp(trav->data,((trav)->next)->data,size) > 0) {
				swap(trav,trav->next,size);
			}
		trav = trav->next;
		}
	}
}
	


void reverse(LinkedList *list) {
	Stack st;
	StackNew(&st,list->size,NULL);
	struct node *trav = list->head;
	while(trav != NULL) {
		StackPush(&st,&(trav->data));
		trav = trav->next;
	}
	trav = list->head;
	while(trav != NULL) {
		StackPop(&st,&(trav->data));
		trav = trav->next;
	}
}

int isPresent(LinkedList *list,void *data) {
	struct node *temp = search(&(list->head),list->size,data);
	if(temp != NULL)
		return 1;
	else
		return 0;


}

struct node* find(LinkedList *list,void *data) {
	struct node *temp = search(&(list->head),list->size,data);
	if(temp == NULL){
		printf("Element not present\n");
		return NULL;
	}
	return temp->data;
}


void merge(LinkedList *first,LinkedList *second,LinkedList *third) {
	struct node *fpt = first->head;
	struct node *spt = second->head;
	int size = first->size;
	if(first->count > second->count) {
		while(fpt != NULL) {
				append(third,fpt->data);
				fpt = fpt->next;
		}
		while(spt != NULL) {
			if(isPresent(third,spt->data))
				spt = spt->next;
			else {
				append(third,spt->data);
				spt = spt->next;
			}
		}
	}
	else {
		while(spt != NULL) {
				append(third,spt->data);
				spt = spt->next;
		}
		while(fpt != NULL) {
			if(isPresent(third,fpt->data))
				fpt = fpt->next;
			else {
				append(third,fpt->data);
				fpt = fpt->next;
			}
		}
	}

}