// MapEditDoc.cpp : implementation of the CMapEditDoc class
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MapEditDoc.h"


#include "MainFrm.h"
#include "MapEditView.h"
#include "SampleView.h"
#include "ToolsBar.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDlgList * m_pDlgList;// 全部NPC的全部对话纪录
extern CDlg *m_pDlg;//某个NPC的全部状态
extern CDlgSingleContent *m_pDlgSingleState; //某个NPC的某种状态的记录链
extern CDlgContent *m_pDlgContent; //某个NPC某个状态的对话

extern CConditionList *m_pConditionList;
extern CEventList *m_pEventList;





void CDlgList::clear()
{
	CDlg *p=m_head;
	CDlg *lp;
	while(p!=NULL)
	{
		lp=p->lpNext;
		p->clear();
		p=lp;
	}
	


}

void CDlg::clear()
{
	CDlgContent *p=m_head;
	CDlgContent *lp;
	while(p!=NULL)
	{
		lp=p->lpNext;
		p->clear();
		p=lp;
	}
//	delete []m_name;

}

void CDlgContent::clear()
{

	CDlgSingleContent *p=m_head;
	CDlgSingleContent *lp;
	while(p!=NULL)
	{
		lp=p->lpNext;
		p->clear();
		p=lp;
	}


}

void CDlgSingleContent::clear()
{
//	delete[]m_Content;

}






/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc

IMPLEMENT_DYNCREATE(CMapEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditDoc, CDocument)
	//{{AFX_MSG_MAP(CMapEditDoc)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVESCENE, OnFileSavescene)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_SYSFILE_CREATE, OnSysfileCreate)
	ON_UPDATE_COMMAND_UI(ID_SYSFILE_CREATE, OnUpdateSysfileCreate)
	ON_COMMAND(ID_SYSFILE_CHANGE, OnSysfileChange)
	ON_UPDATE_COMMAND_UI(ID_SYSFILE_CHANGE, OnUpdateSysfileChange)
	ON_UPDATE_COMMAND_UI(ID_MODEL_ZOOM, OnUpdateModelZoom)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc construction/destruction

CMapEditDoc::CMapEditDoc()
{
	GetExeFilePath(m_WorkingPath);
	m_picwulibin=false;
	m_picrenlibin=false;
	m_execute=false;
	InitData();
	LoadSysFile();

	
	
}	

CMapEditDoc::~CMapEditDoc()
{
	if(SampleHb!=NULL)
		DeleteObject(SampleHb);
	CurDC.DeleteDC();
	SampleDC.DeleteDC();
	MaskDC.DeleteDC();
	BakDC.DeleteDC();
	memDC.DeleteDC();

}

BOOL CMapEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc serialization

void CMapEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc diagnostics

#ifdef _DEBUG
void CMapEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc commands

void CMapEditDoc::GetExeFilePath(char *filepath)
{
	CString ExePath;
	int num;
	GetModuleFileName(GetModuleHandle("mapedit.exe"), filepath, 255);
	ExePath.Format("%s",filepath);// 此时filename中为应用程序的路径+文件名称

	num=ExePath.ReverseFind('\\');
	ExePath=ExePath.Left(num);// 此时ExePath中为应用程序的路径
	
	strcpy(filepath, ExePath);

}

void CMapEditDoc::OnFileNew() 
{
	CString FileName,filename;
	HBITMAP hb;
	BITMAP bm;
	CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
	CMapEditView* pView = (CMapEditView*)pMainWnd->m_wndSplitter1.GetPane(0,0);
	CSampleView* pView2 = (CSampleView*)pMainWnd->m_wndSplitter2.GetPane(0,0);
	CToolsBar* pView3 = (CToolsBar*)pMainWnd->m_wndSplitter2.GetPane(1,0);
	
	if(!m_sysfilein)
	{
		AfxMessageBox("没有找到软件运行配置文件，请先创建配置文件！");
		return;
	}
	if(m_save==1)
	{
		if((MessageBox(NULL,"你确定不保存当前场景信息?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDNO))
		{
			if(strcmp(mapfilename,"")==0)
			{
				OnFileSavescene();
				m_save=0;
				return;
			}
			else
			{
				SaveScene(mapfilename);
				m_save=0;
				return;
			}
		}
	}
	
	char lpszFilter[]="位图 (*.bmp)|*.bmp|所有文件 (*.*)|*.*||";
	
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	
	CFileDialog fileDlg(TRUE, NULL, NULL, dwFlags, lpszFilter, NULL);
	fileDlg.m_ofn.lpstrTitle = "打开地图位图";
	char filepath[256];
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\maps");
	fileDlg.m_ofn.lpstrInitialDir= filepath;
    
	if(fileDlg.DoModal()==IDOK)
	{
		InitData();
		FileName=fileDlg.GetPathName();
		//得到场景位图文件名
		filename=fileDlg.GetFileName();
		hb=(HBITMAP)LoadImage(NULL,FileName,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	//	LoadBmpFromFile(FileName,&hb);
		if(hb==NULL)
		{
			AfxMessageBox("创建内存位图失败！");
			return;
		}
		else
		{
			m_myscene.Clear();

			
			if(m_pDlgList!=NULL)
			m_pDlgList->clear();
//			m_pDlgList=new CDlgList;

			 m_pDlgList=NULL;
			 m_pDlg=NULL;
			 m_pDlgSingleState=NULL;

			if(m_pConditionList!=NULL)
				m_pConditionList->clear();

			
//			m_pConditionList=new CConditionList;
			if(m_pEventList!=NULL)
				m_pEventList->clear();
//			m_pEventList=new CEventList;










			strcpy(mapfilename,"");
			CurDC.DeleteDC();
			GetObject(hb,sizeof(bm),&bm);
		
			m_mapSize.cx=bm.bmWidth;
			m_mapSize.cy=bm.bmHeight;
		
			CreateDC(&CurDC,bm.bmWidth,bm.bmHeight); 
			//将位图选入内存
			CurDC.SelectObject(hb);
			DeleteObject(hb);
			
		//	CreateDC(&CurDC,bm.bmWidth,bm.bmHeight);
	
			m_myscene.m_high=bm.bmHeight;
			m_myscene.m_width=bm.bmWidth;
			strcpy(m_myscene.m_picname,filename);
		//	CString ss;
		//	ss.Format("F:%f,N:%f",m_myscene.m_minsize,m_myscene.m_maxsize);
			pView3->m_displayzoom.SetWindowText("还未设定");
		//	ss.Format("X=%d,Y=%d",m_myscene.m_position.x,m_myscene.m_position.y);
			pView3->m_displaypos.SetWindowText("还未设定");
			pView->Invalidate();
			pView2->Invalidate();
			
			memDC.DeleteDC();
			BakDC.DeleteDC();
			//备份位图
			CreateDC(&memDC,bm.bmWidth,bm.bmHeight); 
			CreateDC(&BakDC,bm.bmWidth,bm.bmHeight); 
			memDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&CurDC,0,0,SRCCOPY);
			BakDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&CurDC,0,0,SRCCOPY);
			m_scenein=false;
			m_mapbmpin=true;
			m_execute=true;
			char modelfile[256];
			strcpy(modelfile,m_WorkingPath);
			strcat(modelfile,"\\model.bmp");
			modelbh=(HBITMAP)LoadImage(NULL,modelfile,IMAGE_BITMAP,0,0,
				               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			if(modelbh!=NULL)
			{
				GetObject(modelbh,sizeof(modelbm),&modelbm);
				modelDC.DeleteDC();
				CreateDC(&modelDC,modelbm.bmWidth,modelbm.bmHeight);
				modelDC.SelectObject(modelbh);
				m_modelin=true;
			}
		}
	}
}

void CMapEditDoc::OnFileOpen() 
{
	CString FileName;
	HBITMAP hb;
	BITMAP bm;
	
	CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
	CMapEditView* pView = (CMapEditView*)pMainWnd->m_wndSplitter1.GetPane(0,0);
	CSampleView* pView2 = (CSampleView*)pMainWnd->m_wndSplitter2.GetPane(0,0);
	CToolsBar* pView3 = (CToolsBar*)pMainWnd->m_wndSplitter2.GetPane(1,0);
	if(!m_sysfilein)
	{
		AfxMessageBox("没有找到软件运行配置文件，请先创建配置文件！");
		return;
	}
	if(m_save==1)
	{
		if((MessageBox(NULL,"你确定不保存当前场景信息?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDNO))
		{
			if(strcmp(mapfilename,"")==0)
			{
				OnFileSavescene();
				m_save=0;
				return;
			}
			else
			{
				SaveScene(mapfilename);
				m_save=0;
				return;
			}
		}
	}
	char lpszFilter[]="场景 (*.map)|*.map|所有文件 (*.*)|*.*||";

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	
	CFileDialog fileDlg(TRUE, NULL, NULL, dwFlags, lpszFilter, NULL);
	fileDlg.m_ofn.lpstrTitle = "打开场景文件";
	char filepath[256];
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\maps");
	fileDlg.m_ofn.lpstrInitialDir= filepath;
    
	if(fileDlg.DoModal()==IDOK)
	{
		InitData();
		if(fileDlg.GetFileExt()!="map")
		{
			FileName="\\"+fileDlg.GetFileTitle();
			FileName=FileName+".map";
		}
		else
			FileName="\\"+fileDlg.GetFileName();
		FileName=filepath+FileName;
	
		ifstream in; //(FileName);
		in.open(FileName,ios::nocreate|ios::in|ios::binary);

		if(in)
		{
			m_myscene.Clear();
			//读入场景信息链表
			m_myscene.read(in);

		

			if(m_pDlgList!=NULL)
			m_pDlgList->clear();
			m_pDlgList=new CDlgList;
			m_pDlgList->read(in);
			if(m_pConditionList!=NULL)
				m_pConditionList->clear();
			m_pConditionList=new CConditionList;
			m_pConditionList->read(in);
			if(m_pEventList!=NULL)
				m_pEventList->clear();
			m_pEventList=new CEventList;
			m_pEventList->read(in);

//////////////////
	        m_scenein=true;
			strcpy(mapfilename,FileName);
			in.close();
			hb=(HBITMAP)LoadImage(NULL,m_myscene.m_picname,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
			
	
			if(hb==NULL)
			{
				AfxMessageBox("场景信息文件损坏！");
				m_scenein=false;
				
				return;
			}
			else
			{
				memDC.DeleteDC();
				CurDC.DeleteDC();	
				m_mapbmpin=true;
				m_scenein=true;
				GetObject(hb,sizeof(bm),&bm);
				m_mapSize.cx=bm.bmWidth;
				m_mapSize.cy=bm.bmHeight;
				CreateDC(&memDC,bm.bmWidth,bm.bmHeight); 
				CreateDC(&CurDC,bm.bmWidth,bm.bmHeight);

	

				memDC.SelectObject(hb);
				DeleteObject(hb);
				CurDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&memDC,0,0,SRCCOPY);



				SampleDC.DeleteDC();

				DrawSceneInDC(&CurDC);   //这句有问题!!!

								
				CString ss;
				ss.Format("F:%f,N:%f",m_myscene.m_minsize,m_myscene.m_maxsize);
				pView3->m_displayzoom.SetWindowText(ss);

				ss.Format("X=%d,Y=%d",m_myscene.m_position.x,m_myscene.m_position.y);
				pView3->m_displaypos.SetWindowText(ss);
				pView->Invalidate();
				pView2->Invalidate();
				m_execute=true;
				
				
				BakDC.DeleteDC();
				CreateDC(&BakDC,bm.bmWidth,bm.bmHeight);
				BakDC.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&CurDC,0,0,SRCCOPY);

				char modelfile[256];
				strcpy(modelfile,m_WorkingPath);
				strcat(modelfile,"\\model.bmp");
				modelbh=(HBITMAP)LoadImage(NULL,modelfile,IMAGE_BITMAP,0,0,
					               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				if(modelbh!=NULL)
				{
					GetObject(modelbh,sizeof(modelbm),&modelbm);
					modelDC.DeleteDC();
					CreateDC(&modelDC,modelbm.bmWidth,modelbm.bmHeight);
					modelDC.SelectObject(modelbh);
					m_modelin=true;
				}
			}
		}
		else
		{
			AfxMessageBox (FileName+"文件所对应的场景文件没有找到!!!");
			in.close();
			return;
		}
	}
	else
	{
		pView->Invalidate();
	}



}

void CMapEditDoc::OnFileSavescene() 
{
	CString FileName;
	if(!m_scenechange)
	{
		AfxMessageBox("没有任何场景信息可以保存！");
		return;
	}
	
	if(m_myscene.m_maxsize==0 ||m_myscene.m_minsize==0)
	{
		AfxMessageBox("还没有设定人物的缩放比例，请设定！！");
		return;
	}
	if(m_myscene.m_position.x==0 || m_myscene.m_position.y==0
	   || m_myscene.m_position.x < 0 || m_myscene.m_position.y < 0)
	{
	   AfxMessageBox("没有指定主角进入场景的初始位置！！");
	   return;
	}
	
	char lpszFilter[]="场景 (*.map)|*.map||";
	
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	
	CFileDialog fileDlg(FALSE, NULL, NULL, dwFlags, lpszFilter, NULL);
	fileDlg.m_ofn.lpstrTitle = "保存场景文件";
	char filepath[256];
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\maps");
	fileDlg.m_ofn.lpstrInitialDir= filepath;
    
	if(fileDlg.DoModal()==IDOK)
	{
		FileName=fileDlg.GetPathName();
		if(fileDlg.GetFileExt()!="map")
		{
			FileName="\\"+fileDlg.GetFileTitle()+".map";
			FileName=filepath+FileName;
		}
		strcpy(filepath,FileName);
		SaveScene(filepath);
	}
}

void CMapEditDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_scenechange);
	
}

void CMapEditDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);
}

void CMapEditDoc::OnSysfileCreate() 
{
	// TODO: Add your command handler code here
	CSYSDLG m_sysdlg;
	m_sysdlg.DoModal();
	LoadSysFile();
	
}

void CMapEditDoc::OnUpdateSysfileCreate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_execute && !m_sysfilein);
	
}

void CMapEditDoc::OnSysfileChange() 
{
	// TODO: Add your command handler code here

	CSYSDLG m_sysdlg;
	m_sysdlg.DoModal();
	LoadSysFile();
}

void CMapEditDoc::OnUpdateSysfileChange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_execute && m_sysfilein);
	
}

void CMapEditDoc::LoadSysFile()
{
	char sysfilepath[256],filepath[256];
	
	strcpy(sysfilepath, m_WorkingPath);
	strcat(sysfilepath, "\\System.dat");

	ifstream in;
	in.open(sysfilepath,ios::nocreate|ios::in|ios::binary);
	if(in)
	{
		m_attriblist.m_head=NULL;
		m_attriblist.read(in);
		m_sysfilein=true;
		in.close();
	}
	else
	{
		in.close();
		m_sysfilein=false;
	}
	
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\thlib\\piclib.txt");
	
	if(!m_picthlib.read(filepath)) //载入物品图片库
	{
//		AfxMessageBox("没有找到物品图片库！");
//		exit(0);
	}
	else
	{
		strcpy(filepath, m_WorkingPath);
		strcat(filepath, "\\thlib\\object");

		in.open(filepath,ios::nocreate|ios::in|ios::binary);
		if(in)
		{
			m_thlist.read(in);       //载入物品库
			in.close();
			m_picwulibin=true;
		}
		else
		{
			m_picwulibin=false;
			in.close();
		}
	}
	
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\npclib\\piclib.txt");
	
	if(!m_picnpclib.read(filepath)) //载入人物图片库
	{
//		AfxMessageBox("没有找到人物图片库！");
//		exit(0);
	}
	else
	{
		strcpy(filepath, m_WorkingPath);
		strcat(filepath, "\\npclib\\rolelib.cha");
		
		in.open(filepath,ios::nocreate|ios::in|ios::binary);
		if(in)
		{
			m_npclib.read(in);//载入人物库
			in.close();
			m_picrenlibin=true;
		}
		else
		{
			m_picrenlibin=false;
			in.close();
		}
	}

}


bool CMapEditDoc::CreateDC(CDC *tempDC,int width, int height)
{
	CDC *dc;
	CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
	CMapEditView* pView = (CMapEditView*)pMainWnd->m_wndSplitter1.GetPane(0,0);
	CBitmap memBitmap; 
	dc=pView->GetDC();
	tempDC->CreateCompatibleDC(dc);
	memBitmap.CreateCompatibleBitmap(dc,width,height);
	tempDC->SelectObject(&memBitmap);
	dc->DeleteDC();
	return true;
}

void CMapEditDoc::DrawSceneInDC(CDC *tempDC)
{
	HBITMAP hb;
	BITMAP bm;
	CPoint pt1,pt2;
	CSceneThingList* thlist;   //指向场景信息中的物品链
	CPointList*	list;   //指向遮盖区链

	thlist=&m_myscene.m_thinglist;
	char filepath[256];
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\thlib\\");


	if(thlist->m_head!=NULL)
	{
		thlist->m_curposi=thlist->m_head;
		while(thlist->m_curposi!=NULL)
		{
			list=&(thlist->m_curposi->m_cover);
			CString filename,file;
			filename=filepath;
			//在物品库中查找
			m_thlist.Find(thlist->m_curposi->m_id);
			filename=filename+m_picthlib.m_name[m_thlist.m_curposi->m_picid];//这句有问题 ????
			//应该是m_thlist有问题

			filename=filename;//+".bmp";
			hb=(HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			if(hb==NULL)
				AfxMessageBox("打开物品图片出错!");
                
			else
			{
				GetObject(hb,sizeof(bm),&bm);
				SampleDC.DeleteDC();

				CreateDC(&SampleDC,bm.bmWidth,bm.bmHeight);
				SampleDC.SelectObject(hb);
	

				transcolor=SampleDC.GetPixel(CPoint(0,0));
				
				CRect rc;
				rc=thlist->m_curposi->m_picarea;
				TransDraw(tempDC,rc.left,rc.top,(byte*)bm.bmBits,bm.bmWidth,bm.bmHeight,transcolor);
				DeleteObject(hb);
				SampleDC.DeleteDC();
			}
	    	if(list->m_head!=NULL)
			{
				list->m_curposi=list->m_head;
				pt1=list->m_curposi->mypt;
				tempDC->MoveTo(pt1);
				tempDC->Ellipse(pt1.x-3,pt1.y-3,pt1.x+3,pt1.y+3);
				list->Next();
				while(list->m_curposi!=NULL)
				{
					pt1=list->m_curposi->mypt;
					tempDC->LineTo(pt1);
					tempDC->Ellipse(pt1.x-3,pt1.y-3,pt1.x+3,pt1.y+3);
					list->Next();
				}
				pt2=list->m_head->mypt;
				tempDC->LineTo(pt2);
			}
			thlist->Next();
		}
	}

	//画人物链
	COLORREF color;
	CSceneNpcList*	npclist;
//	CSceneNpc*	npcnode;
	npclist=&m_myscene.m_npclist;
//	char filepath[256];
	strcpy(filepath, m_WorkingPath);
	strcat(filepath, "\\npclib\\");
	if(npclist->m_head!=NULL)
	{
		npclist->m_curposi=npclist->m_head;
		while(npclist->m_curposi!=NULL)
		{
			char filename[256];
			//在人物库中查找
			strcpy(filename,filepath);
			int renid=npclist->m_curposi->m_id;

			strcat(filename,m_picnpclib.m_name[m_npclib.Npc[npclist->m_curposi->m_id].m_picid[0]]);

		    //	filename=filename+".bmp";
			hb=(HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		
			if(hb==NULL)
				AfxMessageBox("打开人物图片出错!");
			else
			{
				pt1=npclist->m_curposi->m_conposi;
				pt2=npclist->m_curposi->m_center;
			
				pt2=pt2-pt1;
		
				GetObject(hb,sizeof(bm),&bm);
				BakDC.DeleteDC();
				MaskDC.DeleteDC();
			
				CreateDC(&BakDC,bm.bmWidth,bm.bmHeight);
				CreateDC(&MaskDC,80,100);
				BakDC.SelectObject(hb);
				
				
				
				//在NPC图片中拷贝出一帧
				TransDCtoDC(&MaskDC,0,0,&BakDC,80,100,1);
			
				BakDC.DeleteDC();
				SampleDC.DeleteDC();
				DeleteObject(hb);
				
				CPen mypen,*oldpen;
				mypen.CreatePen(PS_DASH,1,RGB(128,128,255));
				oldpen=tempDC->SelectObject(&mypen);
				int i=0;
				m_oldpoint=npclist->m_curposi->m_autoact[i].m_pt;
				tempDC->MoveTo(m_oldpoint);
				tempDC->Ellipse(m_oldpoint.x-3,m_oldpoint.y-3,m_oldpoint.x+3,m_oldpoint.y+3);
				while(npclist->m_curposi->m_autoact[++i].m_state!=-1)
				{
					pt1=npclist->m_curposi->m_autoact[i].m_pt;
					tempDC->LineTo(pt1);
					tempDC->Ellipse(pt1.x-3,pt1.y-3,pt1.x+3,pt1.y+3);
				}
				tempDC->LineTo(m_oldpoint);
				tempDC->SelectObject(oldpen);

				tempDC->BitBlt(pt2.x,pt2.y,80,100,&MaskDC,0,0,SRCINVERT);
			}
			npclist->Next();
		}
	}
	
	CAreaList*	alist;
	CPointList*	list1;
	
	alist=&m_myscene.m_arealist;
	if(alist->m_head!=NULL)
	{
		alist->m_curposi=alist->m_head;
		while(alist->m_curposi!=NULL)
		{
			list1=&alist->m_curposi->m_pointlist;
			//draw  a area
			if(list1->m_head!=NULL)
			{
				//选择颜色
				CPen mypen,*oldpen;
				if(alist->m_curposi->m_statein>=10000 && alist->m_curposi->m_statein < 20000)
					color=m_attriblist.SearchID(10000);
				else
					color=m_attriblist.SearchID(alist->m_curposi->m_statein);
				mypen.CreatePen(PS_SOLID,1,color);
				
				oldpen=tempDC->SelectObject(&mypen);

				list1->m_curposi=list1->m_head;
				pt1=list1->m_curposi->mypt;
				tempDC->MoveTo(pt1);
				tempDC->Ellipse(pt1.x-3,pt1.y-3,pt1.x+3,pt1.y+3);
				list1->Next();
				while(list1->m_curposi!=NULL)
				{
					pt1=list1->m_curposi->mypt;
					tempDC->LineTo(pt1);
					tempDC->Ellipse(pt1.x-3,pt1.y-3,pt1.x+3,pt1.y+3);
					list1->Next();
				}
				pt2=list1->m_head->mypt;
				tempDC->LineTo(pt2);
				tempDC->SelectObject(oldpen);
			}//draw ok	
			
			alist->Next();
		}
	}

}



void CMapEditDoc::TransDraw(CDC* tempDC,int left,int top,byte bit[], int wide, int height, COLORREF cr)
{
	int i,j,blank,x,y;
	byte color[3];
	x=wide+left;
	y=height+top;
	for(i=y;i>top;i--)
	{
		for(j=left;j<x;j++)
		{
			color[0]=*bit++;
			color[1]=*bit++;
			color[2]=*bit++;
			if(!(int(color[2])<GetRValue(cr)+50 && int(color[2])>GetRValue(cr)-50) ||
				!(int(color[1])<GetGValue(cr)+50 && int(color[1])>GetGValue(cr)-50) ||
				!(int(color[0])<GetBValue(cr)+50 && int(color[0])>GetBValue(cr)-50))
				tempDC->SetPixel(j,i,RGB(color[2],color[1],color[0]));
		}
		blank=(wide*3%4);
		if(blank!=0) blank=4-blank;
		bit+=blank;
	}
}

void CMapEditDoc::TransDCtoDC(CDC* pDestDC, int dX, int dY, CDC* pSrcDC, int Width, int Height, int tp)
{         //tp==1时透明，在pDestDC上画   tp==0时从pDestDC 的(dx,dy)出拷贝块
	if(tp==1)
	{
		COLORREF color,cr;
		int r,g,b;
		color=pSrcDC->GetPixel(CPoint(0,0));
		r=GetRValue(color);
		g=GetGValue(color);
		b=GetBValue(color);
		
		for(int j=dY;j<Height+dY;j++)
		{
			for(int i=dX;i<Width+dX;i++)
			{
				cr=pSrcDC->GetPixel(CPoint(i,j));
				if(!(GetRValue(cr)>r-50 && GetRValue(cr)<r+50) ||
				   !(GetGValue(cr)>g-50 && GetGValue(cr)<g+50) ||
				   !(GetBValue(cr)>b-50 && GetBValue(cr)<b+50))
					pDestDC->SetPixel(i,j,cr);
			}
		}
		return;
	}
	if(tp==0)
	{
		pSrcDC->BitBlt(0,0,Width,Height,pDestDC,dX,dY,SRCCOPY);
	}
}

void CMapEditDoc::InitData()
{
	m_save=0;
	m_color=RGB(0,0,0);
	m_linecr=RGB(0,0,0);
	m_zoomin=m_zoomout=0.0f;
	m_modelin=false;
	m_modeltest=false;
	m_startth=false;
	m_starta=false;
	m_startp=false;
	m_startcover=false;
	m_state=0;
	m_mstate=0;
	m_addstate=0;
	m_mapbmpin=false;
	m_scenein=false;
	m_firsthit=false;
	m_qiehuanstart=false;
	m_newwupic=false;
	m_scenechange=false;
	SampleHb=NULL;
	m_oldpoint.x=m_oldpoint.y=0;
	m_daonei=-1;
	m_daowai=-1;
	m_mapSize.cx=m_mapSize.cy=m_samSize.cx=m_samSize.cy=100;
//	m_pDlgList=new CDlgList;
}

void CMapEditDoc::OnUpdateModelZoom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_scenechange);
}

void CMapEditDoc::OnFileSave() 
{
	if(strcmp(mapfilename,"")==0)
		OnFileSavescene();
	else
		SaveScene(mapfilename);
}

void CMapEditDoc::SaveScene(char path[])
{
	ofstream out;
	out.open(path,ios::out|ios::binary);
	if(out)
	{
		m_myscene.write(out);
		if(m_pDlgList!=NULL)
		m_pDlgList->write(out);
		if(m_pConditionList!=NULL)
		m_pConditionList->write(out);
		if(m_pEventList!=NULL)
		m_pEventList->write(out);
		out.close();
		m_scenechange=false;
		m_save=0;
	}
	else
	{
		AfxMessageBox("场景文件创建失败!!");
		out.close();
	}

}
