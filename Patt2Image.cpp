#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>

void main(int argc, char** argv) {

	int values[256] = {0};
	if (argc>1) {
		FILE *f = fopen(argv[1], "rb");
		
		int pattSize = 400; int indent = pattSize/2;
		int pixSize = pattSize/16;
		IplImage *im = cvCreateImage(cvSize(pattSize*2, pattSize*2), IPL_DEPTH_8U, 1);
		cvSet(im, cvScalarAll(0));

		int val;
		for (int i=0; i<3; i++) {
			for (int i=0; i<256; i++) {
				fscanf(f, "%d ", &val);
				values [i]+=val;
			}
		}

			
		for (int y=0; y<16; y++) {
			for (int x=0; x<16; x++) {
				cvRectangle(im, cvPoint(x*pixSize+indent, y*pixSize+indent), cvPoint((x+1)*pixSize+indent, (y+1)*pixSize+indent), cvScalarAll(values [x+(y*16)]/3), -1);
			}
		}

		std::string s = argv[1];
		s = s.substr(0, s.find_last_of("."));
		s = s.append(".bmp");
		cvSaveImage(s.c_str(), im);
		//argv
	}
}
