#include "endetest.h"
#include <stdio.h>

int main(int argc, char* argv[]){
			
	char* input_data = NULL;

	input_data = *(argv+1);

	char* out = NULL;

	printf("\nThis program is program that change string data to binary or hex so you can put only char data\n\n");

	printf("\nYour Input_data\n");
	printf("%s \n\n", input_data);

	if(input_data == NULL){	
		printf("You should put string data and mode if not you meet data error : %d\n",DATA_ERR);
		printf("\nYou should Enter mode with data\n\n");
		printf("If you want change original data to hex Put dtoh\n");
		printf("If you want change hex to original data Put htod\n");
		printf("If you want change original data to binary put dtob\n");
		printf("If you want change binary to original data put btod\n");
		printf("If you want file read Put 1 and read between space\n");


		return DATA_ERR;
	}

	int res = 0;
	int data_len = strlen(input_data); //This case is that Assume your put data is only string
	
	printf("you data_len\n");
	printf("%d\n",data_len);
	
	if(argc < 3){
	
		printf("\nYou should Enter mode with data\n\n");
		printf("If you want change original data to hex Put dtoh\n");
	       	printf("If you want change hex to original data Put htod\n");
		printf("If you want change original data to binary put dtob\n");
		printf("If you want change binary to original data put btod\n");	
		printf("If you want file read Put 1 and read between space\n");
	}

	else if(strcmp(argv[2], "dtoh") == 0){
		
		res = dataToHex(input_data,data_len,&out); //This case is that Assume your put data is only string 
		
		//printf("put number of your input data\n");  //From this line to the third line is assumed that your input data is other data as well as string.
		//scanf("%d",&data_len);
		//res = dataToHex(input_data, data_len, &out); 

		if(res != CONVERT_OK){
			printf("error : %d\n", res);
			return res;
		}
		printf("\nencode result : %s\n", out);

		fileWrite(out);
		
	
	}else if(strcmp(argv[2], "htod") == 0){
		res = hexToData(input_data,data_len,&out); //This case is that Assume your put data is only string

		//printf("put number of your input data\n");  //From this line to the third line is assumed that your input data is other data as well as string.
		//scanf("%d",&data_len);
		//res = dataToHex(input_data, data_len, &out);

		if(res != CONVERT_OK){
			printf("error %d\n", res);
			return res;
		}

		printf("\ndecode result : %s\n", out);

		fileWrite(out);
	
	}else if(strcmp(argv[2], "dtob")== 0){
		res = dataToBinary(input_data,data_len, &out); //This case is that Assume your put data is only string
		
		//printf("put number of your input data\n");  //From this line to the third line is assumed that your input data is other data as well as string.
		//scanf("%d",&data_len);
		//res = dataToHex(input_data, data_len, &out);

		if(res != CONVERT_OK){
			
			printf("error %d\n", res);
			return res;		
		}
		
		printf("\nencode result : %s\n", out);

		fileWrite(out);
	
	}else if(strcmp(argv[2], "btod") == 0){
		
		res = binaryToData(input_data,data_len,&out); //This case is that Assume your put data is only string

		//printf("put number of your input data\n");  //From this line to the third line is assumed that your input data is other data as well as string.
		//scanf("%d",&data_len);
		//res = dataToHex(input_data, data_len, &out);

		if(res != CONVERT_OK){
			
			printf("error %d\n", res);
			return res;	
		}

		printf("\ndecode result : %s\n", out);

		fileWrite(out);
	}
	
	else if(strcmp(argv[1],"1") == 0 && strcmp(argv[2], "read") == 0){
		
		printf("\n\n\nYou choice file read\n");
				
		fileRead();
	
	}

	else{
		printf("\nYou put wrong command\n Put data and commend between space");
	}
		
	free(out);
	return 0;		
		
}

