

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

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
	unsigned char Imagedata[400][400][BytesPerPixel];
    

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 400*400*BytesPerPixel, file);
	fclose(file);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char output[400][400][1];
	int freq[256];
	float prob[256],cdf[256],cdf400[256];
	int cdfround[256];
	int no_pixels = 400*400;
	int i,j,x,k,y;
	float tot =0.0;
		for(i=0;i<400;i++)
		{
			for(j=0;j<400;j++)
			{
				x = int(Imagedata[i][j][0]);
				//cout<<x<<"*****";
				freq[x] = freq[x]+1;
			    
			}
		  
		}
		
		
		for (k=0;k<256;k++)
		{
			//cout<<k<<"=";
			//cout<<freq[k];
			//cout<<"prob="<<prob[k];
			prob[k] = float(freq[k])/float(160000.0);
			tot = tot+prob[k];
			cdf[k] = tot;
			//cout<<"cdf="<<cdf[k];
			cdf400[k] = 255.0*cdf[k];
			//cout<<"cdf*400="<<cdf400[k];
			cdfround[k] = cdf400[k];
			cout<<"cdfround="<<cdfround[k]<<"//";
			
		}
	
	ofstream outfile;
	outfile.open("rose_bright_output_hist.csv");
	for(i=0;i<256;i++)
	{
		    outfile << i << "," << freq[i] << std::endl;

	}
	outfile.close();
	
	for(i=0;i<400;i++)
	{
		for(j=0;j<400;j++)
		{
			for(y=0;y<256;y++)
			{
			if(Imagedata[i][j][0]==y)
			{
				output[i][j][0] = cdfround[y];
			
				}	
			}
			//cout<<output[i][j][0];
		
	}
		
		
	}

	
	
		
		
		
		// Write image data (filename specified by second argument) from image data matrix
	

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output, sizeof(unsigned char), 400*400*1, file);
	fclose(file);

	return 0;
}
