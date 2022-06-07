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
	int i;
	for (i = 0; i < arraySize; i++) {
		sprintf(res + 2 * i, "%d", *(s + i));
	}
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

	for (i = 0; i < arraySize-1; i++) {
		if (s[i]-'0' > 9 || s[i]-'0' < 0) {
			return -1;
		};
		res[x] = s1[i];
		x++;
		if (i % 2 != 0) {
			num1 = strtol(res, NULL, 10);
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
