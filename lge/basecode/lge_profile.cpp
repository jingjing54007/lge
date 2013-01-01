#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#else
#include <sys/timeb.h>
#endif
#include <assert.h>

#include "lge_platform.h"
#include "lge_util.h"
#include "lge_logger.h"
#include "lge_string_format.h"
#include "lge_profile.h"
#include "lge_sys_info.h"

#ifdef ENABLE_PROFILE

typedef struct {
   bool bValid;                 //Whether this data is valid
   unsigned int iProfileInstances;      //# of times ProfileBegin called
   int iOpenProfiles;           //# of times ProfileBegin w/o ProfileEnd
   char szName[MAX_PROFILE_NAME_LEN];            //Name of sample
   float fStartTime;            //The current open profile start time
   float fAccumulator;          //All samples this frame added together
   float fChildrenSampleTime;   //Time taken by all children
   unsigned int iNumParents;            //Number of profile parents
} ProfileSample;

typedef struct {
   bool bValid;        //Whether the data is valid
   char szName[MAX_PROFILE_NAME_LEN];   //Name of the sample
   float fAve;         //Average time per frame (percentage)
   float fMin;         //Minimum time per frame (percentage)
   float fMax;         //Maximum time per frame (percentage)
   float fAveCostTime;	// 平均耗时多长时间(ms)
   float fMaxCostTime;	// 最长耗时多长时间(ms)
   float fTimeOfMax;	// 耗时最长的时间点(ms)
} ProfileSampleHistory;

class TextBox {
public:
	TextBox(int x, int y, int w = 800, int h = 600);

private:
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	// Text Buffers
	char * buffer;
	char * drawBufferPtr;

	// Info
	int pageLineCnt;
	int scrollCnt;
	int currX;
	int currY;
public:
	unsigned int mode;
public:
	void Draw();
	void Printf(const char* fmt, ...);
	void Clear() {buffer[0] = '\0';};
	void SetMode(unsigned int modeIn) {mode = modeIn;};
	void PageUp() {scrollCnt += pageLineCnt;};
	void PageDown() {scrollCnt -= pageLineCnt; if (scrollCnt < 0) scrollCnt = 0;};
	void PageReset() {scrollCnt = 0;};

private:
	void Paginate();	
	void FormatStrCat(char * str);
};

#define PROFILE_SAMPLE_MAX_NUM 20


#define MAX_STR 4096

#define TEXT_NONE 0x00
#define TEXT_DRAW_BOX 0x04
#define TEXT_DRAW_SPACES 0x02
#define TEXT_WRAP_SPACES 0x08
#define TEXT_DRAW_BACKGROUND 0x01

ProfileSample g_samples[PROFILE_SAMPLE_MAX_NUM];
ProfileSampleHistory g_history[PROFILE_SAMPLE_MAX_NUM];

bool g_bEnableProfile = false;
float g_startProfile = 0.0f;
float g_endProfile = 0.0f;

#ifdef _WIN32
float g_StartTime = -1.0f;
#else
struct timeb	g_StartTimeb;
#endif
float g_CurrentTime = -1.0f;
float g_TimeLastTick = -1.0f;
TextBox* g_pTextBox = 0;

// =====================================================================================================================
// =======================================================================================================================
float GetExactTime( void )
{
#ifdef _WIN32
	return( ((float)timeGetTime())/1000.0f );
#else
	struct timeb tp;

	ftime(&tp);

	return tp.time - g_StartTimeb.time +
	  (tp.millitm/1000.0) - (g_StartTimeb.millitm/1000.0);
#endif
}

// =====================================================================================================================
// =======================================================================================================================
void ProfileInit( void )
{
   unsigned int i;

   for (i = 0; i < PROFILE_SAMPLE_MAX_NUM; i++) {
      g_samples[i].bValid = false;
      g_history[i].bValid = false;
   }

   g_startProfile = GetExactTime();

#ifdef _WIN32
	g_StartTime = ((float)timeGetTime()) / 1000.0f;
#else
	ftime(&g_StartTimeb);
#endif

	g_CurrentTime = 0.0f;
	g_TimeLastTick = 0.001f;


   g_pTextBox = new TextBox(400, 150);
   g_pTextBox->SetMode(TEXT_NONE);
}

// =====================================================================================================================
// =======================================================================================================================
int ProfileBegin(const char* name)
{
	if (!g_bEnableProfile) {
		return 0;
	}

   unsigned int i = 0;

   while( i < PROFILE_SAMPLE_MAX_NUM && g_samples[i].bValid == true ) {
      if( strcmp( g_samples[i].szName, name ) == 0 ) {
         //Found the sample
         g_samples[i].iOpenProfiles++;
         g_samples[i].iProfileInstances++;
         g_samples[i].fStartTime = GetExactTime();
         assert( g_samples[i].iOpenProfiles == 1 ); //max 1 open at once
         return i;
       }
       i++;	
   }

   strcpy( g_samples[i].szName, name );
   g_samples[i].bValid = true;
   g_samples[i].iOpenProfiles = 1;
   g_samples[i].iProfileInstances = 1;
   g_samples[i].fAccumulator = 0.0f;
   g_samples[i].fStartTime = GetExactTime();
   g_samples[i].fChildrenSampleTime = 0.0f;
   return i;
}

// =====================================================================================================================
// =======================================================================================================================
void ProfileEnd(const char* name )
{
	if (!g_bEnableProfile) {
		return;
	}

   unsigned int i = 0;
   unsigned int numParents = 0;

   while( i < PROFILE_SAMPLE_MAX_NUM && g_samples[i].bValid == true )
   {
      if( strcmp( g_samples[i].szName, name ) == 0 )
      {  //Found the sample
         unsigned int inner = 0;
         int parent = -1;
         float fEndTime = GetExactTime();
         g_samples[i].iOpenProfiles--;

         //Count all parents and find the immediate parent
         while( g_samples[inner].bValid == true ) {
            if( g_samples[inner].iOpenProfiles > 0 )
            {  //Found a parent (any open profiles are parents)
               numParents++;
               if( parent < 0 )
               {  //Replace invalid parent (index)
                  parent = inner;
               }
               else if( g_samples[inner].fStartTime >=
                        g_samples[parent].fStartTime )
               {  //Replace with more immediate parent
                  parent = inner;
               }
            }
            inner++;
         }

         //Remember the current number of parents of the sample
         g_samples[i].iNumParents = numParents;

         if( parent >= 0 )
         {  //Record this time in fChildrenSampleTime (add it in)
            g_samples[parent].fChildrenSampleTime += fEndTime -
                                                     g_samples[i].fStartTime;
         }

         //Save sample time in accumulator
         g_samples[i].fAccumulator += fEndTime - g_samples[i].fStartTime;
         return;
      }
      i++;	
   }
}

// =====================================================================================================================
// =======================================================================================================================
void StoreProfileInHistory(const char* name, float percent, float time)
{
   unsigned int i = 0;
   float oldRatio;
   float newRatio = 0.8f * g_TimeLastTick;
   if( newRatio > 1.0f ) {
      newRatio = 1.0f;
   }
   oldRatio = 1.0f - newRatio;
   
   float oldRatioMax = 0.0f;
   float newRatioMax = 0.2f * g_TimeLastTick;
   if (newRatioMax > 1.0f) {
		newRatioMax = 1.0f;
   }
   oldRatioMax = 1.0f - newRatioMax;

   while( i < PROFILE_SAMPLE_MAX_NUM && g_history[i].bValid == true ) {
      if( strcmp( g_history[i].szName, name ) == 0 )
      {  //Found the sample
         g_history[i].fAve = (g_history[i].fAve*oldRatio) + (percent*newRatio);
         if( percent < g_history[i].fMin ) {
            g_history[i].fMin = percent;
         }
         else {
            g_history[i].fMin = (g_history[i].fMin*oldRatio) + (percent*newRatio);
         }

         if( g_history[i].fMin < 0.0f ) {
            g_history[i].fMin = 0.0f;
		 }


         if( percent > g_history[i].fMax ) {
            g_history[i].fMax = percent;
         }
         else {
            g_history[i].fMax = (g_history[i].fMax*oldRatioMax) + (percent*newRatioMax);
         }
		 
		if (time > g_history[i].fMaxCostTime) {
			g_history[i].fMaxCostTime = time;
			g_history[i].fTimeOfMax = GetExactTime();
		}
		else {
			g_history[i].fMaxCostTime = (g_history[i].fMaxCostTime * oldRatioMax) + (time * newRatioMax);
		}
		
		g_history[i].fAveCostTime = g_history[i].fAveCostTime * oldRatio + time * newRatio;

		return;
      }
      i++;
   }

   if( i < PROFILE_SAMPLE_MAX_NUM )
   {  //Add to history
      strcpy( g_history[i].szName, name );
      g_history[i].bValid = true;
      g_history[i].fAve = g_history[i].fMin = g_history[i].fMax = percent;
	  g_history[i].fAveCostTime = g_history[i].fMaxCostTime = time;
	  g_history[i].fTimeOfMax = GetExactTime();
   }
   else {
      assert( !"Exceeded Max Available Profile Samples!");
   }
}

// =====================================================================================================================
// =======================================================================================================================
void GetProfileFromHistory(const char* name, float* ave, float* min, float* max, float* aveTime, float* maxTime, float* timeOfMax )
{
   unsigned int i = 0;
   while( i < PROFILE_SAMPLE_MAX_NUM && g_history[i].bValid == true ) {
      if( strcmp( g_history[i].szName, name ) == 0 )
	  {  //Found the sample
         *ave = g_history[i].fAve;
         *min = g_history[i].fMin;
         *max = g_history[i].fMax;
		 *aveTime = g_history[i].fAveCostTime;
		 *maxTime = g_history[i].fMaxCostTime;
		 *timeOfMax = g_history[i].fTimeOfMax;
         return;
	  }
      i++;
   }	
   *ave = *min = *max = *aveTime = *maxTime = 0.0f;
}

// =====================================================================================================================
// =======================================================================================================================
void ProfileDumpOutputToBuffer( void )
{
	if (!g_bEnableProfile || !g_pTextBox) {
		return;
	}

	g_TimeLastTick = GetExactTime() - g_CurrentTime;
	g_CurrentTime = GetExactTime();

	if( g_TimeLastTick <= 0.0f ) {
		g_TimeLastTick = 0.001f;
	}

   unsigned int i = 0;

   g_endProfile = GetExactTime();
   g_pTextBox->Clear();

   g_pTextBox->Printf( "CostT   :   AveT   :     MaxT   :    Ave    :   Max :   # : Profile Name\n" );
   g_pTextBox->Printf( "------------------------------------------------------------------------\n" );

   while( i < PROFILE_SAMPLE_MAX_NUM && g_samples[i].bValid == true ) {		
      unsigned int indent = 0;
      float sampleTime, percentTime, aveTime, minTime, maxTime, aveCostTime, maxCostTime, timeOM;
      char line[256], name[256], indentedName[256];
      char ave[16], min[16], max[16], num[16], aveCost[16], maxCost[16], cost[16], timeOfMax[16];
			
      if( g_samples[i].iOpenProfiles < 0 ) {
         assert( !"ProfileEnd() called without a ProfileBegin()" );	
      }
      else if( g_samples[i].iOpenProfiles > 0 ) {
         assert( !"ProfileBegin() called without a ProfileEnd()" );
      }

      sampleTime = g_samples[i].fAccumulator - g_samples[i].fChildrenSampleTime;
      percentTime = ( sampleTime / (g_endProfile - g_startProfile ) ) * 100.0f;

      aveTime = minTime = maxTime = percentTime;

      //Add new measurement into the history and get the ave, min, and max
      StoreProfileInHistory( g_samples[i].szName, percentTime,  g_samples[i].fAccumulator);
      GetProfileFromHistory( g_samples[i].szName, &aveTime, &minTime, &maxTime, &aveCostTime, &maxCostTime, &timeOM);

      //Format the data
      sprintf( ave, "%3.1f", aveTime );
      sprintf( min, "%3.1f", minTime );
      sprintf( max, "%3.1f", maxTime );
      sprintf( num, "%3d", g_samples[i].iProfileInstances );
	
	  sprintf(cost, "%3.1fms", g_samples[i].fAccumulator * 1000);
	  sprintf(aveCost, "%3.1fms", aveCostTime * 1000);
	  sprintf(maxCost, "%3.1fms", maxCostTime * 1000);
	  sprintf(timeOfMax, "%3.1fs", timeOM);

      strcpy( indentedName, g_samples[i].szName );

      for( indent=0; indent<g_samples[i].iNumParents; indent++ ) {
         sprintf( name, "   %s", indentedName );
         strcpy( indentedName, name );
      }

      sprintf(line,"%7s : %7s : %7s(%7s) : %7s : %7s : %3s : %s\n", cost, aveCost, maxCost, timeOfMax, ave, max, num, indentedName);
      g_pTextBox->Printf( line );	//Send the line to text buffer
      i++;
   }

   {  //Reset samples for next frame
      unsigned int i;
      for( i=0; i<PROFILE_SAMPLE_MAX_NUM; i++ ) {
         g_samples[i].bValid = false;
      }
      g_startProfile = GetExactTime();
   }
}

// =====================================================================================================================
// =======================================================================================================================
void ProfileDraw( void )
{
	if (!g_bEnableProfile) {
		return;
	}

   if( g_pTextBox ) {
		g_pTextBox->Draw();
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	数据显示
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FONT_WIDTH 8
#define FONT_HEIGHT 8

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TextBox::TextBox(int x, int y, int w, int h) {
	m_x = x;
	m_y = y;
	m_h = h;
	m_w = w;

	// Initialize the Buffers and Pointers
	buffer = (char *)malloc(MAX_STR);
	buffer[0] = '\0';
	drawBufferPtr = buffer;
	// Calculate the number of lines per Page
	pageLineCnt = h / FONT_HEIGHT;
	scrollCnt = 0;
	currX = x;

	// Set Mode
	mode = 0;
}

//---------------------------------------------------------------------------
// Draw the Text given to TextBoxPrintf()
//---------------------------------------------------------------------------
void TextBox::Draw() {
	Paginate();
//	CMyBitmap::ShowStringCommon(m_x, m_y, 0xffff00ff, drawBufferPtr, pFontInfo->szGuiFont, 14);
}

//---------------------------------------------------------------------------
// This function will concatinate a formated string the a TextBox
//---------------------------------------------------------------------------
void TextBox::FormatStrCat(char * str) {
	char buff[MAX_STR];
	char buff2[MAX_STR];
	char * cP;
	char * cP2;

	strcpy(buff, str);
	cP = buff;

	// Format String for caption
	// Parse the String
	while (*cP != '\0') {
		// Visible characters
		if ( ' ' <= *cP && *cP <= '~' ) {
			currX += FONT_WIDTH;
		}
		else if ( *cP == '\n' ) {
			currX = m_x; 
		}

		// Wrap 
		if (currX >= m_x + m_w) {
			cP++;
			// Find the last space
			if (mode & TEXT_WRAP_SPACES) {
				while(cP > buff && *cP != ' ') cP--;
			}
			strcpy(buff2, cP);
			*cP++ = '\n';
			*cP = '\0';
			// Eliminate Space
			if (mode & TEXT_WRAP_SPACES && buff2[0] == ' ') cP2 = &buff2[1];
			else cP2 = buff2;
			strcat(cP, cP2);
			currX = m_x;
		} 
		else {
			cP++;
		}
	}

	// Make sure it fits in the text buffer by removing
	// strings at the top of the buffer.
	cP = buffer;
	while (strlen(cP) + strlen(buff) > MAX_STR) {
		cP = strchr(cP, '\n');
		if( !cP ) {
			assert( !"TextBox::FormatStrCat: string too long!!!" );
		}
		cP++;
	}
	// If there are strings that need to be removed. Do so.
	if (cP != buffer) {
		strcpy(buff2, cP);
		strcpy(buffer, buff2);
	}
	// Now there is space. So, concatinate.
	strcat(buffer, buff); 
}

//---------------------------------------------------------------------------
// Paginate the text Box
//---------------------------------------------------------------------------
void TextBox::Paginate() {
	int newLineCnt = 0;
	int pageNewLineCnt;
	char * cP;

	// Calculate the number of new lines from the bottom we want
	pageNewLineCnt = pageLineCnt + scrollCnt;

	// Starting at the end of the string count the number of newlines backwards
	cP = strchr(buffer, '\0');
	while(cP > buffer) {
		if(*cP == '\n') newLineCnt++;
		if (newLineCnt == pageNewLineCnt) {
			cP++;
			break;
		}
		cP--;
	}
	if (cP == buffer && newLineCnt > pageLineCnt) 
		scrollCnt = newLineCnt - pageLineCnt + 1;

	drawBufferPtr = cP;
}

//---------------------------------------------------------------------------
// Printf
//---------------------------------------------------------------------------
void TextBox::Printf(const char* fmt, ... ) {
	va_list  vlist;
	char buff[MAX_STR];

	// Get output string
	va_start(vlist, fmt);
	vsprintf(buff, fmt, vlist);

	FormatStrCat(buff);

	va_end(vlist);
}

// =====================================================================================================================
// =======================================================================================================================
CSimpleProfiler::CSimpleProfiler(const char* pszName)
{
	m_idProfiler = 0;

	if (g_bEnableProfile) {
		m_idProfiler = ProfileBegin(pszName);
	}
}

// =====================================================================================================================
// =======================================================================================================================
CSimpleProfiler::~CSimpleProfiler()
{
	if (g_bEnableProfile) {
		ProfileEnd(g_samples[m_idProfiler].szName);
	}
}

// =====================================================================================================================
// =======================================================================================================================
TimeLogger::TimeLogger(const char* name)
{
    m_name = name;
    m_startTime = TimeGet();
}

// =====================================================================================================================
// =======================================================================================================================
TimeLogger::~TimeLogger()
{
    uint32 costTime = TimeGet() - m_startTime;
    LogMsg("%s  cost  %dms", m_name.c_str(), costTime);
}

// =====================================================================================================================
// =======================================================================================================================
void BeginProfile()
{
	g_bEnableProfile = true;
	ProfileInit();
}

// =====================================================================================================================
// =======================================================================================================================
void EndProfile()
{
	g_bEnableProfile = false;
}

#endif

