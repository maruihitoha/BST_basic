#include <iostream>
//2015112147 김도훈
using namespace std;

// node 클래스
class node 
{
public:
	node(int key, node* left, node* right) //생성자.
		:key(key), left(left), right(right){}
	void show_child() 
	{ //노드의 자식을 보여줌
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
	int key;	// 데이터
	node* left;
	node* right;
	friend class BSTree;
};

class BSTree 
{// 이진탐색트리를 관리하는 클래스
public:

	BSTree() 
	{ // 생성자. 헤드를 NULL로 초기화		
		head = 0;
	}

	~BSTree() 
	{ // 클래스 소멸시 트리 내부 클리어 실행
		clear();
	}

	node* Search_Node(int key)
	{ // 찾고자 하는 값이 존재하는지
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

	// 삽입 함수
	void Insert_Node(int key) 
	{
		Insert_sub(head, key);
	}

	// 삽입함수의 재귀함수 부분. 
	void Insert_sub(node*& p, int key) 
	{
		if (p == 0) 
		{ // 해당 파트가 비어있을 시 새로운 노드 생성
			p = new node(key, 0, 0);
		}
		else if (p->key < key) 
		{ // 현재 위치의 데이터보다 입력받은 데이터 값이 클시 우측으로 이동
			Insert_sub(p->right, key);
		}
		else
		{// 현재 위치의 데이터보다 입력받은 데이터 값이 작을시 좌측으로 이동
			Insert_sub(p->left, key);
		}
	}
	
	// 제일 작은 값을 찾을 때 까지 왼쪽으로 감
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
		{ // 삭제하고자 하는 값이 현재 위치보다 클 시 우측이동
			remove_sub(p->right, key);
		}
		else if (p->key > key) 
		{// 삭제하고자 하는 값이 현재 위치보다 작을 시 좌측이동
			remove_sub(p->left, key);
		}
		else 
		{ // 둘 다 아니면 같은것이니깐 삭제 실행
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

	// 노드 삭제 실행 함수. 
	void delete_node(node*& p) 
	{
		node* tmpP;
		int tmp;
		tmpP = p;

		if (p->left == 0) 
		{ // 좌측에 아무것도 없을 시
			p = p->right;
			delete tmpP;
		}
		else if (p->right == 0) 
		{ // 우측에 아무것도 없을 시
			p = p->left;
			delete tmpP;
		}
		else 
		{ // 양쪽에 다 값이 있을 시
			// 삭제하고자 하는 값보다 큰 값이 부모인 트리에서 가장 작은 값 구하기.
			tmp = return_min(p->right); 
			p->key = tmp; // 삭제하고자 하는 노드의 데이터를 위에서 찾은 값으로 교체.
			remove_sub(p->right, tmp); // 방금 찾은 값의 원래 위치를 삭제.
		}
	}





	// 구조 출력
	void show_sub(node* p, int level) 
	{
		
		if (p != 0)
		{ // 매개변수로 받은 포인터가 널값이 아닐 경우
			show_sub(p->right, level + 1); // 우측 자식 실행
			for (int i = 0; i < level; i++)
			{ // 현재의 레벨 만큼 tab 
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
			show_sub(p->left, level + 1); // 좌측 자식 실행
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

	// 트리 초기화
	void clear() 
	{
		clear_tree(head);
		head = 0;
	}

	// 트리 초기화 재귀함수
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
