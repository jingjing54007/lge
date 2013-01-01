//////////////////////////////////
//
// MyArray.cpp
//
//////////////////////////////////

#include "stdafx.h"
#include "MyArray.h"
#include "MapEdit.h"


CMyItem::CMyItem(Item item)
{
	myitem.AttribCode=item.AttribCode;
	strcpy(myitem.AttribName,item.AttribName);
	myitem.Bvalue=item.Bvalue;
	myitem.Gvalue=item.Gvalue;
	myitem.Rvalue=item.Rvalue;
}

CMyItem::CMyItem()
{
	
}

bool  CMyItem::IsItem(Item item)
{
	if(myitem.AttribCode==item.AttribCode &&
	   strcmp(myitem.AttribName,item.AttribName)==0 &&
	   myitem.Bvalue==item.Bvalue &&
	   myitem.Gvalue==item.Gvalue &&
	   myitem.Rvalue==item.Rvalue)
	   	return true;
	else
		return false;
}
	
int  CMyItem::CheckItem(Item item)   //检查有否相同，返回代码 
{
	if(myitem.AttribCode==item.AttribCode)
		return 2;
	if(strcmp(myitem.AttribName,item.AttribName)==0)
		return 1;
	if((myitem.Rvalue==item.Rvalue) &&
	   (myitem.Gvalue==item.Gvalue) &&
	   (myitem.Bvalue==item.Bvalue))
	   	return 3;
	if((myitem.AttribCode==item.AttribCode) &&
	   (strcmp(myitem.AttribName,item.AttribName)==0) &&
	   ((myitem.Rvalue==item.Rvalue) &&
	   (myitem.Gvalue==item.Gvalue) &&
	   (myitem.Bvalue==item.Bvalue)))
	   return 4;

	else
		return -1;

}

void  CMyItem::read(ifstream& in)
{
	in.read((char*)&myitem,sizeof(Item));
}


void  CMyItem::write(ofstream& out)
{
	out.write((char*)&myitem,sizeof(Item));
}

CItemList::CItemList()
{
	m_count=0;
	m_head=m_curposi=m_preposi=NULL;
}

CItemList::~CItemList()
{
	while(m_head!=NULL)
	{
		m_curposi=m_head;
		m_head=m_head->lpNext;
		delete	m_curposi;
	}
}


void	CItemList::Add(Item item)
{
	CMyItem* temp=new CMyItem(item);
	
	if(m_curposi==NULL && m_curposi==m_head)
	{
		m_head=temp;
		m_head->lpNext=NULL;
		m_curposi=m_preposi=m_head;
		m_count++;
	}
	else
	{
		m_curposi=m_head;
		while(m_curposi->lpNext!=NULL)
		{
			m_preposi=m_curposi;
			m_curposi=m_curposi->lpNext;
		}
		m_curposi->lpNext=temp;
		temp->lpNext=NULL;
		m_preposi=m_curposi;
		m_curposi=temp;
		m_count++;
	}
}

void	CItemList::Changecur(Item item)
{
	m_curposi->myitem.AttribCode=item.AttribCode;
	strcpy(m_curposi->myitem.AttribName,item.AttribName);
	m_curposi->myitem.Bvalue=item.Bvalue;
	m_curposi->myitem.Gvalue=item.Gvalue;
	m_curposi->myitem.Rvalue=item.Rvalue;
}



bool	CItemList::Delcur()
{
	if(m_head==NULL)
		return false;
	CMyItem* temp;
	temp=m_curposi;
	m_curposi=m_curposi->lpNext;
	delete	temp;
	m_count--;
	return true;
}


bool	CItemList::FindItem(Item item)
{
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi==NULL)
	{
		return false;
	}
	else
	{
		while(m_curposi!=NULL)
		{
			if(m_curposi->IsItem(item))
				return true;
			m_preposi=m_curposi;
			m_curposi=m_curposi->lpNext;
		}
	}
	return false;
}


bool    CItemList::CheckItem(Item item,int tp)  //检查有重复 return true
{
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi==NULL)
		return false;
	else	
	{
		while(m_curposi!=NULL)
		{
			if(m_curposi->CheckItem(item)==tp)
				return true;
			m_curposi=m_curposi->lpNext;	
		}
		return false;
	}
}
COLORREF     CItemList::SearchID(int id)
{
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi==NULL)
		return RGB(0,0,0);
	else	
	{
		while(m_curposi!=NULL)
		{
			if(m_curposi->myitem.AttribCode==id)
				return RGB(m_curposi->myitem.Rvalue,m_curposi->myitem.Gvalue,m_curposi->myitem.Bvalue);
			m_curposi=m_curposi->lpNext;	
		}
		return RGB(0,0,0);
	}
}

bool	CItemList::SearchItem(char name[20])
{
	CString temp1,temp2;
	temp1.Format("%s",name);
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi==NULL)
		return false;
	else
	{	
		while(m_curposi!=NULL)
		{
			temp2.Format("%s",m_curposi->myitem.AttribName);
			if(temp1==temp2)
				return true;
			m_curposi=m_curposi->lpNext;
		}
		return false;

	}
}
bool	CItemList::Next()
{
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}

void  CItemList::read(ifstream&	in)
{
	in.read((char*)&m_count,sizeof(int));
	CMyItem*  lpnew;
        for(int i=0;i<m_count;i++)
        {
        	if(m_head==NULL)
        	{
        		m_head=new CMyItem;
        		m_head->read(in);
        		m_head->lpNext=NULL;
        		m_curposi=m_preposi=m_head;
        	}
        	else
        	{
        		lpnew=new CMyItem;
        		lpnew->read(in);
        		lpnew->lpNext=NULL;
        		m_curposi->lpNext=lpnew;
        		m_preposi=m_curposi;
        		m_curposi=lpnew;
        	}
	}
}
void	CItemList::write(ofstream& out)
{
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL)
	{
		m_curposi->write(out);
		Next();
	}
}