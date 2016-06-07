#include "iostream"
#include <stack>
using namespace std;

// ���������ʾ�� �������ֵܱ�ʾ��
typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *lChild, *rChild;
}BiTreeNode, *BiThrTree;

// ������� �ݹ�ʵ��
void InOrder(BiTreeNode* &t)
{
	if(t == NULL)
	{
		return;
	}


	printf("%d->", t->data);
	InOrder(t->lChild);
	InOrder(t->rChild);

	delete t;
	t = NULL;
}

// �ݹ�ʵ��
int CreateBiTree(BiThrTree &root, int *preOrder, int *inOrder, int len)
{
   if (len<=0)
   {
		root = NULL;
		return 1;
   }
   else
   {
		root = new BiTreeNode;
		root->data = *preOrder;
		int i;
		for ( i=0; i<len; i++) if (inOrder[i]==*preOrder) break;
		// ������ָ�� ���������ĵ�ַ ���������������׵�ַ ����������
		CreateBiTree(root->lChild, preOrder+1, inOrder, i);
		// ������ָ�� ���������ĵ�ַ ���������������׵�ַ ����������
		CreateBiTree(root->rChild, preOrder+i+1, inOrder+i+1, len-(i+1));
   }
   return 1;
}

// �ǵݹ�ʵ��
int _CreateBiTree(BiThrTree &_root, int *preOrder, int *inOrder, int len)
{

	stack<BiThrTree> s;
	stack<int> slen;
	stack<int *> spre;
	stack<int *> sin;
	BiTreeNode* root;

	_root = new BiTreeNode;
	_root->data = *preOrder;

	slen.push(len);
	s.push(_root);
	spre.push(preOrder);
	sin.push(inOrder);


	while(!s.empty())
	{
		len = slen.top();
		slen.pop();

		root = s.top();
		s.pop();
			
		preOrder = spre.top();
		spre.pop();

		inOrder = sin.top();
		sin.pop();

			
		int i;
		for ( i=0; i<len; i++) if (inOrder[i]==*preOrder) break;
		if(i > 0)
		{
			root->lChild = new BiTreeNode;
			root->lChild->data = *(preOrder+1);
			slen.push(i);
			s.push(root->lChild);
			spre.push(preOrder+1);
			sin.push(inOrder);
		}
		else
		{
			root->lChild  = NULL;
		}
			

		if( ( len-(i+1) ) > 0)
		{
			root->rChild = new BiTreeNode;
			root->rChild->data = *(preOrder+i+1);
			slen.push(len-(i+1));
			s.push(root->rChild);
			spre.push(preOrder+i+1);
			sin.push(inOrder+i+1);
		}
		else
		{
			root->rChild  = NULL;
		}
			
		
   }
   return 1;
}

void main()
{
	const int K = 10; 
    int preOrder[K] = { 4,3,1,8,5,10,2,7,13,6 };  
    int inOrder[K] = { 1,8,3,10,5,4,7,13,2,6 };  


	BiTreeNode* root;
	CreateBiTree(root, preOrder, inOrder, K);
	InOrder(root);

	cout << endl;

	BiTreeNode* _root;
	_CreateBiTree(_root, preOrder, inOrder, K);
	InOrder(_root);

	
	system("pause");
	return;
}