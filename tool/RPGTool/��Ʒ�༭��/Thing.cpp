#include	"stdafx.h"
#include	"Thing.h"

void	CThing::read(ifstream& in){
	in.read((char*)&m_name,20*sizeof(char));
	in.read((char*)&m_active,sizeof(bool));
	in.read((char*)&m_function,sizeof(int));
	in.read((char*)&m_picid,sizeof(int));
	in.read((char*)&m_visible,sizeof(bool));

}

void	CThing::write(ofstream& out){
	out.write((char*)&m_name,20*sizeof(char));
	out.write((char*)&m_active,sizeof(bool));
	out.write((char*)&m_function,sizeof(int));
	out.write((char*)&m_picid,sizeof(int));
	out.write((char*)&m_visible,sizeof(bool));
}

void	CThingList::Add(CThing &th){
	CThing*	lpold;
	lpold=m_head;
	m_head=new CThing;
	m_head->lpNext=lpold;
	m_head->m_active=th.m_active;
	m_head->m_visible=th.m_visible;
	m_head->m_function=th.m_function;
	m_head->m_picid=th.m_picid;
	strcpy(m_head->m_name,th.m_name);
	m_count++;
}
bool	CThingList::Find(int id){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi->m_ID==id)
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_curposi!=NULL){
		if(m_curposi->m_ID==id)
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
void CThingList::Delcur(){
	if(m_curposi==m_head){
		m_head=m_head->lpNext;
		delete m_curposi;
		m_curposi=m_head;
		m_count--;
		return;
	}
	m_preposi->lpNext=m_curposi->lpNext;
	delete	m_curposi;
	m_curposi=m_head;
	m_count--;
}

CThingList::CThingList(){
	m_head=m_curposi=NULL;
	m_count=0;
}
CThingList::~CThingList(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		delete m_curposi;
	}
}
bool	CThingList::Next(){
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}
void	CThingList::read(ifstream& in){
	in.read((char*)&m_count,sizeof(int));
	CThing*	lpold;
    for(int i=0;i<m_count;i++)
        {
		lpold=m_head;
		m_head=new	CThing;
		m_head->lpNext=lpold;
		}
	m_curposi=m_head;
	i=0;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		m_curposi->m_ID=i;
		i++;
		Next();
	}
}
void	CThingList::write(ofstream& out){
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}
void	CNpc::read(ifstream& in){
		in.read((char*)&m_active,sizeof(bool));
		in.read((char*)&m_attack,sizeof(int));
		in.read((char*)&m_def,sizeof(int));
		in.read((char*)&m_exp,sizeof(int));
		in.read((char*)&m_function,sizeof(int));
		in.read((char*)&m_level,sizeof(int));
		in.read((char*)&m_life,sizeof(int));
		in.read((char*)&m_name,20*sizeof(char));
		in.read((char*)&m_picid,10*sizeof(int));
		in.read((char*)&m_radius,sizeof(float));
		in.read((char*)&m_sight,sizeof(float));
		in.read((char*)&m_speed,sizeof(int));
		in.read((char*)&m_visible,sizeof(bool));
}

void	CNpc::write(ofstream& out){
		out.write((char*)&m_active,sizeof(bool));
		out.write((char*)&m_attack,sizeof(int));
		out.write((char*)&m_def,sizeof(int));
		out.write((char*)&m_exp,sizeof(int));
		out.write((char*)&m_function,sizeof(int));
		out.write((char*)&m_level,sizeof(int));
		out.write((char*)&m_life,sizeof(int));
		out.write((char*)&m_name,20*sizeof(char));
		out.write((char*)&m_picid,10*sizeof(int));
		out.write((char*)&m_radius,sizeof(float));
		out.write((char*)&m_sight,sizeof(float));
		out.write((char*)&m_speed,sizeof(int));
		out.write((char*)&m_visible,sizeof(bool));
}
void	CNpcList::Add(CNpc &th){
	CNpc*	lpold;
	lpold=m_head;
	m_head=new CNpc;
	m_head->lpNext=lpold;
	m_head->m_active=th.m_active;
	m_head->m_visible=th.m_visible;
	m_head->m_function=th.m_function;
	for(int i=0;i<10;i++)
		m_head->m_picid[i]=th.m_picid[i];
	m_head->m_attack=th.m_attack;
	m_head->m_def=th.m_def;
	m_head->m_exp=th.m_exp;
	m_head->m_level=th.m_level;
	m_head->m_life=th.m_life;
	m_head->m_speed=th.m_speed;
	strcpy(m_head->m_name,th.m_name);
	m_head->m_radius=th.m_radius;
	m_head->m_sight=th.m_sight;

	m_count++;
}
CNpcList::CNpcList(){
	m_head=m_curposi=NULL;
	m_count=0;
}
CNpcList::~CNpcList(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		delete m_curposi;
	}
}
bool	CNpcList::Find(int id){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_preposi->m_ID==id)
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_preposi!=NULL){
		if(m_preposi->m_ID==id)
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
void CNpcList::Delcur(){
	if(m_curposi==m_head){
		m_head=m_head->lpNext;
		delete m_curposi;
		m_curposi=m_head;
		return;
	}
	m_preposi->lpNext=m_curposi->lpNext;
	delete	m_curposi;
	m_curposi=m_head;
	m_count--;
}
bool	CNpcList::Next(){
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}
void	CNpcList::read(ifstream& in){
	in.read((char*)&m_count,sizeof(int));
	CNpc*	lpold;
    for(int i=0;i<m_count;i++)
        {
		lpold=m_head;
		m_head=new	CNpc;
		m_head->lpNext=lpold;
		}
	m_curposi=m_head;
	i=0;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		m_curposi->m_ID=i;
		i++;
		Next();
	}
}
void	CNpcList::write(ofstream& out){
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}
