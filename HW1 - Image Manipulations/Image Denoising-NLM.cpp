

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
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
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[256][256][BytesPerPixel];
    

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 256*256*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

int i,j,k,l,n1,n2;
	float sum_f = 0;
	float F,G;
	float a = 12;
	float h = 20;
	int In,I;
	unsigned char output[256][256][BytesPerPixel];

	for(i=0;i<256;i++)
	{
		//cout<<"inside i";
		for(j=0;j<256;j++)
		{
			//cout<<"inside j";
			sum_f = 0;
				F = 0;
				I = 0;
			for(k=i-3;k<=i+3;k++)
			{
				
				for(l=j-3;l<=j+3;l++)
				{
					G = 0;
					In = 0;
				 for(n1=k-1;n1<=k+1;n1++)
				 {
				 	
				 	for(n2=l-1;n2<=l+1;n2++)
					 {
				 		
				 		G = (exp(-(((pow(float(n1),2.0)+pow(float(n2),2.0)))/(2.0*pow(float(a),2.0)))))/((sqrt(2.0*3.1416))*float(a));
				 		In = In + (G*(pow(float(Imagedata[i-n1][j-n2][0])-float(Imagedata[k-n1][l-n2][0]),2.0)));
				 		//					F = exp(-(float(In)/pow(float(h),2.0)));

					 } 
				  }	
					F = exp(-(float(In)/pow(float(h),2.0)));
					sum_f = sum_f + F;
					I = I+(float(Imagedata[k][l][0])*float(F));
				}
			}
			output[i][j][0] = (float(I)/float(sum_f));
			}
		}
					
	
				
					
					
					
					
					
					
					
					
         
	
	
		
	// Write image data (filename specified by second argument) from image data matrix
	

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output, sizeof(unsigned char), 256*256*1, file);
	fclose(file);
	cout<<"adsfasdf";
	return 0;
}

