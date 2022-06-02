#include "test_code.h"
#include "edge_crypto.h"

int enc_dec_sample();
int init_update_final_sample();
int stream_mode_sample();
int symmetric_sample() {
    int     ret = 0;

	do {
		ret = enc_dec_sample();
		if (ret != 0)		break;

		ret = init_update_final_sample();
		if (ret != 0)		break;

		ret = stream_mode_sample();
		if (ret != 0)		break;
	} while(0);

    return ret;
}

int enc_dec_sample() {
    int     ret = 0;

    EDGE_CIPHER_PARAMETERS  param;

    int          cipher_id    = EDGE_CIPHER_ID_ARIA128;
    uint8_t      key[16]      = { 0x00, };
    uint32_t     keylength    = 0;
    uint8_t      iv[16]       = { 0x00, };
    uint32_t     ivlength     = 0;
    uint8_t *    input        = "test text sample";
    uint32_t     inputlength  = 16;
    uint8_t      output[32]   = { 0x00, };
    uint32_t     outputlength = 0;
    uint8_t      dec[32]      = { 0x00, };
    uint32_t     declength    = 0;

    memset(&param, 0, sizeof(EDGE_CIPHER_PARAMETERS));

    keylength = 16;
    ivlength  = 16;

    param.m_mode    = EDGE_CIPHER_MODE_CBC;
    param.m_padding = EDGE_CIPHER_PADDING_PKCS5;

    edge_random_byte(key, keylength);
    edge_random_byte(iv, ivlength);

    memcpy(param.m_modeparam.m_iv, iv, ivlength);
    param.m_modeparam.m_ivlength = ivlength;

    printf("\n##======================   enc_dec_sample() start   ======================##\n");
    hexdump("input", input, inputlength);
    printf("\n *----------------------         edge_enc()         ------------------------\n");
    ret = edge_enc(cipher_id, key, keylength, &param, input, inputlength, output, &outputlength);
	print_result("edge_enc", ret);
	if (ret != 0)	return ret;
    hexdump("output", output, outputlength);
    printf("\n *----------------------         edge_dec()         ------------------------\n");
    ret = edge_dec(cipher_id, key, keylength, &param, output, outputlength, dec, &declength);
    if (ret != 0) {
        printf("edge_dec fail [%d]\n", ret);
        return ret;
    }
    hexdump("dec", dec, declength);

    printf("\n##======================    enc_dec_sample() end    ======================##\n");

    return ret;
}

int init_update_final_sample() {
    int ret = 0;
    EDGE_CIPHER_PARAMETERS  param;

    int          cipher_id     = EDGE_CIPHER_ID_SEED128;
    uint8_t      key[16]       = { 0x00, };
    uint32_t     keylength     = 0;
    uint8_t      iv[16]        = { 0x00, };
    uint32_t     ivlength      = 0;
    uint8_t      input[17]     = "test text sample";
    uint32_t     inputlength   = 16;
    uint8_t      output[32]    = { 0x00, };
    uint32_t     outputlength  = 0;
    uint32_t     outputtotal   = 0;
    uint8_t      dec[32]       = { 0x00, };
    uint32_t     declength     = 0;
    uint32_t     dectotal      = 0;
    uint32_t     paddinglength = 0;

    void*        ctx           = NULL;

    ctx = edge_ctx_new();

    memset(&param, 0, sizeof(EDGE_CIPHER_PARAMETERS));

    keylength = 16;
    ivlength = 16;

    param.m_mode = EDGE_CIPHER_MODE_CFB;
    param.m_padding = EDGE_CIPHER_PADDING_PKCS5;

    edge_random_byte(key, keylength);
    edge_random_byte(iv, ivlength);
    memcpy(param.m_modeparam.m_iv, iv, ivlength);
    param.m_modeparam.m_ivlength = ivlength;
    param.m_modeparam.m_modesize = 16;

    printf("\n##=================== init_update_final_sample() start ===================##\n");
    hexdump("input", input, inputlength);

    do {
        ret = edge_enc_init(ctx, cipher_id, key, keylength, &param);
        if (ret != 0) {
            printf("edge_enc_init fail [%d]\n", ret);
            break;
        }

        ret = edge_enc_update(ctx, input, inputlength, output, &outputlength);
        if (ret != 0) {
            printf("edge_enc_update fail [%d]\n", ret);
            break;
        }
        outputtotal += outputlength;
        printf("\n *----------------------      edge_enc_update()     ------------------------\n");
        hexdump("output", output, outputtotal);

        ret = edge_enc_final(ctx, output + outputtotal, &outputlength);
        if (ret != 0) {
            printf("edge_enc_final fail [%d]\n", ret);
            break;
        }
        outputtotal += outputlength;
        printf("\n *----------------------      edge_enc_final()      ------------------------\n");
        hexdump("output", output, outputtotal);

        ret = edge_dec_init(ctx, cipher_id, key, keylength, &param);
        if (ret != 0) {
            printf("edge_dec_init fail [%d]\n", ret);
            break;
        }

        ret = edge_dec_update(ctx, output, outputtotal, dec, &declength);
        if (ret != 0) {
            printf("edge_dec_update fail [%d]\n", ret);
            break;
        }
        dectotal += declength;
        printf("\n *----------------------      edge_dec_update()     ------------------------\n");
        hexdump("dec", dec, declength);

        ret = edge_dec_final(ctx, dec + dectotal, &declength, &paddinglength);
        if (ret != 0) {
            printf("edge_dec_final fail [%d]\n", ret);
            break;
        }
        dectotal += declength;
        /* TODO  sample
        ret = edge_dec_final(ctx, NULL, NULL, &paddinglength);
        */

        printf("\n *----------------------      edge_dec_final()      ------------------------\n");
        hexdump("dec", dec, dectotal - paddinglength);

    } while (0);
    printf("\n##==================== init_update_final_sample() end ====================##\n");
    edge_ctx_free(ctx);

    return ret;
}

int stream_mode_sample() {
    int ret = 0;
    EDGE_CIPHER_PARAMETERS param;
    int cipher_id = EDGE_CIPHER_ID_HIGHT;

    unsigned char key[16] = { 0x00, };
    int keylength = 0;
    unsigned char iv[16] = { 0x00, };
    int ivlength = 0;
    unsigned char *input = "stream mode test text";
    int inputlength = 21;
    unsigned char output[21] = { 0x00, };
    int outputlength = 0;
    int outputtotal = 0;
    unsigned char dec[30] = { 0x00, };
    int declength = 0;
    int dectotal = 0;
    int paddinglength = 0;

    void* ctx = NULL;

    memset(&param, 0, sizeof(EDGE_CIPHER_PARAMETERS));

    keylength = 16;
    ivlength = 8;

    param.m_mode = EDGE_CIPHER_MODE_CFB;
    param.m_padding = EDGE_CIPHER_PADDING_NONE;

    edge_random_byte(key, keylength);
    edge_random_byte(iv, ivlength);
    memcpy(param.m_modeparam.m_iv, iv, ivlength);
    param.m_modeparam.m_ivlength = ivlength;
    param.m_modeparam.m_modesize = 1;

    printf("\n##====================== stream_mode_sample() start ======================##\n");
    hexdump("input", input, inputlength);

    do {
        ctx = edge_ctx_new();
        ret = edge_enc_init(ctx, cipher_id, key, keylength, &param);
        if (ret != 0) {
            printf("edge_enc_init fail [%d]\n", ret);
            break;
        }

        ret = edge_enc_update(ctx, input, 15, output + outputtotal, &outputlength);
        if (ret != 0) {
            printf("edge_enc_update fail [%d]\n", ret);
            break;
        }
        outputtotal += outputlength;

        ret = edge_enc_update(ctx, input + 15, 6, output + outputtotal, &outputlength);
        if (ret != 0) {
            printf("edge_enc_update fail [%d]\n", ret);
            break;
        }
        outputtotal += outputlength;
        printf("\n *----------------------      edge_enc_update()     ------------------------\n");
        hexdump("output", output, outputtotal);

        ret = edge_enc_final(ctx, output + outputtotal, &outputlength);
        if (ret != 0) {
            printf("edge_enc_final fail [%d]\n", ret);
            break;
        }
        outputtotal += outputlength;
        printf("\n *----------------------      edge_enc_final()      ------------------------\n");
        hexdump("output", output, outputtotal);
        edge_ctx_free(ctx);

        ctx = edge_ctx_new();
        ret = edge_dec_init(ctx, cipher_id, key, keylength, &param);
        if (ret != 0) {
            printf("edge_dec_init fail [%d]\n", ret);
            break;
        }
        
        ret = edge_dec_update(ctx, output, 15, dec + dectotal, &declength);
        if (ret != 0) {
            printf("edge_dec_update fail [%d]\n", ret);
            break;
        }
        dectotal += declength;

        ret = edge_dec_update(ctx, output + 15, 6, dec + dectotal, &declength);
        if (ret != 0) {
            printf("edge_dec_update fail [%d]\n", ret);
            break;
        }
        dectotal += declength;
        printf("\n *----------------------      edge_dec_update()     ------------------------\n");
        hexdump("dec", dec, dectotal);

        ret = edge_dec_final(ctx, dec + dectotal, &declength, &paddinglength);
        if (ret != 0) {
            printf("edge_dec_final fail [%d]\n", ret);
            break;
        }

        dectotal += declength;
        printf("\n *----------------------      edge_dec_final()      ------------------------\n");
        hexdump("dec", dec, dectotal);

    } while (0);
    printf("\n##======================  stream_mode_sample() end  ======================##\n");
    edge_ctx_free(ctx);

    return ret;
}
