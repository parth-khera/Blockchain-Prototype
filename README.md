# Simple Blockchain Prototype in C

A minimal blockchain implementation in C that demonstrates core blockchain concepts including cryptographic hashing, proof-of-work mining, and chain validation.

## Features

- **Block Structure**: Each block contains index, timestamp, data, previous hash, current hash, and nonce
- **SHA-256 Hashing**: Custom implementation of SHA-256 cryptographic hash function
- **Proof-of-Work**: Mining algorithm that requires hash to start with 4 leading zeros
- **Blockchain Validation**: Chain integrity verification through hash validation
- **Memory Management**: Proper allocation and cleanup of all resources
- **Modular Design**: Clean separation of concerns with multiple source files

## Project Structure

```
blockchain_project/
├── src/
│   ├── main.c          # Main demonstration program
│   ├── blockchain.c    # Blockchain core implementation
│   ├── blockchain.h    # Blockchain header file
│   ├── sha256.c        # SHA-256 implementation
│   └── sha256.h        # SHA-256 header file
├── Makefile           # Build configuration
└── README.md          # This file
```

## Building the Project

```bash
cd blockchain_project
make
```

This will create the executable in the `bin/` directory.

## Running the Demo

```bash
make run
```

Or directly:
```bash
./bin/blockchain
```

## Demo Output

The program will:
1. Create a genesis block
2. Add 3 blocks with sample transaction data
3. Mine each block using proof-of-work
4. Print the entire blockchain structure
5. Validate the blockchain integrity

## Key Components

### Block Structure
```c
typedef struct Block {
    uint32_t index;
    time_t timestamp;
    char data[256];
    char previous_hash[65];
    char hash[65];
    uint64_t nonce;
    struct Block* next;
} Block;
```

### Blockchain Functions
- `create_blockchain()` - Initialize new blockchain with genesis block
- `add_block()` - Create and mine new block
- `mine_block()` - Proof-of-work mining algorithm
- `validate_blockchain()` - Verify chain integrity
- `print_blockchain()` - Display all blocks

### SHA-256 Implementation
Custom implementation that includes:
- SHA-256 context management
- Block processing
- Hash computation
- Hex string conversion

## Proof-of-Work

The mining algorithm requires finding a nonce such that the block's SHA-256 hash starts with "0000". This simulates the computational work required in real blockchains.

## Memory Management

All memory is properly allocated and freed:
- Dynamic allocation for blocks
- String buffers for hash storage
- Complete cleanup on exit

## Requirements

- GCC compiler
- Standard C library
- POSIX-compliant system (for time.h)

## Learning Objectives

This project demonstrates:
- Cryptographic hash functions
- Linked list data structures
- Proof-of-work consensus
- Memory management in C
- Modular program design
- Blockchain fundamentals

## Limitations

This is an educational prototype and should not be used for real cryptocurrency applications. Real blockchain systems have additional security features, peer-to-peer networking, and more sophisticated consensus mechanisms.