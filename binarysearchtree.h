#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <type_traits>
#include <qdebug.h>

template <typename T> class BinarySearchTree;

template <typename T> class TreeNode
{
    friend class BinarySearchTree<T>;
public:
    TreeNode(const T);
    ~TreeNode();
    T getData();
protected:
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    T data;
    bool hasLeftIterated;
    bool hasRightIterated;
};

template <typename T>
class BinarySearchTree
{
public:
    bool isSelfRemovable;

    BinarySearchTree(bool(*compare)(const T x, const T y));
    ~BinarySearchTree();
    T iterate(TreeNode<T> *&iterator);
    void insert(const T);
    void remove(const T);
    TreeNode<T> *getRoot();
protected:
    TreeNode<T> *root;

    bool (*compare)(T x, T y);
    TreeNode<T>* findNode(const T);
    TreeNode<T>* findSuccessor(TreeNode<T> *node);
};

template<typename T>
TreeNode <T>::TreeNode(const T a) :
    left(0),
    right(0),
    parent(0),
    data(a),
    hasLeftIterated(false),
    hasRightIterated(false)
{
}

template<typename T>
TreeNode <T>::~TreeNode()
{
    if (std::is_pointer<T>::value)
    {
        qDebug() << "is a pointer";
        delete data;
    }
}

template <typename T>
T TreeNode<T>::getData()
{
    return data;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(bool(*p_compare)(const T x, const T y)) :
    isSelfRemovable(false),
    root(0),
    compare(p_compare)
{
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    if (isSelfRemovable)
    {
        TreeNode<T> *iterator = root;
        while (iterator->left || iterator->right || iterator->parent)
        {
            if (iterator->left)
            {
                iterator->hasLeftIterated = true;
                iterator = iterator->left;
            }
            else if (iterator->right)
            {
                iterator->hasRightIterated = true;
                iterator = iterator->right;
            }
            else
            {
                iterator = iterator->parent;
                if (iterator->left && iterator->hasLeftIterated)
                {
                    delete iterator->left;
                    iterator->left = 0;
                }
                else if (iterator->right && iterator->hasRightIterated)
                {
                    delete iterator->right;
                    iterator->right = 0;
                }
            }
        }
        delete iterator;
    }
}

template<typename T>
T BinarySearchTree<T>::iterate(TreeNode<T> *&iterator)
{
    TreeNode<T> *tempIterator;
    if (iterator == 0)
    {
        iterator = root;
    }

    // We must prevent returning the right element first
    // if there is no left child.
    if (!iterator->left && !iterator->hasRightIterated)
    {
        tempIterator = iterator;
        iterator->hasLeftIterated = true;
        iterator->hasRightIterated = true;
        iterator = iterator->right;
        return tempIterator->data;
    }
    if (iterator->left && !iterator->hasLeftIterated)
    {
        while (iterator->left)
        {
            iterator->hasLeftIterated = true;
            iterator = iterator->left;
        }
        return iterator->data;
    }
    else if (iterator->right && !iterator->hasRightIterated)
    {
        iterator->hasRightIterated = true;
        iterator = iterator->right;
        while (iterator->left)
        {
            iterator->hasLeftIterated = true;
            iterator = iterator->left;
        }
        return iterator->data;
    }
    else if (iterator->parent)
    {
        iterator = iterator->parent;
        // The case: we are on this node at least for the second time
        //           and we have all the childs iterated,
        //           so we have to go up.
        if (iterator->hasRightIterated)
        {
            while (iterator->parent)
            {
                iterator->hasLeftIterated = false;
                iterator->hasRightIterated = false;
                iterator = iterator->parent;
                if (iterator->right && !iterator->hasRightIterated)
                {
                    return iterator->data;
                }
            }
            // The case: it's the root element.
            iterator->hasLeftIterated = false;
            iterator->hasRightIterated = false;
            iterator = 0;
            return 0;
        }
        // The case: the right child wasn't iterated yet.
        else
        {
            // The case: if there is no child on the right we have
            //           to check 'hasRightIterated' to true
            //           in order to prevent infinite loop.
            if (!iterator->right)
            {
                iterator->hasRightIterated = true;
            }
            return iterator->data;
        }
    }
    // The case: the only element is the root.
    else
    {
        // The case: it has been traversed so we have to stop.
        if (iterator->hasLeftIterated && iterator->hasRightIterated)
        {
            iterator->hasLeftIterated = false;
            iterator->hasRightIterated = false;
            iterator = 0;
            return 0;
        }
        // The case: it has not been traversed yet.
        else
        {
            iterator->hasLeftIterated = true;
            iterator->hasRightIterated= true;
            return iterator->data;
        }
    }
}

template<typename T>
void BinarySearchTree<T>::insert(const T x)
{
    TreeNode<T>* n = new TreeNode<T>(x);
    TreeNode<T>* ptr;
    TreeNode<T>* ptr1;

    n->parent = 0;
    n->left = 0;
    n->right = 0;

    ptr = root;
    ptr1 = ptr;
    while(ptr != 0)
    {
        ptr1 = ptr;
        if(compare(x, ptr->data))
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
    }
    n->parent = ptr1;
    if (ptr1 == 0)
    {
        root = n;
    }
    else
    {
        if(compare(x, ptr1->data))
        {
            ptr1->left = n;
        }
        else
        {
            ptr1->right = n;
        }
    }
}

template<typename T>
void BinarySearchTree<T>::remove(const T element)
{
    TreeNode<T> *iterator;
    TreeNode<T> *tempIterator;

    if ((iterator = findNode(element)) != NULL)
    {
        // The case: there are two childs.
        if (iterator->left && iterator->right)
        {
            tempIterator = findSuccessor(iterator);
            if (tempIterator->right)
            {
                if (tempIterator->parent == iterator)
                {
                    iterator->right = tempIterator->right;
                }
                else
                {
                    tempIterator->parent->left = tempIterator->right;
                    tempIterator->right->parent = tempIterator->parent;
                }
                tempIterator->right = iterator->right;
                iterator->right->parent = tempIterator;
            }

            if (iterator->parent)
            {
                tempIterator->parent = iterator->parent;
            }
            else
            {
                root = tempIterator;
                tempIterator->parent = NULL;
            }
            tempIterator->left = iterator->left;
            iterator->left->parent = tempIterator;
        }
        // The case: there is only right child.
        else if (iterator->right)
        {
            if (iterator->parent)
            {
                if (compare(element, iterator->parent->data))
                {
                    iterator->parent->left = iterator->right;
                }
                else
                {
                    iterator->parent->right = iterator->right;
                }
                iterator->right->parent = iterator->parent;
            }
            else
            {
                root = iterator->right;
            }
        }
        // The case: there is only left child.
        else if (iterator->left)
        {
            if (iterator->parent)
            {
                if (compare(element, iterator->parent->data))
                {
                    iterator->parent->left = iterator->left;
                }
                else
                {
                    iterator->parent->right = iterator->left;
                }
                iterator->left->parent = iterator->parent;
            }
            else
            {
                root = iterator->left;
            }
        }
        // The case: current element is a leaf (doesn't have any child)
        else if (iterator->parent)
        {
            if (compare(element, iterator->parent->data))
            {
                iterator->parent->left = NULL;
            }
            else
            {
                iterator->parent->right = NULL;
            }
        }
        else
        {
            root = NULL;
        }
        delete iterator;
    }
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::findNode(const T val)
{
    if (root->data == val)
    {
        return root;
    }

    TreeNode<T> *iterator = root;
    while (iterator->left || iterator->right)
    {
        if (iterator->left && compare(val, iterator->data))
        {
            iterator = iterator->left;
        }
        else if (iterator->right && !compare(val, iterator->data))
        {
            iterator = iterator->right;
        }
        if (iterator->data == val)
        {
            return iterator;
        }
    }
    return 0;
}

/**
 * Finds last left (minimal) node from the right subtree of the node.
 */
template<typename T>
TreeNode<T>* BinarySearchTree<T>::findSuccessor(TreeNode<T> *node)
{
    node = node->right;
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::getRoot()
{
    return root;
}

#endif // BINARYTREE_H
