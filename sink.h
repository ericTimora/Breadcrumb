#ifndef SINK_DEF
#define SINK_DEF
#include <image.h>

class Image;
class Sink{
	protected:
		Image *input;
		Image *input2;
	public:
		void SetInput(Image *img);
		void SetInput2(Image *img);
};
#endif 
