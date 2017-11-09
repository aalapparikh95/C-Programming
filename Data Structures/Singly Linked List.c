#include<stdio.h>
#include<stdlib.h>

struct node
{	
	int value;
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//insert at the head
void insertnode(int value)
{
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->value = value;
	link->next = head;
	
	head = link;
	//printf("Inserted %d", value);	
}

void deletenode(int position)
{
	current = head;
	int i;
	for(i=1;i<position-1;i++)
	{
		current = current->next;
	}
	current->next = current->next->next;
	//printf("Deleted %d", position);
}

int length()
{
	current = head;
	int l = 0;
	while(current->next)
	{
		l++;
		current = current->next;
	}
	return l;
}

void sort()
{
	current = head;
	printf("Initial Current value is %d\n", current->value);
	int i,j,min;
	
	struct node *p = head;
	struct node *minp = NULL;
	
	int l = length();
	
	printf("Length = %d\n", l);
	for(i = 0; i<l; i++)
	{
		min = current->value;
		printf("Assume min is %d\n", min);
		current = current->next;
		printf("Current value is %d\n", current->value);
		for(j = 0; j < l-i; j++)
		{
			if(current->value < min)
			{
				min = current->value;
				printf("Min = %d",min);
				minp = current;
			}	
			current = current->next;
		}
		printf("Min for the iteration is %d\n", min);
		p->next = minp;
	}
}

void printlist()
{
	current = head;
	printf("%d",current->value);
	current = current->next;
	while(current->next)
	{
		printf("-->");
		printf("%d",current->value);
		current = current->next;
	}
	printf("\n");
}


int main()
{
	//printf("Inserting 5");
	insertnode(5);
	insertnode(100);
	insertnode(15);
	insertnode(253);
	insertnode(35);
	printlist();
	sort();
	printlist();
	deletenode(2);
	
	printlist();
	return 0;
}