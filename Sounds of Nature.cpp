// Sounds of Nature.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv.hpp"
#include "highgui.h"


using namespace std;
using namespace cv;

int x[3000], y[3000], ymin[2000], ymax[2000], xmin[2000], xmax[2000], intmax[1000], intmin[1000];
string notes[500];
double frequency[1000];
ofstream outputlog;
int interval = 0;


void mainmenu (string &filepath)	
{
	cout << "Welcome to |Sounds of Nature|" << endl << "This program is designed to convert waveform-like photographs" ;
	cout << endl << "into an audible soundwave." << endl << endl;

	cout << "Enter filepath to desired image: " ;
	getline(cin, filepath);
	
	while(filepath.empty())
	{
		cout << endl << endl << "Error: No path entered. Try again: ";
		getline(cin, filepath);
	}
}

void namechange(string &filepath, string &newfilepath, string &soutputpath)
{
	int fpsize = 0;
	string resetpath = "";	

	resetpath = filepath;
	fpsize = filepath.size();
	
	filepath.erase(fpsize - 4, 4);
	newfilepath = filepath + "new.jpg";
	soutputpath = filepath + "OutputLog.txt";
	filepath = resetpath;

}

void topdownfill(Mat &writeimg, int imgw, int imgh)
{

	floodFill(writeimg, Point(0,0), Scalar(255,255,255), 0 , 0 , CV_FLOODFILL_FIXED_RANGE, NULL);
	floodFill(writeimg, Point(imgw-1,imgh-1), Scalar(255,255,255), 0 , 0 , CV_FLOODFILL_FIXED_RANGE, NULL);

}

void findline(IplImage* gsclimg)
{
	bool flagger = false;
	unsigned int i = 0, j = 0, byte, r, g, b;
	unsigned char* data = (unsigned char *)gsclimg->imageData;	
	int nchannels = gsclimg->nChannels;
	int step = gsclimg->widthStep;	
	unsigned int imgh = gsclimg->height;
	unsigned int imgw = gsclimg->width;

	for( i = 0; i <= imgw; i++)
	{
		j = 0;
		flagger = false;
		while(flagger == false &&  j <= imgh)
		{
			r = data[j*step + i*nchannels + 0];
			g = data[j*step + i*nchannels + 1];
			b = data[j*step + i*nchannels + 2];
       
			byte = ( r + g + b ) / 3;

			if(byte == 0)
			{
				x[i]=i;
				y[i]=j;
				flagger = true;
			}
			j++;
			
		}
	}
}

void findextrema(int imgw)
{
	bool maxflag = false, minflag = false;
	int a=0, b = 0, c = 0;

	while (a<=imgw)
	{
		if(maxflag == false && minflag == false)
		{
			if(y[a+1] > y[a])
			{
				maxflag = true;
			}
			if(y[a+1] < y[a])
			{
				minflag = true;
			}
			if(y[a+1] == y[a])
			{
				a++;
			}
		}
		while(maxflag == true && a<=imgw)
		{
			if(y[a+1] < y[a])
			{
				xmax[b] = a;
				ymax[b] = y[a];
				b++;
				maxflag = false;
				minflag = true;
			}
			a++;
		}
		while(minflag == true && a<=imgw)
		{
			if(y[a+1] > y[a])
			{
				xmin[c] = a;
				ymin[c] = y[a];
				c++;
				minflag = false;
				maxflag = true;
			}
			a++;
		}
	}
}

int findfrequency(int imgw)
{
	int a = 0, b = 0, c = 0, d = 0;
	bool terminate = false;

	cout << endl << "What interval would you like to use? (Default 100) : ";
	cin >> interval;

	if(interval == 0)
	{
		interval = 100;
	}

	while(terminate == false)
	{
		b = b + interval;
		while(xmax[c] < b && xmax[c] != 0)
		{
			intmax[a] = intmax[a] + 1;
			c++;
		}

		while(xmin[d] < b && xmin[d] != 0)
		{
			intmin[a] = intmin[a] + 1;
			d++;
		}
		a++;

		if(xmin[d] == 0 && xmax[c] == 0)
		{
			terminate =  true;
		}
	}

	return interval;
}
void matchnote(int a, string &note)
{
	int freqint = frequency[a];
	
	
	int
		A1  = 440,
		As1 = 466,
		B1  = 493,
		C1  = 523,
		Cs1 = 554,
		D1  = 587,
		Ds1 = 622,
		E1  = 659,
		F1  = 698,
		Fs1 = 739,
		G1  = 783,
		Gs1 = 830,
		A2  = 880,
		As2 = 932,
		B2  = 987,
		C2  = 1046,
		Cs2 = 1108,
		D2  = 1174,
		Ds2 = 1244,
		E2  = 1318,
		F2  = 1396;

	
		if(freqint == A1)
		{
			note = "A";
		}

		if(freqint == As1)
		{
			note = "A#";
		}

		if(freqint == B1)
		{
			note = "B";
		}

		if(freqint == C1)
		{
			note = "C";
		}

		if(freqint == Cs1)
		{
			note = "C#";
		}

		if(freqint == D1)
		{
			note = "D";
		}

		if(freqint == Ds1)
		{
			note = "D#";
		}

		if(freqint == E1)
		{
			note = "E";
		}

		if(freqint == F1)
		{
			note = "F";
		}
		
		if(freqint == Fs1)
		{
			note = "F#";
		}

		if(freqint == G1)
		{
			note = "G";
		}

		if(freqint == Gs1)
		{
			note = "G#";
		}

		if(freqint == A2)
		{
			note = "A";
		}

		if(freqint == As2)
		{
			note = "A#";
		}

		if(freqint == B2)
		{
			note = "B";
		}

		if(freqint == C2)
		{
			note = "C";
		}

		if(freqint == Cs2)
		{
			note = "C#";
		}

		if(freqint == D2)
		{
			note = "D";
		}

		if(freqint == Ds2)
		{
			note = "D#";
		}

		if(freqint == E2)
		{
			note = "E";
		}

		if(freqint == F2)
		{
			note = "F";
		}
}
void determinefrequency(int imgw, const char* outputpath)
{
	string note;
	double n;
	int size = sizeof (intmax);
	outputlog.open(outputpath, ios::out | ios::trunc);

	for(int a = 0; intmax[a] != 0 ; a++)
	{
		if(intmax[a] > intmin[a])
		{
			float m = intmax[a];
			n = m/12;
			frequency[a] = 440 * pow(2,n);
			matchnote(a, note);
			notes[a] = note;
		}
		
		if(intmax[a] < intmin[a] || intmax[a] == intmin[a])
		{
			float m = intmax[a];
			n = m/12;
			frequency[a] = 440 *  ::pow(2, n);
			matchnote(a, note);
			notes[a] = note;
		}
		
		if(outputlog.is_open())
		{
			outputlog.setf(ios::fixed);
			outputlog << notes[a] << ", " << setprecision(2) << frequency[a] << endl;
		}
	}
	outputlog.close();
}

void printfrequency(IplImage* &lineimg, int imgw, const char* outputpath)
{
	string printtext;
	const char* text;
	text = "filler";
	CvFont font;
	cvInitFont(&font, CV_FONT_NORMAL, .5, .5,0,1);
	int placement = 0;
	

	ifstream outputlog(outputpath, ios::in);

	for(int a = 0; a <= imgw; a = a + interval, placement++)
	{
		cvLine(lineimg, cvPoint(a + interval, 900), cvPoint(a + interval, 600), cvScalar(0,0,0), 1);
		getline(outputlog, printtext);
		text = printtext.c_str();
		if((placement % 2) == 0 || placement == 0)
		{
			cvPutText(lineimg, text, cvPoint(a+1, 600), &font, cvScalar(0,0,0));
		}
		else
		{
			cvPutText(lineimg, text, cvPoint(a+1, 910), &font, cvScalar(0,0,0));
		}
	}

	outputlog.close();

}

int _tmain(int argc, _TCHAR* argv[])
{
	string filepath = "";
	string newfilepath = "";
	string soutputpath = "";
	const char* afilepath;
	const char* outputpath;
	const char* loadpath;
	int interval = 0;

	mainmenu(filepath);	
	
	//filepath = "H:\\Sounds of Nature\\Images\\1.jpg";
	namechange(filepath, newfilepath, soutputpath);

	loadpath = filepath.c_str();
	afilepath = newfilepath.c_str();
	outputpath = soutputpath.c_str();
	IplImage* gsclimg = cvLoadImage(loadpath, CV_LOAD_IMAGE_COLOR);	
	cvThreshold(gsclimg, gsclimg ,130, 300, THRESH_BINARY); 
	
	Mat writeimg (gsclimg, true);
	imwrite(newfilepath, writeimg);	

	unsigned int imgh = gsclimg->height;
	unsigned int imgw = gsclimg->width;

	IplImage* lineimg = cvCreateImage(Size(imgw,imgh), IPL_DEPTH_8U, 3);	
	
	findline(gsclimg);

	for (unsigned int i = 0; i <= imgw - 1; i++)
	{
		cvLine(lineimg, cvPoint(x[i],y[i]), cvPoint(x[i+1],y[i+1]), cvScalar(0,0,0), 1);
	}
	
	writeimg = lineimg;	
	topdownfill(writeimg, imgw, imgh);		
	imwrite(newfilepath, writeimg);

	findextrema(imgw);

	interval = findfrequency(imgw);

	determinefrequency(imgw, outputpath);

	printfrequency(lineimg, imgw, outputpath);
	
	writeimg = lineimg;
	imwrite(newfilepath, writeimg);
	
	cout << endl << endl << "Bon appetit!" << endl;
	
	return 0;
}

