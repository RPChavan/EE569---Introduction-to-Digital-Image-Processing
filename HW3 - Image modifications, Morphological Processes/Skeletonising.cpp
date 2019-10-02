
  
  
  
  
  
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
	int BytesPerPixel =1;
	int Row_Size = 375;
	int Column_Size  = 375;
	
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
	unsigned char Imagedata[Row_Size][Column_Size][BytesPerPixel];


	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//Variable declaration
	short Bou_ext_image[Row_Size+2][Column_Size+2][BytesPerPixel];
	short M_image[Row_Size+2][Column_Size+2][BytesPerPixel];
	short M;
	short P[Row_Size+2][Column_Size+2][BytesPerPixel];
	short G_old[Row_Size+2][Column_Size+2][BytesPerPixel];
	short G_new[Row_Size+2][Column_Size+2][BytesPerPixel];
	unsigned char output_image[Row_Size][Column_Size][BytesPerPixel];
	int i,j,k,l,m,n,t,c;
	short arr1[9];
	int count = 0;
	
	//Boundary Extension
	//top rows
	for(i = 1; i <Row_Size; i++)
	{
		for(j=1;j<Column_Size+1;j++)
        {
	       Bou_ext_image[i][j][0] = int(Imagedata[i][j-1][0])/255;
	       //cout<<Bou_ext_image[i][j][0]<<"    ";
	    }
	    //cout<<endl;
   }
   //bottom rows
	for(i=Row_Size+1;i<Row_Size+2;i++)
	{
		for(j=1;j<Column_Size+1;j++)
        {
	       Bou_ext_image[i][j][0] = int(Imagedata[i-2][j-1][0])/255;
	       //cout<<Bou_ext_image[i][j][0]<<"   "; 
	    }
		//cout<<endl;	 
   } 
   //left columns
   	for(j=0;j<1;j++)
	{
		for(i=1;i<Row_Size+1;i++)
        {
	       Bou_ext_image[i][j][0] = int(Imagedata[i-1][j][0])/255;
	       //cut<<Bou_ext_image[i][j][0]<<"//";
	    }
		//cout<<endl;	 
   }
   //Right Columns
	for(j=Column_Size+1;j<Column_Size+2;j++)
	{
		for(i=1;i<Row_Size+1;i++)
        {
	    Bou_ext_image[i][j][0] = int(Imagedata[i-1][j-2][0])/255;
	       //cout<<Bou_ext_image[i][j][0]<<"//"; 
	    }		 
    }
    //top left corner
   for(i = 0; i<1; i++)
   {
   	for (j = 0; j<1; j++)
	   {
   		Bou_ext_image[i][j][0] = int(Imagedata[i][j][0])/255;
   		//cout<<Bou_ext_image[i][j][0];
	   }
    }
    //top right corner
    for(i = 0; i<1; i++)
	{
   		for (j = Column_Size+1; j<Column_Size+2; j++)
		   {
	   		Bou_ext_image[i][j][0] = int(Imagedata[i][j-2][0])/255;
	   	   //	cout<<Bou_ext_image[i][j][0];
	   }
   }
   
   //bottom left
   
    for(i = Row_Size+1; i<Row_Size+2; i++)
	{
   	for (j = 0; j<1; j++)
	   {
   		Bou_ext_image[i][j][0] = int(Imagedata[i-2][j][0])/255;
   	//	cout<<Bou_ext_image[i][j][0];
	   }
   }
   
    //rest of the image
	for(i=1;i<Row_Size+1;i++)
	{
		for(j=1;j<Column_Size+1;j++)
		{
			Bou_ext_image[i][j][0]=int(Imagedata[i-1][j-1][0])/255;
			//cout<<Bou_ext_image[i][j][0]<<"//";
		}
	}
	
	//Displaying Boundary
for(i = 118; i < 130; i++)
{
	for(j = 103; j < 115; j++)
	{
		//cout<<Bou_ext_image[i][j][0]<<"  ";
	}
	cout<<endl;
}
cout<<"******************************************"<<endl;
	//Initialising the M and P matrix
	for(i = 0; i < Row_Size+2; i++)
	{
		for(j = 0; j < Column_Size+2; j++)
		{
			M_image[i][j][0] = 0;
			P[i][j][0] = 0;
		}
	}
    //Thin Conditional Mark Patterns


std::vector<short> STK41{0,0,1,0,1,1,0,0,1};
std::vector<short> STK42{1,1,1,0,1,0,0,0,0};
std::vector<short> STK43{1,0,0,1,1,0,1,0,0};
std::vector<short> STK44{0,0,0,0,1,0,1,1,1};
                       
std::vector<short> STK61{1,1,1,0,1,1,0,0,0};
std::vector<short> STK62{0,1,1,0,1,1,0,0,1};
std::vector<short> STK63{1,1,1,1,1,0,0,0,0};
std::vector<short> STK64{1,1,0,1,1,0,1,0,0};
std::vector<short> STK65{1,0,0,1,1,0,1,1,0};
std::vector<short> STK66{0,0,0,1,1,0,1,1,1};
std::vector<short> STK67{0,0,0,0,1,1,1,1,1};
std::vector<short> STK68{0,0,1,0,1,1,0,1,1};
			 
std::vector<short> STK71{1,1,1,0,1,1,0,0,1};
std::vector<short> STK72{1,1,1,1,1,0,1,0,0};
std::vector<short> STK73{1,0,0,1,1,0,1,1,1};
std::vector<short> STK74{0,0,1,0,1,1,1,1,1};
			  
std::vector<short> STK81{0,1,1,0,1,1,0,1,1};
std::vector<short> STK82{1,1,1,1,1,1,0,0,0};
std::vector<short> STK83{1,1,0,1,1,0,1,1,0};
std::vector<short> STK84{0,0,0,1,1,1,1,1,1};
              
std::vector<short> STK91{1,1,1,0,1,1,0,1,1};
std::vector<short> STK92{0,1,1,0,1,1,1,1,1};
std::vector<short> STK93{1,1,1,1,1,1,1,0,0};
std::vector<short> STK94{1,1,1,1,1,1,0,0,1};
std::vector<short> STK95{1,1,1,1,1,0,1,1,0};
std::vector<short> STK96{1,1,0,1,1,0,1,1,1};
std::vector<short> STK97{1,0,0,1,1,1,1,1,1};
std::vector<short> STK98{0,0,1,1,1,1,1,1,1};
              
std::vector<short> STK101{1,1,1,0,1,1,1,1,1};
std::vector<short> STK102{1,1,1,1,1,1,1,0,1};
std::vector<short> STK103{1,1,1,1,1,0,1,1,1};
std::vector<short> STK104{1,0,1,1,1,1,1,1,1};

std::vector<short> K111{1,1,1,1,1,1,0,1,1};
std::vector<short> K112{1,1,1,1,1,1,1,1,0};
std::vector<short> K113{1,1,0,1,1,1,1,1,1};
std::vector<short> K114{0,1,1,1,1,1,1,1,1};

int flag0 = 0,flag1 = 1, flag2 = 0;


while(flag1==1)
{
	c = c+1;
	//cout<<c;
	if(flag2 == 1){
		//cout<<"here";
	for(i = 1; i < Row_Size+1; i++)
	{
        for(j = 1; j < Column_Size+1; j++)
	   {
		Bou_ext_image[i][j][0] = G_new[i][j][0]; 
		}
	}
				
	}
			
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
		    	
		    	    arr1[m] = Bou_ext_image[k][l][0];
		    	    //cout<<arr1[m]<<"  ";
					m++;
					
	   			}
	   			//cout<<endl;
			}
		std::vector<short> arr(std::begin(arr1), std::end(arr1));
			if((arr == STK41) or
			(arr == STK42) or
			(arr == STK43) or
			(arr == STK44) or
			(arr == STK61) or
			(arr == STK62) or
			(arr == STK63) or
			(arr == STK64) or
			(arr == STK65) or
			(arr == STK66) or
			(arr == STK67) or
			(arr == STK68) or
			(arr == STK71) or
			(arr == STK72) or
			(arr == STK73) or
			(arr == STK74) or
			(arr == STK81) or
			(arr == STK82) or
			(arr == STK83) or
			(arr == STK84) or
			(arr == STK91) or
			(arr == STK92) or
			(arr == STK93) or
			(arr == STK94) or
			(arr == STK95) or
			(arr == STK96) or
			(arr == STK97) or
			(arr == STK98) or
			(arr == STK101) or
			(arr == STK102) or
			(arr == STK103) or
			(arr == STK104) or
			(arr == K111) or
			(arr == K112) or
			(arr == K113) or
			(arr == K114) )
			{
				M_image[i][j][0]  = 1;
			}
			else
			{
				M_image[i][j][0] = 0;
			}	
      }
      
	} 	
	
//Displaying M

for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(M_image[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}
//cout<<count<<"   ";
count = 0;
//cout<<"****************************"<<endl;	
	//Unconditional Mask Patterns
	for(i = 1; i < Row_Size+1; i++)
    {
		for(j = 1; j < Column_Size+1; j++)
		{
			M = M_image[i][j][0];
			m = 0;
			k = 0;
			l = 0;
				
			for(k = i-1; k <= i+1; k++)
		    {
		    	for(l = j-1; l <= j+1; l++)
		    	{
		    	
		    	    arr1[m] = M_image[k][l][0];
		    	    //cout<<arr1[m]<<"  ";
					m++;
					
	   			}
	   			//cout<<endl;
			}
			
		std::vector<short> arr(std::begin(arr1), std::end(arr1));
		//spur	
		std::vector<short> Spur1{0, 0, 0, 0, M, 0, 0, 0, M};//1
		std::vector<short> Spur2{0, 0, 0, 0, M, 0, M, 0, 0};//2
		std::vector<short> Spur3{0, 0, M, 0, M, 0, 0, 0, 0};//1
		std::vector<short> Spur4{M, 0, 0, 0, M, 0, 0, 0, 0};//2
   		if((arr == Spur1) or
			(arr == Spur2) or
			(arr == Spur3) or
			(arr == Spur4))
			{
   		       	P[i][j][0] = 1;
	   		}
   			else
   			{
   				P[i][j][0] = 0;
   			}	
   		//Single 4-connection		
   		if(P[i][j][0]!= 1)
   		{
   			std::vector<short> Sin_41{0, 0, 0, 0, M, 0, 0, M, 0};//3
			std::vector<short> Sin_42{0, 0, 0, 0, M, M, 0, 0, 0};//4
			std::vector<short> Sin_43{0, 0, 0, M, M, 0, 0, 0, 0};//3
			std::vector<short> Sin_44{0, M, 0, 0, M, 0, 0, 0, 0};//4
   			if((arr == Sin_41) or
			   (arr == Sin_42) or 
			   (arr == Sin_43) or
			   (arr == Sin_44))
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//L corner
		if(P[i][j][0]!= 1)
   		{
   			std::vector<short> L_cor1{0, M, 0, 0, M, M, 0, 0, 0};//3
			std::vector<short> L_cor2{0, M, 0, M, M, 0, 0, 0, 0};//4
			std::vector<short> L_cor3{0, 0, 0, 0, M, M, 0, M, 0};//3
			std::vector<short> L_cor4{0, 0, 0, M, M, 0, 0, M, 0};//4
   			if((arr == L_cor1) or
			   (arr == L_cor2) or 
			   (arr == L_cor3) or
			   (arr == L_cor4))
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
	
		//Corner Cluster and Tee branch
		//0------------------00000
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 0;
    		std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//1-------------------00001
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		
		//2---------------------00010
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//3----------------------00011
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//4----------------------00100
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 0;
    		std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//5------------------00101
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//6------------------00110
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 0;
    		std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//7-------------------111
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 1;
    		std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//8--------------------01000
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//9--------------------01001
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 1;
    		std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//10------------------01010
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//11-------------------01011
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//12-------------------01100
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//13------------------01101
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//14-----------------01110
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//15-----------------01111
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//16-------------10000
	if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//17-----------------10001
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//18-------------------10010
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//19--------------------10011
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//20------------------10100
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//21------------------10101
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//22----------------10110
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//23----------------10111
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//24----------------11000
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//25---------------11001
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//26---------------11010
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//27---------------11011
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 0;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//28-----------------11100
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//29---------------11101
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 0;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if((arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//30-----------------11110
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 0;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//31--------------------11111
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			short D3 = 1;
   			short D4 = 1;
   			short D5 = 1;
   			std::vector<short> Cor_clu1{M, M, D1, M, M, D2, D3, D4, D5};//21
   			std::vector<short> Cor_clu2{D1, D2, D3, D4, M, M, D5, M, M};//21
			std::vector<short> Tee_bran1{D1, M, D2, M, M, M, D3, D4, D5};//22
			std::vector<short> Tee_bran2{D1, M, D2, M, M, D3, D4, M, D5};//23
			std::vector<short> Tee_bran3{D1, D2, D3, M, M, M, D4, M, D5};//24
			std::vector<short> Tee_bran4{D1, M, D2, D3, M, M, D4, M, D5};//25
            if(	(arr == Cor_clu1) or
                (arr == Cor_clu2) or
				(arr == Tee_bran1) or
				(arr == Tee_bran2) or
				(arr == Tee_bran3) or
				(arr == Tee_bran4) )
			 
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		
		//Vee Branch
		//D------000
		short D1 = 0;
   		short D2 = 0;
   		short D3 = 0;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------001
		D1 = 0;
   	    D2 = 0;
   		D3 = 1;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------010
		D1 = 0;
   		D2 = 1;
   		D3 = 0;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------011
		D1 = 0;
   		D2 = 1;
   		D3 = 1;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		//D------100
		D1 = 1;
   		D2 = 0;
   		D3 = 0;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------101
		D1 = 1;
   		D2 = 0;
   		D3 = 1;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------110
		D1 = 1;
   		D2 = 1;
   		D3 = 0;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
   		//D------111
		D1 = 1;
   		D2 = 1;
   		D3 = 1;
		//001
		if(P[i][j][0]!= 1)
   		{
   			
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    
   	    //010
   		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
		//011
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   		//100	
   		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//101
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   	    }
   	    //110
   	    if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//111
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D1, M, D2, M, D3, A, B, C};//30
			std::vector<short> Vee_bran2{M, D1, C, D2, M, B, M, D3, A};//31
			std::vector<short> Vee_bran3{C, B, A, D1, M, D2, M, D3, M};//32
			std::vector<short> Vee_bran4{A, D1, M, B, M, D2, C, D3, M};//33
   			if(	(arr == Vee_bran1) or
				(arr == Vee_bran2) or
				(arr == Vee_bran3) or
				(arr == Vee_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
   		}
   		
	//Diagonal Branch
		//D---------------------00
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 0;
   			std::vector<short> Dia_bran1{D1, M, 0, 0, M, M, M, 0, D2};//34
			std::vector<short> Dia_bran2{0, M, D1, M, M, 0, D2, 0, M};//35
			std::vector<short> Dia_bran3{D1, 0, M, M, M, 0, 0, M, D2};//36
			std::vector<short> Dia_bran4{M, 0, D1, 0, M, M, D2, M, 0};//37
		    if(	(arr == Dia_bran1) or
			(arr == Dia_bran2) or
			(arr == Dia_bran3) or
			(arr == Dia_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//D---------------------01
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 0;
   			short D2 = 1;
   			std::vector<short> Dia_bran1{D1, M, 0, 0, M, M, M, 0, D2};//34
			std::vector<short> Dia_bran2{0, M, D1, M, M, 0, D2, 0, M};//35
			std::vector<short> Dia_bran3{D1, 0, M, M, M, 0, 0, M, D2};//36
			std::vector<short> Dia_bran4{M, 0, D1, 0, M, M, D2, M, 0};//37
		    if(	(arr == Dia_bran1) or
			(arr == Dia_bran2) or
			(arr == Dia_bran3) or
			(arr == Dia_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//D---------------------10
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 0;
   			std::vector<short> Dia_bran1{D1, M, 0, 0, M, M, M, 0, D2};//34
			std::vector<short> Dia_bran2{0, M, D1, M, M, 0, D2, 0, M};//35
			std::vector<short> Dia_bran3{D1, 0, M, M, M, 0, 0, M, D2};//36
			std::vector<short> Dia_bran4{M, 0, D1, 0, M, M, D2, M, 0};//37
		    if(	(arr == Dia_bran1) or
			(arr == Dia_bran2) or
			(arr == Dia_bran3) or
			(arr == Dia_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//D---------------------11
		if(P[i][j][0]!= 1)
   		{
   			short D1 = 1;
   			short D2 = 1;
   			std::vector<short> Dia_bran1{D1, M, 0, 0, M, M, M, 0, D2};//34
			std::vector<short> Dia_bran2{0, M, D1, M, M, 0, D2, 0, M};//35
			std::vector<short> Dia_bran3{D1, 0, M, M, M, 0, 0, M, D2};//36
			std::vector<short> Dia_bran4{M, 0, D1, 0, M, M, D2, M, 0};//37
		    if(	(arr == Dia_bran1) or
			(arr == Dia_bran2) or
			(arr == Dia_bran3) or
			(arr == Dia_bran4) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		
		G_new[i][j][0] = ((Bou_ext_image[i][j][0]) && (!(M_image[i][j][0]) || (P[i][j][0])));

		}
	}
	
				
/*	//Displaying P

for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(P[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}			
//cout<<count<<"   ";
count = 0;	
for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(G_new[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}			
//cout<<count;

*/
flag0 =0;
flag2 = 1;
if(flag2 == 1)
{
	for(i = 1; i < Row_Size+1; i++)
	{
		for(j = 1; j < Column_Size+1; j++)
		{
			if(G_old[i][j][0] == G_new[i][j][0])
			{
				flag0 += 1;
			}
		G_old[i][j][0] = G_new[i][j][0]; 
		output_image[i-1][j-1][0] = (unsigned char)(G_new[i][j][0]*255);
        
		}
    }
		if (flag0 == 375*375)
		{
			flag1 = 0;
		}
}
}	

count = 0;
for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(M_image[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}
cout<<count<<endl;;
count = 0;
for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(P[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}
cout<<count<<endl;
count = 0;
for(i = 1; i < Row_Size+1; i++)
{
	for(j = 1; j < Column_Size+1; j++)
	{
		if(G_new[i][j][0] == 1)
		{
			count = count+1;
		}
	}
}
cout<<count<<endl;;
//Bridging
short X[9];
short x, X0, X1, X2, X3, X4, X5, X6, X7, L1, L2, L3, L4, Pq, P1, P2, P3, P4, P5, P6;
unsigned char final1_image[Row_Size][Column_Size][1];
short final_image;
for(i = 1; i < Row_Size+1; i++)
{
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
		    	
		    	    X[m] = G_new[k][l][0];
		    	    //cout<<arr1[m]<<"  ";
					m++;
					
	   			}
	   			//cout<<endl;
			}
			X3 = X[0];
			X2 = X[1];
			X1 = X[2];
			X4 = X[3];
			x = X[4];
			X0 = X[5];
			X5 = X[6];
			X6 = X[7];
			X7 = X[8];
			L1 = ( !x & !X0 & X1 & !X2 & X3 & !X4 & !X5 & !X6 & !X7 );
			L2 = ( !x & !X0 & !X1 & !X2 & X3 & !X4 & X5 & !X6 & !X7 );
			L3 = ( !x & !X0 & !X1 & !X2 & !X3 & !X4 & X5 & !X6 & X7 );
			L4 = ( !x & !X0 & X1 & !X2 & !X3 & !X4 & !X5 & !X6 & X7 );
			Pq = L1 | L2 | L3 | L4;
			P1 = ( !X2 & !X6 & ( X3 | X4 | X5 ) & ( X0 | X1 | X7 ) & !Pq );
			P2 = ( !X0 & !X4 & ( X1 | X2 | X3 ) & ( X5 | X6 | X7 ) & !Pq );
			P3 = ( !X0 & !X6 & X7 & ( X2 | X3 | X4 ) );
			P4 = ( !X0 & !X2 & X1 & ( X4 | X5 | X6 ) );
			P5 = ( !X2 & !X4 & X3 & ( X0 | X6 | X7 ) );
			P6 = ( !X4 & !X6 & X5 & ( X0 | X1 | X2 ) );
			final_image =  (( x | ( P1 | P2 | P3 | P4 | P5 | P6 ) ));
			final1_image[i-1][j-1][0] = (unsigned char)(final_image*255);
		}
	}

count = 0;
for(i = 0; i < Row_Size; i++)
{
	for(j = 0; j < Column_Size; j++)
	{
		if(int(final1_image[i][j][0]) == 1)
		{
			count = count+1;
		}
	}
}
cout<<count<<endl;


			// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output_image, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
