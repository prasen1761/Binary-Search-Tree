/*
Binary Search Tree :
Create Node
Find parent node
Find Node pointer of value 
Insertion
Deletion
Calculate Height of the node
Pre order traversal
In order traversal
Post order traversal
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<vector>
using namespace std;

/*Declare a node structure which consists of data value of the node, left pointer pointing to the left subtree, right pointer pointing to the right subtree and height of the node(optional information)*/
struct Node
{
  int value;
  struct Node * left;
  struct Node * right;
};

//Root pointer which initially points to NULL and later points to root of the BST
struct Node * root_ptr=NULL;

//List to read nodes from the .txt file in case reading an input from the .txt file
std::vector<string> node_list_fp;

//Create node by passing value of the node
struct Node * create_node(int value)
{
  struct Node * ptr= (struct Node *)malloc(sizeof(struct Node));
  ptr->value=value;
  ptr->left=NULL;
  ptr->right=NULL;
  return ptr;
}

//Print tree in Inorder traversal format
void print_tree_in(struct Node * root_ptr)
{
  if(root_ptr)
    {
      print_tree_in(root_ptr->left);
      cout<<root_ptr->value<<" ";
      print_tree_in(root_ptr->right);
    }
}

//Print tree in Preorder traversal format
void print_tree_pre(struct Node * root_ptr)
{
  if(root_ptr)
    {
      cout<<root_ptr->value<<" ";
      print_tree_pre(root_ptr->left);
      print_tree_pre(root_ptr->right);
    }
}

//Print tree in Postorder traversal format
void print_tree_post(struct Node * root_ptr)
{
  if(root_ptr)
    {
      print_tree_post(root_ptr->left);
      print_tree_post(root_ptr->right);
      cout<<root_ptr->value<<" ";
    }
}

//Insert node by passing node pointer and return root pointer
struct Node * insert_node(struct Node *node_ptr)
{
      struct Node * y=NULL;
      struct Node * x= root_ptr;
      while(x!=NULL)
	{
	  y=x;
	  if(node_ptr->value < x->value)
	    x=x->left;
	  else
	    x=x->right;
	}
      if (y==NULL)
	root_ptr=node_ptr;
      else if (node_ptr->value < y->value)//y acts as parent of newly inserted node
	y->left=node_ptr;
      else
	y->right=node_ptr;
      return root_ptr;
}

//Find the parent of node pointer
struct Node * find_parent(struct Node * ptr)
{
  struct Node * rp=root_ptr, *y=NULL;
  while(rp!=ptr)
    {
      if(rp->value > ptr->value)
	{
	  y=rp;
	  rp=rp->left;
	}
      else
	{
	  y=rp;
	  rp=rp->right;
	}
    }
  return y;
}

//Find the node pointer by passing node value
struct Node * find_NodePtr(int value)
{
  struct Node *rp=root_ptr;
  while((rp->value!=value) && (rp!=NULL))
    {
      if(rp->value > value)
	rp=rp->left;
      else
	rp=rp->right;
    }
  return rp;
}

//Delete the node by passing root pointer and value
struct Node * deletion(struct Node * root, int key)
{
  if(root==NULL) return root;
  else
    {
      struct Node * node_ptr= find_NodePtr(key);
      struct Node * parent=find_parent(node_ptr);
      if(((node_ptr->left!=NULL) && (node_ptr->right!=NULL)))
       {
	 struct Node *p=NULL,*y=NULL;
	 y=node_ptr->left;
	 p=node_ptr;
	 while(y->right!=NULL)
	   {
	     p=y;
	     y=y->right;
	   }
	 node_ptr->value=y->value;
	 node_ptr=y;
	 parent=p;
       }
      if((node_ptr->left==NULL) && (node_ptr->right==NULL))
	{
	  if(parent==NULL)return NULL;
	  if(parent->left==node_ptr)parent->left=NULL;
	  else
	    parent->right=NULL;
	  return root;
	}
      if(((node_ptr->left!=NULL) && (node_ptr->right==NULL)))
	{
	  if(parent==NULL)
	      return node_ptr->left;
	  if(parent->left==node_ptr)
	    parent->left=node_ptr->left;
	  else
	    parent->right=node_ptr->left;
	}
      if(((node_ptr->left==NULL) && (node_ptr->right!=NULL)))
	{
	  if(parent==NULL)
	      return node_ptr->right;
	  if(parent->left==node_ptr)
	    parent->left=node_ptr->right;
	  else
	    parent->right=node_ptr->right;
	}
    }
  return root;
}

//Returns Max of two
int max(int a, int b)
{
  return (a>b)?a:b;
}

//Find the height of the node in the tree: starting from 0 of root node
int height_node(struct Node * node_ptr)
{
  if((node_ptr->left==NULL)&&(node_ptr->right==NULL))return 0;
  else if((node_ptr->left!=NULL)&&(node_ptr->right==NULL))
    return 1+height_node(node_ptr->left);
  else if((node_ptr->left==NULL)&&(node_ptr->right!=NULL))
    return 1+height_node(node_ptr->right);
  else
    return 1+max(height_node(node_ptr->left),height_node(node_ptr->right));
}

//Main function
int main(int argc, char *argv[])
{
  struct Node * node_ptr;
  cout<<"Choose one of the options below\n1-Enter a node\n2-Delete a node\n3-Print the tree in L D R format\n4-Height of the node\n5-Quit\n";
  int option;
  cin>>option;
  int val;
  while(option!=5)
    {
      switch(option)
	{
	   case 1: //Insertion
	     cout<<"Enter the value to be insert\n";
	     cin>>val;
	     node_ptr=create_node(val);
	     root_ptr=insert_node(node_ptr);
	     break;
	   case 2: //Delete
	     cout<<"Enter the value to be deleted\n";
	     cin>>val;
	     root_ptr=deletion(root_ptr,val);
	     break;
	   case 3: //print
	     cout<<"\nPre order: ";
	     print_tree_pre(root_ptr);
	     cout<<"\nIn order: ";
	     print_tree_in(root_ptr);
	     cout<<"\nPost order: ";
	     print_tree_post(root_ptr);
	     break;
	   case 4: //height of the node
	     cout<<"Enter the value whose height is to be calculated\n";
	     cin>>val;
	     node_ptr=find_NodePtr(val);
	     cout<<"\nHeight of the node is "<<height_node(node_ptr);
	     break;
	   case 5: //quit
	     break;
	}
      cout<<"\nEnter an option again\n";
      cin>>option;
    }
  return 0;
}
