#include "hax_test.h"

int haxdecode(char *s,int arraySize, char* res) {
	char *s1 = s;
	int  num1;
	int arraySize2 = arraySize*2;
	char *res2 = (char *)calloc(arraySize2, sizeof(char));
	int i;
	int j = 0;
	int x = 0;

	for (i = 0; i < arraySize-1; i++) {
		if (s1[i] - '0' > 54 || s1[i] - '0' < 0) return -1;
		res[x] = s1[i];
		x++;
		if (i % 2 != 0) {
			num1 = strtol(res, NULL, 16);
			sprintf(res2 + j, "%c", num1);
			j++;
			memset(res, 0, arraySize2 * sizeof(char));
			x = 0;
		}
	}
	strcpy(res, res2);
	free(res2);

	return 0;
}

int haxencode(char *s, int arraySize, char *res) {
	int i;
	for (i = 0; i < arraySize; i++) {
		sprintf(res+2*i, "%x", *(s + i));
	}
	return 0;
}

int binaryencode(char *s, int arraySize, char *res) {

	if (s == NULL) return -1;

	size_t len = strlen(s);
	char *binary = malloc(len * 8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
	binary[0] = '\0';
	for (size_t i = 0; i < len; ++i) {
		char ch = s[i];
		for (int j = 7; j >= 0; --j) {
			if (ch & (1 << j)) {
				strcat(binary, "1");
			}
			else {
				strcat(binary, "0");
			}
		}
	}
	strcpy(res, binary);
	return 0;
}

int binarydecode(char *s, int arraySize, char* res) {

	char *s1 = s;
	int  num1;
	int arraySize2 = arraySize *2;
	char *res2 = (char *)calloc(arraySize2, sizeof(char));
	int i;
	int j = 0;
	int x = 0;

	for (i = 1; i < arraySize; i++) {
		res[x] = s1[i-1];
		x++;
		if (i % 8 == 0) {
			num1 = strtol(res, NULL, 2);
			sprintf(res2 + j, "%c", num1);
			j++;
			memset(res, 0, arraySize2 * sizeof(char));
			x = 0;
		}
	}
	strcpy(res, res2);
	free(res2);

	return 0;
}
