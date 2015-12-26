#ifndef PNMREAD_DEF
#define PNMREAD_DEF

#include <source.h>

class PNMreader : public Source{
	char *filename;
	public:
		PNMreader(char *f_in);
		~PNMreader();
		virtual void Execute();
		virtual void Update();
};
#endif
