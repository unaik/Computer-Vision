// Assignment5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Assignment5.h"
#include "blepo.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace blepo;


 int xa1[] = {  158,    3,   56,   93,  125,  105,  213,  178,  244,  284,  
                345,  347,  341,  355,  297,  322,  300,  122,  194,  171,  
                149,  148,  135,  114,  225,  199,  200,  143,  138,  171,  
                  7,    9,    9,   31,   77,   33,   78,  131,  111,  273,  
                256,  256,  321,  340,  355,  144 };
 
 int ya1[] = { 107,   77,   88,   96,   77,   61,   42,   29,   75,   56,  
                80,  111,  134,  138,  131,  127,  115,  168,  163,  188, 
               217,  230,  237,  219,  226,  223,  212,  201,  151,  151,  
               114,  100,   87,  157,  153,  125,  127,  130,  130,  132,  
               134,  154,  158,  160,  160,  50 };
 
 int xs2[] = {  189,   19,   74,  112,  142,  120,  229,  194,  258,  304,  
                365,  365,  355,  374,  312,  336,  313,  155,  225,  203,  
                180,  180,  169,  150,  258,  232,  228,  176,  171,  203,  
                 27,   27,   26,   49,   96,   53,   96,  147,  127,  286,  
                272,  273,  338,  356,  374,  158 };

 int ys2[] = {   97,   63,   76,   84,   63,   47,   29,   16,   65,   46,  
                 68,  100,  124,  126,  121,  118,  103,  157,  152,  177,  
                204,  216,  222,  205,  216,  210,  200,  189,  139,  138,  
                102,   89,   74,  145,  139,  111,  113,  118,  116,  119,  
                122,  142,  147,  148,  150,  37 };

 double hx[] = { 30,91,173,286,79,135,206,296,116,166,226,299,
			  142,187,241,302,162,204,251,307,178,217,260,307};

 double hy[] = { 167,185,208,237,130,140,152,167,105,109,116,124,
			  85,87,91,94,69,71,72,74,57,58,59,59};

 
 double hxnew[] = {22.6,2*22.6,3*22.6,4*22.6,22.6,2*22.6,3*22.6,4*22.6,22.6,2*22.6,3*22.6,4*22.6,22.6,2*22.6,3*22.6,4*22.6,22.6,2*22.6,3*22.6,4*22.6,22.6,2*22.6,3*22.6,4*22.6};
 double hynew[] = {215-11.3,215-11.3,215-11.3,215-11.3,215-33.9,215-33.9,215-33.9,215-33.9,215-56.5,215-56.5,215-56.5,215-56.5,215-79.1,215-79.1,215-79.1,215-79.1,215-101.7,215-101.7,215-101.7,215-101.7,215-124.3,215-124.3,215-124.3,215-124.3};
 
  std::vector<Point> im1(46);
  std::vector<Point> im2(46);
  std::vector<CPoint> H1(24);
  std::vector<CPoint> H2(24);

 

  void CreateVect()
  {
	  for(int i=0; i<46; i++)
	  {
		  im1[i].x= xa1[i];
		  im1[i].y= ya1[i];

		  im2[i].x= xs2[i];
		  im2[i].y= ys2[i];
	  }
	  	  	    
  }

  void NewVect()
  {
	  for(int i=0; i<24;i++)
	  {
		  H1[i].x = hx[i];
		  H1[i].y = hy[i];

		  H2[i].x =  hxnew[i];
		  H2[i].y =  hynew[i];
	  }
  }

  MatDbl MatMult(MatDbl mat1, MatDbl mat2)
  {
	  MatDbl output(3,3);
	  int sum;
	  for(int i=0; i<3; i++)
		  for(int j=0; j< 3;j++)
		  {
			  output(j,i)=0;
			  for(int k=0; k<3; k++)
			  {
				output(j,i)+=mat1(k,i)*mat2(j,k);
			  }
		  }
	 
	  return output;

  }

  void TransMat(std::vector<Point>& im1, std::vector<Point>& im2, MatDbl& T, MatDbl& Tprime)
  {
	  T.Reset(3,3); Tprime.Reset(3,3);
	  int x0=0,y0=0;
	  int x0prime=0,y0prime=0;
	  int davg=0,davgprime=0;
	  int n = im1.size();

	  for(int i=0; i < n;i++)
	  {
		  x0 += im1[i].x;
		  y0 += im1[i].y;

		  x0prime += im2[i].x;
		  y0prime += im2[i].y;
	  }

	  x0=(x0/n);
	  y0=(y0/n);
	  x0prime=(x0prime/n);
	  y0prime=(y0prime/n);
	  
	  for(int i=0; i<n ; i++)
	  {
		  double x1 = (im1[i].x - x0);
		  double y1 = (im1[i].y - y0);
		  double x1p = (im2[i].x - x0prime);
		  double y1p = (im2[i].x - y0prime);
		  double p1,p2,p1p,p2p;

		  p1 = pow(x1,2);
		  p2 = pow(y1,2);
		  p1p = pow(x1p,2);
		  p2p = pow(y1p,2);

		  davg += sqrt(p1+p2);
		  davgprime += sqrt(p1p+p2p);

	  }
	  davg = davg/n;
	  davgprime = davgprime/n;
	  double s,sprime,a=2;
	  a=sqrt(a);
	  s=(a/davg);
	  sprime=(a/davgprime);
	 

	  T(0,0)=s;
	  T(0,1)=0;
	  T(0,2)=0;
	  T(1,0)=0;
	  T(1,1)=s;
	  T(1,2)=0;
	  T(2,0)= -(s*x0);
	  T(2,1)= -(s*y0);
	  T(2,2)= 1;

	  Tprime(0,0)=sprime;
	  Tprime(0,1)=0;
	  Tprime(0,2)=0;
	  Tprime(1,0)=0;
	  Tprime(1,1)=sprime;
	  Tprime(1,2)=0;
	  Tprime(2,0)= -(sprime*x0prime);
	  Tprime(2,1)= -(sprime*y0prime);
	  Tprime(2,2)= 1;
  }

  struct HCoords
  {
	  double x,y,z;
  };

  void GetC(std::vector<Point>& im1,std::vector<Point>& im2, MatDbl* xvalm,MatDbl* xvalmp)
  {
	  for(int i=0; i<46;i++)
	  {
		  xvalm[i](0,0)=im1[i].x;
		  xvalm[i](0,1)=im1[i].y;
		  xvalm[i](0,2)=1;

		  xvalmp[i](0,0)=im2[i].x;
		  xvalmp[i](0,1)=im2[i].y;
		  xvalmp[i](0,2)=1;
	  
		  
	  }

  }

  void NormalizeCoords(MatDbl* xvalm,MatDbl* xvalmp,MatDbl* xcap,MatDbl* xcapprime,MatDbl& T,MatDbl& Tprime)
  {
	  for(int i=0; i<46; i++)
	  {
		xcap[i](0,0)=(T(0,0)*xvalm[i](0,0) + T(1,0)*xvalm[i](0,1) + T(2,0)*xvalm[i](0,2));  
		xcap[i](0,1)=(T(0,1)*xvalm[i](0,0) + T(1,1)*xvalm[i](0,1) + T(2,1)*xvalm[i](0,2));  
		xcap[i](0,2)=(T(0,2)*xvalm[i](0,0) + T(1,2)*xvalm[i](0,1) + T(2,2)*xvalm[i](0,2));  

		xcapprime[i](0,0)=(Tprime(0,0)*xvalmp[i](0,0) + Tprime(1,0)*xvalmp[i](0,1) + Tprime(2,0)*xvalmp[i](0,2));  
		xcapprime[i](0,1)=(Tprime(0,1)*xvalmp[i](0,0) + Tprime(1,1)*xvalmp[i](0,1) + Tprime(2,1)*xvalmp[i](0,2));  
		xcapprime[i](0,2)=(Tprime(0,2)*xvalmp[i](0,0) + Tprime(1,2)*xvalmp[i](0,1) + Tprime(2,2)*xvalmp[i](0,2));  
	  }
  }

  MatDbl FundamentalMat(MatDbl* xcap,MatDbl* xcapprime)
  {
	  MatDbl A,U,sigma,V;
	  MatDbl fun(3,3);
	  A.Reset(9,46);
	  for(int i=0 ;i<46;i++)
	  {
		  A(0,i) = xcap[i](0,0)*xcapprime[i](0,0);
		  A(1,i) = xcap[i](0,0)*xcapprime[i](0,1);
		  A(2,i) = xcap[i](0,0);
		  A(3,i) = xcap[i](0,1)*xcapprime[i](0,0);
		  A(4,i) = xcap[i](0,1)*xcapprime[i](0,1);
		  A(5,i) = xcap[i](0,1); 
		  A(6,i) = xcapprime[i](0,0);
		  A(7,i) = xcapprime[i](0,1);
		  A(8,i) = 1;
	  }
	  Svd(A,&U,&sigma,&V);
	  MatDbl f(3,3);
	  f(0,0)=V(8,0); f(1,0)=V(8,1); f(2,0)=V(8,2); f(0,1)=V(8,3); f(1,1)=V(8,4); f(2,1)=V(8,5); f(0,2)=V(8,6); f(1,2)=V(8,7); f(2,2)=V(8,0);
	  Svd(f,&U,&sigma,&V);
	  MatDbl Sigma1(3,3);
	  Sigma1(0,0)=sigma(0,0);Sigma1(1,0)=0;Sigma1(2,0)=0;Sigma1(0,1)=0;Sigma1(1,1)=sigma(0,1);Sigma1(2,1)=0;Sigma1(0,2)=0;Sigma1(1,2)=0;Sigma1(2,2)=0;
	  V=Transpose(V);
	  fun= MatMult(U,Sigma1);
	  fun= MatMult(fun,V);
	  return fun;
  }

  

  MatDbl OrigCoords(MatDbl fcap,MatDbl T, MatDbl Tprime)
  {
	  MatDbl Tprime1(3,3),T1(3,3);
	  MatDbl realfmat,temp;
	  T1=Transpose(T); 
	  Tprime1=(Tprime);
	  realfmat=MatMult(T1,fcap);
	  realfmat=MatMult(realfmat,Tprime1);
	  return realfmat; 
	  
  }

  Point lined(ImgBgr& img,Point pt,double a,double b, double c)
  {
	  
	  double m = -(a/b);
	  double c1= -(c/b);

	  double x=img.Width()-1;
      double y=m*x+c1;
	  			 
	  double x1=0;
	  double y1=m*x1 + c1;
	  
	  Point pt1,pt2;
	  pt1.x=x;pt1.y=y;
	  pt2.x=x1;pt2.y=y1;
	  DrawLine(pt2,pt1,&img,Bgr(0,255,255),1);
	  return pt1;
  }

  Point lined1(ImgBgr& img,Point pt,double a,double b, double c)
  {
	  
	  double m = -(a/b);
	  double c1= -(c/b);

	  double x=img.Width()-1;
      double y=m*x+c1;
	  			 
	  double x1=0;
	  double y1=m*x1 + c1;
	  
	  Point pt1,pt2;
	  pt1.x=x;pt1.y=y;
	  pt2.x=x1;pt2.y=y1;
	  DrawLine(pt2,pt1,&img,Bgr(0,0,255),1);
	  return pt1;
  }

  void CalcSlope(Point pt1,MatDbl realfmat,double& a, double& b,double& c)
  {
	  double x,y;
	  x=pt1.x;
	  y=pt1.y;

	  a=(realfmat(0,0)*x + realfmat(1,0)*y + realfmat(2,0));
	  b=(realfmat(0,1)*x + realfmat(1,1)*y + realfmat(2,1));
	  c=(realfmat(0,2)*x + realfmat(1,2)*y + realfmat(2,2));
  }

  void CalcSlope1(Point pt1,MatDbl realfmat,double& a,double& b,double& c)
  {
	  double x,y;
	  x=pt1.x;
	  y=pt1.y;

	  a= (realfmat(0,0)*x +realfmat(0,1)*y + realfmat(0,2));
	  b= (realfmat(1,0)*x +realfmat(1,1)*y + realfmat(1,2));
	  c= (realfmat(2,0)*x +realfmat(2,1)*y + realfmat(2,2));
  }

  


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
		
			char str1[50],str2[50],str3[50],str4[50],str5[50],str6[50];
			cout<<"enter the path for checkered image"<<endl;
			gets (str1);
			cout<< "enter the path for the first statue image"<<endl;
			gets(str2);
			cout<< "enter the path for the second statue image"<<endl;
			gets(str3);
			ImgGray check;
			ImgBgr chec,chec1(93,215);
			ImgGray img1,img2;
			ImgBgr i,j;
			Load(str2,&img1);
			Load(str3,&img2);
			Load(str3,&i);
			Load(str2,&j);
			
			Load(str1,&check);
			Load(str1,&chec);
			NewVect();
			MatDbl H(3,3),H3;
			Set (&H,0);
			Figure origimg;
			origimg.Draw(chec);
			Point click1,click2;
			click1=origimg.GrabMouseClick();
			click2=origimg.GrabMouseClick();
			DrawLine(click1,click2,&chec,Bgr(0,0,255),2);
			HomographyFit(H2,H1,&H);
			ImgFloat fx,fy;
			InitWarpHomography(H,chec1.Width(),chec1.Height(),&fx,&fy);
			Warp(chec,fx,fy,&chec1);
			int count=0;
			for(int x=0; x<chec1.Width();x++)
				for(int y=0; y<chec1.Height();y++)
				{
					if(chec1(x,y).r>200 && chec1(x,y).g <50 && chec1(x,y).b<50)
					{count++;}

				}
			
			cout<<count;
			CString st;
			
			st="length in inches = %d ";
			st.Format(st,count);
			
			
			Figure asd;
			asd.Draw(chec1);
			asd.PlaceToTheRightOf(origimg);
			AfxMessageBox(st,MB_OK|MB_ICONEXCLAMATION );

			
			CreateVect();
			MatDbl out;
			MatDbl T,Tprime;
			MatDbl fcap,realfmat;
			TransMat(im1,im2,T,Tprime);
			
			
			MatDbl* xvalm;MatDbl* xvalmp;MatDbl* xcap;MatDbl* xcapprime;
			xvalm = new MatDbl[46];
			xvalmp = new MatDbl[46];
			xcap = new MatDbl[46];
			xcapprime = new MatDbl[46];
			for(int i=0; i<46; i++)
			{xvalm[i].Reset(1,3);xvalmp[i].Reset(1,3);xcap[i].Reset(1,3);xcapprime[i].Reset(1,3);}
			GetC(im1,im2,xvalm,xvalmp);
			NormalizeCoords(xvalm,xvalmp,xcap,xcapprime,T,Tprime);
			fcap=FundamentalMat(xcap,xcapprime);
			realfmat=OrigCoords(fcap,T,Tprime);
						
			Figure disp;
			Figure disp2,disp3;
			disp.Draw(img1);
			int n=0;
			Point ptg,pt1,pt2;
			for(int pq=0; pq<6;pq++)
			{
				if(n<6)
				{
			        double a,b,c,a1,b1,c1;
					ptg=disp.GrabMouseClick();
					CalcSlope1(ptg,realfmat,a,b,c);
					pt1=lined(i,ptg,a,b,c);
					CalcSlope(pt1,realfmat,a1,b1,c1);
					pt2=lined1(j,pt1,a1,b1,c1);
					disp2.Draw(i);
					disp2.PlaceToTheRightOf(disp);
					disp3.Draw(j);
					disp3.PlaceToTheRightOf(disp2);
					n++;
				}
			}
			
			EventLoop();
			

			
						
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
