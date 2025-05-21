#include "csek.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MESSAGE_LEN 256

void hex_dump(const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

double random_r() {
    return ((double)rand() + 1) / ((double)RAND_MAX + 2); // strictly in (0,1)
}

void simulate_message_exchange(const char* sender, const char* receiver, const char* message) {
    size_t msg_len = strlen(message);
    uint8_t keystream[msg_len];
    uint8_t ciphertext[msg_len];
    uint8_t decrypted[msg_len];

    double r = random_r();
    printf("\n[+] Ephemeral entropy (r): %.7f\n", r);

    // Sender context setup
    CSEKContext ctx_sender;
    if (csek_init(&ctx_sender, sender, receiver, r, CSEK_DEFAULT_MU) != 0) {
        fprintf(stderr, "[-] Failed to initialize sender context\n");
        return;
    }

    csek_generate_keystream(&ctx_sender, keystream, msg_len);
    csek_encrypt((const uint8_t*)message, ciphertext, msg_len, keystream);

    printf("[Sender] Plaintext: \"%s\"\n", message);
    printf("[Sender] Keystream: ");
    hex_dump(keystream, msg_len);
    printf("[Sender] Ciphertext: ");
    hex_dump(ciphertext, msg_len);

    // Receiver context setup
    CSEKContext ctx_receiver;
    if (csek_init(&ctx_receiver, sender, receiver, r, CSEK_DEFAULT_MU) != 0) {
        fprintf(stderr, "[-] Failed to initialize receiver context\n");
        return;
    }

    csek_generate_keystream(&ctx_receiver, keystream, msg_len);
    csek_decrypt(ciphertext, decrypted, msg_len, keystream);
    decrypted[msg_len] = '\0'; // null terminate

    printf("[Receiver] Keystream: ");
    hex_dump(keystream, msg_len);
    printf("[Receiver] Decrypted: \"%s\"\n", decrypted);
}

int main() {
    srand((unsigned int)time(NULL));

    char id_a[64], id_b[64], msg1[MAX_MESSAGE_LEN], msg2[MAX_MESSAGE_LEN];

    printf("=== CSEK Protocol Demo Chat ===\n");
    printf("Enter ID for Party A: ");
    fgets(id_a, sizeof(id_a), stdin);
    id_a[strcspn(id_a, "\n")] = '\0';

    printf("Enter ID for Party B: ");
    fgets(id_b, sizeof(id_b), stdin);
    id_b[strcspn(id_b, "\n")] = '\0';

    printf("\nEnter first message from A to B: ");
    fgets(msg1, sizeof(msg1), stdin);
    msg1[strcspn(msg1, "\n")] = '\0';

    simulate_message_exchange(id_a, id_b, msg1);

    printf("\nEnter second message (same or different): ");
    fgets(msg2, sizeof(msg2), stdin);
    msg2[strcspn(msg2, "\n")] = '\0';

    simulate_message_exchange(id_a, id_b, msg2);

    return 0;
}