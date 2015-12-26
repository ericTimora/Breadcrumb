#include <filters.h>
#include <stdlib.h>
#define COLOR_DIMENSION 3

Shrinker::Shrinker(){
	picture.filterData.shrink = this;
}

LRConcat::LRConcat(){
	picture.filterData.lrcon = this;
}

TBConcat::TBConcat(){
	picture.filterData.tbcon = this;
}

Blender::Blender(){
	picture.filterData.blend = this;
}

Shrinker::~Shrinker(){
	delete[] picture.getData();
}

LRConcat::~LRConcat(){
	delete[] picture.getData();
}

TBConcat::~TBConcat(){
	delete[] picture.getData();
}

Blender::~Blender(){
	delete[] picture.getData();
}

void Shrinker::Execute(){
	unsigned char 	*inputBuff;
	unsigned char	*outputBuff;
	int 			index(0);
	int				index1(0);
	const int 		inWidth(input->getWidth());
	const int 		inHeight(input->getHeight());
	const int 		outWidth(inWidth/2);
	const int 		outHeight(inHeight/2);
	
	outputBuff 	= new unsigned char[COLOR_DIMENSION * outWidth * outHeight];

	inputBuff   = input->getData();

	for(int r = 0; r < outHeight; r++){
		for(int c = 0; c < outWidth; c++){
			index 	= COLOR_DIMENSION * ((r * outWidth) + c);
			index1 	= COLOR_DIMENSION * (2 * r * inWidth + 2 * c);
			outputBuff[index + 0] = inputBuff[index1 + 0];
			outputBuff[index + 1] = inputBuff[index1 + 1];
			outputBuff[index + 2] = inputBuff[index1 + 2];
		}
	}
	picture.setWidth(outWidth);
	picture.setHeight(outHeight);
	picture.setData(outputBuff);
	picture.updated = true;
}

void LRConcat::Execute(){
	unsigned char 	*leftBuff;
	unsigned char 	*rightBuff;
	unsigned char 	*outputBuff;
	const int 		leftWidth(input->getWidth());
	const int		leftHeight(input->getHeight());
	const int		rightWidth(input2->getWidth());
	const int		rightHeight(input2->getHeight());
	const int		outWidth(leftWidth + rightWidth);
	int				index(0);
	int				index1(0);
	
	outputBuff 	= new unsigned char[COLOR_DIMENSION * outWidth * leftHeight];
	
	leftBuff 	= input->getData();
	rightBuff 	= input2->getData();

	for(int r = 0; r < leftHeight; r++){
		for(int c = 0; c < leftWidth; c++){
			index 	= COLOR_DIMENSION * (r * outWidth + c);
			index1	= COLOR_DIMENSION * (r * leftWidth + c);
 
			outputBuff[index + 0] = leftBuff[index1 + 0];
			outputBuff[index + 1] = leftBuff[index1 + 1];
			outputBuff[index + 2] = leftBuff[index1 + 2];
		}
	}
	for(int r = 0; r < rightHeight; r++){
		for(int c = 0; c < rightWidth; c++){
			index	= COLOR_DIMENSION * (r * outWidth + c + leftWidth);
			index1 	= COLOR_DIMENSION * (r * rightWidth + c);
			
			outputBuff[index + 0] = rightBuff[index1 + 0];
			outputBuff[index + 1] = rightBuff[index1 + 1];
			outputBuff[index + 2] = rightBuff[index1 + 2];
		}
	}

	picture.setWidth(leftWidth + rightWidth);
	picture.setHeight(leftHeight);
	picture.setData(outputBuff);
	picture.updated = true;
}
void TBConcat::Execute(){
	unsigned char 	*topBuff;
	unsigned char 	*bottomBuff;
	unsigned char 	*outputBuff;
	const int		topWidth(input->getWidth());
	const int		topHeight(input->getHeight());
	const int		botWidth(input2->getWidth());
	const int		botHeight(input2->getHeight());
	const int		outWidth(topWidth);
	const int		outHeight(topHeight + botHeight);
	int				index(0);
	int				index1(0);

	outputBuff 	= new unsigned char[COLOR_DIMENSION * outWidth * outHeight];
	topBuff		= input->getData();
	bottomBuff 	= input2->getData();

	for(int r = 0; r < input->getHeight(); r++){
		for(int c = 0; c < input->getWidth(); c++){
			index 	= COLOR_DIMENSION * (r * outWidth + c);

			outputBuff[index + 0] = topBuff[index + 0];
			outputBuff[index + 1] = topBuff[index + 1];
			outputBuff[index + 2] = topBuff[index + 2];
		}	
	}

	for(int r = 0; r < input2->getHeight(); r++){
		for(int c = 0; c < input2->getWidth(); c++){
			index 	= COLOR_DIMENSION * ((r + topHeight) * outWidth + c);
			index1 	= COLOR_DIMENSION * (r * outWidth + c);

			outputBuff[index + 0] = bottomBuff[index1 + 0];
			outputBuff[index + 1] = bottomBuff[index1 + 1];
			outputBuff[index + 2] = bottomBuff[index1 + 2];
		}
	}

	picture.setWidth(outWidth);
	picture.setHeight(outHeight);
	picture.setData(outputBuff);
	picture.updated = true;
}

void Blender::SetFactor(float fact){
	factor = fact;
}

void Blender::Execute(){
	unsigned char 	*buff1;
	unsigned char 	*buff2;
	unsigned char 	*buffOut;
	const int 		width(input->getWidth());
	const int		height(input->getHeight());
	int				index(0);
	int redFactor(0);
	int greenFactor(0);
	int blueFactor(0);

	buffOut = new unsigned char[COLOR_DIMENSION * width * height];

	buff1 = input->getData();
	buff2 = input2->getData();

	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			index = COLOR_DIMENSION * (r * width + c);

			redFactor 		= (buff1[index + 0] * factor) + (buff2[index + 0] * (1 - factor));
			greenFactor 	= (buff1[index + 1] * factor) + (buff2[index + 1] * (1 - factor));
			blueFactor 		= (buff1[index + 2] * factor) + (buff2[index + 2] * (1 - factor));

			buffOut[index + 0] = redFactor;
			buffOut[index + 1] = greenFactor;
			buffOut[index + 2] = blueFactor;
		}
	}
	picture.setWidth(width);
	picture.setHeight(height);
	picture.setData(buffOut);
	picture.updated = true;

}

void Shrinker::Update(){
	if(input->updated == false)
	    input->Update();
	this->Execute();
}

void LRConcat::Update(){
	if(input->updated == false)
		input->Update();
	if(input2->updated == false)
		input2->Update();
	this->Execute();
}

void TBConcat::Update(){
	if(input->updated == false)
		input->Update();
	if(input2->updated == false)
		input2->Update();
	this->Execute();
}

void Blender::Update(){
	if(input->updated == false)
		input->Update();
	if(input2->updated == false)
		input2->Update();
	this->Execute();
}

