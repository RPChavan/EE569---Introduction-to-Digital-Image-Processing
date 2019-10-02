
  
  
  
  
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

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Row_Size = 500;
	int Column_Size  = 690;
	
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
	int i, j, k;
	int x,r;
	unsigned char output_image[Row_Size][Column_Size][BytesPerPixel];

    short ***Gray = new short**[Row_Size+2];
	for (i = 0; i < Row_Size+2; i++) 
	{
        Gray[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            Gray[i][j] = new short[1];
        }
    }
    

    short ***output_image1 = new short**[Row_Size+2];

	for (i = 0; i < Row_Size+2; i++) 
	{
        output_image1[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            output_image1[i][j] = new short[1];
        }
    }
    short ***output_image2 = new short**[Row_Size+2];

    for (i = 0; i < Row_Size+2; i++) 
	{
        output_image2[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            output_image2[i][j] = new short[1];
        }
    }
    short ***output_image3 = new short**[Row_Size+2];

    for (i = 0; i < Row_Size+2; i++) 
	{
        output_image3[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            output_image3[i][j] = new short[1];
        }
    }

	
	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			Gray[i][j][0] = ( ( int( Imagedata[i][j][0] ) + int( Imagedata[i][j][1] ) + int( Imagedata[i][j][2] ) ) / 3 );
		}
	}
	
	/*for(r = 0; r < 256; r++)
    {
		freq[r] = 0;
	}
	for(i = 0; i < Row_Size; i++)
    {
	    for(j = 0; j < Column_Size; j++)
	    {   
			x = int(GrayImage[i][j][0]);
			freq[x] = freq[x]+1;
	    }
	}
    cout<<endl;
	for(k = 0; k < 256; k++)
	{
		prob[k] = float(freq[k])/float(345000.0);
		tot = tot+prob[k];
		cdf[k] = tot;
	    cout<<k<<"=   ";
	    cout<<freq[k]<<"=  ";
	    cout<<cdf[k]<<endl;
	}*/


	int l,m,n,t,c;
	short arr1[9];
	int count = 0;
	short ***Bou_ext_image = new short**[Row_Size+2];
	for (i = 0; i < Row_Size+2; i++) 
	{
        Bou_ext_image[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            Bou_ext_image[i][j] = new short[1];
        }
    }

	short ***G_new = new short**[Row_Size+2];
	for (i = 0; i < Row_Size+2; i++) 
	{
        G_new[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            G_new[i][j] = new short[1];
        }
    }
    
    short ***G_new2 = new short**[Row_Size+2];
	for (i = 0; i < Row_Size+2; i++) 
	{
        G_new2[i] = new short*[Column_Size+2];
        for (j = 0; j < Column_Size+2; j++)
        {
            G_new2[i][j] = new short[1];
        }
    }


  
    
	//Boundary Extension
	//top rows
	for(i = 1; i <Row_Size; i++)
	{
		for(j=1;j<Column_Size+1;j++)
        {
	       Bou_ext_image[i][j][0] = int(Gray[i][j-1][0]);
	       //cout<<Bou_ext_image[i][j][0]<<"    ";
	    }
	    //cout<<endl;
   }
   //bottom rows
	for(i=Row_Size+1;i<Row_Size+2;i++)
	{
		for(j=1;j<Column_Size+1;j++)
        {
	       Bou_ext_image[i][j][0] = int(Gray[i-2][j-1][0]);
	       //cout<<Bou_ext_image[i][j][0]<<"   "; 
	    }
		//cout<<endl;	 
   } 
   //left columns
   	for(j=0;j<1;j++)
	{
		for(i=1;i<Row_Size+1;i++)
        {
	       Bou_ext_image[i][j][0] = int(Gray[i-1][j][0]);
	       //cut<<Bou_ext_image[i][j][0]<<"//";
	    }
		//cout<<endl;	 
   }
   //Right Columns
	for(j=Column_Size+1;j<Column_Size+2;j++)
	{
		for(i=1;i<Row_Size+1;i++)
        {
	    Bou_ext_image[i][j][0] = int(Gray[i-1][j-2][0]);
	       //cout<<Bou_ext_image[i][j][0]<<"//"; 
	    }		 
    }
    //top left corner
   for(i = 0; i<1; i++)
   {
   	for (j = 0; j<1; j++)
	   {
   		Bou_ext_image[i][j][0] = int(Gray[i][j][0]);
   		//cout<<Bou_ext_image[i][j][0];
	   }
    }
    //top right corner
    for(i = 0; i<1; i++)
	{
   		for (j = Column_Size+1; j<Column_Size+2; j++)
		   {
	   		Bou_ext_image[i][j][0] = int(Gray[i][j-2][0]);
	   	   //	cout<<Bou_ext_image[i][j][0];
	   }
   }
   
   //bottom left
   
    for(i = Row_Size+1; i<Row_Size+2; i++)
	{
   	for (j = 0; j<1; j++)
	   {
   		Bou_ext_image[i][j][0] = int(Gray[i-2][j][0]);
   	//	cout<<Bou_ext_image[i][j][0];
	   }
   }
   
    //rest of the image
	for(i=1;i<Row_Size+1;i++)
	{
		for(j=1;j<Column_Size+1;j++)
		{
			Bou_ext_image[i][j][0]=int(Gray[i-1][j-1][0]);
			//cout<<Bou_ext_image[i][j][0]<<"//";
		}
	}
	
		
	for( i = 1; i < Row_Size+1; i++)
	{
		for(j = 1; j < Column_Size+1; j++)
		{
			if(((int(Bou_ext_image[i][j][0]) >= 65) and (int(Bou_ext_image[i][j][0])) <= 76) )
			{
				output_image1[i][j][0] = 0;
			}
			else
			{
				output_image1[i][j][0] = 1;
			}
		}
	}
	cout<<"hhhh";
	cout<<"hhhhhhhhhhhh";
	cout<<"hhhhhhhhh";
	for( i = 1; i < Row_Size+1; i++)
	{
		for(j = 1; j < Column_Size+1; j++)
		{
			if(int(Imagedata[i-1][j-1][2]) > 30)
			{
				output_image2[i][j][0] = 0;
			}
			else
			{
				output_image2[i][j][0] = 1;
			}
		}
	}
	for( i = 1; i < Row_Size+1; i++)
	{
		for(j = 1; j < Column_Size+1; j++)
		{
			
				output_image3[i][j][0] = (output_image1[i][j][0] || output_image2[i][j][0]);
			
		}
	}
	
    //Hit mask Pattern

std::vector<short> Hit{1,1,1,1,1,1,1,1,1};
std::vector<short>Hit1{0,0,0,0,0,
                       0,0,0,0,0,0,
					   0,0,0,0,0,0,
					   0,0,0,0,0,0,
					   0,0,0,0,0,0};

    for(i = 1; i < Row_Size+1; i++)
    {
    	
    	j = 1;
    	for(j = 1; j < Column_Size+1; j++)
		{
			m = 0;
			k = 0;
			l = 0;
		    //arr[9] = 0;
	
			for(k = i-1; k <= i+1; k++)
		    {
		    	for(l = j-1; l <= j+1; l++)
		    	{
		    	
		    	    arr1[m] = output_image3[k][l][0];
		    	    //cout<<arr1[m]<<"  ";
					m++;
					
	   			}
	   			//cout<<endl;
			}
		std::vector<short> arr(std::begin(arr1), std::end(arr1));
			if((arr == Hit) )
			
			
			{
				G_new[i][j][0]  = 1;
			}	
			else
			{
				G_new[i][j][0] = 0;
			}
           	//*output_image[i-1][j-1][0] = (unsigned char)(G_new[i][j][0]*255);

 		 }
	} 	
	short arr2[25];
	for(i = 2; i < Row_Size-2; i++)
    {
    	
    	for(j = 2; j < Column_Size-2; j++)
		{
			m = 0;
			k = 0;
			l = 0;
		    //arr[9] = 0;
	
			for(k = i-2; k <= i+2; k++)
		    {
		    	for(l = j-2; l <= j+2; l++)
		    	{
		    	
		    	    arr2[m] = G_new[k][l][0];
		    	    //cout<<arr1[m]<<"  ";
					m++;
					
	   			}
	   			//cout<<endl;
			}
		std::vector<short> arr3(std::begin(arr2), std::end(arr2));
		count = 0;
		for(t = 0; t < 25;t++)
		{
			if((arr3[t] == 0))
			{
				count = count+1;
			}
		}
			if(count > 17 )
			
			{
				G_new2[i][j][0]  = 0;
			}	
			else
			{
				G_new2[i][j][0] = 1;
			}
           	output_image[i-1][j-1][0] = (unsigned char)(G_new2[i][j][0]*255);

 		 }
	}
	for (i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] output_image1[i][j];

		delete[] output_image1[i];
	}
	delete[] output_image1; 	

	for ( i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] output_image2[i][j];

		delete[] output_image2[i];
	}
	delete[] output_image2; 
	
	for ( i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] output_image3[i][j];

		delete[] output_image3[i];
	}
	delete[] output_image3; 
	
	for ( i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] Bou_ext_image[i][j];

		delete[] Bou_ext_image[i];
	}
	delete[] Bou_ext_image; 
	
	for ( i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] G_new[i][j];

		delete[] G_new[i];
	}
	delete[] G_new;
	
	for ( i = 0; i < Row_Size; i++)
	{
		for ( j = 0; j < Column_Size; j++)
			delete[] G_new2[i][j];

		delete[] G_new2[i];
	}
	delete[] G_new2;
	
	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output_image, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
