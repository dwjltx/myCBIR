
// myCBIR_4Dlg.h : ͷ�ļ�
//

#pragma once
//��ɫ����ֵ
typedef struct ColorEig {
	//int ID;
	std::string Name;
	double ColorEig1;
	double ColorEig2;
	double ColorEig3;
	std::string Path;
}ColorEig;

typedef struct TextureEig {
	//int ID;
	std::string Name;
	double Exp1;
	double Exp2;
	double Exp3;
	double Exp4;
	double Stadv1;
	double Stadv2;
	double Stadv3;
	double Stadv4;
	std::string Path;
}Texture;

//��״����
typedef struct ShapeEig {
	//int ID;
	std::string Name;
	double Shape0;
	double Shape1;
	double Shape2;
	double Shape3;
	double Shape4;
	double Shape5;
	double Shape6;
	double Shape7;
	std::string Path;

}ShapeEig;
typedef struct NamePath {
	std::string fname;
	std::string fpath;
}NamePath;

typedef struct XSName {//�����Ժ�����
	double Xs;
	std::string Name;
	bool operator<(const XSName& a)const {
		return Xs < a.Xs;
	}
}XSName;

// CmyCBIR_4Dlg �Ի���
class CmyCBIR_4Dlg : public CDialogEx
{
// ����
public:
	CmyCBIR_4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCBIR_4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedXuanze();
public:
	void renderScene(Mat mat,int i);//��ʾͼ��
	ColorEig FuncColor(Mat img,NamePath path);//ͼ�񷵻���ɫ����ֵ
	TextureEig FuncTexture(Mat img, NamePath path);//ͼ�񷵻���������ֵ
	ShapeEig FuncShape(Mat img, NamePath path);//ͼ�񷵻���״����ֵ
	Mat PreStep(Mat mat);//Ԥ����
	IplImage* EqualizeHistColorImage(IplImage *pImage);
	afx_msg void OnBnClickedInit();
	double DisColorEig(ColorEig x1, ColorEig x2);
	double DisTextureEig(TextureEig x1, TextureEig x2);
	double DisShapeEig(ShapeEig x1, ShapeEig x2);
	afx_msg void OnBnClickedJiansuo();
	afx_msg void OnBnClickedCharu();
	afx_msg void OnBnClickedYanse();
	afx_msg void OnBnClickedWenli();
	afx_msg void OnBnClickedXingzhuang();
	afx_msg void OnBnClickedShanchu();
	vector<ColorEig> SelectColorEig();
	vector<TextureEig> SelectTextureEig();
	vector<ShapeEig> SelectShapeEig();
	vector<double> HuMoment(IplImage* img);//hu�����
	vector<XSName> GetColorEig(ColorEig eig);//�õ���ɫ����ֵ�����
	vector<XSName> GetTextureEig(TextureEig eig);
	vector<XSName> GetShapeEig(ShapeEig);
	std::string Dig2Alp(int a);
	void SetxsEdit(vector<XSName> vecxn);
	afx_msg void OnBnClickedTongji();
	void ShowListBox(vector<XSName> vecxs);
};
