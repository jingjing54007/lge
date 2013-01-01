//ver 6.3
/////////////
//#include <iostream.h>
//#include <fstream.h>
#include "areas.h"



#define MAXSCENENUM 99
// 动 态 物 状 态 定 义
#define STAND	0
#define WALK	1
#define RUN		2
#define ATTACK	3
// 动 态 物 朝 向 定 义
#define LEFT 0
#define	LEFTUP	 1
#define	UP		 2
#define	UPRIGHT  3
#define	RIGHT	 4
#define	RIGHTDOWN 5
#define	DOWN     6
#define	DOWNLEFT 7
//
void	copyRECT(RECT& r1,RECT& r2);
class CSceneThing{
public:
	int m_id;
	RECT m_picarea;		//图 片 区 域 位 置		
	CPointList m_cover;	//遮 盖 效 果 区	
	CSceneThing*	lpNext;
	void	read(ifstream& in);
	void	write(ofstream& out);
};
class CSceneThingList{
public:
	int				m_count;
	CSceneThing*	m_head;
	CSceneThing*   m_curposi;
	CSceneThing*	m_preposi;
	void		Add(CSceneThing &th);
	void		Clear();
	void		Delcur();
	bool		Find(int id);
	bool		Next();
	void	read(ifstream& in);
	void 	write(ofstream& out);
	CSceneThingList();
	~CSceneThingList();
};
struct Cautomation{
	int	 m_state;
	POINT 	 m_pt;
	int 	 m_wait;	
};//自 主 运 动 结 构；  循 环（改 变 状 态＋ 运 动＋[ 功 能ＩＤ]+ 时 间 间 隔〕
class CSceneNpc{
public:
	int		 m_id;
	POINT	 m_center;  //中 心 点            		／／ｆｏｒ  二
	POINT	 m_conposi;//中 心 点 在 单 帧 图 片 区 域 中 的 相 对 位 置
	int m_facewidth;// NPC 外 观 宽
	int m_facehigh;	// NPC 外 观 高
	Cautomation		m_autoact[10]; //自 主 运 动 数 组   	／／ｆｏｒ  三
	CSceneNpc*	lpNext;
	void	read(ifstream& in);
	void	write(ofstream& out);
// {游 戏 专 用 变 量 和 函 数
private:
	int	offcode;				// 离 屏 表 面 代 码
	int m_state;	//动作状态
	int m_direction;//	动 作 方 向
	int m_frameid;//	动 作 帧 指 针
	int autoid;//	自 主 运 动 指 针 //if(m_autoact[i].m_state==0) autoid=0;else autoid++;	
public:
	RECT BltRc;
	void NextPosi(int speed);//   使ｓｅａｔ 指 向 场 景 中 下 一 个 位 置
	void NextFace();//   使BaseObject.BltRc指 向 下 个 位 置
	void TimeWork();
	void InitData();
//end}
};
class CSceneNpcList{
public:
	int				m_count;
	CSceneNpc*	m_head;
	CSceneNpc*   m_curposi;
	CSceneNpc*	m_preposi;
	void		Add(CSceneNpc &th);
	void		Clear();
	void		Delcur();
	bool		Find(int id);
	bool		Next();
	void	read(ifstream& in);
	void 	write(ofstream& out);
	CSceneNpcList();
	~CSceneNpcList();
};
class CDrawnode{
public:
	bool	m_type;//m_type=true->is thing;m_type=false->is npc
	int		m_id;
	CDrawnode* lpNext;
};//遮盖效计算专用
class CDrawList{
public:
	CDrawnode*	m_head;
	CDrawnode*	m_curposi;
	CDrawnode*	m_preposi;
	CDrawList();
	~CDrawList();
	void		Clear();
	void		Insert(CDrawnode node);//插到m_preposi后
	void 		Delcur();
	void		Add(CDrawnode node);
	bool		Next2();
	//need add wxx
};//遮盖效果计算专用



///////////////////////对话类Begin

class CDlgSingleContent
{
public:
	void clear();
	int m_nwho; //0是NPC,1是主角
	char m_Content[200];
	int m_nExpressionID;
	CDlgSingleContent *lpNext;
	CDlgSingleContent()
	{
	lpNext=NULL;
	}

	void	read(ifstream&  in)
	{
		in.read((char*)&m_nwho,sizeof(int));
		in.read((char*)m_Content,200*sizeof(char));
		in.read((char*)&m_nExpressionID,sizeof(int));
	}

	void 	write(ofstream& out)
	{
		out.write((char*)&m_nwho,sizeof(int));
		out.write((char*)m_Content,200*sizeof(char));
		out.write((char*)&m_nExpressionID,sizeof(int));
	}


};	



class CDlgContent
{ //该NPC的对话纪录
public:
	void clear();
	int CountSentence;
	CDlgContent * lpNext;
	CDlgSingleContent * m_head;
	CDlgContent()
	{
		m_head=NULL;
		CountSentence=0;
	}


	void	read(ifstream&  in)
	{
		in.read((char*)&CountSentence,sizeof(int));
		CDlgSingleContent *lp;
		for(int i=0;i<CountSentence;i++)
		{
			lp=m_head;
			m_head=new CDlgSingleContent;
			m_head->read(in);
			m_head->lpNext=lp;
		}
		
	}

	void 	write(ofstream& out)
	{

		out.write((char*)&CountSentence,sizeof(int));
		CDlgSingleContent *lp;
		lp=m_head;
    	for(int i=0;i<CountSentence;i++)
		{
			for(int j=0;j<CountSentence-i-1;j++,lp=lp->lpNext);
			lp->write(out);
    		lp=m_head;
		
		}

	}

};
 
class CDlg{//该NPC的对话链
public:
	void clear();
	int m_nCountState; //该NPC共有几种对话状态
	CDlgContent *m_head; 
	CDlg *lpNext;
	char m_name[10];
	CDlg()
	{
		m_nCountState=0;
		m_head=NULL;
	}

	void	read(ifstream&  in)
	{   
		in.read((char*)m_name,10*sizeof(char));
		in.read((char*)&m_nCountState,sizeof(int));
		CDlgContent *lp;
		for(int i=0;i<m_nCountState;i++)
		{
			lp=m_head;
			m_head=new CDlgContent;
			m_head->read(in);
			m_head->lpNext=lp;
		}
		
	}

	void 	write(ofstream& out)
	{
		out.write((char*)m_name,10*sizeof(char));
		out.write((char*)&m_nCountState,sizeof(int));
		CDlgContent *lp;
		lp=m_head;
		for(int i=0;i<m_nCountState;i++)
		{
			for(int j=0;j<m_nCountState-i-1;j++,lp=lp->lpNext);
			lp->write(out);
    		lp=m_head;
		}
	}

};
class CDlgList{ //所有NPC的对话链
public:
	void clear();
	int m_nNpcNum;
	CDlg *m_head;
	CDlgList()
	{
		m_nNpcNum=0;
		m_head=NULL;
	}
void	read(ifstream&  in)
	{
	int i;
	in.read((char*)&m_nNpcNum,sizeof(int)); 
		CDlg *lp;
		for( i=0;i<m_nNpcNum;i++)
		{
			lp=m_head;
			m_head=new CDlg;
			m_head->read(in);
			m_head->lpNext=lp;
		}
	
	}

	void 	write(ofstream& out)
	{
		out.write((char*)&m_nNpcNum,sizeof(int));
		CDlg *lp=m_head;
		for(int i=0;i<m_nNpcNum;i++)
		{
			for(int j=0;j<m_nNpcNum-i-1;j++,lp=lp->lpNext);
			lp->write(out);
    		lp=m_head;
		}
	}
};
/////////////////////对话类End










////////////////////条件及事件类begin



extern int Calculate(CString s);
extern int result(CString s);


class CCondition{
public:
	int m_nID;
	int m_nDone;
	int m_nUsed;
	char m_Describe[50];
	CCondition *lpNext;
	CCondition()
	{
		lpNext=NULL;
		m_nDone=0;
		m_nUsed=0;
	}
	void read(ifstream &in)
	{
		in.read((char*)&m_nID,sizeof(int));
		in.read((char*)&m_nDone,sizeof(int));
		in.read((char*)&m_nUsed,sizeof(int));
		in.read((char*)m_Describe,50*sizeof(char));
	}

	void write(ofstream &out)
	{
		out.write((char*)&m_nID,sizeof(int));
		out.write((char*)&m_nDone,sizeof(int));
		out.write((char*)&m_nUsed,sizeof(int));
		out.write((char*)m_Describe,50*sizeof(char));
	}

};


extern CString CheckCondition(CString s,int f);

class CEvent{
public:
	int m_nID;
	char m_Describe[50];
	char m_Expression[50];
	CEvent *lpNext;
	CEvent()
	{
		lpNext=NULL;
	}
	void read(ifstream &in)
	{
		in.read((char*)&m_nID,sizeof(int));
		in.read((char*)m_Describe,50*sizeof(char));
		in.read((char*)m_Expression,50*sizeof(char));
	}
	void write(ofstream &out)
	{
		out.write((char*)&m_nID,sizeof(int));
		out.write((char*)m_Describe,50*sizeof(char));
		out.write((char*)m_Expression,50*sizeof(char));
	}

	int GetResult()
	{
		return result(CheckCondition(m_Expression,0));
	}

};



class CConditionList{
public:
	int m_nConditionNum;
	CCondition *m_head;
	CConditionList()
	{
		m_nConditionNum=0;
		m_head=0;
	}
	void read(ifstream &in)
	{
		in.read((char*)&m_nConditionNum,sizeof(int));
		CCondition*	lpold;
		for(int i=0;i<m_nConditionNum;i++)
		{
			lpold=m_head;
			m_head=new	CCondition;
			m_head->lpNext=lpold;
			m_head->read(in);
		}

	}
	void write(ofstream &out)
	{
		out.write((char*)&m_nConditionNum,sizeof(int));
		CCondition *lp=m_head;
		for(int i=0;i<m_nConditionNum;i++)
		{
			lp->write(out);
    		lp=lp->lpNext;
		}
	}
	void clear()
	{
		CCondition *p=m_head;
		CCondition *lp;
		while(p!=NULL)
		{
			lp=p->lpNext;
			delete p;
			p=lp;
		}
	}


};

class CEventList{
public:
	int m_nEventNum;
	CEvent *m_head;
	CEventList()
	{
		m_nEventNum=0;
		m_head=NULL;
	}
	void read(ifstream &in)
	{
		in.read((char*)&m_nEventNum,sizeof(int));
		CEvent*	lpold;
		for(int i=0;i<m_nEventNum;i++)
		{
			lpold=m_head;
			m_head=new	CEvent;
			m_head->lpNext=lpold;
			m_head->read(in);
		}
	}

	void write(ofstream &out)
	{
		out.write((char*)&m_nEventNum,sizeof(int));
		CEvent *lp=m_head;
		for(int i=0;i<m_nEventNum;i++)
		{
			lp->write(out);
    		lp=lp->lpNext;
		}
	}

	void clear()
	{
		CEvent *p=m_head;
		CEvent *lp;
		while(p!=NULL)
		{
			lp=p->lpNext;
			delete p;
			p=lp;
		}
	}
};





///////////////////条件及事件类End



class CMyScene{
private:
	bool judgeacross(POINT	pt1,POINT pt2,POINT	pt3,POINT pt4);//遮盖效果计算专用
	bool judgein(CPointList &m_cover,POINT pt);//遮盖效果计算专用
public:
	char m_picname[20];
	POINT m_position;    //主角位置
	int m_high;
	int m_width;
	float m_maxsize;
	float m_minsize;
	CSceneThingList	m_thinglist;//静态物链
	CSceneNpcList	m_npclist;//动态物链
	CAreaList			m_arealist;
	CDrawList			m_drawlist;
	void Clear();
	void arrange();	
	void read(ifstream &in);
	void write(ofstream &out);
// {游 戏 专 用 变 量 和 函 数

public:
//	int		offcode;// 因 其 默 认 为0
	RECT	BltRc;
	void TimeWork(POINT Player);//Player 为 主 角 在 场 景 中 位 置
	void InitData();
//end}
};
class	CSceneLib{
public:
	int	m_count;
	char	m_name[MAXSCENENUM][20];
	void	read();
};

class CMainNpc  
{
public:
	CMainNpc();
	virtual ~CMainNpc();

	bool m_active;//	激活标志
	bool m_visible;//	可见标志
	int m_picid[10];//	动作图片数组	   		／／ ｆｏｒ  一	
				//stand->0;walk->1;run->2;attact->3;dead->4
	float m_radius;//	占地半径
	float m_sight;//	视 野   // 功 能 一：if(m_sight==0)  该ＮＰＣ 不 主 动 靠 近 主 角 ／／ｆｏｒ 四
			// 功 能 二： 视 野 仿 真 寻 道
	int m_attack;//	攻击
	int m_def;//	防御
	int m_exp;//	经验
	int m_level;//	等级
	int m_life;//	生命
	int m_speed;//	速度

	POINT m_center;//  中 心 点            		／／ｆｏｒ  二 
	POINT m_conposi;// 中 心 点 在 单 帧 图 片 区 域 中 的 相 对 位 置
	int m_facewidth;// 物 品 外 观 宽
	int m_facehigh;	// 物 品 外 观 高

	int m_state;//	动作状态
	int m_direction;//	动 作 方 向
	int m_frameid;//	动 作 帧 指 针
	int m_offcode[10];//动作图偏离屏表面号
/////////////////////////////////////////////////////////////////
	public:
		int m_target_type;//0->目标为坐标;1->目标为NPC;2->目标为Thing
		POINT m_target_pos;//目标坐标
		int   m_target_npc;
		int   m_target_thing;
		RECT BltRc;//Blt源区域
		void NextPosi();//   使m_center指 向 场 景 中 下 一 个 位 置
		void NextFace();//   使BltRc指 向 下 个 位 置
		void TimeWork();
		int  TraceMsg(UINT message,WPARAM wParam, LPARAM lParam);
		void InitData();
		void	read(ifstream& in);
		void	write(ofstream& out);
};

