

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

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
	unsigned char output[256][256][BytesPerPixel];
	int i,j;
	int mean_kernel[3][3] = {{1,1,1},
	               {1,1,1},
				   {1,1,1}};
    float avg_mean_kernel = float(1/9.0);
    cout<<avg_mean_kernel;
	for(i=1;i<255;i++)
	{
		for(j=1;j<255;j++)
		{
			//window = {{Imagedata[i-1][j-1],Imagedata[i-1][j],Imagedata[i-1][j+1]},
			//          {Imagedata[i][j-1],Imagedata[i][j],Imagedata[i][j+1]}
			//		  {Imagedata[i+1][j-1],Imagedata[i+1][j],Imagedata[i+1][j+1]}
			//		  }
			    //cout<<Imagedata[i][j][0];
		   		output[i][j][0]=(unsigned char)((avg_mean_kernel)*(float(Imagedata[i-1][j-1][0])+float(Imagedata[i-1][j][0])+float(Imagedata[i-1][j+1][0])+float(Imagedata[i][j-1][0])+float(Imagedata[i][j][0])+float(Imagedata[i][j+1][0])+float(Imagedata[i+1][j-1][0])+float(Imagedata[i+1][j][0])+float(Imagedata[i+1][j+1][0])))/(9/9);
                //cout<<(int)output[i][j][0];
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
