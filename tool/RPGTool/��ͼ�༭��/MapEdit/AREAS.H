//ver 6.3
/////////////
#include <iostream.h>
#include <fstream.h>

class CMyPoint
{
public:
	bool	IsPoint(POINT pt,int off);
	POINT mypt;
	CMyPoint*	lpNext;
	CMyPoint(POINT pt);
	CMyPoint();	
	void	read(ifstream & in);
	void 	write(ofstream& out);//CMyPoint对 象 数 据 存 储 ， 读 取 函 数		
};// 点 类

class	CPointList
{
private:
	
public:
	void	ClearList();//test
	void	Delcur();	//test
	void	Changecur(POINT pt);//test
	bool	FindPoint(POINT pt,int off);	//test;
	CMyPoint*	 m_head;
	int		m_count;	// 记 录 该 链 表 中 节 点 个 数, 为 静 态 变 量
	CMyPoint*	 m_curposi;// 遍 历 用 指 针
	CMyPoint*	m_preposi;//test
	bool	Next();			// 使m_curpois 指 向 下 一 个 节 点
	void 	Add(POINT pt);		// 在 链 头 加 一 节 点
	bool	Del();		// 删 除 刚 加 的 节 点； 链 表 为 空 返 回false;else return true	
	void	read(ifstream&  in);
	void 	write(ofstream& out);//CPointList对 象 数 据 存 储 ， 读 取 函 数
	void	equal(CPointList &plist);
	CPointList();
	~CPointList();
};// 多 边 形 类，

class	CArea
{
public:

	int m_statein;    // 区 域 内 状 态
	int m_stateout;   // 区 域 外 状 态
	CPointList	m_pointlist;
	CArea*	lpNext;
	void	read(ifstream&	in);
	void 	write(ofstream&	out);//CArea对 象 数 据 存 储 ， 读 取 函 数	
};// 区 域 类，

class	CAreaList
{
private:
	
public:
	void	Delcur();	//test   use first "FindPoint()"
	bool	FindPoint(POINT pt,int off);	//test;
	void	Changecur(POINT pt);		//test; use first "FindPoint()"
	CArea*	m_head;
	int		m_count;	// 记 录 该 链 表 中 节 点 个 数
	CArea*	m_curposi;// 遍 历 用 指 针
	CArea*	m_preposi;//test
	bool	Next();			// 使m_curpois 指 向 下 一 个 节 点
	void 	Add();		// 加 一 节 点
	bool	Del();		// 删 一 节 点；链 表 为 空 返 回false;else return true
	void	read(ifstream&	in);
	void 	write(ofstream& out);  //CAreaList对 象 数 据 存 储 ， 读 取 函 数	
	void    Clear();
	CAreaList();
	~CAreaList();
};// 区 域 链 类； 存 放 场 景 所 有 区 域 信 息；

