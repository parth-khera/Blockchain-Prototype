#include "blockchain.h"
#include "sha256.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Block* create_genesis_block(void) {
    Block* block = (Block*)malloc(sizeof(Block));
    if (!block) {
        return NULL;
    }

    block->index = 0;
    block->timestamp = time(NULL);
    strncpy(block->data, "Genesis Block", MAX_BLOCK_DATA - 1);
    block->data[MAX_BLOCK_DATA - 1] = '\0';
    strncpy(block->previous_hash, "0", HASH_SIZE);
    block->previous_hash[HASH_SIZE] = '\0';
    block->nonce = 0;
    block->next = NULL;

    calculate_block_hash(block);
    return block;
}

Block* create_block(const char* data, Block* previous_block) {
    if (!previous_block) {
        return NULL;
    }

    Block* block = (Block*)malloc(sizeof(Block));
    if (!block) {
        return NULL;
    }

    block->index = previous_block->index + 1;
    block->timestamp = time(NULL);
    strncpy(block->data, data, MAX_BLOCK_DATA - 1);
    block->data[MAX_BLOCK_DATA - 1] = '\0';
    strncpy(block->previous_hash, previous_block->hash, HASH_SIZE);
    block->previous_hash[HASH_SIZE] = '\0';
    block->nonce = 0;
    block->next = NULL;

    calculate_block_hash(block);
    return block;
}

void calculate_block_hash(Block* block) {
    if (!block) return;

    char* block_data_str = generate_block_data_string(block);
    if (!block_data_str) return;

    char* hash_hex = sha256_hex((uint8_t*)block_data_str, strlen(block_data_str));
    if (hash_hex) {
        strncpy(block->hash, hash_hex, HASH_SIZE);
        block->hash[HASH_SIZE] = '\0';
        free(hash_hex);
    }
    free(block_data_str);
}

int mine_block(Block* block, uint32_t difficulty) {
    if (!block) return 0;

    char target[HASH_SIZE + 1];
    memset(target, '0', difficulty);
    target[difficulty] = '\0';

    uint64_t start_nonce = block->nonce;
    
    while (1) {
        calculate_block_hash(block);
        
        if (hash_starts_with_zeros(block->hash, difficulty)) {
            return 1;
        }
        
        block->nonce++;
        
        // Prevent infinite loop by checking for overflow
        if (block->nonce <= start_nonce) {
            // Overflow occurred, break to prevent infinite loop
            break;
        }
    }
    
    return 0;
}

char* generate_block_data_string(const Block* block) {
    if (!block) return NULL;

    char* str = (char*)malloc(MAX_BLOCK_DATA + HASH_SIZE * 2 + 50);
    if (!str) return NULL;

    snprintf(str, MAX_BLOCK_DATA + HASH_SIZE * 2 + 50, 
             "%u%ld%s%s%lu", 
             block->index, block->timestamp, block->data, 
             block->previous_hash, block->nonce);
    
    return str;
}

int hash_starts_with_zeros(const char* hash, uint32_t zeros) {
    if (!hash || zeros > HASH_SIZE) return 0;
    
    for (uint32_t i = 0; i < zeros; i++) {
        if (hash[i] != '0') {
            return 0;
        }
    }
    return 1;
}

Blockchain* create_blockchain(void) {
    Blockchain* chain = (Blockchain*)malloc(sizeof(Blockchain));
    if (!chain) {
        return NULL;
    }

    chain->genesis = create_genesis_block();
    if (!chain->genesis) {
        free(chain);
        return NULL;
    }

    chain->last = chain->genesis;
    chain->difficulty = 4; // Start with 4 leading zeros
    chain->length = 1;

    return chain;
}

int add_block(Blockchain* chain, const char* data) {
    if (!chain || !data) return 0;

    Block* new_block = create_block(data, chain->last);
    if (!new_block) return 0;

    if (mine_block(new_block, chain->difficulty)) {
        chain->last->next = new_block;
        chain->last = new_block;
        chain->length++;
        return 1;
    } else {
        free_block(new_block);
        return 0;
    }
}

int validate_blockchain(const Blockchain* chain) {
    if (!chain || !chain->genesis) return 0;

    Block* current = chain->genesis;
    Block* previous = NULL;

    while (current) {
        // Check if hash is valid
        char* current_hash = strdup(current->hash);
        calculate_block_hash(current);
        
        if (strcmp(current_hash, current->hash) != 0) {
            free(current_hash);
            return 0;
        }
        free(current_hash);

        // Check previous hash link (except for genesis)
        if (previous && strcmp(current->previous_hash, previous->hash) != 0) {
            return 0;
        }

        previous = current;
        current = current->next;
    }

    return 1;
}

void print_block(const Block* block) {
    if (!block) return;

    printf("╔═══════════════════════════════════════════════════\n");
    printf("║ Block #%u\n", block->index);
    printf("║ Timestamp: %s", ctime(&block->timestamp));
    printf("║ Data: %s\n", block->data);
    printf("║ Previous Hash: %s\n", block->previous_hash);
    printf("║ Hash: %s\n", block->hash);
    printf("║ Nonce: %lu\n", block->nonce);
    printf("╚═══════════════════════════════════════════════════\n");
}

void print_blockchain(const Blockchain* chain) {
    if (!chain) return;

    printf("\n═══════════════════════════════════════════════════\n");
    printf("           BLOCKCHAIN (Length: %zu)\n", chain->length);
    printf("═══════════════════════════════════════════════════\n\n");

    Block* current = chain->genesis;
    while (current) {
        print_block(current);
        if (current->next) {
            printf("                    ↓\n");
            printf("                    ↓\n");
        }
        current = current->next;
    }
}

void free_block(Block* block) {
    if (block) {
        free(block);
    }
}

void free_blockchain(Blockchain* chain) {
    if (!chain) return;

    Block* current = chain->genesis;
    while (current) {
        Block* next = current->next;
        free_block(current);
        current = next;
    }
    free(chain);
}