# 🎯 Scrabble Game (C)

<p align="center">

<img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C">

<img src="https://img.shields.io/badge/Build-Makefile-orange?style=for-the-badge&logo=gnu" alt="Makefile">

</p>

<p align="center">
    <b>Console implementation of the classic Scrabble game using a Trie data structure.</b>
</p>

---

## 📖 Overview

This project is a console-based implementation of the **Scrabble** game written in **C**.

The application loads a dictionary from a file and stores all words inside a **Trie (Prefix Tree)** for fast word lookup and validation.

Players receive randomly generated letters each round and must create valid words using only the provided letters.

---

## ✨ Features

### 🎮 Game System

* Start a new game
* Multiple rounds
* Configurable number of rounds
* Configurable number of generated letters
* Score tracking
* Final score calculation

### 📚 Dictionary System

* Load dictionary from file
* Add new words
* Fast word lookup
* Word counting
* Case-insensitive search

### 🌳 Trie Data Structure

* Trie creation
* Trie destruction
* Word insertion
* Word search
* Prefix search

### ✅ Validation

* Dictionary validation
* Letter availability validation
* Duplicate prevention
* Invalid input handling

### 💾 Persistence

* Save Trie to binary file
* Load Trie from binary file

---

## 🏗️ Project Structure

```text
Scrabble/
│
├── include/
│   ├── trie.h
│   ├── dictionary.h
│   ├── validation.h
│   ├── game.h
│   └── persistence.h
│
├── src/
│   ├── trie.c
│   ├── dictionary.c
│   ├── validation.c
│   ├── game.c
│   ├── persistence.c
│   └── main.c
│
├── data/
│   ├── dictionary.txt
│   └── trie.bin
│
├── Makefile
│
└── README.md
```

---

## 🌳 Trie Structure

Example:

```text
CAT
CAR
CARD
```

Produces:

```text
(root)
  |
  C
  |
  A
 / \
T   R
     \
      D
```

Trie allows:

* O(k) insertion
* O(k) search

where:

```text
k = word length
```

---

## 🚀 Build & Run

### Compile

```bash
make
```

### Run

```bash
./scrabble
```

---

## 📋 Game Flow

```text
Generate Letters
       │
       ▼
Display Letters
       │
       ▼
Player Enters Word
       │
       ▼
Validate Word
       │
       ▼
Calculate Score
       │
       ▼
Next Round
```

---

## 🧮 Scoring

Default scoring:

```text
1 Letter = 1 Point
```

Example:

```text
APPLE
```

Score:

```text
5 Points
```

---

## 🛠 Technologies

| Technology   | Purpose             |
| ------------ | ------------------- |
| C            | Core implementation |
| Trie         | Dictionary storage  |
| Makefile     | Build automation    |
| Binary Files | Trie serialization  |

---

## 👥 Team Responsibilities

### Member 1

* Game Logic
* Rounds
* Score System
* Settings

### Member 2

* Trie
* Dictionary Loader

### Member 3

* Add New Word
* Save Trie
* Load Trie

### Member 4

* Word Validation
* Dictionary Validation

---

## 📜 License

MIT LICENSE

---
