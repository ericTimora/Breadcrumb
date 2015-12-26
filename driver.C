#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
	PNMreader reader(argv[1]);
	PNMwriter writer;
	Shrinker shrinker1;
	LRConcat lrconcat1;

	reader.Execute();
	shrinker1.SetInput(reader.GetOutput());
	lrconcat1.SetInput(shrinker1.GetOutput());
	lrconcat1.SetInput2(shrinker1.GetOutput());

	shrinker1.Execute();
	lrconcat1.Execute();

	writer.SetInput(lrconcat1.GetOutput());
	writer.Write(argv[2]);
	
	return(0);
}
