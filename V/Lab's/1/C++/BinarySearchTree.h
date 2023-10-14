#include <iostream>
#include "BinarySearchTreeNode.h"
#include <stack>

using namespace std;

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTreeNode<T> *Root;

    BinarySearchTree(BinarySearchTreeNode<T> *root = nullptr)
    {
        Root = root;
    }

    void Add(T value)
    {
        auto addingNode = new BinarySearchTreeNode<T>(value);

        if (Root == nullptr)
            Root = addingNode;
        else
        {
            BinarySearchTreeNode<T> *nodeBuffer = Root;
            T valueBuffer;

            while (true)
            {
                valueBuffer = nodeBuffer->Value;
                bool isMore = valueBuffer > value;
                if (nodeBuffer->Right != nullptr && isMore)
                    nodeBuffer = nodeBuffer->Right;
                else if (nodeBuffer->Left != nullptr && !isMore)
                    nodeBuffer = nodeBuffer->Left;
                else
                {
                    if (isMore)
                        nodeBuffer->Right = addingNode;
                    else
                        nodeBuffer->Left = addingNode;

                    break;
                }
            }
        }
    }

    bool Contains(T value)
    {
        BinarySearchTreeNode<T> *nodeBuffer = Root;

        while (nodeBuffer != nullptr)
        {
            T valueBuffer = nodeBuffer->Value;
            if (value == valueBuffer)
                return true;
            else if (valueBuffer > value)
                nodeBuffer = nodeBuffer->Right;
            else
                nodeBuffer = nodeBuffer->Left;
        }

        return false;
    }

    int Count()
    {
        if (Root == nullptr)
            return 0;

        stack<BinarySearchTreeNode<T> *> s;
        int count = 1;
        s.push(Root);

        while (!s.empty())
        {
            BinarySearchTreeNode<T> *nodeBuffer = s.top();
            s.pop();
            auto left = nodeBuffer->Left;
            auto right = nodeBuffer->Right;
            if (left != nullptr)
            {
                s.push(left);
                count++;
            }
            if (right != nullptr)
            {
                s.push(right);
                count++;
            }
        }

        return count;
    }

    int CountLeaf()
    {
        if (Root == nullptr)
            return 0;

        stack<BinarySearchTreeNode<T> *> s;
        int count = 0;
        s.push(Root);

        while (!s.empty())
        {
            BinarySearchTreeNode<T> *nodeBuffer = s.top();
            s.pop();
            auto left = nodeBuffer->Left;
            auto right = nodeBuffer->Right;
            if (left != nullptr)
                s.push(left);
            if (right != nullptr)
                s.push(right);
            if (left == nullptr && right == nullptr)
                count++;
        }

        return count;
    }

    int GetDepth()
    {
        if (Root == nullptr)
            return -1;

        int depth = 0;

        stack<pair<BinarySearchTreeNode<T> *, int>> s;
        s.push(make_pair(Root, 0));
        
        while (!s.empty())
        {
            pair<BinarySearchTreeNode<T> *, int> bufferPair = s.top();
            s.pop();

            auto left = bufferPair.first->Left;
            auto currentDepth = bufferPair.second;
            auto right = bufferPair.first->Right;

            if (left != nullptr)
                s.push(make_pair(left, currentDepth + 1));
            if (right != nullptr)
                s.push(make_pair(right, currentDepth + 1));

            if (currentDepth > depth)
                depth = currentDepth;
        }

        return depth;
    }

    ~BinarySearchTree<T>()
    {
        Clear();
    }

    void Clear()
    {
        if (Root != nullptr)
        {
            DisposeRootChildren();
            delete Root;
            Root = nullptr;
        }
    }

    void DisposeRootChildren()
    {
        if (Root == nullptr)
            return;

        auto nd{[](stack<BinarySearchTreeNode<T> *> &s, BinarySearchTreeNode<T> *&node)
                {
                    if (node->Left != nullptr)
                    {
                        s.push(node->Left);
                        node->Left = nullptr;
                    }
                    if (node->Right != nullptr)
                    {
                        s.push(node->Right);
                        node->Right = nullptr;
                    }
                }};

        stack<BinarySearchTreeNode<T> *> s;
        nd(s, Root);

        while (!s.empty())
        {
            BinarySearchTreeNode<T> *node = s.top();
            s.pop();
            nd(s, node);
            delete node;
        }
    }

    string ToString()
    {
        return "Root: [" + (Root == nullptr ? "NULL" : Root->ToString()) + "]";
    }
};
