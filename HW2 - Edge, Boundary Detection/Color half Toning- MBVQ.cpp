




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

int Quad_number( int R, int  G, int B )
{
	int Quadrant_no;
	//pyramid mbvq
	/* 1 - CMYW
	   2 - MYGC
	   3 - RGMY
	   4 - KRGB
	   5 - RGBM
	   6 - CMGB*/
				if (  ( R + G ) > 255 )
				{
				    if ( ( G + B ) > 255 )	
					{
						if ( ( R + G + B ) > 510 )
						{
							Quadrant_no = 1;	
						}
						else
						{
							Quadrant_no = 2;
						}
				    }
				    else
				    {
				    	Quadrant_no = 3;
					}
		    	}
				else
				{
				    if (!(( G + B ) > 255 ))
				    {
				    	if (!(( R + G + B) > 255 ))
				    	{
				    		Quadrant_no = 4;
						}
						else
						{
							Quadrant_no = 5;
						}
				    }
					else
					{
						Quadrant_no = 6;
					}		
	    }
	    
	    return Quadrant_no;
}

	//Nearest vertex
	int Vertex_no(float R, float G, float B, int Quadrant_no)
	{
		int vertex = 0;

/* C = 1
   Y = 2
   M = 3
   K = 4
   R = 5
   G = 6
   B = 7
   W = 8*/
//No.1 for CMYW
    if (Quadrant_no == 1)
    {
        vertex = 8;
        if (B < 0.5)
        {
            if (B <= R)
            {
                if (B <= G)
                {
                    vertex = 2;
                }
            }
        }
        if (G < 0.5)
        {
            if (G <= B)
            {
                if (G <= R)
                {
                    vertex = 3;
                }
            }
        }
        if (R < 0.5)
        {
            if (R <= B)
            {
                if (R <= G)
                {
                    vertex = 1;
                }
            }
        }
    }
// No.2 for MYGC
    if (Quadrant_no == 2)
    {
        vertex = 3; 
        if (G >= B)
        {
            if (R >= B)
            {
                if (R >= 0.5)
                {
                    vertex = 2;
                }
                else
                {
                    vertex = 6;
                }
            }
        }
        if (G >= R)
        {
            if (B >= R)
            {
                if (B >= 0.5)
                {
                    vertex = 1;
				}
                else
                {
                    vertex = 6;
                }
            }
        }
    }

//No.3 for RGMY
    if (Quadrant_no == 3)
    {
        if (B > 0.5)
        {
            if (R > 0.5)
            {
                if (B >= G)
                {
                    vertex = 3;
                }
                else
                {
                    vertex = 2;
                }
            }
            else
            {
                if (G > B + R)
                {
                    vertex = 6;
                }
                else 
                {
                    vertex = 3;
                }
            }
        }
        else
        {
            if (R >= 0.5)
            {
                if (G >= 0.5)
                {
                    vertex = 2;
                }
                else
                {
                    vertex = 5;
                }
            }
            else
			{
                if (R >= G)
                {
                    vertex = 5;
                }
                else
                {
                    vertex = 6;
                }
            }
        }
	}

// No.4 for KRGB
/* C = 1
   Y = 2
   M = 3
   K = 4
   R = 5
   G = 6
   B = 7
   W = 8*/
    if (Quadrant_no == 4)
    {
        vertex = 4;
        if (B > 0.5)
        {
            if (B >= R)
            {
                if (B >= G)
                {
                    vertex = 7 ;
                }
            }
        }
        if (G > 0.5)
        {
            if (G >= B)
            {
                if (G >= R)
                {
                    vertex = 6;
                }
            }
        }
        if (R > 0.5)
        {
            if (R >= B)
            {
                if (R >= G)
                {
                    vertex = 5;
                }
            } 
        }
    }
	/* C = 1
   Y = 2
   M = 3
   K = 4
   R = 5
   G = 6
   B = 7
   W = 8*/
	
	// No.5 for RGBM
    if (Quadrant_no == 5)
    {
        vertex = 6;
        if (R > G)
        {
            if (R >= B)
            {
                if (B < 0.5)
                {
                    vertex = 5;
                }
                else
                {
                    vertex = 3;
                }
            }
        }
        if (B > G)
        {
            if (B >= R)
            {
                if (R < 0.5)
                {
                    vertex = 7;
                }
                else
                {
                    vertex = 3;
                }
            }
        }
    }
/* C = 1
   Y = 2
   M = 3
   K = 4
   R = 5
   G = 6
   B = 7
   W = 8*/
    // No.6 for CMGB
    if (Quadrant_no == 6)
    {
        if (B > 0.5)
        {
            if ( R > 0.5)
            {
                if (G >= R)
                {
                    vertex = 1;
                }
                else
                {
                    vertex = 3;
                }
            }
            else
            {
                if (G > 0.5)
                {
                     vertex = 1;
                }
                else
                {
                    vertex = 7;
                }
            }
        }
        else
        {
            if ( R > 0.5)
            {
                if (R - G + B >= 0.5)
                {
                    vertex = 3;
                }
                else
                {
                    vertex = 6;
                }
            }
            else
            {
                if (G >= B)
                {
                    vertex = 6;
                }
                else
                {
                    vertex = 7;
                }
            }
       }
    }
    return vertex;
	}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Row_Size = 375;
	int Column_Size  = 500;
	
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
	int i, j, Quadrant_no, vertex, k, l, m;
	float b1, b2, b3, e1, e2, e3;
	float R, G, B, R1, G1, B1;
	float ***I_new = new float**[Row_Size];
	float h_arr[9]    = {0.0,       0.0,     0.0   ,
	                     0.0,       0.0,   7.0/16.0,
				         3.0/16.0,5.0/16.0,1.0/16.0};
	unsigned char Output_Image[Row_Size][Column_Size][3];
	
	
    for (i = 0; i < Row_Size; i++) 
	{
        I_new[i] = new float*[Column_Size];
        for (j = 0; j < Column_Size; j++)
        {
            I_new[i][j] = new float[3];
        }
    }
    
    for(i = 0; i < Row_Size; i++)
    {
    	for(j = 0; j < Column_Size;j++)
    	{
    		I_new[i][j][0] = float(Imagedata[i][j][0]);
    		I_new[i][j][1] = float(Imagedata[i][j][1]);
    		I_new[i][j][2] = float(Imagedata[i][j][2]);
		}
	}
	
	//For C channel
	
	for(i = 1; i < Row_Size-1; i++)
	{
		if(i % 2 == 0)
		{
		for(j = 1; j < Column_Size-1; j++)
		{
				R1 = float ( I_new[i][j][0]) ;
				G1 = float ( I_new[i][j][1]) ;
				B1 = float ( I_new[i][j][2]) ;
				//cout<<R1<<"    ";
				//cout<<G1<<"   ";
				//cout<<B1<<"   "<<endl;
			    Quadrant_no = Quad_number(R1,G1,B1);
			    R = R1/255.0 ;
				G = G1/255.0 ;
				B = B1/255.0 ;
				//cout<<R<<"   ";
				//cout<<G<<"   ";
				//cout<<B<<"   "<<endl;
				vertex = Vertex_no(R,G,B,Quadrant_no);
				
				
				switch(vertex)
				{
					case 1:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 255;
						break;
					case 2:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 0;
						break;
					case 3:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 255;
						break;
					case 4:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 0;
						break;
					case 5:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 0;
						break;
					case 6:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 0;
						break;
					case 7:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 255;
						break;
					case 8:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 255;
						break;
				}
			b1 = I_new[i][j][0];
		    b2 = I_new[i][j][1];
		    b3 = I_new[i][j][2];
		    //cout<<b1<<"   ";
		    //cout<<b2<<"   ";
		    //cout<<b3<<"   "<<endl;
			//cout<<f[i][j][0]<<endl;;
			e1 = R1- b1;
			e2 = G1 - b2;
			e3 = B1 - b3;
			//cout<<e1<<"  ";
			//cout<<e2<<"  ";
			//cout<<e3<<"  "<<endl;
			//cout<<e<<endl;
			m = 0;
			for(k = i-1; k <= i+1; k++)
			{
				for(l = j-1; l <= j+1; l++)
				{
					//cout<<I_new[k][l][0]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e1<<"   ";
					I_new[k][l][0] = I_new[k][l][0] + h_arr[m]*e1;
					//cout<<I_new[k][l][0]<<"    ";					
				
					
					//cout<<I_new[k][l][1]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e2<<"   ";
					I_new[k][l][1] = I_new[k][l][1] + h_arr[m]*e2;
					//cout<<I_new[k][l][1]<<"    ";					
					
					
					//cout<<I_new[k][l][2]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e3<<"   ";
					I_new[k][l][2] = I_new[k][l][2] + h_arr[m]*e3;
					//cout<<I_new[k][l][2]<<"    ";					
					m++;
					
				}
				
			}
		
					}
				}
		else
		{
			for(j = Column_Size-2; j >= 1; j--)
			{
			    R1 = float ( I_new[i][j][0]) ;
				G1 = float ( I_new[i][j][1]) ;
				B1 = float ( I_new[i][j][2]) ;
				//cout<<R1<<"   ";
				//cout<<G1<<"   ";
				//cout<<B1<<"   "<<endl;
			    Quadrant_no = Quad_number(R1,G1,B1);
			    R = R1/255.0 ;
				G = G1/255.0 ;
				B = B1/255.0 ;
				//cout<<R<<"   ";
				//cout<<G<<"   ";
				//cout<<B<<"   "<<endl;
				vertex = Vertex_no(R,G,B,Quadrant_no);
				
				
				switch(vertex)
				{
					case 1:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 255;
						break;
					case 2:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 0;
						break;
					case 3:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 255;
						break;
					case 4:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 0;
						break;
					case 5:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 0;
						break;
					case 6:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 0;
						break;
					case 7:
						I_new[i][j][0] = 0;
						I_new[i][j][1] = 0;
						I_new[i][j][2] = 255;
						break;
					case 8:
						I_new[i][j][0] = 255;
						I_new[i][j][1] = 255;
						I_new[i][j][2] = 255;
						break;
				}
			b1 = I_new[i][j][0];
		    b2 = I_new[i][j][1];
		    b3 = I_new[i][j][2];
		    //cout<<b1<<"   ";
		    //cout<<b2<<"   ";
		    //cout<<b3<<"   "<<endl;
			//cout<<f[i][j][0]<<endl;;
			e1 = R1- b1;
			e2 = G1 - b2;
			e3 = B1 - b3;
			//cout<<e1<<"  ";
			//cout<<e2<<"  ";
			//cout<<e3<<"  "<<endl;
			//cout<<e<<endl;
			m = 0;
			for(k = i-1; k <= i+1; k++)
			{
				for(l = j+1; l >= j-1; l--)
				{
					//cout<<I_new[k][l][0]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e1<<"   ";
					I_new[k][l][0] = I_new[k][l][0] + h_arr[m]*e1;
					//cout<<I_new[k][l][0]<<"    ";					
				
					
					//cout<<I_new[k][l][1]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e2<<"   ";
					I_new[k][l][1] = I_new[k][l][1] + h_arr[m]*e2;
					//cout<<I_new[k][l][1]<<"    ";					
					
					
					//cout<<I_new[k][l][2]<<"   ";
					//cout<<h_arr[m]<<"   ";
					//cout<<e3<<"   ";
					I_new[k][l][2] = I_new[k][l][2] + h_arr[m]*e3;
					//cout<<I_new[k][l][2]<<"    ";					
					m++;		
			}
		}
		
	}
	
}
}
/*cout<<Quadrant_no<<"   ";			
cout<<vertex;*/

	for(i = 0; i < Row_Size; i++)
	{
		for(j = 0; j < Column_Size; j++)
		{
			//cout<<f[i][j][0]<<"    ";
			Output_Image[i][j][0] = (unsigned char)(I_new[i][j][0]);
			Output_Image[i][j][1] = (unsigned char)(I_new[i][j][1]);
			Output_Image[i][j][2] = (unsigned char)(I_new[i][j][2]);
		}
		//cout<<endl;
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Output_Image, sizeof(unsigned char), Row_Size*Column_Size*3, file);
	fclose(file);

	return 0;
}
