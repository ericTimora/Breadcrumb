#ifndef IMAGE_DEF
#define IMAGE_DEF
#include <filter.h>

class Image{
	unsigned char *data;
	int width;
	int height;
	public:
		Filter filterData;
		bool updated;
		Image();
		void setData(unsigned char *inputData);
		void setWidth(int inputWidth);
		void setHeight(int inputHeight);
		int getWidth();
		int getHeight();		
		unsigned char* getData();
		void Update();
};
#endif
