#include<iostream>
#include<deque>
using namespace std;

class RBTree;
enum Color{red = 0,black = 1};

class RBNode
{
	friend class RBTree;
	private:
		RBNode *left;
		RBNode *right;
		RBNode *parent;
		Color color;
		int item;
	public:
		RBNode(int x);
		~RBNode(){}
};

class RBTree
{
	private:
		RBNode *root;
		RBNode *current;
		void LeftRotate(RBNode *y,RBNode *x);
		void RightRotate(RBNode *y,RBNode *x);
		bool Insert(RBNode *x);
		void DeleteFixup(RBNode *x);
	public:
		RBTree(RBNode *R);
		~RBTree();
		void DeleteRBTree(RBNode *pDT);
		void Display();
		void Rotate();
		void InsertNode(RBNode *x);
		RBNode *Root();
		void DeleteNode(RBNode *pDN);
//		bool Delete(int x);
 		void Delete(int data);
		void MidOrder(RBNode *PO);
};

RBNode::RBNode(int x)
{
	color = red;
	item = x;
	left = NULL;
	right = NULL;
	parent = NULL;
}

RBNode* RBTree::Root()
{
	return root;
}

void RBTree::MidOrder(RBNode *PO)
{
	if(PO != NULL)
	{
		MidOrder(PO->left);
		cout<<"item: "<<PO->item;
	
		if(PO->color == red)
			cout<<"  red"<<endl;
		else
			cout<<"  black"<<endl;
	    MidOrder(PO->right);
	}
}
	
RBTree::RBTree(RBNode *R)
{
	if(R != NULL)
	{
		R->color = black;
		this->root = R;
		this->current = R;
	}
	else
	{
		cout<<"Error by construct the rbtree..."<<endl;
	}
}

RBTree::~RBTree()
{
	if(root != NULL)
	DeleteRBTree(root);
	else
		cout<<"Error by free the rbtree.."<<endl;
}

void RBTree::DeleteRBTree(RBNode *pDT)
{
	if(pDT != NULL)
	{
		DeleteRBTree(pDT->left);
		DeleteRBTree(pDT->right);
		delete pDT;
	}
}

void RBTree::LeftRotate(RBNode *y,RBNode *x)
{
	if(y == root)
	{
		root = x;
		x->parent = NULL;
	}
	else
	{
		x->parent = y->parent;
	}

	if(x->left != NULL)
	{
		y->right = x->left;
		x->left->parent = y;
		x->left = y;
		if((x != root)&&(y->parent->left == y))
			y->parent->left = x;
		else if((x != root)&&(y->parent->right == y))	 
			y->parent->right = x;
		y->parent = x;
	}
	else
	{
		y->right = NULL;
		x->left = y;
		if((y != root)&&(y->parent->left == y))
			y->parent->left = x;
		else	 
			y->parent->right = x;
		y->parent = x;
	}
}

void RBTree::RightRotate(RBNode *y,RBNode *x)
{
	if(y == root)
	{
		root = x;
		x->parent = NULL;
	}
	else
	{
		x->parent = y->parent;
	}

	if(x->right != NULL)
	{
		y->left = x->right;
		x->right->parent = y;
		x->right = y;
		if((x != root)&&(y->parent->left == y))
			y->parent->left = x;
		else if((x != root)&&(y->parent->right == y))	 
			y->parent->right = x;
		y->parent = x;
	}
	else
	{
		y->left = NULL;
		x->right = y;
		if((x != root)&&(y->parent->left == y))
			y->parent->left = x;
		else if((x != root)&&(y->parent->right == y))	 
			y->parent->right = x;
		y->parent = x;
	}
}

bool RBTree::Insert(RBNode *x)
{
	bool test = false;
	while(!test)
	{
		if(x->item == current->item)
		{
			test = true;
			cout<<"A same element exist.."<<endl;
			delete x;
			return false;
		}
		else if(x->item>current->item)
		{
			if(current->right == NULL)
			{
				current->right = x;
				x->parent = current;
				current = current->right;
				cout<<"success to insert.."<<endl;
				test = true;
			}
			else
			{
				current = current->right;
			}
		}
		else if(x->item<current->item)
		{
			if(current->left == NULL)
			{
				current->left = x;
				x->parent = current;
				current = current->left;
				cout<<"success to insert.."<<endl;
				test = true;
			}
			else
			{
				current = current->left;
			}
		}
	}
	return true;
}

void RBTree::InsertNode(RBNode *x)
{
	current = root;
	RBNode *x_uncle = NULL;
	if(this->Insert(x))
	{
		while((x != root)&&(x->parent->color == red))
		{
			if(x->parent == x->parent->parent->left)		//two if to set up the uncle of x
			{
				if(x->parent->parent->right != NULL)
				{
					x_uncle = x->parent->parent->right;
				}

				if((x_uncle != NULL)&&(x_uncle->color == red))					//if uncle is red->x,x_uncle up only
				{
					x->parent->color = black;
					x_uncle->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else										//if uncle is black->2 situation
				{
					if((x->parent->right != NULL)&&(x == x->parent->right))			
					{				//1 x is right child only rotate
						x = x->parent;
						this->LeftRotate(x,x->right);
					}
					else if((x->parent->left != NULL)&&(x == x->parent->left))	
					{				//2 x is left child need to change color and rotate
						x->parent->parent->color = red;
						x->parent->color = black;
						this->RightRotate(x->parent->parent,x->parent);
					}
				}
			}
			else if(x->parent == x->parent->parent->right)
			{
				if(x->parent->parent->left != NULL)
				{
					x_uncle = x->parent->parent->left;
				}

				if((x_uncle != NULL)&&(x_uncle->color == red))					//if uncle is red->x,x_uncle up only
				{
					x->parent->color = black;
					x_uncle->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else										//if uncle is black->2 situation
				{
					if((x->parent->left != NULL)&&(x == x->parent->left))			
					{				//1 x is left child only rotate
						x = x->parent;
						this->RightRotate(x,x->left);
					}
					else if((x->parent->right != NULL)&&(x == x->parent->right))	
					{				//2 x is right child need to change color and rotate
						x->parent->parent->color = red;
						x->parent->color = black;
						this->LeftRotate(x->parent->parent,x->parent);
					}
				}
			}
		}
		root->color = black;
	}
}

void RBTree::Delete(int data)
{
   RBNode *x, *y;
   bool xNull = false;
   current = root;
   while((current != NULL)&&(current->item != data))
   {
	   if(data>current->item)
	   {
		   current = current->right;
	   }
	   else if(data<current->item)
	   {
		   current = current->left;
	   }
   }//while

   if(current == NULL)
   {
	   cout<<"can't find the element.."<<endl;
   }//can't find
   else
   {
	   if((current->left == NULL)&&(current->right == NULL))
	   {
		   y = current;
		   x = NULL;	   
	   }
	   else if((current->left != NULL)&&(current->right == NULL))
	   {
		   y = current;
		   x = current->left;		   
	   }
	   else if((current->left == NULL)&&(current->right != NULL))
	   {
		   y = current;
		   x = current->right;		   
	   }
	   else if((current->left != NULL)&&(current->right != NULL))
	   {
		   y = current->right;
		   while(y->left != NULL)
		   {
			   y = y->left;
		   }
			x = y->right;
		    current->item = y->item;
	   }
	  if(y->color == black)
	  {
		  if(x == NULL)
		  {
			  x = y;
			  xNull = true;
		  }
		  this->DeleteFixup(x);
	  }

	  if(xNull) 
		  x = NULL;

	  if(y == root)
	  {
		  cout<<"The tree root be deleted.."<<endl;
		if(x == NULL)
			root = NULL;
		else
			root = x;
	  }
	  else
	  {
		  if(y->parent->left == y)
		  {
			  y->parent->left = x;
			  if(x != NULL)
				  x->parent = y->parent;
		  }
		  else if(y->parent->right == y)
		  {
			  y->parent->right = x;
			  if(x != NULL)
				  x->parent = y->parent;
		  }
	  }
	 delete y;
	}
}


void RBTree::DeleteFixup(RBNode *x)
{
	RBNode *w;
	RBNode *plNull = new RBNode(0);
	plNull->color = black;
	RBNode *prNull = new RBNode(0);
	prNull->color = black;

	while((x != root)&&(x->color == black))
	{
		if(x->parent->left == x)                  //  x = left(px)
		{	//situation 1
			w = x->parent->right;
			
			if(w->left == NULL)
			{
				w->left = plNull;
				plNull->parent = w;
			}
			if(w->right == NULL)
			{
				w->right = prNull;
				prNull->parent = w;
			}
				
			if(w->color == red)
			{
				w->color = black;
				w->parent->color = red;
				this->LeftRotate(w->parent,w);
			}
			else
			{
				if((w->left->color == black)&&(w->right->color == black))
				{
					w->color = red;
					x = x->parent;
				}
				else if((w->left->color == red)&&(w->right->color == black))
				{
					w->left->color = black;
					w->color = red;
					this->RightRotate(w,w->left);
				}
				else if(w->right->color == red)
				{
					w->color = w->parent->color;
					w->parent->color = black;
					w->right->color = black;
					this->LeftRotate(w->parent,w);
					x = root;
				}
			}
		}
		else if(x->parent->right == x)                  //  x = left(px)
		{	//situation 1
			w = x->parent->left;

			if(w->left == NULL)
				w->left = plNull;
			if(w->right == NULL)
				w->right = prNull;

			if(w->color == red)
			{
				w->color = black;
				w->parent->color = red;
				this->RightRotate(w->parent,w);
			}
			else
			{
				if((w->left->color == black)&&(w->right->color == black)) 
				{
					w->color = red;
					x = x->parent;
				}
				else if((w->right->color == red)&&(w->right->color == black))
				{
					w->right->color = black;
					w->color = red;
					this->LeftRotate(w,w->left);
				}
				else if(w->left->color == red)
				{
					w->color = w->parent->color;
					w->parent->color = black;
					w->left->color = black;
					this->RightRotate(w->parent,w);
					x = root;
				}
			}
		}
		
		if(plNull->parent != NULL)
		{
			if(plNull->parent->left == plNull)
				plNull->parent->left = NULL;
			else if(plNull->parent->right == plNull)
				plNull->parent->right = NULL;

			plNull->parent = NULL;
		}
		if(prNull->parent != NULL)
		{
			if(prNull->parent->left == prNull)
				prNull->parent->left = NULL;
			else if(prNull->parent->right == prNull)
				prNull->parent->right = NULL;
			
			prNull->parent = NULL;
		}
	}
	x->color = black;
	delete plNull;
	delete prNull;
}



																	

			
		
				




