

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
	unsigned char Imagedata[300][390][BytesPerPixel];


	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), 300*390*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	///Boundary Extension
	int Bou_ext_image[304][394][BytesPerPixel];
	int i,j,k,l;
	unsigned char Imagedata1[300][390][3];
//reflecting top rows
i=2;
	for(k=0;k<2;k++)
	{
		for(j=2;j<10;j++)
        {
	       Bou_ext_image[k][j][0] = Imagedata[i][j-2][0];
	       //cout<<Bou_ext_image[k][j][0]<<"//";
	       
	    }
	    i--; 
		cout<<endl;	 
		cout<<endl;
   }
   cout<<endl;
   cout<<endl;
   
   //refelcting bottom rows
  
   i=299;
	for(k=302;k<304;k++)
	{
		for(j=2;j<10;j++)
        {
	       Bou_ext_image[k][j][0] = Imagedata[i][j-2][0];
	       //cout<<Bou_ext_image[k][j][0]<<"//";
	       
	    }
	    i--; 
		cout<<endl;	 
   }
   //left columns

  j=2;
	for(l=0;l<2;l++)
	{
		for(i=2;i<10;i++)
        {
	       Bou_ext_image[i][l][0] = Imagedata[i-2][j][0];
	      // cout<<Bou_ext_image[i][l][0]<<"//";
	       
	    }
	    j--; 
		cout<<endl;	 
   }
   //right columns
 
j=389;
	for(l=392;l<394;l++)
	{
		for(i=2;i<10;i++)
        {
	       Bou_ext_image[i][l][0] = Imagedata[i-2][j][0];
	       //cout<<Bou_ext_image[i][l][0]<<"//";
	       
	    }
	    j--; 
			 
   }

//corners


Bou_ext_image[0][0][0]=Imagedata[1][1][0];
//cout<<Bou_ext_image[0][0][0]<<endl;
Bou_ext_image[0][1][0]=Imagedata[0][1][0];
//cout<<Bou_ext_image[0][1][0]<<endl;
Bou_ext_image[1][0][0]=Imagedata[1][0][0];
//cout<<Bou_ext_image[1][0][0]<<endl;
Bou_ext_image[1][1][0]=Imagedata[0][0][0];
//cout<<Bou_ext_image[1][1][0]<<endl;
	

Bou_ext_image[0][392][0]=Imagedata[0][388][0];
//cout<<Bou_ext_image[0][392][0]<<endl;
Bou_ext_image[0][393][0]=Imagedata[1][388][0];
//cout<<Bou_ext_image[0][393][0]<<endl;
Bou_ext_image[1][392][0]=Imagedata[0][389][0];
//cout<<Bou_ext_image[1][392][0]<<endl;
Bou_ext_image[1][393][0]=Imagedata[1][389][0];
//cout<<Bou_ext_image[1][393][0]<<endl;


Bou_ext_image[302][0][0]=Imagedata[298][0][0];
//cout<<Bou_ext_image[302][0][0]<<endl;
Bou_ext_image[302][1][0]=Imagedata[299][0][0];
//cout<<Bou_ext_image[302][1][0]<<endl;
Bou_ext_image[303][0][0]=Imagedata[298][1][0];
//cout<<Bou_ext_image[303][0][0]<<endl;
Bou_ext_image[303][1][0]=Imagedata[299][1][0];
//cout<<Bou_ext_image[303][1][0]<<endl;


Bou_ext_image[302][392][0]=Imagedata[299][389][0];
//cout<<Bou_ext_image[302][392][0]<<endl;
Bou_ext_image[302][393][0]=Imagedata[298][389][0];
//cout<<Bou_ext_image[302][393][0]<<endl;
Bou_ext_image[303][392][0]=Imagedata[299][388][0];
//cout<<Bou_ext_image[303][392][0]<<endl;
Bou_ext_image[303][393][0]=Imagedata[298][388][0];
//cout<<Bou_ext_image[303][393][0]<<endl;


//Rest of the image
for(i=2;i<303;i++)
{
	for(j=2;j<393;j++)
	{
		Bou_ext_image[i][j][0]=int(Imagedata[i-2][j-2][0]);
		//cout<<Bou_ext_image[i][j][0]<<"//";
	}
}

	//MHC
	for (i=2;i<302;i++)
	{
	  for (j=2;j<392;j++)
	  {
	  	//Green first-even positions
	  	if(i%2==0 and j%2==0)
	  	{
	  		//Green
		    Imagedata1[i-2][j-2][1] = (unsigned char) Bou_ext_image[i][j][0];
			
			//Blue
	  		Imagedata1[i-2][j-2][2] = (((-1.0*float(Bou_ext_image[i+1][j+1][0])-1.0*float(Bou_ext_image[i+1][j-1][0])-1.0*float(Bou_ext_image[i-1][j+1][0])-1.0*float(Bou_ext_image[i-1][j-1][0])
			                      +5.0*float(Bou_ext_image[i][j][0])+(1.0/2.0)*float(Bou_ext_image[i][j-2][0])+(1.0/2.0)*float(Bou_ext_image[i][j+2][0])-(1.0)*float(Bou_ext_image[i-2][j][0])-(1.0)*float(Bou_ext_image[i+2][j][0])
								  +4.0*float(Bou_ext_image[i+1][j][0])+4.0*float(Bou_ext_image[i-1][j][0]))/8.0)+0.5);
			
	  		
	  		//Red
	  		Imagedata1[i-2][j-2][0] = (((-1.0*float(Bou_ext_image[i+1][j+1][0])-1.0*float(Bou_ext_image[i+1][j-1][0])-1.0*float(Bou_ext_image[i-1][j+1][0])-1.0*float(Bou_ext_image[i-1][j-1][0])
			                      +5.0*float(Bou_ext_image[i][j][0])+(1.0/2.0)*float(Bou_ext_image[i][j-2][0])+(1.0/2.0)*float(Bou_ext_image[i][j+2][0])-(1.0/2.0)*float(Bou_ext_image[i-2][j][0])-(1.0/2.0)*float(Bou_ext_image[i+2][j][0])
								  +4.0*float(Bou_ext_image[i][j+1][0])+4.0*float(Bou_ext_image[i][j-1][0]))/8.0)+0.5);
	  		
	  		
		  }
		  //Green second-odd positions
	  	else if(i%2!=0 and j%2!=0)
	  	{
	  		//Green
	  		Imagedata1[i-2][j-2][1] =  (unsigned char)Bou_ext_image[i][j][0];
	  		
	  		//Blue
	  		Imagedata1[i-2][j-2][2] = (((-1.0*float(Bou_ext_image[i+1][j+1][0])-1.0*float(Bou_ext_image[i+1][j-1][0])-1.0*float(Bou_ext_image[i-1][j+1][0])-1.0*float(Bou_ext_image[i-1][j-1][0])
			                      +5.0*float(Bou_ext_image[i][j][0])+(1/2)*float(Bou_ext_image[i][j-2][0])+(1.0/2.0)*float(Bou_ext_image[i][j+2][0])-(1.0/2.0)*float(Bou_ext_image[i-2][j][0])-(1.0/2.0)*float(Bou_ext_image[i+2][j][0])
								  +4.0*float(Bou_ext_image[i][j+1][0])+4.0*float(Bou_ext_image[i][j-1][0]))/8.0)+0.5);
	  		
	  		//Red
	  		Imagedata1[i-2][j-2][0] = (((-1.0*float(Bou_ext_image[i+1][j+1][0])-1.0*float(Bou_ext_image[i+1][j-1][0])-1.0*float(Bou_ext_image[i-1][j+1][0])-1.0*float(Bou_ext_image[i-1][j-1][0])
			                      +5.0*float(Bou_ext_image[i][j][0])+(1/2)*float(Bou_ext_image[i][j-2][0])+(1.0/2.0)*float(Bou_ext_image[i][j+2][0])-(1.0)*float(Bou_ext_image[i-2][j][0])-(1.0)*float(Bou_ext_image[i+2][j][0])
								  +4.0*float(Bou_ext_image[i+1][j][0])+4.0*float(Bou_ext_image[i-1][j][0]))/8.0)+0.5);
	  		
		  }
		  //Blue
		else if(i%2!=0 and j%2==0)
		{
			//Blue
			Imagedata1[i-2][j-2][2]  = (unsigned char)Bou_ext_image[i][j][0];
			
			//Green
			Imagedata1[i-2][j-2][1] = (((2.0*float(Bou_ext_image[i][j+1][0])+2.0*float(Bou_ext_image[i][j-1][0])+2.0*float(Bou_ext_image[i+1][j][0])+2.0*float(Bou_ext_image[i-1][j][0])+4.0*float(Bou_ext_image[i][j][0])
			                          -float(Bou_ext_image[i][j-2][0])-float(Bou_ext_image[i][j+2][0])-float(Bou_ext_image[i-2][j][0])-float(Bou_ext_image[i+2][j][0]))/8.0)+0.5);
			
			//Red
			Imagedata1[i-2][j-2][0] = (((2.0*float(Bou_ext_image[i+1][j+1][0])+2.0*float(Bou_ext_image[i+1][j-1][0])+2.0*float(Bou_ext_image[i-1][j+1][0])+2.0*float(Bou_ext_image[i-1][j-1][0])
			                      +6.0*float(Bou_ext_image[i][j][0])-(3.0/2.0)*float(Bou_ext_image[i][j-2][0])-(3.0/2.0)*float(Bou_ext_image[i][j+2][0])-(3.0/2.0)*float(Bou_ext_image[i-2][j][0])-(3.0/2.0)*float(Bou_ext_image[i+2][j][0]))/8.0)+0.5);
			
			
		
            
	    }
	    //Red
		else if(i%2==0 and j%2!=0)
		{
			//Red
			Imagedata1[i-2][j-2][0] = (unsigned char)Bou_ext_image[i][j][0];
			
			//Green
			Imagedata1[i-2][j-2][1] =  (((2.0*float(Bou_ext_image[i][j+1][0])+2.0*float(Bou_ext_image[i][j-1][0])+2.0*float(Bou_ext_image[i+1][j][0])+2.0*float(Bou_ext_image[i-1][j][0])+4.0*float(Bou_ext_image[i][j][0])
			                          -float(Bou_ext_image[i][j-2][0])-float(Bou_ext_image[i][j+2][0])-float(Bou_ext_image[i-2][j][0])-float(Bou_ext_image[i+2][j][0]))/8.0)+0.5);
			
			//Blue
		    Imagedata1[i-2][j-2][2] = (((2.0*float(Bou_ext_image[i+1][j+1][0])+2.0*float(Bou_ext_image[i+1][j-1][0])+2.0*float(Bou_ext_image[i-1][j+1][0])+2.0*float(Bou_ext_image[i-1][j-1][0])
			                      +6.0*float(Bou_ext_image[i][j][0])-(3.0/2.0)*float(Bou_ext_image[i][j-2][0])-(3.0/2.0)*float(Bou_ext_image[i][j+2][0])-(3.0/2.0)*float(Bou_ext_image[i-2][j][0])-(3.0/2.0)*float(Bou_ext_image[i+2][j][0]))/8.0)+0.5);
			
		}
		
	  }
}


   




	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata1, sizeof(unsigned char), 300*390*3, file);
	fclose(file);

	return 0;
}
