#pragma once
//Fahad Waheed

#include<queue>
#include<iostream>

using namespace std;

template <typename K, typename V>
class MaxHeap
{
public:
	struct Node
	{
		K key;
		V value;
		Node* left, * right;
		Node* parent;

		Node() : key(K()), value(V()), left(NULL), right(NULL), parent(NULL) {};

		Node(K key, V value) : key(key), value(value), left(NULL), right(NULL), parent(NULL) {};
	};

	void SwapNodes(Node*& node1, Node*& node2)
	{
		K key = node1->key;
		V value = node1->value;

		node1->key = node2->key, node1->value = node2->value;
		node2->key = key, node2->value = value;
	}

	K getKey(Node* node)
	{
		if (node == NULL)
			return K();
		return node->key;
	}

	Node* MaximumNode(Node* node1, Node* node2)
	{
		return getKey(node1) > getKey(node2) ? node1 : node2;
	}

	Node* LastNode()
	{
		queue<Node*> Q;
		Q.push(root);
		Node* currnode = NULL;

		while (!Q.empty())
		{
			currnode = Q.front();
			Q.pop();

			if (currnode->left)
				Q.push(currnode->left);
			if (currnode->right)
				Q.push(currnode->right);
		}
		return currnode;
	}

	void CopyNodes(const MaxHeap<K, V>& obj)
	{
		if (obj.root)
		{
			queue<Node*> Q;
			Q.push(obj.root);
			Node* currnode = NULL;

			while (!Q.empty())
			{
				currnode = Q.front();
				Q.pop();

				Insert(pair<K, V>(currnode->key, currnode->value));

				if (currnode->left)
					Q.push(currnode->left);
				if (currnode->right)
					Q.push(currnode->right);
			}
		}
	}

	Node* root;

public:
	MaxHeap() : root(NULL) {};

	MaxHeap(const MaxHeap<K,V>& obj) : root(NULL)
	{
		CopyNodes(obj);
	}

	MaxHeap<K, V>& operator=(const MaxHeap<K, V>& obj)
	{
		this->clear();
		CopyNodes(obj);
		*this;
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	void Insert(pair<K, V> P)
	{
		Node* newNode = new Node(P.first, P.second);
		if (isEmpty())
		{
			root = newNode;
		}
		else
		{
			queue<Node*> Q;
			Q.push(root);
			Node* currnode = NULL;

			while (!Q.empty())
			{
				currnode = Q.front();
				Q.pop();

				if (currnode->left)
					Q.push(currnode->left);
				else
				{
					currnode->left = newNode;
					currnode->left->parent = currnode;
					break;
				}

				if (currnode->right)
					Q.push(currnode->right);
				else
				{
					currnode->right = newNode;
					currnode->right->parent = currnode;
					break;
				}
			}

			Node* parent = newNode->parent;
			while (parent && parent->key < newNode->key)
			{
				SwapNodes(parent, newNode);
				newNode = parent;
				parent = parent->parent;
			}
		}
	}

	void Display()
	{
		if (isEmpty())
			return;

		queue<Node*> Q;
		Q.push(root);
		Node* currnode = NULL;

		while (!Q.empty())
		{
			currnode = Q.front();
			Q.pop();

			cout << currnode->key << "  " << currnode->value << endl;

			if (currnode->left)
				Q.push(currnode->left);
			
			if (currnode->right)
				Q.push(currnode->right);
		}

	}

	pair<K, V> DeleteMax()
	{
		pair<K, V> P;

		if (!isEmpty())
		{
			P.first = root->key, P.second = root->value;

			Node* lastNode = LastNode();
			if (root == lastNode)
			{
				delete root;
				root = NULL;
			}
			else
			{
				root->key = lastNode->key, root->value = lastNode->value;

				if (lastNode->parent->left == lastNode)
					lastNode->parent->left = NULL;
				else if (lastNode->parent->right == lastNode)
					lastNode->parent->right = NULL;

				delete lastNode;
				lastNode = NULL;

				Node* currnode = root;
				Node* maxNode = NULL;

				while (currnode->left || currnode->right)
				{
					maxNode = MaximumNode(currnode->left, currnode->right);
					if (currnode->key < maxNode->key)
						SwapNodes(currnode, maxNode);
					else
						break;

					currnode = maxNode;
				}
			}
		}

		return P;
	}

	void clear()
	{
		if (isEmpty())
			return;

		queue<Node*> Q;

		Q.push(root);
		Node* currnode = NULL;

		while (!Q.empty())
		{
			currnode = Q.front();
			Q.pop();

			if (currnode->left)
				Q.push(currnode->left);
			if (currnode->right)
				Q.push(currnode->right);

			delete currnode;
		}

		root = NULL;
	}

	~MaxHeap()
	{
		clear();
	}
};