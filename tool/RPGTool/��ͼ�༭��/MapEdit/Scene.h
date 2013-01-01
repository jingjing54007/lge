//ver 6.3
/////////////
//#include <iostream.h>
//#include <fstream.h>
#include "areas.h"



#define MAXSCENENUM 99
// �� ̬ �� ״ ̬ �� ��
#define STAND	0
#define WALK	1
#define RUN		2
#define ATTACK	3
// �� ̬ �� �� �� �� ��
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
	RECT m_picarea;		//ͼ Ƭ �� �� λ ��		
	CPointList m_cover;	//�� �� Ч �� ��	
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
};//�� �� �� �� �� ����  ѭ ������ �� ״ ̬�� �� ����[ �� �ܣɣ�]+ ʱ �� �� ����
class CSceneNpc{
public:
	int		 m_id;
	POINT	 m_center;  //�� �� ��            		��������  ��
	POINT	 m_conposi;//�� �� �� �� �� ֡ ͼ Ƭ �� �� �� �� �� �� λ ��
	int m_facewidth;// NPC �� �� ��
	int m_facehigh;	// NPC �� �� ��
	Cautomation		m_autoact[10]; //�� �� �� �� �� ��   	��������  ��
	CSceneNpc*	lpNext;
	void	read(ifstream& in);
	void	write(ofstream& out);
// {�� Ϸ ר �� �� �� �� �� ��
private:
	int	offcode;				// �� �� �� �� �� ��
	int m_state;	//����״̬
	int m_direction;//	�� �� �� ��
	int m_frameid;//	�� �� ֡ ָ ��
	int autoid;//	�� �� �� �� ָ �� //if(m_autoact[i].m_state==0) autoid=0;else autoid++;	
public:
	RECT BltRc;
	void NextPosi(int speed);//   ʹ����� ָ �� �� �� �� �� һ �� λ ��
	void NextFace();//   ʹBaseObject.BltRcָ �� �� �� λ ��
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
};//�ڸ�Ч����ר��
class CDrawList{
public:
	CDrawnode*	m_head;
	CDrawnode*	m_curposi;
	CDrawnode*	m_preposi;
	CDrawList();
	~CDrawList();
	void		Clear();
	void		Insert(CDrawnode node);//�嵽m_preposi��
	void 		Delcur();
	void		Add(CDrawnode node);
	bool		Next2();
	//need add wxx
};//�ڸ�Ч������ר��



///////////////////////�Ի���Begin

class CDlgSingleContent
{
public:
	void clear();
	int m_nwho; //0��NPC,1������
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
{ //��NPC�ĶԻ���¼
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
 
class CDlg{//��NPC�ĶԻ���
public:
	void clear();
	int m_nCountState; //��NPC���м��ֶԻ�״̬
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
class CDlgList{ //����NPC�ĶԻ���
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
/////////////////////�Ի���End










////////////////////�������¼���begin



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





///////////////////�������¼���End



class CMyScene{
private:
	bool judgeacross(POINT	pt1,POINT pt2,POINT	pt3,POINT pt4);//�ڸ�Ч������ר��
	bool judgein(CPointList &m_cover,POINT pt);//�ڸ�Ч������ר��
public:
	char m_picname[20];
	POINT m_position;    //����λ��
	int m_high;
	int m_width;
	float m_maxsize;
	float m_minsize;
	CSceneThingList	m_thinglist;//��̬����
	CSceneNpcList	m_npclist;//��̬����
	CAreaList			m_arealist;
	CDrawList			m_drawlist;
	void Clear();
	void arrange();	
	void read(ifstream &in);
	void write(ofstream &out);
// {�� Ϸ ר �� �� �� �� �� ��

public:
//	int		offcode;// �� �� Ĭ �� Ϊ0
	RECT	BltRc;
	void TimeWork(POINT Player);//Player Ϊ �� �� �� �� �� �� λ ��
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

	bool m_active;//	�����־
	bool m_visible;//	�ɼ���־
	int m_picid[10];//	����ͼƬ����	   		���� ����  һ	
				//stand->0;walk->1;run->2;attact->3;dead->4
	float m_radius;//	ռ�ذ뾶
	float m_sight;//	�� Ұ   // �� �� һ��if(m_sight==0)  �ãΣУ� �� �� �� �� �� �� �� �������� ��
			// �� �� ���� �� Ұ �� �� Ѱ ��
	int m_attack;//	����
	int m_def;//	����
	int m_exp;//	����
	int m_level;//	�ȼ�
	int m_life;//	����
	int m_speed;//	�ٶ�

	POINT m_center;//  �� �� ��            		��������  �� 
	POINT m_conposi;// �� �� �� �� �� ֡ ͼ Ƭ �� �� �� �� �� �� λ ��
	int m_facewidth;// �� Ʒ �� �� ��
	int m_facehigh;	// �� Ʒ �� �� ��

	int m_state;//	����״̬
	int m_direction;//	�� �� �� ��
	int m_frameid;//	�� �� ֡ ָ ��
	int m_offcode[10];//����ͼƫ���������
/////////////////////////////////////////////////////////////////
	public:
		int m_target_type;//0->Ŀ��Ϊ����;1->Ŀ��ΪNPC;2->Ŀ��ΪThing
		POINT m_target_pos;//Ŀ������
		int   m_target_npc;
		int   m_target_thing;
		RECT BltRc;//BltԴ����
		void NextPosi();//   ʹm_centerָ �� �� �� �� �� һ �� λ ��
		void NextFace();//   ʹBltRcָ �� �� �� λ ��
		void TimeWork();
		int  TraceMsg(UINT message,WPARAM wParam, LPARAM lParam);
		void InitData();
		void	read(ifstream& in);
		void	write(ofstream& out);
};

