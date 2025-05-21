# CSEK: Chaotic Stateless Ephemeral Keying

**CSEK** is a lightweight, cryptographically-inspired protocol that enables end-to-end encryption without persistent key storage or centralized authorities. It relies on chaotic key derivation based on sender and receiver identities combined with per-message entropy.

---

## 🔐 Key Features

- **Stateless**: No key storage or synchronization required.
- **Ephemeral**: Every message uses fresh entropy.
- **Symmetric**: Both parties derive the same keystream independently.
- **Chaotic**: Based on the logistic map to ensure sensitive dependence.
- **Identity-Based**: Uses public identifiers to derive encryption state.
- **Forward Secure**: No past or future message is compromised.

---

## 🧠 How It Works

Each party initializes the encryption context with:

- `id_a` and `id_b`: Sender and receiver identifiers (device IDs, usernames, etc.)
- `r`: Per-message random entropy in (0,1)
- `mu`: Logistic map control parameter (default `3.99`)

A chaotic keystream is then generated deterministically and XORed with the message.

---

## 🧪 Demo Example

```text
=== CSEK Protocol Demo Chat ===
Enter ID for Party A: abc
Enter ID for Party B: cba

Enter first message from A to B: selam

[+] Ephemeral entropy (r): 0.3935788
[Sender] Plaintext: "selam"
[Sender] Keystream: 53 E0 6D F9 17 
[Sender] Ciphertext: 20 85 01 98 7A 
[Receiver] Keystream: 53 E0 6D F9 17 
[Receiver] Decrypted: "selam"

Enter second message (same or different): selam

[+] Ephemeral entropy (r): 0.8796601
[Sender] Plaintext: "selam"
[Sender] Keystream: F4 2C 92 F9 17 
[Sender] Ciphertext: 87 49 FE 98 7A 
[Receiver] Keystream: F4 2C 92 F9 17 
[Receiver] Decrypted: "selam"
```

---

## 📁 Project Structure

```
csek/
├── LICENSE
├── Makefile
├── README.md
├── src/
│   ├── csek.h
│   └── csek.c
├── examples/
│   ├── demo.c
│   └── chat.c
├── tests/
│   └── test_csek.c
├── bin/
│   ├── demo
│   └── test_csek
└── run.sh
```

---

## ⚙️ Build & Run

```bash
# Build and run interactively
sh run.sh
```

Options:
- `1` Run demo
- `2` Run tests
- `3` Build only
- `4` Clean build
- `5` Run Chat

---

## 📜 License

Licensed under [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/)

---

## 🧾 Reference

> Cosar, B. (2025). *Stateless, Ephemeral Identity-Based Encryption via Chaotic Mutual Derivation*. Zenodo. https://doi.org/10.5281/zenodo.15382729

---

## 🌐 Authors & Affiliation

Developed independently by [Relteco](https://relteco.com) founder, with no institutional funding.

