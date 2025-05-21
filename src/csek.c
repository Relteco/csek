#include "csek.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/**
 * Generates a pseudo-random float in the range (0,1) by combining two IDs.
 * This is NOT cryptographically secure. It's only meant for demonstration or prototyping.
 * 
 * @param id_a First identity (e.g., device/user ID).
 * @param id_b Second identity.
 * @return A deterministic float based on both identities, in the range (0,1).
 */
static double naive_entropy(const char* id_a, const char* id_b) {
    const char* first = strcmp(id_a, id_b) <= 0 ? id_a : id_b;
    const char* second = strcmp(id_a, id_b) <= 0 ? id_b : id_a;

    unsigned long hash = 5381;
    const char* p;

    for (p = first; *p; ++p) hash = ((hash << 5) + hash) + *p;
    for (p = second; *p; ++p) hash = ((hash << 5) + hash) + *p;

    return (double)(hash % 10000000) / 10000000.0;
}

/**
 * Initializes the CSEK context using identities, entropy value, and chaos parameter.
 *
 * @param ctx Pointer to the context to initialize.
 * @param id_a Sender identity.
 * @param id_b Receiver identity.
 * @param r Per-message entropy (random float in (0,1)).
 * @param mu Chaos parameter for logistic map (usually between 3.57 and 4.0).
 * @return 0 on success, -1 on error.
 */
int csek_init(CSEKContext* ctx, const char* id_a, const char* id_b, double r, double mu) {
    if (!ctx || !id_a || !id_b || r <= 0.0 || r >= 1.0 || mu <= 3.57 || mu >= 4.0) {
        return -1;
    }

    ctx->x0 = naive_entropy(id_a, id_b);
    ctx->r = r;
    ctx->mu = mu;
    return 0;
}

/**
 * Generates a keystream using the chaotic logistic map.
 *
 * @param ctx Initialized CSEK context.
 * @param keystream Output buffer for the generated keystream (must be at least 'length' bytes).
 * @param length Number of keystream bytes to generate.
 * @return 0 on success, -1 on error.
 */
int csek_generate_keystream(CSEKContext* ctx, uint8_t* keystream, size_t length) {
    if (!ctx || !keystream) return -1;

    double x = ctx->x0 + ctx->r;
    if (x <= 0.0 || x >= 1.0) x = fmod(x, 1.0);

    for (size_t i = 0; i < length; i++) {
        x = ctx->mu * x * (1.0 - x);
        keystream[i] = (uint8_t)(fmod(x * 256.0, 256.0));
    }

    return 0;
}

/**
 * Encrypts the plaintext using the generated keystream with XOR operation.
 *
 * @param plaintext Input data to encrypt.
 * @param ciphertext Output buffer for the encrypted data.
 * @param length Number of bytes to encrypt.
 * @param keystream Keystream buffer used for XOR encryption.
 */
void csek_encrypt(const uint8_t* plaintext, uint8_t* ciphertext, size_t length, const uint8_t* keystream) {
    for (size_t i = 0; i < length; i++) {
        ciphertext[i] = plaintext[i] ^ keystream[i];
    }
}

/**
 * Decrypts the ciphertext using the same keystream (XOR decryption).
 *
 * @param ciphertext Input encrypted data.
 * @param plaintext Output buffer for decrypted data.
 * @param length Number of bytes to decrypt.
 * @param keystream Keystream buffer used for XOR decryption (same as used in encryption).
 */
void csek_decrypt(const uint8_t* ciphertext, uint8_t* plaintext, size_t length, const uint8_t* keystream) {
    for (size_t i = 0; i < length; i++) {
        plaintext[i] = ciphertext[i] ^ keystream[i];
    }
}