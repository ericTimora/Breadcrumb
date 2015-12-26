#ifndef FILTERS_DEF
#define FILTERS_DEF
#include <source.h>
#include <sink.h>

class Filters : public Sink, public Source{

};

class Shrinker : public Filters{
	public:
		Shrinker();
		~Shrinker();
		virtual void Execute();
		virtual void Update();
};

class LRConcat : public Filters{
	public:
		LRConcat();
		~LRConcat();
		virtual void Execute();
		virtual void Update();
};

class TBConcat : public Filters{
	public:
		TBConcat();
		~TBConcat();
		virtual void Execute();
		virtual void Update();
};

class Blender : public Filters{
	float factor;
	public:
		Blender();
		~Blender();
		void SetFactor(float fact);
		virtual void Execute();
		virtual void Update();
};
#endif
