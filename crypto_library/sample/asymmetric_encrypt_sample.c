#include <stdio.h>
#include "test_code.h"
#include "edge_crypto.h"

int rsa_enc_sample();
int asymmetric_encrypt_sample() {
    int ret = 0;

    ret = rsa_enc_sample();
    if (ret != 0) return ret;

    return ret;
}

int rsa_enc_sample() {
    int ret = 0;

    EDGE_ASYM_KEY_PARAM key_param;
    EDGE_ASYM_ENC_PARAM param;
    uint8_t input[25] = "rsa_encryption_test_text";
    uint32_t inputlength = 25;
    uint8_t output[512] = { 0x00, };
    uint32_t outputlength = 0;
    uint8_t dec[512] = { 0x00, };
    uint32_t declength = 0;
    uint8_t public_key[2048] = { 0x00, };
    uint32_t public_keylength = 0;
    uint8_t private_key[2048] = { 0x00, };
    uint32_t private_keylength = 0;

    memset(&key_param, 0, sizeof(EDGE_ASYM_KEY_PARAM));
    key_param.m_algorithm = EDGE_ASYM_ID_RSA;
    key_param.rsa.m_bits = 2048;
    key_param.rsa.m_exponent = 65537;

    printf("\n##======================   rsa_enc_sample() start   ======================##\n");
    do {
        printf("\n *----------------------   edge_asym_gen_keypair()  ------------------------\n");
        ret = edge_asym_gen_keypair(public_key, &public_keylength, private_key, &private_keylength, &key_param);
        if (ret != 0) {
			printf ("fail generate key pair %d\n", ret);
			break;
		}

		ret = edge_asym_verify_keypair (public_key, public_keylength, private_key, private_keylength, &key_param);
        if (ret != 0) {
			printf ("fail verify key pair %d\n", ret);
			break;
		}

        hexdump("private_key", private_key, private_keylength);
        hexdump("public_key", public_key, public_keylength);

        param.m_encMode = EDGE_RSA_ENC_MODE_OAEP;
        param.m_oaep.m_hashAlg = EDGE_HASH_ID_SHA256;
        param.m_oaep.m_label = NULL;
        param.m_oaep.m_labelLength = 0;
        param.m_oaep.m_mgfHashAlg = EDGE_HASH_ID_SHA256;

        hexdump("input", input, inputlength);
        printf("\n *----------------------       edge_asym_enc()      ------------------------\n");
        ret = edge_asym_enc(private_key, private_keylength, &param, input, inputlength, output, &outputlength);
        if (ret != 0) break;
        hexdump("output", output, outputlength);

        printf("\n *----------------------       edge_asym_dec()      ------------------------\n");
        ret = edge_asym_dec(public_key, public_keylength, &param, output, outputlength, dec, &declength);
        if (ret != 0) break;
        hexdump("dec", dec, declength);

    } while (0);

    printf("\n##======================    rsa_enc_sample() end    ======================##\n");

    return ret;
}
