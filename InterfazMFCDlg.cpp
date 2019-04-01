
// InterfazMFCDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "InterfazMFC.h"
#include "InterfazMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;



Mat imagenOrigi;
Mat temp;

Mat aux= Mat::zeros(100,100, CV_8UC1);;
string filename ="C:\\Users\\USUARIO\\Documents\\Visual Studio 2017\\Proyectos OPENCV\\InterfazMFC\\5.jpg";
// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CInterfazMFCDlg



CInterfazMFCDlg::CInterfazMFCDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_INTERFAZMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfazMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Opciones, opcionesControl);
}

BEGIN_MESSAGE_MAP(CInterfazMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(Opciones, &CInterfazMFCDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(Opciones, &CInterfazMFCDlg::OnCbnSelchangeOpciones)
	ON_BN_CLICKED(abrir, &CInterfazMFCDlg::OnBnClickedabrir)
	ON_BN_CLICKED(actualizar, &CInterfazMFCDlg::OnBnClickedactualizar)
	ON_BN_CLICKED(Refresh, &CInterfazMFCDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()


// Controladores de mensajes de CInterfazMFCDlg

BOOL CInterfazMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	opcionesControl.SetCurSel(0);


	//if (Color) imagenP = imread(filename);
	 imagenOrigi = imread(filename,0);
	namedWindow("Imagen1", 0);
	cvResizeWindow("Imagen1", 600, 400);
	HWND hWnd = (HWND)cvGetWindowHandle("Imagen1");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(Imagen1)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	imshow("Imagen1", imagenOrigi);
	//2da imagen
	//Rect myROI(300, 150, 200, 200);

	resize(imagenOrigi,temp, Size(600, 400), 0, 0, INTER_AREA);
	

	//temp = acTamaño;
	namedWindow("Imagen2", 0);
	cvResizeWindow("Imagen2", 600, 400);
	HWND hWnd2 = (HWND)cvGetWindowHandle("Imagen2");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(Imagen2)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);
	imshow("Imagen2", temp);
	//if (Color) split(ImgModificada, RGB);



	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CInterfazMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CInterfazMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CInterfazMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInterfazMFCDlg::OnCbnSelchangeCombo1()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}




void CInterfazMFCDlg::OnCbnSelchangeOpciones()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}


void CInterfazMFCDlg::OnBnClickedabrir()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	TCHAR file[] = _T("jpg file (.jpg)|*jpg|png file (.png)|*png||");
	CFileDialog openfile(TRUE, _T("jpg"), _T(".jpg"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, file);
	if (openfile.DoModal() == IDOK) {
		CString filefull;
		filefull = openfile.GetPathName();
		CT2CA pszConvertedAnsiString(filefull);
		string nombre(pszConvertedAnsiString);
		filename = nombre;

	}
	imshow("Imagen1", imagenOrigi);
}


void CInterfazMFCDlg::OnBnClickedactualizar()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	imagenOrigi = imread(filename, IMREAD_GRAYSCALE);
	imshow("Imagen1", imagenOrigi);
	temp = imagenOrigi;
	imshow("Imagen2", temp);
}
void promedio() {
	Mat nueva = Mat::zeros(temp.size(), CV_8UC1);

	for (int fila = 1; fila < temp.rows - 1; fila++)
	{
		for (int col = 1; col < temp.cols - 1; col++)
		{
			nueva.at<uchar>(fila, col) = ((0.11111)*((temp.at<uchar>(fila + 1, col - 1)) + (temp.at<uchar>(fila + 1, col)) + (temp.at<uchar>(fila + 1, col + 1)) + (temp.at<uchar>(fila, col - 1)) + (temp.at<uchar>(fila, col)) + (temp.at<uchar>(fila, col + 1)) + (temp.at<uchar>(fila - 1, col - 1)) + (temp.at<uchar>(fila - 1, col)) + (temp.at<uchar>(fila - 1, col + 1))));
			//nueva.at<uchar>(fila, col) = ((temp.at<uchar>(fila, col)) + 50);
		}
	}
	aux = nueva;
}

	void gaussiano() {
	double mascara[3] [3] = { {0.0625, 0.125, 0.0625 },
											 { 0.125, 0.25, 0.125},
											 { 0.0625, 0.125, 0.0625 } };


	Mat gauss = Mat::zeros(temp.size(), CV_8UC1);
	for (int fila = 1; fila < temp.rows - 1; fila++)
	{
		for (int col = 1; col < temp.cols - 1; col++)
		{
			gauss.at<uchar>(fila, col) = (temp.at<uchar>(fila + 1, col - 1 ) * (mascara[0][0]))+ (temp.at<uchar>(fila + 1, col) * (mascara[0][1]))+ (temp.at<uchar>(fila + 1, col + 1) * (mascara[0][2])) + (temp.at<uchar>(fila, col - 1) * (mascara[1][0])) + (temp.at<uchar>(fila, col) * (mascara[1][1])) + (temp.at<uchar>(fila, col + 1) * (mascara[1][2])) + (temp.at<uchar>(fila - 1, col - 1) * (mascara[2][0])) + (temp.at<uchar>(fila - 1, col) * (mascara[2][1])) + (temp.at<uchar>(fila - 1, col + 1) * (mascara[2][2]));
			// gauss.Data[fila, col, 0] = SaturateCast((1 / (2 * 3.14*1))*(Math.Pow(2.7182818, -((fila*fila+col*col)/(2)))));

			if (gauss.at<uchar>(fila, col) > 255)
			{
				gauss.at<uchar>(fila, col) = 255;
			}
			else if (gauss.at<uchar>(fila, col) < 0)

			{
			gauss.at<uchar>(fila, col) = 0;
			}
		}
	}
	aux = gauss;
}
	void gradiente() {
		double mascaragx[3][3] = { {-0.25, -0.5, -0.25 },
												 { 0, 0, 0},
												 { 0.25, 0.5, 0.25 } };
		double mascaragy[3][3] = { {-0.25, 0, 0.25 },
										 { -0.5, 0, 0.5},
										 { -0.25, 0, 0.25 } };

		Mat gradiente = Mat::zeros(temp.size(), CV_8UC1);
		Mat gx = Mat::zeros(temp.size(), CV_8UC1);
		Mat gy = Mat::zeros(temp.size(), CV_8UC1);
		



		for (int fila = 1; fila < temp.rows - 1; fila++)
		{
			for (int col = 1; col < temp.cols - 1; col++)
			{
				gx.at<uchar>(fila, col) = (temp.at<uchar>(fila + 1, col - 1) * (mascaragx[0][0])) + (temp.at<uchar>(fila + 1, col) * (mascaragx[0][1])) + (temp.at<uchar>(fila + 1, col + 1) * (mascaragx[0][2])) + (temp.at<uchar>(fila, col - 1) * (mascaragx[1][0])) + (temp.at<uchar>(fila, col) * (mascaragx[1][1])) + (temp.at<uchar>(fila, col + 1) * (mascaragx[1][2])) + (temp.at<uchar>(fila - 1, col - 1) * (mascaragx[2][0])) + (temp.at<uchar>(fila - 1, col) * (mascaragx[2][1])) + (temp.at<uchar>(fila - 1, col + 1) * (mascaragx[2][2]));
				//gx.Data[fila, col, 0] = SaturateCast(((temp.Data[fila + 1, col - 1, 0]) * (mascaragx[0, 0]) + (temp.Data[fila + 1, col, 0]) * (mascaragx[0, 1]) + (temp.Data[fila + 1, col + 1, 0]) * (mascaragx[0, 2]) + (temp.Data[fila, col - 1, 0]) * (mascaragx[1, 0]) + (temp.Data[fila, col, 0]) * (mascaragx[1, 1]) + (temp.Data[fila, col + 1, 0]) * (mascaragx[1, 2]) + (temp.Data[fila - 1, col - 1, 0]) * (mascaragx[2, 0]) + (temp.Data[fila - 1, col, 0]) * (mascaragx[2, 1]) + (temp.Data[fila - 1, col + 1, 0]) * (mascaragx[2, 2])));
				// gx.Data[fila, col, 0] = SaturateCast((gx.Data[fila, col, 0])^2);
				if (gx.at<uchar>(fila, col) > 255)
				{
					gx.at<uchar>(fila, col) = 255;
				}
				else if (gx.at<uchar>(fila, col) < 0)

				{
					gx.at<uchar>(fila, col) = 0;
				}
				

			}
		}

		for (int fila = 1; fila < temp.rows - 1; fila++)
		{
			for (int col = 1; col < temp.cols - 1; col++)
			{
				gy.at<uchar>(fila, col) = (temp.at<uchar>(fila + 1, col - 1) * (mascaragy[0][0])) + (temp.at<uchar>(fila + 1, col) * (mascaragy[0][1])) + (temp.at<uchar>(fila + 1, col + 1) * (mascaragy[0][2])) + (temp.at<uchar>(fila, col - 1) * (mascaragy[1][0])) + (temp.at<uchar>(fila, col) * (mascaragy[1][1])) + (temp.at<uchar>(fila, col + 1) * (mascaragy[1][2])) + (temp.at<uchar>(fila - 1, col - 1) * (mascaragy[2][0])) + (temp.at<uchar>(fila - 1, col) * (mascaragy[2][1])) + (temp.at<uchar>(fila - 1, col + 1) * (mascaragy[2][2]));
				// gy.Data[fila, col, 0] = SaturateCast((gy.Data[fila, col, 0]) ^ 2);

				if (gy.at<uchar>(fila, col) > 255)
				{
					gy.at<uchar>(fila, col) = 255;
				}
				else if (gy.at<uchar>(fila, col) < 0)

				{
					gy.at<uchar>(fila, col) = 0;
				}

			}
		}

		double sumaCuadro = 0;
		double raiz;

		for (int fila = 1; fila < temp.rows - 1; fila++)
		{
			for (int col = 1; col < temp.cols - 1; col++)
			{

				
				gradiente.at<uchar>(fila, col) = sqrt(pow(gx.at<uchar>(fila, col), 2) + pow(gy.at<uchar>(fila, col), 2));

				if (gradiente.at<uchar>(fila, col) > 255)
				{
					gradiente.at<uchar>(fila, col) = 255;
				}
				else if (gradiente.at<uchar>(fila, col) < 0)

				{
					gradiente.at<uchar>(fila, col) = 0;
				}
				

			}

		}


		aux = gradiente;
		

	}

	void translateImg(Mat& imgIn, Mat& imgOut)
	{
		int i, j;

		for (i = 0; i < imgIn.rows; i++)
			for (j = 0; j < imgIn.cols; j++)
				imgOut.at<double>(i, j) = imgIn.at<double>(i, j) * pow(-1.0, i + j);
	}
	void scaleImg(Mat& imgIn, Mat& imgOut, float scaleFactor)
	{
		int i, j;

		for (i = 0; i < imgIn.rows; i++)
			for (j = 0; j < imgIn.cols; j++)
				imgOut.at<double>(i, j) = (double)scaleFactor * log(1.0 + imgIn.at<double>(i, j));
	}

	void consoleOut(cv::Mat outMat, int rows = 5, int cols = 5)
	{
		rows = ((rows == -1 || rows >= outMat.rows) ? outMat.rows : rows);
		cols = ((cols == -1 || cols >= outMat.cols) ? outMat.cols : cols);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << outMat.at<double>(i, j);
				cout << " ";
			}
			cout << endl;
		}
	}

	double calcMSE(Mat& imgOrig, Mat& imgReconst)
	{
		int valOrig = 0, valReconst = 0;
		double MSE = 0.0;

		for (int i = 0; i < imgOrig.rows; i++)
		{
			for (int j = 0; j < imgOrig.cols; j++)
			{
				valOrig = imgOrig.at<unsigned char>(i, j);
				valReconst = imgReconst.at<unsigned char>(i, j);

				MSE += pow((double)(valOrig - valReconst), 2.0);
			}
		}
		return (MSE / (imgOrig.rows * imgOrig.cols));
	}

	string convertInt(int number) // converts integer to string
	{
		stringstream ss;
		ss << number;
		return ss.str();
	}

	void FiltroFourier(Mat &imagen, Mat& Salida, int filtro, int magnitud) {

		int dftH, dftW;
		Mat imgIn;

		imgIn = imagen;

		dftH = cv::getOptimalDFTSize(imgIn.rows);
		dftW = cv::getOptimalDFTSize(imgIn.cols);

		Mat imgMod;
		Mat imgPrecFFT(dftH, dftW, CV_64FC1, Scalar::all(0));
		imgIn.convertTo(imgMod, CV_64FC1);
		imgPrecFFT = imgMod(cv::Range::all(), cv::Range::all()).clone();

		// translate image
		vector<Mat> imgsTrans;
		imgsTrans.push_back(Mat_<double>(imgIn.size(), CV_64FC1));
		imgsTrans.push_back(Mat_<double>(imgIn.size(), CV_64FC1));
		imgsTrans[1].setTo(Scalar::all(0), Mat());
		translateImg(imgPrecFFT, imgsTrans[0]);

		Mat imgPrecTransFFT(imgIn.size(), CV_64FC2, Scalar::all(0));
		merge(imgsTrans, imgPrecTransFFT);

		// dft
		Mat imgFFT;
		dft(imgPrecTransFFT, imgFFT, DFT_COMPLEX_OUTPUT);
		Mat imgDispFFT;

		// calculate magnitude
		Mat imgMagnitude(imgIn.size(), CV_64FC1);
		vector<Mat> chans;
		split(imgFFT, chans);
		magnitude(chans[0], chans[1], imgMagnitude);

		// scale magnitude image
		Mat imgMagnitudeScaled(imgIn.size(), CV_64FC1);
		scaleImg(imgMagnitude, imgMagnitudeScaled, 10.0);

		// display magnitude image
		Mat imgDisp;
		convertScaleAbs(imgMagnitudeScaled, imgDisp);
		imshow("Espectro", imgDisp);

		
		//Pasabajos 0 - Pasaaltos 1 - magnitud 50
		if (filtro == 0 || filtro == 1) {
			Mat filtro1(chans[0].rows, chans[0].cols, chans[0].type(), Scalar(filtro));
			circle(filtro1, { filtro1.cols / 2, filtro1.rows / 2 }, magnitud, 1 - filtro, -1, 8, 0);
			Mat filtro2(chans[1].rows, chans[1].cols, chans[1].type(), Scalar(filtro));
			circle(filtro2, { filtro2.cols / 2, filtro2.rows / 2 }, magnitud, 1 - filtro, -1, 8, 0);
			chans[0] = chans[0].mul(filtro1);
			chans[1] = chans[1].mul(filtro2);



			Mat filtro0(imgDisp.rows, imgDisp.cols, imgDisp.type(), Scalar(filtro));
			circle(filtro0, { filtro0.cols / 2, filtro0.rows / 2 }, magnitud, 1 - filtro, -1, 8, 0);
			imgDisp = imgDisp.mul(filtro0);
			imshow("PasaBajos", imgDisp);
		}
		
		
	
		


		merge(chans, imgFFT);

		// inverse dft
		split(imgFFT, chans);
		chans[1].zeros(imgIn.size(), CV_64FC1);
		merge(chans, imgFFT);
		Mat invFFT;
		idft(imgFFT, invFFT, DFT_REAL_OUTPUT + DFT_SCALE);


		// translate image back to original location
		split(invFFT, imgsTrans);
		Mat imgAfterTrans(imgIn.size(), CV_64FC1);
		translateImg(imgsTrans[0], imgAfterTrans);
		imgAfterTrans.convertTo(imgDisp, CV_8UC1);

		Salida = imgDisp;
	}

void CInterfazMFCDlg::OnBnClickedRefresh()
{
	UpdateData();
	CString menu;
	GetDlgItemText(Opciones, menu);
	if (menu == _T("Promedio"))
	{
		promedio();
		imshow("Imagen2", aux);
	}
	else
		if (menu == _T("Gaussiano"))
		{
			gaussiano();
			imshow("Imagen2", aux);
		}
		else
			if (menu == _T("Gradiente"))
			{
				gradiente();
				imshow("Imagen2", aux);
			}

		else
			if (menu == _T("Fourier PasaBajos"))
				{
				FiltroFourier(temp, aux, 0, 45);
					imshow("Imagen2", aux);
				}
			else
				if (menu == _T("Fourier PasaAltos"))
				{
					FiltroFourier(temp, aux, 1, 45);
					imshow("Imagen2", aux);
				}
}
