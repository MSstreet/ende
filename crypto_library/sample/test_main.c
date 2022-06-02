#include "test_code.h"
#include "edge_crypto.h"

int main(int argc, char *argv[])
{
	int				ret = 0;
	int				status = 0;
	char			* signPath = NULL;


	printf("EdgeCrypto Sample \n");
	printf(" Crypto version [%s]\n\n", edge_crypto_get_version());

	status = edge_crypto_get_status();
	printf("current status : %d [%s]\n", status, crypto_getStatusString(status));

	if (argc == 2) {
		signPath = argv[1];
		printf ("sign data file path [%s]\n", signPath);
	}

	printf("process crypto initialize ...");
	ret = edge_crypto_init(signPath);
	if (ret != 0) {
		printf("fail [%d]\n", ret);
		return ret;
	} 
	printf("success [%d]\n", ret);

	status = edge_crypto_get_status();
	printf("current status : %d [%s]\n", status, crypto_getStatusString(status));


    do {
        ret = symmetric_sample();
        if (ret != 0) {
            printf_red("symmetric_sample error[%d]\n", ret);
            break;
        }

        ret = auth_crypto_sample();
        if (ret != 0) {
            printf_red("auth_crypto_sample error[%ds]\n", ret);
            break;
        }

        ret = hash_sample();
        if (ret != 0) {
            printf_red("hash_sample error[%d]\n", ret);
            break;
        }

        ret = mac_sample();
        if (ret != 0) {
            printf_red("mac_sample error[%d]\n", ret);
            break;
        }

        ret = asymmetric_encrypt_sample();
        if (ret != 0) {
            printf_red("asymmetric_encrypt_sample error[%d]\n", ret);
            break;
        }

        ret = asymmetric_sign_sample();
        if (ret != 0) {
            printf_red("asymmetric_sign_sample error[%d]\n", ret);
            break;
        }

        ret = keyagreement_sample();
        if (ret != 0) {
            printf_red("keyagreement_sample error[%d]\n", ret);
            break;
        }

        ret = asymmetric_sign_sample();
        if (ret != 0) {
            printf_red("asymmetric_sign_sample error[%d]\n", ret);
            break;
        }
    } while (0);

	edge_crypto_final();

	return 0;
}
