#include "StdAfx.h"
#include "Algorithm.h"
#include "Innovations.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CAlgorithm, CDialog)

CAlgorithm::CAlgorithm(CWnd* pParent /*=NULL*/)
           : CDialog(IDD_DIALOG1, pParent)
{
}

CAlgorithm::~CAlgorithm()
{
}

void CAlgorithm::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlgorithm, CDialog)
    ON_BN_CLICKED(IDOK, &CAlgorithm::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CAlgorithm::OnBnClickedCancel)
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CAlgorithm::Reset(const float *InitParam)
{
    //��������
    m_OutputBuf.resize(0);
    //CVSD��ʼ��
    m_CVSD.init();
}

//�ܺ���
void CAlgorithm::RunAlgorithm(const float *InitParam, const float *pdInput, const int InputSize,
                              int& OutputSize, float& OutputRate, float **pdOutput)
{
    //��������
    float inputRate  = InitParam[0];  //�������
    float maxStep    = InitParam[1];  //�������(�������ã���Χ0~30,Ĭ��ֵ20)
    float minStep    = InitParam[2];  //��С����(�������ã���Χ0~1,Ĭ��ֵ0.01)
    float sylIntTau  = InitParam[3];  //���ڻ���ʱ��(�������ã���Χ0~1,Ĭ��ֵ0.98)
    float recIntTau  = InitParam[4];  //�ع�����ʱ��(�������ã���Χ0~1,Ĭ��ֵ0.96)
    float codeRateHz = InitParam[5];  //��������
    //CVSD���²���
    m_CVSD.paraUpdate(maxStep, minStep, sylIntTau, recIntTau);
    
    //�������
    OutputRate =  32e3;

    //�����С
    OutputSize = InputSize;

    //CVSD����
    m_OutputBuf.resize(OutputSize);
    for (int idx = 0;idx<OutputSize;idx++)
    {
        m_CVSD.dec((pdInput[idx]>0.5f) ? 1 : 0, m_OutputBuf[idx]);
    }

    //�˿����
    if (OutputSize > 0)
    {
        *pdOutput = &m_OutputBuf[0];
    }
};

//�������
void CAlgorithm::OnBnClickedOk()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnBnClickedCancel()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnEnChangeEdit()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if (bShow)
    {
        CString value2str;
    }
}

BOOL CAlgorithm::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}
