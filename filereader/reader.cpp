//Alex Scheufele
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int getLine(ifstream& stream, string& res);

class Node
{
	Node() : data(""), left(nullptr), right(nullptr) {}
	Node(string data) : data(data), left(nullptr), right(nullptr) {}
	string data;
	Node* left;
	Node* right;
	friend class BST;
};

class BST
{
public:
	BST(const char* filepath)
	{
		stream.open(filepath, ios::in);
		if (stream.fail())
		{
			cout << "file failed to open... exiting" << endl;
			exit(1);
		}
		root = new Node();
		if (!stream.fail())
		{
			getLine(stream, root->data);
		}
		else
		{
			std::cout << "Binary Search Tree Failed to Initialize... bad ifstream handle.";
		}
		string tmp;
		while (getLine(stream, tmp))
		{
			this->insert(root, tmp);
			tmp = "";
		}
	}
	int search(Node* root, string key)
	{
		if (root == nullptr)
		{
			return 0;
		}
		if (root->data == key)
		{
			cout << root->data << " == " << key << endl;
			return 1;
		}
		if (key > root->data)
		{
			return search(root->right, key);
		}
		if (key < root->data)
		{
			return search(root->left, key);
		}
	}
	void print_in_order_traversal(Node* pRoot)
	{
		if (pRoot == nullptr)
			return;
		cout << pRoot->data;
		print_in_order_traversal(pRoot->left);
		print_in_order_traversal(pRoot->right);
	}
	~BST()
	{
		del(root);
		stream.close();
	}

	Node* root;
private:
	ifstream stream;
	Node* insert(Node* root, string& data)
	{
		if (root == nullptr)
		{
			//cout << data << endl;
			return new Node(data);
		}
		if (root->data < data)
		{
			root->right = insert(root->right, data);
		}
		else if (root->data > data)
		{
			root->left = insert(root->left, data);
		}
		return root;
	}
	void del(Node* root)
	{
		if (root == nullptr)
			return;
		del(root->left);
		del(root->right);
		delete root;
	}
};

int main(int argc, char* argv)
{
	string user_phrase;

	cout << "loading data " << endl;
	auto start = chrono::steady_clock::now();
	BST tree("C:\\Users\\asche\\Downloads\\rockyou.txt");
	//BST tree("tester.txt");
	auto end = chrono::steady_clock::now();
	cout << "(" << chrono::duration_cast<chrono::seconds>(end - start).count() << "s)" << endl;
	cout << "This program will tell you if your entered phrase is listed in a file of the most commonly used passwords." << endl;
	cout << "This program does not store any phrase entered..." << endl;
	cout << "Enter phrase: ";
	
	cin >> user_phrase;

	//tree.print_in_order_traversal(tree.root);

	while (user_phrase != "q")
	{
		if (tree.search(tree.root, user_phrase))
		{
			cout << "Your phrase was found in the file. Sorry." << endl;
		}
		else
		{
			cout << "Congratulations. Your phrase was not found." << endl;
		}
		cout << "Enter another phrase, or 'q' to quit: ";
		cin >> user_phrase;
	}
	cout << "exiting..." << endl;

	return 0;
}

int getLine(ifstream& stream, string& res)
{
	if (stream.eof())
	{
		return 0;
	}
	char c = ' ';
	while ((c = stream.get()) != '\n' && !stream.eof())
	{
		res += c;
	}
	return 1;
}