import json
import os

# calc probability of each element and add it in dectionary
def build_probability_table(text):
    freq = {}
    for ch in text:
        freq[ch] = freq.get(ch, 0) + 1  # if the char is already in freq array freq.get(ch, 0) will return 1 else will return 0
    total = len(text)
    prob_table = {}
    for ch in freq:
        prob_table[ch] = freq[ch] / total
    return prob_table

# build huffman codes depending on the probability table
def build_huffman_codes(probs):
    sorted_prob = sorted(probs.items(), key=lambda x: x[1]) # sort elements depends on the the second value in the tuple which is the probability of each char
    Bin_codes = {ch: "" for ch in probs} # here we will store binary code for each char

    if len(sorted_prob) == 1:
        char, _ = sorted_prob[0]
        Bin_codes[char] = "0"
        return Bin_codes

    while len(sorted_prob) > 1:
        # the least two probability
        firstLeast = sorted_prob.pop(0)
        secondLeast = sorted_prob.pop(0)

        firstLeast_chars, firstLeast_prob = firstLeast
        secondLeast_chars, secondLeast_prob = secondLeast

        # binary codes distribution and here we use for loop because the firstLeast_chars or secondLeast_chars would be 2 chars or more
        for ch in firstLeast_chars:
            Bin_codes[ch] = "0" + Bin_codes[ch]
        for ch in secondLeast_chars:
            Bin_codes[ch] = "1" + Bin_codes[ch]

        # merge two char or more in one node and add them in the sorted_prop then re sort sorted_prop array
        new_node = (firstLeast_chars + secondLeast_chars, firstLeast_prob + secondLeast_prob)
        sorted_prob.append(new_node)
        sorted_prob.sort(key=lambda x: x[1])

    return Bin_codes

def pad_bits(bitstring):
    # to know how many bits we need to add to make it from 8 bits
    extra_bits = (8 - len(bitstring) % 8) % 8 # for example len(bitstring) = 16
    bitstring += "0" * extra_bits                          #(8 - 16 % 8) % 8 = (8 - 0) % 8 = 0

    return bitstring, extra_bits

def bits_to_bytes(bitstring):
    byte_list = []
    for i in range(0, len(bitstring), 8):# start from zero to the end which is length of bitstirng and each step is += 8
        byte_value = int(bitstring[i:i + 8], 2) # number -> 2 here is to make the int to understand that the input is binary
        byte_list.append(byte_value)
    return bytes(byte_list)

def bytes_to_bits(bytedata):
    bits = ""
    for b in bytedata:
        bits += f"{b:08b}"  # the first b => the asci code num from 0 to 255 that we want to transform it to bin
                            # the second b => transform the asci num to binary 
                            # 8 => make it from 8 bits
                            # 0 => if the num of bits < 8 will add zeros
    return bits


# ============================ #
#          Compression         #
# ============================ #
def compress(input_file, output_file):
    try:
        with open(input_file, "r") as f:
            text = f.read()
    except Exception :
        print(f"Error reading {input_file}: {Exception}")
        return

    if not text:
        print("Empty file, nothing to compress.\n")
        with open(output_file, "wb") as f:
            pass
        return

    probs = build_probability_table(text) # probs is dictionary of -> {char: probability}
    codes = build_huffman_codes(probs) # codes is dictionary of -> {char: binary code}

    # Convert text to bits and store it in encoded
    encoded = ""
    for ch in text:
        encoded += codes[ch]

    
    encoded, extra_bits = pad_bits(encoded)

    binary_data = bits_to_bytes(encoded)

    # Section of compressed binary file the output_file have extand of .bin
    try:
        with open(output_file, "wb") as out:
            out.write(binary_data)
    except Exception:
        print(f"Error writing {output_file}: {Exception}")
        return

    # Store JSON with codes, extra_bits, and binary code after add the padding zeros
    Format_Json = {
        "codes": codes,
        "extra_bits": extra_bits,
        "padded_binary": encoded 
    }

    # the output file with extansion of .json to stor the format_json dictionary
    with open("codes.json", "w") as f:
        json.dump(Format_Json, f, indent=2)
    
    original_size = len(text) * 8
    compressed_size = len(encoded)
    ratio = 100 - ((compressed_size / original_size) * 100)

    print(f"\nCompression completed successfully:")
    print(f"Input file: {input_file}")
    print(f"Output file: {output_file}")
    print(f"Original size: {original_size} bits")
    print(f"Compressed size: {compressed_size} bits")
    print(f"Compression Ratio: {ratio:.2f}%\n")


# ================================= #
#          Decompression            #
# ================================= #
def decompress(compressed_file, output_file):  #compressed_file is the file with .bin extansion & output_file is the file with .txt extansion
    # Read codes and extra_bits from codes.json
    try:
        with open("codes.json", "r") as f:
            Format_Json = json.load(f)  # convert json data to dictionary 
            codes = Format_Json["codes"]  # also will return dictionary
            extra_bits = Format_Json["extra_bits"]  # this will return int 
    except Exception :
        print(f"Error reading codes.json: {Exception}")
        return

    try:
        with open(compressed_file, "rb") as f:
            data = f.read()
    except Exception as e:
        print(f"Error reading {compressed_file}: {e}")
        return

    if not data:
        print("Empty compressed file.\n")
        return
    
    bits = bytes_to_bits(data) # convert bytes data to bits string
    if extra_bits > 0:
        bits = bits[:-extra_bits] # to ignore the padding zeros added in the end of string during compression

    reverse_codes = {}
    for k, v in codes.items():
        reverse_codes[v] = k

    decoded = []
    current = ""
    for bit in bits:
        current += bit
        if current in reverse_codes:
            decoded.append(reverse_codes[current])
            current = ""

    text = "".join(decoded)

    try:
        with open(output_file, "w") as out:
            out.write(text)
    except Exception :
        print(f"Error writing {output_file}: {Exception}")
        return

    print(f"Decompression Done: '{compressed_file}' → '{output_file}'")
    print(f"Restored text: {text}\n")



# ============================ #
#          Main Menu           #
# ============================ #
def main_menu():
    while True:
        print("========= Huffman Compression System =========")
        print("1 - Compress a file")
        print("2 - Decompress a file")
        print("3 - Exit")
        choice = input("Please enter your choice (1-3): ").strip()

        if choice == "1":
            in_file = input("Enter the input file name (e.g. input.txt): ").strip()
            if not os.path.exists(in_file):
                print(f"\n Error: Input file '{in_file}' not found. Please try again.\n")
                continue

            out_file = input("Enter the compressed file name (e.g. compressed.bin): ").strip()
            if not out_file:
                out_file = os.path.splitext(in_file)[0] + ".bin"
            elif not out_file.endswith(".bin"):
                out_file += ".bin"
            compress(in_file, out_file)

        elif choice == "2":
            in_file = input("Enter the compressed file name (e.g. compressed.bin): ").strip()
            if not os.path.exists(in_file):
                print(f"\n Error: Input file '{in_file}' not found. Please try again.\n")
                continue

            out_file = input("Enter the output file name (e.g. output.txt): ").strip()
            if not out_file:
                out_file = os.path.splitext(in_file)[0] + "_decompressed.txt"
            decompress(in_file, out_file)

        elif choice == "3":
            print("Exiting the program....")
            break
        else:
            print("Invalid choice, please try again.\n")

if __name__ == "__main__":
    main_menu()
