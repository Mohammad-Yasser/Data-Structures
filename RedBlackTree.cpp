#include <bits/stdc++.h>
using namespace std;

struct Node {
	int val = -1;bool red = 1;
	Node *parent = 0, *left = 0, *right = 0;
	Node() {

	}
	Node(bool red, int val, Node* parent) :
			val(val), red(red), parent(parent) {

	}
};

struct RedBlackTree {
	Node *root = 0;
	inline void insert(int val) {
		if (root == NULL)
			root = new Node(0, val, 0);
		else {
			Node *parent = search(val);

			Node* newNode = new Node(1, val, parent);
			if (val > parent->val)
				parent->right = newNode;
			else
				parent->left = newNode;
			fix(newNode);
		}
	}

	void fix(Node *curr) {
		if (!curr or curr == root or !curr->parent->red) {
			root->red = 0;
			return;
		}

		Node *parent = curr->parent;
		Node *grandParent = parent->parent;
		Node *uncle;
		if (grandParent->left == parent)
			uncle = grandParent->right;
		else
			uncle = grandParent->left;
		if (uncle && uncle->red) {
			uncle->red = parent->red = 0;
			grandParent->red = 1;
			fix(grandParent);
			return;
		}

		bool parentLeft = (grandParent->left == parent), currLeft = (parent->left == curr);
		if (parentLeft != currLeft) {
			rotate(curr);
			fix(parent);
			return;
		}

		rotate(parent);
		parent->red = 0;
		if (parent->left)
			parent->left->red = 1;
		if (parent->right)
			parent->right->red = 1;
		return;
	}

	void displaySorted(Node* curr) {
		if (!curr)
			return;
		displaySorted(curr->left);
		cout << curr->val << ' ';
		displaySorted(curr->right);

	}

	int getHeight(Node *curr) {
		if (!curr)
			return 0;
		return 1 + max(getHeight(curr->left), getHeight(curr->right));
	}

	void getSortedVector(Node* curr, vector<int> & vec) {
		if (!curr)
			return;
		getSortedVector(curr->left, vec);
		vec.push_back(curr->val);
		getSortedVector(curr->right, vec);

	}

	inline Node* search(int val) {
		Node *curr = root, *parent = NULL;

		while (curr != NULL) {
			parent = curr;
			if (val > curr->val)
				curr = curr->right;
			else
				curr = curr->left;
		}
		return parent;
	}

	inline Node** getChildNode(Node* child) { // return Node** pointing to the Node* pointing to the child
		Node* parent = child->parent;
		if (parent == NULL)
			return NULL;
		if (parent->left == child)
			return &parent->left;
		return &parent->right;
	}

	inline bool isLeftChild(Node *child) {
		Node* parent = child->parent;
		return parent->left == child;
	}

	inline void rotate(Node *child) {
		if (child == root)
			return;
		bool isLeft = isLeftChild(child);
		Node *parent = child->parent, *grandParent = parent->parent;
		if (grandParent)
			*getChildNode(parent) = child;
		child->parent = grandParent;
		parent->parent = child;
		if (isLeft) {
			parent->left = child->right;
			if (parent->left)
				parent->left->parent = parent;
			child->right = parent;
		} else {
			parent->right = child->left;
			if (parent->right)
				parent->right->parent = parent;
			child->left = parent;
		}
		if (root == parent)
			root = child;
	}
};

int main() {

	RedBlackTree tree;

	const int N = 30000;
	vector<int> vec(N);
	for (int i = 0; i < N; ++i)
		vec[i] = rand();


	for (auto x : vec)
		tree.insert(x);

	sort(vec.begin(), vec.end());

	vector<int> v2;
	tree.getSortedVector(tree.root, v2);

	cout << (v2 == vec) << endl;
	cout << tree.getHeight(tree.root) << ' ' << log2(N);

	return 0;
}
