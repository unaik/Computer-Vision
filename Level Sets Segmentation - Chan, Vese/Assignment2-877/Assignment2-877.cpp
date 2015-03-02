// Assignment2-877.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Assignment2-877.h"
#include "blepo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace blepo;

ImgFloat Magnitude(ImgFloat& phifx, ImgFloat& phify)
{
	ImgFloat temp(phifx.Width(),phifx.Height());
	for(int y=0; y < temp.Height(); y++)
		for(int x=0; x < temp.Width(); x++)
		{
			float val1 = phifx(x,y);
			float val2 = phify(x,y);
			float power1 = pow (val1,2);
			float power2 = pow (val2,2);
			temp(x,y)=sqrt(power1+power2);
		}

		return temp;

}

void Magdiv(ImgFloat& phifx,ImgFloat& phify, ImgFloat& magnitude, ImgFloat& out1, ImgFloat& out2)
{
	for(int y=0; y<phifx.Height(); y++)
		for(int x=0; x<phifx.Width(); x++)
		{
			float temp1,temp2,phix,phiy,mag;
			phix=phifx(x,y);
			phiy=phify(x,y);
			mag=magnitude(x,y);
			if(mag>=0.1f)
			{
			temp1=(phix/mag);
			temp2=(phiy/mag);
			
			
			out1(x,y)=temp1;
			out2(x,y)=temp2;
			}

			else
			{out1(x,y)=phix; out2(x,y)=phiy;}
		}

}


void Calccico(ImgFloat& phi,ImgGray& img,float& ci,float& co)
	{
		float count=0,count1=0;
		ci=0;co=0;
		float tempval,tempval1;
		for(int y=0; y<img.Height(); y++)
			for(int x=0; x<img.Width(); x++)
			{
				if(phi(x,y)>=0.0f)
				{
				  tempval=img(x,y);
				  ci+=tempval;
				  count++;
				 }
				else
				{
					tempval1=img(x,y);
					co+=tempval1;
					count1++;
				}
			}
			
			ci=ci/count;
			co=co/count1;
			

    }


void DrawGamma(ImgFloat& phif,ImgGray& cont, ImgBinary& contour,const ImgGray& img)
{
	
	ImgGray::Iterator manip;
	Bgr col1;
	col1.r=255,col1.g=0;col1.b=255;
	ImgBgr result;
	Convert(img,&result);
	for(manip=cont.Begin(); manip!=cont.End();manip++)
	{*manip=0;}
	ImgBinary::Iterator manip1;
	for(manip1=contour.Begin(); manip1!=contour.End();manip1++)
	{*manip1=0;}

	for(int y=1; y<phif.Height(); y++)
		for(int x=1; x<phif.Width(); x++)
		{
			if (phif(x,y)*phif(x-1,y)<=0)
			{cont(x,y)=255;}
			if (phif(x,y)*phif(x,y-1)<=0)
			{cont(x,y)=255;}
			
		}
	Convert(cont,&contour);
	

}

void Divergence(ImgFloat& phifx,ImgFloat& phify,ImgFloat& output)
{
	ImgFloat temp1,temp2,temp3;
	ImgFloat::Iterator xx;
	for(xx=temp1.Begin();xx!=temp1.End();xx++)
	{*xx=0;}
	for(xx=temp2.Begin();xx!=temp2.End();xx++)
	{*xx=0;}
	for(xx=temp3.Begin();xx!=temp3.End();xx++)
	{*xx=0;}
	Gradient(phifx,1,&temp1,&temp2);
	Gradient(phify,1,&temp2,&temp3);
	Add(temp1,temp3,&output);
}

void CalcDeltaPhi(ImgGray& img,ImgFloat& magnitude,float ci,float co,ImgFloat& divergenceimg,ImgFloat& deltaphi)
{
	float v=1,lambdai=1,lambdao=1,mu=0.01;
	deltaphi.Reset(img.Width(),img.Height());
	for(int y=0; y<img.Height(); y++)
		for(int x=0; x<img.Width(); x++)
		{
			float mag,im,div;
			float pow1,pow2;
			mag=magnitude(x,y);
			im=img(x,y);
			div=divergenceimg(x,y);
			pow1=pow((im-ci),2);
			pow2=pow((im-co),2);
			deltaphi(x,y)=-(mag)*(v+(lambdai*pow1)-(lambdao*pow2)-(mu*div));
		}

}

void ReInitialize(ImgFloat& phi,ImgBinary& contour)
{
	ImgInt chamfer;
	ImgGray contour1;
	Convert(contour,&contour1);
	Chamfer(contour1,&chamfer);

	for(int y=0; y<phi.Height();y++)
		for(int x=0; x<phi.Width();x++)
		{
			if(phi(x,y)>0.0f){phi(x,y)=chamfer(x,y);}
			else{phi(x,y)=-chamfer(x,y);}
		}


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
			ImgGray img;
			char str[50];
			cout<<"enter the path to the image : ";
			gets(str);
			Load(str,&img);
			int width,height;
			width=img.Width();
			height=img.Height();
			ImgBinary contour(width,height);
			ImgGray cont(width,height);
			ImgInt phi(width,height);
			ImgBgr result,result1;
			Bgr col;
			col.r=255;col.b=0;col.g=0;
			ImgFloat phif(width,height),phifx(width,height),phify(width,height),magnitude,deltaphi(width,height);
			ImgInt::Iterator iter;
			for(iter=phi.Begin();iter!=phi.End();iter++)
				{*iter=-1;}
			for(int y=5; y<height-5; y++ )
				for(int x=5; x<width-5; x++)
				{
					phi(x,y)=1;
				}
			Convert(phi,&phif);
			
			Convert(img,&result);
			Convert(img,&result1);
			DrawGamma(phif,cont,contour,img);
			Set(&result,contour,col);
			Figure fig6;
			fig6.Draw(result);
			
			float ci;
			float co;
			Calccico(phif,img,ci,co);
			
			
			ImgFloat out1(width,height),out2(width,height),ggx,ggy,tmp,output(width,height);
			
			for(int p=0; p<30;p++)
			{
				Gradient(phif,1,&phifx,&phify);
			    magnitude=Magnitude(phifx,phify);
				Magdiv(phifx,phify,magnitude,out1,out2);
				Divergence(phifx,phify,output);
				CalcDeltaPhi(img,magnitude,ci,co,output,deltaphi);
			    Add(phif,deltaphi,&phif);
				ImgBinary::Iterator man;
			    for(man=contour.Begin();man!=contour.End();man++)
				{*man=0;}
			  	DrawGamma(phif,cont,contour,img);
				result=result1;
				Set(&result,contour,col);
				fig6.Draw(result);
				ReInitialize(phif,contour);
				Calccico(phif,img,ci,co);			
			}
			
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
