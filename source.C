#include <source.h>
#include <iostream>

using namespace std;
Source::Source(){
}

Source::~Source(){
}
Image * Source::GetOutput(){
	return &picture;
}
