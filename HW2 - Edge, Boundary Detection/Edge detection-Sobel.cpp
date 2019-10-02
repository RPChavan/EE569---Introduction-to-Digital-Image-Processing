
  
  


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

    
int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Row_Size = 321;
	int Column_Size  = 481;
	
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
	unsigned char Imagedata[Row_Size][Column_Size][3];


	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Row_Size*Column_Size*3, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//Variable declaration
	unsigned char Gray[Row_Size+4][Column_Size+4][1];
	float xmask[9] = {-1.0/4.0, 0, 1.0/4.0,
	                -2.0/4.0, 0, 2.0/4.0,
				    -1.0/4.0, 0, 1.0/4.0};
	float ymask[9] = { 1.0/4.0, 2.0/4.0, 1.0/4.0,
	                 0, 0, 0,
				    -1.0/4.0,-2.0/4.0,-1.0/4.0};
	short xgradient[Row_Size][Column_Size][1] ;
	short ygradient[Row_Size][Column_Size][1] ;
    unsigned char mag[Row_Size][Column_Size][1];
	unsigned char normalised_mag[Row_Size][Column_Size][1];
	unsigned char normalised_mag_inv[Row_Size][Column_Size][1];
	int i, j, k, l, m, n;
	int varx[9],vary[9];
	int Threshold = 70;
	unsigned char thres_image[Row_Size][Column_Size][1];
	
	for(i = 0; i < Row_Size+4; i++)
	{
		for(j = 0; j <  Column_Size+4; j++)
		{
			Gray[i][j][0] = 0;
		}
	}
	
    //Coverting the color image into a gray scale image
	for(i = 2; i < Row_Size+2; i++)
	{
		for(j = 2; j < Column_Size+2; j++)
		{
			Gray[i][j][0] = (unsigned char)(((int(Imagedata[i-2][j-2][0])+int(Imagedata[i-2][j-2][1])+int(Imagedata[i-2][j-2][2]))/3.0)+0.5) ; 
		}

	}
	//Boundary Extension
	//top rows
	for(i = 0; i < 2; i++)
	{
		for(j = 2; j < Column_Size+2; j++)
        {
	       Gray[i][j][0] = (unsigned char)Gray[i+2][j][0];
	       
	    }
	    //cout<<endl;
   }
    //bottom rows
   	for(i=Row_Size+2;i<Row_Size+4;i++)
	{
		for(j=2;j<Column_Size+2;j++)
        {
	       Gray[i][j][0] = (Gray[i-2][j][0]);
	       
	    }
	    
		cout<<endl;	 
   }
   
   //left columns
   	for(j = 0;j < 2; j++)
	{
		for(i = 2;i < Row_Size+2; i++)
        {
	       Gray[i][j][0] = (unsigned char)Gray[i][j+2][0]; 
	    }
	  
		cout<<endl;	 
   }
	
	//Right Columns
   
	for(j=Column_Size+2;j<Column_Size+4;j++)
	{
		for(i=2;i<Row_Size+2;i++)
        {
	       Gray[i][j][0] = (unsigned char)Gray[i][j-2][0];
	    }		 
   }
   
    //top left corner
   
   for(i = 0; i<2; i++){
   	for (j = 0; j<2; j++){
   		Gray[i][j][0] = Gray[i+2][j+2][0];
	   }
   }
   
    //top right corner
   
    for(i = 0; i<2; i++){
   	for (j = Column_Size+2; j<Column_Size+4; j++){
   		Gray[i][j][0] = (unsigned char)Gray[i+2][j-2][0];
	   }
   }
   
      
   //bottom left
   
    for(i = Row_Size+2; i<Row_Size+4; i++){
   	for (j = 0; j<2; j++){
   		Gray[i][j][0] = (unsigned char)Gray[i-2][j+2][0];
	   }
   }
   
    //bottom right
    for(i = Row_Size+2; i<Row_Size+4; i++){
   	    for (j = Column_Size+2; j<Column_Size+4; j++){
   		Gray[i][j][0] = (unsigned char)Gray[i-2][j-2][0];
	   }
   }
	

	//Finding the x-gradient and y-gradient values
    for(i = 2; i < Row_Size+2; i++)
    {
    	j = 2;
    	for(j = 2; j < Column_Size+2; j++)
		{
			xgradient[i-2][j-2][0] = 0;
			ygradient[i-2][j-2][0] = 0;
			m = 0;
			k = 0;
			l = 0;
		    varx[9] = 0;
		    vary[9] = 0;
			for(k = i-1; k <= i+1; k++)
		    {
		    	for(l = j-1; l <= j+1; l++)
		    	{
		    		varx[m] = float(Gray[k][l][0]) * xmask[m]	;
		    		vary[m] = float(Gray[k][l][0]) * ymask[m]     ;
					m++;
	   			}
			}
	
		for(m = 0; m < 9; m++)
		{
		xgradient[i-2][j-2][0] = xgradient[i-2][j-2][0] + varx[m];
		ygradient[i-2][j-2][0] = ygradient[i-2][j-2][0] + vary[m];
	    }
      }
	}



//Normalising the x-gradient and y-gradient

for(i = 0; i < Row_Size; i++)
{
	for(j = 0; j < Column_Size; j++)
	{
		mag[i][j][0] = (unsigned char)( pow( pow ( float ( xgradient[i][j][0] ), 2 ) + pow ( float ( ygradient[i][j][0] ), 2 ),0.5 ) );
	
	}
}

float minimum = float(mag[0][0][0]);
float maximum = float(mag[0][0][0]);
  for (int i = 0; i < Row_Size; ++i)
    {
        for (int j = 0; j < Column_Size ; ++j)
        {
        	
            if (mag[i][j][0] < minimum)
            {
                minimum = float(mag[i][j][0]);
            }
            if (mag[i][j][0] > maximum)
            {
                maximum = float(mag[i][j][0]);
            }
            
        }
    }
cout<<maximum<<endl;
cout<<minimum<<endl;
for(i = 0; i < Row_Size; i++)
{
	for(j = 0; j < Column_Size; j++)
	{
		normalised_mag[i][j][0] = (unsigned char) (int(((float(mag[i][j][0])-minimum)/(maximum-minimum))*255));
	}
}
minimum = float(normalised_mag[0][0][0]);
 maximum = float(normalised_mag[0][0][0]);
  for (int i = 0; i < Row_Size; ++i)
    {
        for (int j = 0; j < Column_Size ; ++j)
        {
        	
            if (normalised_mag[i][j][0] < minimum)
            {
                minimum = float(normalised_mag[i][j][0]);
            }
            if (normalised_mag[i][j][0] > maximum)
            {
                maximum = float(normalised_mag[i][j][0]);
            }
            
        }
    }
cout<<maximum<<endl;
cout<<minimum<<endl;

//Thresholding cdf method

int x,r;
int freq[256];
float prob[256],cdf[256],cdf255[256];
float tot =0.0;
short ***I_new = new short**[Row_Size];
for (i = 0; i < Row_Size; i++) 
	{
        I_new[i] = new short*[Column_Size];
        for (j = 0; j < Column_Size; j++)
        {
            I_new[i][j] = new short[1];
        }
    }
    
    for(i = 0; i < Row_Size; i++)
    {
    	for(j = 0; j < Column_Size;j++)
    	{
    		I_new[i][j][0] = short(normalised_mag[i][j][0]);
    		
		}
	}
for(r = 0; r < 256; r++)
{
	freq[r] = 0;
}
//thresolding
for(i = 0; i < Row_Size; i++)
{
	for(j = 0; j < Column_Size; j++)
	{
			x = I_new[i][j][0];
			freq[x] = freq[x]+1;
	}
}
cout<<endl;
for(k = 0; k < 256; k++)
{
	prob[k] = float(freq[k])/float(154401.0);
	tot = tot+prob[k];
	cdf[k] = tot;
    cout<<k<<"=   ";
    cout<<cdf[k]<<endl;
}

for(i = 0; i < Row_Size; i++)
{
	for(j = 0; j < Column_Size; j++)
	{
		if(short(normalised_mag[i][j][0]) > 55)
		{
			thres_image[i][j][0] = (unsigned char)0;
		}
		else
		{
			thres_image[i][j][0] = (unsigned char)255;
		}
	}
}

	ofstream outfile;
	outfile.open("sobelpig.csv");
	for(i=0;i<256;i++)
	{
		    outfile << i << "," << cdf[i] << std::endl;

	}
	outfile.close();

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(thres_image, sizeof(unsigned char), Row_Size+4*Column_Size+4*1, file);
	fclose(file);

	return 0;
}
