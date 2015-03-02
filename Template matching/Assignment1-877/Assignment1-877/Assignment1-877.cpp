// Assignment1-877.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Assignment1-877.h"
#include "blepo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace blepo;

ImgBgr templatemat(ImgGray& orignalimg, ImgGray& templateimg, ImgBgr& temp, ImgInt& probmap,int thresh,Bgr col)
{

	for(int y=0; y<orignalimg.Height()-templateimg.Height(); y++)
				for(int x=0; x<orignalimg.Width()-templateimg.Width(); x++)
				{
					int diff=0;
					
					for(int j=0; j<templateimg.Height(); j++)
						for(int i=0; i<templateimg.Width();i++)
						{
							diff += abs(orignalimg(x+i,y+j)-templateimg(i,j));
						}

				  probmap(x,y)=diff;
				  if(probmap(x,y)<thresh)
				  {
					  Rect rec(x,y,x+templateimg.Width(),y+templateimg.Height());
					  DrawRect(rec,&temp,col);
				  }
				}
	return temp;

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
			ImgGray orignalimg,templateimg,template1img,trainingimg;
			ImgBgr temp;
			char str[50],str1[50];
			Bgr col,col1;
			col.b=0; col.g=0; col.r=255;
			col1.b=255; col1.g=0; col1.r=0;
						
			Rect templ(395,295,399,301),templ1(124,209,154,217);
			
			cout<<"Enter path for training image:"<<endl;
			gets(str);
			cout<<"Enter path for testing image:"<<endl;
			gets(str1);
			


			Load(str1,&orignalimg);
			Load(str,&trainingimg);
			Convert(orignalimg,&temp);
			Extract(trainingimg,templ,&templateimg);
			Extract(trainingimg,templ1,&template1img);
			
			int width=orignalimg.Width();
			int height=orignalimg.Height();
			ImgInt probmap(width,height),probmap1(width,height);
			ImgInt::Iterator iter;
			for(iter=probmap.Begin();iter!=probmap.End();iter++)
			{*iter=0;}
			for(iter=probmap1.Begin();iter!=probmap1.End();iter++)
			{*iter=0;}
			
			
			temp=templatemat(orignalimg,templateimg,temp,probmap,900,col);
			temp=templatemat(orignalimg,template1img,temp,probmap1,9500,col1);
           

			Figure trainingimage,testingimage,tempimage,temp1image,outputimage;
			trainingimage.Draw(trainingimg);
			trainingimage.SetTitle("Training image");
			testingimage.Draw(orignalimg);
			testingimage.SetTitle("Test image");
			tempimage.Draw(templateimg);
			tempimage.SetTitle("Alphabet template");
			temp1image.Draw(template1img);
			temp1image.SetTitle("Word template");
			outputimage.Draw(temp);
			outputimage.SetTitle("Template matching output");
           	
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
