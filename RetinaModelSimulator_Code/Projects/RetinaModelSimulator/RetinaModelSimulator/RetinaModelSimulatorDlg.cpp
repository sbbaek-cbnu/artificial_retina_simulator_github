
// RetinaModelSimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RetinaModelSimulator.h"
#include "RetinaModelSimulatorDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)	
END_MESSAGE_MAP()


// CRetinaModelSimulatorDlg dialog




CRetinaModelSimulatorDlg::CRetinaModelSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRetinaModelSimulatorDlg::IDD, pParent)
	, m_RadioPath(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nLen = 0;

	t_fstart = 0.0f;
	t_fend = 0.0f;
	t_fstep = 0.0f;
	flightintensity = 0.0f;
	flightintensity_cone = 0.0f;
	flightduration = 0.0f;
	flightstart = 0.0f;
	simulationsw_dual = 0;
	simulationsw_rod = 0;
	simulationsw_cone = 0;
	m_bThreadFlag = 1;
	simulationstop = 0;
}

void CRetinaModelSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_RadioPath);
	DDX_Control(pDX, IDC_EDIT2, t_start);
	DDX_Control(pDX, IDC_EDIT3, t_end);
	DDX_Control(pDX, IDC_EDIT4, t_step);
	DDX_Control(pDX, IDC_EDIT5, lightintensity);
	DDX_Control(pDX, IDC_EDIT6, lightintensity_cone);
	DDX_Control(pDX, IDC_EDIT7, lightstart);
	DDX_Control(pDX, IDC_EDIT8, lightduration);
	DDX_Control(pDX, IDC_COMBO1, parameter_cell);
	DDX_Control(pDX, IDC_EDIT9, mcap);
	DDX_Control(pDX, IDC_PROGRESS1, progress);
	DDX_Control(pDX, IDC_figure, m_pictu);
	DDX_Control(pDX, IDC_EDIT10, conduct);
	DDX_Control(pDX, IDC_EDIT1, msgboard);
	DDX_Control(pDX, IDC_EDIT12, revpotential);
	DDX_Control(pDX, IDC_EDIT17, conduct_ion);
	//  DDX_Control(pDX, IDC_EDIT13, threshold);
	DDX_Control(pDX, IDC_EDIT14, slope);
	DDX_Control(pDX, IDC_EDIT15, tconstant);
	DDX_Control(pDX, IDC_COMBO4, parameter_synapse);
	DDX_Control(pDX, IDC_EDIT13, revpotential_synapse);
	DDX_Control(pDX, IDC_COMBO2, ionselection);
//	DDX_Control(pDX, IDC_COMBO3, cellselection_graph);
}

BEGIN_MESSAGE_MAP(CRetinaModelSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRetinaModelSimulatorDlg::OnBnClickedOk)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO1,IDC_RADIO3,OnBnClickedRadio) //path 선택 라디오 버튼 그룹화
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRetinaModelSimulatorDlg::OnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &CRetinaModelSimulatorDlg::OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CRetinaModelSimulatorDlg::OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CRetinaModelSimulatorDlg::OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CRetinaModelSimulatorDlg::OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CRetinaModelSimulatorDlg::OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CRetinaModelSimulatorDlg::OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CRetinaModelSimulatorDlg::OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CRetinaModelSimulatorDlg::OnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CRetinaModelSimulatorDlg::OnChangeEdit10)
	ON_BN_CLICKED(IDC_BUTTON1, &CRetinaModelSimulatorDlg::OnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CRetinaModelSimulatorDlg::OnSelchangeCombo4)
	ON_EN_CHANGE(IDC_EDIT12, &CRetinaModelSimulatorDlg::OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &CRetinaModelSimulatorDlg::OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &CRetinaModelSimulatorDlg::OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &CRetinaModelSimulatorDlg::OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT17, &CRetinaModelSimulatorDlg::OnChangeEdit17)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRetinaModelSimulatorDlg::OnSelchangeCombo2)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CRetinaModelSimulatorDlg::OnClickedButton2)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CRetinaModelSimulatorDlg message handlers

BOOL CRetinaModelSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//edit box initialization
	t_start.SetWindowTextA("0");
	t_end.SetWindowTextA("10");
	t_step.SetWindowTextA("0.00001");
	lightintensity.SetWindowTextA("100");
	lightintensity_cone.SetWindowTextA("50000");
	lightstart.SetWindowTextA("1");
	lightduration.SetWindowTextA("0.02");

	//combo box initialization
	OnBnClickedRadio(0);

	//dialog size initialization
	//this->SetWindowPos(NULL,0,0,1380,690,SWP_NOMOVE);
	
	//cell, ion channel, and synapse parameters initialization
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<6;j++)
		{
			cellvalue[i][j]=0.0;
		}
	}

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<6;j++)
		{
			for(int k=0;k<4;k++)
			{
				synapsevalue[i][j][k]=0.0;
			}
		}
	}

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<6;j++)
		{
			for(int k=0;k<6;k++)
			{
				for(int l=0;l<2;l++)
				{
					ionvalue[i][j][k][l]=0.0;
				}
			}
		}
	}

	cellvalue[0][0]=0.02; //rod
	cellvalue[0][1]=0.01; //rod bipolar
	cellvalue[0][2]=1; //ganglion

	synapsevalue[0][0][0]=2.56; //chemical synapse (r-rb)
	synapsevalue[0][0][1]=0.0; //reversal potential
	synapsevalue[0][0][2]=20.0; //slope
	synapsevalue[0][0][3]=0.01; //time constant
	synapsevalue[0][1][0]=2.56; //chemical synapse (rb-g)
	synapsevalue[0][1][1]=0.0; //reversal potential
	synapsevalue[0][1][2]=20.0; //slope
	synapsevalue[0][1][3]=0.01; //time constant

	cellvalue[1][0]=10; //cone
	cellvalue[1][1]=0.01; //cone bipolar
	cellvalue[1][2]=1; //ganglion

	synapsevalue[1][0][0]=2.56; //chemical synapse (c-cb)
	synapsevalue[1][0][1]=0.0; //reversal potential
	synapsevalue[1][0][2]=20.0; //slope
	synapsevalue[1][0][3]=0.01; //time constant
	synapsevalue[1][1][0]=2.56; //chemical synapse (cb-g)
	synapsevalue[1][1][1]=0.0; //reversal potential
	synapsevalue[1][1][2]=20.0; //slope
	synapsevalue[1][1][3]=0.01; //time constant

	cellvalue[2][0]=0.02; //rod
	cellvalue[2][1]=10; //cone
	cellvalue[2][2]=0.01; //rod bipolar
	cellvalue[2][3]=0.01; //cone bipolar
	cellvalue[2][4]=20; //amacrine
	cellvalue[2][5]=1; //ganglion

	synapsevalue[2][0][0]=0.2; //electrical synapse (r-c)
	synapsevalue[2][0][1]=0.0;
	synapsevalue[2][0][2]=0.0;
	synapsevalue[2][0][3]=0.0;
	synapsevalue[2][1][0]=2.56; //chemical synapse(r-rb)
	synapsevalue[2][1][1]=0.0; //reversal potential
	synapsevalue[2][1][2]=20.0; //slope
	synapsevalue[2][1][3]=0.01; //time constant
	synapsevalue[2][2][0]=2.56; //chemical synapse(c-cb)
	synapsevalue[2][2][1]=0.0; //reversal potential
	synapsevalue[2][2][2]=20.0; //slope
	synapsevalue[2][2][3]=0.01; //time constant
	synapsevalue[2][3][0]=1.2; //chemical synapse(rb-a)
	synapsevalue[2][3][1]=-10.0; //reversal potential
	synapsevalue[2][3][2]=20.0; //slope
	synapsevalue[2][3][3]=0.01; //time constant
	synapsevalue[2][4][0]=0.2; //electrical synapse(a-cb)
	synapsevalue[2][4][1]=0.0;
	synapsevalue[2][4][2]=0.0;
	synapsevalue[2][4][3]=0.0;
	synapsevalue[2][5][0]=2.56; //chemical synapse(cb-g)
	synapsevalue[2][5][1]=0.0; //reversal potential
	synapsevalue[2][5][2]=20.0; //slope
	synapsevalue[2][5][3]=0.01; //time constant

	//ion channel parameters initialization
	//rod cell
	ionvalue[0][0][0][0]=3.0;
	ionvalue[0][0][0][1]=-32.0;
	ionvalue[0][0][1][0]=2.0;
	ionvalue[0][0][1][1]=-74.0;
	ionvalue[0][0][2][0]=0.7;
	ionvalue[0][0][3][0]=2.0;
	ionvalue[0][0][3][1]=-20.0;
	ionvalue[0][0][4][0]=5.0;
	ionvalue[0][0][4][1]=-74.0;
	ionvalue[0][0][5][0]=0.35;
	ionvalue[0][0][5][1]=-77.0;
	ionvalue[2][0][0][0]=3.0;
	ionvalue[2][0][0][1]=-32.0;
	ionvalue[2][0][1][0]=2.0;
	ionvalue[2][0][1][1]=-74.0;
	ionvalue[2][0][2][0]=0.7;
	ionvalue[2][0][3][0]=2.0;
	ionvalue[2][0][3][1]=-20.0;
	ionvalue[2][0][4][0]=5.0;
	ionvalue[2][0][4][1]=-74.0;
	ionvalue[2][0][5][0]=0.35;
	ionvalue[2][0][5][1]=-77.0;
	//cone cell
	ionvalue[1][0][0][0]=0.2; //gf_peak
	ionvalue[1][0][1][0]=0.7; //gi_peak
	ionvalue[1][0][2][1]=-72; //e_c
	ionvalue[2][1][0][0]=0.2; //gf_peak
	ionvalue[2][1][1][0]=0.7; //gi_peak
	ionvalue[2][1][2][1]=-72; //e_c
	//rod bipolar cell
	ionvalue[0][1][0][0]=0.975;
	ionvalue[0][1][0][1]=-17.7;
	ionvalue[0][1][1][0]=2.0;
	ionvalue[0][1][1][1]=-58.0;
	ionvalue[0][1][2][0]=50.0;
	ionvalue[0][1][2][1]=-58.0;
	ionvalue[0][1][3][0]=1.1;
	ionvalue[0][1][4][0]=8.5;
	ionvalue[0][1][4][1]=-58.0;
	ionvalue[0][1][5][0]=0.23;
	ionvalue[0][1][5][1]=-21.0;
	ionvalue[2][2][0][0]=0.975;
	ionvalue[2][2][0][1]=-17.7;
	ionvalue[2][2][1][0]=2.0;
	ionvalue[2][2][1][1]=-58.0;
	ionvalue[2][2][2][0]=50.0;
	ionvalue[2][2][2][1]=-58.0;
	ionvalue[2][2][3][0]=1.1;
	ionvalue[2][2][4][0]=8.5;
	ionvalue[2][2][4][1]=-58.0;
	ionvalue[2][2][5][0]=0.23;
	ionvalue[2][2][5][1]=-21.0;
	//cone bipolar cell
	ionvalue[1][1][0][0]=0.975;
	ionvalue[1][1][0][1]=-17.7;
	ionvalue[1][1][1][0]=2.0;
	ionvalue[1][1][1][1]=-58.0;
	ionvalue[1][1][2][0]=50.0;
	ionvalue[1][1][2][1]=-58.0;
	ionvalue[1][1][3][0]=1.1;
	ionvalue[1][1][4][0]=8.5;
	ionvalue[1][1][4][1]=-58.0;
	ionvalue[1][1][5][0]=0.23;
	ionvalue[1][1][5][1]=-21.0;
	ionvalue[2][3][0][0]=0.975;
	ionvalue[2][3][0][1]=-17.7;
	ionvalue[2][3][1][0]=2.0;
	ionvalue[2][3][1][1]=-58.0;
	ionvalue[2][3][2][0]=50.0;
	ionvalue[2][3][2][1]=-58.0;
	ionvalue[2][3][3][0]=1.1;
	ionvalue[2][3][4][0]=8.5;
	ionvalue[2][3][4][1]=-58.0;
	ionvalue[2][3][5][0]=0.23;
	ionvalue[2][3][5][1]=-21.0;
	//amacrine cell
	ionvalue[2][4][0][0]=4.0;
	ionvalue[2][4][0][1]=40.0;
	ionvalue[2][4][1][0]=0.4;
	ionvalue[2][4][1][1]=-80.0;
	ionvalue[2][4][2][0]=0.46;
	ionvalue[2][4][2][1]=-54.0;
	//ganglion cell
	ionvalue[0][2][0][0]=50.0;
	ionvalue[0][2][0][1]=35.0;
	ionvalue[0][2][1][0]=2.2;
	ionvalue[0][2][2][0]=12.0;
	ionvalue[0][2][2][1]=-75.0;
	ionvalue[0][2][3][0]=0.05;
	ionvalue[0][2][3][1]=-75.0;
	ionvalue[0][2][4][0]=36.0;
	ionvalue[0][2][4][1]=-75.0;
	ionvalue[0][2][5][0]=0.05;
	ionvalue[0][2][5][1]=-62.0;
	ionvalue[1][2][0][0]=50.0;
	ionvalue[1][2][0][1]=35.0;
	ionvalue[1][2][1][0]=2.2;
	ionvalue[1][2][2][0]=12.0;
	ionvalue[1][2][2][1]=-75.0;
	ionvalue[1][2][3][0]=0.05;
	ionvalue[1][2][3][1]=-75.0;
	ionvalue[1][2][4][0]=36.0;
	ionvalue[1][2][4][1]=-75.0;
	ionvalue[1][2][5][0]=0.05;
	ionvalue[1][2][5][1]=-62.0;
	ionvalue[2][5][0][0]=50.0;
	ionvalue[2][5][0][1]=35.0;
	ionvalue[2][5][1][0]=2.2;
	ionvalue[2][5][2][0]=12.0;
	ionvalue[2][5][2][1]=-75.0;
	ionvalue[2][5][3][0]=0.05;
	ionvalue[2][5][3][1]=-75.0;
	ionvalue[2][5][4][0]=36.0;
	ionvalue[2][5][4][1]=-75.0;
	ionvalue[2][5][5][0]=0.05;
	ionvalue[2][5][5][1]=-62.0;

	OnSelchangeCombo1();
	OnSelchangeCombo2();
	OnSelchangeCombo4();

	//msgboard buffer set to maximum
	msgboard.SetLimitText(0);

	checkfp=0;

	ReplaceMsgBoard("Initialization Succeeded.");	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

int CRetinaModelSimulatorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//Create Thread
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(ThreadFirst, NULL);

	if(p1 == NULL)
	{
		AfxMessageBox("Thread Initialization Failed.");
		exit(0);
	}
	ReplaceMsgBoard("Thread Initialization Succeeded.");
	//CloseHandle(p1);

	return 0;
}

void CRetinaModelSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRetinaModelSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);	
	}
	else
	{

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRetinaModelSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRetinaModelSimulatorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	CString t_cstart;
	CString t_cend;
	CString t_cstep;
	CString clightintensity;
	CString clightintensity_cone;
	CString clightduration;
	CString clightstart;

	UpdateData(TRUE);
	//edit box value 가져오기
	t_start.GetWindowTextA(t_cstart);
	t_end.GetWindowTextA(t_cend);
	t_step.GetWindowTextA(t_cstep);
	lightintensity.GetWindowTextA(clightintensity);
	lightintensity_cone.GetWindowTextA(clightintensity_cone);
	lightduration.GetWindowTextA(clightduration);
	lightstart.GetWindowTextA(clightstart);

	//가져온 value를 float로 변환
	t_fstart=atof(t_cstart.GetString());
	t_fend=atof(t_cend.GetString());
	t_fstep=atof(t_cstep.GetString());
	flightintensity=atof(clightintensity.GetString());
	flightintensity_cone=atof(clightintensity_cone.GetString());
	flightduration=atof(clightduration.GetString());
	flightstart=atof(clightstart.GetString());
	
	if(m_RadioPath==0 && simulationsw_dual==0 && simulationsw_rod==0 && simulationsw_cone==0) //Rod path simulation run
	{
		progress.SetRange(0,100);
		progress.SetPos(0);
		progress.SetStep(1);

		simulationsw_rod=1;
	}
	else if(m_RadioPath==1 && simulationsw_dual==0 && simulationsw_rod==0 && simulationsw_cone==0) //Cone path simulation run
	{	
		progress.SetRange(0,100);
		progress.SetPos(0);
		progress.SetStep(1);

		simulationsw_cone=1;
	}
	else if(m_RadioPath==2 && simulationsw_dual==0 && simulationsw_rod==0 && simulationsw_cone==0) //Dual path simulation run
	{		
		progress.SetRange(0,100);
		progress.SetPos(0);
		progress.SetStep(1);

		simulationsw_dual=1; // start
	}

	//CDialogEx::OnOK();
}


void CRetinaModelSimulatorDlg::OnBnClickedRadio(UINT msg) // path 선택
{
	UpdateData(TRUE); //인덱스 값 업데이트

	if(m_RadioPath==0) //rod path
	{
		//combo box control
		parameter_cell.ResetContent();
		parameter_cell.AddString("Rod Cell");		
		parameter_cell.AddString("Rod Bipolar Cell");
		parameter_cell.AddString("Ganglion Cell");

		parameter_synapse.ResetContent();
		parameter_synapse.AddString("Chemical Synapse (R-RB)");
		parameter_synapse.AddString("Chemical Synapse (RB-G)");
		
		parameter_cell.SetCurSel(0);
		parameter_synapse.SetCurSel(0);

		//picture control 
		HBITMAP hBitmap=NULL;		
		hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_rodpath),IMAGE_BITMAP,300,330,LR_LOADMAP3DCOLORS);
		m_pictu.SetBitmap(hBitmap);
		if(!hBitmap)::CloseHandle(hBitmap);

		//light intensity edit box able/disable
		lightintensity.EnableWindow(TRUE);
		lightintensity_cone.EnableWindow(FALSE);

		OnSelchangeCombo1();
		OnSelchangeCombo4();
	}
	else if(m_RadioPath==1) //cone path
	{
		//combo box control
		parameter_cell.ResetContent();
		parameter_cell.AddString("Cone Cell");
		parameter_cell.AddString("Cone Bipolar Cell");
		parameter_cell.AddString("Ganglion Cell");

		parameter_synapse.ResetContent();
		parameter_synapse.AddString("Chemical Synapse (C-CB)");		
		parameter_synapse.AddString("Chemical Synapse (CB-G)");
		
		parameter_cell.SetCurSel(0);
		parameter_synapse.SetCurSel(0);
		
		//picture control 
		HBITMAP hBitmap=NULL;		
		hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_conepath),IMAGE_BITMAP,300,330,LR_LOADMAP3DCOLORS);
		m_pictu.SetBitmap(hBitmap);
		if(!hBitmap)::CloseHandle(hBitmap);

		//light intensity edit box able/disable
		lightintensity.EnableWindow(FALSE);
		lightintensity_cone.EnableWindow(TRUE);

		OnSelchangeCombo1();
		OnSelchangeCombo4();
	}
	else if(m_RadioPath==2) //dual path
	{
		//combo box control
		parameter_cell.ResetContent();
		parameter_cell.AddString("Rod Cell");
		parameter_cell.AddString("Cone Cell");
		parameter_cell.AddString("Rod Bipolar Cell");
		parameter_cell.AddString("Cone Bipolar Cell");
		parameter_cell.AddString("Amacrine Cell");
		parameter_cell.AddString("Ganglion Cell");

		parameter_synapse.ResetContent();
		parameter_synapse.AddString("Electrical Synapse (R-C)");		
		parameter_synapse.AddString("Chemical Synapse (R-RB)");		
		parameter_synapse.AddString("Chemical Synapse (C-CB)");		
		parameter_synapse.AddString("Chemical Synapse (RB-A)");
		parameter_synapse.AddString("Electrical Synapse (CB-A)");		
		parameter_synapse.AddString("Chemical Synapse (CB-G)");
		
		parameter_cell.SetCurSel(0);
		parameter_synapse.SetCurSel(0);

		//picture control 
		HBITMAP hBitmap=NULL;
		hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_dualpath),IMAGE_BITMAP,300,330,LR_LOADMAP3DCOLORS);
		m_pictu.SetBitmap(hBitmap);
		if(!hBitmap)::CloseHandle(hBitmap);

		//light intensity edit box able/disable
		lightintensity.EnableWindow(TRUE);
		lightintensity_cone.EnableWindow(TRUE);

		OnSelchangeCombo1();
		OnSelchangeCombo4();
	}
	else //else
	{
		parameter_cell.ResetContent();
		parameter_synapse.ResetContent();
	}
}
UINT CRetinaModelSimulatorDlg::ThreadFirst(LPVOID _mothod)
{
	CRetinaModelSimulatorDlg *fir  = (CRetinaModelSimulatorDlg*)_mothod;
	CRetinaModelSimulatorDlg* pDlg = (CRetinaModelSimulatorDlg*)AfxGetApp()->m_pMainWnd;

	while(pDlg->m_bThreadFlag)
	{
		if(pDlg->simulationsw_dual==1 && pDlg->simulationsw_rod==0 && pDlg->simulationsw_cone==0)
		{
			pDlg->simulationsw_dual=2; //on progress

			pDlg->DualPathSimulation();			
		}		
		else if(pDlg->simulationsw_rod==1 && pDlg->simulationsw_dual==0 && pDlg->simulationsw_cone==0)
		{
			pDlg->simulationsw_rod=2;

			pDlg->RodPathSimulation();	
		}
		else if(pDlg->simulationsw_cone==1 && pDlg->simulationsw_dual==0 && pDlg->simulationsw_rod==0)
		{
			pDlg->simulationsw_cone=2;

			pDlg->ConePathSimulation();	
		}
		Sleep(1000);
	}	
	
	return 0;
}

void CRetinaModelSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
		
	CDialogEx::OnTimer(nIDEvent);
}

void CRetinaModelSimulatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString msg;
	msg.Format("Coordinate: %d,%d",point.x,point.y);
	//AfxMessageBox(msg);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CRetinaModelSimulatorDlg::OnSelchangeCombo1() //combobox cursel_cell이 바뀔때
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int cursel_cell    = parameter_cell.GetCurSel();
	CString floatstring;
		
	floatstring.Format(_T("%.3f"),cellvalue[m_RadioPath][cursel_cell]);
	mcap.SetWindowTextA(floatstring);	

	if(m_RadioPath==0)//rod path
	{
		SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		SetDlgItemText(IDC_STATIC_MC_UNIT,"[nF]");

		SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
		SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[nS]");

		if(cursel_cell==0) //rod
		{
			ionselection.ResetContent();	
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Chloride Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);
		}
		else if(cursel_cell==1) //rod bipolar
		{
			ionselection.ResetContent();
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Transient Outward Current");			
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[pF]");
		}
		else if(cursel_cell==2) //ganglion
		{
			ionselection.ResetContent();
			ionselection.AddString("Sodium Current");
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("A Type Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[uF/\ncm2]");
			SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
			SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[mS/\ncm2]");
		}
		else
		{
			ionselection.ResetContent();
		}
	}
	else if(m_RadioPath==1) //cone path
	{
		SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		SetDlgItemText(IDC_STATIC_MC_UNIT,"[nF]");

		SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
		SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[nS]");

		if(cursel_cell==0) //cone
		{
			ionselection.ResetContent();
			ionselection.AddString("G_f Channel Current");
			ionselection.AddString("G_i Channel Current");
			ionselection.AddString("Static Channel Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Time Constant (C/g)");
			SetDlgItemText(IDC_STATIC_MC_UNIT,"[ms]");

			SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Time Constant");
			SetDlgItemText(IDC_STATIC_MC_ION_UNIT," ");
		}
		else if(cursel_cell==1) //cone bipolar
		{
			ionselection.ResetContent();
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Transient Outward Current");			
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);
			
			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[pF]");
		}
		else if(cursel_cell==2) //ganglion
		{
			ionselection.ResetContent();
			ionselection.AddString("Sodium Current");
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("A Type Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[uF/\ncm2]");
			SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
			SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[mS/\ncm2]");
		}
		else
		{
			ionselection.ResetContent();
		}
	}
	else if(m_RadioPath==2) //dual path
	{
		SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		SetDlgItemText(IDC_STATIC_MC_UNIT,"[nF]");

		SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
		SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[nS]");

		if(cursel_cell==0) //rod
		{
			ionselection.ResetContent();	
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Chloride Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);
		}
		else if(cursel_cell==1) //cone
		{
			ionselection.ResetContent();
			ionselection.AddString("G_f Channel Current");
			ionselection.AddString("G_i Channel Current");
			ionselection.AddString("Static Channel Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Time Constant (C/g)");
			SetDlgItemText(IDC_STATIC_MC_UNIT,"[ms]");

			SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Time Constant");
			SetDlgItemText(IDC_STATIC_MC_ION_UNIT," ");
		}
		else if(cursel_cell==2) //rod bipolar
		{
			ionselection.ResetContent();
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Transient Outward Current");			
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[pF]");
		}
		else if(cursel_cell==3) //cone bipolar
		{
			ionselection.ResetContent();
			ionselection.AddString("Hyperpolarization Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Transient Outward Current");			
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[pF]");
		}
		else if(cursel_cell==4) //amacrine
		{
			ionselection.ResetContent();
			ionselection.AddString("Sodium Current");
			ionselection.AddString("Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[pF]");
		}
		else if(cursel_cell==5) //ganglion
		{
			ionselection.ResetContent();
			ionselection.AddString("Sodium Current");
			ionselection.AddString("Calcium Current");
			ionselection.AddString("Delayed Rectifier Current");
			ionselection.AddString("Calcium-Potassium Current");
			ionselection.AddString("A Type Potassium Current");
			ionselection.AddString("Leakage Current");
			ionselection.SetCurSel(0);

			SetDlgItemText(IDC_STATIC_MC,"Membrane Capacitance");
		    SetDlgItemText(IDC_STATIC_MC_UNIT,"[uF/\ncm2]");
			SetDlgItemText(IDC_STATIC_MC_ION,"Maximum Conductance");
			SetDlgItemText(IDC_STATIC_MC_ION_UNIT,"[mS/\ncm2]");
		}
	}
	else
	{
		ionselection.ResetContent();
	}

	OnSelchangeCombo2();
}

void CRetinaModelSimulatorDlg::OnSelchangeCombo4() //combobox cursel_synapse가 바뀔때
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	int cursel_synapse = parameter_synapse.GetCurSel();
	CString floatstring;
	CString floatstring2;
	CString floatstring3;
	CString floatstring4;

	floatstring.Format(_T("%.3f"),synapsevalue[m_RadioPath][cursel_synapse][0]);
	floatstring2.Format(_T("%.3f"),synapsevalue[m_RadioPath][cursel_synapse][1]);
	floatstring3.Format(_T("%.3f"),synapsevalue[m_RadioPath][cursel_synapse][2]);
	floatstring4.Format(_T("%.3f"),synapsevalue[m_RadioPath][cursel_synapse][3]);

	conduct.SetWindowTextA(floatstring);
	revpotential_synapse.SetWindowTextA(floatstring2);
	slope.SetWindowTextA(floatstring3);
	tconstant.SetWindowTextA(floatstring4);

	if((cursel_synapse==0 || cursel_synapse==4) && m_RadioPath==2)
	{
		revpotential_synapse.SetWindowTextA("Unavailable");
		slope.SetWindowTextA("Unavailable");
		tconstant.SetWindowTextA("Unavailable");
		revpotential_synapse.EnableWindow(FALSE);
		slope.EnableWindow(FALSE);
		tconstant.EnableWindow(FALSE);
	}
	else
	{
		revpotential_synapse.EnableWindow(TRUE);
		slope.EnableWindow(TRUE);
		tconstant.EnableWindow(TRUE);
	}

}

void CRetinaModelSimulatorDlg::ReplaceMsgBoard(CString msg)
{
	//msgbox initialzation
	CString currentTimeText;
	SYSTEMTIME CurTime;
	::GetLocalTime(&CurTime);

	nLen=msgboard.GetWindowTextLength();
	msgboard.SetSel(nLen,nLen);
	currentTimeText.Format("(%d:%d:%d) ",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
	msgboard.ReplaceSel(currentTimeText);

	nLen=msgboard.GetWindowTextLength();
	msgboard.SetSel(nLen,nLen);
	msgboard.ReplaceSel(msg);

	nLen=msgboard.GetWindowTextLength();
	msgboard.SetSel(nLen,nLen);
	msgboard.ReplaceSel("\n");
}


void CRetinaModelSimulatorDlg::OnChangeEdit2() //When value of T_start changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	t_start.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 0)
	{
		AfxMessageBox("Out of bound error!");
		t_start.SetWindowTextA("0");
	}

}


void CRetinaModelSimulatorDlg::OnChangeEdit3() //When value of T_end changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	t_end.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 0)
	{
		AfxMessageBox("Out of bound error!");
		t_end.SetWindowTextA("10");
	}

}


void CRetinaModelSimulatorDlg::OnChangeEdit4() //When value of T_step changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	t_step.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp >= 1 || ttemp <= 0)
	{
		AfxMessageBox("Out of bound error!");
		t_step.SetWindowTextA("0.00001");
	}
}


void CRetinaModelSimulatorDlg::OnChangeEdit5() //When value of lightintensity changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here	
	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	lightintensity.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 1.0 || ttemp > 1000.0)
	{
		AfxMessageBox("Out of bound error!");
		lightintensity.SetWindowTextA("100");
	}
}


void CRetinaModelSimulatorDlg::OnChangeEdit6() //When value of lightintensity_cone changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	lightintensity_cone.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 1.0 || ttemp > 900000.0)
	{
		AfxMessageBox("Out of bound error!");
		lightintensity_cone.SetWindowTextA("50000");
	}
}


void CRetinaModelSimulatorDlg::OnChangeEdit7() //When value of lightstart changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	lightstart.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 0)
	{
		AfxMessageBox("Out of bound error!");
		lightstart.SetWindowTextA("1");
	}

}


void CRetinaModelSimulatorDlg::OnChangeEdit8() //When value of lightduration changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	CString ctemp;
	float ttemp;
	
	lightduration.GetWindowTextA(ctemp);
	ttemp=atof(ctemp.GetString());

	if(ttemp < 0)
	{
		AfxMessageBox("Out of bound error!");
		lightduration.SetWindowTextA("0.02");
	}
}


void CRetinaModelSimulatorDlg::OnChangeEdit9() //When value of membrane capacitance changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel = parameter_cell.GetCurSel();

	CString ctemp;

	mcap.GetWindowTextA(ctemp);
	cellvalue[m_RadioPath][cursel]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnChangeEdit10() //When value of maximum conductance_synapse changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel = parameter_synapse.GetCurSel();

	CString ctemp;

	conduct.GetWindowTextA(ctemp);
	synapsevalue[m_RadioPath][cursel][0]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnClickedButton1() //about...
{
	// TODO: Add your control notification handler code here

	CAboutDlg dlg;
	dlg.DoModal();
}


void CRetinaModelSimulatorDlg::OnChangeEdit13() //when value of reversal potential_synapse changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel = parameter_synapse.GetCurSel();

	CString ctemp;

	revpotential_synapse.GetWindowTextA(ctemp);
	synapsevalue[m_RadioPath][cursel][1]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnChangeEdit14() //when value of slope changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel = parameter_synapse.GetCurSel();

	CString ctemp;

	slope.GetWindowTextA(ctemp);
	synapsevalue[m_RadioPath][cursel][2]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnChangeEdit15() //when value of time constant changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel = parameter_synapse.GetCurSel();

	CString ctemp;

	tconstant.GetWindowTextA(ctemp);
	synapsevalue[m_RadioPath][cursel][3]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnChangeEdit17() //when value of maximum conductance_ion changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int cursel =parameter_cell.GetCurSel();
	int cursel2=ionselection.GetCurSel();

	CString ctemp;

	conduct_ion.GetWindowTextA(ctemp);
	ionvalue[m_RadioPath][cursel][cursel2][0]=atof(ctemp.GetString());
}


void CRetinaModelSimulatorDlg::OnChangeEdit12() //when value of reversal potential_ion changes
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	int cursel =parameter_cell.GetCurSel();
	int cursel2=ionselection.GetCurSel();

	CString ctemp;

	revpotential.GetWindowTextA(ctemp);
	ionvalue[m_RadioPath][cursel][cursel2][1]=atof(ctemp.GetString());
}

void CRetinaModelSimulatorDlg::OnSelchangeCombo2() //when selection of ion channel changes 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	int cursel_cell = parameter_cell.GetCurSel();
	int cursel_ion = ionselection.GetCurSel();

	CString floatstring;
	CString floatstring2;

	floatstring.Format(_T("%.3f"),ionvalue[m_RadioPath][cursel_cell][cursel_ion][0]);
	floatstring2.Format(_T("%.3f"),ionvalue[m_RadioPath][cursel_cell][cursel_ion][1]);
	
	conduct_ion.SetWindowTextA(floatstring);
	revpotential.SetWindowTextA(floatstring2);

	if(m_RadioPath==0 && cursel_cell==0 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==0 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==0 && cursel_cell==1 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==2 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==1 && cursel_cell==1 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==3 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==0 && cursel_cell==2 && cursel_ion==1)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==5 && cursel_ion==1)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==1 && cursel_cell==2 && cursel_ion==1)
	{
		revpotential.SetWindowTextA("Variable");
		revpotential.EnableWindow(FALSE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==1 && cursel_cell==0 && cursel_ion==0)
	{
		revpotential.SetWindowTextA("Unavailable");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==1 && cursel_cell==0 && cursel_ion==1)
	{
		revpotential.SetWindowTextA("Unavailable");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==1 && cursel_ion==0)
	{
		revpotential.SetWindowTextA("Unavailable");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==1 && cursel_ion==1)
	{
		revpotential.SetWindowTextA("Unavailable");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==1 && cursel_cell==0 && cursel_ion==2)
	{
		conduct_ion.SetWindowTextA("Unavailable");
		conduct_ion.EnableWindow(FALSE);
		revpotential.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==2 && cursel_cell==1 && cursel_ion==2)
	{
		conduct_ion.SetWindowTextA("Unavailable");
		conduct_ion.EnableWindow(FALSE);
		revpotential.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath==0 && cursel_cell==0 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==0 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==0 && cursel_cell==2 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==0 && cursel_cell==2 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==1 && cursel_cell==2 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==1 && cursel_cell==2 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==5 && cursel_ion==3)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==5 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_K");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==0 && cursel_cell==1 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==0 && cursel_cell==1 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==1 && cursel_cell==1 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==1 && cursel_cell==1 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==2 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==2 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==3 && cursel_ion==2)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath==2 && cursel_cell==3 && cursel_ion==4)
	{
		revpotential.SetWindowTextA("= E_KV");
		revpotential.EnableWindow(FALSE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51,"Same with the delayed rectifier current's");
	}
	else if(m_RadioPath!=0 || cursel_cell!=0 || cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=0 || cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}	
	else if(m_RadioPath!=0 || cursel_cell!=1 || cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=2 || cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}	
	else if(m_RadioPath!=1 || cursel_cell!=1 || cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=3 || cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}	
	else if(m_RadioPath!=0 || cursel_cell!=2 || cursel_ion!=1)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=5 || cursel_ion!=1)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 || cursel_cell!=2 || cursel_ion!=1)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 || cursel_cell!=0 || cursel_ion!=0)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 || cursel_cell!=0 || cursel_ion!=1)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=1 || cursel_ion!=0)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=1 || cursel_ion!=1)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 || cursel_cell!=0 || cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 || cursel_cell!=1 || cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=0 && cursel_cell!=0 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=0 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=0 && cursel_cell!=2 && cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=0 && cursel_cell!=2 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 && cursel_cell!=2 && cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 && cursel_cell!=2 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=5 && cursel_ion!=3)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=5 && cursel_ion!=4)
	{		
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=0 && cursel_cell!=1 && cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=0 && cursel_cell!=1 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 && cursel_cell!=1 && cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=1 && cursel_cell!=1 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=2 && cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=2 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=3 && cursel_ion!=2)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
	else if(m_RadioPath!=2 && cursel_cell!=3 && cursel_ion!=4)
	{
		revpotential.EnableWindow(TRUE);
		conduct_ion.EnableWindow(TRUE);

		SetDlgItemText(IDC_STATIC_MC_51," ");
	}
}


BOOL CRetinaModelSimulatorDlg::PreTranslateMessage(MSG* pMsg) //esc키 종료 방지
{
	// TODO: Add your specialized code here and/or call the base class

	if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;


	return CDialogEx::PreTranslateMessage(pMsg);
}

/*-----------------------------------------------------------------------------------------------*/

// Temperature
long double celcius_Na_A = 22;
long double celcius_K_A  = 22;

long double heav(long double x)
{
	long double y;

    if(x>=0)
		y = 1.0;  // pulse	
    else
        y = 0.0;

	return y;
} 
    
long double q10_A (long double celcius_A)
{
	long double fun;

	fun = pow((long double)3.0,(celcius_A-6.3)/(long double)10.0);

	return fun;
}

long double expm1_A(long double x ,long double y)
{
	long double fun;

	if(abs(x/y) < 1e-6)
		fun = y*(1-x/y/2);
	else
		fun = x/(exp(x/y)-1);
	
	return fun;
}

long double alpha_m_A (long double v_CB)
{
	long double fun;
	
	v_CB = -v_CB-(65);
	fun = q10_A(celcius_Na_A) * 0.1 * expm1_A((v_CB+25),10);

	return fun;
}
long double beta_m_A(long double v_CB)
{
	long double fun;

	v_CB = -v_CB-(65);
	fun = q10_A(celcius_Na_A)*4*exp(v_CB/18);

	return fun;
}
long double alpha_h_A(long double v_CB)
{
	long double fun;

	v_CB = -v_CB-(65);
	fun = q10_A(celcius_Na_A)*0.07*exp(v_CB/20);

	return fun;
}
long double beta_h_A(long double v_CB)
{
	long double fun;

	v_CB = -v_CB-(65);
	fun = q10_A(celcius_Na_A)*1/(exp(.1*v_CB +3)+1);

	return fun;
}

long double alpha_n_A(long double v_CB)
{
	long double fun;

	v_CB = -v_CB-(65);
	fun = q10_A(celcius_K_A)*0.01*expm1_A(v_CB+10,10);

	return fun;
}
long double beta_n_A(long double v_CB)
{
	long double fun;

	v_CB = -v_CB-(65);
	fun = q10_A(celcius_K_A)*0.125*exp(v_CB/80);

	return fun;
}

long double round(long double a)
{
	long double y;

	y=floor(a+0.5);

	return y;
}
/*-----------------------------------------------------------------------------------------------*/
void CRetinaModelSimulatorDlg::DualPathSimulation(void) //Simulation Run --> Dual Path Simulation
{
#define NI (85) //Number of integrated variable

	/* Global parameter */
	// Rod cell phototransduction
	long double a1_R = 50; 
	long double a2_R = 0.0003; 
	long double a3_R = 0.03; 
	long double eps_R = 0.5;
	long double Ttot_R = 1000;
	long double b1_R = 2.5;
	long double tau1_R = 0.2;
	long double tau2_R = 5.0;
	long double PDEtot_R = 100;
	long double rCa_R = 50;
	long double c0_R = 0.1;
	long double b_R = 0.25;
	long double k1_R = 0.2;
	long double k2_R = 0.8;
	long double eT_R = 500;
	long double Vbar_R = 0.4;
	long double Kc_R = 0.1; 
	long double Amax_R= 65.6;
	long double sigma_R = 1.0; 
	long double Jmax_R = 5040;

	// Rod cell ion channel
	long double Eh_R = -32.0;
	long double EK_R = -74.0;
	long double ECl_R = -20.0;
	long double EL_R = -77.0;

	// Rod cell intracellular calcium system
	long double Jex_R = 20;
	long double Jex2_R = 20; 
	long double Kex_R = 2.3; 
	long double Kex2_R = 0.5;
	long double Cae_R = 0.01;
	long double F_R = 9.64846e4;
	long double V1_R = 3.812e-13; 
	long double V2_R = 5.236e-13; 
	long double DCa_R = 6e-8; 
	long double delta_R = 3e-5; 
	long double S1_R = 3.142e-8;
	long double Lb1_R = 0.4; 
	long double Lb2_R = 0.2; 
	long double Hb1_R = 100; 
	long double Hb2_R = 90; 
	long double BL_R = 500; 
	long double BH_R = 300;

	// Cone cell
	// [mV]     
	long double E_C  = -72;
	long double Vf_C = -57;
	long double Ve_C = 4;

	// [msec]
	//long double rL_C = 10;
	long double rL_C = cellvalue[2][1];
	long double rf_C = 67;

	long double Gf_peak_C = 0.2;
	long double Gi_peak_C = 0.7;     

	// [sec]
	long double K_C = 10;

	// [/sec]
	long double alpha_C    = 83.3;
	long double k12_peak_C = 10;
	long double k12M_C     = 250;
	long double k23_C      = 17;
	long double k34_C      = 1.3;
	long double k32_C      = 0.03;

	// [/sec^2]
	long double v_C = 2.125; 
	long double n_C = 6;
	long double A_C = 6.76;

	// Cone cell offset
	long double offset;

	// Rod cell membrane capacitance
	//long double Cm_R = 0.02;
	long double Cm_R = cellvalue[2][0];

	// Chemical synbapse between rod and rod bipolar
	//long double Vslope_C_RB = 20;
	long double Vslope_C_RB = synapsevalue[2][1][2];
	//long double tau_C_RB = 0.01;
	long double tau_C_RB = synapsevalue[2][1][3];
	long double Vth_C_RB = 0.0; //declaration

	// Rod bipolar
	// Chemical Parameter 
	long double F_RB=9.649e4;
	long double Dca_RB=6.0e-8;

	// Morphologycal Parameter%
	// Soma: Diameter 12 micron
	long double PIP_RB = 3.14159;
	long double radius_RB = 6.0; 
	long double radius_d_RB = 5.6;

	// Chemical parameter         */
	long double Ca_o_RB = 2500.; 

	// Ca current parameter         */
	long double gCa_RB = 1.1;

	// Ca buffer parameter	     */
	long double LB_to1_RB = 300.; 
	long double HB_to1 = 100.; 
	long double LB_to2_RB = 500.; 
	long double HB_to2 = 300.; 
	long double Lb1_RB = 0.4; 
	long double Lb2_RB = 0.2; 
	long double Hb1_RB = 100.; 
	long double Hb2_RB = 90.; 

	// Ca exchanger & pump parameter   */
	long double Jnc_RB = 9.*40; 
	long double Jatp_RB = 9.5*40;
	long double Ca_e_RB = 0.01;

	// Rod bipolar ion channel
	long double EL_RB = -21.0;

	// Rod bipolar synaptic current
	long double gmax_syn_RB=2.56;

	// Rod bipolar membrane capacitance
	//long double Cm_RB = 0.01;
	long double Cm_RB = cellvalue[2][2];

	// Chemical synapse between rod bipolar and amacrine
	long double Vslope_C_RBA = 20;
	long double tau_C_RBA = .01;
	long double Vth_C_RBA = 0.0; //declaration

	// Chemical synapse between cone and cone bipolar
	long double Vslope_C_CCB = 20;
	long double tau_C_CCB = .01;
	long double Vth_C_CCB = 0.0; //declaration

	// Cone bipolar
	// Chemical Parameter 
	long double F_CB=9.649e4;
	long double Dca_CB=6.0e-8;

	// Morphologycal Parameter%
	// Soma: Diameter 12 micron
	long double PIP_CB = 3.14159;
	long double radius_CB = 6.0; 
	long double radius_d_CB = 5.6;

	// Chemical parameter         */
	long double Ca_o_CB = 2500.; 

	// Ca current parameter         */
	long double gCa_CB = 1.1;

	// Ca buffer parameter	     */
	long double LB_to1_CB = 300.; 
	long double HB_to1_CB = 100.; 
	long double LB_to2_CB = 500.; 
	long double HB_to2_CB = 300.; 
	long double Lb1_CB = 0.4;
	long double Lb2_CB = 0.2; 
	long double Hb1_CB = 100.; 
	long double Hb2_CB = 90.;

	// Ca exchanger & pump parameter   */
	long double Jnc_CB = 9.*40; 
	long double Jatp_CB = 9.5*40;
	long double Ca_e_CB = 0.01;     

	// Cone bipolar ionic channel
	long double EL_CB = -21.0;

	// Cone bipolar membrane capacitance
	//long double Cm_CB = 0.01;
	long double Cm_CB = cellvalue[2][3];

	// Amacrine cell
	// Timescale
	long double tscale_A = 1000;

	// Reversal potential of amacrine [mV]
	long double EK_A = -80.0;
	long double ENa_A = 40.0;
	long double El_A = -54;

	// Maximum conductance of amacrine [nS]
	long double gNa_bar_A = 4.0;
	long double gK_bar_A  = 0.4;
	long double gL_A      = 0.46;

	// Membrane capacitance of amacrine [nF]
	//long double Cm_A = 20;
	long double Cm_A = cellvalue[2][4];

	// Chemical synapse between cone bipolar and ganglion
	long double Vslope_C_CBG = 20;
	long double tau_C_CBG = .01;
	long double Vth_C_CBG = 0.0; //declaration

	// Ganglion cell
	// Time scale
	long double tscale_G=1000; // scale to seconds factor

	//-------Na---
	long double g_Na_G = 50.0;
	long double VNa_G = 35.0;

	//-------Ca, KCa---
	long double g_Ca_G = 2.2;
	long double Ca2e_G = 1800;
	long double tCa_G = 50.0;
	long double Ca2res_G = 0.1;
	long double r_G = 12.5;
	long double g_KCa_G = 0.05;
	long double Ca2diss_G = 1.0;
	long double R_G = 8.31;
	long double F_G = 96500;
	long double T_G = 293;        
	long double VK_G = -75.0;

	//-------K---
	long double g_K_G = 12.0;   
		
	//-------A---
	long double g_A_G = 36.0;

	//-------L---
	long double g_L_G = 0.05;
	long double VL_G = -62.0;
		  
	//-------I---        
	//long double Cm_G = 1.0; 
	long double Cm_G = cellvalue[2][5];

	/* For preallocation */
	long double tlength;
	int height;
	int width;
	long double** ystar;
	long double** Vpre_C_RB;
	long double** s_syn_RB;
	long double** Vpre_C_RBA;
	long double** s_syn_CB;
	long double** s_syn2_A;
	long double** Vpre_C_CBG;
	long double** Vpre_C_CCB;
	long double** s_syn_G;
	long double** Iphoto_R2; 

	long double** real_t;

	long double y11[85][4] = {0};
	long double k  [85][4] = {0};

	int percentage;

	struct data
	{
		long double tstart;
		long double tstep;
		long double tlast;
		long double duration;
		long double light_start;
		long double light_intensity;
		long double light_intensity_cone;
	};

	struct data data;

	//FILE* fp;

	data.tstart=t_fstart;
	data.tlast=t_fend;
	data.tstep=t_fstep;
	data.light_intensity=flightintensity;
	data.light_intensity_cone=flightintensity_cone;
	data.duration=flightduration;
	data.light_start=flightstart;

	ReplaceMsgBoard("Setting Global/External Parameters Finished.");

	/* Preallocation */
	int i,j;	

	tlength=round((data.tlast-data.tstart)/data.tstep +1);
	
	height= NI;
	width=(int)tlength +1;	

	ystar = (long double **) malloc(sizeof(long double*) * height);
	Vpre_C_RB = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_RB = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_RBA = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_CB = (long double **) malloc(sizeof(long double*) * 1);
	s_syn2_A = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_CBG = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_CCB = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_G = (long double **) malloc(sizeof(long double*) * 1);
	real_t = (long double **) malloc(sizeof(long double*) * 1);
	Iphoto_R2 = (long double **) malloc(sizeof(long double*) *1);
	
	for(i=0; i<height;i++)
	{
		ystar[i]=(long double *) malloc(sizeof(long double) * width); //long double ystar[85,tlength];
	}
	
	for(i=0;i<1;i++)
	{
		Vpre_C_RB[i] = (long double *) malloc(sizeof(long double) * width);
		s_syn_RB[i]  = (long double *) malloc(sizeof(long double) * width);
		Vpre_C_RBA[i]= (long double *) malloc(sizeof(long double) * width);
		s_syn_CB[i]  = (long double *) malloc(sizeof(long double) * width);
		s_syn2_A[i]  = (long double *) malloc(sizeof(long double) * width);
		Vpre_C_CBG[i]= (long double *) malloc(sizeof(long double) * width);
		Vpre_C_CCB[i]= (long double *) malloc(sizeof(long double) * width);
		s_syn_G[i]   = (long double *) malloc(sizeof(long double) * width);
		real_t[i]    = (long double *) malloc(sizeof(long double) * width);
		Iphoto_R2[i] = (long double *) malloc(sizeof(long double) * width);
	}
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			ystar[i][j]=0;			
		}		
	}	

	for(i=0;i<1;i++)
		for(j=0;j<width;j++)
		{
			Vpre_C_RB[i][j]=0;
			s_syn_RB[i][j]=0;
			Vpre_C_RBA[i][j]=0;
			s_syn_CB[i][j]=0;
			s_syn2_A[i][j]=0;
			Vpre_C_CBG[i][j]=0;
			Vpre_C_CCB[i][j]=0;
			s_syn_G[i][j]=0;
			real_t[i][j]=0;
		}
	ReplaceMsgBoard("Memory Dynamic Preallocation Finished.");

	/* Initial Condition */
	// Rod and Cone cell Initial Condition
	y11[0][0] = -35.15299217465973700000000000000000000000000000000000;
	y11[1][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[2][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[3][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[4][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[5][0] = 0.30000000000000143000000000000000000000000000000000;
	y11[6][0] = 34.88372093023302500000000000000000000000000000000000;
	y11[7][0] = 1.99999999999998670000000000000000000000000000000000;
	y11[8][0] = 0.64132528330066263000000000000000000000000000000000;
	y11[9][0] = 0.26412772593690498000000000000000000000000000000000;
	y11[19][0] = 0.04079255338037327700000000000000000000000000000000;
	y11[11][0] = 0.00280004667419985350000000000000000000000000000000;
	y11[12][0] = 0.00007207438056699847500000000000000000000000000000;
	y11[13][0] = 0.44095899101175912000000000000000000000000000000000;
	y11[14][0] = 0.99912312462833097000000000000000000000000000000000;
	y11[15][0] = 0.46586591802631688000000000000000000000000000000000;
	y11[16][0] = 0.65322043938092211000000000000000000000000000000000;
	y11[17][0] = 0.12381319321649724000000000000000000000000000000000;
	y11[18][0] = 0.12381319648326869000000000000000000000000000000000;
	y11[19][0] = 99.23899869893260500000000000000000000000000000000000;
	y11[20][0] = 36.28001495889955700000000000000000000000000000000000;
	y11[21][0] = 99.23900194523179200000000000000000000000000000000000;
	y11[22][0] = 36.28001580109989300000000000000000000000000000000000;
	y11[23][0] = -45.76654665646767500000000000000000000000000000000000;
	y11[24][0] = 0.01137478132545304700000000000000000000000000000000;
	y11[25][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[26][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[27][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[28][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[29][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[30][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[31][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[32][0] = 0.00000000000000000000000000000000000000000000000000;
	offset=42.2321233629648844498660764656960964202880859375; // Cone Cell Membrane Potential offset

	// Chemical Synapse Between Rod and Rod Bipolar Initial Condition
	y11[33][0] = 0;

	// Rod Bipolar Initial Condition
	y11[34][0] = -36.424516776897130;
	y11[35][0] = 0.928238175043767;
	y11[36][0] = 0.054905344261992;
	y11[37][0] = 0.001217870414180;
	y11[38][0] = 1.200618479085905e-05;
	y11[39][0] = 4.438540983730620e-08;
	y11[40][0] = 0.824374082910590;
	y11[41][0] = 0.109794106890060;
	y11[42][0] = 0.290203193088928;
	y11[43][0] = 0.475464147362579;
	y11[44][0] = 0.011561930331728;
	y11[45][0] = 0.011563608687641;
	y11[46][0] = 6.780371247710756;
	y11[47][0] = 1.268364765067093;
	y11[48][0] = 11.302574980627850;
	y11[49][0] = 3.805639865311822;
	y11[50][0] = 0.186127778073054;
	y11[51][0] = 0.024443585120781;

	// Chemical Synapse Between Rod Bipolar and Amacrine Initial Condition
	y11[52][0] = 0;

	// Chemical Synapse Between Cone and Cone Bipolar Initial Condition
	y11[53][0] = 0;

	// Cone Bipolar Initial Condition
	y11[54][0] = -40.85865173873610700638892012648284435272216796875000;
	y11[55][0] = 0.91442826153121192778172598991659469902515411376953;
	y11[56][0] = 0.06802394011168773346742710828038980253040790557861;
	y11[57][0] = 0.00189760228726293194399799002525242030969820916653;
	y11[58][0] = 0.00002352697486413260014254458796223445915529737249;
	y11[59][0] = 0.00000010938512049644076438087637219778724961827265;
	y11[60][0] = 0.75119613755960557011093214896391145884990692138672;
	y11[61][0] = 0.12833933300174665825821307407750282436609268188477;
	y11[62][0] = 0.23512534165859483303862020875385496765375137329102;
	y11[63][0] = 0.44667148688898017372395088386838324368000030517578;
	y11[64][0] = 0.01069015667321450424598339168369420804083347320557;
	y11[65][0] = 0.01146115054172941634391680310045558144338428974152;
	y11[66][0] = 6.69114537743995629881510467384941875934600830078125;
	y11[67][0] = 1.17390152355585408727733920386526733636856079101562;
	y11[68][0] = 11.29221858507642828328698669793084263801574707031250;
	y11[69][0] = 3.77261483646810091840961831621825695037841796875000;
	y11[70][0] = 0.11197954384331872124125339951206115074455738067627;
	y11[71][0] = 0.04078196799520746040901286733060260303318500518799;

	// Amacrine Initial Condition
	y11[72][0] = -50.34951375105524107311794068664312362670898437500000;
	y11[73][0] = 0.24340676136333766477193307764537166804075241088867;
	y11[74][0] = 0.15952849172211810979682411471003433689475059509277;
	y11[75][0] = 0.54575595513993369056748861112282611429691314697266;

	// Chemical Synapse Between Cone Bipolar and Ganglion Initial Condition
	y11[76][0] = 0;

	// Ganglion Initial Condition
	y11[77][0]=-61.698524;
	y11[78][0]=0.027940;
	y11[79][0]=0.887161;
	y11[80][0]=0.003019;
	y11[81][0]=0.100007;
	y11[82][0]=0.107809;
	y11[83][0]=0.070467;
	y11[84][0]=0.300453;

	for(i=0;i<NI;i++)
	{
		ystar[i][0]=y11[i][0];
	}

	 ReplaceMsgBoard("Derivatives Initialization Finished.");
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("*** Dual Path Simulation (R+C+RB+CB+A+G) ***");
	 CString announce, announce2, announce3;
	 announce.Format("Start Time = %f, End Time = %f, Time Step = %f",data.tstart,data.tlast,data.tstep);
	 announce2.Format("Light Intensity for Rod = %f, Light Intensity for Cone = %f",data.light_intensity,data.light_intensity_cone);
	 announce3.Format("Light Starting Time = %f, Light Duration = %f",data.light_start,data.duration);
	 ReplaceMsgBoard(announce);
	 ReplaceMsgBoard(announce2);
	 ReplaceMsgBoard(announce3);
	 ReplaceMsgBoard(" ");

	 CString announce4, announce5, announce6, announce7, announce8, announce9, announce10;

	 ReplaceMsgBoard("** Rod Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[2][0]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f",ionvalue[2][0][0][0],ionvalue[2][0][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f",ionvalue[2][0][1][0], ionvalue[2][0][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[2][0][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium-Chloride Current *");
	 announce8.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][0][3][0], ionvalue[2][0][3][1]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[2][0][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][0][5][0], ionvalue[2][0][5][1]);
	 ReplaceMsgBoard(announce10);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Cone Cell **");
	 announce4.Format("Time Constant = %f", cellvalue[2][1]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* G_f Channel Current *");
	 announce5.Format("Maximum Time Constant = %f", ionvalue[2][1][0][0]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* G_i Channel Current *");
	 announce6.Format("Maximum Time Constant = %f", ionvalue[2][1][1][0]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Static Channel Current *");
	 announce7.Format("Reversal Potential = %f", ionvalue[2][1][2][1]);
	 ReplaceMsgBoard(announce7);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Rod Bipolar Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[2][2]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][2][0][0], ionvalue[2][2][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][2][1][0], ionvalue[2][2][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Transient Outward Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[2][2][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[2][2][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[2][2][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][2][5][0], ionvalue[2][2][5][1]);
	 ReplaceMsgBoard(announce10);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Cone Bipolar Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[2][3]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][3][0][0], ionvalue[2][3][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][3][1][0], ionvalue[2][3][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Transient Outward Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[2][3][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[2][3][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[2][3][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][3][5][0], ionvalue[2][3][5][1]);
	 ReplaceMsgBoard(announce10);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Amacrine Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[2][4]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Sodium Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][4][0][0], ionvalue[2][4][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Potassium Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][4][1][0], ionvalue[2][4][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce7.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][4][2][0], ionvalue[2][4][2][1]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Ganglion Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[2][5]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Sodium Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][5][0][0], ionvalue[2][5][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce6.Format("Maximum Conductance = %f", ionvalue[2][5][1][0]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce7.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][5][2][0], ionvalue[2][5][2][1]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[2][5][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* A Type Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[2][5][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[2][5][5][0], ionvalue[2][5][5][1]);
	 ReplaceMsgBoard(announce10);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Electrical Synapse (R-C) **");
	 announce4.Format("Maximum Conductance = %f",synapsevalue[2][0][0]);
	 ReplaceMsgBoard(announce4);	
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (R-RB) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f",synapsevalue[2][1][0], synapsevalue[2][1][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[2][1][2], synapsevalue[2][1][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (C-CB) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[2][2][0], synapsevalue[2][2][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[2][2][2], synapsevalue[2][2][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (RB-A) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[2][3][0], synapsevalue[2][3][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[2][3][2], synapsevalue[2][3][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Electrical Synapse (CB-A) **");
	 announce4.Format("Maximum Conductance = %f", synapsevalue[2][4][0]);
	 ReplaceMsgBoard(announce4);	
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (CB-G) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[2][5][0], synapsevalue[2][5][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[2][5][2], synapsevalue[2][5][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	/* Model */
	long double t;

	percentage = 0;

	fp = fopen("C:\\Output_DualPath.dat","w+");
	checkfp++;

	for(i=0;i<(int)(tlength);i++)
	{
		if(simulationstop==1)
		{
			simulationstop=0;
			fclose(fp);
			remove("C:\\Output_DualPath.dat");
			goto FREE;
		}

		t=(long double)i*data.tstep + data.tstart;
		real_t[0][i]=t;

		int perfect=(int)tlength-1;
		int perfect2=perfect/100;

		if(i%perfect2==0)
		{	
			CString c_simulationprogress;
			c_simulationprogress.Format("Simulation %d %% Finished.",percentage++);

			if((percentage-1)%10==0)
			{
				ReplaceMsgBoard(c_simulationprogress);
			}
			
			progress.StepIt();
		}

		for(j=0;j<4;j++) //4th order
		{
			// ROD
			long double V_R   = y11[0][j];             // membrane potential (mV)
			// outer segment
			long double Rh_R  = y11[1][j];             // active rhodopsin (uM)
			long double Rhi_R = y11[2][j];             // inactive rhodopsin (uM)
			long double Tr_R  = y11[3][j];             // active transducin (uM)
			long double PDE_R = y11[4][j];             // active phosphodiesterase (uM)
			long double Ca_R  = y11[5][j];             // intracellular free Ca in outer segment (uM)
			long double Cab_R = y11[6][j];             // intracellular Ca buffer in outer segment (uM)
			long double cGMP_R= y11[7][j];             // cyclic GMP (uM)
			// Ih
			long double C1_R  = y11[8][j];
			long double C2_R  = y11[9][j];
			long double O1_R  = y11[10][j];
			long double O2_R  = y11[11][j];
			long double O3_R  = y11[12][j];
			// IKv, ICa, IKCa
			long double mKv_R  = y11[13][j];
			long double hKv_R = y11[14][j];
			long double mCa_R  = y11[15][j];
			long double mKCa_R = y11[16][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_R  = y11[17][j];
			long double Ca_f_R  = y11[18][j];
			long double Cab_ls_R= y11[19][j];
			long double Cab_hs_R= y11[20][j];
			long double Cab_lf_R= y11[21][j];
			long double Cab_hf_R= y11[22][j];
			// CONE
			long double VC_C = y11[23][j];             // membrane potential (mV)
			long double Gf_C = y11[24][j];
			long double y1_C = y11[25][j];
			long double y2_C = y11[26][j];
			long double y3_C = y11[27][j];
			long double y4_C = y11[28][j];
			long double y5_C = y11[29][j];
			long double z1_C = y11[30][j];
			long double z2_C = y11[31][j];
			long double z3_C = y11[32][j];
        
			// Chemical Synapse Between Rod and Rod Bipolar
			long double S_C_RB = y11[33][j];
        
			// Rod Bipolar
			long double v_RB   = y11[34][j];             // membrane potential (mV)
			long double C1_RB  = y11[35][j];
			long double C2_RB  = y11[36][j];
			long double OP1_RB  = y11[37][j];
			long double OP2_RB  = y11[38][j];
			long double OP3_RB  = y11[39][j];
			// IKv, ICa, IKCa
			long double mKv_RB  = y11[40][j];
			long double hKv_RB = y11[41][j];
			long double mCa_RB  = y11[42][j];
			long double mKca_RB = y11[43][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_RB  = y11[44][j];
			long double Ca_d_RB  = y11[45][j];
			long double bCa_ls_RB= y11[46][j];
			long double bCa_hs_RB= y11[47][j];
			long double bCa_ld_RB= y11[48][j];
			long double bCa_hd_RB= y11[49][j];
			// IA
			long double mA_RB= y11[50][j];
			long double hA_RB= y11[51][j];
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
			long double S_C_RBA = y11[52][j];
        
			// Chemical Synapse Between Cone and Cone Bipolar
			long double S_C_CCB = y11[53][j];
        
			// Cone Bipolar
			long double v_CB   = y11[54][j];             // membrane potential (mV)
			// Ih
			long double C1_CB  = y11[55][j];
			long double C2_CB  = y11[56][j];
			long double OP1_CB  = y11[57][j];
			long double OP2_CB  = y11[58][j];
			long double OP3_CB  = y11[59][j];
			// IKv, ICa, IKCa
			long double mKv_CB  = y11[60][j];
			long double hKv_CB = y11[61][j];
			long double mCa_CB  = y11[62][j];
			long double mKca_CB = y11[63][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_CB  = y11[64][j];
			long double Ca_d_CB  = y11[65][j];
			long double bCa_ls_CB= y11[66][j];
			long double bCa_hs_CB= y11[67][j];
			long double bCa_ld_CB= y11[68][j];
			long double bCa_hd_CB= y11[69][j];
			// IA
			long double mA_CB= y11[70][j];
			long double hA_CB= y11[71][j];
        
			// Amacrine
			long double VA_A = y11[72][j];             // membrane potential (mV)
			long double m_A = y11[73][j];
			long double h_A = y11[74][j];
			long double n_A = y11[75][j];
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
			long double S_C_CBG = y11[76][j];
        
			// Ganglion
			long double V_G = y11[77][j];
			long double Na_m_G = y11[78][j];
			long double Na_h_G = y11[79][j];
			long double Ca_n_G = y11[80][j];
			long double Ca_i_G = y11[81][j];
			long double K_n_G = y11[82][j];
			long double A_m_G = y11[83][j];
			long double A_h_G = y11[84][j];			

			// ROD
			// Phototransduction        
			//long double jhv_R = data.light_intensity *( heav(t-(data.tstart+data.light_start)) - heav(t-(data.tstart+data.light_start+data.duration)) ) ; //pulse

			long double jhv_R = 0;
			
			if (data.light_start <= t && t <= data.light_start + data.duration)
				jhv_R = data.light_intensity;
			else
				jhv_R = 0.0;	

			long double dRh_R  = jhv_R - a1_R*Rh_R + a2_R*Rhi_R;
			long double dRhi_R = a1_R*Rh_R - (a2_R+a3_R)*Rhi_R;
			long double dTr_R  = eps_R*Rh_R*(Ttot_R-Tr_R) - b1_R*Tr_R + tau2_R*PDE_R - tau1_R*Tr_R*(PDEtot_R-PDE_R);
			long double dPDE_R = tau1_R*Tr_R*(PDEtot_R-PDE_R) - tau2_R*PDE_R;
			long double J_R    = Jmax_R*pow(cGMP_R,3) / (pow(cGMP_R,3)+1000);
			long double dCa_R  = b_R*J_R - rCa_R*(Ca_R-c0_R) - k1_R*(eT_R-Cab_R)*Ca_R + k2_R*Cab_R;
			long double dCab_R = k1_R*(eT_R-Cab_R)*Ca_R - k2_R*Cab_R;
			long double dcGMP_R= Amax_R/(1.0+(pow(Ca_R,4)/pow(Kc_R,4))) - cGMP_R*(Vbar_R+sigma_R*PDE_R);
        
			long double Iphoto_R = -Jmax_R*pow(cGMP_R,3)/(pow(cGMP_R,3)+1000)*(1-exp((V_R-8.5)/17));
			Iphoto_R2[0][i]=Iphoto_R;
        
			// Ih			
			long double ahh_R = 8 / ( exp((V_R+78)/14) + 1);
			long double bhh_R = 18 / ( exp(-(V_R+8)/19) + 1);
			long double dC1_R = -4*ahh_R*C1_R + bhh_R*C2_R;
			long double dC2_R =  4*ahh_R*C1_R - (3*ahh_R+bhh_R)*C2_R + 2*bhh_R*O1_R;
			long double dO1_R =  3*ahh_R*C2_R - (2*ahh_R+2*bhh_R)*O1_R + 3*bhh_R*O2_R;
			long double dO2_R =  2*ahh_R*O1_R - (ahh_R+3*bhh_R)*O2_R + 4*bhh_R*O3_R;
			long double dO3_R =  ahh_R*O2_R - 4*bhh_R*O3_R;
			long double Ih_R  = ionvalue[2][0][0][0]*(O1_R+O2_R+O3_R)*(V_R-ionvalue[2][0][0][1]);
			// IKv			
			long double amKv_R = 5*(100-V_R) / (exp( (100-V_R)/42 ) - 1 );
			long double bmKv_R = 9*exp( -(V_R-20)/40 );
			long double ahKv_R = 0.15*exp( -V_R/22 );
			long double bhKv_R = 0.4125 / ( exp( (10-V_R)/7 ) + 1 );
			long double dmKv_R = amKv_R*(1-mKv_R) - bmKv_R*mKv_R;
			long double dhKv_R = ahKv_R*(1-hKv_R) - bhKv_R*hKv_R;
			long double IKv_R  = ionvalue[2][0][1][0]*pow(mKv_R,3)*hKv_R*(V_R-ionvalue[2][0][1][1]);
			// ICa
			long double amCa_R = 3*(80-V_R) / ( exp( (80-V_R)/25 ) -1 );
			long double bmCa_R = 10 / ( 1 + exp( (V_R+38)/7 ) );
			long double hCa_R  = exp( (40-V_R)/18 ) / ( 1 + exp( (40-V_R)/18 ) );
			long double dmCa_R = amCa_R*(1-mCa_R) - bmCa_R*mCa_R;
			long double ECa_R  = -12.5*log(Ca_s_R/1600);
			long double ICa_R  = ionvalue[2][0][2][0]*pow(mCa_R,4)*hCa_R*(V_R-ECa_R);
        
			// ICl(Ca)			
			long double mCl_R  = 1.0 / ( 1 + exp( (0.37-Ca_s_R) / 0.09  ) );
			long double IClCa_R = ionvalue[2][0][3][0]*mCl_R*(V_R-ionvalue[2][0][3][1]);
        
			// IK(Ca)
			long double amKCa_R = 15*(80-V_R) / ( exp( (80-V_R)/40 ) - 1 );
			long double bmKCa_R = 20*exp( -V_R/35 );
			long double dmKCa_R = amKCa_R*(1-mKCa_R) - bmKCa_R*mKCa_R;
			long double mKCa_s_R = Ca_s_R / (Ca_s_R + 0.3 );
			long double IkCa_R = ionvalue[2][0][4][0] * mKCa_R * mKCa_R * mKCa_s_R * (V_R-ionvalue[2][0][1][1]);
        
			// IL			
			long double IL_R = ionvalue[2][0][5][0]*(V_R-ionvalue[2][0][5][1]);        
        
			// Intracellular calcium system
			long double Iex_R = Jex_R *exp( -(V_R+14)/70 ) * (Ca_s_R - Cae_R) / ( Ca_s_R - Cae_R + Kex_R );
			long double Iex2_R= Jex2_R*( Ca_s_R - Cae_R ) / ( Ca_s_R -Cae_R + Kex2_R );
			long double dCa_s_R = - (ICa_R + Iex_R + Iex2_R ) / ( 2.0 * F_R * V1_R ) * 1e-06 - DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V1_R ) - Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) + Lb2_R *Cab_ls_R - Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) + Hb2_R * Cab_hs_R;
			long double dCa_f_R =   DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V2_R ) - Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) + Lb2_R * Cab_lf_R - Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) + Hb2_R * Cab_hf_R;
			long double dCab_ls_R = Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) - Lb2_R * Cab_ls_R;
			long double dCab_hs_R = Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) - Hb2_R * Cab_hs_R;
			long double dCab_lf_R = Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) - Lb2_R * Cab_lf_R;
			long double dCab_hf_R = Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) - Hb2_R * Cab_hf_R;			

			// CONE
			long double I_C;

			if (data.light_start <= t && t <= data.light_start + data.duration)
				I_C = data.light_intensity_cone;
			else
				I_C = 0.0;		
        
			// activation and inactivation rates
			long double Gi_C  = ionvalue[2][1][1][0]/(1+z1_C/K_C);
			long double F_C   = ionvalue[2][1][0][0]/(1+exp((VC_C-Vf_C)/Ve_C));
			long double k12_C = k12_peak_C+v_C*z2_C*(k12M_C-k12_peak_C)/(k12M_C-k12_peak_C+v_C*z2_C);
			long double k21_C = k12_C/6.76;
        
			long double dGf_C  = (F_C-Gf_C)/rf_C;
			long double dy1_C  = I_C - alpha_C * y1_C;
			long double dy2_C  = alpha_C * (y1_C - y2_C);
			long double dy3_C  = alpha_C * (y2_C - y3_C);
			long double dy4_C  = alpha_C * (y3_C - y4_C);
			long double dy5_C  = alpha_C * (y4_C - y5_C);
			long double dz1_C  = alpha_C * y5_C - k12_C * z1_C + k21_C * z2_C;
			long double dz2_C  = k12_C * z1_C - (k21_C + k23_C) * z2_C + k32_C * z3_C;
			long double dz3_C  = k23_C * z2_C - (k32_C + k34_C) * z3_C;

			// Rod and Cone Total Current and Membrane Potential			
			long double IALL_R = Iphoto_R + Ih_R + IKv_R + ICa_R + IClCa_R + IkCa_R + IL_R +Iex_R + Iex2_R ;
        
			long double dV_R   = (-IALL_R + synapsevalue[2][0][0]*((VC_C + offset)-V_R))/Cm_R; // All electrical synapses between cones and rods have the same conductance value of 0.2nS [35]. FROM PUBLIO 2009
			long double dVC_C   = (ionvalue[2][1][2][1]-VC_C*(1+Gf_C+Gi_C) + synapsevalue[2][0][0]*(V_R-(VC_C + offset)))/rL_C;

			// Chemical Synapse Between Rod and Rod Bipolar			
			Vpre_C_RB[0][i]=V_R;
			
			//Vth_C_RB = -35.15299217465973700000000000000000000000000000000000;
			Vth_C_RB = Vpre_C_RB[0][0];			
	
			long double Sinf_C_RB = tanh(abs(Vpre_C_RB[0][i] - Vth_C_RB)/Vslope_C_RB);
			
			long double d_st_C_RB = 0;
			if (Vpre_C_RB[0][i] >= Vth_C_RB) // 2015 December added [97-98 line].
				d_st_C_RB = 0;
			else if (abs(Vpre_C_RB[0][i]-Vth_C_RB) >= 0) // New version
				d_st_C_RB = (Sinf_C_RB - S_C_RB) / ((1-Sinf_C_RB) * tau_C_RB );
			else
				d_st_C_RB = 0;

			if(t<data.light_start)
				d_st_C_RB = 0;			
        
			// Rod Bipolar
			s_syn_RB[0][i]=S_C_RB;
			// Ih
			long double ah_RB = 3 / ( exp( (v_RB+110)/15 ) + 1. );
			long double bh_RB = 1.5 / ( exp( -(v_RB+115)/15 ) + 1. );
        
			long double dC1_RB = bh_RB*C2_RB - 4.*ah_RB*C1_RB;
			long double dC2_RB = C1_RB*4.*ah_RB + OP1_RB*2.*bh_RB - C2_RB*bh_RB - C2_RB*3.*ah_RB;    //original
			// long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
			long double dOP1_RB = C2_RB*3.*ah_RB + OP2_RB*3.*bh_RB - OP1_RB*2.*(bh_RB+ah_RB);
			long double dOP2_RB = OP1_RB*2.*ah_RB + OP3_RB*4.*bh_RB - OP2_RB*(3.*bh_RB + ah_RB);
			long double dOP3_RB = ah_RB*OP2_RB - 4*bh_RB*OP3_RB;
        
			long double mh_RB = OP1_RB + OP2_RB + OP3_RB;
			long double ih_RB = mh_RB * ionvalue[2][2][0][0] * ( v_RB - (ionvalue[2][2][0][1]) );
        
			// IKv
			long double amKv_RB = 400 / ( exp( -(v_RB-15)/36 ) + 1. );
			long double bmKv_RB = 1.0 * exp( -v_RB / 13 );
        
			long double d_mKv_RB = amKv_RB * ( 1. - mKv_RB ) - bmKv_RB * mKv_RB;
        
			long double ahKv_RB = 0.0003 * exp( -v_RB / 7 );
			long double bhKv_RB = 80 / ( exp( -(-115-v_RB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
			long double d_hKv_RB = ahKv_RB * ( 1. - hKv_RB ) - bhKv_RB * hKv_RB;
        
			long double iKv_RB = ionvalue[2][2][1][0] * mKv_RB * mKv_RB * mKv_RB * hKv_RB*( v_RB - (ionvalue[2][2][1][1]) );
        
			// ICa
			long double Vd_RB = 4/3*PIP_RB*(radius_d_RB*radius_d_RB*radius_d_RB)*1e-15;
			long double Vs_RB = 4/3*PIP_RB*(radius_RB*radius_RB*radius_RB)*1e-15-Vd_RB;
			long double Ssd_RB = 4*PIP_RB*radius_d_RB*radius_d_RB*1e-10;
			long double dsd_RB = ((radius_RB-radius_d_RB)/2 + radius_d_RB)*1e-5;
			        
			long double amCa_RB = 12000*( 120 - v_RB ) / ( exp( (120-v_RB)/25 ) - 1. );  // original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
			long double bmCa_RB = 40000 / ( 1.0 + exp( (68+v_RB)/25 ) );
			long double d_mCa_RB = amCa_RB * ( 1. - mCa_RB ) - bmCa_RB * mCa_RB;
			long double mCa_4_RB = pow((long double) mCa_RB, (long double)4.0 );
        
			long double hCa_RB = exp( (50-v_RB)/11 )/( 1.0 + exp( (50-v_RB)/11) );
        
			long double ECa_RB = 12.9*log(Ca_o_RB/Ca_s_RB);
        
			long double iCa_RB = ionvalue[2][2][3][0]*mCa_4_RB*hCa_RB*(v_RB-ECa_RB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
			long double iNC_RB = Jnc_RB*exp(-(v_RB+14.)/70.) *( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 2.3 );
			long double iATP_RB = Jatp_RB*( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
			long double dbCa_ls_RB = Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) - Lb2_RB*bCa_ls_RB;
        
			long double dbCa_hs_RB = Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB) - Hb2_RB*bCa_hs_RB;
        
			long double dCa_s_RB = -(iCa_RB+iNC_RB+iATP_RB)/(2.*F_RB*Vs_RB)*1.0E-6 - Dca_RB*Ssd_RB/Vs_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ls_RB - Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) + Hb2_RB*bCa_hs_RB - Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB);
        
			long double dCa_d_RB = Dca_RB*Ssd_RB/Vd_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ld_RB - Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) + Hb2_RB*bCa_hd_RB - Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB);
        
			long double dbCa_ld_RB = Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) - Lb2_RB*bCa_ld_RB;
			long double dbCa_hd_RB = Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB) - Hb2_RB*bCa_hd_RB;
        
			// IK(Ca)
			long double mKca_c1_RB = Ca_s_RB / ( Ca_s_RB + 0.2 );
			long double amKca_RB = 100 * ( 230 - v_RB )/( exp( (230-v_RB)/52 ) - 1. );
			long double bmKca_RB = 120 * exp( -v_RB / 95 );
			long double d_mKca_RB = amKca_RB * ( 1. - mKca_RB ) - bmKca_RB * mKca_RB;
        
			long double iKca_RB = ionvalue[2][2][4][0] * mKca_c1_RB*mKca_RB*mKca_RB*(v_RB - (ionvalue[2][2][1][1]));
			// IL
			long double EL_RB = ionvalue[2][2][5][1];
			long double il_RB = ionvalue[2][2][5][0]*((v_RB-EL_RB));
        
			// IA
			long double amA_RB = 2400 / ( 1.0 + exp( -(v_RB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
			long double bmA_RB = 12 * exp( -v_RB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
			long double d_mA_RB = amA_RB * ( 1. - mA_RB ) - bmA_RB * mA_RB;
        
			long double ahA_RB = 0.045 * exp( -v_RB / 13 );
			long double bhA_RB = 75 / ( exp( -(30+v_RB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
			long double d_hA_RB = ahA_RB * ( 1.0 - hA_RB ) - bhA_RB * hA_RB;
        
        
			long double iA_RB = ionvalue[2][2][2][0] * pow( (long double)mA_RB, (long double)3.0 ) * hA_RB * ( v_RB - (ionvalue[2][2][1][1]) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
        
			// Isyn
			//long double gmax_syn_RB=2.56; //nS
			long double gmax_syn_RB = synapsevalue[2][1][0];
			long double Isyn_RB = gmax_syn_RB * s_syn_RB[0][i] * (v_RB-synapsevalue[2][1][1]);
        
        
			// Total current and membrane potential
			//long double Cm_RB = 0.01;
			long double Cm_RB = cellvalue[2][2];
			long double IALL_RB = iKca_RB + iCa_RB + ih_RB + iKv_RB + il_RB + iA_RB + Isyn_RB; //for chemical synapse simulation
			long double dV_RB   = -IALL_RB / Cm_RB; //for reference %for current clamp simulation
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
			Vpre_C_RBA[0][i]=v_RB;
			
			//Vth_C_RBA = -36.424516776897130;
			Vth_C_RBA = Vpre_C_RB[0][0];			

			//long double Vslope_C_RBA = 20;
			long double Vslope_C_RBA = synapsevalue[2][3][2];
			//long double tau_C_RBA = .01;
			long double tau_C_RBA = synapsevalue[2][3][3];
        
			long double Sinf_C_RBA = tanh(abs(Vpre_C_RBA[0][i] - Vth_C_RBA)/Vslope_C_RBA);
			long double d_st_C_RBA = 0;

			if(Vpre_C_RBA[0][i] < Vth_C_RBA)
				d_st_C_RBA = 0;
			else if (abs(Vpre_C_RBA[0][i]-Vth_C_RBA) >= 0) // New version
				d_st_C_RBA = (Sinf_C_RBA - S_C_RBA) / ((1-Sinf_C_RBA) * tau_C_RBA );
			else
				d_st_C_RBA = 0;

			if(t<data.light_start)
				d_st_C_RBA = 0;	
			        
			// Chemical Synapse Between Cone and Cone Bipolar
			Vpre_C_CCB[0][i]=VC_C + offset;
						
			//Vth_C_CCB = -45.76654665646767500000000000000000000000000000000000 + offset;
			Vth_C_CCB = Vpre_C_CCB[0][0];
			
			//long double Vslope_C_CCB = 20;
			long double Vslope_C_CCB = synapsevalue[2][2][2];
			//long double tau_C_CCB = .01;
			long double tau_C_CCB = synapsevalue[2][2][3];
        
			long double Sinf_C_CCB = tanh(abs(Vpre_C_CCB[0][i] - Vth_C_CCB)/Vslope_C_CCB);
			long double d_st_C_CCB=0;

			if(Vpre_C_CCB[0][i] >= Vth_C_CCB)
				d_st_C_CCB = 0;
			else if (abs(Vpre_C_CCB[0][i]-Vth_C_CCB) >= 0) // New version
				d_st_C_CCB = (Sinf_C_CCB - S_C_CCB) / ((1-Sinf_C_CCB) * tau_C_CCB );
			else
				d_st_C_CCB = 0;

			if(t<data.light_start)
				d_st_C_CCB = 0;	
			        
			// Cone Bipolar
			s_syn_CB[0][i]=S_C_CCB;
			// Ih
			long double ah_CB = 3 / ( exp( (v_CB+110)/15 ) + 1. );
			long double bh_CB = 1.5 / ( exp( -(v_CB+115)/15 ) + 1. );
        
			long double dC1_CB = bh_CB*C2_CB - 4.*ah_CB*C1_CB;
			long double dC2_CB = C1_CB*4.*ah_CB + OP1_CB*2.*bh_CB - C2_CB*bh_CB - C2_CB*3.*ah_CB;    //original
			//long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
			long double dOP1_CB = C2_CB*3.*ah_CB + OP2_CB*3.*bh_CB - OP1_CB*2.*(bh_CB+ah_CB);
			long double dOP2_CB = OP1_CB*2.*ah_CB + OP3_CB*4.*bh_CB - OP2_CB*(3.*bh_CB + ah_CB);
			long double dOP3_CB = ah_CB*OP2_CB - 4*bh_CB*OP3_CB;
        
			long double mh_CB = OP1_CB + OP2_CB + OP3_CB;
			long double ih_CB = mh_CB * ionvalue[2][3][0][0] * ( v_CB - (ionvalue[2][3][0][1]) );
        
			// IKv
			long double amKv_CB = 400 / ( exp( -(v_CB-15)/36 ) + 1. );
			long double bmKv_CB = 1.0 * exp( -v_CB / 13 );
        
			long double d_mKv_CB = amKv_CB * ( 1. - mKv_CB ) - bmKv_CB * mKv_CB;
        
			long double ahKv_CB = 0.0003 * exp( -v_CB / 7 );
			long double bhKv_CB = 80 / ( exp( -(-115-v_CB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
			long double d_hKv_CB = ahKv_CB * ( 1. - hKv_CB ) - bhKv_CB * hKv_CB;
        
			long double iKv_CB = ionvalue[2][3][1][0] * mKv_CB * mKv_CB * mKv_CB * hKv_CB*( v_CB - (ionvalue[2][3][1][1]) );
        
			// ICa			
			long double Vd_CB = 4/3*PIP_CB*(radius_d_CB*radius_d_CB*radius_d_CB)*1e-15;
			long double Vs_CB = 4/3*PIP_CB*(radius_CB*radius_CB*radius_CB)*1e-15-Vd_CB;
			long double Ssd_CB = 4*PIP_CB*radius_d_CB*radius_d_CB*1e-10;
			long double dsd_CB = ((radius_CB-radius_d_CB)/2 + radius_d_CB)*1e-5;
			        
			long double amCa_CB = 12000*( 120 - v_CB ) / ( exp( (120-v_CB)/25 ) - 1. );  //original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
			long double bmCa_CB = 40000 / ( 1.0 + exp( (68+v_CB)/25 ) );
			long double d_mCa_CB = amCa_CB * ( 1. - mCa_CB ) - bmCa_CB * mCa_CB;
			long double mCa_4_CB = pow( (long double)mCa_CB, (long double)4.0 );
        
			long double hCa_CB = exp( (50-v_CB)/11 )/( 1.0 + exp( (50-v_CB)/11) );
        
			long double ECa_CB = 12.9*log(Ca_o_CB/Ca_s_CB);
        
			long double iCa_CB = ionvalue[2][3][3][0]*mCa_4_CB*hCa_CB*(v_CB-ECa_CB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
			long double iNC_CB = Jnc_CB*exp(-(v_CB+14.)/70.) *( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 2.3 );
			long double iATP_CB = Jatp_CB*( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
			long double dbCa_ls_CB = Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) - Lb2_CB*bCa_ls_CB;
        
			long double dbCa_hs_CB = Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB) - Hb2_CB*bCa_hs_CB;
        
			long double dCa_s_CB = -(iCa_CB+iNC_CB+iATP_CB)/(2.*F_CB*Vs_CB)*1.0E-6 - Dca_CB*Ssd_CB/Vs_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ls_CB - Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) + Hb2_CB*bCa_hs_CB - Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB);
        
			long double dCa_d_CB = Dca_CB*Ssd_CB/Vd_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ld_CB - Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) + Hb2_CB*bCa_hd_CB - Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB);
        
			long double dbCa_ld_CB = Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) - Lb2_CB*bCa_ld_CB;
			long double dbCa_hd_CB = Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB) - Hb2_CB*bCa_hd_CB;
        
			// IK(Ca)
			long double mKca_c1_CB = Ca_s_CB / ( Ca_s_CB + 0.2 );
			long double amKca_CB = 100 * ( 230 - v_CB )/( exp( (230-v_CB)/52 ) - 1. );
			long double bmKca_CB = 120 * exp( -v_CB / 95 );
			long double d_mKca_CB = amKca_CB * ( 1. - mKca_CB ) - bmKca_CB * mKca_CB;
        
			long double iKca_CB = ionvalue[2][3][4][0] * mKca_c1_CB*mKca_CB*mKca_CB*(v_CB - (ionvalue[2][3][1][1]));
			// IL
			long double EL_CB = ionvalue[2][3][5][1];
			long double il_CB = ionvalue[2][3][5][0]*((v_CB-EL_CB));
        
			// IA
			long double amA_CB = 2400 / ( 1.0 + exp( -(v_CB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
			long double bmA_CB = 12 * exp( -v_CB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
			long double d_mA_CB = amA_CB * ( 1. - mA_CB ) - bmA_CB * mA_CB;
        
			long double ahA_CB = 0.045 * exp( -v_CB / 13 );
			long double bhA_CB = 75 / ( exp( -(30+v_CB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
			long double d_hA_CB = ahA_CB * ( 1.0 - hA_CB ) - bhA_CB * hA_CB;
        
        
			long double iA_CB = ionvalue[2][3][2][0] * pow( (long double)mA_CB, (long double)3.0 ) * hA_CB * ( v_CB - (ionvalue[2][3][1][1]) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
			// Isyn
			long double Isyn_CB = synapsevalue[2][2][0] * s_syn_CB[0][i] * (v_CB-synapsevalue[2][2][1]);
        
			// Total current and membrane potential of cone bipolar
			//long double Cm_CB = 0.01;
			long double Cm_CB = cellvalue[2][3];
			long double IALL_CB = iKca_CB + iCa_CB + ih_CB + iKv_CB + il_CB + iA_CB + Isyn_CB; //for chemical synapse simulation
			long double dV_CB   = (-IALL_CB + synapsevalue[2][4][0]*(VA_A-v_CB)) / Cm_CB; //for reference %for current clamp simulation
        
			// Amacrine
			//info from chemical synapse
			s_syn2_A[0][i]=S_C_RBA;
        
			// Na
			long double mtau_na_A = 1/(alpha_m_A(VA_A) + beta_m_A(VA_A));
			long double minf_na_A = alpha_m_A(VA_A) / (alpha_m_A(VA_A) + beta_m_A(VA_A));
			long double htau_na_A = 1/((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
			long double hinf_na_A = (alpha_h_A(VA_A)/3.5) / ((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
        
			long double dm_A = (minf_na_A-m_A)/mtau_na_A * tscale_A;
			long double dh_A = (hinf_na_A-h_A)/htau_na_A * tscale_A;
        
			long double gNa_A = ionvalue[2][4][0][0]*m_A*m_A*m_A*h_A;
        
			long double INa_A = gNa_A*(VA_A-ionvalue[2][4][0][1]);
        
			// K
			long double tau_k_A = 1/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
			long double inf_k_A = (alpha_n_A(VA_A)/5)/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
        
			long double dn_A = (inf_k_A-n_A)/tau_k_A * tscale_A;
        
			long double gK_A = ionvalue[2][4][1][0]*n_A*n_A*n_A*n_A;
        
			long double IK_A = gK_A*(VA_A-ionvalue[2][4][1][1]);
        
			// L
			long double Il_A = ionvalue[2][4][2][0]*(VA_A-ionvalue[2][4][2][1]);
        
			// Isyn
			long double Isyn2_A = synapsevalue[2][3][0] * s_syn2_A[0][i] * (VA_A-synapsevalue[2][3][1]);
        
			// Membrane potential of amacrine
			long double Iion_A = INa_A + IK_A + Il_A;
			long double Im_A = -Isyn2_A - Iion_A;
			long double dVA_A =(((Im_A) + synapsevalue[2][4][0]*(v_CB-VA_A)) /(Cm_A)) * tscale_A; // 0.2nS
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
			Vpre_C_CBG[0][i] = v_CB;
						
			//Vth_C_CBG = -40.85865173873610700638892012648284435272216796875000;
			Vth_C_CBG = Vpre_C_CBG[0][0];			

			//long double Vslope_C_CBG = 20;
			long double Vslope_C_CBG = synapsevalue[2][5][2];
			//long double tau_C_CBG = .01;
			long double tau_C_CBG = synapsevalue[2][5][3];

			long double Sinf_C_CBG = tanh(abs(Vpre_C_CBG[0][i] - Vth_C_CBG) /Vslope_C_CBG);
			long double d_st_C_CBG=0;

			//if (t <= 0.1)
			//	d_st_C_CBG = 0;
            
			if (Vpre_C_CBG[0][i] <= Vth_C_CBG) // 2015 December added [97-98 line].
				d_st_C_CBG = 0;
            
			else if (abs(Vpre_C_CBG[0][i]-Vth_C_CBG) >= 0) // NEW version
				d_st_C_CBG = (Sinf_C_CBG - S_C_CBG) / ((1-Sinf_C_CBG) * tau_C_CBG );
            
			else
				d_st_C_CBG = 0;

			if(t<data.light_start)
				d_st_C_CBG = 0;	
			
        
			// Ganglion
			//-------Na---
			long double alpha_Na_m_G = (-0.6*(V_G+30.0))/(exp(-0.1*(V_G+30.0))-1.0);
			long double beta_Na_m_G = 20.0*exp(-(V_G+55.0)/18.0);
			long double alpha_Na_h_G = 0.4*exp(-(V_G+50.0)/20.0);
			long double beta_Na_h_G = 6.0/(exp(-0.1*(V_G+20.0))+1.0);
			long double gNa_G = ionvalue[2][5][0][0]*(pow(Na_m_G,3))*Na_h_G;
        
			long double I_Na_G = gNa_G*(V_G-ionvalue[2][5][0][1]);
        
			long double dNa_m_G = (-(alpha_Na_m_G+beta_Na_m_G)*Na_m_G+alpha_Na_m_G) *tscale_G;
			long double dNa_h_G = (-(alpha_Na_h_G+beta_Na_h_G)*Na_h_G+alpha_Na_h_G) *tscale_G;
        
			//-------Ca, KCa---
			long double VCa_G = 1000.0*(R_G*T_G/(2*F_G))*log(Ca2e_G/Ca_i_G);
        
			long double alpha_Ca_n_G = (-0.3*(V_G+13.0))/(exp(-0.1*(V_G+13.0))-1.0);
			long double beta_Ca_n_G = 10.0*exp(-(V_G+38.0)/18.0);
			long double gCa_G = ionvalue[2][5][1][0]*(pow(Ca_n_G,3));
        
			long double I_Ca_G = gCa_G*(V_G-VCa_G);
        
			long double gKCa_G = ionvalue[2][5][3][0]*((pow((Ca_i_G/Ca2diss_G),2))/(1.0+(pow((Ca_i_G/Ca2diss_G),2))));
        
			long double I_KCa_G = gKCa_G*(V_G-ionvalue[2][5][2][1]);
        
			long double dCa_n_G = (-(alpha_Ca_n_G+beta_Ca_n_G)*Ca_n_G+alpha_Ca_n_G) *tscale_G;
			long double dCa_i_G = (-(((10^4)*3.0*I_Ca_G)/(2.0*F_G*r_G))-((Ca_i_G-Ca2res_G)/tCa_G)) *tscale_G;
        
			//-------K---        
			long double alpha_K_n_G = (-0.02*(V_G+40.0))/(exp(-0.1*(V_G+40.0))-1.0);
			long double beta_K_n_G = 0.4*exp(-(V_G+50.0)/80.0);
			long double gK_G = ionvalue[2][5][2][0]*(pow(K_n_G,4));
        
			long double I_K_G = gK_G*(V_G-ionvalue[2][5][2][1]);
        
			long double dK_n_G =  (-(alpha_K_n_G+beta_K_n_G)*K_n_G+alpha_K_n_G) *tscale_G;
        
			//-------A---        
			long double alpha_A_m_G = (-0.006*(V_G+90.0))/(exp(-0.1*(V_G+90.0))-1.0);
			long double beta_A_m_G = 0.1*exp(-(V_G+30.0)/10.0);
			long double alpha_A_h_G = 0.04*exp(-(V_G+70.0)/20.0);
			long double beta_A_h_G = 0.6/(exp(-0.1*(V_G+40.0))+1.0);
			long double gA_G = ionvalue[2][5][4][0]*(pow(A_m_G,3))*A_h_G;
        
			long double I_A_G = gA_G*(V_G-ionvalue[2][5][2][1]);
        
			long double dA_m_G=(-(alpha_A_m_G+beta_A_m_G)*A_m_G+alpha_A_m_G) *tscale_G;
			long double dA_h_G=(-(alpha_A_h_G+beta_A_h_G)*A_h_G+alpha_A_h_G) *tscale_G;
        
			//-------L---    
			long double I_leak_G = ionvalue[2][5][5][0]*(V_G-ionvalue[2][5][5][1]);
        
			//------ Isyn (in/20)---
			s_syn_G[0][i]=S_C_CBG;
			long double Isyn_G = (synapsevalue[2][5][0] * s_syn_G[0][i] * (V_G-synapsevalue[2][5][1]));
        
			//-------I---
			//long double Cm_G = 1.0;
			long double Cm_G = cellvalue[2][5];
			long double Iall_G = I_Na_G + I_Ca_G + I_KCa_G + I_K_G + I_A_G + I_leak_G;
			long double dV_G = ((-Isyn_G - Iall_G*20) / (Cm_G * 20)) * tscale_G ;

			// Rod Derivatives
			k[0][j] = dV_R;
			k[1][j] = dRh_R;
			k[2][j] = dRhi_R;
			k[3][j] = dTr_R;
			k[4][j] = dPDE_R;
			k[5][j] = dCa_R;
			k[6][j] = dCab_R;
			k[7][j] = dcGMP_R;
			k[8][j] = dC1_R;
			k[9][j] = dC2_R;
			k[10][j] = dO1_R;
			k[11][j] = dO2_R;
			k[12][j] = dO3_R;
			k[13][j] = dmKv_R;
			k[14][j] = dhKv_R;
			k[15][j] = dmCa_R;
			k[16][j] = dmKCa_R;
			k[17][j] = dCa_s_R;
			k[18][j] = dCa_f_R;
			k[19][j] = dCab_ls_R;
			k[20][j] = dCab_hs_R;
			k[21][j] = dCab_lf_R;
			k[22][j] = dCab_hf_R;
        
			// Cone Deriviates
			k[23][j] = dVC_C*1000;
			k[24][j] = dGf_C*1000;
			k[25][j] = dy1_C;
			k[26][j] = dy2_C;
			k[27][j] = dy3_C;
			k[28][j] = dy4_C;
			k[29][j] = dy5_C;
			k[30][j] = dz1_C;
			k[31][j] = dz2_C;
			k[32][j] = dz3_C;

			// Chemical Synapse Between Rod and Rod Bipolar Deriviates
			k[33][j]=d_st_C_RB;

			// Rod Bipolar Deriviates
			k[34][j] = dV_RB;
			k[35][j] = dC1_RB;
			k[36][j] = dC2_RB;
			k[37][j] = dOP1_RB;
			k[38][j] = dOP2_RB;
			k[39][j] = dOP3_RB;
			k[40][j] = d_mKv_RB;
			k[41][j] = d_hKv_RB;
			k[42][j] = d_mCa_RB;
			k[43][j] = d_mKca_RB;
			k[44][j] = dCa_s_RB;
			k[45][j] = dCa_d_RB;
			k[46][j] = dbCa_ls_RB;
			k[47][j] = dbCa_hs_RB;
			k[48][j] = dbCa_ld_RB;
			k[49][j] = dbCa_hd_RB;
			k[50][j] = d_mA_RB;
			k[51][j] = d_hA_RB;
       
			// Chemical Synapse Between Rod Bipolar and Amacrine Deriviates
			k[52][j]=d_st_C_RBA;
        
			// Chemical Synapse Between Cone and Cone Bipolar Deriviates
			k[53][j]=d_st_C_CCB;
       
			// Cone Bipolar Deriviates
			k[54][j] = dV_CB;
			k[55][j] = dC1_CB;
			k[56][j] = dC2_CB;
			k[57][j] = dOP1_CB;
			k[58][j] = dOP2_CB;
			k[59][j] = dOP3_CB;
			k[60][j] = d_mKv_CB;
			k[61][j] = d_hKv_CB;
			k[62][j] = d_mCa_CB;
			k[63][j] = d_mKca_CB;
			k[64][j] = dCa_s_CB;
			k[65][j] = dCa_d_CB;
			k[66][j] = dbCa_ls_CB;
			k[67][j] = dbCa_hs_CB;
			k[68][j] = dbCa_ld_CB;
			k[69][j] = dbCa_hd_CB;
			k[70][j] = d_mA_CB;
			k[71][j] = d_hA_CB;
        
			// Amacrine Deriviates
			k[72][j] = dVA_A;
			k[73][j] = dm_A;
			k[74][j] = dh_A;
			k[75][j] = dn_A;
        
			// Chemical Synapse Between Cone Bipolar and Ganglion Deriviates
			k[76][j]=d_st_C_CBG;
        
			// Ganglion Output
			k[77][j] = dV_G;
			k[78][j] = dNa_m_G;
			k[79][j] = dNa_h_G;
			k[80][j] = dCa_n_G;
			k[81][j] = dCa_i_G;
			k[82][j] = dK_n_G;
			k[83][j] = dA_m_G;
			k[84][j] = dA_h_G;

			if(j<=1)
			{
				for(int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep/2.0*k[l][j];  
			}
			else if(j==2)
			{
				for (int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep*k[l][j];
			}
			else if(j==3)
			{
				for (int l=0;l<85;l++)
				{
					ystar[l][i+1] = ystar[l][i]+data.tstep/6.0*(k[l][0]+2.0*k[l][1]+2.0*k[l][2]+k[l][3]);  

					if(t<data.light_start) // for stability
					{
						ystar[0][i+1]=y11[0][0];
						ystar[23][i+1]=y11[23][0];
					}
					
					y11[l][0] = ystar[l][i+1];
				}
				//if(i==0)
					//fprintf(fp[0], "Time, Rod Photocurrent, Rod Membrane Potential, Cone Membrane Potential, Activation Level of Synapse [R-RB], Rod Bipolar Membrane Potential, Activation Level of Synapse [RB-A], Activation Level of Synapse [C-CB], Cone Bipolar Membrane Potential, Amacrine Membrane Potential, Activation Level of Synapse [CB-G], Ganglion Membrane Potential\n");
				fprintf(fp,"%.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",real_t[0][i],Iphoto_R2[0][i],ystar[0][i],ystar[23][i],ystar[33][i],ystar[34][i],ystar[52][i],ystar[53][i],ystar[54][i],ystar[72][i],ystar[76][i],ystar[77][i]);
				
				if(i==0) // ploting with KST 
				{
					CopyFile("kst\\bin\\preset\\DualPath_Reference.kst","kst\\bin\\preset\\DualPath.kst",false);	
					ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\DualPath.kst",NULL,SW_SHOW);
				}			
			}           
		}
	}
	fclose(fp);

	ReplaceMsgBoard("Computation Finished.");
	ReplaceMsgBoard("Writing Temporary Output File Finished.");
	ReplaceMsgBoard("Drawing Simulation Graphs Finished.");

	/* Ploting with KST */
	//CopyFile("kst\\bin\\preset\\DualPath_Reference.kst","kst\\bin\\preset\\DualPath.kst",false);	
	//ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\DualPath.kst",NULL,SW_HIDE);

FREE:
	simulationsw_dual=0; //exit

	/* Free allocation */

	for(i=0;i<height;i++)
		free(ystar[i]);
	
	free(ystar);

	for(i=0;i<1;i++)
	{
		free(Vpre_C_RB[i]); 
		free(s_syn_RB[i]); 
		free(Vpre_C_RBA[i]);
		free(s_syn_CB[i]);  
		free(s_syn2_A[i]);  
		free(Vpre_C_CBG[i]);
		free(Vpre_C_CCB[i]);
		free(s_syn_G[i]);  
		free(real_t[i]);
	}

	free(Vpre_C_RB); 
	free(s_syn_RB); 
	free(Vpre_C_RBA);
	free(s_syn_CB);  
	free(s_syn2_A);  
	free(Vpre_C_CBG);
	free(Vpre_C_CCB);
	free(s_syn_G);
	free(real_t);

	ReplaceMsgBoard("Freeing Memory Finished.");
}
/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
void CRetinaModelSimulatorDlg::RodPathSimulation(void) //Simulation Run --> Rod Path Simulation
{
	#define NI (85) //Number of integrated variable

	/* Global parameter */
	// Rod cell phototransduction
	long double a1_R = 50; 
	long double a2_R = 0.0003; 
	long double a3_R = 0.03; 
	long double eps_R = 0.5;
	long double Ttot_R = 1000;
	long double b1_R = 2.5;
	long double tau1_R = 0.2;
	long double tau2_R = 5.0;
	long double PDEtot_R = 100;
	long double rCa_R = 50;
	long double c0_R = 0.1;
	long double b_R = 0.25;
	long double k1_R = 0.2;
	long double k2_R = 0.8;
	long double eT_R = 500;
	long double Vbar_R = 0.4;
	long double Kc_R = 0.1; 
	long double Amax_R= 65.6;
	long double sigma_R = 1.0; 
	long double Jmax_R = 5040;

	// Rod cell ion channel
	long double Eh_R = -32.0;
	long double EK_R = -74.0;
	long double ECl_R = -20.0;
	long double EL_R = -77.0;

	// Rod cell intracellular calcium system
	long double Jex_R = 20;
	long double Jex2_R = 20; 
	long double Kex_R = 2.3; 
	long double Kex2_R = 0.5;
	long double Cae_R = 0.01;
	long double F_R = 9.64846e4;
	long double V1_R = 3.812e-13; 
	long double V2_R = 5.236e-13; 
	long double DCa_R = 6e-8; 
	long double delta_R = 3e-5; 
	long double S1_R = 3.142e-8;
	long double Lb1_R = 0.4; 
	long double Lb2_R = 0.2; 
	long double Hb1_R = 100; 
	long double Hb2_R = 90; 
	long double BL_R = 500; 
	long double BH_R = 300;

	//// Cone cell
	//// [mV]     
	//long double E_C  = -72;
	//long double Vf_C = -57;
	//long double Ve_C = 4;

	//// [msec]
	//long double rL_C = 10;
	//long double rf_C = 67;

	//long double Gf_peak_C = 0.2;
	//long double Gi_peak_C = 0.7;     

	//// [sec]
	//long double K_C = 10;

	//// [/sec]
	//long double alpha_C    = 83.3;
	//long double k12_peak_C = 10;
	//long double k12M_C     = 250;
	//long double k23_C      = 17;
	//long double k34_C      = 1.3;
	//long double k32_C      = 0.03;

	//// [/sec^2]
	//long double v_C = 2.125; 
	//long double n_C = 6;
	//long double A_C = 6.76;

	//// Cone cell offset
	//long double offset;

	// Rod cell membrane capacitance
	//long double Cm_R = 0.02;
	long double Cm_R = cellvalue[0][0];

	// Chemical synbapse between rod and rod bipolar
	//long double Vslope_C_RB = 20;
	long double Vslope_C_RB = synapsevalue[0][0][2];
	//long double tau_C_RB = 0.01;
	long double tau_C_RB = synapsevalue[0][0][3];

	// Rod bipolar
	// Chemical Parameter 
	long double F_RB=9.649e4;
	long double Dca_RB=6.0e-8;

	// Morphologycal Parameter%
	// Soma: Diameter 12 micron
	long double PIP_RB = 3.14159;
	long double radius_RB = 6.0; 
	long double radius_d_RB = 5.6;

	// Chemical parameter         */
	long double Ca_o_RB = 2500.; 

	// Ca current parameter         */
	//long double gCa_RB = 1.1;
	long double gCa_RB = ionvalue[0][1][3][0];

	// Ca buffer parameter	     */
	long double LB_to1_RB = 300.; 
	long double HB_to1 = 100.; 
	long double LB_to2_RB = 500.; 
	long double HB_to2 = 300.; 
	long double Lb1_RB = 0.4; 
	long double Lb2_RB = 0.2; 
	long double Hb1_RB = 100.; 
	long double Hb2_RB = 90.; 

	// Ca exchanger & pump parameter   */
	long double Jnc_RB = 9.*40; 
	long double Jatp_RB = 9.5*40;
	long double Ca_e_RB = 0.01;

	// Rod bipolar ion channel
	long double EL_RB = -21.0;

	// Rod bipolar synaptic current
	long double gmax_syn_RB=2.56;

	// Rod bipolar membrane capacitance
	//long double Cm_RB = 0.01;
	long double Cm_RB = cellvalue[0][1];

	// Chemical synapse between rod bipolar and amacrine
	//long double Vslope_C_RBA = 20;
	//long double tau_C_RBA = .01;

	// Chemical synapse between cone and cone bipolar
	//long double Vslope_C_CCB = 20;
	//long double tau_C_CCB = .01;  

	//// Cone bipolar
	//// Chemical Parameter 
	//long double F_CB=9.649e4;
	//long double Dca_CB=6.0e-8;

	//// Morphologycal Parameter%
	//// Soma: Diameter 12 micron
	//long double PIP_CB = 3.14159;
	//long double radius_CB = 6.0; 
	//long double radius_d_CB = 5.6;

	//// Chemical parameter         */
	//long double Ca_o_CB = 2500.; 

	//// Ca current parameter         */
	//long double gCa_CB = 1.1;

	//// Ca buffer parameter	     */
	//long double LB_to1_CB = 300.; 
	//long double HB_to1_CB = 100.; 
	//long double LB_to2_CB = 500.; 
	//long double HB_to2_CB = 300.; 
	//long double Lb1_CB = 0.4;
	//long double Lb2_CB = 0.2; 
	//long double Hb1_CB = 100.; 
	//long double Hb2_CB = 90.;

	//// Ca exchanger & pump parameter   */
	//long double Jnc_CB = 9.*40; 
	//long double Jatp_CB = 9.5*40;
	//long double Ca_e_CB = 0.01;     

	//// Cone bipolar ionic channel
	//long double EL_CB = -21.0;

	//// Cone bipolar membrane capacitance
	//long double Cm_CB = 0.01;

	//// Amacrine cell
	//// Timescale
	//long double tscale_A = 1000;

	//// Reversal potential of amacrine [mV]
	//long double EK_A = -80.0;
	//long double ENa_A = 40.0;
	//long double El_A = -54;

	//// Maximum conductance of amacrine [nS]
	//long double gNa_bar_A = 4.0;
	//long double gK_bar_A  = 0.4;
	//long double gL_A      = 0.46;

	//// Membrane capacitance of amacrine [nF]
	//long double Cm_A = 20;

	//// Chemical synapse between cone bipolar and ganglion
	//long double Vslope_C_CBG = 20;
	//long double tau_C_CBG = .01;

	// Ganglion cell
	// Time scale
	long double tscale_G=1000; // scale to seconds factor

	//-------Na---
	//long double g_Na_G = 50.0;
	long double g_Na_G = ionvalue[0][2][0][0];
	//long double VNa_G = 35.0;
	long double VNa_G = ionvalue[0][2][0][1];

	//-------Ca, KCa---
	//long double g_Ca_G = 2.2;
	long double g_Ca_G = ionvalue[0][2][1][0];
	long double Ca2e_G = 1800;
	long double tCa_G = 50.0;
	long double Ca2res_G = 0.1;
	long double r_G = 12.5;
	//long double g_KCa_G = 0.05;
	long double g_KCa_G = ionvalue[0][2][3][0];
	long double Ca2diss_G = 1.0;
	long double R_G = 8.31;
	long double F_G = 96500;
	long double T_G = 293;        
	//long double VK_G = -75.0;
	long double VK_G = ionvalue[0][2][2][1];

	//-------K---
	//long double g_K_G = 12.0; 
	long double g_K_G = ionvalue[0][2][2][0];
		
	//-------A---
	//long double g_A_G = 36.0;
	long double g_A_G = ionvalue[0][2][4][0];

	//-------L---
	//long double g_L_G = 0.05;
	long double g_L_G = ionvalue[0][2][5][0];
	//long double VL_G = -62.0;
	long double VL_G = ionvalue[0][2][5][1];
		  
	//-------I---        
	//long double Cm_G = 1.0; 
	long double Cm_G = cellvalue[0][2];

	/* For preallocation */
	long double tlength;
	int height;
	int width;
	long double** ystar;
	long double** Vpre_C_RB;
	long double** s_syn_RB;
//	long double** Vpre_C_RBA;
//	long double** s_syn_CB;
//	long double** s_syn2_A;
//	long double** Vpre_C_CBG;
//	long double** Vpre_C_CCB;
	long double** Vpre_C_RBG;
	long double** s_syn_G;
	long double** Iphoto_R2; 

	long double** real_t;

	long double y11[85][4] = {0};
	long double k  [85][4] = {0};

	int percentage;

	struct data
	{
		long double tstart;
		long double tstep;
		long double tlast;
		long double duration;
		long double light_start;
		long double light_intensity;
		long double light_intensity_cone;
	};

	struct data data;

	//FILE* fp;

	data.tstart=t_fstart;
	data.tlast=t_fend;
	data.tstep=t_fstep;
	data.light_intensity=flightintensity;
	data.light_intensity_cone=flightintensity_cone;
	data.duration=flightduration;
	data.light_start=flightstart;

	ReplaceMsgBoard("Setting Global/External Parameters Finished.");

	/* Preallocation */
	int i,j;	

	tlength=round((data.tlast-data.tstart)/data.tstep +1);
	
	height= NI;
	width=(int)tlength +1;	

	ystar = (long double **) malloc(sizeof(long double*) * height);
	Vpre_C_RB = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_RB = (long double **) malloc(sizeof(long double*) * 1);
//	Vpre_C_RBA = (long double **) malloc(sizeof(long double*) * 1);
//	s_syn_CB = (long double **) malloc(sizeof(long double*) * 1);
//	s_syn2_A = (long double **) malloc(sizeof(long double*) * 1);
//	Vpre_C_CBG = (long double **) malloc(sizeof(long double*) * 1);
//	Vpre_C_CCB = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_RBG = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_G = (long double **) malloc(sizeof(long double*) * 1);
	real_t = (long double **) malloc(sizeof(long double*) * 1);
	Iphoto_R2 = (long double **) malloc(sizeof(long double*) *1);
	
	for(i=0; i<height;i++)
	{
		ystar[i]=(long double *) malloc(sizeof(long double) * width); //long double ystar[85,tlength];
	}
	
	for(i=0;i<1;i++)
	{
		Vpre_C_RB[i] = (long double *) malloc(sizeof(long double) * width);
		s_syn_RB[i]  = (long double *) malloc(sizeof(long double) * width);
//		Vpre_C_RBA[i]= (long double *) malloc(sizeof(long double) * width);
//		s_syn_CB[i]  = (long double *) malloc(sizeof(long double) * width);
//		s_syn2_A[i]  = (long double *) malloc(sizeof(long double) * width);
//		Vpre_C_CBG[i]= (long double *) malloc(sizeof(long double) * width);
//		Vpre_C_CCB[i]= (long double *) malloc(sizeof(long double) * width);
		Vpre_C_RBG[i]= (long double *) malloc(sizeof(long double) * width);
		s_syn_G[i]   = (long double *) malloc(sizeof(long double) * width);
		real_t[i]    = (long double *) malloc(sizeof(long double) * width);
		Iphoto_R2[i] = (long double *) malloc(sizeof(long double) * width);
	}
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			ystar[i][j]=0;			
		}		
	}	

	for(i=0;i<1;i++)
		for(j=0;j<width;j++)
		{
			Vpre_C_RB[i][j]=0;
			s_syn_RB[i][j]=0;
//			Vpre_C_RBA[i][j]=0;
//			s_syn_CB[i][j]=0;
//			s_syn2_A[i][j]=0;
//			Vpre_C_CBG[i][j]=0;
//			Vpre_C_CCB[i][j]=0;
			Vpre_C_RBG[i][j]=0;
			s_syn_G[i][j]=0;
			real_t[i][j]=0;
		}
	ReplaceMsgBoard("Memory Dynamic Preallocation Finished.");

	/* Initial Condition */
	// Rod and Cone cell Initial Condition
	y11[0][0] = -36.185963;          // V(0][0], resting membrane potential  
	y11[1][0] = 0.0;                 // Rh(0][0]
	y11[2][0] = 0.0;                 // Rhi(0][0]
	y11[3][0] = 0.0;                 // Tr(0][0]
	y11[4][0] = 0.0;                 // PDE(0][0]
	y11[5][0] = 0.300000000000037;   // Ca(0][0]
	y11[6][0] = 34.883720929940061;  // Cab(0][0]
	y11[7][0] = 2.000000000017296;   // cGMP(0][0]
	y11[8][0] = 0.64582664;          // C1(0][0], Ih
	y11[9][0]= 0.29823381;          // C2(0][0], Ih
	y11[10][0]= 0.051645089;         // O1(0][0], Ih
	y11[11][0]= 0.0039748312;        // O2(0][0], Ih
	y11[12][0]= 0.00011472013;       // O3(0][0], Ih
	y11[13][0]= 0.43018469;          // mKv(0][0], IKv
	y11[14][0]= 0.99927789;          // hKv(0][0], IKv
	y11[15][0]= 0.43647161;          // mCa(0][0], ICa
	y11[16][0]= 0.64228624;          // mKCa(0][0], IKCa
	y11[17][0]= 0.096557982;         // [Ca]s(0][0]
	y11[18][0]= 0.096558392;         // [Ca]f(0][0]
	y11[19][0]= 80.92926;            // [Cab]ls(0][0]
	y11[20][0]= 29.067444;           // [Cab]hs(0][0]
	y11[21][0]= 80.929703;           // [Cab]lf(0][0]
	y11[22][0]= 29.067556;           // [Cab]hf(0][0]
	// y11[23][0] = -45.76654665646767500000000000000000000000000000000000;
	// y11[24][0] = 0.01137478132545304700000000000000000000000000000000;
	// y11[25][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[26][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[27][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[28][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[29][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[30][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[31][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[32][0] = 0.00000000000000000000000000000000000000000000000000;
	// offset=42.2321233629648844498660764656960964202880859375; // Cone Cell Membrane Potential offset

	//// Chemical Synapse Between Rod and Rod Bipolar Initial Condition
	y11[33][0] = 0;

	//// Rod Bipolar Initial Condition
	y11[34][0] = -36.424516776897130;
	y11[35][0] = 0.928238175043767;
	y11[36][0] = 0.054905344261992;
	y11[37][0] = 0.001217870414180;
	y11[38][0] = 1.200618479085905e-05;
	y11[39][0] = 4.438540983730620e-08;
	y11[40][0] = 0.824374082910590;
	y11[41][0] = 0.109794106890060;
	y11[42][0] = 0.290203193088928;
	y11[43][0] = 0.475464147362579;
	y11[44][0] = 0.011561930331728;
	y11[45][0] = 0.011563608687641;
	y11[46][0] = 6.780371247710756;
	y11[47][0] = 1.268364765067093;
	y11[48][0] = 11.302574980627850;
	y11[49][0] = 3.805639865311822;
	y11[50][0] = 0.186127778073054;
	y11[51][0] = 0.024443585120781;

	// //// Chemical Synapse Between Rod Bipolar and Amacrine Initial Condition
	// y11[52][0] = 0;
	// 

	// //// Chemical Synapse Between Cone and Cone Bipolar Initial Condition
	// y11[53][0] = 0;
	// 

	// //// Cone Bipolar Initial Condition
	// y11[54][0] = -40.85865173873610700638892012648284435272216796875000;
	// y11[55][0] = 0.91442826153121192778172598991659469902515411376953;
	// y11[56][0] = 0.06802394011168773346742710828038980253040790557861;
	// y11[57][0] = 0.00189760228726293194399799002525242030969820916653;
	// y11[58][0] = 0.00002352697486413260014254458796223445915529737249;
	// y11[59][0] = 0.00000010938512049644076438087637219778724961827265;
	// y11[60][0] = 0.75119613755960557011093214896391145884990692138672;
	// y11[61][0] = 0.12833933300174665825821307407750282436609268188477;
	// y11[62][0] = 0.23512534165859483303862020875385496765375137329102;
	// y11[63][0] = 0.44667148688898017372395088386838324368000030517578;
	// y11[64][0] = 0.01069015667321450424598339168369420804083347320557;
	// y11[65][0] = 0.01146115054172941634391680310045558144338428974152;
	// y11[66][0] = 6.69114537743995629881510467384941875934600830078125;
	// y11[67][0] = 1.17390152355585408727733920386526733636856079101562;
	// y11[68][0] = 11.29221858507642828328698669793084263801574707031250;
	// y11[69][0] = 3.77261483646810091840961831621825695037841796875000;
	// y11[70][0] = 0.11197954384331872124125339951206115074455738067627;
	// y11[71][0] = 0.04078196799520746040901286733060260303318500518799;
	// 

	// //// Amacrine Initial Condition
	// y11[72][0] = -50.34951375105524107311794068664312362670898437500000;
	// y11[73][0] = 0.24340676136333766477193307764537166804075241088867;
	// y11[74][0] = 0.15952849172211810979682411471003433689475059509277;
	// y11[75][0] = 0.54575595513993369056748861112282611429691314697266;
	// 

	// // Temperature of amacrine
	// global celcius_Na_A;
	// global celcius_K_A;
	// celcius_Na_A = 22;
	// celcius_K_A  = 22;
	// 

	// //// Chemical Synapse Between Cone Bipolar and Ganglion Initial Condition
	// y11[76][0] = 0;

	//// Chemical Synapse Between Rod Bipolar and Ganglion Initial Condition
	y11[76][0] = 0;

	//// Ganglion Initial Condition
	y11[77][0]=-61.698524;
	y11[78][0]=0.027940;
	y11[79][0]=0.887161;
	y11[80][0]=0.003019;
	y11[81][0]=0.100007;
	y11[82][0]=0.107809;
	y11[83][0]=0.070467;
	y11[84][0]=0.300453;

	for(i=0;i<NI;i++)
	{
		ystar[i][0]=y11[i][0];
	}

	 ReplaceMsgBoard("Derivatives Initialization Finished.");

	 ReplaceMsgBoard("*** Rod Path Simulation (R+RB+G) ***");
	 CString announce, announce2, announce3;
	 announce.Format("Start Time = %f, End Time = %f, Time Step = %f",data.tstart,data.tlast,data.tstep);
	 announce2.Format("Light Intensity for Rod = %f",data.light_intensity);
	 announce3.Format("Light Starting Time = %f, Light Duration = %f",data.light_start,data.duration);
	 ReplaceMsgBoard(announce);
	 ReplaceMsgBoard(announce2);
	 ReplaceMsgBoard(announce3);
	 ReplaceMsgBoard(" ");

	 CString announce4, announce5, announce6, announce7, announce8, announce9, announce10;

	 ReplaceMsgBoard("** Rod Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[0][0]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f",ionvalue[0][0][0][0],ionvalue[0][0][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f",ionvalue[0][0][1][0], ionvalue[0][0][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[0][0][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium-Chloride Current *");
	 announce8.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][0][3][0], ionvalue[0][0][3][1]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[0][0][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][0][5][0], ionvalue[0][0][5][1]);
	 ReplaceMsgBoard(announce10);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Rod Bipolar Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[0][1]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][1][0][0], ionvalue[0][1][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][1][1][0], ionvalue[0][1][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Transient Outward Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[0][1][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[0][1][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[0][1][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][1][5][0], ionvalue[0][1][5][1]);
	 ReplaceMsgBoard(announce10);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Ganglion Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[0][2]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Sodium Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][2][0][0], ionvalue[0][2][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce6.Format("Maximum Conductance = %f", ionvalue[0][2][1][0]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce7.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][2][2][0], ionvalue[0][2][2][1]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[0][2][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* A Type Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[0][2][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[0][2][5][0], ionvalue[0][2][5][1]);
	 ReplaceMsgBoard(announce10);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (R-RB) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f",synapsevalue[0][0][0], synapsevalue[0][0][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[0][0][2], synapsevalue[0][0][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (RB-G) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[0][1][0], synapsevalue[0][1][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[0][1][2], synapsevalue[0][1][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	/* Model */
	long double t;

	percentage = 0;

	fp = fopen("C:\\Output_RodPath.dat","w+");
	checkfp++;

	for(i=0;i<(int)(tlength);i++)
	{
		if(simulationstop==1)
		{
			simulationstop=0;
			fclose(fp);
			remove("C:\\Output_RodPath.dat");
			goto FREE;
		}

		t=(long double)i*data.tstep + data.tstart;
		real_t[0][i]=t;

		int perfect=(int)tlength-1;
		int perfect2=perfect/100;

		if(i%perfect2==0)
		{	
			CString c_simulationprogress;
			c_simulationprogress.Format("Simulation %d %% Finished.",percentage++);

			if((percentage-1)%10==0)
			{
				ReplaceMsgBoard(c_simulationprogress);
			}
			
			progress.StepIt();
		}

		for(j=0;j<4;j++) //4th order
		{
			// ROD
			long double V_R   = y11[0][j];             // membrane potential (mV)
			// outer segment
			long double Rh_R  = y11[1][j];             // active rhodopsin (uM)
			long double Rhi_R = y11[2][j];             // inactive rhodopsin (uM)
			long double Tr_R  = y11[3][j];             // active transducin (uM)
			long double PDE_R = y11[4][j];             // active phosphodiesterase (uM)
			long double Ca_R  = y11[5][j];             // intracellular free Ca in outer segment (uM)
			long double Cab_R = y11[6][j];             // intracellular Ca buffer in outer segment (uM)
			long double cGMP_R= y11[7][j];             // cyclic GMP (uM)
			// Ih
			long double C1_R  = y11[8][j];
			long double C2_R  = y11[9][j];
			long double O1_R  = y11[10][j];
			long double O2_R  = y11[11][j];
			long double O3_R  = y11[12][j];
			// IKv, ICa, IKCa
			long double mKv_R  = y11[13][j];
			long double hKv_R = y11[14][j];
			long double mCa_R  = y11[15][j];
			long double mKCa_R = y11[16][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_R  = y11[17][j];
			long double Ca_f_R  = y11[18][j];
			long double Cab_ls_R= y11[19][j];
			long double Cab_hs_R= y11[20][j];
			long double Cab_lf_R= y11[21][j];
			long double Cab_hf_R= y11[22][j];
			// CONE
//			long double VC_C = y11[23][j];             // membrane potential (mV)
//			long double Gf_C = y11[24][j];
//			long double y1_C = y11[25][j];
//			long double y2_C = y11[26][j];
//			long double y3_C = y11[27][j];
//			long double y4_C = y11[28][j];
//			long double y5_C = y11[29][j];
//			long double z1_C = y11[30][j];
//			long double z2_C = y11[31][j];
//			long double z3_C = y11[32][j];
        
			// Chemical Synapse Between Rod and Rod Bipolar
			long double S_C_RB = y11[33][j];
        
			// Rod Bipolar
			long double v_RB   = y11[34][j];             // membrane potential (mV)
			long double C1_RB  = y11[35][j];
			long double C2_RB  = y11[36][j];
			long double OP1_RB  = y11[37][j];
			long double OP2_RB  = y11[38][j];
			long double OP3_RB  = y11[39][j];
			// IKv, ICa, IKCa
			long double mKv_RB  = y11[40][j];
			long double hKv_RB = y11[41][j];
			long double mCa_RB  = y11[42][j];
			long double mKca_RB = y11[43][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_RB  = y11[44][j];
			long double Ca_d_RB  = y11[45][j];
			long double bCa_ls_RB= y11[46][j];
			long double bCa_hs_RB= y11[47][j];
			long double bCa_ld_RB= y11[48][j];
			long double bCa_hd_RB= y11[49][j];
			// IA
			long double mA_RB= y11[50][j];
			long double hA_RB= y11[51][j];
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
//			long double S_C_RBA = y11[52][j];
        
			// Chemical Synapse Between Cone and Cone Bipolar
//			long double S_C_CCB = y11[53][j];
        
			// Cone Bipolar
//			long double v_CB   = y11[54][j];             // membrane potential (mV)
			// Ih
//			long double C1_CB  = y11[55][j];
//			long double C2_CB  = y11[56][j];
//			long double OP1_CB  = y11[57][j];
//			long double OP2_CB  = y11[58][j];
//			long double OP3_CB  = y11[59][j];
			// IKv, ICa, IKCa
//			long double mKv_CB  = y11[60][j];
//			long double hKv_CB = y11[61][j];
//			long double mCa_CB  = y11[62][j];
//			long double mKca_CB = y11[63][j];
			// Intracellular calcium system in inner segment
//			long double Ca_s_CB  = y11[64][j];
//			long double Ca_d_CB  = y11[65][j];
//			long double bCa_ls_CB= y11[66][j];
//			long double bCa_hs_CB= y11[67][j];
//			long double bCa_ld_CB= y11[68][j];
//			long double bCa_hd_CB= y11[69][j];
			// IA
//			long double mA_CB= y11[70][j];
//			long double hA_CB= y11[71][j];
        
			// Amacrine
//			long double VA_A = y11[72][j];             // membrane potential (mV)
//			long double m_A = y11[73][j];
//			long double h_A = y11[74][j];
//			long double n_A = y11[75][j];
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
//			long double S_C_CBG = y11[76][j];

			// Chemical Synapse Between Rod Bipolar and Ganglion
			long double S_C_RBG = y11[76][j];

			// Ganglion
			long double V_G = y11[77][j];
			long double Na_m_G = y11[78][j];
			long double Na_h_G = y11[79][j];
			long double Ca_n_G = y11[80][j];
			long double Ca_i_G = y11[81][j];
			long double K_n_G = y11[82][j];
			long double A_m_G = y11[83][j];
			long double A_h_G = y11[84][j];			

			// ROD
			// Phototransduction   
			//long double jhv_R = data.light_intensity *( heav(t-(data.tstart+data.light_start)) - heav(t-(data.tstart+data.light_start+data.duration)) ) ; //pulse

			long double jhv_R = 0;
			
			if (data.light_start <= t && t <= data.light_start + data.duration)
				jhv_R = data.light_intensity;
			else
				jhv_R = 0.0;	

			long double dRh_R  = jhv_R - a1_R*Rh_R + a2_R*Rhi_R;
			long double dRhi_R = a1_R*Rh_R - (a2_R+a3_R)*Rhi_R;
			long double dTr_R  = eps_R*Rh_R*(Ttot_R-Tr_R) - b1_R*Tr_R + tau2_R*PDE_R - tau1_R*Tr_R*(PDEtot_R-PDE_R);
			long double dPDE_R = tau1_R*Tr_R*(PDEtot_R-PDE_R) - tau2_R*PDE_R;
			long double J_R    = Jmax_R*pow(cGMP_R,3) / (pow(cGMP_R,3)+1000);
			long double dCa_R  = b_R*J_R - rCa_R*(Ca_R-c0_R) - k1_R*(eT_R-Cab_R)*Ca_R + k2_R*Cab_R;
			long double dCab_R = k1_R*(eT_R-Cab_R)*Ca_R - k2_R*Cab_R;
			long double dcGMP_R= Amax_R/(1.0+(pow(Ca_R,4)/pow(Kc_R,4))) - cGMP_R*(Vbar_R+sigma_R*PDE_R);
        
			long double Iphoto_R = -Jmax_R*pow(cGMP_R,3)/(pow(cGMP_R,3)+1000)*(1-exp((V_R-8.5)/17));
			Iphoto_R2[0][i]=Iphoto_R;
        
			// Ih			
			long double ahh_R = 8 / ( exp((V_R+78)/14) + 1);
			long double bhh_R = 18 / ( exp(-(V_R+8)/19) + 1);
			long double dC1_R = -4*ahh_R*C1_R + bhh_R*C2_R;
			long double dC2_R =  4*ahh_R*C1_R - (3*ahh_R+bhh_R)*C2_R + 2*bhh_R*O1_R;
			long double dO1_R =  3*ahh_R*C2_R - (2*ahh_R+2*bhh_R)*O1_R + 3*bhh_R*O2_R;
			long double dO2_R =  2*ahh_R*O1_R - (ahh_R+3*bhh_R)*O2_R + 4*bhh_R*O3_R;
			long double dO3_R =  ahh_R*O2_R - 4*bhh_R*O3_R;
			long double Ih_R  = ionvalue[0][0][0][0]*(O1_R+O2_R+O3_R)*(V_R-ionvalue[0][0][0][1]);
			// IKv			
			long double amKv_R = 5*(100-V_R) / (exp( (100-V_R)/42 ) - 1 );
			long double bmKv_R = 9*exp( -(V_R-20)/40 );
			long double ahKv_R = 0.15*exp( -V_R/22 );
			long double bhKv_R = 0.4125 / ( exp( (10-V_R)/7 ) + 1 );
			long double dmKv_R = amKv_R*(1-mKv_R) - bmKv_R*mKv_R;
			long double dhKv_R = ahKv_R*(1-hKv_R) - bhKv_R*hKv_R;
			long double IKv_R  = ionvalue[0][0][1][0]*pow(mKv_R,3)*hKv_R*(V_R-ionvalue[0][0][1][1]);
			// ICa
			long double amCa_R = 3*(80-V_R) / ( exp( (80-V_R)/25 ) -1 );
			long double bmCa_R = 10 / ( 1 + exp( (V_R+38)/7 ) );
			long double hCa_R  = exp( (40-V_R)/18 ) / ( 1 + exp( (40-V_R)/18 ) );
			long double dmCa_R = amCa_R*(1-mCa_R) - bmCa_R*mCa_R;
			long double ECa_R  = -12.5*log(Ca_s_R/1600);
			long double ICa_R  = ionvalue[0][0][2][0]*pow(mCa_R,4)*hCa_R*(V_R-ECa_R);
        
			// ICl(Ca)			
			long double mCl_R  = 1.0 / ( 1 + exp( (0.37-Ca_s_R) / 0.09  ) );
			long double IClCa_R = ionvalue[0][0][3][0]*mCl_R*(V_R-ionvalue[0][0][3][1]);
        
			// IK(Ca)
			long double amKCa_R = 15*(80-V_R) / ( exp( (80-V_R)/40 ) - 1 );
			long double bmKCa_R = 20*exp( -V_R/35 );
			long double dmKCa_R = amKCa_R*(1-mKCa_R) - bmKCa_R*mKCa_R;
			long double mKCa_s_R = Ca_s_R / (Ca_s_R + 0.3 );
			long double IkCa_R = ionvalue[0][0][4][0] * mKCa_R * mKCa_R * mKCa_s_R * (V_R-ionvalue[0][0][1][1]);
        
			// IL			
			long double IL_R = ionvalue[0][0][5][0]*(V_R-ionvalue[0][0][5][1]);        
        
			// Intracellular calcium system
			long double Iex_R = Jex_R *exp( -(V_R+14)/70 ) * (Ca_s_R - Cae_R) / ( Ca_s_R - Cae_R + Kex_R );
			long double Iex2_R= Jex2_R*( Ca_s_R - Cae_R ) / ( Ca_s_R -Cae_R + Kex2_R );
			long double dCa_s_R = - (ICa_R + Iex_R + Iex2_R ) / ( 2.0 * F_R * V1_R ) * 1e-06 - DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V1_R ) - Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) + Lb2_R *Cab_ls_R - Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) + Hb2_R * Cab_hs_R;
			long double dCa_f_R =   DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V2_R ) - Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) + Lb2_R * Cab_lf_R - Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) + Hb2_R * Cab_hf_R;
			long double dCab_ls_R = Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) - Lb2_R * Cab_ls_R;
			long double dCab_hs_R = Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) - Hb2_R * Cab_hs_R;
			long double dCab_lf_R = Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) - Lb2_R * Cab_lf_R;
			long double dCab_hf_R = Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) - Hb2_R * Cab_hf_R;			

			// CONE
//			long double I_C;

//			if (data.light_start <= t && t <= data.light_start + data.duration)
//				I_C = data.light_intensity_cone;
//			else
//				I_C = 0.0;		
        
			// activation and inactivation rates
//			long double Gi_C  = Gi_peak_C/(1+z1_C/K_C);
//			long double F_C   = Gf_peak_C/(1+exp((VC_C-Vf_C)/Ve_C));
//			long double k12_C = k12_peak_C+v_C*z2_C*(k12M_C-k12_peak_C)/(k12M_C-k12_peak_C+v_C*z2_C);
//			long double k21_C = k12_C/6.76;
        
//			long double dGf_C  = (F_C-Gf_C)/rf_C;
//			long double dy1_C  = I_C - alpha_C * y1_C;
//			long double dy2_C  = alpha_C * (y1_C - y2_C);
//			long double dy3_C  = alpha_C * (y2_C - y3_C);
//			long double dy4_C  = alpha_C * (y3_C - y4_C);
//			long double dy5_C  = alpha_C * (y4_C - y5_C);
//			long double dz1_C  = alpha_C * y5_C - k12_C * z1_C + k21_C * z2_C;
//			long double dz2_C  = k12_C * z1_C - (k21_C + k23_C) * z2_C + k32_C * z3_C;
//			long double dz3_C  = k23_C * z2_C - (k32_C + k34_C) * z3_C;

			// Rod and Cone Total Current and Membrane Potential			
			long double IALL_R = Iphoto_R + Ih_R + IKv_R + ICa_R + IClCa_R + IkCa_R + IL_R +Iex_R + Iex2_R ;
            long double dV_R   = -IALL_R/Cm_R;
//			long double dV_R   = (-IALL_R + 0.2*((VC_C + offset)-V_R))/Cm_R; // All electrical synapses between cones and rods have the same conductance value of 0.2nS [35]. FROM PUBLIO 2009
//			long double dVC_C   = (E_C-VC_C*(1+Gf_C+Gi_C) + 0.2*(V_R-(VC_C + offset)))/rL_C;

			// Chemical Synapse Between Rod and Rod Bipolar			
			Vpre_C_RB[0][i]=V_R;
			long double Vth_C_RB = Vpre_C_RB[0][0];

			long double Sinf_C_RB = tanh(abs(Vpre_C_RB[0][i] - Vth_C_RB)/Vslope_C_RB);
			
			long double d_st_C_RB = 0;
			if (Vpre_C_RB[0][i] >= Vth_C_RB) // 2015 December added [97-98 line].
				d_st_C_RB = 0;
			else if (abs(Vpre_C_RB[0][i]-Vth_C_RB) >= 0) // New version
				d_st_C_RB = (Sinf_C_RB - S_C_RB) / ((1-Sinf_C_RB) * tau_C_RB );
			else
				d_st_C_RB = 0;

			if(t<data.light_start)
				d_st_C_RB = 0;				
        
			// Rod Bipolar
			s_syn_RB[0][i]=S_C_RB;
			// Ih
			long double ah_RB = 3 / ( exp( (v_RB+110)/15 ) + 1. );
			long double bh_RB = 1.5 / ( exp( -(v_RB+115)/15 ) + 1. );
        
			long double dC1_RB = bh_RB*C2_RB - 4.*ah_RB*C1_RB;
			long double dC2_RB = C1_RB*4.*ah_RB + OP1_RB*2.*bh_RB - C2_RB*bh_RB - C2_RB*3.*ah_RB;    //original
			// long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
			long double dOP1_RB = C2_RB*3.*ah_RB + OP2_RB*3.*bh_RB - OP1_RB*2.*(bh_RB+ah_RB);
			long double dOP2_RB = OP1_RB*2.*ah_RB + OP3_RB*4.*bh_RB - OP2_RB*(3.*bh_RB + ah_RB);
			long double dOP3_RB = ah_RB*OP2_RB - 4*bh_RB*OP3_RB;
        
			long double mh_RB = OP1_RB + OP2_RB + OP3_RB;
			long double ih_RB = mh_RB * ionvalue[0][1][0][0] * ( v_RB - (ionvalue[0][1][0][1]) );
        
			// IKv
			long double amKv_RB = 400 / ( exp( -(v_RB-15)/36 ) + 1. );
			long double bmKv_RB = 1.0 * exp( -v_RB / 13 );
        
			long double d_mKv_RB = amKv_RB * ( 1. - mKv_RB ) - bmKv_RB * mKv_RB;
        
			long double ahKv_RB = 0.0003 * exp( -v_RB / 7 );
			long double bhKv_RB = 80 / ( exp( -(-115-v_RB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
			long double d_hKv_RB = ahKv_RB * ( 1. - hKv_RB ) - bhKv_RB * hKv_RB;
        
			long double iKv_RB = ionvalue[0][1][1][0] * mKv_RB * mKv_RB * mKv_RB * hKv_RB*( v_RB - (ionvalue[0][1][1][1]) );
        
			// ICa
			long double Vd_RB = 4/3*PIP_RB*(radius_d_RB*radius_d_RB*radius_d_RB)*1e-15;
			long double Vs_RB = 4/3*PIP_RB*(radius_RB*radius_RB*radius_RB)*1e-15-Vd_RB;
			long double Ssd_RB = 4*PIP_RB*radius_d_RB*radius_d_RB*1e-10;
			long double dsd_RB = ((radius_RB-radius_d_RB)/2 + radius_d_RB)*1e-5;
			        
			long double amCa_RB = 12000*( 120 - v_RB ) / ( exp( (120-v_RB)/25 ) - 1. );  // original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
			long double bmCa_RB = 40000 / ( 1.0 + exp( (68+v_RB)/25 ) );
			long double d_mCa_RB = amCa_RB * ( 1. - mCa_RB ) - bmCa_RB * mCa_RB;
			long double mCa_4_RB = pow((long double) mCa_RB, (long double)4.0 );
        
			long double hCa_RB = exp( (50-v_RB)/11 )/( 1.0 + exp( (50-v_RB)/11) );
        
			long double ECa_RB = 12.9*log(Ca_o_RB/Ca_s_RB);
        
			long double iCa_RB = gCa_RB*mCa_4_RB*hCa_RB*(v_RB-ECa_RB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
			long double iNC_RB = Jnc_RB*exp(-(v_RB+14.)/70.) *( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 2.3 );
			long double iATP_RB = Jatp_RB*( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
			long double dbCa_ls_RB = Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) - Lb2_RB*bCa_ls_RB;
        
			long double dbCa_hs_RB = Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB) - Hb2_RB*bCa_hs_RB;
        
			long double dCa_s_RB = -(iCa_RB+iNC_RB+iATP_RB)/(2.*F_RB*Vs_RB)*1.0E-6 - Dca_RB*Ssd_RB/Vs_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ls_RB - Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) + Hb2_RB*bCa_hs_RB - Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB);
        
			long double dCa_d_RB = Dca_RB*Ssd_RB/Vd_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ld_RB - Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) + Hb2_RB*bCa_hd_RB - Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB);
        
			long double dbCa_ld_RB = Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) - Lb2_RB*bCa_ld_RB;
			long double dbCa_hd_RB = Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB) - Hb2_RB*bCa_hd_RB;
        
			// IK(Ca)
			long double mKca_c1_RB = Ca_s_RB / ( Ca_s_RB + 0.2 );
			long double amKca_RB = 100 * ( 230 - v_RB )/( exp( (230-v_RB)/52 ) - 1. );
			long double bmKca_RB = 120 * exp( -v_RB / 95 );
			long double d_mKca_RB = amKca_RB * ( 1. - mKca_RB ) - bmKca_RB * mKca_RB;
        
			long double iKca_RB = ionvalue[0][1][4][0] * mKca_c1_RB*mKca_RB*mKca_RB*(v_RB - (ionvalue[0][1][1][1]));
			// IL
			long double EL_RB = ionvalue[0][1][5][1];
			long double il_RB = ionvalue[0][1][5][0]*((v_RB-EL_RB));
        
			// IA
			long double amA_RB = 2400 / ( 1.0 + exp( -(v_RB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
			long double bmA_RB = 12 * exp( -v_RB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
			long double d_mA_RB = amA_RB * ( 1. - mA_RB ) - bmA_RB * mA_RB;
        
			long double ahA_RB = 0.045 * exp( -v_RB / 13 );
			long double bhA_RB = 75 / ( exp( -(30+v_RB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
			long double d_hA_RB = ahA_RB * ( 1.0 - hA_RB ) - bhA_RB * hA_RB;
        
        
			long double iA_RB = ionvalue[0][1][2][0] * pow( (long double)mA_RB, (long double)3.0 ) * hA_RB * ( v_RB - (ionvalue[0][1][1][1]) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
        
			// Isyn
			//long double gmax_syn_RB=2.56; //nS
			long double gmax_syn_RB = synapsevalue[0][0][0];
			long double Isyn_RB = gmax_syn_RB * s_syn_RB[0][i] * (v_RB-synapsevalue[0][0][1]);
        
        
			// Total current and membrane potential
			//long double Cm_RB = 0.01;
			long double Cm_RB = cellvalue[0][1];

			long double IALL_RB = iKca_RB + iCa_RB + ih_RB + iKv_RB + il_RB + iA_RB + Isyn_RB; //for chemical synapse simulation
			long double dV_RB   = -IALL_RB / Cm_RB; //for reference %for current clamp simulation
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
//			Vpre_C_RBA[0][i]=v_RB;
//			long double Vth_C_RBA = -36.424516776897130;
//			long double Vslope_C_RBA = 20;
//			long double tau_C_RBA = .01;
        
//			long double Sinf_C_RBA = tanh(abs(Vpre_C_RBA[0][i] - Vth_C_RBA)/Vslope_C_RBA);
//			long double d_st_C_RBA = 0;

//			if (abs(Vpre_C_RBA[0][i]-Vth_C_RBA) >= 0) // New version
//				d_st_C_RBA = (Sinf_C_RBA - S_C_RBA) / ((1-Sinf_C_RBA) * tau_C_RBA );
//			else
//				d_st_C_RBA = 0;
			        
			// Chemical Synapse Between Cone and Cone Bipolar
//			Vpre_C_CCB[0][i]=VC_C + offset;
//			long double Vth_C_CCB = -45.76654665646767500000000000000000000000000000000000 + offset;
//			long double Vslope_C_CCB = 20;
//			long double tau_C_CCB = .01;
        
//			long double Sinf_C_CCB = tanh(abs(Vpre_C_CCB[0][i] - Vth_C_CCB)/Vslope_C_CCB);
//			long double d_st_C_CCB=0;

//			if(Vpre_C_CCB[0][i] >= Vth_C_CCB)
//				d_st_C_CCB = 0;
//			else if (abs(Vpre_C_CCB[0][i]-Vth_C_CCB) >= 0) // New version
//				d_st_C_CCB = (Sinf_C_CCB - S_C_CCB) / ((1-Sinf_C_CCB) * tau_C_CCB );
//			else
//				d_st_C_CCB = 0;
			        
			// Cone Bipolar
//			s_syn_CB[0][i]=S_C_CCB;
			// Ih
//			long double ah_CB = 3 / ( exp( (v_CB+110)/15 ) + 1. );
//			long double bh_CB = 1.5 / ( exp( -(v_CB+115)/15 ) + 1. );
        
//			long double dC1_CB = bh_CB*C2_CB - 4.*ah_CB*C1_CB;
//			long double dC2_CB = C1_CB*4.*ah_CB + OP1_CB*2.*bh_CB - C2_CB*bh_CB - C2_CB*3.*ah_CB;    //original
			//long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
//			long double dOP1_CB = C2_CB*3.*ah_CB + OP2_CB*3.*bh_CB - OP1_CB*2.*(bh_CB+ah_CB);
//			long double dOP2_CB = OP1_CB*2.*ah_CB + OP3_CB*4.*bh_CB - OP2_CB*(3.*bh_CB + ah_CB);
//			long double dOP3_CB = ah_CB*OP2_CB - 4*bh_CB*OP3_CB;
        
//			long double mh_CB = OP1_CB + OP2_CB + OP3_CB;
//			long double ih_CB = mh_CB * 0.975 * ( v_CB - (-17.7) );
        
			// IKv
//			long double amKv_CB = 400 / ( exp( -(v_CB-15)/36 ) + 1. );
//			long double bmKv_CB = 1.0 * exp( -v_CB / 13 );
        
//			long double d_mKv_CB = amKv_CB * ( 1. - mKv_CB ) - bmKv_CB * mKv_CB;
        
//			long double ahKv_CB = 0.0003 * exp( -v_CB / 7 );
//			long double bhKv_CB = 80 / ( exp( -(-115-v_CB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
//			long double d_hKv_CB = ahKv_CB * ( 1. - hKv_CB ) - bhKv_CB * hKv_CB;
        
//			long double iKv_CB = 2.0 * mKv_CB * mKv_CB * mKv_CB * hKv_CB*( v_CB - (-58.0) );
        
			// ICa			
//			long double Vd_CB = 4/3*PIP_CB*(radius_d_CB*radius_d_CB*radius_d_CB)*1e-15;
//			long double Vs_CB = 4/3*PIP_CB*(radius_CB*radius_CB*radius_CB)*1e-15-Vd_CB;
//			long double Ssd_CB = 4*PIP_CB*radius_d_CB*radius_d_CB*1e-10;
//			long double dsd_CB = ((radius_CB-radius_d_CB)/2 + radius_d_CB)*1e-5;
			        
//			long double amCa_CB = 12000*( 120 - v_CB ) / ( exp( (120-v_CB)/25 ) - 1. );  //original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
//			long double bmCa_CB = 40000 / ( 1.0 + exp( (68+v_CB)/25 ) );
//			long double d_mCa_CB = amCa_CB * ( 1. - mCa_CB ) - bmCa_CB * mCa_CB;
//			long double mCa_4_CB = pow( (long double)mCa_CB, (long double)4.0 );
        
//			long double hCa_CB = exp( (50-v_CB)/11 )/( 1.0 + exp( (50-v_CB)/11) );
        
//			long double ECa_CB = 12.9*log(Ca_o_CB/Ca_s_CB);
        
//			long double iCa_CB = gCa_CB*mCa_4_CB*hCa_CB*(v_CB-ECa_CB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
//			long double iNC_CB = Jnc_CB*exp(-(v_CB+14.)/70.) *( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 2.3 );
//			long double iATP_CB = Jatp_CB*( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
//			long double dbCa_ls_CB = Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) - Lb2_CB*bCa_ls_CB;
        
//			long double dbCa_hs_CB = Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB) - Hb2_CB*bCa_hs_CB;
        
//			long double dCa_s_CB = -(iCa_CB+iNC_CB+iATP_CB)/(2.*F_CB*Vs_CB)*1.0E-6 - Dca_CB*Ssd_CB/Vs_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ls_CB - Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) + Hb2_CB*bCa_hs_CB - Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB);
        
//			long double dCa_d_CB = Dca_CB*Ssd_CB/Vd_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ld_CB - Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) + Hb2_CB*bCa_hd_CB - Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB);
        
//			long double dbCa_ld_CB = Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) - Lb2_CB*bCa_ld_CB;
//			long double dbCa_hd_CB = Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB) - Hb2_CB*bCa_hd_CB;
        
			// IK(Ca)
//			long double mKca_c1_CB = Ca_s_CB / ( Ca_s_CB + 0.2 );
//			long double amKca_CB = 100 * ( 230 - v_CB )/( exp( (230-v_CB)/52 ) - 1. );
//			long double bmKca_CB = 120 * exp( -v_CB / 95 );
//			long double d_mKca_CB = amKca_CB * ( 1. - mKca_CB ) - bmKca_CB * mKca_CB;
      
//			long double iKca_CB = 8.5 * mKca_c1_CB*mKca_CB*mKca_CB*(v_CB - (-58.0));
			// IL
//			long double EL_CB = -21.0;
//			long double il_CB = 0.23*((v_CB-EL_CB));
        
			// IA
//			long double amA_CB = 2400 / ( 1.0 + exp( -(v_CB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
//			long double bmA_CB = 12 * exp( -v_CB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
//			long double d_mA_CB = amA_CB * ( 1. - mA_CB ) - bmA_CB * mA_CB;
        
//			long double ahA_CB = 0.045 * exp( -v_CB / 13 );
//			long double bhA_CB = 75 / ( exp( -(30+v_CB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
//			long double d_hA_CB = ahA_CB * ( 1.0 - hA_CB ) - bhA_CB * hA_CB;
        
        
//			long double iA_CB = 50.0 * pow( (long double)mA_CB, (long double)3.0 ) * hA_CB * ( v_CB - (-58.0) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
			// Isyn
//			long double Isyn_CB = 2.56 * s_syn_CB[0][i] * (v_CB-0);
        
			// Total current and membrane potential of cone bipolar
//			long double Cm_CB = 0.01;
//			long double IALL_CB = iKca_CB + iCa_CB + ih_CB + iKv_CB + il_CB + iA_CB + Isyn_CB; //for chemical synapse simulation
//			long double dV_CB   = (-IALL_CB + 0.2*(VA_A-v_CB)) / Cm_CB; //for reference %for current clamp simulation
        
			// Amacrine
			//info from chemical synapse
//			s_syn2_A[0][i]=S_C_RBA;
        
			// Na
//			long double mtau_na_A = 1/(alpha_m_A(VA_A) + beta_m_A(VA_A));
//			long double minf_na_A = alpha_m_A(VA_A) / (alpha_m_A(VA_A) + beta_m_A(VA_A));
//			long double htau_na_A = 1/((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
//			long double hinf_na_A = (alpha_h_A(VA_A)/3.5) / ((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
        
//			long double dm_A = (minf_na_A-m_A)/mtau_na_A * tscale_A;
//			long double dh_A = (hinf_na_A-h_A)/htau_na_A * tscale_A;
        
//			long double gNa_A = gNa_bar_A*m_A*m_A*m_A*h_A;
        
//			long double INa_A = gNa_A*(VA_A-ENa_A);
        
			// K
//			long double tau_k_A = 1/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
//			long double inf_k_A = (alpha_n_A(VA_A)/5)/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
        
//			long double dn_A = (inf_k_A-n_A)/tau_k_A * tscale_A;
        
//			long double gK_A = gK_bar_A*n_A*n_A*n_A*n_A;
        
//			long double IK_A = gK_A*(VA_A-EK_A);
        
			// L
//			long double Il_A = gL_A*(VA_A-El_A);
        
			// Isyn
//			long double Isyn2_A = 1.2 * s_syn2_A[0][i] * (VA_A+10);
        
			// Membrane potential of amacrine
//			long double Iion_A = INa_A + IK_A + Il_A;
//			long double Im_A = -Isyn2_A - Iion_A;
//			long double dVA_A =(((Im_A) + 0.2*(v_CB-VA_A)) /(Cm_A)) * tscale_A; // 0.2nS
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
//			Vpre_C_CBG[0][i] = v_CB;
//			long double Vth_C_CBG = -40.85865173873610700638892012648284435272216796875000;
//			long double Vslope_C_CBG = 20;
//			long double tau_C_CBG = .01;
        
//			long double Sinf_C_CBG = tanh(abs(Vpre_C_CBG[0][i] - Vth_C_CBG) /Vslope_C_CBG);
//			long double d_st_C_CBG=0;

//			if (t <= 0.1)
//				d_st_C_CBG = 0;
            
//			else if (Vpre_C_CBG[0][i] <= Vth_C_CBG) // 2015 December added [97-98 line].
//				d_st_C_CBG = 0;
            
//			else if (abs(Vpre_C_CBG[0][i]-Vth_C_CBG) >= 0) // NEW version
//				d_st_C_CBG = (Sinf_C_CBG - S_C_CBG) / ((1-Sinf_C_CBG) * tau_C_CBG );
            
//			else
//				d_st_C_CBG = 0;

			// Chemical Synapse Between Rod Bipolar and Ganglion
			Vpre_C_RBG[0][i] = v_RB;
			//long double Vth_C_RBG = -36.424516776897130;
			long double Vth_C_RBG = Vpre_C_RBG[0][0];
			//long double Vslope_C_RBG = 20;
			long double Vslope_C_RBG = synapsevalue[0][1][2];
			//long double tau_C_RBG = .01;
			long double tau_C_RBG = synapsevalue[0][1][3];

			long double Sinf_C_RBG = tanh(abs(Vpre_C_RBG[0][i] - Vth_C_RBG) /Vslope_C_RBG);
			long double d_st_C_RBG=0;
            
			if (Vpre_C_RBG[0][i] <= Vth_C_RBG) // 2015 December added [97-98 line].
				d_st_C_RBG = 0;
           
			else if (abs(Vpre_C_RBG[0][i]-Vth_C_RBG) >= 0) // NEW version
				d_st_C_RBG = (Sinf_C_RBG - S_C_RBG) / ((1-Sinf_C_RBG) * tau_C_RBG );
            
			else
				d_st_C_RBG = 0;	

			if(t<data.light_start)
				d_st_C_RBG = 0;	
        
			// Ganglion
			//-------Na---
			long double alpha_Na_m_G = (-0.6*(V_G+30.0))/(exp(-0.1*(V_G+30.0))-1.0);
			long double beta_Na_m_G = 20.0*exp(-(V_G+55.0)/18.0);
			long double alpha_Na_h_G = 0.4*exp(-(V_G+50.0)/20.0);
			long double beta_Na_h_G = 6.0/(exp(-0.1*(V_G+20.0))+1.0);
			long double gNa_G = g_Na_G*(pow(Na_m_G,3))*Na_h_G;
        
			long double I_Na_G = gNa_G*(V_G-VNa_G);
        
			long double dNa_m_G = (-(alpha_Na_m_G+beta_Na_m_G)*Na_m_G+alpha_Na_m_G) *tscale_G;
			long double dNa_h_G = (-(alpha_Na_h_G+beta_Na_h_G)*Na_h_G+alpha_Na_h_G) *tscale_G;
        
			//-------Ca, KCa---
			long double VCa_G = 1000.0*(R_G*T_G/(2*F_G))*log(Ca2e_G/Ca_i_G);
        
			long double alpha_Ca_n_G = (-0.3*(V_G+13.0))/(exp(-0.1*(V_G+13.0))-1.0);
			long double beta_Ca_n_G = 10.0*exp(-(V_G+38.0)/18.0);
			long double gCa_G = g_Ca_G*(pow(Ca_n_G,3));
        
			long double I_Ca_G = gCa_G*(V_G-VCa_G);
        
			long double gKCa_G = g_KCa_G*((pow((Ca_i_G/Ca2diss_G),2))/(1.0+(pow((Ca_i_G/Ca2diss_G),2))));
        
			long double I_KCa_G = gKCa_G*(V_G-VK_G);
        
			long double dCa_n_G = (-(alpha_Ca_n_G+beta_Ca_n_G)*Ca_n_G+alpha_Ca_n_G) *tscale_G;
			long double dCa_i_G = (-(((10^4)*3.0*I_Ca_G)/(2.0*F_G*r_G))-((Ca_i_G-Ca2res_G)/tCa_G)) *tscale_G;
        
			//-------K---        
			long double alpha_K_n_G = (-0.02*(V_G+40.0))/(exp(-0.1*(V_G+40.0))-1.0);
			long double beta_K_n_G = 0.4*exp(-(V_G+50.0)/80.0);
			long double gK_G = g_K_G*(pow(K_n_G,4));
        
			long double I_K_G = gK_G*(V_G-VK_G);
        
			long double dK_n_G =  (-(alpha_K_n_G+beta_K_n_G)*K_n_G+alpha_K_n_G) *tscale_G;
        
			//-------A---        
			long double alpha_A_m_G = (-0.006*(V_G+90.0))/(exp(-0.1*(V_G+90.0))-1.0);
			long double beta_A_m_G = 0.1*exp(-(V_G+30.0)/10.0);
			long double alpha_A_h_G = 0.04*exp(-(V_G+70.0)/20.0);
			long double beta_A_h_G = 0.6/(exp(-0.1*(V_G+40.0))+1.0);
			long double gA_G = g_A_G*(pow(A_m_G,3))*A_h_G;
        
			long double I_A_G = gA_G*(V_G-VK_G);
        
			long double dA_m_G=(-(alpha_A_m_G+beta_A_m_G)*A_m_G+alpha_A_m_G) *tscale_G;
			long double dA_h_G=(-(alpha_A_h_G+beta_A_h_G)*A_h_G+alpha_A_h_G) *tscale_G;
        
			//-------L---    
			long double I_leak_G = g_L_G*(V_G-VL_G);
        
			//------ Isyn (in/20)---
			s_syn_G[0][i]=S_C_RBG;
			long double Isyn_G = (synapsevalue[0][1][0] * s_syn_G[0][i] * (V_G-synapsevalue[0][1][1]));
        
			//-------I---
			//long double Cm_G = 1.0;
			long double Cm_G = cellvalue[0][2];
			long double Iall_G = I_Na_G + I_Ca_G + I_KCa_G + I_K_G + I_A_G + I_leak_G;
			long double dV_G = ((-Isyn_G - Iall_G*20) / (Cm_G * 20)) * tscale_G ;

			// Rod Derivatives
			k[0][j] = dV_R;
			k[1][j] = dRh_R;
			k[2][j] = dRhi_R;
			k[3][j] = dTr_R;
			k[4][j] = dPDE_R;
			k[5][j] = dCa_R;
			k[6][j] = dCab_R;
			k[7][j] = dcGMP_R;
			k[8][j] = dC1_R;
			k[9][j] = dC2_R;
			k[10][j] = dO1_R;
			k[11][j] = dO2_R;
			k[12][j] = dO3_R;
			k[13][j] = dmKv_R;
			k[14][j] = dhKv_R;
			k[15][j] = dmCa_R;
			k[16][j] = dmKCa_R;
			k[17][j] = dCa_s_R;
			k[18][j] = dCa_f_R;
			k[19][j] = dCab_ls_R;
			k[20][j] = dCab_hs_R;
			k[21][j] = dCab_lf_R;
			k[22][j] = dCab_hf_R;
        
			// Cone Deriviates
//			k[23][j] = dVC_C*1000;
//			k[24][j] = dGf_C*1000;
//			k[25][j] = dy1_C;
//			k[26][j] = dy2_C;
//			k[27][j] = dy3_C;
//			k[28][j] = dy4_C;
//			k[29][j] = dy5_C;
//			k[30][j] = dz1_C;
//			k[31][j] = dz2_C;
//			k[32][j] = dz3_C;

			// Chemical Synapse Between Rod and Rod Bipolar Deriviates
			k[33][j]=d_st_C_RB;

			// Rod Bipolar Deriviates
			k[34][j] = dV_RB;
			k[35][j] = dC1_RB;
			k[36][j] = dC2_RB;
			k[37][j] = dOP1_RB;
			k[38][j] = dOP2_RB;
			k[39][j] = dOP3_RB;
			k[40][j] = d_mKv_RB;
			k[41][j] = d_hKv_RB;
			k[42][j] = d_mCa_RB;
			k[43][j] = d_mKca_RB;
			k[44][j] = dCa_s_RB;
			k[45][j] = dCa_d_RB;
			k[46][j] = dbCa_ls_RB;
			k[47][j] = dbCa_hs_RB;
			k[48][j] = dbCa_ld_RB;
			k[49][j] = dbCa_hd_RB;
			k[50][j] = d_mA_RB;
			k[51][j] = d_hA_RB;
       
			// Chemical Synapse Between Rod Bipolar and Amacrine Deriviates
//			k[52][j]=d_st_C_RBA;
        
			// Chemical Synapse Between Cone and Cone Bipolar Deriviates
//			k[53][j]=d_st_C_CCB;
       
			// Cone Bipolar Deriviates
//			k[54][j] = dV_CB;
//			k[55][j] = dC1_CB;
//			k[56][j] = dC2_CB;
//			k[57][j] = dOP1_CB;
//			k[58][j] = dOP2_CB;
//			k[59][j] = dOP3_CB;
//			k[60][j] = d_mKv_CB;
//			k[61][j] = d_hKv_CB;
//			k[62][j] = d_mCa_CB;
//			k[63][j] = d_mKca_CB;
//			k[64][j] = dCa_s_CB;
//			k[65][j] = dCa_d_CB;
//			k[66][j] = dbCa_ls_CB;
//			k[67][j] = dbCa_hs_CB;
//			k[68][j] = dbCa_ld_CB;
//			k[69][j] = dbCa_hd_CB;
//			k[70][j] = d_mA_CB;
//			k[71][j] = d_hA_CB;
        
			// Amacrine Deriviates
//			k[72][j] = dVA_A;
//			k[73][j] = dm_A;
//			k[74][j] = dh_A;
//			k[75][j] = dn_A;
        
			// Chemical Synapse Between Cone Bipolar and Ganglion Deriviates
//			k[76][j]=d_st_C_CBG;

			// Chemical Synapse Between Rod Bipolar and Ganglion Deriviates
			k[76][j]=d_st_C_RBG;
        
			// Ganglion Output
			k[77][j] = dV_G;
			k[78][j] = dNa_m_G;
			k[79][j] = dNa_h_G;
			k[80][j] = dCa_n_G;
			k[81][j] = dCa_i_G;
			k[82][j] = dK_n_G;
			k[83][j] = dA_m_G;
			k[84][j] = dA_h_G;

			if(j<=1)
			{
				for(int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep/2.0*k[l][j];  
			}
			else if(j==2)
			{
				for (int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep*k[l][j];
			}
			else if(j==3)
			{
				for (int l=0;l<85;l++)
				{
					ystar[l][i+1] = ystar[l][i]+data.tstep/6.0*(k[l][0]+2.0*k[l][1]+2.0*k[l][2]+k[l][3]);  

					if(t<data.light_start) // for stability
					{
						ystar[0][i+1]=y11[0][0];
						ystar[23][i+1]=y11[23][0];
					}
					
					y11[l][0] = ystar[l][i+1];
				}
				//if(i==0)
					//fprintf(fp[0], "Time, Rod Photocurrent, Rod Membrane Potential, Activation Level of Synapse [R-RB], Rod Bipolar Membrane Potential, Activation Level of Synapse [CB-G], Ganglion Membrane Potential\n");
				fprintf(fp,"%.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",real_t[0][i],Iphoto_R2[0][i],ystar[0][i],ystar[33][i],ystar[34][i],ystar[76][i],ystar[77][i]);
			
				if(i==0) // ploting with KST
				{
					CopyFile("kst\\bin\\preset\\RodPath_Reference.kst","kst\\bin\\preset\\RodPath.kst",false);	
					ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\RodPath.kst",NULL,SW_SHOW);	
				}			
			}           
		}
	}
	fclose(fp);

	ReplaceMsgBoard("Computation Finished.");
	ReplaceMsgBoard("Writing Temporary Output File Finished.");
	ReplaceMsgBoard("Drawing Simulation Graphs Finished.");

	/* Ploting with KST */
	//CopyFile("kst\\bin\\preset\\RodPath_Reference.kst","kst\\bin\\preset\\RodPath.kst",false);	
	//ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\RodPath.kst",NULL,SW_HIDE);	

FREE:
	simulationsw_rod=0; //exit

	/* Free allocation */

	for(i=0;i<height;i++)
		free(ystar[i]);
	
	free(ystar);

	for(i=0;i<1;i++)
	{
		free(Vpre_C_RB[i]); 
		free(s_syn_RB[i]); 
		//free(Vpre_C_RBA[i]);
		//free(s_syn_CB[i]);  
		//free(s_syn2_A[i]);  
		//free(Vpre_C_CBG[i]);
		//free(Vpre_C_CCB[i]);
		free(Vpre_C_RBG[i]);
		free(s_syn_G[i]);  
		free(real_t[i]);
	}

	free(Vpre_C_RB); 
	free(s_syn_RB); 
	//free(Vpre_C_RBA);
	//free(s_syn_CB);  
	//free(s_syn2_A);  
	//free(Vpre_C_CBG);
	//free(Vpre_C_CCB);
	free(Vpre_C_RBG);
	free(s_syn_G);
	free(real_t);

	ReplaceMsgBoard("Freeing Memory Finished.");
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
void CRetinaModelSimulatorDlg::ConePathSimulation(void) //Simulation Run --> Cone Path Simulation
{
	#define NI (85) //Number of integrated variable

	/* Global parameter */
	// Rod cell phototransduction
//	long double a1_R = 50; 
//	long double a2_R = 0.0003; 
//	long double a3_R = 0.03; 
//	long double eps_R = 0.5;
//	long double Ttot_R = 1000;
//	long double b1_R = 2.5;
//	long double tau1_R = 0.2;
//	long double tau2_R = 5.0;
//	long double PDEtot_R = 100;
//	long double rCa_R = 50;
//	long double c0_R = 0.1;
//	long double b_R = 0.25;
//	long double k1_R = 0.2;
//	long double k2_R = 0.8;
//	long double eT_R = 500;
//	long double Vbar_R = 0.4;
//	long double Kc_R = 0.1; 
//	long double Amax_R= 65.6;
//	long double sigma_R = 1.0; 
//	long double Jmax_R = 5040;

	// Rod cell ion channel
//	long double Eh_R = -32.0;
//	long double EK_R = -74.0;
//	long double ECl_R = -20.0;
//	long double EL_R = -77.0;

	// Rod cell intracellular calcium system
//	long double Jex_R = 20;
//	long double Jex2_R = 20; 
//	long double Kex_R = 2.3; 
//	long double Kex2_R = 0.5;
//	long double Cae_R = 0.01;
//	long double F_R = 9.64846e4;
//	long double V1_R = 3.812e-13; 
//	long double V2_R = 5.236e-13; 
//	long double DCa_R = 6e-8; 
//	long double delta_R = 3e-5; 
//	long double S1_R = 3.142e-8;
//	long double Lb1_R = 0.4; 
//	long double Lb2_R = 0.2; 
//	long double Hb1_R = 100; 
//	long double Hb2_R = 90; 
//	long double BL_R = 500; 
//	long double BH_R = 300;

	// Cone cell
	// [mV]     
	long double E_C  = ionvalue[1][0][2][1];
	long double Vf_C = -57;
	long double Ve_C = 4;

	// [msec]
	//long double rL_C = 10;
	long double rL_C = cellvalue[1][0];
	long double rf_C = 67;

	long double Gf_peak_C = ionvalue[1][0][0][0];
	long double Gi_peak_C = ionvalue[1][0][1][0];     

	// [sec]
	long double K_C = 10;

	// [/sec]
	long double alpha_C    = 83.3;
	long double k12_peak_C = 10;
	long double k12M_C     = 250;
	long double k23_C      = 17;
	long double k34_C      = 1.3;
	long double k32_C      = 0.03;

	// [/sec^2]
	long double v_C = 2.125; 
	long double n_C = 6;
	long double A_C = 6.76;

	// Cone cell offset
	long double offset;

	// Rod cell membrane capacitance
//	long double Cm_R = 0.02;

	// Chemical synbapse between rod and rod bipolar
//	long double Vslope_C_RB = 20;
//	long double tau_C_RB = 0.01;

	// Rod bipolar
	// Chemical Parameter 
//	long double F_RB=9.649e4;
//	long double Dca_RB=6.0e-8;

	// Morphologycal Parameter%
	// Soma: Diameter 12 micron
//	long double PIP_RB = 3.14159;
//	long double radius_RB = 6.0; 
//	long double radius_d_RB = 5.6;

	// Chemical parameter         */
//	long double Ca_o_RB = 2500.; 

	// Ca current parameter         */
//	long double gCa_RB = 1.1;

	// Ca buffer parameter	     */
//	long double LB_to1_RB = 300.; 
//	long double HB_to1 = 100.; 
//	long double LB_to2_RB = 500.; 
//	long double HB_to2 = 300.; 
//	long double Lb1_RB = 0.4; 
//	long double Lb2_RB = 0.2; 
//	long double Hb1_RB = 100.; 
//	long double Hb2_RB = 90.; 

	// Ca exchanger & pump parameter   */
//	long double Jnc_RB = 9.*40; 
//	long double Jatp_RB = 9.5*40;
//	long double Ca_e_RB = 0.01;

	// Rod bipolar ion channel
//	long double EL_RB = -21.0;

	// Rod bipolar synaptic current
//	long double gmax_syn_RB=2.56;

	// Rod bipolar membrane capacitance
//	long double Cm_RB = 0.01;

	// Chemical synapse between rod bipolar and amacrine
//	long double Vslope_C_RBA = 20;
//	long double tau_C_RBA = .01;

	// Chemical synapse between cone and cone bipolar
	long double Vslope_C_CCB = 20;
	long double tau_C_CCB = .01;  

	// Cone bipolar
	// Chemical Parameter 
	long double F_CB=9.649e4;
	long double Dca_CB=6.0e-8;

	// Morphologycal Parameter%
	// Soma: Diameter 12 micron
	long double PIP_CB = 3.14159;
	long double radius_CB = 6.0; 
	long double radius_d_CB = 5.6;

	// Chemical parameter         */
	long double Ca_o_CB = 2500.; 

	// Ca current parameter         */
	//long double gCa_CB = 1.1;
	long double gCa_CB = ionvalue[1][1][3][0];

	// Ca buffer parameter	     */
	long double LB_to1_CB = 300.; 
	long double HB_to1_CB = 100.; 
	long double LB_to2_CB = 500.; 
	long double HB_to2_CB = 300.; 
	long double Lb1_CB = 0.4;
	long double Lb2_CB = 0.2; 
	long double Hb1_CB = 100.; 
	long double Hb2_CB = 90.;

	// Ca exchanger & pump parameter   */
	long double Jnc_CB = 9.*40; 
	long double Jatp_CB = 9.5*40;
	long double Ca_e_CB = 0.01;     

	// Cone bipolar ionic channel
	long double EL_CB = -21.0;

	// Cone bipolar membrane capacitance
	//long double Cm_CB = 0.01;
	long double Cm_CB = cellvalue[1][1];

	// Amacrine cell
	// Timescale
//	long double tscale_A = 1000;

	// Reversal potential of amacrine [mV]
//	long double EK_A = -80.0;
//	long double ENa_A = 40.0;
//	long double El_A = -54;

	// Maximum conductance of amacrine [nS]
//	long double gNa_bar_A = 4.0;
//	long double gK_bar_A  = 0.4;
//	long double gL_A      = 0.46;

	// Membrane capacitance of amacrine [nF]
//	long double Cm_A = 20;

	// Chemical synapse between cone bipolar and ganglion
	long double Vslope_C_CBG = 20;
	long double tau_C_CBG = .01;

	// Ganglion cell
	// Time scale
	long double tscale_G=1000; // scale to seconds factor

	//-------Na---
	//long double g_Na_G = 50.0;
	long double g_Na_G = ionvalue[1][2][0][0];
	//long double VNa_G = 35.0;
	long double VNa_G = ionvalue[1][2][0][1];

	//-------Ca, KCa---
	//long double g_Ca_G = 2.2;
	long double g_Ca_G = ionvalue[1][2][1][0];
	long double Ca2e_G = 1800;
	long double tCa_G = 50.0;
	long double Ca2res_G = 0.1;
	long double r_G = 12.5;
	//long double g_KCa_G = 0.05;
	long double g_KCa_G = ionvalue[1][2][3][0];
	long double Ca2diss_G = 1.0;
	long double R_G = 8.31;
	long double F_G = 96500;
	long double T_G = 293;        
	//long double VK_G = -75.0;
	long double VK_G = ionvalue[1][2][2][1];

	//-------K---
	//long double g_K_G = 12.0;
	long double g_K_G = ionvalue[1][2][2][0];
		
	//-------A---
	//long double g_A_G = 36.0;
	long double g_A_G = ionvalue[1][2][4][0];

	//-------L---
	//long double g_L_G = 0.05;
	long double g_L_G = ionvalue[1][2][5][0];
	//long double VL_G = -62.0;
	long double VL_G = ionvalue[1][2][5][1];

	//-------I---        
	//long double Cm_G = 1.0; 
	long double Cm_G = cellvalue[1][2];

	/* For preallocation */
	long double tlength;
	int height;
	int width;
	long double** ystar;
//	long double** Vpre_C_RB;
//	long double** s_syn_RB;
//	long double** Vpre_C_RBA;
	long double** s_syn_CB;
//	long double** s_syn2_A;
	long double** Vpre_C_CBG;
	long double** Vpre_C_CCB;
	long double** s_syn_G;
//	long double** Iphoto_R2; 

	long double** real_t;

	long double y11[85][4] = {0};
	long double k  [85][4] = {0};

	int percentage;

	struct data
	{
		long double tstart;
		long double tstep;
		long double tlast;
		long double duration;
		long double light_start;
		long double light_intensity;
		long double light_intensity_cone;
	};

	struct data data;

	//FILE* fp;

	data.tstart=t_fstart;
	data.tlast=t_fend;
	data.tstep=t_fstep;
	data.light_intensity=flightintensity;
	data.light_intensity_cone=flightintensity_cone;
	data.duration=flightduration;
	data.light_start=flightstart;

	ReplaceMsgBoard("Setting Global/External Parameters Finished.");

	/* Preallocation */
	int i,j;	

	tlength=round((data.tlast-data.tstart)/data.tstep +1);
	
	height= NI;
	width=(int)tlength +1;	

	ystar = (long double **) malloc(sizeof(long double*) * height);
//	Vpre_C_RB = (long double **) malloc(sizeof(long double*) * 1);
//	s_syn_RB = (long double **) malloc(sizeof(long double*) * 1);
//	Vpre_C_RBA = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_CB = (long double **) malloc(sizeof(long double*) * 1);
//	s_syn2_A = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_CBG = (long double **) malloc(sizeof(long double*) * 1);
	Vpre_C_CCB = (long double **) malloc(sizeof(long double*) * 1);
	s_syn_G = (long double **) malloc(sizeof(long double*) * 1);
	real_t = (long double **) malloc(sizeof(long double*) * 1);
//	Iphoto_R2 = (long double **) malloc(sizeof(long double*) *1);
	
	for(i=0; i<height;i++)
	{
		ystar[i]=(long double *) malloc(sizeof(long double) * width); //long double ystar[85,tlength];
	}
	
	for(i=0;i<1;i++)
	{
//		Vpre_C_RB[i] = (long double *) malloc(sizeof(long double) * width);
//		s_syn_RB[i]  = (long double *) malloc(sizeof(long double) * width);
//		Vpre_C_RBA[i]= (long double *) malloc(sizeof(long double) * width);
		s_syn_CB[i]  = (long double *) malloc(sizeof(long double) * width);
//		s_syn2_A[i]  = (long double *) malloc(sizeof(long double) * width);
		Vpre_C_CBG[i]= (long double *) malloc(sizeof(long double) * width);
		Vpre_C_CCB[i]= (long double *) malloc(sizeof(long double) * width);
		s_syn_G[i]   = (long double *) malloc(sizeof(long double) * width);
		real_t[i]    = (long double *) malloc(sizeof(long double) * width);
//		Iphoto_R2[i] = (long double *) malloc(sizeof(long double) * width);
	}
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			ystar[i][j]=0;			
		}		
	}	

	for(i=0;i<1;i++)
		for(j=0;j<width;j++)
		{
//			Vpre_C_RB[i][j]=0;
//			s_syn_RB[i][j]=0;
//			Vpre_C_RBA[i][j]=0;
			s_syn_CB[i][j]=0;
//			s_syn2_A[i][j]=0;
			Vpre_C_CBG[i][j]=0;
			Vpre_C_CCB[i][j]=0;
			s_syn_G[i][j]=0;
			real_t[i][j]=0;
		}
	ReplaceMsgBoard("Memory Dynamic Preallocation Finished.");

	/* Initial Condition */
	// Rod and Cone cell Initial Condition
	// y11[0][0] = -35.15299217465973700000000000000000000000000000000000;
	// y11[1][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[2][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[3][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[4][0] = 0.00000000000000000000000000000000000000000000000000;
	// y11[5][0] = 0.30000000000000143000000000000000000000000000000000;
	// y11[6][0] = 34.88372093023302500000000000000000000000000000000000;
	// y11[7][0] = 1.99999999999998670000000000000000000000000000000000;
	// y11[8][0] = 0.64132528330066263000000000000000000000000000000000;
	// y11[9][0] = 0.26412772593690498000000000000000000000000000000000;
	// y11[10][0] = 0.04079255338037327700000000000000000000000000000000;
	// y11[11][0] = 0.00280004667419985350000000000000000000000000000000;
	// y11[12][0] = 0.00007207438056699847500000000000000000000000000000;
	// y11[13][0] = 0.44095899101175912000000000000000000000000000000000;
	// y11[14][0] = 0.99912312462833097000000000000000000000000000000000;
	// y11[15][0] = 0.46586591802631688000000000000000000000000000000000;
	// y11[16][0] = 0.65322043938092211000000000000000000000000000000000;
	// y11[17][0] = 0.12381319321649724000000000000000000000000000000000;
	// y11[18][0] = 0.12381319648326869000000000000000000000000000000000;
	// y11[19][0] = 99.23899869893260500000000000000000000000000000000000;
	// y11[20][0] = 36.28001495889955700000000000000000000000000000000000;
	// y11[21][0] = 99.23900194523179200000000000000000000000000000000000;
	// y11[22][0] = 36.28001580109989300000000000000000000000000000000000;
	y11[23][0] = -42.2321233629648844498660764656960964202880859375;
	y11[24][0] = 0.004863366238889023189517768486211934941820800304412841796875;
	y11[25][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[26][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[27][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[28][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[29][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[30][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[31][0] = 0.00000000000000000000000000000000000000000000000000;
	y11[32][0] = 0.00000000000000000000000000000000000000000000000000;
	offset=-y11[23][0]; // Cone Cell Membrane Potential offset

	// //// Chemical Synapse Between Rod and Rod Bipolar Initial Condition
	// y11[33][0] = 0;

	// //// Rod Bipolar Initial Condition
	// y11[34][0] = -36.424516776897130;
	// y11[35][0] = 0.928238175043767;
	// y11[36][0] = 0.054905344261992;
	// y11[37][0] = 0.001217870414180;
	// y11[38][0] = 1.200618479085905e-05;
	// y11[39][0] = 4.438540983730620e-08;
	// y11[40][0] = 0.824374082910590;
	// y11[41][0] = 0.109794106890060;
	// y11[42][0] = 0.290203193088928;
	// y11[43][0] = 0.475464147362579;
	// y11[44][0] = 0.011561930331728;
	// y11[45][0] = 0.011563608687641;
	// y11[46][0] = 6.780371247710756;
	// y11[47][0] = 1.268364765067093;
	// y11[48][0] = 11.302574980627850;
	// y11[49][0] = 3.805639865311822;
	// y11[50][0] = 0.186127778073054;
	// y11[51][0] = 0.024443585120781;

	// //// Chemical Synapse Between Rod Bipolar and Amacrine Initial Condition
	// y11[52][0] = 0;

	//// Chemical Synapse Between Cone and Cone Bipolar Initial Condition
	y11[53][0] = 0;

	//// Cone Bipolar Initial Condition
	y11[54][0] = -36.424516776897130;
	y11[55][0] = 0.928238175043767;
	y11[56][0] = 0.054905344261992;
	y11[57][0] = 0.001217870414180;
	y11[58][0] = 1.200618479085905e-05;
	y11[59][0] = 4.438540983730620e-08;
	y11[60][0] = 0.824374082910590;
	y11[61][0] = 0.109794106890060;
	y11[62][0] = 0.290203193088928;
	y11[63][0] = 0.475464147362579;
	y11[64][0] = 0.011561930331728;
	y11[65][0] = 0.011563608687641;
	y11[66][0] = 6.780371247710756;
	y11[67][0] = 1.268364765067093;
	y11[68][0] = 11.302574980627850;
	y11[69][0] = 3.805639865311822;
	y11[70][0] = 0.186127778073054;
	y11[71][0] = 0.024443585120781;

	// //// Amacrine Initial Condition
	// y11[72][0] = -50.34951375105524107311794068664312362670898437500000;
	// y11[73][0] = 0.24340676136333766477193307764537166804075241088867;
	// y11[74][0] = 0.15952849172211810979682411471003433689475059509277;
	// y11[75][0] = 0.54575595513993369056748861112282611429691314697266;

	// // Temperature of amacrine
	// global celcius_Na_A;
	// global celcius_K_A;
	// celcius_Na_A = 22;
	// celcius_K_A  = 22;

	//// Chemical Synapse Between Cone Bipolar and Ganglion Initial Condition
	y11[76][0] = 0;

	//// Ganglion Initial Condition
	y11[77][0]=-61.698524;
	y11[78][0]=0.027940;
	y11[79][0]=0.887161;
	y11[80][0]=0.003019;
	y11[81][0]=0.100007;
	y11[82][0]=0.107809;
	y11[83][0]=0.070467;
	y11[84][0]=0.300453;

	for(i=0;i<NI;i++)
	{
		ystar[i][0]=y11[i][0];
	}

	 ReplaceMsgBoard("Derivatives Initialization Finished.");

	 ReplaceMsgBoard("*** Cone Path Simulation (C+CB+G) ***");
	 CString announce, announce2, announce3;
	 announce.Format("Start Time = %f, End Time = %f, Time Step = %f",data.tstart,data.tlast,data.tstep);
	 announce2.Format("Light Intensity for Cone = %f",data.light_intensity_cone);
	 announce3.Format("Light Starting Time = %f, Light Duration = %f",data.light_start,data.duration);
	 ReplaceMsgBoard(announce);
	 ReplaceMsgBoard(announce2);
	 ReplaceMsgBoard(announce3);
	 ReplaceMsgBoard(" ");

	 CString announce4, announce5, announce6, announce7, announce8, announce9, announce10;

     ReplaceMsgBoard("** Cone Cell **");
	 announce4.Format("Time Constant = %f", cellvalue[1][0]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* G_f Channel Current *");
	 announce5.Format("Maximum Time Constant = %f", ionvalue[1][0][0][0]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* G_i Channel Current *");
	 announce6.Format("Maximum Time Constant = %f", ionvalue[1][0][1][0]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Static Channel Current *");
	 announce7.Format("Reversal Potential = %f", ionvalue[1][0][2][1]);
	 ReplaceMsgBoard(announce7);	 
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Cone Bipolar Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[1][1]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Hyperpolarization Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][1][0][0], ionvalue[1][1][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce6.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][1][1][0], ionvalue[1][1][1][1]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Transient Outward Current *");
	 announce7.Format("Maximum Conductance = %f", ionvalue[1][1][2][0]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[1][1][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[1][1][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][1][5][0], ionvalue[1][1][5][1]);
	 ReplaceMsgBoard(announce10);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Ganglion Cell **");
	 announce4.Format("Membrane Capacitance = %f", cellvalue[1][2]);
	 ReplaceMsgBoard(announce4);
	 ReplaceMsgBoard("* Sodium Current *");
	 announce5.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][2][0][0], ionvalue[1][2][0][1]);
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard("* Calcium Current *");
	 announce6.Format("Maximum Conductance = %f", ionvalue[1][2][1][0]);
	 ReplaceMsgBoard(announce6);
	 ReplaceMsgBoard("* Delayed Rectifier Current *");
	 announce7.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][2][2][0], ionvalue[1][2][2][1]);
	 ReplaceMsgBoard(announce7);
	 ReplaceMsgBoard("* Calcium-Potassium Current *");
	 announce8.Format("Maximum Conductance = %f", ionvalue[1][2][3][0]);
	 ReplaceMsgBoard(announce8);
	 ReplaceMsgBoard("* A Type Potassium Current *");
	 announce9.Format("Maximum Conductance = %f", ionvalue[1][2][4][0]);
	 ReplaceMsgBoard(announce9);
	 ReplaceMsgBoard("* Leakage Current *");
	 announce10.Format("Maximum Conductance = %f, Reversal Potential = %f", ionvalue[1][2][5][0], ionvalue[1][2][5][1]);
	 ReplaceMsgBoard(announce10);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (C-CB) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[1][0][0], synapsevalue[1][0][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[1][0][2], synapsevalue[1][0][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	 ReplaceMsgBoard("** Chemical Synapse (CB-G) **");
	 announce4.Format("Maximum Conductance = %f, Reversal Potential = %f", synapsevalue[1][1][0], synapsevalue[1][1][1]);
	 ReplaceMsgBoard(announce4);
	 announce5.Format("Slope = %f, Time Constant = %f", synapsevalue[1][1][2], synapsevalue[1][1][3]);	 
	 ReplaceMsgBoard(announce5);
	 ReplaceMsgBoard(" ");

	/* Model */
	long double t;

	percentage = 0;

	fp = fopen("C:\\Output_ConePath.dat","w+");
	checkfp++;

	for(i=0;i<(int)(tlength);i++)
	{

		if(simulationstop==1)
		{
			simulationstop=0;
			fclose(fp);
			remove("C:\\Output_ConePath.dat");
			goto FREE;
		}

		t=(long double)i*data.tstep + data.tstart;
		real_t[0][i]=t;

		int perfect=(int)tlength-1;
		int perfect2=perfect/100;

		if(i%perfect2==0)
		{	
			CString c_simulationprogress;
			c_simulationprogress.Format("Simulation %d %% Finished.",percentage++);

			if((percentage-1)%10==0)
			{
				ReplaceMsgBoard(c_simulationprogress);
			}
			
			progress.StepIt();
		}

		for(j=0;j<4;j++) //4th order
		{
			// ROD
//			long double V_R   = y11[0][j];             // membrane potential (mV)
			// outer segment
//			long double Rh_R  = y11[1][j];             // active rhodopsin (uM)
//			long double Rhi_R = y11[2][j];             // inactive rhodopsin (uM)
//			long double Tr_R  = y11[3][j];             // active transducin (uM)
//			long double PDE_R = y11[4][j];             // active phosphodiesterase (uM)
//			long double Ca_R  = y11[5][j];             // intracellular free Ca in outer segment (uM)
//			long double Cab_R = y11[6][j];             // intracellular Ca buffer in outer segment (uM)
//			long double cGMP_R= y11[7][j];             // cyclic GMP (uM)
			// Ih
//			long double C1_R  = y11[8][j];
//			long double C2_R  = y11[9][j];
//			long double O1_R  = y11[10][j];
//			long double O2_R  = y11[11][j];
//			long double O3_R  = y11[12][j];
			// IKv, ICa, IKCa
//			long double mKv_R  = y11[13][j];
//			long double hKv_R = y11[14][j];
//			long double mCa_R  = y11[15][j];
//			long double mKCa_R = y11[16][j];
			// Intracellular calcium system in inner segment
//			long double Ca_s_R  = y11[17][j];
//			long double Ca_f_R  = y11[18][j];
//			long double Cab_ls_R= y11[19][j];
//			long double Cab_hs_R= y11[20][j];
//			long double Cab_lf_R= y11[21][j];
//			long double Cab_hf_R= y11[22][j];
			// CONE
			long double VC_C = y11[23][j];             // membrane potential (mV)
			long double Gf_C = y11[24][j];
			long double y1_C = y11[25][j];
			long double y2_C = y11[26][j];
			long double y3_C = y11[27][j];
			long double y4_C = y11[28][j];
			long double y5_C = y11[29][j];
			long double z1_C = y11[30][j];
			long double z2_C = y11[31][j];
			long double z3_C = y11[32][j];
        
			// Chemical Synapse Between Rod and Rod Bipolar
//			long double S_C_RB = y11[33][j];
        
			// Rod Bipolar
//			long double v_RB   = y11[34][j];             // membrane potential (mV)
//			long double C1_RB  = y11[35][j];
//			long double C2_RB  = y11[36][j];
//			long double OP1_RB  = y11[37][j];
//			long double OP2_RB  = y11[38][j];
//			long double OP3_RB  = y11[39][j];
			// IKv, ICa, IKCa
//			long double mKv_RB  = y11[40][j];
//			long double hKv_RB = y11[41][j];
//			long double mCa_RB  = y11[42][j];
//			long double mKca_RB = y11[43][j];
			// Intracellular calcium system in inner segment
//			long double Ca_s_RB  = y11[44][j];
//			long double Ca_d_RB  = y11[45][j];
//			long double bCa_ls_RB= y11[46][j];
//			long double bCa_hs_RB= y11[47][j];
//			long double bCa_ld_RB= y11[48][j];
//			long double bCa_hd_RB= y11[49][j];
			// IA
//			long double mA_RB= y11[50][j];
//			long double hA_RB= y11[51][j];
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
//			long double S_C_RBA = y11[52][j];
        
			// Chemical Synapse Between Cone and Cone Bipolar
			long double S_C_CCB = y11[53][j];
        
			// Cone Bipolar
			long double v_CB   = y11[54][j];             // membrane potential (mV)
			// Ih
			long double C1_CB  = y11[55][j];
			long double C2_CB  = y11[56][j];
			long double OP1_CB  = y11[57][j];
			long double OP2_CB  = y11[58][j];
			long double OP3_CB  = y11[59][j];
			// IKv, ICa, IKCa
			long double mKv_CB  = y11[60][j];
			long double hKv_CB = y11[61][j];
			long double mCa_CB  = y11[62][j];
			long double mKca_CB = y11[63][j];
			// Intracellular calcium system in inner segment
			long double Ca_s_CB  = y11[64][j];
			long double Ca_d_CB  = y11[65][j];
			long double bCa_ls_CB= y11[66][j];
			long double bCa_hs_CB= y11[67][j];
			long double bCa_ld_CB= y11[68][j];
			long double bCa_hd_CB= y11[69][j];
			// IA
			long double mA_CB= y11[70][j];
			long double hA_CB= y11[71][j];
        
			// Amacrine
//			long double VA_A = y11[72][j];             // membrane potential (mV)
//			long double m_A = y11[73][j];
//			long double h_A = y11[74][j];
//			long double n_A = y11[75][j];
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
			long double S_C_CBG = y11[76][j];
        
			// Ganglion
			long double V_G = y11[77][j];
			long double Na_m_G = y11[78][j];
			long double Na_h_G = y11[79][j];
			long double Ca_n_G = y11[80][j];
			long double Ca_i_G = y11[81][j];
			long double K_n_G = y11[82][j];
			long double A_m_G = y11[83][j];
			long double A_h_G = y11[84][j];			

			// ROD
			// Phototransduction        
//			long double jhv_R = data.light_intensity *( heav(t-(data.tstart+data.light_start)) - heav(t-(data.tstart+data.light_start+data.duration)) ) ; //pulse
//			long double dRh_R  = jhv_R - a1_R*Rh_R + a2_R*Rhi_R;
//			long double dRhi_R = a1_R*Rh_R - (a2_R+a3_R)*Rhi_R;
//			long double dTr_R  = eps_R*Rh_R*(Ttot_R-Tr_R) - b1_R*Tr_R + tau2_R*PDE_R - tau1_R*Tr_R*(PDEtot_R-PDE_R);
//			long double dPDE_R = tau1_R*Tr_R*(PDEtot_R-PDE_R) - tau2_R*PDE_R;
//			long double J_R    = Jmax_R*pow(cGMP_R,3) / (pow(cGMP_R,3)+1000);
//			long double dCa_R  = b_R*J_R - rCa_R*(Ca_R-c0_R) - k1_R*(eT_R-Cab_R)*Ca_R + k2_R*Cab_R;
//			long double dCab_R = k1_R*(eT_R-Cab_R)*Ca_R - k2_R*Cab_R;
//			long double dcGMP_R= Amax_R/(1.0+(pow(Ca_R,4)/pow(Kc_R,4))) - cGMP_R*(Vbar_R+sigma_R*PDE_R);
        
//			long double Iphoto_R = -Jmax_R*pow(cGMP_R,3)/(pow(cGMP_R,3)+1000)*(1-exp((V_R-8.5)/17));
//			Iphoto_R2[0][i]=Iphoto_R;
        
			// Ih			
//			long double ahh_R = 8 / ( exp((V_R+78)/14) + 1);
//			long double bhh_R = 18 / ( exp(-(V_R+8)/19) + 1);
//			long double dC1_R = -4*ahh_R*C1_R + bhh_R*C2_R;
//			long double dC2_R =  4*ahh_R*C1_R - (3*ahh_R+bhh_R)*C2_R + 2*bhh_R*O1_R;
//			long double dO1_R =  3*ahh_R*C2_R - (2*ahh_R+2*bhh_R)*O1_R + 3*bhh_R*O2_R;
//			long double dO2_R =  2*ahh_R*O1_R - (ahh_R+3*bhh_R)*O2_R + 4*bhh_R*O3_R;
//			long double dO3_R =  ahh_R*O2_R - 4*bhh_R*O3_R;
//			long double Ih_R  = 3.0*(O1_R+O2_R+O3_R)*(V_R-Eh_R);
			// IKv			
//			long double amKv_R = 5*(100-V_R) / (exp( (100-V_R)/42 ) - 1 );
//			long double bmKv_R = 9*exp( -(V_R-20)/40 );
//			long double ahKv_R = 0.15*exp( -V_R/22 );
//			long double bhKv_R = 0.4125 / ( exp( (10-V_R)/7 ) + 1 );
//			long double dmKv_R = amKv_R*(1-mKv_R) - bmKv_R*mKv_R;
//			long double dhKv_R = ahKv_R*(1-hKv_R) - bhKv_R*hKv_R;
//			long double IKv_R  = 2.0*pow(mKv_R,3)*hKv_R*(V_R-EK_R);
			// ICa
//			long double amCa_R = 3*(80-V_R) / ( exp( (80-V_R)/25 ) -1 );
//			long double bmCa_R = 10 / ( 1 + exp( (V_R+38)/7 ) );
//			long double hCa_R  = exp( (40-V_R)/18 ) / ( 1 + exp( (40-V_R)/18 ) );
//			long double dmCa_R = amCa_R*(1-mCa_R) - bmCa_R*mCa_R;
//			long double ECa_R  = -12.5*log(Ca_s_R/1600);
//			long double ICa_R  = 0.7*pow(mCa_R,4)*hCa_R*(V_R-ECa_R);
        
			// ICl(Ca)			
//			long double mCl_R  = 1.0 / ( 1 + exp( (0.37-Ca_s_R) / 0.09  ) );
//			long double IClCa_R = 2.0*mCl_R*(V_R-ECl_R);
        
			// IK(Ca)
//			long double amKCa_R = 15*(80-V_R) / ( exp( (80-V_R)/40 ) - 1 );
//			long double bmKCa_R = 20*exp( -V_R/35 );
//			long double dmKCa_R = amKCa_R*(1-mKCa_R) - bmKCa_R*mKCa_R;
//			long double mKCa_s_R = Ca_s_R / (Ca_s_R + 0.3 );
//			long double IkCa_R = 5.0 * mKCa_R * mKCa_R * mKCa_s_R * (V_R-EK_R);
        
			// IL			
//			long double IL_R = 0.35*(V_R-EL_R);        
        
			// Intracellular calcium system
//			long double Iex_R = Jex_R *exp( -(V_R+14)/70 ) * (Ca_s_R - Cae_R) / ( Ca_s_R - Cae_R + Kex_R );
//			long double Iex2_R= Jex2_R*( Ca_s_R - Cae_R ) / ( Ca_s_R -Cae_R + Kex2_R );
//			long double dCa_s_R = - (ICa_R + Iex_R + Iex2_R ) / ( 2.0 * F_R * V1_R ) * 1e-06 - DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V1_R ) - Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) + Lb2_R *Cab_ls_R - Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) + Hb2_R * Cab_hs_R;
//			long double dCa_f_R =   DCa_R * ( Ca_s_R - Ca_f_R ) / delta_R * ( S1_R / V2_R ) - Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) + Lb2_R * Cab_lf_R - Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) + Hb2_R * Cab_hf_R;
//			long double dCab_ls_R = Lb1_R * Ca_s_R * ( BL_R - Cab_ls_R ) - Lb2_R * Cab_ls_R;
//			long double dCab_hs_R = Hb1_R * Ca_s_R * ( BH_R - Cab_hs_R ) - Hb2_R * Cab_hs_R;
//			long double dCab_lf_R = Lb1_R * Ca_f_R * ( BL_R - Cab_lf_R ) - Lb2_R * Cab_lf_R;
//			long double dCab_hf_R = Hb1_R * Ca_f_R * ( BH_R - Cab_hf_R ) - Hb2_R * Cab_hf_R;			

			// CONE
			long double I_C;

			if (data.light_start <= t && t <= data.light_start + data.duration)
				I_C = data.light_intensity_cone;
			else
				I_C = 0.0;		
        
			// activation and inactivation rates
			long double Gi_C  = ionvalue[1][0][1][0]/(1+z1_C/K_C);
			long double F_C   = ionvalue[1][0][0][0]/(1+exp((VC_C-Vf_C)/Ve_C));
			long double k12_C = k12_peak_C+v_C*z2_C*(k12M_C-k12_peak_C)/(k12M_C-k12_peak_C+v_C*z2_C);
			long double k21_C = k12_C/6.76;
        
			long double dGf_C  = (F_C-Gf_C)/rf_C;
			long double dy1_C  = I_C - alpha_C * y1_C;
			long double dy2_C  = alpha_C * (y1_C - y2_C);
			long double dy3_C  = alpha_C * (y2_C - y3_C);
			long double dy4_C  = alpha_C * (y3_C - y4_C);
			long double dy5_C  = alpha_C * (y4_C - y5_C);
			long double dz1_C  = alpha_C * y5_C - k12_C * z1_C + k21_C * z2_C;
			long double dz2_C  = k12_C * z1_C - (k21_C + k23_C) * z2_C + k32_C * z3_C;
			long double dz3_C  = k23_C * z2_C - (k32_C + k34_C) * z3_C;

			// Rod and Cone Total Current and Membrane Potential			
//			long double IALL_R = Iphoto_R + Ih_R + IKv_R + ICa_R + IClCa_R + IkCa_R + IL_R +Iex_R + Iex2_R ;
        
//			long double dV_R   = (-IALL_R + 0.2*((VC_C + offset)-V_R))/Cm_R; // All electrical synapses between cones and rods have the same conductance value of 0.2nS [35]. FROM PUBLIO 2009
//			long double dVC_C   = (E_C-VC_C*(1+Gf_C+Gi_C) + 0.2*(V_R-(VC_C + offset)))/rL_C;
			long double dVC_C   = (ionvalue[1][0][2][1]-VC_C*(1+Gf_C+Gi_C))/rL_C;
			// Chemical Synapse Between Rod and Rod Bipolar			
//			Vpre_C_RB[0][i]=V_R;
//			long double Vth_C_RB = -35.15299217465973700000000000000000000000000000000000;

        
//			long double Sinf_C_RB = tanh(abs(Vpre_C_RB[0][i] - Vth_C_RB)/Vslope_C_RB);
			
//			long double d_st_C_RB = 0;
//			if (Vpre_C_RB[0][i] >= Vth_C_RB) // 2015 December added [97-98 line].
//				d_st_C_RB = 0;
//			else if (abs(Vpre_C_RB[0][i]-Vth_C_RB) >= 0) // New version
//				d_st_C_RB = (Sinf_C_RB - S_C_RB) / ((1-Sinf_C_RB) * tau_C_RB );
//			else
//				d_st_C_RB = 0;
			
        
			// Rod Bipolar
//			s_syn_RB[0][i]=S_C_RB;
			// Ih
//			long double ah_RB = 3 / ( exp( (v_RB+110)/15 ) + 1. );
//			long double bh_RB = 1.5 / ( exp( -(v_RB+115)/15 ) + 1. );
        
//			long double dC1_RB = bh_RB*C2_RB - 4.*ah_RB*C1_RB;
//			long double dC2_RB = C1_RB*4.*ah_RB + OP1_RB*2.*bh_RB - C2_RB*bh_RB - C2_RB*3.*ah_RB;    //original
			// long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
//			long double dOP1_RB = C2_RB*3.*ah_RB + OP2_RB*3.*bh_RB - OP1_RB*2.*(bh_RB+ah_RB);
//			long double dOP2_RB = OP1_RB*2.*ah_RB + OP3_RB*4.*bh_RB - OP2_RB*(3.*bh_RB + ah_RB);
//			long double dOP3_RB = ah_RB*OP2_RB - 4*bh_RB*OP3_RB;
        
//			long double mh_RB = OP1_RB + OP2_RB + OP3_RB;
//			long double ih_RB = mh_RB * 0.975 * ( v_RB - (-17.7) );
        
			// IKv
//			long double amKv_RB = 400 / ( exp( -(v_RB-15)/36 ) + 1. );
//			long double bmKv_RB = 1.0 * exp( -v_RB / 13 );
        
//			long double d_mKv_RB = amKv_RB * ( 1. - mKv_RB ) - bmKv_RB * mKv_RB;
        
//			long double ahKv_RB = 0.0003 * exp( -v_RB / 7 );
//			long double bhKv_RB = 80 / ( exp( -(-115-v_RB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
//			long double d_hKv_RB = ahKv_RB * ( 1. - hKv_RB ) - bhKv_RB * hKv_RB;
        
//			long double iKv_RB = 2.0 * mKv_RB * mKv_RB * mKv_RB * hKv_RB*( v_RB - (-58.0) );
        
			// ICa
//			long double Vd_RB = 4/3*PIP_RB*(radius_d_RB*radius_d_RB*radius_d_RB)*1e-15;
//			long double Vs_RB = 4/3*PIP_RB*(radius_RB*radius_RB*radius_RB)*1e-15-Vd_RB;
//			long double Ssd_RB = 4*PIP_RB*radius_d_RB*radius_d_RB*1e-10;
//			long double dsd_RB = ((radius_RB-radius_d_RB)/2 + radius_d_RB)*1e-5;
			        
//			long double amCa_RB = 12000*( 120 - v_RB ) / ( exp( (120-v_RB)/25 ) - 1. );  // original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
//			long double bmCa_RB = 40000 / ( 1.0 + exp( (68+v_RB)/25 ) );
//			long double d_mCa_RB = amCa_RB * ( 1. - mCa_RB ) - bmCa_RB * mCa_RB;
//			long double mCa_4_RB = pow((long double) mCa_RB, (long double)4.0 );
        
//			long double hCa_RB = exp( (50-v_RB)/11 )/( 1.0 + exp( (50-v_RB)/11) );
        
//			long double ECa_RB = 12.9*log(Ca_o_RB/Ca_s_RB);
        
//			long double iCa_RB = gCa_RB*mCa_4_RB*hCa_RB*(v_RB-ECa_RB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
//			long double iNC_RB = Jnc_RB*exp(-(v_RB+14.)/70.) *( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 2.3 );
//			long double iATP_RB = Jatp_RB*( Ca_s_RB - Ca_e_RB )/( Ca_s_RB - Ca_e_RB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
//			long double dbCa_ls_RB = Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) - Lb2_RB*bCa_ls_RB;
        
//			long double dbCa_hs_RB = Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB) - Hb2_RB*bCa_hs_RB;
        
//			long double dCa_s_RB = -(iCa_RB+iNC_RB+iATP_RB)/(2.*F_RB*Vs_RB)*1.0E-6 - Dca_RB*Ssd_RB/Vs_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ls_RB - Lb1_RB*Ca_s_RB*(LB_to1_RB - bCa_ls_RB) + Hb2_RB*bCa_hs_RB - Hb1_RB*Ca_s_RB*(HB_to1 - bCa_hs_RB);
        
//			long double dCa_d_RB = Dca_RB*Ssd_RB/Vd_RB/dsd_RB*( Ca_s_RB - Ca_d_RB ) + Lb2_RB*bCa_ld_RB - Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) + Hb2_RB*bCa_hd_RB - Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB);
        
//			long double dbCa_ld_RB = Lb1_RB*Ca_d_RB*(LB_to2_RB - bCa_ld_RB) - Lb2_RB*bCa_ld_RB;
//			long double dbCa_hd_RB = Hb1_RB*Ca_d_RB*(HB_to2 - bCa_hd_RB) - Hb2_RB*bCa_hd_RB;
        
			// IK(Ca)
//			long double mKca_c1_RB = Ca_s_RB / ( Ca_s_RB + 0.2 );
//			long double amKca_RB = 100 * ( 230 - v_RB )/( exp( (230-v_RB)/52 ) - 1. );
//			long double bmKca_RB = 120 * exp( -v_RB / 95 );
//			long double d_mKca_RB = amKca_RB * ( 1. - mKca_RB ) - bmKca_RB * mKca_RB;
        
//			long double iKca_RB = 8.5 * mKca_c1_RB*mKca_RB*mKca_RB*(v_RB - (-58.0));
			// IL
//			long double EL_RB = -21.0;
//			long double il_RB = 0.23*((v_RB-EL_RB));
        
			// IA
//			long double amA_RB = 2400 / ( 1.0 + exp( -(v_RB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
//			long double bmA_RB = 12 * exp( -v_RB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
//			long double d_mA_RB = amA_RB * ( 1. - mA_RB ) - bmA_RB * mA_RB;
        
//			long double ahA_RB = 0.045 * exp( -v_RB / 13 );
//			long double bhA_RB = 75 / ( exp( -(30+v_RB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
//			long double d_hA_RB = ahA_RB * ( 1.0 - hA_RB ) - bhA_RB * hA_RB;
        
        
//			long double iA_RB = 50.0 * pow( (long double)mA_RB, (long double)3.0 ) * hA_RB * ( v_RB - (-58.0) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
        
			// Isyn
//			long double gmax_syn_RB=2.56; //nS
//			long double Isyn_RB = gmax_syn_RB * s_syn_RB[0][i] * (v_RB-0);
        
        
			// Total current and membrane potential
//			long double Cm_RB = 0.01;
        
//			long double IALL_RB = iKca_RB + iCa_RB + ih_RB + iKv_RB + il_RB + iA_RB + Isyn_RB; //for chemical synapse simulation
//			long double dV_RB   = -IALL_RB / Cm_RB; //for reference %for current clamp simulation
        
			// Chemical Synapse Between Rod Bipolar and Amacrine
//			Vpre_C_RBA[0][i]=v_RB;
//			long double Vth_C_RBA = -36.424516776897130;
//			long double Vslope_C_RBA = 20;
//			long double tau_C_RBA = .01;
        
//			long double Sinf_C_RBA = tanh(abs(Vpre_C_RBA[0][i] - Vth_C_RBA)/Vslope_C_RBA);
//			long double d_st_C_RBA = 0;

//			if (abs(Vpre_C_RBA[0][i]-Vth_C_RBA) >= 0) // New version
//				d_st_C_RBA = (Sinf_C_RBA - S_C_RBA) / ((1-Sinf_C_RBA) * tau_C_RBA );
//			else
//				d_st_C_RBA = 0;
			        
			// Chemical Synapse Between Cone and Cone Bipolar
			Vpre_C_CCB[0][i]=VC_C + offset;
			//long double Vth_C_CCB = -42.2321233629648844498660764656960964202880859375 + offset;
			long double Vth_C_CCB = Vpre_C_CCB[0][0];
			//long double Vslope_C_CCB = 20;
			long double Vslope_C_CCB = synapsevalue[1][0][2];
			//long double tau_C_CCB = .01;
			long double tau_C_CCB = synapsevalue[1][0][3];

			long double Sinf_C_CCB = tanh(abs(Vpre_C_CCB[0][i] - Vth_C_CCB)/Vslope_C_CCB);
			long double d_st_C_CCB=0;

			if(Vpre_C_CCB[0][i] >= Vth_C_CCB)
				d_st_C_CCB = 0;
			else if (abs(Vpre_C_CCB[0][i]-Vth_C_CCB) >= 0) // New version
				d_st_C_CCB = (Sinf_C_CCB - S_C_CCB) / ((1-Sinf_C_CCB) * tau_C_CCB );
			else
				d_st_C_CCB = 0;

			if(t<data.light_start)
				d_st_C_CCB = 0;	
			        
			// Cone Bipolar
			s_syn_CB[0][i]=S_C_CCB;
			// Ih
			long double ah_CB = 3 / ( exp( (v_CB+110)/15 ) + 1. );
			long double bh_CB = 1.5 / ( exp( -(v_CB+115)/15 ) + 1. );
        
			long double dC1_CB = bh_CB*C2_CB - 4.*ah_CB*C1_CB;
			long double dC2_CB = C1_CB*4.*ah_CB + OP1_CB*2.*bh_CB - C2_CB*bh_CB - C2_CB*3.*ah_CB;    //original
			//long double dC2 = -C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;  %reference paper
			long double dOP1_CB = C2_CB*3.*ah_CB + OP2_CB*3.*bh_CB - OP1_CB*2.*(bh_CB+ah_CB);
			long double dOP2_CB = OP1_CB*2.*ah_CB + OP3_CB*4.*bh_CB - OP2_CB*(3.*bh_CB + ah_CB);
			long double dOP3_CB = ah_CB*OP2_CB - 4*bh_CB*OP3_CB;
        
			long double mh_CB = OP1_CB + OP2_CB + OP3_CB;
			long double ih_CB = mh_CB * ionvalue[1][1][0][0] * ( v_CB - (ionvalue[1][1][0][1]) );
        
			// IKv
			long double amKv_CB = 400 / ( exp( -(v_CB-15)/36 ) + 1. );
			long double bmKv_CB = 1.0 * exp( -v_CB / 13 );
        
			long double d_mKv_CB = amKv_CB * ( 1. - mKv_CB ) - bmKv_CB * mKv_CB;
        
			long double ahKv_CB = 0.0003 * exp( -v_CB / 7 );
			long double bhKv_CB = 80 / ( exp( -(-115-v_CB)/15 ) + 1.0 ) + 0.02; //original
			//long double bhKv = 80 / (exp( -(v+115)/15 ) + 1.0 ) + 0.02;  %reference paper
			long double d_hKv_CB = ahKv_CB * ( 1. - hKv_CB ) - bhKv_CB * hKv_CB;
        
			long double iKv_CB = ionvalue[1][1][1][0] * mKv_CB * mKv_CB * mKv_CB * hKv_CB*( v_CB - (ionvalue[1][1][1][1]) );
        
			// ICa			
			long double Vd_CB = 4/3*PIP_CB*(radius_d_CB*radius_d_CB*radius_d_CB)*1e-15;
			long double Vs_CB = 4/3*PIP_CB*(radius_CB*radius_CB*radius_CB)*1e-15-Vd_CB;
			long double Ssd_CB = 4*PIP_CB*radius_d_CB*radius_d_CB*1e-10;
			long double dsd_CB = ((radius_CB-radius_d_CB)/2 + radius_d_CB)*1e-5;
			        
			long double amCa_CB = 12000*( 120 - v_CB ) / ( exp( (120-v_CB)/25 ) - 1. );  //original
			//long double amCa = 12000*( 120 - v ) / ( exp( (v-120)/25 ) - 1. ); %reference
			long double bmCa_CB = 40000 / ( 1.0 + exp( (68+v_CB)/25 ) );
			long double d_mCa_CB = amCa_CB * ( 1. - mCa_CB ) - bmCa_CB * mCa_CB;
			long double mCa_4_CB = pow( (long double)mCa_CB, (long double)4.0 );
        
			long double hCa_CB = exp( (50-v_CB)/11 )/( 1.0 + exp( (50-v_CB)/11) );
        
			long double ECa_CB = 12.9*log(Ca_o_CB/Ca_s_CB);
        
			long double iCa_CB = gCa_CB*mCa_4_CB*hCa_CB*(v_CB-ECa_CB);
        
			//  Calcium pump and exchanger [Iex, Iex2]
			long double iNC_CB = Jnc_CB*exp(-(v_CB+14.)/70.) *( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 2.3 );
			long double iATP_CB = Jatp_CB*( Ca_s_CB - Ca_e_CB )/( Ca_s_CB - Ca_e_CB + 0.5 );
        
			//  Calcium buffer concentration & Calcium concentration
			long double dbCa_ls_CB = Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) - Lb2_CB*bCa_ls_CB;
        
			long double dbCa_hs_CB = Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB) - Hb2_CB*bCa_hs_CB;
        
			long double dCa_s_CB = -(iCa_CB+iNC_CB+iATP_CB)/(2.*F_CB*Vs_CB)*1.0E-6 - Dca_CB*Ssd_CB/Vs_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ls_CB - Lb1_CB*Ca_s_CB*(LB_to1_CB - bCa_ls_CB) + Hb2_CB*bCa_hs_CB - Hb1_CB*Ca_s_CB*(HB_to1_CB - bCa_hs_CB);
        
			long double dCa_d_CB = Dca_CB*Ssd_CB/Vd_CB/dsd_CB*( Ca_s_CB - Ca_d_CB ) + Lb2_CB*bCa_ld_CB - Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) + Hb2_CB*bCa_hd_CB - Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB);
        
			long double dbCa_ld_CB = Lb1_CB*Ca_d_CB*(LB_to2_CB - bCa_ld_CB) - Lb2_CB*bCa_ld_CB;
			long double dbCa_hd_CB = Hb1_CB*Ca_d_CB*(HB_to2_CB - bCa_hd_CB) - Hb2_CB*bCa_hd_CB;
        
			// IK(Ca)
			long double mKca_c1_CB = Ca_s_CB / ( Ca_s_CB + 0.2 );
			long double amKca_CB = 100 * ( 230 - v_CB )/( exp( (230-v_CB)/52 ) - 1. );
			long double bmKca_CB = 120 * exp( -v_CB / 95 );
			long double d_mKca_CB = amKca_CB * ( 1. - mKca_CB ) - bmKca_CB * mKca_CB;
        
			long double iKca_CB = ionvalue[1][1][4][0] * mKca_c1_CB*mKca_CB*mKca_CB*(v_CB - (ionvalue[1][1][1][1]));
			// IL
			long double EL_CB = ionvalue[1][1][5][1];
			long double il_CB = ionvalue[1][1][5][0]*((v_CB-EL_CB));
        
			// IA
			long double amA_CB = 2400 / ( 1.0 + exp( -(v_CB-50.)/28. ) );   //original
			//long double amA = 1200 / ( 1.0 + exp( -(v-50.)/28. ) );  %reference paper
			long double bmA_CB = 12 * exp( -v_CB/10. );  //original
			//long double bmA = 6 * exp(-v/10. );   %reference paper
			long double d_mA_CB = amA_CB * ( 1. - mA_CB ) - bmA_CB * mA_CB;
        
			long double ahA_CB = 0.045 * exp( -v_CB / 13 );
			long double bhA_CB = 75 / ( exp( -(30+v_CB)/15 ) + 1.0 );  //original
			//long double bhA = 75 / ( exp( -(v+50)/15 ) + 1.0 );  %reference paper
			long double d_hA_CB = ahA_CB * ( 1.0 - hA_CB ) - bhA_CB * hA_CB;
        
        
			long double iA_CB = ionvalue[1][1][2][0] * pow( (long double)mA_CB, (long double)3.0 ) * hA_CB * ( v_CB - (ionvalue[1][1][1][1]) );   //original
			//long double iA = 35.0 * power( mA, 3.0 ) * hA * ( v - (-58.0) );  %reference
			// Isyn
			long double Isyn_CB = synapsevalue[1][0][0] * s_syn_CB[0][i] * (v_CB-synapsevalue[1][0][1]);
        
			// Total current and membrane potential of cone bipolar
			long double Cm_CB = cellvalue[1][1];
			long double IALL_CB = iKca_CB + iCa_CB + ih_CB + iKv_CB + il_CB + iA_CB + Isyn_CB; //for chemical synapse simulation
//			long double dV_CB   = (-IALL_CB + 0.2*(VA_A-v_CB)) / Cm_CB; //for reference %for current clamp simulation
            long double dV_CB   = (-IALL_CB) / Cm_CB;

			// Amacrine
			//info from chemical synapse
//			s_syn2_A[0][i]=S_C_RBA;
        
			// Na
//			long double mtau_na_A = 1/(alpha_m_A(VA_A) + beta_m_A(VA_A));
//			long double minf_na_A = alpha_m_A(VA_A) / (alpha_m_A(VA_A) + beta_m_A(VA_A));
//			long double htau_na_A = 1/((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
//			long double hinf_na_A = (alpha_h_A(VA_A)/3.5) / ((alpha_h_A(VA_A)/3.5) + (beta_h_A(VA_A)/3.5));
        
//			long double dm_A = (minf_na_A-m_A)/mtau_na_A * tscale_A;
//			long double dh_A = (hinf_na_A-h_A)/htau_na_A * tscale_A;
        
//			long double gNa_A = gNa_bar_A*m_A*m_A*m_A*h_A;
        
//			long double INa_A = gNa_A*(VA_A-ENa_A);
        
			// K
//			long double tau_k_A = 1/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
//			long double inf_k_A = (alpha_n_A(VA_A)/5)/((alpha_n_A(VA_A)/5) + (beta_n_A(VA_A)/5));
        
//			long double dn_A = (inf_k_A-n_A)/tau_k_A * tscale_A;
        
//			long double gK_A = gK_bar_A*n_A*n_A*n_A*n_A;
        
//			long double IK_A = gK_A*(VA_A-EK_A);
        
			// L
//			long double Il_A = gL_A*(VA_A-El_A);
        
			// Isyn
//			long double Isyn2_A = 1.2 * s_syn2_A[0][i] * (VA_A+10);
        
			// Membrane potential of amacrine
//			long double Iion_A = INa_A + IK_A + Il_A;
//			long double Im_A = -Isyn2_A - Iion_A;
//			long double dVA_A =(((Im_A) + 0.2*(v_CB-VA_A)) /(Cm_A)) * tscale_A; // 0.2nS
        
			// Chemical Synapse Between Cone Bipolar and Ganglion
			Vpre_C_CBG[0][i] = v_CB;
			//long double Vth_C_CBG = -36.424516776897130;
			long double Vth_C_CBG = Vpre_C_CBG[0][0];
			//long double Vslope_C_CBG = 20;
			long double Vslope_C_CBG = synapsevalue[1][1][2];
			//long double tau_C_CBG = .01;
			long double tau_C_CBG = synapsevalue[1][1][3];
        
			long double Sinf_C_CBG = tanh(abs(Vpre_C_CBG[0][i] - Vth_C_CBG) /Vslope_C_CBG);
			long double d_st_C_CBG=0;

			//if (t <= 0.1)
			//	d_st_C_CBG = 0;
            
			if (Vpre_C_CBG[0][i] <= Vth_C_CBG) // 2015 December added [97-98 line].
				d_st_C_CBG = 0;
            
			else if (abs(Vpre_C_CBG[0][i]-Vth_C_CBG) >= 0) // NEW version
				d_st_C_CBG = (Sinf_C_CBG - S_C_CBG) / ((1-Sinf_C_CBG) * tau_C_CBG );
            
			else
				d_st_C_CBG = 0;

			if(t<data.light_start)
				d_st_C_CBG = 0;	
			
        
			// Ganglion
			//-------Na---
			long double alpha_Na_m_G = (-0.6*(V_G+30.0))/(exp(-0.1*(V_G+30.0))-1.0);
			long double beta_Na_m_G = 20.0*exp(-(V_G+55.0)/18.0);
			long double alpha_Na_h_G = 0.4*exp(-(V_G+50.0)/20.0);
			long double beta_Na_h_G = 6.0/(exp(-0.1*(V_G+20.0))+1.0);
			long double gNa_G = g_Na_G*(pow(Na_m_G,3))*Na_h_G;
        
			long double I_Na_G = gNa_G*(V_G-VNa_G);
        
			long double dNa_m_G = (-(alpha_Na_m_G+beta_Na_m_G)*Na_m_G+alpha_Na_m_G) *tscale_G;
			long double dNa_h_G = (-(alpha_Na_h_G+beta_Na_h_G)*Na_h_G+alpha_Na_h_G) *tscale_G;
        
			//-------Ca, KCa---
			long double VCa_G = 1000.0*(R_G*T_G/(2*F_G))*log(Ca2e_G/Ca_i_G);
        
			long double alpha_Ca_n_G = (-0.3*(V_G+13.0))/(exp(-0.1*(V_G+13.0))-1.0);
			long double beta_Ca_n_G = 10.0*exp(-(V_G+38.0)/18.0);
			long double gCa_G = g_Ca_G*(pow(Ca_n_G,3));
        
			long double I_Ca_G = gCa_G*(V_G-VCa_G);
        
			long double gKCa_G = g_KCa_G*((pow((Ca_i_G/Ca2diss_G),2))/(1.0+(pow((Ca_i_G/Ca2diss_G),2))));
        
			long double I_KCa_G = gKCa_G*(V_G-VK_G);
        
			long double dCa_n_G = (-(alpha_Ca_n_G+beta_Ca_n_G)*Ca_n_G+alpha_Ca_n_G) *tscale_G;
			long double dCa_i_G = (-(((10^4)*3.0*I_Ca_G)/(2.0*F_G*r_G))-((Ca_i_G-Ca2res_G)/tCa_G)) *tscale_G;
        
			//-------K---        
			long double alpha_K_n_G = (-0.02*(V_G+40.0))/(exp(-0.1*(V_G+40.0))-1.0);
			long double beta_K_n_G = 0.4*exp(-(V_G+50.0)/80.0);
			long double gK_G = g_K_G*(pow(K_n_G,4));
        
			long double I_K_G = gK_G*(V_G-VK_G);
        
			long double dK_n_G =  (-(alpha_K_n_G+beta_K_n_G)*K_n_G+alpha_K_n_G) *tscale_G;
        
			//-------A---        
			long double alpha_A_m_G = (-0.006*(V_G+90.0))/(exp(-0.1*(V_G+90.0))-1.0);
			long double beta_A_m_G = 0.1*exp(-(V_G+30.0)/10.0);
			long double alpha_A_h_G = 0.04*exp(-(V_G+70.0)/20.0);
			long double beta_A_h_G = 0.6/(exp(-0.1*(V_G+40.0))+1.0);
			long double gA_G = g_A_G*(pow(A_m_G,3))*A_h_G;
        
			long double I_A_G = gA_G*(V_G-VK_G);
        
			long double dA_m_G=(-(alpha_A_m_G+beta_A_m_G)*A_m_G+alpha_A_m_G) *tscale_G;
			long double dA_h_G=(-(alpha_A_h_G+beta_A_h_G)*A_h_G+alpha_A_h_G) *tscale_G;
        
			//-------L---    
			long double I_leak_G = g_L_G*(V_G-VL_G);
        
			//------ Isyn (in/20)---
			s_syn_G[0][i]=S_C_CBG;
			long double Isyn_G = (synapsevalue[1][1][0] * s_syn_G[0][i] * (V_G-synapsevalue[1][1][1]));
        
			//-------I---
			long double Cm_G = cellvalue[1][2];
			long double Iall_G = I_Na_G + I_Ca_G + I_KCa_G + I_K_G + I_A_G + I_leak_G;
			long double dV_G = ((-Isyn_G - Iall_G*20) / (Cm_G * 20)) * tscale_G ;

			// Rod Derivatives
//			k[0][j] = dV_R;
//			k[1][j] = dRh_R;
//			k[2][j] = dRhi_R;
//			k[3][j] = dTr_R;
//			k[4][j] = dPDE_R;
//			k[5][j] = dCa_R;
//			k[6][j] = dCab_R;
//			k[7][j] = dcGMP_R;
//			k[8][j] = dC1_R;
//			k[9][j] = dC2_R;
//			k[10][j] = dO1_R;
//			k[11][j] = dO2_R;
//			k[12][j] = dO3_R;
//			k[13][j] = dmKv_R;
//			k[14][j] = dhKv_R;
//			k[15][j] = dmCa_R;
//			k[16][j] = dmKCa_R;
//			k[17][j] = dCa_s_R;
//			k[18][j] = dCa_f_R;
//			k[19][j] = dCab_ls_R;
//			k[20][j] = dCab_hs_R;
//			k[21][j] = dCab_lf_R;
//			k[22][j] = dCab_hf_R;
        
			// Cone Deriviates
			k[23][j] = dVC_C*1000;
			k[24][j] = dGf_C*1000;
			k[25][j] = dy1_C;
			k[26][j] = dy2_C;
			k[27][j] = dy3_C;
			k[28][j] = dy4_C;
			k[29][j] = dy5_C;
			k[30][j] = dz1_C;
			k[31][j] = dz2_C;
			k[32][j] = dz3_C;

			// Chemical Synapse Between Rod and Rod Bipolar Deriviates
//			k[33][j]=d_st_C_RB;

			// Rod Bipolar Deriviates
//			k[34][j] = dV_RB;
//			k[35][j] = dC1_RB;
//			k[36][j] = dC2_RB;
//			k[37][j] = dOP1_RB;
//			k[38][j] = dOP2_RB;
//			k[39][j] = dOP3_RB;
//			k[40][j] = d_mKv_RB;
//			k[41][j] = d_hKv_RB;
//			k[42][j] = d_mCa_RB;
//			k[43][j] = d_mKca_RB;
//			k[44][j] = dCa_s_RB;
//			k[45][j] = dCa_d_RB;
//			k[46][j] = dbCa_ls_RB;
//			k[47][j] = dbCa_hs_RB;
//			k[48][j] = dbCa_ld_RB;
//			k[49][j] = dbCa_hd_RB;
//			k[50][j] = d_mA_RB;
//			k[51][j] = d_hA_RB;
       
			// Chemical Synapse Between Rod Bipolar and Amacrine Deriviates
//			k[52][j]=d_st_C_RBA;
        
			// Chemical Synapse Between Cone and Cone Bipolar Deriviates
			k[53][j]=d_st_C_CCB;
       
			// Cone Bipolar Deriviates
			k[54][j] = dV_CB;
			k[55][j] = dC1_CB;
			k[56][j] = dC2_CB;
			k[57][j] = dOP1_CB;
			k[58][j] = dOP2_CB;
			k[59][j] = dOP3_CB;
			k[60][j] = d_mKv_CB;
			k[61][j] = d_hKv_CB;
			k[62][j] = d_mCa_CB;
			k[63][j] = d_mKca_CB;
			k[64][j] = dCa_s_CB;
			k[65][j] = dCa_d_CB;
			k[66][j] = dbCa_ls_CB;
			k[67][j] = dbCa_hs_CB;
			k[68][j] = dbCa_ld_CB;
			k[69][j] = dbCa_hd_CB;
			k[70][j] = d_mA_CB;
			k[71][j] = d_hA_CB;
        
			// Amacrine Deriviates
//			k[72][j] = dVA_A;
//			k[73][j] = dm_A;
//			k[74][j] = dh_A;
//			k[75][j] = dn_A;
        
			// Chemical Synapse Between Cone Bipolar and Ganglion Deriviates
			k[76][j]=d_st_C_CBG;
        
			// Ganglion Output
			k[77][j] = dV_G;
			k[78][j] = dNa_m_G;
			k[79][j] = dNa_h_G;
			k[80][j] = dCa_n_G;
			k[81][j] = dCa_i_G;
			k[82][j] = dK_n_G;
			k[83][j] = dA_m_G;
			k[84][j] = dA_h_G;

			if(j<=1)
			{
				for(int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep/2.0*k[l][j];  
			}
			else if(j==2)
			{
				for (int l=0;l<85;l++)
					y11[l][j+1] = ystar[l][i]+data.tstep*k[l][j];
			}
			else if(j==3)
			{
				for (int l=0;l<85;l++)
				{
					ystar[l][i+1] = ystar[l][i]+data.tstep/6.0*(k[l][0]+2.0*k[l][1]+2.0*k[l][2]+k[l][3]);  

					if(t<data.light_start) // for stability
					{
						ystar[0][i+1]=y11[0][0];
						ystar[23][i+1]=y11[23][0];
					}
					
					y11[l][0] = ystar[l][i+1];
				}
				//if(i==0)
					//fprintf(fp[0], "Time, Cone Membrane Potential, Activation Level of Synapse [C-CB], Cone Bipolar Membrane Potential, Activation Level of Synapse [CB-G], Ganglion Membrane Potential\n");
				fprintf(fp,"%.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n",real_t[0][i],ystar[23][i]+offset,ystar[53][i],ystar[54][i],ystar[76][i],ystar[77][i]);
				
				if(i==0) //ploting with KST
				{
					CopyFile("kst\\bin\\preset\\ConePath_Reference.kst","kst\\bin\\preset\\ConePath.kst",false);	
					ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\ConePath.kst",NULL,SW_SHOW);
				}			
			}           
		}
	}
	fclose(fp);

	ReplaceMsgBoard("Computation Finished.");
	ReplaceMsgBoard("Writing Temporary Output File Finished.");
	ReplaceMsgBoard("Drawing Simulation Graphs Finished.");

	/* Ploting with KST */
	//CopyFile("kst\\bin\\preset\\ConePath_Reference.kst","kst\\bin\\preset\\ConePath.kst",false);	
	//ShellExecute(NULL,"open","kst\\bin\\kst2","kst\\bin\\preset\\ConePath.kst",NULL,SW_HIDE);

FREE:
	simulationsw_cone=0; //exit

	/* Free allocation */

	for(i=0;i<height;i++)
		free(ystar[i]);
	
	free(ystar);

	for(i=0;i<1;i++)
	{
//		free(Vpre_C_RB[i]); 
//		free(s_syn_RB[i]); 
//		free(Vpre_C_RBA[i]);
		free(s_syn_CB[i]);  
//		free(s_syn2_A[i]);  
		free(Vpre_C_CBG[i]);
		free(Vpre_C_CCB[i]);
		free(s_syn_G[i]);  
		free(real_t[i]);
	}

//	free(Vpre_C_RB); 
//	free(s_syn_RB); 
//	free(Vpre_C_RBA);
	free(s_syn_CB);  
//	free(s_syn2_A);  
	free(Vpre_C_CBG);
	free(Vpre_C_CCB);
	free(s_syn_G);
	free(real_t);

	ReplaceMsgBoard("Freeing Memory Finished.");
}
/*-----------------------------------------------------------------------------------------------*/

void CRetinaModelSimulatorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default	

	// first process of exit	

	//AfxMessageBox("1");

	CDialogEx::OnClose();
}

BOOL CRetinaModelSimulatorDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	// second process of exit	

	//AfxMessageBox("2");

	return CDialogEx::DestroyWindow();
}

void CRetinaModelSimulatorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

	// third process of exit

	m_bThreadFlag=0;	

	//AfxMessageBox("3");

	if(checkfp!=0)
		fclose(fp);

	ShellExecute(NULL,"open","taskkill","/f /IM kst2.exe",NULL,SW_HIDE);
	
	while(GetProcess("kst2.exe"));

	int nResult  = remove("C:\\Output_DualPath.dat");
	int nResult2 = remove("C:\\Output_RodPath.dat");
	int nResult3 = remove("C:\\Output_ConePath.dat");	
}


void CRetinaModelSimulatorDlg::OnClickedButton2() //simulation stop
{
	// TODO: Add your control notification handler code here

	if(simulationstop==0 && (simulationsw_rod==2 || simulationsw_cone==2 || simulationsw_dual==2))
	{
		simulationstop=1;
	}
}


BOOL CRetinaModelSimulatorDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	
	/*
	//창크기 고정
	cs.cx=1376;
	cs.cy=664;
	
	//최대화, 최소화 버튼 비활성화
	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
	*/

	return CDialogEx::PreCreateWindow(cs);
}


void CRetinaModelSimulatorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default

	/*
	//창크기 고정

	LPMINMAXINFO lpminmax = (LPMINMAXINFO)lpMMI;

	lpminmax->ptMinTrackSize.x = 1376;
	lpminmax->ptMinTrackSize.y = 664;
	lpminmax->ptMaxTrackSize.x = 1376;
	lpminmax->ptMaxTrackSize.y = 664;
	*/

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}



#include <TlHelp32.h>

BOOL CRetinaModelSimulatorDlg::GetProcess(CString name) //프로세스 실행 여부를 리턴한다.
{
	/*
		@brief	프로세스 실행 여부를 리턴한다.
		@param	[IN] name: ex) Run.exe
		@return 프로세스 없음 FALSE
				프로세스 있음 TRUE
		출처: http://secure4u.tistory.com/entry/MFC-%ED%98%84%EC%9E%AC-%EC%8B%A4%ED%96%89%EC%A4%91%EC%9D%B8-%ED%94%84%EB%A1%9C%EC%84%B8%EC%8A%A4-%EC%8B%A4%ED%96%89-%EC%97%AC%EB%B6%80-%ED%99%95%EC%9D%B8
	*/

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //현재 모든 프로세스들의 상태를 스냅

	PROCESSENTRY32 pe32;

	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		exit(EXIT_FAILURE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}

	do{
		if(name.Compare(pe32.szExeFile)==0) //실행중인 프로세스가 있다면
		{
			//MessageBox(pe32.szExeFile);
			return TRUE;
		}
	}while(Process32Next(hProcessSnap, &pe32));

	return FALSE;
}
