
// myCBIR_4Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "myCBIR_4.h"
#include "myCBIR_4Dlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmyCBIR_4Dlg �Ի���

ColorEig pic_colorEig;
TextureEig pic_textureEig;
ShapeEig pic_shapeEig;

map<string, string> PathMap;//map��·��

int radio_method=0;//��ѡ����ֵ����

CmyCBIR_4Dlg::CmyCBIR_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYCBIR_4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyCBIR_4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmyCBIR_4Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_XUANZE, &CmyCBIR_4Dlg::OnBnClickedXuanze)
	ON_BN_CLICKED(IDC_INIT, &CmyCBIR_4Dlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_JIANSUO, &CmyCBIR_4Dlg::OnBnClickedJiansuo)
	ON_BN_CLICKED(IDC_CHARU, &CmyCBIR_4Dlg::OnBnClickedCharu)
	ON_BN_CLICKED(IDC_YANSE, &CmyCBIR_4Dlg::OnBnClickedYanse)
	ON_BN_CLICKED(IDC_WENLI, &CmyCBIR_4Dlg::OnBnClickedWenli)
	ON_BN_CLICKED(IDC_XINGZHUANG, &CmyCBIR_4Dlg::OnBnClickedXingzhuang)
	ON_BN_CLICKED(IDC_SHANCHU, &CmyCBIR_4Dlg::OnBnClickedShanchu)
	ON_BN_CLICKED(IDC_TONGJI, &CmyCBIR_4Dlg::OnBnClickedTongji)
END_MESSAGE_MAP()


// CmyCBIR_4Dlg ��Ϣ�������

BOOL CmyCBIR_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmyCBIR_4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmyCBIR_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*����ת���ַ���*/
std::string CmyCBIR_4Dlg::Dig2Alp(int a)
{

	std::string str = "";

	std::string str_dig = "";
	while (a) {
		str_dig = "";
		str_dig += a % 10 + '0';
		str = str_dig + str;
		a /= 10;
	}
	return str;


}
void CmyCBIR_4Dlg::SetxsEdit(vector<XSName> vecxn)//������ʾ������
{
	int editname = 1011;
	for (int i = 0; i < vecxn.size(); i++) {
		CString str;
		str.Format(_T("%f"), vecxn[i].Xs);
		GetDlgItem(editname)->SetWindowTextA(str);
		editname++;
	}
}
vector<double> CmyCBIR_4Dlg::HuMoment(IplImage* img)
{
	vector<double> myhu;
	myhu.clear();
	double M[7] = { 0 };
	int bmpWidth = img->width;
	int bmpHeight = img->height;
	int bmpStep = img->widthStep;
	int bmpChannels = img->nChannels;
	uchar* pBmpBuf = (uchar*)img->imageData;
	double m00 = 0, m11 = 0, m20 = 0, m02 = 0, m30 = 0, m03 = 0, m12 = 0, m21 = 0;//���ľ�
	double x0 = 0, y0 = 0;
	double u20 = 0, u02 = 0, u11 = 0, u30 = 0, u03 = 0, u12 = 0, u21 = 0;//�淶��������ľ�
	double t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
	int Center_x = 0, Center_y = 0;//����
	int i, j;
	//���ͼ����������ģ���ͨ�أ�
	double s10 = 0, s01 = 0, s00 = 0;
	for (j = 0; j < bmpHeight; j++) {
		for (i = 0; i < bmpWidth; i++) {
			s10 += i*pBmpBuf[j*bmpStep + i];
			s01 += j*pBmpBuf[j*bmpStep + i];
			s00 += pBmpBuf[j*bmpStep + i];
		}
	}
	Center_x = (int)(s10 / s00 + 0.5);
	Center_y = (int)(s01 / s00 + 0.5);
	//  ������ס����׾�(���ľ�)
	m00 = s00;
	for (j = 0; j < bmpHeight; j++) {
		for (i = 0; i < bmpWidth; i++) {
			x0 = (i - Center_x);
			y0 = (j - Center_y);
			m11 += x0*y0*pBmpBuf[j*bmpStep + i];
			m20 += x0*x0*pBmpBuf[j*bmpStep + i];
			m02 += y0*y0*pBmpBuf[j*bmpStep + i];
			m03 += y0*y0*y0*pBmpBuf[j*bmpStep + i];
			m30 += x0*x0*x0*pBmpBuf[j*bmpStep + i];
			m12 += x0*y0*y0*pBmpBuf[j*bmpStep + i];
			m21 += x0*x0*y0*pBmpBuf[j*bmpStep + i];
		}
	}
	//  ����淶��������ľ�: mij/pow(m00,((i+j+2)/2)
	u20 = m20 / pow(m00, 2);
	u02 = m02 / pow(m00, 2);
	u11 = m11 / pow(m00, 2);
	u30 = m30 / pow(m00, 2.5);
	u03 = m03 / pow(m00, 2.5);
	u12 = m12 / pow(m00, 2.5);
	u21 = m21 / pow(m00, 2.5);

	//  �����м����
	t1 = (u20 - u02);
	t2 = (u30 - 3 * u12);
	t3 = (3 * u21 - u03);
	t4 = (u30 + u12);
	t5 = (u21 + u03);
	//  ���㲻��� 
	M[0] = u20 + u02;
	M[1] = t1*t1 + 4 * u11*u11;
	M[2] = t2*t2 + t3*t3;
	M[3] = t4*t4 + t5*t5;
	M[4] = t2*t4*(t4*t4 - 3 * t5*t5) + t3*t5*(3 * t4*t4 - t5*t5);
	M[5] = t1*(t4*t4 - t5*t5) + 4 * u11*t4*t5;
	M[6] = t3*t4*(t4*t4 - 3 * t5*t5) - t2*t5*(3 * t4*t4 - t5*t5);
	for (int i = 0; i < 7; i++) {
		myhu.push_back(M[i]);
	}
	return myhu;
}

vector<XSName> CmyCBIR_4Dlg::GetColorEig(ColorEig eig)
{

	vector<ColorEig> ce;
	
	ce = SelectColorEig();
	vector<XSName> vecxn;
	XSName xn;
	int kk=0;
	set<XSName> setxn;
	for (int i = 0; i < ce.size(); i++) {
		xn.Xs = DisColorEig(eig, ce[i]);
		xn.Name = ce[i].Name;
		setxn.insert(xn);
	}
	set<XSName>::iterator it;
	for (it = setxn.begin(); it != setxn.end(); it++) {
		vecxn.push_back(*it);
		kk++;
		if (kk == 9)
			break;
	}

	return vecxn;
}

vector<XSName> CmyCBIR_4Dlg::GetTextureEig(TextureEig eig)
{
	vector<TextureEig> te;
	te = SelectTextureEig();

	vector<XSName> vecxn;
	XSName xn;
	int kk = 0;
	set<XSName> setxn;
	for (int i = 0; i < te.size(); i++) {
		xn.Xs = DisTextureEig(eig, te[i]);
		xn.Name = te[i].Name;
		setxn.insert(xn);
	}
	set<XSName>::iterator it;
	for (it = setxn.begin(); it != setxn.end(); it++) {
		vecxn.push_back(*it);
		kk++;
		if (kk == 9)
			break;
	}

	return vecxn;

}

vector<XSName> CmyCBIR_4Dlg::GetShapeEig(ShapeEig eig)
{

	vector<ShapeEig> se;
	se = SelectShapeEig();

	vector<XSName> vecxn;
	XSName xn;
	int kk = 0;
	set<XSName> setxn;
	for (int i = 0; i < se.size(); i++) {
		xn.Xs = DisShapeEig(eig, se[i]);
		xn.Name = se[i].Name;
		setxn.insert(xn);
	}
	set<XSName>::iterator it;
	for (it = setxn.begin(); it != setxn.end(); it++) {
		vecxn.push_back(*it);
		kk++;
		if (kk == 9)
			break;
	}

	return vecxn;
}



void CmyCBIR_4Dlg::renderScene(Mat mat, int i )
{
	CWnd* pWnd = GetDlgItem(i);
	
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	IplImage img = mat;
	CvvImage cimg;
	cimg.CopyOf(&img);
	CRect rect;
	GetDlgItem(i)->GetClientRect(&rect);
	int tlx = rect.left;//rect.TopLeft().x; 
	int tly = rect.top;// rect.TopLeft().y;
	int brx = rect.Width();// tlx + mat2.cols - 1;
	int bry = rect.Height();// tly + mat2.rows - 1;
	CRect drawRect;
	drawRect.SetRect(tlx, tly, brx, bry);
	cimg.DrawToHDC(hDC, &drawRect);

	ReleaseDC(pDC);
}

//����ͼƬ��ť
void CmyCBIR_4Dlg::OnBnClickedXuanze()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	std::string  tstring,tname;
	char szFilters[] = "JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp|";
	CFileDialog fileDlg(TRUE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp| All Files (*.*) |*.*||"), NULL);
	if (fileDlg.DoModal() != IDOK)
		return;
	str = fileDlg.GetPathName();
	tstring = str.GetBuffer(0);//·��
	str = fileDlg.GetFileName();//�ļ���
	tname = str.GetBuffer(0);
	Mat mat = imread(tstring, 1);//��ȡѡ���ͼƬ
	renderScene(mat, IDC_PIC);//���溯��
    
	NamePath mpath;
	mpath.fpath = tstring;
	mpath.fname = tname;
    //Ԥ����
	mat = PreStep(mat);
	//����ֵ��ȡ
	pic_colorEig = FuncColor(mat, mpath);//�õ���ѡ���ļ�����ɫ����ֵ
	//AfxMessageBox(_T("��ɫ����ֵ"));
	pic_textureEig = FuncTexture(mat, mpath);//�õ���ѡ���ļ�����������ֵ
	//AfxMessageBox(_T("��������ֵ"));
	pic_shapeEig = FuncShape(mat, mpath);//�õ���ѡ���ļ�����״����ֵ
	//AfxMessageBox(_T("��״����ֵ"));


	//���ļ�
	/*Mat img = imread(tstring, 1);
	double xx = (double)img.at<Vec3b>(2, 2)[1];
	char ss[20];
	std::string mystr;
	sprintf(ss, "%f", xx);
	mystr = ss;
	CString SS;
	SS.Format(_T(ss));
	//SS = (CString)SS + (CString)"_mat_" + (CString)str;
	//SetDlgItemText(IDC_XIANSHI, SS);
	if (!mat.data) {
		MessageBox("error", "no image loaded!", MB_OK);
		return;
	}*/

	
}



//**********************************
//          ��ɫ����
//**********************************
ColorEig CmyCBIR_4Dlg::FuncColor(Mat img, NamePath path)
{
	ColorEig Eig_Color;
	//��ɫ��
	IplImage ipl_hist = img;
	IplImage* img_hsi = cvCreateImage(cvGetSize(&ipl_hist), IPL_DEPTH_8U, 3);
	IplImage* img_hue = cvCreateImage(cvGetSize(&ipl_hist), IPL_DEPTH_8U, 1);
	cvCvtColor(&ipl_hist, img_hsi, CV_BGR2HSV);//Error�ĺ���
	cvSplit(img_hsi, img_hue, NULL, NULL, NULL);
	//namedWindow("HSI");
	Mat after_hsi = cvarrToMat(img_hsi);
	Mat after_hue = cvarrToMat(img_hue);
	//std::cout << (int)after_hue.at<uchar>(3, 3) << std::endl;//��ȷ��ȡHue														 //��������ֵ
	double m1 = 0, m2 = 0, m3 = 0;
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			m1 += ((double)after_hue.at<uchar>(i, j) / (64 * 64));
			m2 += (((double)after_hue.at<uchar>(i, j) - m1)*((double)after_hue.at<uchar>(i, j) - m1) / (64 * 64));
			m3 += (((double)after_hue.at<uchar>(i, j) - m1)*((double)after_hue.at<uchar>(i, j) - m1)*((double)after_hue.at<uchar>(i, j) - m1) / (64 * 64));
		}
	}
	m2 = sqrt(m2);
	m3 = pow(m3, (float)1 / 3);

	Eig_Color.ColorEig1 = m1;
	Eig_Color.ColorEig2 = m2;
	Eig_Color.ColorEig3 = m3;
	Eig_Color.Name = path.fname;
	Eig_Color.Path = path.fpath;
	return Eig_Color;
}
//**********************************
//          ��������
//**********************************
TextureEig CmyCBIR_4Dlg::FuncTexture(Mat img, NamePath path)
{
	TextureEig Eig_texture;

	//��������ֵ��ȡ
	//�ҶȻ�
	Mat grayImg;
	cvtColor(img, grayImg, CV_RGB2GRAY);//Error�ĺ���
	//namedWindow("�Ҷ�ͼ");
	//imshow("�Ҷ�ͼ",grayImg);
	//std::cout << "grayImg.channels()" << grayImg.channels() << std::endl;
	//std::cout << "grayImg.size" << grayImg.size() << std::endl;
	//��8���Ҷȵȼ���ÿ���ȼ���32����������[0,31],[32,63]
	int gray_img[64][64];
	double gray_dst0[8][8] = { 0 }, gray_dst1[8][8] = { 0 }, gray_dst2[8][8] = { 0 }, gray_dst3[8][8] = { 0 };
	int real_num;//ֵ
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			real_num = (int)grayImg.at<uchar>(i, j);


			if (real_num >= 0 && real_num <= 31)
				gray_img[i][j] = 0;
			else if (real_num >= 32 && real_num <= 63)
				gray_img[i][j] = 1;
			else if (real_num >= 64 && real_num <= 95)
				gray_img[i][j] = 2;
			else if (real_num >= 96 && real_num <= 127)
				gray_img[i][j] = 3;
			else if (real_num >= 128 && real_num <= 159)
				gray_img[i][j] = 4;
			else if (real_num >= 160 && real_num <= 191)
				gray_img[i][j] = 5;
			else if (real_num >= 192 && real_num <= 223)
				gray_img[i][j] = 6;
			else if (real_num >= 224 && real_num <= 255)
				gray_img[i][j] = 7;
			else {
				//std::cout << "ͼ����ֵ����" << std::endl;
				//std::cout << (int)grayImg.at<uchar>(i, j) << std::endl;
				AfxMessageBox(_T("Error"), MB_OK);
			}
		}
	}
	int rows, cols;
	//0�ȷ���ĻҶȹ�������
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64 - 1; j++) {
			rows = gray_img[i][j];
			cols = gray_img[i][j + 1];
			gray_dst0[rows][cols]++;
		}
	}
	//45�ȷ���ĻҶȹ�������
	for (int i = 0; i < 64 - 1; i++) {
		for (int j = 0; j < 64 - 1; j++) {
			rows = gray_img[i][j];
			cols = gray_img[i + 1][j + 1];
			gray_dst1[rows][cols]++;
		}
	}
	//90�ȷ���ĻҶȹ�������
	for (int i = 0; i < 64 - 1; i++) {
		for (int j = 0; j < 64; j++) {
			rows = gray_img[i][j];
			cols = gray_img[i + 1][j];
			gray_dst2[rows][cols]++;
		}
	}
	//135�ȷ���ĻҶȹ�������
	for (int i = 0; i < 64 - 1; i++) {
		for (int j = 1; j < 64; j++) {
			rows = gray_img[i][j];
			cols = gray_img[i + 1][j - 1];
			gray_dst3[rows][cols]++;
		}
	}

	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << gray_dst1[i][j] << "\t";
		}
		std::cout << "\n";
	}*/
	double max0 = 0, max1 = 0, max2 = 0, max3 = 0;
	//�����ĸ���������������ֵ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gray_dst0[i][j] > max0)
				max0 = gray_dst0[i][j];
			if (gray_dst1[i][j] > max1)
				max1 = gray_dst1[i][j];
			if (gray_dst2[i][j] > max2)
				max2 = gray_dst2[i][j];
			if (gray_dst3[i][j] > max3)
				max3 = gray_dst3[i][j];
		}
	}
	//��һ��
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			gray_dst0[i][j] /= max0;
			gray_dst1[i][j] /= max1;
			gray_dst2[i][j] /= max2;
			gray_dst3[i][j] /= max3;
		}
	}

	//����ֵһ����
	double H[4] = {0};
	for (int i = 0; i < 8 - 1; i++) {
		for (int j = 0; j < 8 - 1; j++) {
			H[0] += gray_dst0[i][j] / (1 + (i - j)*(i - j));
			H[1] += gray_dst1[i][j] / (1 + (i - j)*(i - j));
			H[2] += gray_dst2[i][j] / (1 + (i - j)*(i - j));
			H[3] += gray_dst3[i][j] / (1 + (i - j)*(i - j));
		}
	}

	//����ֵ�Աȶ�,������
	double Con[4] = { 0 }, Ent[4] = {0};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Con[0] += gray_dst0[i][j] * (i - j)*(i - j);
			Con[1] += gray_dst1[i][j] * (i - j)*(i - j);
			Con[2] += gray_dst2[i][j] * (i - j)*(i - j);
			Con[3] += gray_dst3[i][j] * (i - j)*(i - j);
			if (gray_dst0[i][j] == 0)
				Ent[0] += 0;
			else
				Ent[0] += gray_dst0[i][j] * log10(gray_dst0[i][j]);
			if (gray_dst1[i][j] == 0)
				Ent[1] += 0;
			else
				Ent[1] += gray_dst1[i][j] * log10(gray_dst1[i][j]);
			if (gray_dst2[i][j] == 0)
				Ent[2] += 0;
			else
				Ent[2] += gray_dst2[i][j] * log10(gray_dst2[i][j]);
			if (gray_dst3[i][j] == 0)
				Ent[3] += 0;
			else
				Ent[3] += gray_dst3[i][j] * log10(gray_dst3[i][j]);
		}
	}
	std::cout << "���ԣ�" << Ent[0] << std::endl;
	//����ֵ�����
	double avrx[4], avry[4];
	double sumx[8] = { 0 }, sumy[8] = { 0 };

	//��ÿ��ÿ�е�ֵ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sumx[i] += gray_dst0[i][j];
			sumy[i] += gray_dst0[j][i];
		}
	}
	//���ֵ
	for (int i = 0; i < 8; i++) {
		avrx[0] = sumx[i] / 8;
		avry[0] = sumy[i] / 8;
	}
	//�󷽲�
	double sx[4] = { 0 }, sy[4] = { 0 };
	for (int i = 0; i < 8; i++) {
		sx[0] += pow((sumx[i] - avrx[0]), 2);
		sy[0] += pow((sumy[i] - avry[0]), 2);
	}
	sx[0] /= 8; sy[0] /= 8;
	sx[0] = sqrt(sx[0]); sy[0] = sqrt(sy[0]);


	sumx[8] = { 0 }, sumy[8] = { 0 };
	//��ÿ��ÿ�е�ֵ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sumx[i] += gray_dst1[i][j];
			sumy[i] += gray_dst1[j][i];
		}
	}
	//���ֵ
	for (int i = 0; i < 8; i++) {
		avrx[1] = sumx[i] / 8;
		avry[1] = sumy[i] / 8;
	}
	//�󷽲�

	for (int i = 0; i < 8; i++) {
		sx[1] += pow((sumx[i] - avrx[1]), 2);
		sy[1] += pow((sumy[i] - avry[1]), 2);
	}
	sx[1] /= 8; sy[1] /= 8;
	sx[1] = sqrt(sx[1]); sy[1] = sqrt(sy[1]);

	sumx[8] = { 0 }, sumy[8] = { 0 };
	//��ÿ��ÿ�е�ֵ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sumx[i] += gray_dst2[i][j];
			sumy[i] += gray_dst2[j][i];
		}
	}
	//���ֵ
	for (int i = 0; i < 8; i++) {
		avrx[2] = sumx[i] / 8;
		avry[2] = sumy[i] / 8;
	}
	//�󷽲�

	for (int i = 0; i < 8; i++) {
		sx[2] += pow((sumx[i] - avrx[2]), 2);
		sy[2] += pow((sumy[i] - avry[2]), 2);
	}
	sx[2] /= 8; sy[2] /= 8;
	sx[2] = sqrt(sx[2]); sy[2] = sqrt(sy[2]);

	sumx[8] = { 0 }, sumy[8] = { 0 };
	//��ÿ��ÿ�е�ֵ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sumx[i] += gray_dst3[i][j];
			sumy[i] += gray_dst3[j][i];
		}
	}
	//���ֵ
	for (int i = 0; i < 8; i++) {
		avrx[3] = sumx[i] / 8;
		avry[3] = sumy[i] / 8;
	}
	//�󷽲�

	for (int i = 0; i < 8; i++) {
		sx[3] += pow((sumx[i] - avrx[3]), 2);
		sy[3] += pow((sumy[i] - avry[3]), 2);
	}
	sx[3] /= 8; sy[3] /= 8;
	sx[3] = sqrt(sx[3]); sy[3] = sqrt(sy[3]);


	//��Corr
	double Corr[4];
	double Corr_m[4] = { 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Corr_m[0] += i*j*gray_dst0[i][j];
			Corr_m[1] += i*j*gray_dst1[i][j];
			Corr_m[2] += i*j*gray_dst2[i][j];
			Corr_m[3] += i*j*gray_dst3[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		if (sx[i] * sy[i] == 0) {
			Corr[0] = 0;
			Corr[1] = 0;
			Corr[2] = 0;
			Corr[3] = 0;
		}
		else {
			Corr[0] = (Corr_m[0] - avrx[i] * avry[i]) / (sx[i] * sy[i]);
			Corr[1] = (Corr_m[1] - avrx[i] * avry[i]) / (sx[i] * sy[i]);
			Corr[2] = (Corr_m[2] - avrx[i] * avry[i]) / (sx[i] * sy[i]);
			Corr[3] = (Corr_m[3] - avrx[i] * avry[i]) / (sx[i] * sy[i]);
		}
	}

	//����ֵ��ֵ(���)
	double MeanH = 0, MeanCon = 0, MeanEnt = 0, MeanCorr = 0;
	for (int i = 0; i < 4; i++) {
		MeanH += (H[i] / 4);
		MeanCon += (Con[i] / 4);
		MeanEnt += (Ent[i] / 4);
		MeanCorr += (Corr[i] / 4);
	}
	//����ֵ��׼����
	double SH = 0, SCon = 0, SEnt = 0, SCorr = 0;
	for (int i = 0; i < 4; i++) {
		SH += pow((H[i] - MeanH), 2);
		SCon += pow((Con[i] - MeanCon), 2);
		SEnt += pow((Ent[i] - MeanEnt), 2);
		SCorr += pow((Corr[i] - MeanCorr), 2);
	}
	SH /= 4; SCon /= 4; SEnt /= 4; SCorr /= 4;
	SH = sqrt(SH); SCon = sqrt(SCon); SEnt = sqrt(SEnt); SCorr = sqrt(SCorr);

	Eig_texture.Exp1 = MeanH;
	Eig_texture.Exp2 = MeanCon;
	Eig_texture.Exp3 = MeanEnt;
	Eig_texture.Exp4 = MeanCorr;
	Eig_texture.Stadv1 = SH;
	Eig_texture.Stadv2 = SCon;
	Eig_texture.Stadv3 = SEnt;
	Eig_texture.Stadv4 = SCorr;
	Eig_texture.Name = path.fname;
	Eig_texture.Path = path.fpath;
	//AfxMessageBox(_T("�õ���������ֵ"));
	//std::cout << "ǰ�ĸ�����ֵ��" << MeanH << "," << MeanCon << "," << MeanEnt << "," << MeanCorr << std::endl;
	//std::cout << "���ĸ�����ֵ��" << SH << "," << SCon << "," << SEnt << "," << SCorr << std::endl;
	return Eig_texture;
}
//**********************************
//          ��״����
//**********************************
ShapeEig CmyCBIR_4Dlg::FuncShape(Mat img, NamePath path)
{
	ShapeEig Eig_shape;
	//��״����
	//�ҶȻ�
	Mat grayImg;
	cvtColor(img, grayImg, CV_RGB2GRAY);
	//��ֵ�˲�
	Mat shapedst;
	medianBlur(grayImg, shapedst, 3);
	//namedWindow("��ֵ�˲���");
	//imshow("��ֵ�˲���",shapedst);
	//sobel��
	double M[64][64], J[64][64];
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			M[i][j] = (double)shapedst.at<uchar>(i, j);
			J[i][j] = M[i][j];
		}
	}

	for (int i = 1; i < 64 - 1; i++) {
		for (int j = 1; j < 64 - 1; j++) {
			J[i][j] = abs(M[i - 1][j + 1] - M[i - 1][j - 1] + 2 * M[i][j + 1] - 2 * M[i][j - 1] + M[i + 1][j + 1] - M[i + 1][j - 1]) +
				abs(M[i - 1][j - 1] - M[i + 1][j - 1] + 2 * M[i - 1][j] - 2 * M[i + 1][j] + M[i - 1][j + 1] - M[i + 1][j + 1]);
		}
	}
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			shapedst.at<uchar>(i, j) = (uchar)J[i][j];
		}
	}

	//namedWindow("�񻯺�");
	//imshow("�񻯺�",shapedst);
	//std::cout << shapedst.size() << std::endl;

	//������ֵ�����ж�ֵ��
	double t1 = 150, t0 = 10;
	while (1) {
		double L = 0, countL = 0, H = 0, countH = 0;
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j<64; j++)
				if ((double)shapedst.at<uchar>(i, j) < t1) {
					L += (double)shapedst.at<uchar>(i, j);
					countL++;
				}
				else {
					H += (double)shapedst.at<uchar>(i, j);
					countH++;
				}
		}
		double u1, u2;
		u1 = L / countL; u2 = H / countH;
		double t2 = (u1 + u2) / 2;
		t1 = t2;
		if (abs(t1 - t2) <= t0)
			break;

	}
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			if ((double)shapedst.at<uchar>(i, j) < t1)
				shapedst.at<uchar>(i, j) = uchar(0);
			else
				shapedst.at<uchar>(i, j) = uchar(255);
		}
	}
	//namedWindow("��ֵ����");
	//imshow("��ֵ����",shapedst);
	//std::cout << shapedst.size() << std::endl;
	//����Hu����غ�������
	vector<double> myhu;
	IplImage ipl = shapedst;
	myhu = HuMoment(&ipl);

	vector<double>::iterator itt;
	double MHu[7] = { 0 };
	int ii = 0;
	for (itt = myhu.begin(); itt != myhu.end(); itt++) {
		MHu[ii] = *itt;
		ii++;
	}
	Eig_shape.Shape0 = MHu[0];
	Eig_shape.Shape1 = MHu[1];
	Eig_shape.Shape2 = MHu[2];
	Eig_shape.Shape3 = MHu[3];
	Eig_shape.Shape4 = MHu[4];
	Eig_shape.Shape5= MHu[5];
	Eig_shape.Shape6 = MHu[6];

	Eig_shape.Shape7 = 0;//�����ʻ�û��
	Eig_shape.Name = path.fname;
	Eig_shape.Path = path.fpath;


	return Eig_shape;
}

//**********************************
//          Ԥ����
//**********************************

//��ɫֱ��ͼ���⻯
IplImage* CmyCBIR_4Dlg::EqualizeHistColorImage(IplImage *pImage)
{
	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
	// ԭͼ��ֳɸ�ͨ�����پ��⻯,���ϲ�����ɫͼ���ֱ��ͼ���⻯  
	const int MAX_CHANNEL = 4;
	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };

	int i;
	for (i = 0; i < pImage->nChannels; i++)
		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);

	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);

	for (i = 0; i < pImage->nChannels; i++)
		cvEqualizeHist(pImageChannel[i], pImageChannel[i]);

	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);

	for (i = 0; i < pImage->nChannels; i++)
		cvReleaseImage(&pImageChannel[i]);

	return pEquaImage;
}


Mat CmyCBIR_4Dlg::PreStep(Mat mat)
{
	Mat img_resize;
	//AfxMessageBox(_T("aaaaaaaaaaa"));
	resize(mat, img_resize, Size(64, 64));//�������ô�С
	//��ֵ�˲�
	//AfxMessageBox(_T("bbbbbbbbbbb"));
	Mat dst;
	medianBlur(img_resize, dst, 3);

	//ֱ��ͼ���⻯
	//AfxMessageBox(_T("cccccccccccc"));
	IplImage iplimage = dst;
	IplImage* pHist = EqualizeHistColorImage(&iplimage);

	Mat img_hist = cvarrToMat(pHist);
	//AfxMessageBox(_T("dddddddddddddd"));
	return img_hist;
}

//��ʼ����ť
void CmyCBIR_4Dlg::OnBnClickedInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string initPath,initName;
	ColorEig ce;
	TextureEig te;
	ShapeEig se;
	MYSQL *m_sqlCon;
	//��ʼ�����ݿ����
	m_sqlCon=mysql_init(NULL);

	if (!mysql_real_connect(m_sqlCon, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return;
	}
	else
	{
		AfxMessageBox(_T("���ݿ����ӳɹ�"));
		UpdateData(true);
		//�������ݿ��ַ���ʽ�����������������
		mysql_query(m_sqlCon, "set names 'gb2312'");
		//����
		char deleteAll[1000];
		sprintf(deleteAll, "delete from mycolor");
		mysql_real_query(m_sqlCon, deleteAll, strlen(deleteAll));
		sprintf(deleteAll, "delete from mytexture");
		mysql_real_query(m_sqlCon, deleteAll, strlen(deleteAll));
		sprintf(deleteAll, "delete from myshape");
		mysql_real_query(m_sqlCon, deleteAll, strlen(deleteAll));
		//AfxMessageBox(_T("111111111111111"));

		for (int i = 1; i < 91; i++) {
			if (i < 10) {
				initPath = (string)"G:\\butterfly\\image_000" + Dig2Alp(i) + (string)".jpg";//��·����
				initName=(string)"image_000"+ Dig2Alp(i) + (string)".jpg";
			}
			else {
				initPath = (string)"G:\\butterfly\\image_00" + Dig2Alp(i) + (string)".jpg";
				initName= (string)"image_00" + Dig2Alp(i) + (string)".jpg";
			}
			
			NamePath fpath;
			Mat img = imread(initPath,1);
			Mat img2;
			img2 = PreStep(img);
			//AfxMessageBox(_T("1111111111111222222"));
			ce = FuncColor(img2, fpath);
			te = FuncTexture(img2, fpath);
			se = FuncShape(img2, fpath);
			//AfxMessageBox(_T("2222222222222"));
			char insertce[1000], insertte[1000], insertse[1000];
			sprintf(insertce, "insert into mycolor(Name,ColorEig1,ColorEig2,ColorEig3,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%s\')",
				initName.c_str(),ce.ColorEig1,ce.ColorEig2,ce.ColorEig3, initPath.c_str());
			mysql_real_query(m_sqlCon, insertce, strlen(insertce));
			//AfxMessageBox(_T("3333333333333"));
			sprintf(insertte, "insert into mytexture(Name,Exp1,Exp2,Exp3,Exp4,Stadv1,Stadv2,Stadv3,Stadv4,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%s\')",
				initName.c_str(), te.Exp1, te.Exp2, te.Exp3, te.Exp4, te.Stadv1, te.Stadv2, te.Stadv3, te.Stadv4, initPath.c_str());
			mysql_real_query(m_sqlCon, insertte, strlen(insertte));
			sprintf(insertse, "insert into myshape(Name,Shape0,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%s\')",
				initName.c_str(), se.Shape0, se.Shape1, se.Shape2, se.Shape3, se.Shape4, se.Shape5, se.Shape6, se.Shape7, initPath.c_str());
			mysql_real_query(m_sqlCon, insertse, strlen(insertse));
			PathMap.insert(pair<string, string>(initName, initPath));//���ļ�������·��

		}
		
	}

	UpdateData(false);
	mysql_close(m_sqlCon);//�ر�����
}


//**********************************
//          ��ɫ����ֵ���ƶ�
//**********************************
double CmyCBIR_4Dlg::DisColorEig(ColorEig x1, ColorEig x2)
{
	double dis = 0;
	dis = sqrt((x1.ColorEig1 - x2.ColorEig1)*(x1.ColorEig1 - x2.ColorEig1) +
		(x1.ColorEig2 - x2.ColorEig2)*(x1.ColorEig2 - x2.ColorEig2) +
		(x1.ColorEig3 - x2.ColorEig3)*(x1.ColorEig3 - x2.ColorEig3));
	return dis;
}
//**********************************
//          ��������ֵ���ƶ�
//**********************************
double CmyCBIR_4Dlg::DisTextureEig(TextureEig x1, TextureEig x2)
{
	double dis = 0;
	dis = sqrt((x1.Exp1 - x2.Exp1)*(x1.Exp1 - x2.Exp1) +
		(x1.Exp2 - x2.Exp2)*(x1.Exp2 - x2.Exp2) +
		(x1.Exp3 - x2.Exp3)*(x1.Exp3 - x2.Exp3) +
		(x1.Exp4 - x2.Exp4)*(x1.Exp4 - x2.Exp4) +
		(x1.Stadv1 - x2.Stadv1)*(x1.Stadv1 - x2.Stadv1) +
		(x1.Stadv2 - x2.Stadv2)*(x1.Stadv2 - x2.Stadv2) +
		(x1.Stadv3 - x2.Stadv3)*(x1.Stadv3 - x2.Stadv3) +
		(x1.Stadv4 - x2.Stadv4)*(x1.Stadv4 - x2.Stadv4));
	return dis;
}
//**********************************
//          ��״����ֵ���ƶ�
//**********************************
double CmyCBIR_4Dlg::DisShapeEig(ShapeEig x1, ShapeEig x2)
{
	double dis = 0;
	dis = sqrt((x1.Shape0 - x2.Shape0)*(x1.Shape0 - x2.Shape0) +
		(x1.Shape1 - x2.Shape1)*(x1.Shape1 - x2.Shape1) +
		(x1.Shape2 - x2.Shape2)*(x1.Shape2 - x2.Shape2) +
		(x1.Shape3 - x2.Shape3)*(x1.Shape3 - x2.Shape3) +
		(x1.Shape4 - x2.Shape4)*(x1.Shape4 - x2.Shape4) +
		(x1.Shape5 - x2.Shape5)*(x1.Shape5 - x2.Shape5) +
		(x1.Shape6 - x2.Shape6)*(x1.Shape6 - x2.Shape6) +
		(x1.Shape7 - x2.Shape7)*(x1.Shape7 - x2.Shape7));
	return dis;
}

//ͼƬ������ť
void CmyCBIR_4Dlg::OnBnClickedJiansuo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int pickname = 1021;//ID��
	CString temps;
	temps.Format("ѡ��%d��ť", radio_method);
	AfxMessageBox(temps);
	if (radio_method == 0) {
		//��ɫ����ֵ
		vector<XSName> ce;
		ce = GetColorEig(pic_colorEig);
		SetxsEdit(ce);
		ShowListBox(ce);
		for (int i = 0; i < ce.size(); i++) {
			string finalPath = PathMap[ce[i].Name];
			Mat img = imread(finalPath, 1);
			renderScene(img, pickname);
			pickname++;
		}
	}
	else if (radio_method == 1) {
		//��������ֵ
		vector<XSName> te;
		te = GetTextureEig(pic_textureEig);
		SetxsEdit(te);
		ShowListBox(te);
		for (int i = 0; i < te.size(); i++) {
			string finalPath = PathMap[te[i].Name];
			Mat img = imread(finalPath, 1);
			renderScene(img, pickname);
			pickname++;
			
		}
	}
	else if (radio_method == 2) {
		//��״����ֵ
		vector<XSName> se;
		se = GetShapeEig(pic_shapeEig);
		SetxsEdit(se);
		ShowListBox(se);
		for (int i = 0; i < se.size(); i++) {
			string finalPath = PathMap[se[i].Name];
			Mat img = imread(finalPath, 1);
			renderScene(img, pickname);
			pickname++;
		}
	}
	else
		AfxMessageBox(_T("��ѡ������������ֵ��"));


	
}

//����ͼƬ��ť
void CmyCBIR_4Dlg::OnBnClickedCharu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int rt1,rt2,rt3;
	CString str;
	std::string  tstring,tname;
	char szFilters[] = "JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp|";
	CFileDialog fileDlg(TRUE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp| All Files (*.*) |*.*||"), NULL);
	if (fileDlg.DoModal() != IDOK)
		return;
	str = fileDlg.GetPathName();
	tstring = str.GetBuffer(0);//·��
	str = fileDlg.GetFileName();
	tname = str.GetBuffer(0);
	Mat mat = imread(tstring, 1);//��ȡѡ���ͼƬ
	Mat mat2 = PreStep(mat);//Ԥ����
	NamePath mpath;
	mpath.fname = tname;
	mpath.fpath = tstring;
	ColorEig ce = FuncColor(mat2, mpath);
	TextureEig te = FuncTexture(mat2, mpath);
	ShapeEig se = FuncShape(mat2, mpath);
	PathMap.insert(pair<string, string>(tname, tstring));
	renderScene(mat, IDC_PIC);
	
	MYSQL *con;
	con = mysql_init(NULL);
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return;
	}
	else
	{
		AfxMessageBox(_T("���ݿ����ӳɹ�"));
		UpdateData(true);
		//�������ݿ��ַ���ʽ�����������������
		mysql_query(con, "set names 'gb2312'");

		char insertce[1000], insertte[1000], insertse[1000];
		sprintf(insertce, "insert into mycolor(Name,ColorEig1,ColorEig2,ColorEig3,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%s\')",
			tname.c_str(), ce.ColorEig1, ce.ColorEig2, ce.ColorEig3, tstring.c_str());
		rt1=mysql_real_query(con, insertce, strlen(insertce));
		//AfxMessageBox(_T("3333333333333"));
		sprintf(insertte, "insert into mytexture(Name,Exp1,Exp2,Exp3,Exp4,Stadv1,Stadv2,Stadv3,Stadv4,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%s\')",
			tname.c_str(), te.Exp1, te.Exp2, te.Exp3, te.Exp4, te.Stadv1, te.Stadv2, te.Stadv3, te.Stadv4, tstring.c_str());
		rt2=mysql_real_query(con, insertte, strlen(insertte));
		sprintf(insertse, "insert into myshape(Name,Shape0,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Path) values(\'%s\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%f\',\'%s\')",
			tname.c_str(), se.Shape0, se.Shape1, se.Shape2, se.Shape3, se.Shape4, se.Shape5, se.Shape6, se.Shape7, tstring.c_str());
		rt3=mysql_real_query(con, insertse, strlen(insertse));
		if (rt1 == 0 && rt2 == 0 && rt3 == 0) {
			AfxMessageBox(_T("ͼƬ��Ϣ����ɹ�"));
		}

	}
	UpdateData(false);
	mysql_close(con);
	//AfxMessageBox(_T("����"));
}


//��ɫ��ѡ��ť
void CmyCBIR_4Dlg::OnBnClickedYanse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	radio_method = 0;
	/*CButton *p0 = (CButton*)GetDlgItem(IDC_YANSE);
	p0->EnableWindow(TRUE);
	CButton *p1 = (CButton*)GetDlgItem(IDC_WENLI);
	p0->EnableWindow(FALSE);
	CButton *p2 = (CButton*)GetDlgItem(IDC_XINGZHUANG);
	p0->EnableWindow(FALSE);*/
}

//����ѡ��ť
void CmyCBIR_4Dlg::OnBnClickedWenli()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	radio_method = 1;
	/*CButton *p0 = (CButton*)GetDlgItem(IDC_YANSE);
	p0->EnableWindow(FALSE);
	CButton *p1 = (CButton*)GetDlgItem(IDC_WENLI);
	p0->EnableWindow(TRUE);
	CButton *p2 = (CButton*)GetDlgItem(IDC_XINGZHUANG);
	p0->EnableWindow(FALSE);*/
}

//��״��ѡ��ť
void CmyCBIR_4Dlg::OnBnClickedXingzhuang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	radio_method = 2;
	/*CButton *p0 = (CButton*)GetDlgItem(IDC_YANSE);
	p0->EnableWindow(FALSE);
	CButton *p1 = (CButton*)GetDlgItem(IDC_WENLI);
	p0->EnableWindow(FALSE);
	CButton *p2 = (CButton*)GetDlgItem(IDC_XINGZHUANG);
	p0->EnableWindow(TRUE);*/
}


void CmyCBIR_4Dlg::OnBnClickedShanchu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	std::string  tstring, tname;
	char szFilters[] = "JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp|";
	CFileDialog fileDlg(TRUE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("JPEG(*.jpg)|*.jpg|GIF(*.gif)|*.gif|bmp(*.bmp)|*.bmp| All Files (*.*) |*.*||"), NULL);
	if (fileDlg.DoModal() != IDOK)
		return;
	str = fileDlg.GetPathName();
	tstring = str.GetBuffer(0);//·��
	str = fileDlg.GetFileName();
	tname = str.GetBuffer(0);

	MYSQL *con;
	con = mysql_init(NULL);
	int rt;
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0)) {
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return;
	}
	else
	{
		char select[1000];
		sprintf(select, "delete from  mycolor where Name='\%s\'",tname.c_str());
		rt = mysql_real_query(con, select, strlen(select));
		
		sprintf(select, "delete from  mytexture where Name='\%s\'", tname.c_str());
		rt = mysql_real_query(con, select, strlen(select));
		
		sprintf(select, "delete from  myshape where Name='\%s\'", tname.c_str());
		rt = mysql_real_query(con, select, strlen(select));

		if (rt == 0) {
			AfxMessageBox(_T("ͼƬ��Ϣɾ���ɹ�"));
		}
		
	}
	UpdateData(false);
	mysql_close(con);
}

//��ѯ��ɫ����ֵ��������
vector<ColorEig> CmyCBIR_4Dlg::SelectColorEig()
{
	vector<ColorEig> allEig;
	ColorEig ce;
	allEig.clear();
	//���ݿ�
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	con = mysql_init(NULL);
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		
	}
	else
	{
		AfxMessageBox(_T("���ݿ����ӳɹ�"));
		UpdateData(true);
		//�������ݿ��ַ���ʽ�����������������
		mysql_query(con, "set names 'gb2312'");

		char select[1000];
		vector<std::string> rowline;
		std::string eachrow;
		sprintf(select, "select Name,ColorEig1,ColorEig2,ColorEig3,Path from mycolor");
		//ִ��
		int rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			int t;
			for (t = 0; t < mysql_num_fields(res);) {
				eachrow = row[t];//Name
				t++;
				ce.Name = eachrow;
				eachrow = row[t];//ColorEig1
				t++;
				ce.ColorEig1 = atof(eachrow.c_str());
				eachrow = row[t];//ColorEig2
				t++;
				ce.ColorEig2 = atof(eachrow.c_str());
				eachrow = row[t];//ColorEig3
				t++;
				ce.ColorEig3 = atof(eachrow.c_str());
				eachrow = row[t];//Path
				t++;
				ce.Path = eachrow;

				allEig.push_back(ce);

			}
		}

	}
	UpdateData(false);
	mysql_close(con);
	

	return allEig;
}
//��ѯ��������ֵ��������
vector<TextureEig> CmyCBIR_4Dlg::SelectTextureEig()
{
	vector<TextureEig> allEig;
	TextureEig te;
	allEig.clear();
	//���ݿ�
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	con = mysql_init(NULL);
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		
	}
	else
	{
		AfxMessageBox(_T("���ݿ����ӳɹ�"));
		UpdateData(true);
		//�������ݿ��ַ���ʽ�����������������
		mysql_query(con, "set names 'gb2312'");
		//���ݿ�
		char select[1000];
		vector<std::string> rowline;
		std::string eachrow;
		sprintf(select, "select Name,Exp1,Exp2,Exp3,Exp4,Stadv1,Stadv2,Stadv3,Stadv4,Path from mytexture");
		//ִ��
		int rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			int t;
			for (t = 0; t < mysql_num_fields(res);) {
				eachrow = row[t];//Name
				t++;
				te.Name = eachrow;
				eachrow = row[t];//Exp1
				t++;
				te.Exp1 = atof(eachrow.c_str());
				eachrow = row[t];//Exp2
				t++;
				te.Exp2 = atof(eachrow.c_str());
				eachrow = row[t];//Exp3
				t++;
				te.Exp3 = atof(eachrow.c_str());
				eachrow = row[t];//Exp4
				t++;
				te.Exp4 = atof(eachrow.c_str());
				eachrow = row[t];//Stadv1
				t++;
				te.Stadv1 = atof(eachrow.c_str());
				eachrow = row[t];//Stadv2
				t++;
				te.Stadv2 = atof(eachrow.c_str());
				eachrow = row[t];//Stadv3
				t++;
				te.Stadv3 = atof(eachrow.c_str());
				eachrow = row[t];//Stadv4
				t++;
				te.Stadv4 = atof(eachrow.c_str());
				eachrow = row[t];//Path
				t++;
				te.Path = eachrow;

				allEig.push_back(te);

			}
		}

	}
	UpdateData(false);
	mysql_close(con);


	return allEig;
}
//��ѯ��״����ֵ��������
vector<ShapeEig> CmyCBIR_4Dlg::SelectShapeEig()
{
	vector<ShapeEig> allEig;
	ShapeEig se;
	allEig.clear();
	//���ݿ�
	//���ݿ�
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	con = mysql_init(NULL);
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		
	}
	else
	{
		AfxMessageBox(_T("���ݿ����ӳɹ�"));
		UpdateData(true);
		//�������ݿ��ַ���ʽ�����������������
		mysql_query(con, "set names 'gb2312'");

		char select[1000];
		vector<std::string> rowline;
		std::string eachrow;
		sprintf(select, "select Name,Shape0,Shape1,Shape2,Shape3,Shape4,Shape5,Shape6,Shape7,Path from myshape");
		//ִ��
		int rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			int t;
			for (t = 0; t < mysql_num_fields(res);) {
				eachrow = row[t];//Name
				t++;
				se.Name = eachrow;
				eachrow = row[t];//Shape0
				t++;
				se.Shape0 = atof(eachrow.c_str());
				eachrow = row[t];//Shape1
				t++;
				se.Shape1 = atof(eachrow.c_str());
				eachrow = row[t];//Shape2
				t++;
				se.Shape2 = atof(eachrow.c_str());
				eachrow = row[t];//Shape3
				t++;
				se.Shape3= atof(eachrow.c_str());
				eachrow = row[t];//Shape4
				t++;
				se.Shape4= atof(eachrow.c_str());
				eachrow = row[t];//Shape5
				t++;
				se.Shape5 = atof(eachrow.c_str());
				eachrow = row[t];//Shape6
				t++;
				se.Shape6 = atof(eachrow.c_str());
				eachrow = row[t];//Shape7
				t++;
				se.Shape7= atof(eachrow.c_str());
				eachrow = row[t];//Path
				t++;
				se.Path = eachrow;

				allEig.push_back(se);

			}
		}

	}
	UpdateData(false);
	mysql_close(con);


	return allEig;
}

//��ѯ��¼
void CmyCBIR_4Dlg::OnBnClickedTongji()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	string numcount1,numcount2,numcount3;
	con = mysql_init(NULL);
	int rt;
	if (!mysql_real_connect(con, "localhost", "root",
		"123zyfwan", "mycbir", 3306, NULL, 0)) {
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return;
	}
	else
	{
		char select[1000];
		sprintf(select, "select count(*) from mycolor");
		rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++)
				numcount1 = row[t];
		}
		
		sprintf(select, "select count(*) from mytexture");
		rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++)
				numcount2 = row[t];
		}
		
		sprintf(select, "select count(*) from myshape");
		rt = mysql_real_query(con, select, strlen(select));
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++)
				numcount3 = row[t];
		}
	}
	CString sss;
	sss.Format(_T("��ɫ����%d����¼���������%d����¼����״����%d����¼"),atoi(numcount1.c_str()), atoi(numcount2.c_str()), atoi(numcount3.c_str()));
	AfxMessageBox(sss);
	UpdateData(false);
	mysql_close(con);
}

//��ʾListBox������
void CmyCBIR_4Dlg::ShowListBox(vector<XSName> vecxs)
{
	CListBox *m_listbox;
	m_listbox = (CListBox*)GetDlgItem(IDC_LIST);
	m_listbox->ResetContent();//���
	string fpath[9];
	for (int i = 0; i < vecxs.size(); i++) {
		fpath[i] = PathMap[vecxs[i].Name];
	}
	CString mstr[9] ;
	for (int i = 0; i < vecxs.size(); i++) {
		mstr[i].Format(_T(fpath[i].c_str()));
		m_listbox->AddString(mstr[i]);
	}

}
