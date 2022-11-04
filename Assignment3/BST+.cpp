#include "BST+.h"

template <class T>
BSTNode<T> *BST<T>::findLeftMost(bst_node *nodePtr)
{

    // if tree is empty
    if (nodePtr == nullptr)
    {
        return nullptr;
    }
    // if no nodes on the left return this node
    else if (nodePtr->left == nullptr)
    {
        return nodePtr;
    }
    // recursively find the left most node
    else
    {
        return findLeftMost(nodePtr->left);
    }
}

template <class T>
BSTNode<T> *BST<T>::destroySubTree(bst_node *node)
{
    // base case
    if (node == nullptr)
        return nullptr;
    else
    {
        destroySubTree(node->left);
        destroySubTree(node->right);
        delete node;
    }
    return nullptr;
}

template <class T>
void BST<T>::insertNode(const T &val)
{
    bst_node *newNode = new BSTNode(val);
    bst_node *nodePtr;

    // check if the tree is empty
    if (isEmpty())
    {
        // if empty make newnode the root
        root = newNode;
        return;
    }
    else
        nodePtr = root;

    // traverse the tree till an empty branch is found or a duplicate node is found
    while (nodePtr != nullptr)
    {
        if (val < nodePtr->value)
            if (nodePtr->left)
                nodePtr = nodePtr->left;
            
            else
            {
                nodePtr->left = newNode;
                break;
            }
        
    
        else if (val > nodePtr->value)
            if (nodePtr->right)
                nodePtr = nodePtr->right;
            
            else 
            {
                nodePtr->right = newNode;
                break;
            }
            
        
        else
            // increase the count of the node if duplicate value is found
            nodePtr->count++;
            break;
        
    }
}

template <class T>
void BST<T>::remove(const T &val)
{
    // use of a helper function for deletion
    root = deleteNode(val, root);
}

template <class T>
BSTNode<T> *BST<T>::deleteNode(const T &val, bst_node *nodePtr)
{
    // temp stores the address of the node to be deleted
    bst_node *temp;
    if (nodePtr == nullptr)
        return nullptr;
    else if (val < nodePtr->value)
        nodePtr->left = deleteNode(val, nodePtr->left);
    else if (val > nodePtr->value)
        nodePtr->right = deleteNode(val, nodePtr->right);
    else if (nodePtr->left && nodePtr->right)
    {
        // if duplicate found no need to delete just reduce the count
        if (nodePtr->count > 1)
        {
            nodePtr->count--;
            return nodePtr;
        }
        temp = findLeftMost(nodePtr->right);
        nodePtr->value = temp->value;
        nodePtr->right = deleteNode(nodePtr->value, nodePtr->right);
    }
    else
    {
        if (nodePtr->count > 1)
        {
            nodePtr->count--;
            return nodePtr;
        }
        temp = nodePtr;
        if (nodePtr->left == nullptr)
            nodePtr = nodePtr->right;
        else if (nodePtr->right == nullptr)
            nodePtr = nodePtr->left;
        delete temp;
    }

    return nodePtr;
}

template <class T>
T *BST<T>::search(bst_node *node, const T &searchVal) const
{
    while (node != nullptr)
    {
        if (searchVal > node->value)
            node = node->right;
    
        else if (searchVal < node->value)
            node = node->left;

        else
            return &node->value;
    }
    return 0;
}

template <class T>
void BST<T>::searchNode(const T &val) const
{
    cout << ((search(root, val) != nullptr) ? 
    "Value found!" : "Value not found") << endl;
}

template <class T>
void BST<T>::displayNode(bst_node *node) const
{
    int count = node->count;
    cout << node->value << ", Count: " << node->count << "\n";
}

template <class T>
void BST<T>::displayInOrder(bst_node *node) const
{
    if (node != nullptr)
    {
        displayInOrder(node->left);
        displayNode(node);
        displayInOrder(node->right);
    }
    return;
}

template <class T>
void BST<T>::displayPostOrder(bst_node *node) const
{
    if (node != nullptr)
    {
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        displayNode(node);
    }
    return;
}

template <class T>
void BST<T>::displayPreOrder(bst_node *node) const
{
    if (node != nullptr)
    {
        displayNode(node);
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
    return;
}
