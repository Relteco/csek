#include "../src/csek.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void test_encryption_cycle() {
    const char* id_a = "alpha";
    const char* id_b = "beta";
    double r = 0.12345;
    double mu = 3.99;

    const char* msg = "Test1234";
    size_t len = strlen(msg);

    CSEKContext ctx;
    assert(csek_init(&ctx, id_a, id_b, r, mu) == 0);

    uint8_t keystream[len];
    assert(csek_generate_keystream(&ctx, keystream, len) == 0);

    uint8_t ciphertext[len];
    uint8_t decrypted[len];

    csek_encrypt((const uint8_t*)msg, ciphertext, len, keystream);
    csek_decrypt(ciphertext, decrypted, len, keystream);

    assert(memcmp(msg, decrypted, len) == 0);
    printf("✅ test_encryption_cycle passed\n");
}

int main() {
    test_encryption_cycle();
    return 0;
}