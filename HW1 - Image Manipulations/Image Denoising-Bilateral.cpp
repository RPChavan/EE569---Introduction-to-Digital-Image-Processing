
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

int i,j,k,l;
	float sum_weights = 0;
	float sigmac = 12.0;
	float sigmas = 20.0;
	float w	;
	int I;
	unsigned char output[256][256][BytesPerPixel];

	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			sum_weights = 0;
				w = 0;
				I = 0;
			for(k=i-2;k<=i+2;k++)
			{
				
				for(l=j-2;l<=j+2;l++)
				{
                w = exp(-((pow(float(i-k),2.0)+pow(float(j-l),2.0))/(2.0*pow(sigmac,2.0)))-(pow((float(Imagedata[i][j][0])-float(Imagedata[k][l][0])),2)/(2.0*pow(sigmas,2.0))));
				//cout<<w<<endl;	
				sum_weights = sum_weights+w;
			    //cout<<sum_weights<<endl;
				I = I+(float(Imagedata[k][l][0])*float(w));
				//cout<<I<<endl;
				}
				
			}
			//cout<<sum_weights<<endl;
			//cout<<endl<<I;
		
		output[i][j][0] = (unsigned char)(float(I)/float(sum_weights));
	
		}
	 } 
		for(i=0;i<256;i++){
			for(j=0;j<256;j++){
				//cout<<int(output[i][j][0])<<endl;
			}
		}
	
		
		
		







		
		
	// Write image data (filename specified by second argument) from image data matrix
	

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output, sizeof(unsigned char), 256*256*1, file);
	fclose(file);

	return 0;
}
