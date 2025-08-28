#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define MAX_BLOCK_DATA 256
#define HASH_SIZE 64
#define TARGET_PREFIX "0000"

// Block structure
typedef struct Block {
    uint32_t index;
    time_t timestamp;
    char data[MAX_BLOCK_DATA];
    char previous_hash[HASH_SIZE + 1];
    char hash[HASH_SIZE + 1];
    uint64_t nonce;
    struct Block* next;
} Block;

// Blockchain structure
typedef struct {
    Block* genesis;
    Block* last;
    uint32_t difficulty;
    size_t length;
} Blockchain;

// Function prototypes
Block* create_genesis_block(void);
Block* create_block(const char* data, Block* previous_block);
void calculate_block_hash(Block* block);
int mine_block(Block* block, uint32_t difficulty);
void free_block(Block* block);

Blockchain* create_blockchain(void);
int add_block(Blockchain* chain, const char* data);
int validate_blockchain(const Blockchain* chain);
void print_block(const Block* block);
void print_blockchain(const Blockchain* chain);
void free_blockchain(Blockchain* chain);

// Utility functions
int hash_starts_with_zeros(const char* hash, uint32_t zeros);
char* generate_block_data_string(const Block* block);

#endif // BLOCKCHAIN_H