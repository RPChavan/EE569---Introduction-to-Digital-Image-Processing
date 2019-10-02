
  
  
  
  
  
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
             
std::vector<short> ST51{1,1,0,0,1,1,0,0,0};
std::vector<short> ST52{0,1,0,0,1,1,0,0,1};
std::vector<short> ST53{0,1,1,1,1,0,0,0,0};
std::vector<short> ST54{0,0,1,0,1,1,0,1,0};           
std::vector<short> ST55{0,1,1,0,1,1,0,0,0};
std::vector<short> ST56{1,1,0,1,1,0,0,0,0};
std::vector<short> ST57{0,0,0,1,1,0,1,1,0};
std::vector<short> ST58{0,0,0,0,1,1,0,1,1};
            
std::vector<short> ST61{1,1,0,0,1,1,0,0,1};
std::vector<short> ST62{0,1,1,1,1,0,1,0,0};
             
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
			(arr == ST51) or
			(arr == ST52) or
			(arr == ST53) or
			(arr == ST54) or
			(arr == ST55) or
			(arr == ST56) or
			(arr == ST57) or
			(arr == ST58) or
			(arr == ST61) or
			(arr == ST62) or
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
			(arr == STK104) )
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
		std::vector<short> Spur1{0, 0, M, 0, M, 0, 0, 0, 0};//1
		std::vector<short> Spur2{M, 0, 0, 0, M, 0, 0, 0, 0};//2
   		if((arr == Spur1) or
			(arr == Spur2))
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
   			if((arr == Sin_41) or
			   (arr == Sin_42))
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//L cluster
		if(P[i][j][0]!= 1)
   		{
   			std::vector<short> Lclust_1{0, 0, M, 0, M, M, 0, 0, 0};//5
			std::vector<short> Lclust_2{0, M, M, 0, M, 0, 0, 0, 0};//6
			std::vector<short> Lclust_3{M, M, 0, 0, M, 0, 0, 0, 0};//7
			std::vector<short> Lclust_4{M, 0, 0, M, M, 0, 0, 0, 0};//8
			std::vector<short> Lclust_5{0, 0, 0, M, M, 0, M, 0, 0};//9
			std::vector<short> Lclust_6{0, 0, 0, 0, M, 0, M, M, 0};//10
			std::vector<short> Lclust_7{0, 0, 0, 0, M, 0, 0, M, M};//11
			std::vector<short> Lclust_8{0, 0, 0, 0, M, M, 0, 0, M};//12
   			if(	(arr == Lclust_1) or 
				(arr == Lclust_2) or 
				(arr == Lclust_3) or 
				(arr == Lclust_4) or
				(arr == Lclust_5) or
				(arr == Lclust_6) or
				(arr == Lclust_7) or
				(arr == Lclust_8) )
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//4-Connected Offset
		if(P[i][j][0]!= 1)
   		{
   			std::vector<short> Con_off1{0, M, M, M, M, 0, 0, 0, 0};//13
			std::vector<short> Con_off2{M, M, 0, 0, M, M, 0, 0, 0};//14
			std::vector<short> Con_off3{0, M, 0, 0, M, M, 0, 0, M};//15
			std::vector<short> Con_off4{0, 0, M, 0, M, M, 0, M, 0};//16
			if(	(arr == Con_off1) or
				(arr == Con_off2) or
				(arr == Con_off3) or
				(arr == Con_off4) )
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//Spur Corner Cluster
		//10
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 0;
   			std::vector<short> SpurC1{0, A, M, 0, M, B, M, 0, 0};//17
			std::vector<short> SpurC2{M, B, 0, A, M, 0, 0, 0, M};//18
			std::vector<short> SpurC3{0, 0, M, A, M, 0, M, B, 0};//19
			std::vector<short> SpurC4{M, 0, 0, 0, M, B, 0, A, M};//20
			if(	(arr == SpurC1) or
				(arr == SpurC2) or
				(arr == SpurC3) or
				(arr == SpurC4) )
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//01
		if(P[i][j][0]!= 1)
   		{
   			short A = 0;
   			short B = 1;
   			std::vector<short> SpurC1{0, A, M, 0, M, B, M, 0, 0};//17
			std::vector<short> SpurC2{M, B, 0, A, M, 0, 0, 0, M};//18
			std::vector<short> SpurC3{0, 0, M, A, M, 0, M, B, 0};//19
			std::vector<short> SpurC4{M, 0, 0, 0, M, B, 0, A, M};//20
			if(	(arr == SpurC1) or
				(arr == SpurC2) or
				(arr == SpurC3) or
				(arr == SpurC4) )
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//11
		if(P[i][j][0]!= 1)
   		{
   			short A = 1;
   			short B = 1;
   			std::vector<short> SpurC1{0, A, M, 0, M, B, M, 0, 0};//17
			std::vector<short> SpurC2{M, B, 0, A, M, 0, 0, 0, M};//18
			std::vector<short> SpurC3{0, 0, M, A, M, 0, M, B, 0};//19
			std::vector<short> SpurC4{M, 0, 0, 0, M, B, 0, A, M};//20
			if(	(arr == SpurC1) or
				(arr == SpurC2) or
				(arr == SpurC3) or
				(arr == SpurC4) )
			   {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//Corner Cluster
		if(P[i][j][0]!= 1)
   		{
   			short D = 2;
   			std::vector<short> Cor_clu{M, M, D, M, M, D, D, D, D};//21
   			for(n = 0; n < 9; n++)
		    {
	   			if (Cor_clu[n] == 2)
				{
					Cor_clu[n] = arr[n];
				}
				else
				{
					Cor_clu[n] = Cor_clu[n];
				}
		    }
            if(	(arr == Cor_clu) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//Tee Branch
		if(P[i][j][0]!= 1)
   		{
   			short D = 2;
   			std::vector<short> Tee_bran1{D, M, 0, M, M, M, D, 0, 0};//22
			std::vector<short> Tee_bran2{0, M, D, M, M, M, 0, 0, D};//23
			std::vector<short> Tee_bran3{0, 0, D, M, M, M, 0, M, D};//24
			std::vector<short> Tee_bran4{D, 0, 0, M, M, M, D, M, 0};//25
			std::vector<short> Tee_bran5{D, M, D, M, M, 0, 0, M, 0};//26
			std::vector<short> Tee_bran6{0, M, 0, M, M, 0, D, M, D};//27
			std::vector<short> Tee_bran7{0, M, 0, 0, M, M, D, M, D};//28
			std::vector<short> Tee_bran8{D, M, D, 0, M, M, 0, M, 0};//29
			for(n = 0; n < 9; n++)
		    {
	   			if (Tee_bran1[n] == 2)
			{
				Tee_bran1[n] =arr[n];
			}
			else
			{
				Tee_bran1[n] =Tee_bran1[n];
			}
			
			
			if (Tee_bran2[n] == 2)
			{
				Tee_bran2[n] =arr[n];
			}
			else
			{
				Tee_bran2[n] =Tee_bran2[n];
			}
			
			if (Tee_bran3[n] == 2)
			{
				Tee_bran3[n] =arr[n];
			}
			else
			{
				Tee_bran3[n] =Tee_bran3[n];
			}
			
			if (Tee_bran4[n] == 2)
			{
				Tee_bran4[n] =arr[n];
			}
			else
			{
				Tee_bran4[n] =Tee_bran4[n];
			}
			
			if (Tee_bran5[n] == 2)
			{
				Tee_bran5[n] =arr[n];
			}
			else
			{
				Tee_bran5[n] =Tee_bran5[n];
			}
			
			if (Tee_bran6[n] == 2)
			{
				Tee_bran6[n] =arr[n];
			}
			else
			{
				Tee_bran6[n] =Tee_bran6[n];
			}
			
			if (Tee_bran7[n] == 2)
			{
				Tee_bran7[n] =arr[n];
			}
			else
			{
				Tee_bran7[n] =Tee_bran7[n];
			}
			
			if (Tee_bran8[n] == 2)
			{
				Tee_bran8[n] =arr[n];
			}
			else
			{
				Tee_bran8[n] =Tee_bran8[n];
			}
		}
		if(	(arr == Tee_bran1) or
			(arr == Tee_bran2) or
			(arr == Tee_bran3) or
			(arr == Tee_bran4) or
			(arr == Tee_bran5) or
			(arr == Tee_bran6) or
			(arr == Tee_bran7) or
			(arr == Tee_bran8) )
                {
   		        	P[i][j][0] = 1;
	   			}
   				else
   				{
   					P[i][j][0] = 0;
   				}
		}
		//Vee Branch
		//001
		if(P[i][j][0]!= 1)
   		{
   			short D = 2;
   			short A = 0;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 0;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 0;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 1;
   			short B = 0;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 1;
   			short B = 0;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 1;
   			short B = 1;
   			short C = 0;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
   			short D = 2;
   			short A = 1;
   			short B = 1;
   			short C = 1;
	   		std::vector<short> Vee_bran1{M, D, M, D, M, D, A, B, C};//30
			std::vector<short> Vee_bran2{M, D, C, D, M, B, M, D, A};//31
			std::vector<short> Vee_bran3{C, B, A, D, M, D, M, D, M};//32
			std::vector<short> Vee_bran4{A, D, M, B, M, D, C, D, M};//33
			for(n = 0; n < 9; n++)
		    {
			if (Vee_bran1[n] == 2)//30
				{
					Vee_bran1[n] =arr[n];
				}
				else
				{
					Vee_bran1[n] =Vee_bran1[n];
				}
				
				if (Vee_bran2[n] == 2)//31
				{
					Vee_bran2[n] =arr[n];
				}
				else
				{
					Vee_bran2[n] =Vee_bran2[n];
				}
				
				if (Vee_bran3[n] == 2)//32
				{
					Vee_bran3[n] =arr[n];
				}
				else
				{
					Vee_bran3[n] =Vee_bran3[n];
				}
				
				if (Vee_bran4[n] == 2)//33
				{
					Vee_bran4[n] =arr[n];
				}
				else
				{
					Vee_bran4[n] =Vee_bran4[n];
				}
			}
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
		if(P[i][j][0]!= 1)
   		{
   			short D = 2;
   			std::vector<short> Dia_bran1{D, M, 0, 0, M, M, M, 0, D};//34
			std::vector<short> Dia_bran2{0, M, D, M, M, 0, D, 0, M};//35
			std::vector<short> Dia_bran3{D, 0, M, M, M, 0, 0, M, D};//36
			std::vector<short> Dia_bran4{M, 0, D, 0, M, M, D, M, 0};//37
			for(n = 0; n < 9; n++)
		    {
	   		if (Dia_bran1[n] == 2)
			{
				Dia_bran1[n] =arr[n];
			}
			else
			{
				Dia_bran1[n] =Dia_bran1[n];
			}
			
			if (Dia_bran2[n] == 2)
			{
				Dia_bran2[n] =arr[n];
			}
			else
			{
				Dia_bran2[n] =Dia_bran2[n];
			}
			
			if (Dia_bran3[n] == 2)
			{
				Dia_bran3[n] =arr[n];
			}
			else
			{
				Dia_bran3[n] =Dia_bran3[n];
			}
			
			if (Dia_bran4[n] == 2)
			{
				Dia_bran4[n] =arr[n];
			}
			else
			{
				Dia_bran4[n] =Dia_bran4[n];
			}
		}
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
	
				
	//Displaying P

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

			// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output_image, sizeof(unsigned char), Row_Size*Column_Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
