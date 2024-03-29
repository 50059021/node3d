#include "MainRoot.h"
#include "RenderSystem.h"
#include "IniFile.h"
#include "TextRender.h"

typedef CRenderSystem* (WINAPI * PFN_RENDER_SYSTEM_PLUG_CREATE_SYSTEM)();

CMainRoot::CMainRoot()
{
	{
#ifdef _DEBUG
		HMODULE hIns = LoadLibrary("RenderSystemDX9d.dll");
#else
		HMODULE hIns = LoadLibrary("RenderSystemDX9.dll");
#endif
		if (hIns)
		{
			PFN_RENDER_SYSTEM_PLUG_CREATE_SYSTEM pFunc = (PFN_RENDER_SYSTEM_PLUG_CREATE_SYSTEM)GetProcAddress(hIns, "RENDER_SYSTEM_PLUG_CREATE_SYSTEM");
			if (NULL==pFunc)
			{
				MessageBox(NULL,"Create render system failed!","Error",0);
				return;
			}
			m_pRenderSystem = pFunc();
			SetRenderSystem(m_pRenderSystem);
		}
		else
		{
			MessageBox(NULL,"Load \"RenderSystemDX9d.dll\" failed!","Error",0);
			return;
		}
	}
	//
	std::string strUIFilename = IniGetStr("UIEditorUI.cfg","UIConfig","file");
	std::string strTheme = IniGetStr("UIEditorUI.cfg","UIConfig","theme");
	std::string strThemeFilename = "Data\\Themes\\"+strTheme+"\\UIStyle.xml";
	UISetDialogRes(strUIFilename);
	GetStyleMgr().Create(strThemeFilename);

	std::string strLanguage = IniGetStr("UIEditorUI.cfg","UIConfig","language");
	std::string strFont1 = IniGetStr("Font.cfg",strLanguage.c_str(),"font1");
	GetTextRender().registerFont(L"font1",strFont1);
	UIGraph::InitFont(L"font1",12);
}

CMainRoot::~CMainRoot()
{
}

void CMainRoot::Run()
{
	RECT rc={0,0,800,500};
	CreateRenderWindow(L"UI编辑器", 800, 500);

	m_dlgMain.Create("IDD_MAIN");
	m_dlgView.Create("IDD_VIEW", &m_dlgMain);
	m_dlgUIList.Create("IDD_DIALOG_LIST", &m_dlgMain);

	m_dlgUIList.SetDlgView(&m_dlgView);
	std::string strEditUIFilename = IniGetStr("UIEditorUI.cfg","UIConfig","edit");
	m_dlgUIList.InitDialogListFromXML(strEditUIFilename);
	m_dlgUIList.createDialogStringFromXML(strEditUIFilename,"DialogString.ini");
	UISetDialogRes(strEditUIFilename);

	m_dlgMain.OnSize(rc);
	CRoot::Run();
}

void CMainRoot::OnFrameMove(double fTime, float fElapsedTime)
{
	CRoot::OnFrameMove(fTime, fElapsedTime);
	m_dlgMain.OnFrameMove(fTime, fElapsedTime);
}

void CMainRoot::OnFrameRender(double fTime, float fElapsedTime)
{
	if(m_pRenderSystem->BeginFrame())
	{
		m_pRenderSystem->SetupRenderState();
		m_pRenderSystem->ClearBuffer(true,true,0xFFFFFFFF);

			CRect<int> rcViewport;
			m_pRenderSystem->getViewport(rcViewport);
			Matrix mProjection;
			//R.getProjectionMatrix(mProjection);
			mProjection.MatrixPerspectiveFovLH(PI/4,(float)rcViewport.right/(float)rcViewport.bottom,0.1f,100);
			m_pRenderSystem->setProjectionMatrix(mProjection);

			float fZ = 50;
			Matrix mWorld=Matrix::newTranslation(Vec3D(-fZ/mProjection._11,fZ/mProjection._22,fZ))*
				Matrix::newScale(Vec3D(fZ/mProjection._11/rcViewport.right*2.0f,-fZ/mProjection._22/rcViewport.bottom*2.0f,1.0f));

		m_dlgMain.OnFrameRender(mWorld, fTime, fElapsedTime);
		m_pRenderSystem->EndFrame();
	}
	CRoot::OnFrameRender(fTime, fElapsedTime);
}


bool CMainRoot::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool bNoFurtherProcessing = m_dlgMain.MsgProc(hWnd, uMsg, wParam, lParam);
	return false;
}