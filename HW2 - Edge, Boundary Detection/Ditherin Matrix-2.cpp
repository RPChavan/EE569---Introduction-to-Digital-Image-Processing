
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;
int In[2][2] = {{1,2},
	                {3,0}};
    int (*I2n)[4] = new int[4][4];
    int i,j,k,l;
        
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

	//Variable declaration
	int i,j,k,l,b;
	int dithering_I1 = 1;
	short I2[2][2] = {{1,2},
	                {3,0}};
	short  two_n = 2;  
	short n = two_n/2; //16
    unsigned char Out_image[Row_Size][Column_Size][1];
    float **T2 = new float*[two_n];
    for (i = 0; i < two_n; i++) 
	{
        T2[i] = new float[two_n];
    }
    
    
    for(i = 0; i < two_n; i++)
    {
    	for(j = 0; j < two_n; j++)
    	{
    		T2[i][j] =  ( ( float( I2[i][j] ) + 0.5 ) * 255.0 ) / ( two_n * two_n ) ;
    		cout<<T2[i][j]<<"   ";
		}
		cout<<endl;
	}
	
	
	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			
		if (  (float ( Imagedata[i][j][0] ) >= 0)  & (float ( Imagedata[i][j][0] ) <= T2[i % two_n][j % two_n] ) )
		{
			Out_image[i][j][0] = (unsigned char)0;

			
		}
		else if ( (float ( Imagedata[i][j][0] ) > T2[i % two_n][j % two_n] ) & (float ( Imagedata[i][j][0] ) < 256 ) )	
		{
			Out_image[i][j][0] = (unsigned char)255;
		}
		}
	}
	
	





		// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Out_image, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
