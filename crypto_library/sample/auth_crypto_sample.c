#include "test_code.h"
#include "edge_crypto.h"

int gcm_sample();
//int gcm_init_update_final_sample();
int ccm_sample();
//int ccm_init_update_final_sample();

int auth_crypto_sample() {
    int ret = 0;

    ret = gcm_sample();
	if (ret != 0)	return ret;

    //ret = gcm_init_update_final_sample();
	//if (ret != 0)	return ret;

    ret = ccm_sample();
	if (ret != 0)	return ret;

    //ret = ccm_init_update_final_sample();
	//if (ret != 0)	return ret;

    return ret;
}

int gcm_sample() {
    int ret = 0;

    int cipher_id = EDGE_CIPHER_ID_ARIA128;
    uint8_t key[16] = { 0x00 };
    uint32_t keylength = 16;
    uint8_t iv[16] = { 0x00 };
    uint32_t ivlength = 16;
    uint8_t input[21] = "gcm_test_text_sample";
    uint32_t inputlength = 21;
    uint8_t output[32] = { 0x00 };
    uint64_t outputlength = 0;
    uint8_t tag[32] = { 0x00 };
    uint32_t taglength = 12;
    uint8_t dec[32] = { 0x00 };
    uint64_t declength = 0;

    edge_random_byte(key, keylength);
    edge_random_byte(iv, ivlength);

    printf("\n##======================     gcm_sample() start     ======================##\n");
    hexdump("input", input, inputlength);
    printf("\n *----------------------       edge_gcm_enc()       ------------------------\n");
    ret = edge_gcm_enc(cipher_id, key, keylength, NULL, 0, iv, ivlength, input, inputlength, output, &outputlength, taglength, tag);
    if (ret != 0) {
        printf("edge_gcm_enc fail [%d]\n", ret);
        return ret;
    }
    hexdump("output", output, outputlength);
    hexdump("tag", tag, taglength);

    printf("\n *----------------------       edge_gcm_dec()       ------------------------\n");
    ret = edge_gcm_dec(cipher_id, key, keylength, NULL, 0, iv, ivlength, output, outputlength, dec, &declength, tag, taglength);
    if (ret != 0) {
        printf("edge_gcm_dec fail [%d]\n", ret);
        return ret;
    }
    hexdump("dec", dec, declength);

	/*
    printf("\n *----------------------  edge_gcm_dec() tag change ------------------------\n");
    ret = edge_gcm_dec(cipher_id, key, keylength, NULL, 0, iv, ivlength, output, outputlength, dec, &declength, "test_tag", taglength);
    printf("return value = %d\n", ret);

    printf("\n##======================      gcm_sample() end      ======================##\n");
	*/

    return 0;
}

#if 0
int gcm_init_update_final_sample() {
    int ret = 0;

    int cipher_id = EDGE_CIPHER_ID_SEED128;
    uint8_t key[16] = { 0x00 };
    uint32_t keylength = 16;
    uint8_t aad[128] = { 0x00 };
    uint64_t aadlength = 128;
    uint8_t iv[16] = { 0x00 };
    uint32_t ivlength = 16;
    uint8_t input[21] = "gcm_test_text_sample";
    uint32_t inputlength = 21;
    uint8_t output[32] = { 0x00 };
    uint64_t outputlength = 0;
    uint64_t outputtotal = 0;
    uint8_t tag[12] = { 0x00 };
    uint32_t taglength = 12;
    uint8_t dec[32] = { 0x00 };
    uint64_t declength = 0;
    uint64_t dectotal = 0;

    void* ctx = NULL;

    edge_random_byte(key, keylength);
    edge_random_byte(aad, aadlength);
    edge_random_byte(iv, ivlength);

    printf("\n##================= gcm_init_update_final_sample() start =================##\n");
    hexdump("input", input, inputlength);
    do {
        ctx = edge_gcm_ctx_new();
        ret = edge_gcm_enc_init(ctx, cipher_id, key, keylength, aad, aadlength, iv, ivlength);
        if (ret != 0) {
            printf("edge_gcm_enc_init fail [%d]\n", ret);
            break;
        }

        printf("\n *----------------------    edge_gcm_enc_update()   ------------------------\n");
        ret = edge_gcm_enc_update(ctx, input, inputlength, output, &outputlength);
        //ret = edge_gcm_enc_update(ctx, input, inputlength, NULL, &outputlength);
        //ret = edge_gcm_enc_update(ctx, input, inputlength, output, NULL);
        //ret = edge_gcm_enc_update(ctx, NULL, 0, NULL, NULL);
        if (ret != 0) {
            printf("edge_gcm_enc_update fail [%d]\n", ret);
            return ret;
        }
        outputtotal += outputlength;
        hexdump("output", output, outputtotal);

        printf("\n *----------------------    edge_gcm_enc_final()    ------------------------\n");
        ret = edge_gcm_enc_final(ctx, output + outputtotal, &outputlength, taglength, tag);
        if (ret != 0) {
            printf("edge_gcm_enc_final fail [%d]\n", ret);
            return ret;
        }
        outputtotal += outputlength;
        hexdump("output", output, outputtotal);
        hexdump("tag", tag, taglength);
        edge_gcm_ctx_free(ctx);

        ctx = edge_gcm_ctx_new();
        ret = edge_gcm_dec_init(ctx, cipher_id, key, keylength, aad, aadlength, iv, ivlength);

        printf("\n *----------------------    edge_gcm_dec_update()   ------------------------\n");
        ret = edge_gcm_dec_update(ctx, output, outputtotal, dec, &declength);
        if (ret != 0) {
            printf("edge_gcm_dec_update fail [%d]\n", ret);
            return ret;
        }
        dectotal += declength;
        hexdump("dec", dec, dectotal);

        printf("\n *----------------------    edge_gcm_enc_final()    ------------------------\n");
        ret = edge_gcm_dec_final(ctx, dec + dectotal, &declength, tag, taglength);
        if (ret != 0) {
            printf("edge_gcm_dec_final fail [%d]\n", ret);
            return ret;
        }
        dectotal += declength;
        hexdump("dec", dec, dectotal);
    } while (0);

    printf("\n##================== gcm_init_update_final_sample() end ==================##\n");
    edge_gcm_ctx_free(ctx);

    return 0;
}
#endif

int ccm_sample() {
    int ret = 0;

    int cipher_id = EDGE_CIPHER_ID_ARIA128;
    uint8_t key[16] = { 0x00 };
    //uint32_t keylength = 15;
    uint32_t keylength = 16;
    uint8_t nonce[16] = { 0x00 };
    uint32_t noncelength = 7;
    uint8_t input[21] = "ccm_test_text_sample";
    uint32_t inputlength = 21;
    uint8_t output[29] = { 0x00 };
    uint64_t outputlength = 0;
    uint32_t taglength = 8;
    uint8_t dec[21] = { 0x00 };
    uint64_t declength = 0;

    edge_random_byte(key, keylength);
    edge_random_byte(nonce, noncelength);

    printf("\n##======================     ccm_sample() start     ======================##\n");
    hexdump("input", input, inputlength);
    printf("\n *----------------------       edge_ccm_enc()       ------------------------\n");
    ret = edge_ccm_enc(cipher_id, key, keylength, NULL, 0, nonce, noncelength, input, inputlength, taglength, output, &outputlength);
    if (ret != 0) {
        printf("edge_ccm_enc fail [%d]\n", ret);
        return ret;
    }
    hexdump("output", output, outputlength);

    printf("\n *----------------------       edge_ccm_dec()       ------------------------\n");
    ret = edge_ccm_dec(cipher_id, key, keylength, NULL, 0, nonce, noncelength, output, outputlength, taglength, dec, &declength);
    if (ret != 0) {
        printf("edge_ccm_dec fail [%d]\n", ret);
        return ret;
    }
    hexdump("dec", dec, declength);

    printf("\n *----------------------  edge_ccm_dec() tag change ------------------------\n");
    memcpy(output + outputlength - taglength, "test_tag", taglength);
    ret = edge_ccm_dec(cipher_id, key, keylength, NULL, 0, nonce, noncelength, output, outputlength, taglength, dec, &declength);
    printf("return value = %d\n", ret);

    printf("\n##======================      ccm_sample() end      ======================##\n");

    return 0;
}

#if 0
int ccm_init_update_final_sample() {
    int ret = 0;

    int cipher_id = EDGE_CIPHER_ID_SEED128;
    uint8_t key[16] = { 0x00 };
    uint32_t keylength = 16;
    uint8_t aad[128] = { 0x00 };
    uint64_t aadlength = 128;
    uint8_t nonce[13] = { 0x00 };
    uint32_t noncelength = 13;
    uint8_t input[21] = "ccm_test_text_sample";
    uint32_t inputlength = 21;
    uint8_t output[33] = { 0x00 };
    uint64_t outputlength = 0;
    uint64_t outputtotal = 0;
    uint8_t tag[12] = { 0x00 };
    uint32_t taglength = 12;
    uint8_t dec[21] = { 0x00 };
    uint64_t declength = 0;
    uint64_t dectotal = 0;

    void* ctx = NULL;

    edge_random_byte(key, keylength);
    edge_random_byte(aad, aadlength);
    edge_random_byte(nonce, noncelength);

    printf("\n##================= ccm_init_update_final_sample() start =================##\n");
    hexdump("input", input, inputlength);
    do {
        ctx = edge_ccm_ctx_new();
        ret = edge_ccm_enc_init(ctx, cipher_id, key, keylength, aad, aadlength, nonce, noncelength, inputlength, taglength);
        if (ret != 0) {
            printf("edge_ccm_enc_init fail [%d]\n", ret);
            break;
        }

        printf("\n *----------------------    edge_ccm_enc_update()   ------------------------\n");
        ret = edge_ccm_enc_update(ctx, input, inputlength, output, &outputlength);
        if (ret != 0) {
            printf("edge_ccm_enc_update fail [%d]\n", ret);
            return ret;
        }
        outputtotal += outputlength;
        hexdump("output", output, outputtotal);

        printf("\n *----------------------    edge_ccm_enc_final()    ------------------------\n");
        ret = edge_ccm_enc_final(ctx, output + outputtotal, &outputlength);
        if (ret != 0) {
            printf("edge_ccm_enc_final fail [%d]\n", ret);
            return ret;
        }
        outputtotal += outputlength;
        hexdump("output", output, outputtotal);
        edge_ccm_ctx_free(ctx);

        ctx = edge_ccm_ctx_new();
        ret = edge_ccm_dec_init(ctx, cipher_id, key, keylength, aad, aadlength, nonce, noncelength, outputtotal, taglength);

        printf("\n *----------------------    edge_ccm_dec_update()   ------------------------\n");
        ret = edge_ccm_dec_update(ctx, output, outputtotal, dec, &declength);
        if (ret != 0) {
            printf("edge_ccm_dec_update fail [%d]\n", ret);
            return ret;
        }
        dectotal += declength;
        hexdump("dec", dec, dectotal);

        printf("\n *----------------------    edge_ccm_enc_final()    ------------------------\n");
        ret = edge_ccm_dec_final(ctx);
        if (ret != 0) {
            printf("edge_ccm_dec_final fail [%d]\n", ret);
            return ret;
        }
    } while (0);

    printf("\n##================== ccm_init_update_final_sample() end ==================##\n");
    edge_ccm_ctx_free(ctx);

    return 0;
}
#endif
