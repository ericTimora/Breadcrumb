#include <image.h>
#include <filters.h>
#include <PNMreader.h>

Image::Image() : width(0), height(0), data(0), updated(false) {}

void Image::setData(unsigned char *inputData){
	data = inputData;
}

void Image::setWidth(int inputWidth){
	width = inputWidth;
}

void Image::setHeight(int inputHeight){
	height = inputHeight;
}

int Image::getWidth(){
	return width;
}

int Image::getHeight(){
	return height;
}

unsigned char* Image::getData(){
	return data;
}

void Image::Update(){
	if(filterData.pnmRead != 0)
		filterData.pnmRead->Update();

	else if(filterData.shrink != 0)
		filterData.shrink->Update();	

	else if(filterData.lrcon != 0)
		filterData.lrcon->Update();

	else if(filterData.tbcon != 0)
		filterData.tbcon->Update();

	else
		filterData.blend->Update();
}






