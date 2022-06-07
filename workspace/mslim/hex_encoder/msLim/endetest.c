#include "endetest.h"
#include <stdio.h>

int dataToHex(char* inData, int input_len, char* outHex){

	if(input_len > 499) return OVER_MEMORY_ERR;

	int i = 0;

	for(; i <= input_len - 1; i++){

		sprintf(outHex, "%x", inData[i]);
		
		outHex = outHex + 2;
	
	}
	
	return CONVERT_OK;
	
}

int hexToData(char* inHex, int input_len, char* outData){

	

	char tmp[2];

	int h = 0;
	int j = 0;

	while(j < input_len){
		
		strncpy(tmp, inHex, 2);
		h = (int)strtol(tmp,NULL,16);
		
		

		sprintf(outData, "%c", h);
		

		inHex = inHex + 2;
		outData++;

		
		j += 2;
	
	}

	return CONVERT_OK;

}

int dataToBinary(char* inData, int input_len, char* outBinary){

	if(input_len > 125) return OVER_MEMORY_ERR;

	dataToHex(inData,input_len,outBinary);

	char tmp[2];
	char* tmp_ = NULL;

	tmp_ = (char*)malloc(1000);
	if (tmp_ == NULL) return ASSINMENT_ERR;

	int i, j = 0, h = 0;
	int buf[8];
	int len = strlen(outBinary) / 2;

	int cnt = 0;

	strcpy(tmp_, outBinary);

	while(*tmp_ != NULL) {

		strncpy(tmp, tmp_, 2);

		h = (int)strtol(tmp,NULL,16);

		for(i = 7; i >= 0; i--){

			buf[i] = h % 2;
			h = h / 2;
		}

		for(i = 0; i < 8; i++){
			sprintf(outBinary,"%d", buf[i]);
			outBinary++;
		}
		tmp_ = tmp_ + 2;
		cnt++;
	}

	printf("%d\n",cnt);

	tmp_ = NULL;
	free(tmp_);

	return CONVERT_OK;
}

int binaryToData(char* inBinary, int input_len, char* outData){

	for(int i = 0; i < input_len - 1; i++){
		if(inBinary[i] != '0'){
			if(inBinary[i] != '1')
				return DATA_ERR;
		}
	}

	char tmp[8];

	char* tmp_ = NULL;
	tmp_ = (char*)malloc(input_len);
	if(tmp_ == NULL) return ASSINMENT_ERR;

	int h = 0, i = 0;
	int pos = 0;

	strcpy(tmp_,inBinary);

	while(*tmp_ != NULL){

		h = 0;
		pos = 0;

		strncpy(tmp, tmp_, 8);

		for(i = 7; i >= 0; i--){

			if(tmp[i] == '1')
				h += 1 << pos;

			
			pos++;
		}

		sprintf(outData, "%c", h);
		outData++;
		tmp_ = tmp_ + 8;
	}

	tmp_ = NULL;
	free(tmp_);

	return CONVERT_OK;
}

	
