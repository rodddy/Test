
// Test6Dlg.cpp : ʵ���ļ�
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


// CTest6Dlg ��Ϣ�������

BOOL CTest6Dlg::OnInitDialog()
	{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
	}

void CTest6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	CDialog::OnSysCommand(nID, lParam);
	}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTest6Dlg::OnPaint()
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
HCURSOR CTest6Dlg::OnQueryDragIcon()
	{
	return static_cast<HCURSOR>(m_hIcon);
	}


void CTest6Dlg::OnBnClickedOk()
	{

	CString strFileName; // ͼ���ļ���

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.bmp)||"); 

	//�������Ի���ȷ����ť

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

		strFileName = dlg.GetPathName();

	//BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;

	//Ϊͼ����������ռ�
	//memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));

	DWORD dataBytes = bmpHeader.bfSize - sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER);
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	bmpFile.Close();

	//��ʾͼ��
	//CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
	//CRect rect;
	//pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
	//CDC *pDC=pWnd->GetDC(); //���pictrue�ؼ���DC
	//pDC->SetStretchBltMode(COLORONCOLOR);
	//StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,
	//	bmpInfo.biWidth,bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);

	//ReleaseDC(pDC);

	// ����BMPλͼ
		BYTE* BmpData=(BYTE*)new char[dataBytes+ sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];             //ͼ������
		memcpy(BmpData,&bmpInfo,sizeof(BITMAPFILEHEADER));
		memcpy(BmpData+sizeof(BITMAPFILEHEADER),&bmpInfo,sizeof(BITMAPINFOHEADER));
		memcpy(BmpData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),pBmpData,dataBytes);

	CxImage img(BmpData,dataBytes+ sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),CXIMAGE_FORMAT_BMP);
	image.Save(_T("image.tiff"),CXIMAGE_FORMAT_TIF);

	// �ж�ͼ���Ƿ���Ч

	//	image.SetJpegQuality( 80 );

	//	// ��λͼת����JPEG��ʽͼ��

	//	image.Save(_T("image.tiff"),CXIMAGE_FORMAT_TIF);

	}

BOOL saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
	{
	if(!imgBuf)
		return 0;

	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0
	int colorTablesize = 0;
	if(biBitCount == 8)
		colorTablesize = 1024;
	int lineByte=(width * biBitCount/8+3)/4*4;

	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���

	FILE *fp=fopen(bmpName,"wb");
	//�Զ�����д�ķ�ʽ���ļ�

	if(fp==0) return 0;

	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp����
	//bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
	fileHead.bfOffBits=54+colorTablesize;
	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
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
	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
	//����Ҷ�ͼ������ɫ��д���ļ�
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height*lineByte, 1, fp);
	//�ر��ļ�
	fclose(fp);
	return 1;
	}


void CTest6Dlg::OnBnClickedButton1()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strFileName; // ͼ���ļ���

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.bmp)||"); 

	//�������Ի���ȷ����ť

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

		strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//��ɫ��ָ��
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}
	//Ϊͼ����������ռ�
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	char writePath[]="lenacpy1.BMP";
	saveBmp(writePath, pBmpData, bmpInfo.biWidth, bmpInfo.biHeight, bmpInfo.biBitCount, pColorTable);
	}

void CTest6Dlg::OnBnClickedButton2()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFileName; // ͼ���ļ���

	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.bmp)||"); 

	//�������Ի���ȷ����ť

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

		strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//��ɫ��ָ��
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}

	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);

	//Ϊͼ����������ռ�
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));

	BYTE *imfData;             //ͼ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strFileName; // ͼ���ļ���

	CFileDialog dlg( TRUE , "(*.tif)|*.tif","*.tif" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.tif)||"); 

	//�������Ի���ȷ����ť

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

		strFileName = dlg.GetPathName();

	CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

	CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
	CRect rect;
	pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
	CxImage image;
	image.Load(strFileName, CXIMAGE_FORMAT_TIF);

	for(int i = 0;i < 6;i ++){
		CString LayPath;
		LayPath.Format("%s%d",_T("Lay") ,i);
		LayPath = LayPath + _T("//");
		if (!CreateDirectory(LayPath, NULL ) )
			{
			CString strMsg;
			strMsg.Format ("����·��\"%s\"ʧ�ܣ��Ƿ����?", LayPath);
			}
		for(int j = 0; j < 5;j ++){
			CString FileName;
			FileName.Format("%s%s%d",LayPath , _T("Image") , j);
			image.Save(FileName,CXIMAGE_FORMAT_BMP);
			}
		}
	image.Draw(pDC->GetSafeHdc(),rect);
	//     pDC->DeleteDC();

	//CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
	//CRect rect;
	//pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
	//CDC *pDC=pWnd->GetDC(); //���pictrue�ؼ���DC
	//pDC->SetStretchBltMode(COLORONCOLOR);
	//StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,
	//	bmpInfo.biWidth,bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);

	ReleaseDC(pDC);

	}


void CTest6Dlg::OnBnClickedButton4()
	{

	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strFileName; // ͼ���ļ���
	CFileDialog dlg( TRUE , "(*.bmp)|*.bmp","*.bmp" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.bmp)||"); 

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

	strFileName = dlg.GetPathName();

	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

	RGBQUAD *pColorTable;//��ɫ��ָ��
	if(bmpInfo.biBitCount==8)
		{
		pColorTable=new RGBQUAD[256];
		bmpFile.Read(pColorTable,sizeof(RGBQUAD));
		}
	//Ϊͼ����������ռ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strFileName; // ͼ���ļ���

	CFileDialog dlg( TRUE , "(*.tif)|*.tif","*.tif" ,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,"λͼ�ļ�(*.tif)||"); 

	//�������Ի���ȷ����ť

	if(dlg.DoModal() == IDOK)

		// ��ȡ�ļ���

		strFileName = dlg.GetPathName();
	
	image.Load(strFileName, CXIMAGE_FORMAT_TIF);
	CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

	CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
	CRect rect;
	pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������

	image.Draw(pDC->GetSafeHdc(),rect);
	//image.SetCodecOption();
	image.Save("img.tif",CXIMAGE_FORMAT_TIF);
	image.IncreaseBpp(16);
	image.Save("img16.tif",CXIMAGE_FORMAT_TIF);
	}

BOOL CTest6Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	double rates = 1;
	if (zDelta > 0){
		rates = rates - 0.1;
		CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

		CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������

		CRect rt(rect.TopLeft().x,rect.TopLeft().y,rect.Width()*rates,rect.Height()*rates);
		image.Draw(pDC->GetSafeHdc(),rt);
		}
	else{
		rates = rates -0.2;
		CDC *pDC=GetDlgItem(IDC_STATIC_PIC)->GetDC();

		CWnd *pWnd=GetDlgItem(IDC_STATIC_PIC); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		//SIZE sz = {rect.Width()*0.6,rect.Height()*0.6};
		
		CRect rt(rect.TopLeft().x,rect.TopLeft().y,rect.Width()*rates,rect.Height()*rates);
		image.Draw(pDC->GetSafeHdc(),rt);

		}

	//return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	return 0;

	}
