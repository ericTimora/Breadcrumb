#ifndef SOURCE_DEF
#define SOURCE_DEF
#include <image.h>

class Source{
	protected:
		Image picture;
	public:
		Source();
		virtual ~Source();
		Image * GetOutput();
		virtual void Execute() = 0;
		virtual void Update() = 0;
};
#endif
