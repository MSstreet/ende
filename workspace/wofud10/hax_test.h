#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int haxdecode(char *input,int input_len, char* output, int *output_len);
int haxencode(char *s, int arraySize, char *rest, int* output_len);
int binaryencode(char *s, int arraySize, char *rest, int* output_len);
int binarydecode(char *s, int arraySize, char* rest, int* output_len);

