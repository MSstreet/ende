#include "hax_test.h"

int main(int argc, char* argv[]) {

	char* input = argv[1];
	int err;
	printf("%s\n", input);
	int arraySize = strlen(input) + 1;
	char* res = (char*)calloc(arraySize * 2, sizeof(char));
	char temp[2] = { 0xFF, 0xAB };

	if (strcmp(argv[2], "haxencode") == 0) {
		haxencode(input, arraySize, res);
		printf("hax =%s\n", res);
	}

	if (strcmp(argv[2], "haxdecode") == 0) {
		err = haxdecode(input, arraySize, res);
		if (err != 0) {
			printf("Error ! %d\n", err);
			return err;
		}
		else {
			printf("text =%s\n", res);
		}
	}

	if (strcmp(argv[2], "binaryencode") == 0) {
		binaryencode(input, arraySize, res);
		printf("binary =%s\n", res);
	}

	if (strcmp(argv[2], "binarydecode") == 0) {
		err = binarydecode(input, arraySize, res);
		if (err != 0) {
			printf("Error ! %d\n", err);
			return err;
		}
		else {
			printf("binary =%s\n", res);
		}
	}
	free(res);
	return 0;
}

