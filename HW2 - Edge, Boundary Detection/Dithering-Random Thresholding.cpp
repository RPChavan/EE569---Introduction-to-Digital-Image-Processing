
  
  
  
  
// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;

//Function that generates the threshold value
int random_thresholder(int pixelvalue,double random_no)
{
	
	if(  (double(pixelvalue) >= 0) && (double(pixelvalue) < random_no) )
	{	
	  return 0;  
    }
	else if( (double(pixelvalue) >= random_no) && (double(pixelvalue) < 256) )
	{	
	  return 255;
	}

}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Row_Size = 600;
	int Column_Size  = 400;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Row_Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[Row_Size][Column_Size][BytesPerPixel];


	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

//Variable Declaration
int i,j;
double random_no;
unsigned char outimage[Row_Size][Column_Size][BytesPerPixel];

std::default_random_engine generator;
std::uniform_real_distribution<double> random_distribution(0.0,255.0);

for(i=0; i<Row_Size; i++ )
{
	for(j=0; j<Column_Size; j++)
	{
		//cout<<int(Imagedata[i][j][0])<<"   ";
		random_no  = random_distribution(generator);
		//cout<<random_no<<"   ";
		outimage[i][j][0] = random_thresholder(int(Imagedata[i][j][0]), random_no);
		//cout<<int(outimage[i][j][0])<<endl;
		
	}
}

// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outimage, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
