//ver 6.3
/////////////
/*
��Ʒ�ࣺ ��ƷID
		����
		ͼƬID
//		��������
//		ͼƬ����
		�����־
		�ɼ���־
		����
	
�����ࣺ ��ƷID
		����
//		��������
//		ͼƬ����
		�����־
		�ɼ���־
		����	
		����״̬
		�������飨ÿ��Ԫ�ذ������������ͣ���ӦͼƬ�ţ�
		/////
		����
		����
		����
		�ȼ�
		����
		��Ǯ
		�ٶ�
		/////
*/
#include <iostream.h>
#include <fstream.h>
#define	 MAXOBJECTNUM	999
class	CThing{
public:
	int		m_ID;//��ʾ�������еڼ��������������ļ���
	char m_name[20];	//����
	bool m_active;		//�����־
	bool m_visible;		//�ɼ���־
	int  m_function;		//����	
	int  m_picid;
		
	CThing*	lpNext;
	void	read(ifstream& in);
	void 	write(ofstream& out);
};

class CFace{
public:
	char m_strDescribe[20]; //��������
	char m_FileName[20]; //ͼƬ��
	void	read(ifstream& in)
	{
		in.getline(m_strDescribe,20);
		in.getline(m_FileName,20);
		
	}

};

class CNpcFace
{
public:
	char m_name[20];//	����
	int m_nFaceNum;
	CFace m_face[10]; //����

BOOL	read(CString filename)
{
	ifstream in(filename);
	if(in)
	{
		m_nFaceNum=0;
		if(!in.eof())
			in.getline(m_name,20);
		while(!in.eof())
		{
			m_face[m_nFaceNum++].read(in);
			
		}
		in.close();
		if(m_nFaceNum==0)
			return false;
		return true;
		}
		else
		{
			in.close();
			return false;
		}
	}

};
class	CNpc{
public:
	int		m_ID;//��ʾ�������еڼ��������������ļ�
	char m_name[20];//	����
	bool m_active;//	�����־
	bool m_visible;//	�ɼ���־
	int m_function;//  ����				��������  ��
	int m_picid[10];//	����ͼƬ����	   		���� ����  һ	
	float m_radius;//	ռ�ذ뾶
	float m_sight;//	�� Ұ   //if(m_sight==0)  �ãΣУ� �� �� �� �� �� �� �� �������� ��
	int m_attack;//	����
	int m_def;//	����
	int m_exp;//	����
	int m_level;//	�ȼ�
	int m_life;//	����
	int m_speed;//	�ٶ�
	
	CNpc*	lpNext;
	void	read(ifstream& in);
	void 	write(ofstream& out);
};

class	CThingList{
public:
	int			m_count;
	CThing*		m_head;
	CThing*		m_curposi;
	CThing*		m_preposi;
	void		Add(CThing &th);
	void		Delcur();
	bool		Find(int id);
	bool		Next();
	void	read(ifstream& in);
	void 	write(ofstream& out);
	CThingList();
	~CThingList();
};
//NPC ��, �� �� ɫ �� �� �� ��
class	CNpcList{
public:
	int			m_count;
	CNpc*		m_head;
	CNpc*		m_curposi;
	CNpc*		m_preposi;
	void		Add(CNpc &th);
	void		Delcur();
	bool		Find(int id);
	bool		Next();
	void	read(ifstream& in);
	void 	write(ofstream& out);
	CNpcList();
	~CNpcList();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class	CThingLib{
public:
	int	m_count;
	CThing	Thing[MAXOBJECTNUM];
	void	read(ifstream& in);
};
//NPC  ��, ��  �� �� �� �� �� �� �� Ϸ ��
class	CNpcLib{
public:
	int	m_count;
	CNpc	Npc[MAXOBJECTNUM];
	void	read(ifstream& in);
};