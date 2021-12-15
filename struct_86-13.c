#include<stdio.h>
#include<malloc.h>

struct node
{
	int data;
	struct node* prev;
	struct node* next;
}*head, * tail;

int create_list(int n);
void print_begin(struct node* Head);
void print_end(struct node* Tail);
int insert_node(int Pos, int Value, int n);
int delete_node(int Pos, int n);
void reverse_list(int n);
void lowest_value(void);
void sort_low(void);

int main()
{
	printf("How many nodes do you want? ");
	int n;
	scanf("%d", &n);
	create_list(n);
	print_begin(head);
	print_end(tail);
	
	sort_low();
	
	
	print_begin(head);
	print_end(tail);
	return 0;
}

void sort_low(void)
{
	int low_value;
	struct node* temp, * scanner, * place_holder;
	temp = head;
	
	low_value = head->data;//set the low_value to whatever is in node1
	temp = temp->next;//move to node2

	while (temp != NULL)//this is going right to left so don't introduce a left to right scan trying to save processing power - it won't save you anything and it may create infinite loops
	{
		if (temp->data > low_value)//if it's not lower than the lowest_value, then it still might be lower than some intermediate value - so you'll have to scroll from node2 onwards
		{
			//place_holder = temp->prev;//mark the spot you left off DON'T NEED IT?!?!
			scanner = head->next;//we need to reset scanner to 2nd node every iteration of the while loop so it has to be within this if block not outside While like it was originally
			if (temp->data < temp->prev->data)//this is preventing unnecessary looping by saying "only go through all this trouble if the previous value is GREATER than the temp value - otherwise jump out -- this saves time with 54321-6 : 12345-6 - no sorting needed for the last node 6 because it's already sorted
			{
				while (temp->data > scanner->data)//if the node is > previous nodes keep moving it along 
				{
					scanner = scanner->next;//try this example 975318  13579-8
					printf("scanner skips past lower value\n");
				}

				if (temp->data < scanner->data)//if the node's data is < a previous node, then reposition it before that node
				{
					//adjacent end swap
					if (temp->next == NULL && scanner->next->next == NULL)
					{
						printf("\nadjacent END swap\n");
						
						print_begin(head);
						print_end(tail);

						//temp LEFT
						temp->prev = scanner->prev;//link temp BACK to node bef scanner
						scanner->prev->next = temp;//link node bef scanner FORWARD to temp
						
						//temp to scanner MID
						scanner->prev = temp;//link scanner BACK to temp
						temp->next = scanner;//link temp FORWARD to scanner
						
						//scanner RIGHT
						scanner->next = NULL;//make scanner the LAST node
						
						tail = scanner;//reposition tail

						
						print_begin(head);
						print_end(tail);

						break;//this is kinda cheating bc you know you're at the end of the list with the if conditional statements - it's used to keep the list from running through temp=temp->next another time - couldn't figure out why so I used break as a bandaid

					}

					//non-adjacent end swap
					else if (temp->next == NULL && scanner->next->next != NULL)
					{
						printf("\nNON-adjacent END swap\n");
						print_begin(head);
						print_end(tail);

						temp->prev->next = NULL;//the node bef temp now becomes the last node
						tail = temp->prev;//reposition tail to the 2nd to last node which will soon become the last node

						temp->prev = scanner->prev;//link temp BACK to the node BEFORE scanner
						scanner->prev->next = temp;//link the node before scanner FORWARD to temp

						temp->next = scanner;//link temp forward to scanner so it sits just before scanner
						scanner->prev = temp;//link scanner back to temp

						print_begin(head);
						print_end(tail);
						
						break;
					
					}

					//adjacent AND non-adjacent middle swap (insert temp behind scanner - it's an actual swap)
					else if (temp->next != NULL)//means temp is not the last node and is therefore in the middle

						//SHAH YOU'LL NEED TO NEST adjacent and non adjacent in two if's WITHIN this else if block
					{
						if (scanner->next == temp)//scanner is adjacent to temp
						{
							printf("\nadjacent MIDDLE swap\n");
							print_begin(head);
							print_end(tail);

							place_holder = temp->prev;//mark your spot before temp

							//temp LEFT
							temp->prev = scanner->prev;//link temp BACK to node bef scanner
							scanner->prev->next = temp;//link node bef scanner FORWARD to temp		

							//scanner RIGHT
							scanner->next = temp->next;//link scanner forward to the node after temp
							temp->next->prev = scanner;//link the node after temp back to scanner

							//temp to scanner MID
							scanner->prev = temp;//link scanner BACK to temp
							temp->next = scanner;//link temp FORWARD to scanner

							temp = place_holder;//put temp back where it was

							print_begin(head);
							print_end(tail);
							/*break;*///break will ruin the entire program!
						}
						
						
						else if (scanner->next != temp)//scanner is NOT adjacent to temp
						{
							printf("\nNON-adjacent MIDDLE swap\n");
							print_begin(head);
							print_end(tail);
							
							place_holder = temp->prev;//mark your spot before temp
							
							//temp leaves a vacancy and so the nodes on either side of temp need to be  connected before you move temp behind scanner
							temp->prev->next = temp->next;
							temp->next->prev = temp->prev;

							//temp LEFT
							temp->prev = scanner->prev;//link temp BACK to node bef scanner
							scanner->prev->next = temp;//link node bef scanner FORWARD to temp		

							//temp RIGHT (is to scanner)
							temp->next = scanner;
							scanner->prev = temp;

							//scanner RIGHT should already properly connected so do nothing

							temp = place_holder;//put temp back where it was

							print_begin(head);
							print_end(tail);
							/*break;*///break will ruin the entire program!
						}

					}
					
				}

			}
			
		}


		else if (temp->data <= low_value)//if it is lower than lowest_value, then...
		{
			printf("\nnew low_value\n");
			low_value = temp->data;//assign the new lower value to low_value before you forget
			
			//then move and relink it as the FIRST node ALWAYS
			//this requires the use of a "place_holder" node so you always "remember" where temp was.
			//You don't want to increment all the way through the list to find the old position even if you could write some n - 1 type formula since hat wastes processing power
			//instead mark the node BEFORE temp with a pointer called "place_holder" and then reassign place holder's address to temp after you're done

			place_holder = temp->prev;//This places the place_holder pointer on the node prev to temp before you move temp around (the reason you do prev and not next is so you can use the temp = temp->next expression in the outermost part of the While loop to apply to all the conditional blocks)
			
			//before you move temp, connect the nodes on either side of it to EACH OTHER so you don't have a break in the link
			if (temp->next != NULL)
			{
				temp->prev->next = temp->next;//make the node before temp link to the node after temp
				temp->next->prev = temp->prev;//make the node after temp link backward to the node before temp

			}
			else if (temp->next == NULL)//special case if you have to MOVE THE LAST NODE bc you'll have to assign NULL to the 2nd to last node
			{
				temp->prev->next = NULL;//2nd to last node end at NULL
				
				tail = temp->prev;//move tail to the 2nd to last node because it will become the last node
				
			}

			//now you are moving/reconnecting the underlying node pointed to by temp (which holds the new lowest_value)
				temp->prev = NULL;//temp's node now points prev to NULL so it's in position 1
				temp->next = head;//and now it links forward to the old first node
				temp->next->prev = temp;//link the old first node back to the new first node - I FORGOT THIS - ARGGG!
				head = temp;//move head back to the new first node

				//now that this node occupies the first position in the list, you can reuse the temp pointer for its original purpose.
				//to do that, let's move it back to place_holder's position
				temp = place_holder;//move temp back to its "original position" - ready to be incremented to the next node with temp = temp->next in the outermost portion of thw while loop

				print_begin(head);
				print_end(tail);
		}
	
		//if you put this in an else block, it will get stuck - it shouldn't be in an else block because it needs to be triggered even after the if and else if blocks have been entered - leave this alone!
		temp = temp->next;//moves to the next node
		printf("temp = temp->next\n");
	}

}
void lowest_value(void)
{
	struct node* temp;
	int i = 1;
	int node_number;
	int low_value;
	temp = head;
	low_value = temp->data;//assign the first node's value to low_value OUTSIDE the While loop
	
	while (temp != NULL)
	{
		if (temp->data < low_value)
		{
			low_value = temp->data;//if temp->data is lower than the value you stored in low_value, replace that value with the new low value
			node_number = i;//this is my node tracker, if the new value is lower than the old, it will assign the i counter value to node_number
		}
		temp = temp->next;
		i++;
	}
	printf("%d is the lowest value and was found in node %d\n", low_value, node_number);
}
void reverse_list(int n)
{
	struct node* temp_1, * temp_2;
	temp_1 = head;
	temp_2 = head->next;
	printf("temp_1->data = %d\n", temp_1->data);
	printf("temp_2->data = %d\n\n", temp_2->data);


	for (int i = 1; i < n - 1; i++)
	{
		
		temp_1->prev = temp_2;
		temp_2->prev = temp_2->next;
		temp_2->next = temp_1;
		temp_1 = temp_2;//now bump scanner down RIGHTWARD using prev instead of next!
		temp_2 = temp_2->prev;

		printf("inside WHILE\n");
		printf("temp_1->data = %d\n", temp_1->data);
		printf("temp_2->data = %d\n", temp_2->data);
		
		//GREAT NOW WE JUST HAVE SEGMENTATION FAULT FROM A MISSING LINK
		
	}
	printf("\noutside for loop\n");
	tail = head;//move tail to head so that BOTH are on the LEFT most node (original 1st new last)
	printf("tail->data = %d\n", tail->data);
	printf("head->data = %d\n", head->data);
	head = temp_2;//now you can place head at the RIGHTMOST node (original tail)
	head->next = temp_1;//this was missing and screwed things up - it links back to the 2nd to last node (or the new 2nd node)

	printf("temp->data = %d\n", temp_2->data);
	printf("head->data = %d\n", head->data);
	printf("head->prev->data = %d\n", head->prev->data);//this showed me my error in the last version

	//clean up NULL pointers
	head->prev = NULL;
	tail->next = NULL;

}
int delete_node(int Pos, int n)
{
	//first and last head and tail pointers will have ot be replaced
	struct node* temp;

	if (Pos == 1)//first node
	{
		temp = head;//position scanner with head at beginning
		head = head->next;//reposition head to new beginning which is 2nd node
		head->prev = NULL;//make the new first node's prev pointer point to NULL
		free(temp);//now you can deallocate the memory of the first node
	}

	else if (Pos == n)//last node
	{
		temp = tail;//position scanner at last node
		tail = tail->prev;//move tail backwards to 2nd to last node
		tail->next = NULL;//make the last node point to NULL
		free(temp);//now blow up the last node
	}

	else
	{
		temp = head->next;//place scanner at 2nd node

		for (int i = 2; i < Pos; i++)//beginning at the 2nd node, traverse the list until you land on top of the target node Pos
		{
			temp = temp->next;
		}

		//advanced doubly linked double pointer technique
		temp->prev->next = temp->next;//go to the node scanner->prev points to and make that node's next pointer hold the address in scanner->next - this will create the forward link and skip over scanner
		temp->next->prev = temp->prev;//go to the node scanner->next points to and make that node's prev pointer hold the address that is held in scanner->prev - this will link the node next to scanner link BACK to the node before scanner and skip over scanner

		free(temp);//now you can free scanner
	}

}
int insert_node(int Pos, int Value, int n)
{
	//create a new node using malloc
	//put the new value in the data member
	//traverse to the nodes before and after it
	//point their prev/next pointers to your new node and the new node's pointers to the bef/aft
	struct node* new_node, * temp, * bef, * aft;
	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = Value;



	if (Pos == 1)//if you want to insert the new node as the first node
	{
		temp = head;//place scanner at 1st node which will become 2nd node
		new_node->prev = NULL;//1st node links back to NULL
		new_node->next = temp;//1st node links forward to 2nd
		temp->prev = new_node;//2nd node links back to 1st
		head = head->prev;//move head back through incrementing so it points to the new 1st node
	}

	else if (Pos == n)//if last node
	{
		temp = tail;//place scanner at original last node
		temp->next = new_node;//link 2nd to last foward to new last node
		new_node->prev = temp;//link new last node back to 2nd to last
		new_node->next = NULL;//link new last node forward to NULL;
		tail = tail->next;//move tail pointer from 2nd to last to last
	}

	else//middle nodes
	{
		//assign bef and aft pointers next to each other as 1st and 2nd positions
		bef = head;
		aft = head->next;

		for (int i = 2; i < Pos; i++)//move bef and aft pointers in sync since they are already one step apart
		{
			bef = bef->next;//moves to 2
			aft = aft->next;//moves to 3 our target position
		}

		bef->next = new_node;//link prev node FORWARD to new node
		new_node->prev = bef;//link new node BACKWARD to bef node

		new_node->next = aft;//now link new node forward to aft node
		aft->prev = new_node;//link aft node backward to new node
	}
}
int create_list(int n)
{
	//create just the first node
	struct node* new_node, * temp;
	temp = (struct node*)malloc(sizeof(struct node));
	printf("Enter data: ");
	scanf("%d", &temp->data);
	temp->prev = NULL;//first node points BACK to NULL 
	temp->next = NULL;//first node points FORWARD to NULL for now
	head = temp;//head now points to scanner the first node


	//create the rest of the nodes
	for (int i = 2; i <= n; i++)
	{
		new_node = (struct node*)malloc(sizeof(struct node));
		printf("Enter Data: ");
		scanf("%d", &new_node->data);
		tail = new_node;
		new_node->next = NULL;//latest node must terminate at NULL;
		new_node->prev = temp;//link current node backwards to prev node
		temp->next = new_node;//link prev node forward to current node
		temp = temp->next;//move scanner down one node
	}

}
void print_begin(struct node* Head)
{
	while (Head != NULL)
	{
		printf("%d ", Head->data);
		Head = Head->next;
	}
	printf("\n");
}
void print_end(struct node* Tail)
{
	while (Tail != NULL)
	{
		printf("%d ", Tail->data);
		Tail = Tail->prev;
	}
	printf("\n");
}