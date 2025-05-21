#include "../src/csek.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char* id_a = "deviceA";
    const char* id_b = "deviceB";
    const char* message = "Hello from CSEK!";
    double r = 0.54321;
    double mu = CSEK_DEFAULT_MU;

    CSEKContext ctx;
    if (csek_init(&ctx, id_a, id_b, r, mu) != 0) {
        fprintf(stderr, "Failed to initialize CSEK context\n");
        return 1;
    }

    size_t len = strlen(message);
    uint8_t keystream[len];
    uint8_t ciphertext[len];
    uint8_t decrypted[len];

    if (csek_generate_keystream(&ctx, keystream, len) != 0) {
        fprintf(stderr, "Failed to generate keystream\n");
        return 1;
    }

    csek_encrypt((const uint8_t*)message, ciphertext, len, keystream);
    csek_decrypt(ciphertext, decrypted, len, keystream);

    printf("Original : %s\n", message);
    printf("Encrypted: ");
    for (size_t i = 0; i < len; ++i)
        printf("%02X ", ciphertext[i]);
    printf("\n");

    printf("Decrypted: %.*s\n", (int)len, decrypted);
    return 0;
}