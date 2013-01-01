#include <iostream.h>
#include <fstream.h>
//库最多容纳MAXNUM个元素
#define MAXNUM	999
class CNameLib{
public:
	int		m_count;
	char	m_name[999][20];
	BOOL	read(CString filename)
			{
				ifstream in(filename);
				if(in)
				{
					m_count=0;
					while(!in.eof())
						in.getline(m_name[m_count++],20);
					in.close();
					m_count--;
					return true;
				}
				else
				{
					AfxMessageBox("没有找到物品库文件!");
					in.close();
					return false;
				}
			}
};
