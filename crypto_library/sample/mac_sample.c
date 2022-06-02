#include "test_code.h"
#include "edge_crypto.h"
int mac_simple_sample();
int mac_init_update_final_sample();

int mac_sample() {
    int ret = 0;

    ret = mac_simple_sample();

    ret = mac_init_update_final_sample();

    return ret;
}

int mac_simple_sample() {
    int ret = 0;

    int mac_id = EDGE_HMAC_ID_SHA256;
    uint8_t key[37] = { 0x00 };
    uint32_t keylength = 37;
    uint8_t input[14] = "mac_test_text";
    uint32_t inputlength = 14;
    uint8_t* output = NULL;
    uint32_t outputlength = 0;

    output = (uint8_t*)calloc(1, 32);

    edge_random_byte(key, keylength);

    printf("\n##======================  mac_simple_sample() start ======================##\n");
    hexdump("input", input, inputlength);
    do {
        printf("\n *----------------------         edge_mac()         ------------------------\n");
        ret = edge_mac(mac_id, key, keylength, input, inputlength, output, &outputlength);
        if (ret != 0) break;
        hexdump("output", output, outputlength);
    } while (0);
    printf("\n##======================   mac_simple_sample() end  ======================##\n");

    free(output);

    return ret;
}

int mac_init_update_final_sample() {
    int ret = 0;

    int mac_id = EDGE_CMAC_ID_HIGHT;
    uint8_t key[16] = { 0x00 };
    uint32_t keylength = 16;
    uint8_t input[14] = "mac_test_text";
    uint32_t inputlength = 14;
    uint8_t* output = NULL;
    uint32_t outputlength = 0;

    void* ctx = NULL;

    output = (uint8_t*)calloc(1, 16);

    edge_random_byte(key, keylength);

    ctx = edge_mac_ctx_new();

    printf("\n##================= mac_init_update_final_sample() start =================##\n");
    hexdump("input", input, inputlength);
    do {
        printf("\n *----------------------       edge_mac_init()      ------------------------\n");
        ret = edge_mac_init(ctx, mac_id, key, keylength);
        if (ret != 0) break;
        printf("\n *----------------------      edge_mac_update()     ------------------------\n");
        ret = edge_mac_update(ctx, input, 5);
        if (ret != 0) break;
        ret = edge_mac_update(ctx, input + 5, 5);
        if (ret != 0) break;
        ret = edge_mac_update(ctx, input + 10, 4);
        if (ret != 0) break;
        printf("\n *----------------------      edge_mac_final()      ------------------------\n");
        ret = edge_mac_final(ctx, output, &outputlength);
        if (ret != 0) break;
        hexdump("output", output, outputlength);
    } while (0);
    printf("\n##================== mac_init_update_final_sample() end ==================##\n");

    edge_mac_ctx_free(ctx);
    free(output);

    return ret;
}
