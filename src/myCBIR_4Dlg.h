
// myCBIR_4Dlg.h : 头文件
//

#pragma once
//颜色特征值
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

//形状特征
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

typedef struct XSName {//相似性和名字
	double Xs;
	std::string Name;
	bool operator<(const XSName& a)const {
		return Xs < a.Xs;
	}
}XSName;

// CmyCBIR_4Dlg 对话框
class CmyCBIR_4Dlg : public CDialogEx
{
// 构造
public:
	CmyCBIR_4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCBIR_4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedXuanze();
public:
	void renderScene(Mat mat,int i);//显示图像
	ColorEig FuncColor(Mat img,NamePath path);//图像返回颜色特征值
	TextureEig FuncTexture(Mat img, NamePath path);//图像返回纹理特征值
	ShapeEig FuncShape(Mat img, NamePath path);//图像返回形状特征值
	Mat PreStep(Mat mat);//预处理
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
	vector<double> HuMoment(IplImage* img);//hu不变矩
	vector<XSName> GetColorEig(ColorEig eig);//得到颜色特征值最近的
	vector<XSName> GetTextureEig(TextureEig eig);
	vector<XSName> GetShapeEig(ShapeEig);
	std::string Dig2Alp(int a);
	void SetxsEdit(vector<XSName> vecxn);
	afx_msg void OnBnClickedTongji();
	void ShowListBox(vector<XSName> vecxs);
};
