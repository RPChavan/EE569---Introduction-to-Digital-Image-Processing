

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
		cout << "program_name input_image.raw output1_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
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
	unsigned char Imagedata[256][256][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 256*256*3, file);
	fclose(file);
	
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char R[256][256][1];
	unsigned char G[256][256][1];
	unsigned char B[256][256][1];
	unsigned char output[256][256][1];
	int i,j;
	for(i=0;i<256;i++){
		for(j=0;j<256;j++){
			R[i][j][0] = Imagedata[i][j][0];
			G[i][j][0] = Imagedata[i][j][1];
			B[i][j][0] = Imagedata[i][j][2];
		}
	}
	
for(i=0;i<256;i++){
		for(j=0;j<256;j++){
			output[i][j][0] = 	B[i][j][0];
	
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
