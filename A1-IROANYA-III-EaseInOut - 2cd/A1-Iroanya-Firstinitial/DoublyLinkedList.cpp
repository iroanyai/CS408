#include "DoublyLinkedList.h"

dLinkedList::dLinkedList() { //this is dLinkedList constructor which initialises the variables
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

void dLinkedList::headInsert(DFrameData* data) //insert at head constructor
{
	node* n = new node(data); //creating a new node which we have to insert

	if (head == nullptr) { //checks if the liost is empty
		head = n; //if empty, head becomes n
		tail = head; //since there is just one node, tail and head will be the same
	}
	else {
		head->prev = n; //otherwise, when list is not empty, head's previous will be n making n the had
		n->next = head; //and n's next will be head
		head = n; //n finally becomes head
	}

	size++; //increments the list's size
}

void dLinkedList::deleteTail() //function to delete at tail
{
	if (head == tail) { //checks if list contains just one node
		delete tail; //deletes that node
		head = nullptr; //list is now empty
		tail = nullptr;
	}
	else {
		node* temp2 = tail->prev; //otherwise tail's prev becomes temp
		delete tail; //delete tail
		tail = temp2; //reassign tail
		temp2 = nullptr; //discard temp
	}
	size--; //decrement list size
}

int dLinkedList::getSize() { //gets size of the linked list
	return size;
}

DFrameData* dLinkedList::getDFrameData(int index) //reads the cloud
{
	node* temp = head;
	int count = 0;

	while (temp != nullptr) {
		if (count == index) {
			return temp->data; //returns the address of the data
		}
		else {
			count++;
			temp = temp->next; //traverse the list further
		}
	}
}

dLinkedList::~dLinkedList() {

	while (size > 0)
		deleteTail();
}

