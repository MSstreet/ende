#include "endetest.h"
#include <stdio.h>

int dataToHex(char* inData, int input_len, char** outData){

	if(inData == NULL) return DATA_ERR;

	int i = 0;
	int j = 0;

	*outData = (char*)malloc(input_len * 2 + 1);
	if (*outData == NULL) return ASSINMENT_ERR;

	for(; i <= input_len - 1; i++){

		sprintf(*outData, "%x", inData[i]);
		
		*outData = *outData + 2;
		j += 2;
	
	}
	
	*outData -= j;
	
	
	return CONVERT_OK;
	
}

int hexToData(char* inHex, int input_len, char** outData){
	
	for(int i = 0; i < input_len - 1; i++){

		if(!(inHex[i] >= 48 && inHex[i] <= 57)){
			if(!(inHex[i] >= 65 && inHex[i] <= 70)){
				if(!(inHex[i] >= 97 && inHex[i] <= 102)){
					return DATA_ERR;
				
				}
			}
		}	
	
	}

	if(inHex == NULL) return DATA_ERR;
	if((input_len % 2) != 0 ) return DATA_ERR;
	
	*outData = (char*)malloc(input_len / 2 + 1);
	if(*outData == NULL) return ASSINMENT_ERR;

	char tmp[2];

	int h = 0;
	int j = 0;
	int k = 0;

	while(j < input_len){
		
		strncpy(tmp, inHex, 2);
		h = (int)strtol(tmp,NULL,16);
		
		sprintf(*outData, "%c", h);
		
		inHex = inHex + 2;
		*outData = *outData + 1;
		
		k++;
		j += 2;
	}
	
	*outData -= k;

	return CONVERT_OK;
}

int dataToBinary(char* inData, int input_len, char** outData){

	if(inData == NULL) return DATA_ERR;

	char* tmp_ = NULL;
	int tmp_len = 0;
	int i = 0, j = 0, h = 0;
	int t = 0, k = 0;
	int buf[8];
	
	*outData = (char*)malloc(input_len * 8 + 1);
	if(outData == NULL) return ASSINMENT_ERR;

	tmp_ = (char*)malloc(input_len * 3);
	if (tmp_ == NULL) return ASSINMENT_ERR;

	while(j < input_len) {

		tmp_len = 0;
	
		sprintf(tmp_, "%d", inData[j]);

		h = strtol(tmp_,NULL,10);
		t = h;

		while(t != 0){
			t = t / 10;
			tmp_len++;
		}

		for(i = 7; i >= 0; i--){
			buf[i] = h % 2;
			h = h / 2;
		}

		for(i = 0; i < 8; i++){
			sprintf(*outData,"%d", buf[i]);
			*outData = *outData + 1;
			k++;
		}
		
		tmp_ = tmp_ + tmp_len;
		j++;
	}

	*outData = *outData - k;

	tmp_ = NULL;
	free(tmp_);

	return CONVERT_OK;
}

int binaryToData(char* inBinary, int input_len, char** outData){

	if(inBinary == NULL) return DATA_ERR;
	if((input_len % 8) != 0) return DATA_ERR;

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

	*outData = (char*)malloc(input_len / 8 + 1);
	if(outData == NULL) return ASSINMENT_ERR;

	int h = 0, i = 0, j = 0;
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

		sprintf(*outData, "%c", h);
		*outData = *outData + 1;
		
		j++;
		tmp_ = tmp_ + 8;
	}

	*outData = *outData - j;

	tmp_ = NULL;
	free(tmp_);

	return CONVERT_OK;
}


int fileWrite(char* data){

	FILE* fp;
	int res = 0;

	int data_len = strlen(data);
	
	fp = fopen("write.txt", "w");

	if (fp == NULL) {
		res = ERR;
		printf("%d\n", res);
		
		return res;
	}


	else {
		printf("\nsuccess to open file\n");
	}


	fprintf(fp, "%s\n", data);

	fclose(fp);

	return CONVERT_OK;
}


int fileRead() {

	FILE* fp;

	int res = 0;
	char s[1000]; 
	//char *s 
	//s = (char*)malloc(data_len);

	fp = fopen("write.txt", "r");

	if (fp == NULL) {
		res = ERR;
		printf("%d\n", res);
		
		return res;
	}

	fscanf(fp,"%s", s);

	printf("%s\n", s);

	fclose(fp);

	return CONVERT_OK;
}


	
