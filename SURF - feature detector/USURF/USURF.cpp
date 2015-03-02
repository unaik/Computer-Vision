// USURF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "USURF.h"
#include "blepo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace blepo;

class scoreandsign
{
public:
	ImgInt score;
	ImgInt sign;
};

class features
{
public:
	ImgInt feat;
};

class point 
{
public:
	point(float x, float y, float val): xx(x), yy(y), vv(val) {}
     
	
	int xx,yy;
	float vv;

	bool operator < (const point& other)
	{return vv> other.vv;}
};







void Score(ImgInt& integral, float width,float height, ImgInt& out,ImgInt& sign )
{
	float dxx=0,dyy=0,dxy=0,det;
	float xxx1,xxx2,xxy1,yyx1,yyy1,yyy2,x1,x2,y1,y2;
	xxx1=floor(width/2);
	xxx2=width+xxx1;
	xxy1=floor(height/2);
	yyx1=floor(height/2);
	yyy1=floor(width/2);
	yyy2=yyy1+width;
	x1=y1=width-(width-1);
	x2=y2=width;

	for(int y=0; y<integral.Height(); y++)
			for(int x=0; x<integral.Width();x++)
			{
				
				if(x-xxx2>0 && x+xxx2<integral.Width() && y-xxy1 >0 && y+xxy1<integral.Height())
				{
					dxx=(1*(integral(x-xxx2,y-xxy1)+integral(x-xxx1,y+xxy1)-integral(x-xxx2,y+xxy1)-integral(x-xxx1,y-xxy1))-2*(integral(x-xxx1,y-xxy1)+integral(x+xxx1,y+xxy1)-integral(x-xxx1,y+xxy1)-integral(x+xxx1,y-xxy1))+1*(integral(x+xxx1,y-xxy1)+integral(x+xxx2,y+xxy1)-integral(x+xxx2,y-xxy1)-integral(x+xxx1,y+xxy1)));
				}

				if(x-yyx1>0 && x+yyx1<integral.Width() && y-yyy2>0 && y+yyy2<integral.Height())
				{
					dyy=(1*(integral(x-yyx1,y-yyy2)+integral(x+yyx1,y-yyy1)-integral(x-yyx1,y-yyy1)-integral(x+yyx1,y-yyy2))-2*(integral(x-yyx1,y-yyy1)+integral(x+yyx1,y+yyy1)-integral(x-yyx1,y+yyy1)-integral(x+yyx1,y-yyy1))+1*(integral(x-yyx1,y+yyy1)+integral(x+yyx1,y+yyy2)-integral(x-yyx1,y+yyy2)-integral(x+yyx1,y+yyy1)));
				}

				if(x-x2>0 && x+x2<integral.Width() && y-y2>0 && y+y2<integral.Height())
				{
					dxy=(1*(integral(x-x2,y-y2)+integral(x-x1,y-y1)-integral(x-x2,y-y1)-integral(x-x1,y-y2))-1*(integral(x+x1,y-y2)+integral(x+x2,y-y1)-integral(x+x1,y-y1)-integral(x+x2,y-y2))-1*(integral(x-x2,y+y1)+integral(x-x1,y+y2)-integral(x-x2,y+y2)-integral(x-x1,y+y1))+1*(integral(x+x1,y+y1)+integral(x+x2,y+y2)-integral(x+x1,y+y2)-integral(x+x2,y+y1)));
				}

				det=dxx*dyy-pow((0.9*dxy),2);
				
				out(x,y)=det;
				sign(x,y)=dxx+dyy;
				
				
				
			}
}

scoreandsign * SecndDerivativeFilter( ImgInt& integral)
{
	scoreandsign * approx = new scoreandsign[4];
	float dxx=0,dyy=0,dxy=0,det;
	float width,height;
	ImgInt conv(integral.Width(),integral.Height());
	
	approx[0].score=conv;
	approx[1].score=conv;
	approx[2].score=conv;
	approx[3].score=conv;
	approx[0].sign=conv;
	approx[1].sign=conv;
	approx[2].sign=conv;
	approx[3].sign=conv;
	
	

	float xxx1,xxx2,xxy1,yyx1,yyy1,yyy2,x1,x2,y1,y2;	

		width=3;
		height=width*2-1;
		
		xxx1=floor(width/2);
		xxx2=width+xxx1;
		xxy1=floor(height/2);
		yyx1=floor(height/2);
		yyy1=floor(width/2);
		yyy2=yyy1+width;
		x1=y1=width-(width-1);
		x2=y2=width;

		
		Score(integral,3,5,approx[0].score,approx[0].sign);
		Score(integral,5,9,approx[1].score,approx[1].sign);
		Score(integral,7,13,approx[2].score,approx[2].sign);
		Score(integral,9,17,approx[3].score,approx[3].sign);
		
		return approx;
}

void IntegImage(ImgGray& gray,ImgInt& integral)
{
	
	for(int y=0; y<integral.Height();y++)
		for(int x=0; x<integral.Width();x++)
		{
			if(x-1<0 && y-1>0)
			{integral(x,y)=gray(x,y)-0+0+integral(x,y-1);}
			
			else if(y-1<0 && x-1>0)
			{integral(x,y)=gray(x,y)-0+integral(x-1,y)+0;}

			
			else if(y-1<0 && x-1<0)
			{integral(x,y)=gray(x,y);}

			else if (x-1>0 && y-1>0)
			{integral(x,y)=gray(x,y)-integral(x-1,y-1)+integral(x-1,y)+integral(x,y-1);}
		}
}


 features* NonMaxSup(scoreandsign* get)
 {
	 features * feature;
	 feature= new features[2];
	 ImgInt conv1(get[0].score.Width(),get[0].score.Height());
	 feature[0].feat=conv1;
	 feature[1].feat=conv1;
	 
			
			int i=0;


	 for(int y=1; y<get[1].score.Height()-1;y++)
		 for(int x=1; x<get[1].score.Width()-1; x++)
		 {
			
			 
			 {
				 
			 if(get[1].score(x,y)>=(get[1].score(x+1,y-1) && get[1].score(x+1,y) && get[1].score(x+1,y+1) && get[1].score(x-1,y) && get[1].score(x-1,y+1) && get[1].score(x-1,y-1) && get[1].score(x,y+1) && get[1].score(x,y-1)))
            
			 {
				 if((get[1].score(x,y))> get[0].score(x,y) && get[0].score(x+1,y-1) && get[0].score(x+1,y) && get[0].score(x+1,y+1) && get[0].score(x-1,y) && get[0].score(x-1,y+1) && get[0].score(x-1,y-1) && get[0].score(x,y+1) && get[0].score(x,y-1))
				 {
					 if( (get[1].score(x,y))>  get[2].score(x,y) && get[2].score(x+1,y-1) && get[2].score(x+1,y) && get[2].score(x+1,y+1) && get[2].score(x-1,y) && get[2].score(x-1,y+1) && get[2].score(x-1,y-1) && get[2].score(x,y+1) && get[2].score(x,y-1) )
				            { 
								
								feature[0].feat(x,y)=get[1].score(x,y);i++;
								
					        }
				 }
			 }
			 
			 }
		 }
		

		 for(int y=1; y<get[2].score.Height()-1;y++)
		     for(int x=1; x<get[2].score.Width()-1; x++)
		 {
			
			
			 {
				 
			 if(get[2].score(x,y)>=(get[2].score(x+1,y-1) && get[2].score(x+1,y) && get[2].score(x+1,y+1) && get[2].score(x-1,y) && get[2].score(x-1,y+1) && get[2].score(x-1,y-1) && get[2].score(x,y+1) && get[2].score(x,y-1)))
            
			 {
				 if((get[2].score(x,y))> get[1].score(x,y) && get[1].score(x+1,y-1) && get[1].score(x+1,y) && get[1].score(x+1,y+1) && get[1].score(x-1,y) && get[1].score(x-1,y+1) && get[1].score(x-1,y-1) && get[1].score(x,y+1) && get[1].score(x,y-1))
				 {
					 if( (get[2].score(x,y))>  get[3].score(x,y) && get[3].score(x+1,y-1) && get[3].score(x+1,y) && get[3].score(x+1,y+1) && get[3].score(x-1,y) && get[3].score(x-1,y+1) && get[3].score(x-1,y-1) && get[3].score(x,y+1) && get[3].score(x,y-1) )
				            { 
								
								feature[1].feat(x,y)=get[2].score(x,y);i++;
								
					        }
				 }
			 }
			 
			 }
		 }
		
			 int io=0;
		 std::vector<point> whi;
		 std::vector<point> jackandcoke;
		 for(int y=1; y<feature[1].feat.Height()-1;y++)
		    for(int x=1; x<feature[1].feat.Width()-1; x++)
			{
				float a,b;
				{a=feature[0].feat(x,y);}
				{b=feature[1].feat(x,y);io++;}
				whi.push_back(point(x,y,a));
				jackandcoke.push_back(point(x,y,b));

			}
			
		std::sort(whi.begin(),whi.end());
		std::sort(jackandcoke.begin(),jackandcoke.end());


		std::vector<point> featur;
		std::vector<point> featur1;
		ImgGray scapegoat(feature[0].feat.Width(),feature[0].feat.Width()),scapegoat1(feature[1].feat.Width(),feature[1].feat.Width());
		Set(&scapegoat,0);Set(&scapegoat1,0);
		
 
            for (int i=0 ; i<whi.size() ; i++)
             {
               
               
               if (featur.size() == 100)  break;
		       if (scapegoat(( whi[i].xx ), ( whi[i].yy )) != 1)  
                 {
                   featur.push_back(whi[i]);
                   int left   =max( whi[i].xx - 10, 0);
                   int top    =max( whi[i].yy - 10, 0);
                   int right  = min( whi[i].xx + 10, feature[0].feat.Width());
                   int bottom =  min( whi[i].yy+ 10, feature[0].feat.Width());
                   Set(&scapegoat, Rect(left, top, right, bottom), 1);
                 }
             }


			for (int i=0 ; i<jackandcoke.size() ; i++)
             {
               
               
               if (featur1.size() == 100)  break;
		       if (scapegoat1(( jackandcoke[i].xx ), ( jackandcoke[i].yy )) != 1)  
                 {
                   featur1.push_back(jackandcoke[i]);
                   int left   =max( jackandcoke[i].xx - 10, 0);
                   int top    =max( jackandcoke[i].yy - 10, 0);
                   int right  = min( jackandcoke[i].xx +10, feature[1].feat.Width());
                   int bottom =  min( jackandcoke[i].yy+ 10, feature[1].feat.Width());
                   Set(&scapegoat1, Rect(left, top, right, bottom), 1);
                 }
             }

			Set(&feature[0].feat,0);
			Set(&feature[1].feat,0);
			

			for(int p=0; p<featur.size();p++)
			{
				feature[0].feat(featur[p].xx,featur[p].yy)=featur[p].vv;

			}

		
			for(int p=0; p<featur1.size();p++)
			{
				feature[1].feat(featur1[p].xx,featur1[p].yy)=featur1[p].vv;

			}
		
		 return feature;
 }

 void Draw(ImgBgr& orig, features* feature,scoreandsign* get)
 {
	 Bgr col,col1,col2;
	 col.b=0;col.g=255;col.r=0;
	 col1.r=255;col1.b=0;col1.g=0;
	 col2.b=255;col2.g=0;col2.r=0;
	 Point pt;
	 for(int y=0; y< feature[0].feat.Height();y++)
		 for(int x=0; x<feature[0].feat.Width();x++)
		 {
			 if(feature[0].feat(x,y)>0)
			 {
				 orig(x,y)=col;
				 pt.x=x;
				 pt.y=y;
				 if(get[3].sign(x,y)<0)
					 {DrawCircle(pt,4,&orig,col1);}
				 else
					{DrawCircle(pt,4,&orig,col2);}
			 }
			 

			 if(feature[1].feat(x,y)>0)
			 {
				 orig(x,y)=col;
				 pt.x=x;
				 pt.y=y;
				 if(get[1].sign(x,y)<8000)
					 {DrawCircle(pt,6,&orig,col1);}
				 else 
					{DrawCircle(pt,6,&orig,col2);}

			 
			 }
		 }

		 Figure result;
		 result.Draw(orig);
		 result.SetTitle("Result");
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
			ImgBgr orig;
			ImgGray gray;
			ImgInt integral,integral1;
			
			CString  image;
			CFileDialog fileDlg(TRUE, NULL, NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,NULL);
			if(fileDlg.DoModal() == IDOK)
			{
				 image = fileDlg.GetPathName();
			}
			
			Load(image,&orig);
			int width=orig.Width();
			int height=orig.Height();
			Convert(orig,&gray);
			integral.Reset(width,height);
			
			ImgInt::Iterator iter;
			for(iter=integral.Begin();iter!=integral.End();iter++)
			{*iter=0;}

			IntegImage(gray,integral);
			
			scoreandsign* get;
			get=new scoreandsign[4];
			
			get=SecndDerivativeFilter(integral);
			
			features * feature;
			feature= new features[2];
			
			feature=NonMaxSup(get);
			Draw(orig,feature,get);
						
			cout<<"done";
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
