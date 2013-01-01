/*
物品类： 物品ID
		名字
		图片ID
//		地面区域
//		图片区域
		激活标志
		可见标志
		功能
	
人物类： 物品ID
		名字
//		地面区域
//		图片区域
		激活标志
		可见标志
		功能	
		动作状态
		动作数组（每个元素包括：动作类型，相应图片号）
		/////
		攻击
		防御
		经验
		等级
		生命
		金钱
		速度
		/////
*/
#include <iostream.h>
#include <fstream.h>

void	copyRECT(RECT& r1,RECT& r2);

class	CThing{
public:
	int		m_ID;//表示其是链中第几个数，不存入文件！
	char m_name[20];	//名字
	bool m_active;		//激活标志
	bool m_visible;		//可见标志
	int  m_function;		//功能	
	int  m_picid;
		
	CThing*	lpNext;
	void	read(ifstream& in);
	void 	write(ofstream& out);
};
class	CNpc{
public:
	int		m_ID;//表示其是链中第几个数，不存入文件
	char m_name[20];//	名字
	bool m_active;//	激活标志
	bool m_visible;//	可见标志
	int m_function;//  功能				／／ｆｏｒ  五
	int m_picid[10];//	动作图片数组	   		／／ ｆｏｒ  一	
	float m_radius;//	占地半径
	float m_sight;//	视 野   //if(m_sight==0)  该ＮＰＣ 不 主 动 靠 近 主 角 ／／ｆｏｒ 四
	int m_attack;//	攻击
	int m_def;//	防御
	int m_exp;//	经验
	int m_level;//	等级
	int m_life;//	生命
	int m_speed;//	速度
	
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