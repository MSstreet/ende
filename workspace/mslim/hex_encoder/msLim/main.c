#include "endetest.h"
#include <stdio.h>

int main(int argc, char* argv[]){
	
	int res = 0;

	char* hello0 = "hellohhellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello";
	char hello1[100] = "68656c6c6f68";
	char* hello2 = "011010000110010101101100011011000110111100100000";

	char *out = NULL;



	out = (char*)malloc(1000);
	

	if(strcmp(argv[1], "dtoh") == 0){
		res = dataToHex(hello0, strlen(hello0), out);

		if(res != CONVERT_OK){
			printf("error %d\n", res);
			return res;
		}

		printf("%s\n", out);
	
	}else if(strcmp(argv[1], "htod") == 0){
		res = hexToData(hello1, strlen(hello1),out);

		if(res != CONVERT_OK){
			printf("error %d\n", res);
			return res;
		}

		printf("%s\n",out);
	
	}else if(strcmp(argv[1], "dtob")== 0){
		res = dataToBinary(hello0, strlen(hello0), out);
		
		if(res != CONVERT_OK){
			
			printf("error %d\n", res);
			return res;		
		}
		
		printf("%s\n",out);
	}else{
		res = binaryToData(hello2,strlen(hello2),out);

		if(res != CONVERT_OK){
			
			printf("error %d\n", res);
			return res;	
		}

		printf("%s\n",out);
	}




		
		

}

