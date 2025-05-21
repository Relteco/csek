# CSEK Protocol: Secure Implementation Guidelines

This document provides essential recommendations to ensure secure integration of the CSEK (Chaotic Stateless Ephemeral Keying) protocol in real-world applications.

---

## ✅ 1. Identity Management
- Use deterministic, unique IDs (e.g., UUID v5).
- Avoid using randomly generated ephemeral IDs.
- Do not transmit IDs over insecure channels.

---

## 🔐 2. Ephemeral Entropy (`r`) Generation
- Must be unique per message.
- Use secure random generators (e.g., `getrandom`, `crypto.randomBytes`).
- Never reuse an `r` value.

---

## 🧠 3. Secure Entropy Derivation
Replace naive hash:
```c
double x0 = naive_entropy(id_a, id_b);
```
With cryptographically secure method:
```c
x0 = SHA256(sorted_concat(ID_A, ID_B)) → float (0,1)
```

---

## 🔁 4. Avoid Keystream Reuse
- Always generate a new keystream per message.
- Use `ctx->x0 + r` as unique chaotic seed.

---

## 🔒 5. Optional KDF Usage
If input is user password or secret:
```c
x0 = Argon2id(ID_A || ID_B, salt, memory=64MB, iterations=3)
```

---

## 🛡 6. Side-Channel Protection
- Use timing-safe comparisons.
- Ensure constant-time XOR processing where possible.

---

## 🧾 7. Logging Warning
- Never log internal values like `r`, `x0`, or keystream in production.

---

## 📦 8. Message Structure
Transmit messages with structured metadata:
```json
{
  "r": 0.6789,
  "ciphertext": "<base64-encoded-bytes>"
}
```

---

## 📚 9. Licensing and Legal
- Protocol is licensed under **CC BY-NC 4.0**.
- Commercial use must receive written permission from the author.

---

## 📂 10. Deployment Checklist
- [ ] Unique `r` for every message
- [ ] Secure entropy derivation
- [ ] No plaintext reuse
- [ ] Side-channel safe implementation
- [ ] License terms respected

---

© 2025, Relteco. All rights reserved.