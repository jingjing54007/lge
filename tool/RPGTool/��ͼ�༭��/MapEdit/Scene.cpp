//ver 6.3
/////////////
#include "stdafx.h"
#include "scene.h"
#include "thing.h"
/////////////

void	copyRECT(RECT& r1,RECT& r2){
	r1.left=r2.left;
	r1.right=r2.right;
	r1.top=r2.top;
	r1.bottom=r2.bottom;
}
/////////////////
void	CSceneThing::read(ifstream &in){
	in.read((char*)&m_id,sizeof(int));
	in.read((char*)&m_picarea,sizeof(RECT));
	m_cover.read(in);
}
void	CSceneThing::write(ofstream &out){
	out.write((char*)&m_id,sizeof(int));
	out.write((char*)&m_picarea,sizeof(RECT));
	m_cover.write(out);
}
void CSceneThingList::Add(CSceneThing &th){
	CSceneThing*	lpold;
	lpold=m_head;
	m_head=new CSceneThing;
	m_head->lpNext=lpold;
	m_head->m_id=th.m_id;
	copyRECT(m_head->m_picarea,th.m_picarea);
	m_head->m_cover.equal(th.m_cover);
	m_count++;
}
void CSceneThingList::Clear(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		m_curposi->m_cover.ClearList();
		delete m_curposi;
	}
	m_head=m_curposi=NULL;
	m_count=0;
}
void CSceneThingList::Delcur(){
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
bool CSceneThingList::Find(int id){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi->m_id==id)
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_curposi!=NULL){
		if(m_curposi->m_id==id)
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
bool CSceneThingList::Next(){
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}
void CSceneThingList::read(ifstream& in){
	in.read((char*)&m_count,sizeof(int));
	CSceneThing*	lpold;
    for(int i=0;i<m_count;i++)
        {
		lpold=m_head;
		m_head=new	CSceneThing;
		m_head->lpNext=lpold;
		}
	m_curposi=m_head;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		Next();
	}
}
void CSceneThingList::write(ofstream& out){
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}
CSceneThingList::CSceneThingList(){
	m_head=m_curposi=NULL;
	m_count=0;
}
CSceneThingList::~CSceneThingList(){
	Clear();
}
////////////////////class CSceneNpcList
void	CSceneNpc::read(ifstream &in){
	in.read((char*)&m_id,sizeof(int));
	in.read((char*)&m_center,sizeof(POINT));
	in.read((char*)&m_conposi,sizeof(POINT));
	in.read((char*)&m_facehigh,sizeof(int));
	in.read((char*)&m_facewidth,sizeof(int));
	in.read((char*)&m_autoact,10*sizeof(Cautomation));
}
void	CSceneNpc::write(ofstream &out){
	out.write((char*)&m_id,sizeof(int));
	out.write((char*)&m_center,sizeof(POINT));
	out.write((char*)&m_conposi,sizeof(POINT));
	out.write((char*)&m_facehigh,sizeof(int));
	out.write((char*)&m_facewidth,sizeof(int));
	out.write((char*)&m_autoact,10*sizeof(Cautomation));
}
void CSceneNpc::NextFace(){
	if(++m_frameid>7)  m_frameid=0;  
	BltRc.left=m_frameid*m_facewidth;
	BltRc.right=BltRc.left+m_facewidth;
	BltRc.top=m_direction*m_facehigh;
	BltRc.bottom=BltRc.top+m_facehigh;
}
void CSceneNpc::NextPosi(int speed){
	
switch(m_direction)
	{
	case 0:	m_center.x-=speed;
			break;
	case 1: m_center.x-=speed;
		    m_center.y-=speed;	
			break;
	case 2: m_center.y-=speed;
			break;
	case 3:	m_center.x+=speed;
			m_center.y-=speed;
			break;
	case 4: m_center.x+=speed;
			break;
	case 5:	m_center.x+=speed;
			m_center.y+=speed;
			break;
	case 6:	m_center.y+=speed;
			break;
	case 7:	m_center.x-=speed;
			m_center.y+=speed;
			break;
	}
}
void CSceneNpc::TimeWork(){

	NextFace();
	NextPosi(8);
}
void CSceneNpc::InitData(){
	BltRc.left=0;		BltRc.top=0;
	BltRc.bottom=m_facehigh;	BltRc.right=m_facewidth;
	m_direction=RIGHT;
	m_state=STAND;
	m_frameid=0;
}
void CSceneNpcList::Add(CSceneNpc &th){
	CSceneNpc*	lpold;
	lpold=m_head;
	m_head=new CSceneNpc;
	m_head->lpNext=lpold;
	m_head->m_id=th.m_id;
	m_head->m_conposi=th.m_conposi;
	m_head->m_facehigh=th.m_facehigh;
	m_head->m_facewidth=th.m_facewidth;
	m_head->m_center=th.m_center;
	for(int i=0;i<10;i++){
		m_head->m_autoact[i].m_pt=th.m_autoact[i].m_pt;
		m_head->m_autoact[i].m_state=th.m_autoact[i].m_state;
		m_head->m_autoact[i].m_wait=th.m_autoact[i].m_wait;
	}
	m_count++;
}
void CSceneNpcList::Clear(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		delete m_curposi;
	}
	m_head=m_curposi=NULL;
	m_count=0;
}
void CSceneNpcList::Delcur(){
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
bool CSceneNpcList::Find(int id){
	m_preposi=m_head;
	m_curposi=m_head;
	if(m_curposi->m_id==id)
		return true;
	m_curposi=m_curposi->lpNext;
	while(m_curposi!=NULL){
		if(m_curposi->m_id==id)
			return true;
		m_preposi=m_curposi;
		m_curposi=m_curposi->lpNext;
	}
	return false;
}
bool CSceneNpcList::Next(){
	if(m_curposi==NULL)
		return false;
	m_curposi=m_curposi->lpNext;
	return true;
}
void CSceneNpcList::read(ifstream& in){
	in.read((char*)&m_count,sizeof(int));
	CSceneNpc*	lpold;
    for(int i=0;i<m_count;i++)
        {
		lpold=m_head;
		m_head=new	CSceneNpc;
		m_head->lpNext=lpold;
		}
	m_curposi=m_head;
	while(m_curposi!=NULL)
	{
		m_curposi->read(in);
		Next();
	}
}
void CSceneNpcList::write(ofstream& out){
	out.write((char*)&m_count,sizeof(int));
	m_curposi=m_head;
	while(m_curposi!=NULL){
		m_curposi->write(out);
		Next();
	}
}
CSceneNpcList::CSceneNpcList(){
	m_head=m_curposi=NULL;
	m_count=0;
}
CSceneNpcList::~CSceneNpcList(){
	while(m_head!=NULL){
		m_curposi=m_head;			
		m_head=m_head->lpNext;
		delete m_curposi;
	}
}

//////////////////////////////////////////////////////////////////
/*
	bool inarea;
	CDrawnode temnode;
	m_drawlist.clear();
	m_thinglist.m_curposi=m_thinglist.m_head;
	while(m_thinglist.m_curposi!=NULL){
		temnode.m_id=m_thinglist.m_curposi->m_id;
		temnode.m_type=true;
		m_drawlist.Add(temnode);
		m_thinglist.Next();
	}
	m_npclist.m_curposi=m_npclist.m_head;
	while(m_npclist.m_curposi!=NULL){
		m_drawlist.m_curposi=m_drawlist.m_head;
		inarea=false;
		while(m_drawlist.m_curposi!=NULL&&!inarea){
	

			m_drawlist.Next();
		}

		m_npclist.Next();
	}
*/

void CMyScene::read(ifstream &in){
	Clear();// 清 空
	in.read((char*)&m_position,sizeof(POINT));
	in.read((char*)&m_maxsize,sizeof(float));
	in.read((char*)&m_minsize,sizeof(float));
	in.read((char*)&m_high,sizeof(int));
	in.read((char*)&m_width,sizeof(int));
	in.read((char*)&m_picname,20*sizeof(char));
//	AfxMessageBox("Here 1");
	m_arealist.read(in);
//	AfxMessageBox("Here 2");
	m_thinglist.read(in);
//	AfxMessageBox("Here 3");
	m_npclist.read(in);
//	AfxMessageBox("Here 4");
}
void CMyScene::write(ofstream &out){
	out.write((char*)&m_position,sizeof(POINT));
	out.write((char*)&m_maxsize,sizeof(float));
	out.write((char*)&m_minsize,sizeof(float));
	out.write((char*)&m_high,sizeof(int));
	out.write((char*)&m_width,sizeof(int));
	out.write((char*)&m_picname,20*sizeof(char));
	m_arealist.write(out);
	m_thinglist.write(out);
	m_npclist.write(out);
}
void CMyScene::Clear(){
	m_arealist.Clear();
	m_drawlist.Clear();
	m_npclist.Clear();
	m_thinglist.Clear();
}
void CMyScene::arrange(){
	bool inarea;
	CDrawnode temnode;
	m_drawlist.Clear();
	m_thinglist.m_curposi=m_thinglist.m_head;
	while(m_thinglist.m_curposi!=NULL){
		temnode.m_id=m_thinglist.m_curposi->m_id;
		temnode.m_type=true;
		m_drawlist.Add(temnode);
		m_thinglist.Next();
	}
	m_npclist.m_curposi=m_npclist.m_head;
	while(m_npclist.m_curposi!=NULL){
		m_drawlist.m_curposi=m_drawlist.m_head;
		inarea=false;
		while(m_drawlist.m_curposi!=NULL&&!inarea){
			if(m_drawlist.m_curposi->m_type){
				
			}else{
			
			}
				m_drawlist.Next2();
		}
		if(inarea)
			m_drawlist.Insert(temnode);
		else {
			m_drawlist.m_curposi=new CDrawnode;
			m_drawlist.m_curposi->lpNext=NULL;
			m_drawlist.m_curposi->m_id=m_npclist.m_curposi->m_id;
			m_drawlist.m_curposi->m_type=false;
		}
		m_npclist.Next();
	}
}


bool CMyScene::judgein(CPointList &cover,POINT pt){
	POINT ptout;
	POINT pt1;
	POINT pt2;
	int acrossnum=0;
	ptout.x=0;
	ptout.y=pt.y;
	cover.m_curposi=cover.m_head;
	while(cover.m_curposi!=NULL){
			bool tof=false;
			pt1=cover.m_curposi->mypt;
			pt2=cover.m_curposi->lpNext->mypt;
			if(pt1.x<pt.x&&pt1.y<pt.y){
				if(pt2.y<pt.y)
					tof=true;
			}
			else if(pt1.x>pt.x&&pt1.y<pt.y){
				if(pt2.x<pt.x&&pt2.y>pt.y)
					tof=true;
			}
			else if(pt1.x<pt.x&&pt1.y>pt.y){
				if(pt2.y<pt.y)
					tof=true;
			}
			if(tof){
				if(judgeacross(cover.m_curposi->mypt,
					   cover.m_curposi->lpNext->mypt,
					   pt,
					   ptout))
					acrossnum++;
			}
			cover.Next();
			}		
	if(acrossnum%2)
		return true;
	return false;
}
bool CMyScene::judgeacross(POINT pt1,
						   POINT pt2,
						   POINT pt3,
						   POINT pt4)
{
	float k1,k2,k3,k4,k5;
	k1=(float)(pt2.y-pt1.y)/(float)(pt2.x-pt1.x);
	k2=(float)(pt3.y-pt1.y)/(float)(pt3.x-pt1.x);
	k3=(float)(pt4.y-pt1.y)/(float)(pt4.x-pt1.x);
	if((k2>k1&&k3<k1)||(k3>k1&&k2<k1)){
		k4=(float)(pt3.y-pt2.y)/(float)(pt3.x-pt2.x);
		k5=(float)(pt4.y-pt2.y)/(float)(pt4.x-pt2.x);
		if((k4<k1&&k5>k1)||(k4>k1&&k5<k1))
			return true;
		return false;
	}
	return false;
}
void CMyScene::TimeWork(POINT Player){

}
void CMyScene::InitData(){

}
bool CDrawList::Next2(){
	if(m_curposi==NULL)
		return false;
	m_preposi=m_curposi;
	m_curposi=m_curposi->lpNext;
	return true;
}
void CDrawList::Add(CDrawnode node ){
	CDrawnode* lpold;
	lpold=m_head;
	m_head=new CDrawnode;
	m_head->lpNext=lpold;
	m_head->m_id=node.m_id;
	m_head->m_type=node.m_type;
}
CDrawList::CDrawList(){
	m_head=m_curposi=NULL;
}
void CDrawList::Clear(){
	while(m_head!=NULL){
		m_curposi=m_head;
		m_head=m_head->lpNext;
		delete m_curposi;
	}
	m_curposi=NULL;
	m_head=NULL;
}
CDrawList::~CDrawList(){
	Clear();
}
void CDrawList::Delcur(){
	if(m_curposi==m_head){
		m_head=m_head->lpNext;
		delete m_curposi;
		m_curposi=m_head;
		return;
	}
	m_preposi->lpNext=m_curposi->lpNext;
	delete	m_curposi;
	m_curposi=m_head;
	
}
void CDrawList::Insert(CDrawnode node){
	m_preposi->lpNext=new CDrawnode;
	m_preposi->lpNext->lpNext=m_curposi;
	m_preposi->lpNext->m_id=node.m_id;
	m_preposi->lpNext->m_type=node.m_type;
}

void CSceneLib::read(){
				m_count=0;
				ifstream in("scenelib\\scenelib.txt");
				if(in){			
					while(!in.eof()){
						in.getline(m_name[m_count],20);
						m_count++;
					}
				}
				in.close();
}

//////////////////////////////////////////////////////////////////////
// CMainNpc Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainNpc::CMainNpc()
{

}

CMainNpc::~CMainNpc()
{

}
void CMainNpc::InitData(){
	m_active=true;
	m_visible=true;
	m_picid[0]=0;//	动作图片数组	   		／／ ｆｏｒ  一	
				//stand->0;walk->1;run->2;attact->3;dead->4
	m_radius=40;//	占地半径
	m_sight=300;//	视 野   // 功 能 一：if(m_sight==0)  该ＮＰＣ 不 主 动 靠 近 主 角 ／／ｆｏｒ 四
			// 功 能 二： 视 野 仿 真 寻 道
	m_attack=10;//	攻击
	m_def=1;//	防御
	m_exp=0;//	经验
	m_level=1;//	等级
	m_life=100;//	生命
	m_speed=10;//	速度

	m_center.x=100;//  中 心 点            		／／ｆｏｒ  二 
	m_conposi.y=100;// 中 心 点 在 单 帧 图 片 区 域 中 的 相 对 位 置
	m_facewidth=80;// 物 品 外 观 宽
	m_facehigh=100;	// 物 品 外 观 高

	m_state=0;//	动作状态
	m_direction=4;//	动 作 方 向
	m_frameid=0;//	动 作 帧 指 针


}
void CMainNpc::NextFace(){

}
void CMainNpc::NextPosi(){
}
void CMainNpc::read(ifstream &in){
}
void CMainNpc::write(ofstream &out){
}
void CMainNpc::TimeWork(){
}
int CMainNpc::TraceMsg(UINT message,WPARAM wParam,LPARAM lParam)
{
	return 1;
}

