/*Написать программу, которая использует класс string
для анализа строки, содержащей математическое выражение, например, вида  (2+3)*4+1. Строка вводится с клавиатуры Программа выдает результат
вычисления выражения.*/
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;
struct tree
{
	char sim;
	int value;
	tree* left;
	tree* right;
};
class Tree
{
	tree* root;
public:
	Tree()
	{
		root = NULL;
	};
	~Tree()
	{
		deleteTree(root);
	}
	void pushTree(char s, int num,tree*& root);
	void showTree(tree* root);
	void deleteTree(tree*& root);
	int search(char s, tree* root);
	tree*& getRoot();
};
int Tree::search(char s, tree* root)
{
	if (root->sim==s)
	{
		return root->value;
	}
	if (root->sim>s)
	{
		if (root->left == NULL)
			cout << " Elements not found \n";
		else
			search(s,root->left);
	}
	if (root->sim<s)
	{
		if (root->right == NULL)
			cout << " Elements not found \n";
		else
			search(s,root->right);
	}
}
tree*& Tree::getRoot()
{
	return root;
}
void Tree::pushTree(char s, int num,tree*& root)
{
	if (root == NULL)
	{
		root = new tree;
		root->sim = s;
		root->value = num;
		root->left = root->right = NULL;
	}
	else
	{
		if (root->sim > s)
			pushTree(s, num, root->left);
		if (root->sim < s)
			pushTree(s, num, root->right);
	}
}
void Tree::showTree(tree* root)
{
	if (root != NULL)
	{
		showTree(root->left);
		cout << root->sim << " " << root->value << endl;
		showTree(root->right);
	}
}
void Tree::deleteTree(tree*& root)
{
	if (!root)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
		root = NULL;
	}
}
struct stek
{
	char elem;
	int prior;
	stek* next;
};
struct stekInt
{
	int elem;
	stekInt* next;
};
class StekInt
{
	stekInt* head;
public:
	StekInt()
	{
		head = NULL;
	}
	~StekInt()
	{
		deleteStekInt();
	}
	void pop(int n);
	int push();
	void deleteStekInt();
	void show();
};
void StekInt::pop(int n)
{
	stekInt* tmp = new stekInt;
	tmp->elem = n;
	tmp->next = head;
	head = tmp;
}
int StekInt::push()
{
	if (!head)return 99999;
	int data = head->elem;
	stekInt* tmp = head;
	head = head->next;
	delete tmp;
	return data;
}
void StekInt::deleteStekInt()
{
	stekInt* tmp = NULL;
	while (head)
	{
		tmp = head->next;
		delete head;
		head = tmp;
	}
	delete tmp;
}
void StekInt::show()
{
	stekInt* tmp = head;
	cout << " Стек : \n";
	while (tmp)
	{
		cout << tmp->elem << " ";
		tmp = tmp->next;
	}
	cout << endl;
	delete tmp;
}
class Stek
{
protected:
	stek * head;
public:
	Stek()
	{
		head = NULL;
	}
	~Stek()
	{
		deleteStek();
	}
	bool empty();
	void pop(char s);
	char push();
	void deleteStek();
	void show();
	stek* getHead();
	void stekOb(string& str, int prior);
	void brackets(string& str);
	char putElem();
};
char Stek::putElem()
{
	return head->elem;
}
stek* Stek::getHead()
{
	return head;
}
void Stek::brackets(string& str)
{
	stek* tmp = NULL;
	while (head)
	{
		if (head->elem == '(')
		{
			push();
			break;
		}
		else
		{
			tmp = head->next;
			str += push();
			head = tmp;
		}
	}
	tmp = NULL;
	delete tmp;
}
void Stek::stekOb(string& str, int prior)
{
	stek* tmp = NULL;
	while (head)
	{
		if (head->prior >= prior)
		{
			tmp = head->next;
			str += push();
			head = tmp;
		}
		else
			break;
	}
	tmp = NULL;
	delete tmp;
}
void Stek::show()
{
	stek* tmp = head;
	cout << " Стек : \n";
	while (tmp)
	{
		cout << tmp->elem << " ";
		tmp = tmp->next;
	}
	cout << endl;
	delete tmp;
}
void Stek::pop(char s)
{
	stek* tmp = new stek;
	tmp->elem = s;
	if (s == '(' || s == ')')
		tmp->prior = 1;
	if (s == '+' || s == '-')
		tmp->prior = 2;
	if (s == '*' || s == '/')
		tmp->prior = 3;
	tmp->next = head;
	head = tmp;
}
char Stek::push()
{
	if (!head)return 'f';
	stek* tmp = head;
	char data = head->elem;
	if (!head->next)
	{
		head = NULL;
		tmp = NULL;
		delete tmp;
		return data;
	}
	else
	{
		head = head->next;
		tmp = NULL;
		delete tmp;
		return data;
	}
}
void Stek::deleteStek()
{
	stek* tmp = NULL;
	try
	{
		if (head == NULL)
			throw (char*)"NULL\n";
		else
		{
			if (head->next == NULL)
			{
				return;
			}
			else
			{
				while (head)
				{
					tmp = head->next;
					delete head;
					head = tmp;
				}
				delete tmp;
				head = NULL;
				return;
			}
		}

	}
	catch (const char* s)
	{
		delete tmp;
		head = NULL;
		return;
	}

}
bool Stek::empty()
{
	if (head)
		return true;
	else
		return false;
}
class reversePolishEntry
{
	string stroka;
	Stek st;
	string strn;
public:
	reversePolishEntry(string stroka) :stroka(stroka) {};
	~reversePolishEntry()
	{
		st.deleteStek();
	}
	bool analysString(string str);
	void analys(string& str);
	string& getStr() { return strn; }
	int CalcInt(string str, Tree ob);
	int sum(int a, int b, char s);
};
bool reversePolishEntry::analysString(string str)
{
	Stek tmp;
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (str.at(i) == '(')
			tmp.pop(str.at(i));
		if (str.at(i) == ')')
		{
			if (tmp.putElem() == '(')
			{
				tmp.push();
				continue;
			}
		}
	}
	if (tmp.getHead())
		return false;
	else
		return true;
}
int reversePolishEntry::sum(int a, int b, char s)
{
	switch (s)
	{
	case '*':
		return a * b;
	case '/':
		if (b == 0)
		{
			cout << " На ноль делить нельзя \n";
			system("pause");
			exit(0);
		}
		else
			return a / b;
	case '+':
		return a + b;
	case '-':
		return a - b;
	default:
		cout << " Error !!!\n";
		return -500;
	}
}
int reversePolishEntry::CalcInt(string str,Tree ob)
{
	int len = str.length();
	StekInt st;
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (str.at(i) == '*' || str.at(i) == '/' || str.at(i) == '+' || str.at(i) == '-')
		{
			int n2;
			int n1;
			n2 = st.push();
			n1 = st.push();
			st.pop(sum(n1,n2, str.at(i)));
			continue;
		}
		else
		{
			st.pop(ob.search(str.at(i), ob.getRoot()));
		}
	}
	return st.push();
}
void reversePolishEntry::analys(string& str)
{
	int prior = 0;
	string temp;
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (str.at(i) >= 'a')
		{
			temp += str.at(i);
		}
		if (str.at(i) == '*' || str.at(i) == '/')
		{
			int prior = 3;
			st.stekOb(temp, prior);
			st.pop(str.at(i));
		}
		if (str.at(i) == '+' || str.at(i) == '-')
		{
			int prior = 2;
			st.stekOb(temp, prior);
			st.pop(str.at(i));
		}
		if (str.at(i) == '(')
		{
			st.pop(str.at(i));
		}
		if (str.at(i) == ')')
		{
			st.brackets(temp);
		}
	}
	if (st.empty())
	{
		stek* tmp = st.getHead();
		while (tmp)
		{

			temp += tmp->elem;
			tmp = tmp->next;
		}
		delete tmp;
		st.deleteStek();
	}
	strn = temp;
}
char* strg(string str)
{
	char* string;
	int len = str.length();
	string = new char[len];
	int i;
	for (i = 0; i < len; i++)
	{
		string[i] = str.at(i);
	}
	string[i] = 0;
	return string;
}
string& changeStr(string& str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (str.at(i) == '/' || str.at(i) == '*' || str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '(' || str.at(i) == ')')
			str.at(i) = ' ';
			

	}
	return str;
}
string& changeStr1(string& str)
{
	
	return str;
}
void udal(string& str)
{
	int i;
	char name[30];
	string reduxName;
	int strLen = str.length();
	for (i=0;i < strLen; i++)
	{
		name[i] = str.at(i);
	}
	name[i] = 0;
	int len = strlen(name);
	for (int i = 0; i < len; i++)
	{
		if (name[i] >= '0'&&name[i] <= '9')
			name[i] = '!';
	}
	for (int i = 0; i<len; i++)
	{
		if (name[i] == name[i + 1])
		{
			for (int j = i; j<len; j++)
			{
				name[j] = name[j + 1];
			}
			len--;
		}
	}
	for (int i = 0; i < len; i++)
	{
		reduxName += name[i];
	}
	int j = 0;
	int sLen = reduxName.length();
	for (int i = 0; i < sLen; i++)
	{
		if (reduxName.at(i) == '!')
		{
			reduxName.at(i) = 'a' + j;
			j++;
		}
	}
	cout << " "<<reduxName << endl;
	str=reduxName;
}
int main()
{
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree ob1;
	int len = 0;
	int i = 0;
	string polish;
	string name;
	char buff[30];
	char* word, *next;
	cout << " Введите строку : ";
	getline(cin, polish);
	name = polish;
	polish = changeStr(polish);
	strcpy(buff, strg(polish));
	word = strtok_s(buff, " ", &next);
	while (word)
	{
		ob1.pushTree('a' + i, atoi(word), ob1.getRoot());
		i++;
		word = strtok_s(NULL, " ", &next);
	}
	reversePolishEntry ob(name);
	if (ob.analysString(name))
	{

	}
	else
	{
		cout << " Строка составлена не верно \n";
		exit(0);
	}
	udal(name);
	ob.analys(name);
	string str = ob.getStr();
	cout << " Обратная польская запись : " << str << endl;
	cout << " Результат : " << ob.CalcInt(str,ob1) << endl;
	word = next = NULL;
	delete word;
	delete next;
	system("pause");
}
