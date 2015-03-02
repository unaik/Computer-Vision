// mosaicking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mosaicking.h"
#include "blepo.h"
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace blepo;

int six8[] = {201,151,218,150,202,158,217,157,205,160,215,160,205,181,214,181,204,184,215,183,231,148,249,147,232,155,248,154,236,158,246,158,235,179,246,179,235,181,246,181,365,110,377,109,369,113,373,113,369,120,373,120,369,123,373,123,369,129,374,129};
int eight6[]= {50,239,65,238,50,246,65,246,53,249,63,249,52,269,62,269,51,272,61,272,81,237,98,236,82,244,97,243,85,246,95,246,83,267,94,267,82,270,93,270,213,202,225,201,217,205,221,205,217,212,221,212,217,215,221,215,217,221,221,221};
int zero6[]= {118,7,128,7,118,28,128,28,118,52,128,52,150,4,160,3,150,25,160,25,150,50,160,49,117,93,127,92,117,114,127,114,149,90,159,90,149,111,159,110,13,6,22,6,13,28,22,27,13,52,22,52,73,41,282,50,242,94,273,14};
int six0[]= {205,160,215,160,205,181,215,181,205,205,214,204,236,158,246,157,235,179,245,179,236,203,245,202,203,245,212,243,203,266,212,266,234,243,245,242,234,264,244,264,105,161,114,160,105,181,114,181,104,205,113,204,161,193,369,203,328,249,358,168};
int one6[] ={125,129,114,108,125,106,114,84,160,132,158,82,147,82,140,133,157,105,189,118,107,165,126,164,112,193,140,162,158,162,156,190,109,74,23,134,19,106,10,84,20,82,16,169,15,192,8,106,68,55,42,60,45,48,135,51,219,30,212,43,241,23,210,35,7,13,145,106,226,50,280,72,247,50,262,54,258,62,275,33,288,32,276,56,289,57};
int six1[] ={214,204,204,184,214,182,204,160,248,207,246,158,236,159,229,208,245,180,279,190,197,240,216,239,202,268,229,239,247,237,245,266,199,150,115,210,113,182,105,162,115,159,109,245,109,267,103,183,160,135,136,136,139,125,224,127,308,108,300,121,330,101,229,111,104,95,235,183,355,126,370,151,336,128,350,131,347,140,365,109,377,109,365,134,378,133};
int six7[]= {160,134,309,103,336,127,330,102,309,38,353,68,355,126,369,151,201,151,250,147, 201,267,245,265,326,157,345,175,328,249,343,257,248,54,296,103,160,193,368,204};
int seven6[]= {18,127,170,98,195,122,189,97,170,34,213,66,215,123,228,147,60,145,110,142, 58,262,102,259,185,153,204,171,186,243,200,252,110,48,155,99,17,187,226,200};
int four6[] = {253,55,360,56,338,125,249,196,294,69,340,161,304,164,338,190,254,55,254,153,319,8,378,56,227,57,232,92,308,188,357,38,304,45,315,44,326,17,305,132};
int six4[] = {31,131,134,139,112,204,20,274,70,147,112,240,77,242,109,267,31,131,18,230,98,89,151,137,3,131,7,167,80,265,132,120,82,123,92,123,104,97,79,209};
int five4[]= {109,157,104,210,103,185,137,265,157,283,182,263,180,282,236,282,275,282,276,220,237,223,239,200,276,195,239,141,278,136,298,105,262,81,108,80,129,123,204,112,158,86,180,82,156,123,180,119,136,148,194,142,186,196,160,154,166,197,137,202};
int four5[]= {173,94,169,148,168,123,203,202,223,219,249,199,247,217,302,217,341,216,340,154,302,159,304,136,342,131,305,77,343,70,367,38,325,14,171,18,194,60,266,48,220,21,244,18,218,60,243,57,200,88,258,78,252,133,224,92,232,133,202,141};
int four2[]= {276,280, 276,272, 308,265, 317,264, 327,264, 309,213, 318,213, 338,212,328,213, 309,189, 309,168, 319,168, 328,166, 338,187,342,160, 254,194, 255,187, 247,236, 239,236, 220,237, 206,156, 199,85,199,91, 258,84, 233,115, 199,85, 199,92, 258,77, 258,84,225,93 };
int two4[]= {114,202, 113,195, 144,186, 153,186, 163,185, 145,136, 154,136, 173,135,164,135, 145,112, 145,92, 155,91, 164,90, 173,110, 178,84,91,118, 92,111, 84,160, 75,160, 57,162, 42,81, 33,9, 33,14, 93,7, 68,39,33,7, 32,15, 93,1, 93,6, 60,15};
int three4[]= {160,23,177,20,195,17,160,65,177,63,194,60,264,11,283,7,264,56,283,53,200,128,200,165,263,140,263,94,291,92,291,139,183,166,182,131,154,69,155,19,158,168,165,131,262,192,281,191,290,191,183,150,177,42,264,34,195,40,283,32};
int four3[]= {209,95,226,93,243,90,207,136,225,134,242,132,311,85,330,82,310,129,330,127,247,199,246,236,309,213,309,168,338,166,338,212,229,236,229,200,202,140,204,92,203,238,212,202,308,265,327,264,337,264,229,220,224,115,311,108,243,112,330,105};
int eight9[]= {157,33,252,21,165,56,102,143,161,165,246,185,178,79,200,77,222,74,163,108,163,127,162,132,273,67,246,100,246,120,247,125,163,81,247,73,188,78,211,76,233,74,246,46,174,164,162,104,247,96,265,132,266,75,158,38,159,87,249,77};
int nine8[]= {151,123,248,113,160,146,93,234,153,259,241,281,173,170,195,168,218,166,157,199,157,219,156,223,270,159,242,192,242,213,243,218,158,172,243,165,184,170,206,167,229,165,243,137,167,257,156,195,243,188,261,226,263,167,154,127,154,177,245,169};
int zero11[]= {118, 52,128, 52,159, 49,149, 49,112, 89,131, 88,112, 142,131, 142,149, 91,159, 91,149, 136,159, 136,116, 213,126, 213,218, 261,232, 244,250, 222,244, 218,117, 115,127, 115,149, 113,159, 113,129, 186,113, 185,369, 44,315, 52,344, 64,364, 85,363, 72,380, 102};
int eleven0[]= {72, 9,82, 9,115, 7,104, 7,66, 46,85, 46,66, 102,84, 102,104, 49,114, 49,104, 96,114, 96,69, 173,79, 173,172, 221,187, 205,205, 183,199, 178,70, 75,80, 75,103, 73,113, 73,82, 147,67, 145,326, 4,273, 12,301, 24,320, 45,319, 33,335, 62};
int zero10[]= { 118, 7, 128, 6, 150, 4, 160, 3, 118, 27,128, 27, 150, 25, 160, 25, 118, 32, 128, 30,369, 44, 314, 183, 314, 189, 316, 52, 117, 93,127, 92, 149, 90, 159, 90, 117, 114, 127, 114,149, 112, 159, 112, 117, 117, 117, 138, 232, 145,231, 58, 255, 156, 111, 186, 129, 185, 149, 189 };
int ten0[]= { 46, 94, 57, 94, 79, 92, 89, 92, 46, 114,56, 114, 79, 112, 89, 112, 46, 118, 56, 117,296, 136, 242, 274, 242, 281, 244, 142, 43, 180,53, 179, 76, 179, 86, 178, 42, 202, 53, 202,76, 199, 86, 201, 42, 205, 41, 226, 159, 235,160, 147, 183, 246, 33, 277, 52, 276, 73, 280 };

std::vector<CPoint> sixeight(30);
std::vector<CPoint> eightsix(30);

std::vector<CPoint> zerosix(30);
std::vector<CPoint> sixzero(30);

std::vector<CPoint> sixone(30);
std::vector<CPoint> onesix(30);

std::vector<CPoint> sixseven(20);
std::vector<CPoint> sevensix(20);

std::vector<CPoint> sixfour(20);
std::vector<CPoint> foursix(20);

std::vector<CPoint> fivefour(30);
std::vector<CPoint> fourfive(30);

std::vector<CPoint> fourtwo(30);
std::vector<CPoint> twofour(30);

std::vector<CPoint> fourthree(30);
std::vector<CPoint> threefour(30);

std::vector<CPoint> eightnine(30);
std::vector<CPoint> nineeight(30);

std::vector<CPoint> zeroeleven(30);
std::vector<CPoint> elevenzero(30);

std::vector<CPoint> zeroten(30);
std::vector<CPoint> tenzero(30);


void CreateVect()
{
	int j=0;
	for(int i=0; i<30; i++)
	{
		sixeight[i].x = six8[j];
		sixeight[i].y = six8[j+1];
		eightsix[i].x=eight6[j];
		eightsix[i].y=eight6[j+1];
		zerosix[i].x=zero6[j];
		zerosix[i].y=zero6[j+1];
		sixzero[i].x=six0[j];
		sixzero[i].y=six0[j+1];
		sixone[i].x=six1[j];
		sixone[i].y=six1[j+1];
		onesix[i].x=one6[j];
		onesix[i].y=one6[j+1];
		fourfive[i].x=four5[j];
		fourfive[i].y=four5[j+1];
		
		fivefour[i].x=five4[j];
		fivefour[i].y=five4[j+1];
		fourtwo[i].x=four2[j];
        fourtwo[i].y=four2[j+1];
		twofour[i].x=two4[j];
		twofour[i].y=two4[j+1];
		fourthree[i].x=four3[j];
		fourthree[i].y=four3[j+1];
		threefour[i].x=three4[j];
		threefour[i].y=three4[j+1];
		eightnine[i].x=eight9[j];
		eightnine[i].y=eight9[j+1];
		nineeight[i].x=nine8[j];
		nineeight[i].y=nine8[j+1];
		zeroeleven[i].x=zero11[j];
		zeroeleven[i].y=zero11[j+1];
		elevenzero[i].x=eleven0[j];
		elevenzero[i].y=eleven0[j+1];
		zeroten[i].x=zero10[j];
		zeroten[i].y=zero10[j+1];
		tenzero[i].x=ten0[j];
		tenzero[i].y=ten0[j+1];

		j=j+2;
		
	}

	int k=0;
	for(int i=0; i<20; i++)
	{
		sixseven[i].x=six7[k];
		sixseven[i].y=six7[k+1];
		sevensix[i].x=seven6[k];
		sevensix[i].y=seven6[k+1];
		sixfour[i].x=six4[k];
		sixfour[i].y=six4[k+1];
		foursix[i].x=four6[k];
		foursix[i].y=four6[k+1];
		k=k+2;
	}

	
}

void AddOff(int newzx,int newzy)
{
   for(int i=0; i<30; i++)
   {
	   sixeight[i].x=sixeight[i].x +newzx;
	   sixeight[i].y=sixeight[i].y +newzy;
	   eightsix[i].x=eightsix[i].x +newzx;
	   eightsix[i].y=eightsix[i].y +newzy;

	   sixone[i].x+=newzx;
	   sixone[i].y+=newzy;
	   onesix[i].x+=newzx;
	   onesix[i].y+=newzy;

	   zerosix[i].x+=newzx;
	   zerosix[i].y+=newzy;
	   sixzero[i].x+=newzx;
	   sixzero[i].y+=newzy;

	   fourfive[i].x+=newzx;
	   fourfive[i].y+=newzy;
	   fivefour[i].x+=newzx;
	   fivefour[i].y+=newzy;

	   fourtwo[i].x+=newzx;
       fourtwo[i].y+=newzy;
	   twofour[i].x+=newzx;
	   twofour[i].y+=newzy;

	   fourthree[i].x+=newzx;
	   fourthree[i].y+=newzy;
	   threefour[i].x+=newzx;
	   threefour[i].y+=newzy;

	   eightnine[i].x+=newzx;
	   eightnine[i].y+=newzy;
	   nineeight[i].x+=newzx;
	   nineeight[i].y+=newzy;

	   zeroeleven[i].x+=newzx;
	   zeroeleven[i].y+=newzy;
	   elevenzero[i].x+=newzx;
	   elevenzero[i].y+=newzy;

	   zeroten[i].x+=newzx;
	   zeroten[i].y+=newzy;
	   tenzero[i].x+=newzx;
	   tenzero[i].y+=newzy;
   }

   for(int i=0; i<20; i++)
   {
	   sixseven[i].x+=newzx;
	   sixseven[i].y+=newzy;
	   sevensix[i].x+=newzx;
	   sevensix[i].y+=newzy;

	   sixfour[i].x+=newzx;
	   sixfour[i].y+=newzy;
	   foursix[i].x+=newzx;
	   foursix[i].y+=newzy;
   }

   
}

Point FindCenter(ImgBinary& six)
{
	Point pt1,pt2;
	int flag=0,flag1=0;
	for(int y=1; y<six.Height()-1 ; y++)
		for(int x=1; x<six.Width()-1 ; x++)
		{
			if(six(x,y)==1 && flag==0)
			{
				pt1.x=x;
				pt1.y=y;
				flag=1;
				break;
			}
		}

	for(int y=six.Height()-1; y>1 ; y--)
		for(int x=six.Width()-1; x>1 ; x--)
		{
			if(six(x,y)==1 && flag1==0 )
			{
				pt2.x=x;
				pt2.y=y;
				flag1=1;
				break;
			}
		}

	int d2= pt1.y + (pt2.y-pt1.y)/2;
	int d1= pt1.x + (pt2.x-pt1.x)/2;
	Point center;
	center.x = d1;
	center.y = d2;
	cout<< d2<<" " <<d1<<endl;
	return center;
}

ImgBgr WarpingFunc(ImgBgr& img,std::vector<CPoint>& pt1,std::vector<CPoint>& pt2)
{
	MatDbl H;
	ImgBgr tempwarp;
	Set(&H,0);
	HomographyFit(pt1,pt2,&H);
	ImgFloat fxx,fyy;
	InitWarpHomography(H,img.Width(),img.Height(),&fxx,&fyy);
	Warp(img,fxx,fyy,&tempwarp);
	return tempwarp;
}

ImgBgr IndirectWarpingFunc(ImgBgr& img, std::vector<CPoint>& pt1, std::vector<CPoint>& pt2, std::vector<CPoint>& ref,std::vector<CPoint>& central)
{
	MatDbl H,H1,H2;
	ImgBgr tempwarp;
	HomographyFit(central,ref,&H1);
	HomographyFit(pt1,pt2,&H);
	MatrixMultiply(H1,H,&H2);
	ImgFloat fxx,fyy;
	InitWarpHomography(H2,img.Width(),img.Height(),&fxx,&fyy);
	Warp(img,fxx,fyy,&tempwarp);

	return tempwarp;
}

ImgBgr Feathering(ImgBgr& img,ImgBgr& warped)
{
	ImgBinary image,warpedimg,copyimg,copywarped;
	ImgBgr img1, warped1,feather(img.Width(),img.Height());
	Set(&feather,Bgr(0,0,0));
	Convert(img,&image);
	Convert(warped,&warpedimg);
	Xor(image,warpedimg,&copywarped);
	And(image,warpedimg,&copyimg); //overlapping region
	Convert(copyimg,&img1);
	Point center;
	center = FindCenter(copyimg);
	float d1=center.x;
	float d2=center.y;
	float as = (d1)/((d1)+(d2+50));
	float bs = (d2)/((d1)+(d2+50));
	
		
			for(int y=0 ; y < img1.Height(); y++)
				for(int x=0; x < img1.Width(); x++)
				{
					
					
						if(img1(x,y)==Bgr(255,255,255))
						{
							img1(x,y).b=as*img(x,y).b + bs*warped(x,y).b;
							img1(x,y).r=as*img(x,y).r + bs*warped(x,y).r;
							img1(x,y).g=as*img(x,y).g + bs*warped(x,y).g;
						}
					
				}

           
	
	return img1;
}


void Getoutline(ImgBgr& tempwarp,ImgBgr& maincanvas)
{
	ImgBinary warp,warp1;
	Convert(tempwarp,&warp);
	Convert(tempwarp,&warp1);
	Erode3x3(warp,&warp);
    Erode3x3(warp,&warp);
	Xor(warp,warp1,&warp);
	
	for(int y=0 ; y<maincanvas.Height(); y++)
		for(int x=0; x<maincanvas.Width(); x++)
		{
			if(warp(x,y)==1)
			{maincanvas(x,y)=Bgr(0,0,255);}
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
			cout<<"Enter only the location of the file containing the images \n (For eg: 'C:/tillman/') also it is assumed that the images are \n named small_tillman00.jpg .....small_tillman11.jpg."<<endl<<endl;
			ImgBgr canvas[12];
			ImgBgr imgarr[12];
			ImgBgr maincanvas,tempwarp[11],feather[11],maincanvas1,maincanvas2;
			CString imgstring,imgstring1,imgstring2;
			char path[50];
			CString get;
			cout<<"Enter the path to the folder in which the images are stored: "<<endl;
			gets(path);
			get=path;
			
			imgstring1="small_tillman0%d.jpg";
			imgstring2="small_tillman%d.jpg";
			imgstring1 = get + imgstring1;
			imgstring2 = get + imgstring2;
						
			for(int i=0; i<10;i++)
			{
				imgstring.Format(imgstring1,i);
				Load(imgstring,&imgarr[i]);
			}
			
			for(int i=10; i<12; i++)
			{
				imgstring.Format(imgstring2,i);
				Load(imgstring,&imgarr[i]);
			}
			
			Figure canv;
			for(int i=0; i<12; i++)
			{
				canvas[i].Reset(4*imgarr[i].Width(),4*imgarr[i].Height());
				Set(&canvas[i],Bgr(0,0,0));
				Set(&canvas[i],Point((canvas[i].Width()/2)-(imgarr[i].Width()/2),(canvas[i].Height()/2)-(imgarr[i].Height()/2)),imgarr[i]);
				
			}
			
			maincanvas1.Reset(canvas[0].Width(),canvas[0].Height());
			maincanvas.Reset(canvas[0].Width(),canvas[0].Height());
			maincanvas2.Reset(canvas[0].Width(),canvas[0].Height());
			Set(&maincanvas,Bgr(0,0,0));
			Set(&maincanvas1,Bgr(0,0,0));
			Set(&maincanvas,Point((canvas[6].Width()/2)-(imgarr[6].Width()/2),(canvas[6].Height()/2)-(imgarr[6].Height()/2)),imgarr[6]);
			
			int newzx=((canvas[6].Width()/2)-(imgarr[6].Width()/2));
			int newzy=((canvas[6].Height()/2)-(imgarr[6].Height()/2));
			

			CreateVect();
			AddOff(newzx,newzy);
			tempwarp[0]=WarpingFunc(canvas[0],sixzero,zerosix);
			tempwarp[1]=WarpingFunc(canvas[1],sixone,onesix);
			tempwarp[2]=IndirectWarpingFunc(canvas[2],fourtwo,twofour,foursix,sixfour);
			tempwarp[3]=IndirectWarpingFunc(canvas[3],fourthree,threefour,foursix,sixfour);
			tempwarp[4]=WarpingFunc(canvas[4],sixfour,foursix);
			tempwarp[5]=IndirectWarpingFunc(canvas[5],fourfive,fivefour,foursix,sixfour);
			tempwarp[6]=WarpingFunc(canvas[7],sixseven,sevensix);
			tempwarp[7]=WarpingFunc(canvas[8],sixeight,eightsix);
			tempwarp[8]=IndirectWarpingFunc(canvas[9],eightnine,nineeight,eightsix,sixeight);
			tempwarp[9]=IndirectWarpingFunc(canvas[10],zeroten,tenzero,zerosix,sixzero);
			tempwarp[10]=IndirectWarpingFunc(canvas[11],zeroeleven,elevenzero,zerosix,sixzero);
			ImgBinary one,two;
			Getoutline(tempwarp[0],maincanvas1);
			Getoutline(tempwarp[1],maincanvas1);
			Getoutline(tempwarp[2],maincanvas1);
			Getoutline(tempwarp[3],maincanvas1);
			Getoutline(tempwarp[4],maincanvas1);
			Getoutline(tempwarp[5],maincanvas1);
			Getoutline(tempwarp[6],maincanvas1);
			Getoutline(tempwarp[7],maincanvas1);
			Getoutline(tempwarp[8],maincanvas1);
			Getoutline(tempwarp[9],maincanvas1);
			Getoutline(canvas[6],maincanvas1);
			feather[0]=Feathering(canvas[6],tempwarp[0]);
			Convert(canvas[6],&one);
			Convert(tempwarp[0],&two);
			Xor(one,two,&one);
			ImgBgr copy1;
			copy1=canvas[6];
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					copy1(x,y).r=canvas[6](x,y).r * one(x,y);
					copy1(x,y).g=canvas[6](x,y).g * one(x,y);
					copy1(x,y).b=canvas[6](x,y).b * one(x,y);

					tempwarp[0](x,y).r= tempwarp[0](x,y).r * one(x,y); 
					tempwarp[0](x,y).g= tempwarp[0](x,y).g * one(x,y); 
					tempwarp[0](x,y).b= tempwarp[0](x,y).b * one(x,y); 

					if(feather[0](x,y).r > 0 && feather[0](x,y).b > 0)
					{maincanvas(x,y)=feather[0](x,y);}
				}
			
			Set(&maincanvas,Bgr(0,0,0));
			Or(tempwarp[0],maincanvas,&maincanvas);
			Or(copy1,maincanvas,&maincanvas);
			
			
			feather[1]=Feathering(canvas[6],tempwarp[1]);
			Convert(maincanvas,&one);
			Convert(tempwarp[1],&two);
			Xor(one,two,&one);
			
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[1](x,y).r= tempwarp[1](x,y).r * one(x,y); 
					tempwarp[1](x,y).g= tempwarp[1](x,y).g * one(x,y); 
					tempwarp[1](x,y).b= tempwarp[1](x,y).b * one(x,y);

					if(feather[1](x,y).r > 0 && feather[1](x,y).b > 0)
					{maincanvas(x,y)=feather[1](x,y);}
				}
			Or(tempwarp[1],maincanvas,&maincanvas);
			
			feather[2]=Feathering(canvas[6],tempwarp[7]);
			Convert(maincanvas,&one);
			Convert(tempwarp[7],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[7](x,y).r= tempwarp[7](x,y).r * one(x,y); 
					tempwarp[7](x,y).g= tempwarp[7](x,y).g * one(x,y); 
					tempwarp[7](x,y).b= tempwarp[7](x,y).b * one(x,y);

					if(feather[2](x,y).r > 0 && feather[2](x,y).b > 0)
					{maincanvas(x,y)=feather[2](x,y);}
				}
			Or(tempwarp[7],maincanvas,&maincanvas);

			feather[3]=Feathering(canvas[6],tempwarp[6]);
			Convert(maincanvas,&one);
			Convert(tempwarp[6],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[6](x,y).r= tempwarp[6](x,y).r * one(x,y); 
					tempwarp[6](x,y).g= tempwarp[6](x,y).g * one(x,y); 
					tempwarp[6](x,y).b= tempwarp[6](x,y).b * one(x,y);

					if(feather[3](x,y).r > 0 && feather[3](x,y).b > 0)
					{maincanvas(x,y)=feather[3](x,y);}
				}
			Or(tempwarp[6],maincanvas,&maincanvas);

			feather[4]=Feathering(canvas[6],tempwarp[4]);
			Convert(maincanvas,&one);
			Convert(tempwarp[4],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[4](x,y).r= tempwarp[4](x,y).r * one(x,y); 
					tempwarp[4](x,y).g= tempwarp[4](x,y).g * one(x,y); 
					tempwarp[4](x,y).b= tempwarp[4](x,y).b * one(x,y);

					if(feather[4](x,y).r > 0 && feather[4](x,y).b > 0)
					{maincanvas(x,y)=feather[4](x,y);}
				}
			Or(tempwarp[4],maincanvas,&maincanvas);

			//
			feather[5]=Feathering(canvas[6],tempwarp[8]);
			Convert(maincanvas,&one);
			Convert(tempwarp[8],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[8](x,y).r= tempwarp[8](x,y).r * one(x,y); 
					tempwarp[8](x,y).g= tempwarp[8](x,y).g * one(x,y); 
					tempwarp[8](x,y).b= tempwarp[8](x,y).b * one(x,y);

					if(feather[5](x,y).r > 0 && feather[5](x,y).b > 0)
					{maincanvas(x,y)=feather[5](x,y);}
				}
			Or(tempwarp[8],maincanvas,&maincanvas);

			//
			feather[6]=Feathering(canvas[6],tempwarp[10]);
			Convert(maincanvas,&one);
			Convert(tempwarp[8],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[10](x,y).r= tempwarp[10](x,y).r * one(x,y); 
					tempwarp[10](x,y).g= tempwarp[10](x,y).g * one(x,y); 
					tempwarp[10](x,y).b= tempwarp[10](x,y).b * one(x,y);

					if(feather[6](x,y).r > 0 && feather[6](x,y).b > 0)
					{maincanvas(x,y)=feather[6](x,y);}
				}
			

			//
			feather[7]=Feathering(canvas[6],tempwarp[9]);
			Convert(maincanvas,&one);
			Convert(tempwarp[9],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[9](x,y).r= tempwarp[9](x,y).r * one(x,y); 
					tempwarp[9](x,y).g= tempwarp[9](x,y).g * one(x,y); 
					tempwarp[9](x,y).b= tempwarp[9](x,y).b * one(x,y);

					if(feather[7](x,y).r > 0 && feather[7](x,y).b > 0)
					{maincanvas(x,y)=feather[7](x,y);}
				}
			Or(tempwarp[9],maincanvas,&maincanvas);
			

           feather[8]=Feathering(canvas[6],tempwarp[2]);
		   Convert(maincanvas,&one);
		   Convert(tempwarp[2],&two);
		   Xor(one,two,&one);
		   for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[2](x,y).r= tempwarp[2](x,y).r * one(x,y); 
					tempwarp[2](x,y).g= tempwarp[2](x,y).g * one(x,y); 
					tempwarp[2](x,y).b= tempwarp[2](x,y).b * one(x,y);

				}
           Or(tempwarp[2],maincanvas,&maincanvas);
          

		   //
		   feather[9]=Feathering(canvas[6],tempwarp[5]);
			Convert(maincanvas,&one);
			Convert(tempwarp[5],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[5](x,y).r= tempwarp[5](x,y).r * one(x,y); 
					tempwarp[5](x,y).g= tempwarp[5](x,y).g * one(x,y); 
					tempwarp[5](x,y).b= tempwarp[5](x,y).b * one(x,y);

					if(feather[9](x,y).r > 0 && feather[9](x,y).b > 0)
					{maincanvas(x,y)=feather[9](x,y);}
				}
			
			Or(tempwarp[5],maincanvas,&maincanvas);

			//

			feather[10]=Feathering(canvas[6],tempwarp[3]);
			Convert(maincanvas,&one);
			Convert(tempwarp[3],&two);
			Xor(one,two,&one);
			for(int y=0; y < maincanvas.Height(); y++)
				for(int x=0 ; x < maincanvas.Width(); x++)
				{
					tempwarp[3](x,y).r= tempwarp[3](x,y).r * one(x,y); 
					tempwarp[3](x,y).g= tempwarp[3](x,y).g * one(x,y); 
					tempwarp[3](x,y).b= tempwarp[3](x,y).b * one(x,y);

				}

		    Or(tempwarp[3],maincanvas,&maincanvas);
		    
			canv.Draw(maincanvas);
			canv.SetTitle("stiched image");
			
			Or(maincanvas,maincanvas1,&maincanvas2);
			Figure out;
			out.Draw(maincanvas2);
			out.SetTitle("outline");
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
