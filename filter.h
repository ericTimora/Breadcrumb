#ifndef FILTERH
#define FILTERH

class PNMreader;
class Shrinker;
class LRConcat;
class TBConcat;
class Blender;

class Filter{
	public:
		Filter();
		PNMreader *pnmRead;
		Shrinker *shrink;
		LRConcat *lrcon;
		TBConcat *tbcon;
		Blender *blend;
};

#endif
