# Compilation Guide

## To compile this blockchain project:

### On Linux/macOS:
```bash
cd blockchain_project
gcc -Wall -Wextra -std=c99 -O2 src/*.c -o blockchain
./blockchain
```

### On Windows with MinGW:
```bash
cd blockchain_project
gcc -Wall -Wextra -std=c99 -O2 src/main.c src/blockchain.c src/sha256.c -o blockchain.exe
blockchain.exe
```

### On Windows with Visual Studio:
1. Open Developer Command Prompt
2. Navigate to project directory
3. Run:
```cmd
cl /W4 /O2 src\main.c src\blockchain.c src\sha256.c
main.exe
```

## Expected Output:
The program will demonstrate:
- Creating a genesis block
- Mining 3 additional blocks with proof-of-work
- Printing the complete blockchain structure
- Validating the chain integrity

## Sample Output Preview:
```
===================================================
           SIMPLE BLOCKCHAIN PROTOTYPE
===================================================

🚀 Creating Blockchain with Genesis Block...
✅ Genesis Block Created and Mined!

➕ Adding Block 1: 'Alice sends 5 BTC to Bob'...
✅ Block 1 Mined Successfully!

➕ Adding Block 2: 'Bob sends 2 BTC to Charlie'...
✅ Block 2 Mined Successfully!

➕ Adding Block 3: 'Charlie sends 1 BTC to Dave'...
✅ Block 3 Mined Successfully!

═══════════════════════════════════════════════════
           BLOCKCHAIN (Length: 4)
═══════════════════════════════════════════════════

╔═══════════════════════════════════════════════════
║ Block #0
║ Timestamp: [timestamp]
║ Data: Genesis Block
║ Previous Hash: 0
║ Hash: 0000[rest of hash]
║ Nonce: [nonce value]
╚═══════════════════════════════════════════════════
                    ↓
                    ↓
╔═══════════════════════════════════════════════════
║ Block #1
║ Timestamp: [timestamp]
║ Data: Alice sends 5 BTC to Bob
║ Previous Hash: [hash from previous block]
║ Hash: 0000[rest of hash]
║ Nonce: [nonce value]
╚═══════════════════════════════════════════════════
                    ↓
                    ↓
╔═══════════════════════════════════════════════════
║ Block #2
║ Timestamp: [timestamp]
║ Data: Bob sends 2 BTC to Charlie
║ Previous Hash: [hash from previous block]
║ Hash: 0000[rest of hash]
║ Nonce: [nonce value]
╚═══════════════════════════════════════════════════
                    ↓
                    ↓
╔═══════════════════════════════════════════════════
║ Block #3
║ Timestamp: [timestamp]
║ Data: Charlie sends 1 BTC to Dave
║ Previous Hash: [hash from previous block]
║ Hash: 0000[rest of hash]
║ Nonce: [nonce value]
╚═══════════════════════════════════════════════════

🔍 Validating Blockchain Integrity...
✅ Blockchain is VALID! All blocks are properly linked and hashes are correct.

🗑️  Cleaning up memory...
✅ Memory cleanup completed!

===================================================
          BLOCKCHAIN DEMO COMPLETED!
===================================================