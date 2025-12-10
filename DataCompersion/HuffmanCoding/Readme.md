# 🗜️ Huffman Compression System (Python)

A **text compression and decompression tool** built using the **Huffman Coding algorithm**.  
This program efficiently compresses text files into binary form (`.bin`) and restores them to their original form (`.txt`) while preserving data accuracy.

---

## 🚀 Features

- 📉 **Lossless compression** using Huffman encoding  
- 🧠 **Automatic probability calculation** for each character  
- 🔢 **Custom binary code generation** for every unique character  
- 🧩 **Bit padding** to make binary data byte-aligned  
- 🔄 **Full decompression support** to restore original text  
- 💾 **Saves metadata** (`codes.json`) to handle decompression correctly  
- 🧰 **Simple interactive menu** for compressing and decompressing files  
- 🧹 **Handles errors gracefully** (missing files, empty inputs, etc.)

---

## 🧱 Project Structure

```
huffman_compression.py
│
├── build_probability_table(text)   # Calculates probability of each character
├── build_huffman_codes(probs)      # Builds Huffman binary codes
├── pad_bits(bitstring)             # Adds padding to make 8-bit aligned
├── bits_to_bytes(bitstring)        # Converts bitstring to byte sequence
├── bytes_to_bits(bytedata)         # Converts bytes back to bits
│
├── compress(input_file, output_file)    # Compresses a text file
├── decompress(compressed_file, output_file)  # Decompresses binary file
│
└── main_menu()                     # User interface for running compression/decompression
```

---

## ⚙️ How It Works

### 1️⃣ Compression Steps:
1. Read input text file (`input.txt`)
2. Build frequency and probability table
3. Generate Huffman binary codes
4. Encode text into bits
5. Pad to 8-bit multiples and convert to bytes
6. Save compressed file as `.bin`
7. Save metadata (`codes.json`) including:
   - Character codes  
   - Extra bits count  
   - Padded binary string  

### 2️⃣ Decompression Steps:
1. Read metadata from `codes.json`
2. Load binary data from `.bin` file
3. Remove padding bits
4. Decode binary data into characters
5. Write restored text into `.txt` file

---

## 🧩 Example Usage

### ▶️ Compression
```bash
========= Huffman Compression System =========
1 - Compress a file
2 - Decompress a file
3 - Exit
Please enter your choice (1-3): 1
Enter the input file name (e.g. input.txt): input.txt
Enter the compressed file name (e.g. compressed.bin): compressed.bin
```

**Output:**
```
Compression completed successfully:
Input file: input.txt
Output file: compressed.bin
Original size: 800 bits
Compressed size: 480 bits
Compression Ratio: 40.00%
```

### 🔁 Decompression
```bash
========= Huffman Compression System =========
Please enter your choice (1-3): 2
Enter the compressed file name (e.g. compressed.bin): compressed.bin
Enter the output file name (e.g. output.txt): output.txt
```

**Output:**
```
Decompression Done: 'compressed.bin' → 'output.txt'
Restored text: Hello, Huffman!
```

---

## 📦 Files Generated

| File | Description |
|------|--------------|
| `input.txt` | Original text file |
| `compressed.bin` | Binary compressed output |
| `codes.json` | Metadata file (stores Huffman codes and padding info) |
| `output.txt` | Restored text after decompression |

---

## 🧠 Algorithm Overview

**Huffman Coding** is a greedy algorithm that:
1. Assigns shorter binary codes to frequent characters  
2. Assigns longer binary codes to rare characters  
3. Ensures no code is a prefix of another (prefix-free)  
4. Results in **optimal lossless compression**

---

## ⚙️ How to Run

### 1. Run in terminal:
```bash
python huffman_compression.py
```

### 2. Choose from the menu:
```
1 - Compress a file
2 - Decompress a file
3 - Exit
```

---

## 👤 Author

**Mohamed Ahmed Maawad Mahmoud (محمد أحمد معوض محمود)**  
Faculty of Computers and Artificial Intelligence, Cairo University  
🌍 Egypt | 💻 Python Developer | ✉️ [LinkedIn](www.linkedin.com/in/møĥãmmęđ-bãĥŗ-91716529b)
