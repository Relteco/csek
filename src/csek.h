#ifndef CSEK_H
#define CSEK_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Default chaos parameter for the logistic map
#define CSEK_DEFAULT_MU 3.99

// CSEK protocol context structure
typedef struct {
    double x0;        // Shared entropy seed
    double r;         // Per-message random scalar (ephemeral)
    double mu;        // Chaos control parameter (logistic map)
} CSEKContext;

/**
 * Initialize the CSEK encryption context using sender/receiver identifiers and entropy scalar.
 * 
 * @param ctx   Pointer to the CSEKContext to initialize
 * @param id_a  Sender identifier (e.g., "device123")
 * @param id_b  Receiver identifier
 * @param r     Per-message random scalar (must be in range (0,1))
 * @param mu    Logistic map parameter (suggested: 3.99)
 * @return      0 on success, -1 on error
 */
int csek_init(CSEKContext* ctx, const char* id_a, const char* id_b, double r, double mu);

/**
 * Generate a keystream of specified length using the initialized context.
 * 
 * @param ctx       Pointer to initialized CSEKContext
 * @param keystream Output buffer to fill with keystream bytes
 * @param length    Number of bytes to generate
 * @return          0 on success, -1 on failure
 */
int csek_generate_keystream(CSEKContext* ctx, uint8_t* keystream, size_t length);

/**
 * Encrypt a message using the XOR of the plaintext and keystream.
 * 
 * @param plaintext Input message buffer
 * @param ciphertext Output buffer for the encrypted message
 * @param length    Message length in bytes
 * @param keystream Keystream buffer of equal length
 */
void csek_encrypt(const uint8_t* plaintext, uint8_t* ciphertext, size_t length, const uint8_t* keystream);

/**
 * Decrypt a message using the XOR of the ciphertext and keystream.
 * 
 * @param ciphertext Input encrypted buffer
 * @param plaintext  Output buffer for the decrypted message
 * @param length     Message length in bytes
 * @param keystream  Keystream buffer used during encryption
 */
void csek_decrypt(const uint8_t* ciphertext, uint8_t* plaintext, size_t length, const uint8_t* keystream);

#ifdef __cplusplus
}
#endif

#endif // CSEK_H