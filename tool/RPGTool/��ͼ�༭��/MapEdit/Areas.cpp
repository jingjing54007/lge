//ver 6.3

#include	"stdafx.h"
#include    "areas.h"


void  CMyPoint::read(ifstream&  in)
{
	in.read((char*)&mypt,sizeof(POINT));
}
void  CMyPoint::write(ofstream&  out)
{
	out.write((char*)&mypt,sizeof(POINT));
	
}
CMyPoint::CMyPoint(POINT pt)
{
	mypt=pt;
}
bool   CMyPoint::IsPoint(POINT pt,int off){
	if((pt.x>mypt.x-off)&&
		(pt.x<mypt.x+off)&&
		(pt.y>mypt.y-off)&&
		(pt.y<mypt.y+off))
		return true;	
	return false;
}
CMyPoint::CMyPoint()
{
        
}
void  CPointList::read(ifstream&	in)
{
	in.read((char*)&m_count,sizeof(int));
	CMyPoint*	lpold;
        for(int i=0;i<m_count;i++)
        {
		lpold=m_head;
		m_head=new	CMyPoint;
		m_head->lpNext=lpold;
		}
	m_curposi=m_head;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		Next();
	}
}
void	CPointList::write(ofstream&	out)
{
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}
bool	CPointList::Next()
{
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}

CPointList::CPointList()
{
	m_count=0;
	m_head=m_curposi=NULL;
}
CPointList::~CPointList()
{
	while(m_head!=NULL)
	{
		m_curposi=m_head;
		m_head=m_head->lpNext;
		delete	m_curposi;
	}
}
void	CPointList::Add(POINT pt)
{
	CMyPoint*	lpold;
	lpold=m_head;
	m_head=new CMyPoint(pt);
	m_head->lpNext=lpold;
	m_count++;
}
void	CPointList::Changecur(POINT pt){
	m_curposi->mypt=pt;
}
bool	CPointList::Del()
{
	if(m_head==NULL)
		return false;
	CMyPoint*	tem;
	tem=m_head;
	m_head=m_head->lpNext;
	delete	tem;
	m_count--;
	return true;
}
void	CPointList::Delcur(){
	if(m_curposi==m_head){
		Del();
		return;
	}
	m_preposi->lpNext=m_curposi->lpNext;
	delete	m_curposi;
	m_curposi=m_head;
	m_count--;
	return;
}
void	CPointList::equal(CPointList &plist){
	ClearList();
	m_curposi=m_head=NULL;
	plist.m_curposi=plist.m_head;
	while(plist.m_curposi!=NULL){
		Add(plist.m_curposi->mypt);
		plist.Next();
	}
}
bool	CPointList::FindPoint(POINT pt,int off){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi->IsPoint(pt,off))
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_curposi!=NULL){
		if(m_curposi->IsPoint(pt,off))
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
void	CPointList::ClearList(){
	while(Del()==true)
	{
	}
}
void	CArea::read(ifstream&	in)
{
	in.read((char*)&m_statein,sizeof(int));
	in.read((char*)&m_stateout,sizeof(int));
	
	m_pointlist.read(in);
}
void	CArea::write(ofstream& out)
{
	out.write((char*)&m_statein,sizeof(int));
	out.write((char*)&m_stateout,sizeof(int));
	m_pointlist.write(out);
}

void CAreaList::Add()
{
	CArea*	lpold;
	lpold=m_head;
	m_head=new CArea;
	m_head->lpNext=lpold;
	m_count++;
}
void CAreaList::Clear(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		m_curposi->m_pointlist.ClearList();
		delete m_curposi;
	}
	m_head=m_curposi=NULL;
	m_count=0;
}
void	CAreaList::Changecur(POINT pt){
	m_curposi->m_pointlist.Changecur(pt);
}
bool	CAreaList::FindPoint(POINT pt,int off){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi->m_pointlist.FindPoint(pt,off))
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_curposi!=NULL){
		if(m_curposi->m_pointlist.FindPoint(pt,off))
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
CAreaList::CAreaList()
{
	m_count=0;
	m_head=m_curposi=NULL;
}
CAreaList::~CAreaList()
{
	while(m_head!=NULL)
	{
		m_curposi=m_head;
		m_head=m_head->lpNext;
		delete	m_curposi;
	}
}
bool CAreaList::Del()
{
	if(m_head==NULL)
		return false;
	CArea*	tem;
	tem=m_head;
	m_head=m_head->lpNext;
	tem->m_pointlist.ClearList();
	delete	tem;
	m_count--;
	return true;
}
void CAreaList::Delcur(){
	if(m_curposi==m_head){
		Del();
		return;
	}
	m_preposi->lpNext=m_curposi->lpNext;
	m_curposi->m_pointlist.ClearList();
	delete	m_curposi;
	m_curposi=m_head;
	m_count--;
}

bool CAreaList::Next()
{
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}
void CAreaList::read(ifstream& in)
{
	in.read((char*)&m_count,sizeof(int));
	CArea*	lpold;
	for(int i=0;i<m_count;i++){
		lpold=m_head;
		m_head=new	CArea;
		m_head->lpNext=lpold;
	}
	m_curposi=m_head;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		Next();
	}
}
void CAreaList::write(ofstream&	out)
{
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}

