#include "tree.h"
#include <iostream>
#include <string.h>

using namespace std;


//constructor

Tree::Tree()
{
    root = NULL;
    return;
}

//destructor

Tree::~Tree()
{
    ClearTree(root);
    return;
}

//recursive traversal of tree destroying all nodes

void Tree::ClearTree(TreeNode *T)
{
    if(T==NULL) return;  // Nothing to clear
    if(T->left != NULL) ClearTree(T->left); // Clear left sub-tree
    if(T->right != NULL) ClearTree(T->right); // Clear right sub-tree
    delete T;    // Destroy this node
    return;
}

//check if tree is empty 

bool Tree::isEmpty()
{
    return(root==NULL);
}


//duplicate node on a tree
TreeNode *Tree::DupNode(TreeNode * T)
{
    TreeNode *dupNode;

    dupNode = new TreeNode();
    *dupNode = *T;    // Copy the data structure
    dupNode->left = NULL;    // Set pointers to NULL
    dupNode->right = NULL;
    return dupNode;
}

//searching the tree

TreeNode *Tree::SearchTree(int Key)
{
    int      ValueInTree = false;
    TreeNode *temp;

    temp = root;
    while((temp != NULL) && (temp->Key != Key))
    {
        if(Key < temp->Key)
            temp = temp->left;  //searching the key that comes before this node.
        else
            temp = temp->right; //searching the key that comes after this node 
    }
    if(temp == NULL) return temp;    //if key is not found
    else
        return(DupNode(temp));    //if found, return duplicate
}

//creating new node
bool Tree::Insert(TreeNode *newNode)
{
    TreeNode *temp;
    TreeNode *back;

    temp = root;
    back = NULL;

    while(temp != NULL) // Loop till temp falls out of the tree 
    {
        back = temp;
        if(newNode->Key < temp->Key)
            temp = temp->left;
        else
            temp = temp->right;
    }

    //Attach the new node to the node that back points to 
    if(back == NULL) // Attach as root node in a new tree 
        root = newNode;
    else
    {
        if(newNode->Key < back->Key)
            back->left = newNode;
        else
            back->right = newNode;
    }
   return true ;
}

//inserting data to the tree
bool Tree::Insert(int Key, float f, int i, char *cA)
{
    TreeNode *newNode;

    // Create the new node and copy data into it
    newNode = new TreeNode();
    newNode->Key = Key;
    newNode->fValue = f;
    newNode->iValue = i;
    strcpy(newNode->cArray, cA);
    newNode->left = newNode->right = NULL;

    // repeating insert until done
    return(Insert(newNode));
}

//deletion
bool Tree::Delete(int Key)
{
    TreeNode *back;
    TreeNode *temp;
    TreeNode *delParent;    // Parent of node to delete
    TreeNode *delNode;      // Node to delete

    temp = root;
    back = NULL;

    // Find the node to delete 
    while((temp != NULL) && (Key != temp->Key))
    {
        back = temp;
        if(Key < temp->Key)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if(temp == NULL) // Didn't find the one to delete 
    {
        return false;
    }
    else
    {
        if(temp == root) // Deleting the root 
        {
            delNode = root;
            delParent = NULL; 
        }                
        else
        {
            delNode = temp;
            delParent = back;
        }
    }

    // Case 1: Deleting node with no children or one child 
    if(delNode->right == NULL)
    {
        if(delParent == NULL)    // If deleting the root    
        {
            root = delNode->left;
            delete delNode;
            return true;
        }
        else
        {
            if(delParent->left == delNode)
                delParent->left = delNode->left;
            else
                delParent->right = delNode->left;
                delete delNode;
            return true;
        }
    }
    else // There is at least one child 
    {
        if(delNode->left == NULL)    // Only 1 child and it is on the right
        {
            if(delParent == NULL)    // If deleting the root    
            {
                root = delNode->right;
                delete delNode;
                return true;
            }
            else
            {
                if(delParent->left == delNode)
                    delParent->left = delNode->right;
                else
                    delParent->right = delNode->right;
                delete delNode;
                return true;
            }
        }
        else // Case 2: Deleting node with two children 
        {
            /*finding the replacement value, Locate the node  
             containing the largest value smaller than the 
             key of the node being deleted.*/                
            temp = delNode->left;
            back = delNode;
            while(temp->right != NULL)
            {
                back = temp;
                temp = temp->right;
            }
            // Copy the replacement values into the node to be deleted 
            delNode->Key = temp->Key;
            delNode->fValue = temp->fValue;
            delNode->iValue = temp->iValue;
            strcpy(delNode->cArray, temp->cArray);

            // Remove the replacement node from the tree 
            if(back == delNode)
                back->left = temp->left;
            else
                back->right = temp->left;
            delete temp;
            return true;
        }
    }
}

//printing the data for only 1 node
void Tree::PrintOne(TreeNode *T)
{
    cout << T->Key << "\t\t" << T->fValue << "\t\t" << T->iValue << "\t\t" 
        << T->cArray << "\n";
}

//printing all data in B-tree

void Tree::PrintAll(TreeNode *T)
{
    if(T != NULL)
    {
        PrintAll(T->left);
        PrintOne(T);
        PrintAll(T->right);
    }
}
