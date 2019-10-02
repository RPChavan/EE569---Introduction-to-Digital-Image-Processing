
  
  
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
	short  two_n = 8;  
	short n = two_n/2;
	short n_bytwo = n/2;
	int I4[4][4];
    int I8[8][8];
	unsigned char Out_image[Row_Size][Column_Size][1];
    float **T8 = new float*[two_n];
    for (i = 0; i < two_n; i++) 
	{
        T8[i] = new float[two_n];
    }


k =0;
	for(i = 0; i<n_bytwo; i++)
	{
		l=0;
		for(j = 0; j<n_bytwo; j++)
			{
			    I4[i][j] = (4*(I2[k][l])) + 1;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}
	
	k=0;
	for(i = 0; i<n_bytwo; i++)
	{
		l=0;
		for(j = n_bytwo; j<n; j++)
			{
			    I4[i][j] = (4*(I2[k][l])) + 2;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}
	
	k=0;
	for(i = n_bytwo; i<n; i++)
	{
		l=0;
		for(j = 0; j<n_bytwo; j++)
			{
			    I4[i][j] = (4*(I2[k][l])) + 3;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	} 

    k=0;
	for(i = n_bytwo; i<n; i++)
	{
		l=0;
		for(j = n_bytwo; j<n; j++)
			{
			    I4[i][j] = (4*(I2[k][l]));
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}

for(i = 0; i < n; i++)
{
	for(j = 0; j < n; j++)
	{
		cout<<I4[i][j]<<"  ";
	}
	cout<<endl;
}
//for I8
k =0;
	for(i = 0; i<n; i++)
	{
		l=0;
		for(j = 0; j<n; j++)
			{
			    I8[i][j] = (4*(I4[k][l])) + 1;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}
	
	k=0;
	for(i = 0; i<n; i++)
	{
		l=0;
		for(j = n; j<two_n; j++)
			{
			    I8[i][j] = (4*(I4[k][l])) + 2;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}
	
	k=0;
	for(i = n; i<two_n; i++)
	{
		l=0;
		for(j = 0; j<n; j++)
			{
			    I8[i][j] = (4*(I4[k][l])) + 3;
			    l++;
			    //return I2n[i][j];
			}
		k++;
	} 

    k=0;
	for(i = n; i<two_n; i++)
	{
		l=0;
		for(j = n; j<two_n; j++)
			{
			    I8[i][j] = (4*(I4[k][l]));
			    l++;
			    //return I2n[i][j];
			}
		k++;
	}

for(i = 0; i < two_n; i++)
{
	for(j = 0; j < two_n; j++)
	{
		cout<<I8[i][j]<<"  ";
	}
	cout<<endl;
}

    
    for(i = 0; i < two_n; i++)
    {
    	for(j = 0; j < two_n; j++)
    	{
    		T8[i][j] =  ( ( float( I8[i][j] ) + 0.5 ) * 255.0 ) / ( two_n * two_n ) ;
    		cout<<T2[i][j]<<"   ";
		}
		cout<<endl;
	}

	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			
		if (  (float ( Imagedata[i][j][0] ) >= 0)  & (float ( Imagedata[i][j][0] ) <= T8[i % two_n][j % two_n] ) )
		{
			Out_image[i][j][0] = (unsigned char)0;
			
		}
		else if ( (float ( Imagedata[i][j][0] ) > T8[i % two_n][j % two_n] ) & (float ( Imagedata[i][j][0] ) < 256 ) )	
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
