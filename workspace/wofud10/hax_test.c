#include "hax_test.h"

int haxdecode(char *input,int input_len, char* output, int *output_len) {
	char *s1 = input;
	int  num1;
	int input_len2 = input_len *2;
	char *res2 = (char *)calloc(input_len2, sizeof(char));
	int i;
	int j = 0;
	int x = 0;

	for (i = 0; i < input_len -1; i++) {
		if (s1[i] - '0' > 54 || s1[i] - '0' < 0) return -1;
		output[x] = s1[i];
		x++;
		if (i % 2 != 0) {
			num1 = strtol(output, NULL, 16);
			sprintf(res2 + j, "%c", num1);
			j++;
			memset(output, 0, input_len * sizeof(char));
			x = 0;
		}
	}
	strcpy(output, res2);
	*output_len = strlen(output);
	free(res2);

	return 0;
}

int haxencode(char *input, int input_len, char *output, int* output_len) {
	int i;
	for (i = 0; i < input_len; i++) {
		sprintf(output+2*i, "%x", *(input + i));
	}
	*output_len = input_len*2;
	return 0;
}

int binaryencode(char *input, int intput_len, char *output, int* output_len) {

	if (input == NULL) return -1;

	size_t len = strlen(input);
	char *binary = malloc(len * 8 + 1);
	binary[0] = '\0';
	for (size_t i = 0; i < len; ++i) {
		char ch = input[i];
		for (int j = 7; j >= 0; --j) {
			if (ch & (1 << j)) {
				strcat(binary, "1");
			}
			else {
				strcat(binary, "0");
			}
		}
	}
	strcpy(output, binary);
	*output_len = strlen(output);
	free(binary);
	return 0;
}

int binarydecode(char *intput, int input_len, char* output, int* output_len) {
	input_len = input_len - 1;
	if (input_len % 2 != 0) {
		printf("Wrong input");
		return -1;
	}
	char *s1 = intput;
	int  num1;
	int input_len2 = input_len *2;
	char *res2 = (char *)calloc(input_len2, sizeof(char));
	int i;
	int j = 0;
	int x = 0;



	for (i = 1; i < input_len; i++) {
		output[x] = s1[i-1];
		x++;
		if (i % 8 == 0) {
			num1 = strtol(output, NULL, 2);
			sprintf(res2 + j, "%c", num1);
			j++;
			memset(output, 0, input_len2 * sizeof(char));
			x = 0;
		}
	}
	strcpy(output, res2);
	*output_len = strlen(output);
	free(res2);

	return 0;
}
