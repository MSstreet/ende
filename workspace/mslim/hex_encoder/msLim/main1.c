#include "endetest.h"
#include <stdio.h>

int main(int argc, char* argv[]){

	 char* out = NULL;
	 char input[100];
	 
	 int input_len = 0;
	 int res = 0;


	 if(argc < 2){

		  printf("\nYou should Enter mode\n\n");
		  printf("If you want change original data to hex Put dtoh\n");
	 	  printf("If you want change hex to original data Put htod\n");
	 	  printf("If you want change original data to binary put dtob\n");
	 	  printf("If you want change binary to original data put btod\n");

	  
    	}		

	 else if(strcmp(argv[1], "dtoh") == 0){
		
	   		
		printf("put original data you can put it below 100 length of it\n");
		scanf("%s",input);
		
		printf("put length of data\n");
		scanf("%d",&input_len);

	 	res = dataToHex(input,input_len,&out);

		 if(res != CONVERT_OK){
			
			 printf("error : %d\n", res);
			 return res;
		 }
		printf("\nencode result : %s\n", out);
	 }

	 else if(strcmp(argv[1], "htod") == 0){
	
 		 printf("put original data you can put it below 100 length of it\n");
		 scanf("%s",input);

		 printf("put length of data\n");
		 scanf("%d",&input_len);
		 res = hexToData(input,input_len,&out);
		 if(res != CONVERT_OK){

			  printf("error : %d\n", res);
			  return res;
		}
		 printf("\nencode result : %s\n", out);
	 }
	 else if(strcmp(argv[1], "dtob") == 0){
	 	
		 printf("put original data you can put it below 100 length of it\n");
		 scanf("%s",input);

		 printf("put length of data\n");
		 scanf("%d",&input_len);
		 res = dataToBinary(input,input_len,&out);
		 if(res != CONVERT_OK){

			 printf("error : %d\n", res);
			 return res;
		 }
		 printf("\nencode result : %s\n", out);
	 
	 }
	else if(strcmp(argv[1], "btod") == 0){
		
		printf("put original data you can put it below 100 length of it\n");
		scanf("%s",input);

		printf("put length of data\n");
		scanf("%d",&input_len);
		res = binaryToData(input,input_len,&out);
		
		if(res != CONVERT_OK){

			printf("error : %d\n", res);
			return res;
		}
		printf("\nencode result : %s\n", out);
	
	}
	else{
	 	 
	 	printf("\nYou put wrong command\n Put data and commend between space");
	 
	 }

	free(out);
	
	return 0;

}
