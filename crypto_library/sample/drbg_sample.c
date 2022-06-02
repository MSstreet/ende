#include "test_code.h"
#include "edge_crypto.h"
int drbg_sample1();
int drbg_sample2();

int drbg_sample() {
    int ret = 0;

    ret = drbg_sample1();

    ret = drbg_sample2();

    return ret;
}

int drbg_sample1() {
    int ret = 0;

    int drbg_id = EDGE_DRBG_ID_SHA256;
    uint8_t entropy[128] = { 0x00, };   // set custom entropy
    uint32_t entropy_size = 128;
    uint8_t output[128] = { 0x00 };
    uint32_t outputlength = 128;

    void *ctx = NULL;

    ctx = edge_drbg_ctx_new(drbg_id);
    printf("\n##======================    drbg_sample1() start    ======================##\n");
    do {
        printf("\n *----------------------      edge_drbg_init()      ------------------------\n");
        ret = edge_drbg_init(ctx, entropy, entropy_size, NULL, 0, NULL, 0);
        if (ret != 0) break;
        printf("\n *----------------------       edge_drbg_gen()      ------------------------\n");
        ret = edge_drbg_gen(ctx, outputlength * 8, output, NULL, 0);
        if (ret != 0) break;
        hexdump("random", output, outputlength);

        memcpy(entropy, output, outputlength);
        printf("\n *----------------------     edge_drbg_reseed()     ------------------------\n");
        ret = edge_drbg_reseed(ctx, entropy, entropy_size, NULL, 0);
        if (ret != 0) break;
        printf("\n *----------------------       edge_drbg_gen()      ------------------------\n");
        ret = edge_drbg_gen(ctx, outputlength * 8, output, NULL, 0);
        if (ret != 0) break;
        hexdump("random", output, outputlength);
    } while (0);
    printf("\n##======================     drbg_sample1() end     ======================##\n");
    edge_drbg_ctx_free(ctx);

    return ret;
}

int drbg_sample2() {
    int ret = 0;

    int drbg_id = EDGE_DRBG_ID_SEED128;
    uint8_t entropy[128] = { 0x00, };   // set custom entropy
    uint32_t entropy_size = 128;
    uint8_t entropy2[128] = { 0x00, };   // set custom entropy
    uint32_t entropy2_size = 128;
    uint8_t nonce[64] = { 0x00 };       // set custom nonce
    uint32_t noncelength = 64;
    uint8_t additional_input[29] = "additional input sample text";
    uint32_t additional_input_length = 28;
    uint8_t output[128] = { 0x00 };
    uint32_t outputlength = 128;

    void *ctx = NULL;
    unsigned char a;

    for (a = 0; a < 128; a++) {
        entropy2[a] = a;
    }

    ctx = edge_drbg_ctx_new(drbg_id);
    edge_drbg_ctx_setDF(ctx, 1);        // df use
    printf("\n##======================    drbg_sample2() start    ======================##\n");
    do {
        printf("\n *----------------------      edge_drbg_init()      ------------------------\n");
        ret = edge_drbg_init(ctx, entropy, entropy_size, nonce, noncelength, additional_input, additional_input_length);
        if (ret != 0) break;
        printf("\n *----------------------   edge_drbg_gen_with_pr()  ------------------------\n");
        ret = edge_drbg_gen_with_pr(ctx, outputlength * 8, output, entropy2, entropy2_size, NULL, 0);
        if (ret != 0) break;
        hexdump("random", output, outputlength);

        memcpy(entropy, output, outputlength);
        printf("\n *----------------------     edge_drbg_reseed()     ------------------------\n");
        ret = edge_drbg_reseed(ctx, entropy, entropy_size, NULL, 0);
        if (ret != 0) break;
        printf("\n *----------------------   edge_drbg_gen_with_pr()  ------------------------\n");
        ret = edge_drbg_gen_with_pr(ctx, outputlength * 8, output, entropy2, entropy2_size, NULL, 0);
        if (ret != 0) break;
        hexdump("random", output, outputlength);
    } while (0);
    printf("\n##======================     drbg_sample2() end     ======================##\n");

    edge_drbg_ctx_free(ctx);

    return ret;
}
