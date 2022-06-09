#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERR			10000

#define OVER_MEMORY_ERR		10001
#define ASSINMENT_ERR		10002
#define DATA_ERR		10003

#define CONVERT_OK		1

int dataToHex(char* inData, int input_len, char** outData);
int hexToData(char* inHex, int input_len, char** outData);
int dataToBinary(char* inData, int input_len, char** outData);
int binaryToData(char* inBinary, int input_len, char** outData);

