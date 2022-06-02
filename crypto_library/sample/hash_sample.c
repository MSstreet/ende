#include "test_code.h"
#include "edge_crypto.h"

int hash_simple_sample();
int hash_init_update_final_sample();

int hash_sample() {
    int ret = 0;

    ret = hash_simple_sample();

    ret = hash_init_update_final_sample();

    return ret;
}

int hash_simple_sample() {
    int ret = 0;

    int hash_id = EDGE_HASH_ID_SHA256;
    uint8_t input[15] = "hash_test_text";
    uint32_t inputlength = 15;
    uint8_t* output = NULL;
    uint32_t outputlength = 0;

    output = (uint8_t*)calloc(1, 32);

    printf("\n##====================== hash_simple_sample() start ======================##\n");
    hexdump("input", input, inputlength);
    do {
        printf("\n *----------------------         edge_hash()        ------------------------\n");
        ret = edge_hash(hash_id, input, inputlength, output, &outputlength);
        if (ret != 0) break;
        hexdump("output", output, outputlength);
    } while (0);
    printf("\n##======================  hash_simple_sample() end  ======================##\n");

    free(output);

    return ret;
}

int hash_init_update_final_sample() {
    int ret = 0;

    int hash_id = EDGE_HASH_ID_SHA256;
    uint8_t input[15] = "hash_test_text";
    uint32_t inputlength = 15;
    uint8_t* output = NULL;
    uint32_t outputlength = 0;

    void* ctx = NULL;

    output = (uint8_t*)calloc(1, 32);

    ctx = edge_hash_ctx_new();

    printf("\n##================ hash_init_update_final_sample() start =================##\n");
    hexdump("input", input, inputlength);
    do {
        printf("\n *----------------------      edge_hash_init()      ------------------------\n");
        ret = edge_hash_init(ctx, hash_id);
        if (ret != 0) break;
        printf("\n *----------------------     edge_hash_update()     ------------------------\n");
        ret = edge_hash_update(ctx, input, 5);
        if (ret != 0) break;
        ret = edge_hash_update(ctx, input + 5, 5);
        if (ret != 0) break;
        ret = edge_hash_update(ctx, input + 10, 5);
        if (ret != 0) break;
        printf("\n *----------------------     edge_hash_final()      ------------------------\n");
        ret = edge_hash_final(ctx, output, &outputlength);
        if (ret != 0) break;
        hexdump("output", output, outputlength);
    } while (0);
    printf("\n##================= hash_init_update_final_sample() end ==================##\n");

    edge_hash_ctx_free(ctx);
    free(output);

    return ret;
}
