#include <iostream.h>
#include <fstream.h>
//库最多容纳MAXNUM个元素
#define MAXNUM	999

class CNameLib{
public:
	int		m_count;
	char	m_name[999][20];
	void	read(){
				m_count=0;
				ifstream in("piclib.txt");
				if(in){			
					while(!in.eof()){
						in.getline(m_name[m_count],20);
						m_count++;
					}
				}
				in.close();
			}
};
