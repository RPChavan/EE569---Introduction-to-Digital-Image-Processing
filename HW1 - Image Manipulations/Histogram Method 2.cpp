

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
	unsigned char Imagedata[400][400][1];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 400*400*1, file);
	fclose(file);
		///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

int i,j,y,n,x;
int freq[256],cfreq[256];
    short row[160000] ;
    short column[160000];
    short sorted[160000];
    short tab[160000] ;

	n=0;				  
    unsigned char output1[400][400][1];
    for(y=0;y<256;y++)
    {
	for(i=0;i<400;i++)
	{
		for(j=0;j<400;j++)
		{
			if(Imagedata[i][j][0] == y)
			{
				sorted[n] = Imagedata[i][j][0];
				row[n] = i;
				column[n] = j;
				n++;
			}
		}
	}
}


for (i=0;i<256;i++)
{
	for(j=0;j<625;j++)
	{
		sorted[(625*i)+j] = i;
		
		
	}
}
int count=0;
for (i=0;i<160000;i++)
{
  if (sorted[i] == 0)
  {
  	count ++;
  }
}

n = 0;
short temp1, temp2;
short temp3;

short x1,y1;	
for(i=0;i<160000;i++)
	{
		x1 = row[i];
		y1 = column[i];
		output1[x1][y1][0] = (unsigned char)sorted[i];
		
	}
	for(i=0;i<400;i++)
		{
			for(j=0;j<400;j++)
			{
				x = int(output1[i][j][0]);
				//cout<<x<<"*****";
				freq[x] = freq[x]+1;
			    
			}
		  
		}
		cfreq[0] = freq[0];
		 for(x=1;x<256;x++){
		 	cfreq[x] = freq[x]+cfreq[x-1];
		 }
		
	ofstream outfile;
	outfile.open("rose_bright_cumhist.csv");
	for(i=0;i<256;i++)
	{
		    outfile << i << "," << cfreq[i] << std::endl;

	}
	outfile.close();

		// Write image data (filename specified by second argument) from image data matrix
	

if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output1, sizeof(unsigned char), 400*400*1, file);
	fclose(file);

	return 0;


}

