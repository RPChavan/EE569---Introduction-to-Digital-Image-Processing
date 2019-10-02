
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;
int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Row_Size = 400;
	int Column_Size  = 600;
	
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
			Column_Size = atoi(argv[4]);
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
	int f[Row_Size][Column_Size][BytesPerPixel];
	int i, j, b, e, k, l, m;
	int Threshold = 127;
	float h_arr[25] =   {0.0,               0.0,          0.0,       0.0,            0.0       ,
	                     0.0,               0.0,          0.0,       0.0,            0.0       ,
						 0.0,               0.0,          0.0,      7.0/48.0,      5.0/48.0    ,
						 3.0/48.0,       5.0/48.0,     7.0/48.0,    5.0/48.0,      3.0/48.0    ,
						 1.0/48.0,       3.0/48.0,     5.0/48.0,    3.0/48.0,      1.0/48.0    };
						 
	unsigned char Output_Image[Row_Size][Column_Size][BytesPerPixel];
	
	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
	    //cout<<int(Imagedata[i][j][0])<<"   ";
		f[i][j][0] = int(Imagedata[i][j][0]);
		//cout<<f[i][j]<<"   ";
		}
		cout<<endl;
	}
	
	//first pixel
	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			if(f[i][j][0]  < Threshold)
			{
				b = 0;
			}
			else
			{
				b = 255;
			}
			//cout<<f[i][j][0]<<endl;;
			e = f[i][j][0] - b;
			//cout<<e<<endl;
			f[i][j][0] = b;
			//cout<<f[i][j][0];
			m = 0;
			for(k = i-2; k <= i+2; k++)
			{
					for(l = j+2; l >= j-2; l--)
				{
					//cout<<f[k][l][0]<<"-----";
					f[k][l][0] = f[k][l][0] + h_arr[m]*e;
					//cout<<f[k][l][0]<<"    ";					
					
				}
				
			}
		}
	}
	
	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			//cout<<f[i][j][0]<<"    ";
			Output_Image[i][j][0] = (unsigned char)f[i][j][0];
		}
		cout<<endl;
	}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Output_Image, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
