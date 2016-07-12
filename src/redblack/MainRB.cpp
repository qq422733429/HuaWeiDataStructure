#include"RBTree.h"

void main()
{
	RBNode *R = new RBNode(11);
	RBTree rbtree(R);
	RBNode *Node1 = new RBNode(8);
	rbtree.InsertNode(Node1);
	RBNode *Node2 = new RBNode(2);
	rbtree.InsertNode(Node2);
	RBNode *Node3 = new RBNode(14);
	rbtree.InsertNode(Node3);
	RBNode *Node4 = new RBNode(7);
	rbtree.InsertNode(Node4);
	RBNode *Node5 = new RBNode(8);
	rbtree.InsertNode(Node5);
	RBNode *Node6 = new RBNode(1);
	rbtree.InsertNode(Node6);
	RBNode *Node7 = new RBNode(5);
	rbtree.InsertNode(Node7);
	RBNode *Node8 = new RBNode(4);
	rbtree.InsertNode(Node8);
	RBNode *Node9 = new RBNode(9);
	rbtree.InsertNode(Node9);
	RBNode *Node10 = new RBNode(13);
	rbtree.InsertNode(Node10);
	RBNode *Node11 = new RBNode(6);
	rbtree.InsertNode(Node11);
	RBNode *Node12 = new RBNode(0);
	rbtree.InsertNode(Node12);
	RBNode *Node13 = new RBNode(17);
	rbtree.InsertNode(Node13);
	RBNode *Node14 = new RBNode(15);
	rbtree.InsertNode(Node14);
	RBNode *Node15 = new RBNode(12);
	rbtree.InsertNode(Node15);
	rbtree.Delete(8);
	rbtree.MidOrder(rbtree.Root());
	system("pause");
}
