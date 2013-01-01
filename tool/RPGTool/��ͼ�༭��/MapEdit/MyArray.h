/////////////////////////////////
//
// MyArray.h
//
/////////////////////////////////
#include <iostream.h>
#include <fstream.h>

struct  Item{
	int  AttribCode;       //�������Դ���
	char AttribName[20];   //������������
	int  Rvalue;
	int  Gvalue;
	int  Bvalue;
};

class CMyItem
{
public:
	
	Item    myitem;
	bool	IsItem(Item item);
	int    CheckItem(Item item);
	
	CMyItem*	lpNext;
	CMyItem(Item item);
	CMyItem();	
	void	read(ifstream&	in);
	void 	write(ofstream&	out);		
};// 

class	CItemList
{

public:
	void	ClearList();
	bool	Delcur();
	void	Changecur(Item item);
	bool	FindItem(Item item);
	bool    CheckItem(Item item,int tp);
	COLORREF     SearchID(int id);
	bool	SearchItem(char name[20]);  
	CMyItem*   m_head;
	int	   m_count; 		//�洢�������нڵ����
	CMyItem*   m_curposi;	//��ǰָ��
	CMyItem*   m_preposi;	//ǰ��ָ��
	bool	Next();			// ʹm_curposiָ����һ���ڵ�λ��
	void 	Add(Item item);	//������ĩβ��һ�ڵ�
	
	void	read(ifstream&	in);
	void 	write(ofstream&	out); //CItemList�������ݴ洢����ȡ����
	CItemList();
	~CItemList();
};

