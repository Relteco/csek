# CSEK: Chaotic Stateless Ephemeral Keying Protocol


# CSEK - Chaotic Stateless Ephemeral Keying

**CSEK** is a lightweight encryption protocol that provides identity-bound, sessionless, and forward-secret communication without key exchange. Based on chaotic keystream generation and ephemeral entropy, it offers strong unpredictability with minimal implementation overhead.

> Stateless. Ephemeral. Deterministic. Secure.

## Features
- Stateless design (no session/key management)
- Per-message randomization (ephemeral scalar `r`)
- Chaotic keystream generation
- XOR-based symmetric encryption
- Forward secrecy by design
- Suitable for IoT, embedded, and decentralized systems

## Build

```bash
make