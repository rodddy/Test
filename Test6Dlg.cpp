
// Test6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test6.h"
#include "Test6Dlg.h"

#include "head/ximage.h"

//#pragma comment(lib, "lib/png.lib")

//#pragma comment(lib, "lib/libdcr.lib")

//#pragma comment(lib, "lib/Jpeg.lib")

//#pragma comment(lib, "lib/zlib.lib")

#pragma comment(lib, "lib/tiff.lib")

//#pragma comment(lib, "lib/jasper.lib")

#pragma comment(lib, "lib/cximage.lib")

//#pragma comment(lib, "lib/mng.lib")



#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




CTest6Dlg::CTest6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest6Dlg::IDD, pParent)
	{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CTest6Dlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
	}

BEGIN_MESSAGE_MAP(CTest6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTest6Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTest6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTest6Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTest6Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTest6Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTest6Dlg::OnBnClickedButton5)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CTest6Dlg 消息处理程序

BOOL CTest6Dlg::OnInitDialog()
	{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	}

void CTest6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	CDialog::OnSysCommand(nID, lParam);
	}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest6Dlg::OnPaint()
	{
	if (IsIconic())
		{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		}
	else
		{
		CDialogEx::OnPaint();
		}
	}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest6Dlg::OnQueryDragIcon()
	{
	return static_cast<HCURSOR>(m_hIcon);
	}


void CTest6Dlg::OnBnClickedOk()
	{

	CString strFileName; // 图像文件名

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.bmp)||"); 

	//假如点击对话框确定按钮

	if(dlg.DoModal() == IDOK)

		// 获取文件名

		strFileName = dlg.GetPathName();

	//BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;

	//为图像数据申请空间
	//memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));

	DWORD dataBytes = bmpHeader.bfSize - sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER);
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	bmpFile.Close();

	//显示图像
	//CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
	//CRect rect;
	//pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	//CDC *pDC=pWnd->GetDC(); //获得pictrue控件的DC
	//pDC->SetStretchBltMode(COLORONCOLOR);
	//StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,
	//	bmpInfo.biWidth,bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);

	//ReleaseDC(pDC);

	// 加载BMP位图
		BYTE* BmpData=(BYTE*)new char[dataBytes+ sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];             //图像数据
		memcpy(BmpData,&bmpInfo,sizeof(BITMAPFILEHEADER));
		memcpy(BmpData+sizeof(BITMAPFILEHEADER),&bmpInfo,sizeof(BITMAPINFOHEADER));
		memcpy(BmpData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),pBmpData,dataBytes);

	CxImage img(BmpData,dataBytes+ sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),CXIMAGE_FORMAT_BMP);
	image.Save(_T("image.tiff"),CXIMAGE_FORMAT_TIF);

	// 判断图像是否有效

	//	image.SetJpegQuality( 80 );

	//	// 将位图转换成JPEG格式图像

	//	image.Save(_T("image.tiff"),CXIMAGE_FORMAT_TIF);

	}

BOOL saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
	{
	if(!imgBuf)
		return 0;

	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
	int colorTablesize = 0;
	if(biBitCount == 8)
		colorTablesize = 1024;
	int lineByte=(width * biBitCount/8+3)/4*4;

	//待存储图像数据每行字节数为4的倍数

	FILE *fp=fopen(bmpName,"wb");
	//以二进制写的方式打开文件

	if(fp==0) return 0;

	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits=54+colorTablesize;
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
	//如果灰度图像，有颜色表，写入文件
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
	//关闭文件
	fclose(fp);
	return 1;
	}


void CTest6Dlg::OnBnClickedButton1()
	{
	// TODO: 在此添加控件通知处理程序代码

	CString strFileName; // 图像文件名

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.bmp)||"); 

	//假如点击对话框确定按钮

	if(dlg.DoModal() == IDOK)

		// 获取文件名

		strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//颜色表指针
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}
	//为图像数据申请空间
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	char writePath[]="lenacpy1.BMP";
	saveBmp(writePath, pBmpData, bmpInfo.biWidth, bmpInfo.biHeight, bmpInfo.biBitCount, pColorTable);
	}

void CTest6Dlg::OnBnClickedButton2()
	{
	// TODO: 在此添加控件通知处理程序代码
	CString strFileName; // 图像文件名

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.bmp)||"); 

	//假如点击对话框确定按钮

	if(dlg.DoModal() == IDOK)

		// 获取文件名

		strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//颜色表指针
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}

	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	//为图像数据申请空间
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));

	BYTE *imfData;             //图像数据
	imfData = (BYTE*)new char[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + dataBytes];



	HANDLE m_hFile= CreateFile( "abc.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL );

	DWORD	ret,ret2,ret3;
	WriteFile( m_hFile, &bmpHeader, sizeof(BITMAPFILEHEADER), &ret, NULL );
	WriteFile( m_hFile, &bmpInfo, sizeof(BITMAPINFOHEADER), &ret, NULL );
	WriteFile( m_hFile, pBmpData, dataBytes, &ret, NULL );

	CloseHandle(m_hFile);


	memcpy(imfData,&bmpHeader,sizeof(BITMAPFILEHEADER));
	memcpy(imfData+sizeof(BITMAPFILEHEADER),&bmpInfo,sizeof(BITMAPINFOHEADER));
	memcpy(imfData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),pBmpData,dataBytes);
	//memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));

	CxImage image_temp( imfData,bmpInfo.biSizeImage,CXIMAGE_FORMAT_BMP);
	 image_temp.Save("adfasdfasdf.tiff",CXIMAGE_FORMAT_TIF);
	}


void CTest6Dlg::OnBnClickedButton3()
	{
	// TODO: 在此添加控件通知处理程序代码

	CString strFileName; // 图像文件名

	CFileDialog dlg( TRUE , "(*.tif)|*.tif","*.tif" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.tif)||"); 

	//假如点击对话框确定按钮

	if(dlg.DoModal() == IDOK)

		// 获取文件名

		strFileName = dlg.GetPathName();

	CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

	CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
	CRect rect;
	pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	CxImage image;
	image.Load(strFileName, CXIMAGE_FORMAT_TIF);

	for(int i = 0;i < 6;i ++){
		CString LayPath;
		LayPath.Format("%s%d",_T("Lay") ,i);
		LayPath = LayPath + _T("//");
		if (!CreateDirectory(LayPath, NULL ) )
			{
			CString strMsg;
			strMsg.Format ("创建路径\"%s\"失败！是否继续?", LayPath);
			}
		for(int j = 0; j < 5;j ++){
			CString FileName;
			FileName.Format("%s%s%d",LayPath , _T("Image") , j);
			image.Save(FileName,CXIMAGE_FORMAT_BMP);
			}
		}
	image.Draw(pDC->GetSafeHdc(),rect);
	//     pDC->DeleteDC();

	//CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
	//CRect rect;
	//pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	//CDC *pDC=pWnd->GetDC(); //获得pictrue控件的DC
	//pDC->SetStretchBltMode(COLORONCOLOR);
	//StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,
	//	bmpInfo.biWidth,bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);

	ReleaseDC(pDC);

	}


void CTest6Dlg::OnBnClickedButton4()
	{

	// TODO: 在此添加控件通知处理程序代码

	CString strFileName; // 图像文件名
	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.bmp)||"); 

	if(dlg.DoModal() == IDOK)

		// 获取文件名

	strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//颜色表指针
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}
	//为图像数据申请空间
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	BYTE temp[256];
	for(int i = 0;i<256;i++){
		temp[i] = pBmpData[i];
		//printf(temp[i]);
		}

	char writePath[]="lenacpy1.BMP";
	saveBmp(writePath, pBmpData, bmpInfo.biWidth, bmpInfo.biHeight, bmpInfo.biBitCount, pColorTable);
	}


void CTest6Dlg::OnBnClickedButton5()
	{
	// TODO: 在此添加控件通知处理程序代码

	CString strFileName; // 图像文件名

	CFileDialog dlg( TRUE , "(*.tif)|*.tif","*.tif" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"位图文件(*.tif)||"); 

	//假如点击对话框确定按钮

	if(dlg.DoModal() == IDOK)

		// 获取文件名

		strFileName = dlg.GetPathName();
	
	image.Load(strFileName, CXIMAGE_FORMAT_TIF);
	CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

	CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
	CRect rect;
	pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域

	image.Draw(pDC->GetSafeHdc(),rect);
	//image.SetCodecOption();
	image.Save("img.tif",CXIMAGE_FORMAT_TIF);
	image.IncreaseBpp(16);
	image.Save("img16.tif",CXIMAGE_FORMAT_TIF);
	}

BOOL CTest6Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	double rates = 1;
	if (zDelta > 0){
		rates = rates - 0.1;
		CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

		CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域

		CRect rt(rect.TopLeft().x,rect.TopLeft().y,rect.Width()*rates,rect.Height()*rates);
		image.Draw(pDC->GetSafeHdc(),rt);
		}
	else{
		rates = rates -0.2;
		CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

		CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		//SIZE sz = {rect.Width()*0.6,rect.Height()*0.6};
		
		CRect rt(rect.TopLeft().x,rect.TopLeft().y,rect.Width()*rates,rect.Height()*rates);
		image.Draw(pDC->GetSafeHdc(),rt);

		}

	//return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	return 0;

	}
