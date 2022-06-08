#include "hax_test.h"

int main() {
	char str[50];
	char str2[50];

	FILE *f = fopen("C:\\Users\\admin\\source\\repos\\Filetest\\hello.txt", "r");;
	if (f == NULL) {
		printf("file does not exist! \n");
		return -1;
	}
	fscanf(f, "%s %s\n", str, str2);

	if (str == NULL) {
		printf("Wrong input");
		return 0;
	}
	int output_len = 0;
	char* input = str;
	int err;
	printf("%s\n", input);
	int arraySize = strlen(input) + 1;
	char* res = (char*)calloc(arraySize * 2, sizeof(char));
	char* bires = (char*)calloc(arraySize * 8, sizeof(char));
	char temp[2] = { 0xFF, 0xAB };

	if (strcmp(str2, "haxencode") == 0) {
		haxencode(input, arraySize, res, &output_len);
		printf("hax =%s %d\n", res, output_len);
	}

	else if (strcmp(str2, "haxdecode") == 0) {
		err = haxdecode(input, arraySize, res, &output_len);
		if (err != 0) {
			printf("Error ! %d\n", err);
			return err;
		}
		else {
			printf("hax2binary =%s %d\n", res, output_len);
		}
	}
	else if (strcmp(str2, "binaryencode") == 0) {
		binaryencode(input, arraySize, bires, &output_len);
		printf("binary =%s %d\n", bires, output_len);
	}

	else if (strcmp(str2, "binarydecode") == 0) {
		err = binarydecode(input, arraySize, res, &output_len);
		if (err != 0) {
			printf("Error ! %d\n", err);
			return err;
		}
		else {
			printf("binary =%s %d\n", res, output_len);
		}
	}
	else {
		printf("Wrong input");
		return 0;
	}
	free(res);
	return 0;
}
