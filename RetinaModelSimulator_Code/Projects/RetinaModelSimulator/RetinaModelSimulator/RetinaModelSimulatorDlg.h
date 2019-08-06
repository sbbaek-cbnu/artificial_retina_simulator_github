
// RetinaModelSimulatorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CRetinaModelSimulatorDlg dialog
class CRetinaModelSimulatorDlg : public CDialogEx
{
// Construction
public:
	CRetinaModelSimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RETINAMODELSIMULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_RadioPath;
	afx_msg void OnBnClickedRadio(UINT msg);
	CEdit t_start;
	CEdit t_end;
	CEdit t_step;
	CEdit lightintensity;
	CEdit lightintensity_cone;
	CEdit lightstart;
	CEdit lightduration;
	CComboBox parameter_cell;
	CEdit mcap;
	CProgressCtrl progress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
private:
	CStatic m_pictu;
public:
	afx_msg void OnSelchangeCombo1();
	CEdit conduct;
	CEdit msgboard;
	int nLen;
	void ReplaceMsgBoard(CString msg);
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnChangeEdit10();	
	float cellvalue[3][6];
	afx_msg void OnClickedButton1();
	afx_msg void OnSelchangeCombo4();
	CEdit revpotential;
	CEdit conduct_ion;
//	CEdit threshold;
	CEdit slope;
	CEdit tconstant;
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit17();
	CComboBox parameter_synapse;
	float synapsevalue[3][6][4];
	CEdit revpotential_synapse;
    CComboBox ionselection;
	afx_msg void OnSelchangeCombo2();
	float ionvalue[3][6][6][2];
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DualPathSimulation(void);
	float t_fstart;
	float t_fend;
	float t_fstep;
	float flightintensity;
	float flightintensity_cone;
	float flightduration;
	float flightstart;
//	void preeallocation_dual(void);
//	void freeallocation_dual(void);
	int simulationsw_dual;
	int simulationsw_rod;
	int simulationsw_cone;

	static UINT ThreadFirst(LPVOID _mothod);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	int m_bThreadFlag;
	afx_msg void OnDestroy();
	void RodPathSimulation(void);
	void ConePathSimulation(void);
	afx_msg void OnClickedButton2();
	int simulationstop;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//CComboBox cellselection_graph;
	virtual BOOL DestroyWindow();
	BOOL GetProcess(CString name);
	FILE* fp;

	int checkfp; // to decide whether executing fclose function or not when program close if fclose(null) runs, error may occur
};
