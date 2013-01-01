/////////////////////////////////
//
// MyArray.h
//
/////////////////////////////////
#include <iostream.h>
#include <fstream.h>

struct  Item{
	int  AttribCode;       //区域属性代码
	char AttribName[20];   //区域属性名称
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
	int	   m_count; 		//存储该链表中节点个数
	CMyItem*   m_curposi;	//当前指针
	CMyItem*   m_preposi;	//前驱指针
	bool	Next();			// 使m_curposi指向下一个节点位置
	void 	Add(Item item);	//在链表末尾加一节点
	
	void	read(ifstream&	in);
	void 	write(ofstream&	out); //CItemList对象数据存储、读取函数
	CItemList();
	~CItemList();
};

