#include <stdio.h>
#include <stdlib.h>
#include "blockchain.h"

void demo_blockchain() {
    printf("🚀 Creating Blockchain with Genesis Block...\n");
    Blockchain* chain = create_blockchain();
    if (!chain) {
        printf("❌ Failed to create blockchain!\n");
        return;
    }

    printf("✅ Genesis Block Created and Mined!\n\n");

    // Add first block
    printf("➕ Adding Block 1: 'Alice sends 5 BTC to Bob'...\n");
    if (add_block(chain, "Alice sends 5 BTC to Bob")) {
        printf("✅ Block 1 Mined Successfully!\n\n");
    } else {
        printf("❌ Failed to mine Block 1!\n");
    }

    // Add second block
    printf("➕ Adding Block 2: 'Bob sends 2 BTC to Charlie'...\n");
    if (add_block(chain, "Bob sends 2 BTC to Charlie")) {
        printf("✅ Block 2 Mined Successfully!\n\n");
    } else {
        printf("❌ Failed to mine Block 2!\n");
    }

    // Add third block
    printf("➕ Adding Block 3: 'Charlie sends 1 BTC to Dave'...\n");
    if (add_block(chain, "Charlie sends 1 BTC to Dave")) {
        printf("✅ Block 3 Mined Successfully!\n\n");
    } else {
        printf("❌ Failed to mine Block 3!\n");
    }

    // Print the entire blockchain
    print_blockchain(chain);

    // Validate the blockchain
    printf("\n🔍 Validating Blockchain Integrity...\n");
    if (validate_blockchain(chain)) {
        printf("✅ Blockchain is VALID! All blocks are properly linked and hashes are correct.\n");
    } else {
        printf("❌ Blockchain is INVALID! There's a problem with the chain.\n");
    }

    // Clean up
    printf("\n🗑️  Cleaning up memory...\n");
    free_blockchain(chain);
    printf("✅ Memory cleanup completed!\n");
}

int main() {
    printf("===================================================\n");
    printf("           SIMPLE BLOCKCHAIN PROTOTYPE\n");
    printf("===================================================\n\n");

    printf("📋 Features:\n");
    printf("• SHA-256 Cryptographic Hashing\n");
    printf("• Proof-of-Work Mining (4 leading zeros)\n");
    printf("• Blockchain Validation\n");
    printf("• Linked List Structure\n");
    printf("• Memory Management\n\n");

    demo_blockchain();

    printf("\n===================================================\n");
    printf("          BLOCKCHAIN DEMO COMPLETED!\n");
    printf("===================================================\n");

    return 0;
}