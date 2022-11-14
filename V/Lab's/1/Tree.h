#pragma once
#include <vector>


using namespace std;
using uint = unsigned int;

template <class T> class BinTree;


template <class T> class TreeNode
{

private: 
	
	// Left and right nodes
	TreeNode<T> *_left;
	TreeNode<T> *_right;

public:

	// Data
	T _data;

	// Конструктор
	// Constuctor
	TreeNode(const T& data, TreeNode<T> *l = nullptr, TreeNode<T> *r = nullptr)
	{
		_data = data;
		_left = l;
		_right = r;
	}


	TreeNode<T> *Left(void) const
	{
		return _left;
	}
	TreeNode<T> *Right(void) const
	{
		return _right;
	}
	TreeNode<T> *This(void)
	{
		return this;
	}


	void SetChild(TreeNode<T> *l = nullptr, TreeNode<T> *r = nullptr)
	{
		_left = l;
		_right = r;

	}

	void ShowData()
	{
		cout << _data;
	}

	uint GetDepth(uint number = nullptr)
	{
		TreeNode<T> *temp = this;
		uint counter = number;
		

		while ((temp->Left() != nullptr) || (temp->Right() != nullptr))
		{
			if (temp->Left() == nullptr)
			{
				temp = temp->Right();
				counter++;
			}
			else if (temp->Right() == nullptr)
			{
				temp = temp->Left();
				counter++;
			}
			else
			{
				uint tempc = counter;
				counter = temp->Left()->GetDepth(tempc + 1);
				counter = temp->Right()->GetDepth(tempc + 1);

				break;
			}
		}
		
		return counter;

	}

	void Delete()
	{
		TreeNode<T> *temp = this;

		while ((temp->Left() != nullptr) || (temp->Right() != nullptr))
		{
			if (temp->Left() == nullptr)
			{
				temp = temp->Right();
			}
			else if (temp->Right() == nullptr)
			{
				temp = temp->Left();
			}
			else
			{
				temp->Left()->Delete();
				temp->Right()->Delete();
			}
		}

		delete temp;
		
	}



	friend class BinTree<T>;

};
