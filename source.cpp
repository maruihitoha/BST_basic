#include <iostream>
//2015112147 �赵��
using namespace std;

// node Ŭ����
class node 
{
public:
	node(int key, node* left, node* right) //������.
		:key(key), left(left), right(right){}
	void show_child() 
	{ //����� �ڽ��� ������
		if (left == 0 && right == 0) 
		{
			cout << "no child " << endl;
		}
		else if (left != 0 && right == 0) 
		{
			cout << "left child only :: " << left->key << endl;
		}
		else if (left == 0 && right != 0) 
		{
			cout << "right child only :: " << right->key << endl;
		}
		else 
		{
			cout << "left :: " << left->key << " right :: "<< right->key <<endl;
		}
	}
private :
	int key;	// ������
	node* left;
	node* right;
	friend class BSTree;
};

class BSTree 
{// ����Ž��Ʈ���� �����ϴ� Ŭ����
public:

	BSTree() 
	{ // ������. ��带 NULL�� �ʱ�ȭ		
		head = 0;
	}

	~BSTree() 
	{ // Ŭ���� �Ҹ�� Ʈ�� ���� Ŭ���� ����
		clear();
	}

	node* Search_Node(int key)
	{ // ã���� �ϴ� ���� �����ϴ���
		node* tmp;
		tmp = head;
		while (tmp != 0) 
		{
			if (tmp->key == key) 
			{ 
				cout << "key found!!" << endl;
				return tmp; 
			}
			else if (tmp->key <= key)
			{ 
				tmp = tmp->right; 
			}
			else 
			{ 
				tmp = tmp->left; 
			}
		}
		cout << "key not found" << endl;
		return 0;
	}

	// ���� �Լ�
	void Insert_Node(int key) 
	{
		Insert_sub(head, key);
	}

	// �����Լ��� ����Լ� �κ�. 
	void Insert_sub(node*& p, int key) 
	{
		if (p == 0) 
		{ // �ش� ��Ʈ�� ������� �� ���ο� ��� ����
			p = new node(key, 0, 0);
		}
		else if (p->key < key) 
		{ // ���� ��ġ�� �����ͺ��� �Է¹��� ������ ���� Ŭ�� �������� �̵�
			Insert_sub(p->right, key);
		}
		else
		{// ���� ��ġ�� �����ͺ��� �Է¹��� ������ ���� ������ �������� �̵�
			Insert_sub(p->left, key);
		}
	}
	
	// ���� ���� ���� ã�� �� ���� �������� ��
	int return_min(node* min_p) 
	{
		while (min_p->left != 0) 
		{
			min_p = min_p->left;
		}
		return min_p->key;
	}

	

	void remove_sub(node*& p, int key) 
	{
		if (p->key < key) 
		{ // �����ϰ��� �ϴ� ���� ���� ��ġ���� Ŭ �� �����̵�
			remove_sub(p->right, key);
		}
		else if (p->key > key) 
		{// �����ϰ��� �ϴ� ���� ���� ��ġ���� ���� �� �����̵�
			remove_sub(p->left, key);
		}
		else 
		{ // �� �� �ƴϸ� �������̴ϱ� ���� ����
			delete_node(p);
		}

	}

	void remove(int key) 
	{
		if (Search_Node(key)) 
		{
			remove_sub(head, key);
		}
	}

	// ��� ���� ���� �Լ�. 
	void delete_node(node*& p) 
	{
		node* tmpP;
		int tmp;
		tmpP = p;

		if (p->left == 0) 
		{ // ������ �ƹ��͵� ���� ��
			p = p->right;
			delete tmpP;
		}
		else if (p->right == 0) 
		{ // ������ �ƹ��͵� ���� ��
			p = p->left;
			delete tmpP;
		}
		else 
		{ // ���ʿ� �� ���� ���� ��
			// �����ϰ��� �ϴ� ������ ū ���� �θ��� Ʈ������ ���� ���� �� ���ϱ�.
			tmp = return_min(p->right); 
			p->key = tmp; // �����ϰ��� �ϴ� ����� �����͸� ������ ã�� ������ ��ü.
			remove_sub(p->right, tmp); // ��� ã�� ���� ���� ��ġ�� ����.
		}
	}





	// ���� ���
	void show_sub(node* p, int level) 
	{
		
		if (p != 0)
		{ // �Ű������� ���� �����Ͱ� �ΰ��� �ƴ� ���
			show_sub(p->right, level + 1); // ���� �ڽ� ����
			for (int i = 0; i < level; i++)
			{ // ������ ���� ��ŭ tab 
				cout << '\t';
			}
			cout << " " << p->key;
			if ((p->left != 0) && (p->right != 0))
			{
				cout << "<";
			}
			else if (p->right != 0)
			{
				cout << "/";
			}
			else if (p->left != 0)
			{
				cout << "\\";
			}
			cout << endl;
			show_sub(p->left, level + 1); // ���� �ڽ� ����
		}
	}

	void show_structure()
	{
		if (head == 0) 
		{
			cout << "empty" << endl;
		}
		else 
		{
			cout << endl;
			show_sub(head, 1);
			cout << endl;
		}
	}

	// Ʈ�� �ʱ�ȭ
	void clear() 
	{
		clear_tree(head);
		head = 0;
	}

	// Ʈ�� �ʱ�ȭ ����Լ�
	int clear_tree(node* a) 
	{
		if (a == 0) 
		{
			return 0;
		}
		else 
		{
			clear_tree(a->left);
			clear_tree(a->right);
			delete a;
			return 1;
		}
	}

private:
	node* head;
};

int main() 
{
	BSTree test;
	node* t_node;
	int input;
	char cmd;

	cout << endl << "Commands:" << endl;
	cout << "  +key : Insert (or update) element" << endl;
	cout << "  ?key : Retrieve element" << endl;
	cout << "  -key : Remove element" << endl;
	cout << "  ckey : clear tree" << endl;

	do 
	{
		cout << endl;
		test.show_structure();
		cout << endl << "command : ";
		cin >> cmd;
		if (cmd == '+' || cmd == '?' ||
			cmd == '-' || cmd == '<')
			cin >> input;
		switch (cmd) 
		{
			case '+' :
				cout << "insert : key = " << input << endl;
				test.Insert_Node(input);
				break;
			case '-' :
				cout << "remove : key = " << input << endl;
				test.remove(input);
				break;
			case '?' :
				cout << "search" << input << endl;
				t_node = test.Search_Node(input);
				if (t_node != 0) 
				{
					t_node->show_child();
				}
				break;
			case 'C' : case 'c' :
				test.clear();
				cout << "tree cleared!" << endl;
				break;
			case 'Q' : case 'q' :
				break;
			default:
				cout << "invalid command" << endl;
	
		}

	} while ((cmd != 'Q') && (cmd != 'q'));

}
