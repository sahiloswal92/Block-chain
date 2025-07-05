# Block-chain
Block chain using c
# 🧱 Simple Blockchain Implementation in C

This project is a simple implementation of a *blockchain system* in the C programming language. It simulates core blockchain functionality such as block creation, hashing, chain validation, and basic transaction logging.

## 📜 Features

- ✅ Genesis block creation
- ➕ Add new transaction blocks
- 👀 Display the entire blockchain
- ❌ Delete the blockchain
- 🔍 Search for a block by its number
- 🔐 Validate the integrity of the blockchain
- 📊 Calculate total and average transaction amounts
- 🔄 Display Genesis and Latest blocks

## 💡 How It Works

Each block stores:
- *Amount* transacted
- *Sender* and *Receiver* information
- *Timestamp*
- *Transaction data* summary
- *Blockchain name* (e.g., Bitcoin, Ethereum)
- *Hash* (simple hash based on block content)

The chain starts with a *Genesis Block*, and additional blocks can only be added afterward.

## 🏗️ Data Structure

Each block is represented as a node in a singly linked list:

```c
struct node {
    float amount;
    int blockno;
    char timestamp[20];
    char sender[20];
    char receiver[20];
    char data[250];
    char type[20];
    char hash[65]; 
    struct node* next;
};
