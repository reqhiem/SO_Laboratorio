#include "ListNode.h"


/****************************************************************************************\
List Node class
\****************************************************************************************/
ListNode::ListNode() {
	_value = -1;
	_pnext = nullptr;
}

ListNode::~ListNode() {
	//delete _pnext;
}