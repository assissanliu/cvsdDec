#pragma once
#include "CVSD.h"

class CAlgorithm : public CDialog
{
    DECLARE_DYNAMIC(CAlgorithm)

public:
    CAlgorithm(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CAlgorithm();

    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnEnChangeEdit();
    virtual BOOL OnInitDialog();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum {  IDD = IDD_DIALOG1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    void Reset(const float *InitParam);
    void RunAlgorithm(const float *InitParam, const float *pdInput, const int InputSize,
                      int& OutputSize, float& OutputRate, float **pdOutput);

private:
    //输出数据缓存
    vector<float> m_OutputBuf;
    //编码类
    CVSD m_CVSD;
};
