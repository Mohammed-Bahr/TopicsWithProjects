#include <bits/stdc++.h>
using namespace std;

// Node structure for Huffman Tree
struct HNode {
    char data;
    int freq;
    HNode *left, *right;
    
    HNode(char d, int f) :data(d) , freq(f) , left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HNode* a, HNode* b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoding {
private:
    HNode* root;
    unordered_map<char, string> chCodes;
    unordered_map<char, int> frequency;
    string text;

   void calculateFrequency(string text) {
        for (char ch : text) {
            frequency[ch]++;
        }
    }
    
    HNode* buildHuffmanTree() {
        priority_queue<HNode*, vector<HNode*>, Compare> minHeap;
        
        for (auto pair : frequency) {
            minHeap.push(new HNode(pair.first, pair.second));
        }
        
        while (minHeap.size() > 1) {
            HNode* left = minHeap.top();
            minHeap.pop();
            
            HNode* right = minHeap.top();
            minHeap.pop();
            
            // Create internal node with combined frequency
            int sum = left->freq + right->freq;
            HNode* node = new HNode('\0', sum);
            node->left = left;
            node->right = right;
            
            minHeap.push(node);
        }
        
        return minHeap.top(); // root 
    }
    
    // Generate Huffman codes by traversing tree
    void generateCodes(HNode* node, string code) {
        if (node == nullptr) return;
        
        if (node->left == nullptr && node->right == nullptr) {
            chCodes[node->data] = code;
            return;
        }
        
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }
    
    // Print tree structure (for visualization)
    void printTree(HNode* node, string prefix, bool isLeft) {
        if (node == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        
        if (node->left == nullptr && node->right == nullptr) {
            cout << "['" << node->data << "': " << node->freq << "]" << endl;
        } else {
            cout << "[" << node->freq << "]" << endl;
        }
        
        if (node->left != nullptr || node->right != nullptr) {
            printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
            printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    
public:
    HuffmanCoding(string t = "") : root(nullptr) , text(t) {}
    
    // Encode the input text
    string encode() {
        if (text.empty()) return "";
        
        calculateFrequency(text);
        
        root = buildHuffmanTree();
        
        // Step 3: Generate codes
        generateCodes(root, "");
        
        // Step 4: Encode the text
        string encodedText = "";
        for (char ch : text) {
            encodedText += (chCodes[ch] + "_");
        }
        
        return encodedText;
    }
    
    string decode(string encodedText) {
        if (encodedText.empty() || root == nullptr) return "";
        
        string decodedText = "";
        HNode* current = root;
        
        for (char bit : encodedText) {
            // Traverse tree based on bit
            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }
            
            if (current->left == nullptr && current->right == nullptr) {
                decodedText += current->data;
                current = root; 
            }
        }
        
        return decodedText;
    }
    
    // Display Huffman codes
    void displayCodes() {
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║     HUFFMAN CODES TABLE        ║" << endl;
        cout << "╠═══════╦══════════╦═════════════╣" << endl;
        cout << "║ Char  ║ Freq     ║ Code        ║" << endl;
        cout << "╠═══════╬══════════╬═════════════╣" << endl;
        
        for (auto pair : chCodes) {
            cout << "║   " << pair.first << "   ║    " 
                 << frequency[pair.first] << "     ║ " 
                 << pair.second << string(12 - pair.second.length(), ' ') << "║" << endl;
        }
        
        cout << "╚═══════╩══════════╩═════════════╝" << endl;
    }
    
    // Display tree structure
    void displayTree() {
        cout << "\n=== Huffman Tree Structure ===" << endl;
        printTree(root, "", false);
    }
    
    // Calculate compression statistics
    void displayStats(string original, string encoded) {
        int originalBits = original.length() * 8;
        int encodedBits = encoded.length();
        double compressionRatio = (1.0 - (double)encodedBits / originalBits) * 100;
        
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║      COMPRESSION STATISTICS            ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ Original text length: " << original.length() << " characters" << endl;
        cout << "║ Original size: " << originalBits << " bits" << endl;
        cout << "║ Encoded size: " << encodedBits << " bits" << endl;
        cout << "║ Compression ratio: " << compressionRatio << "%" << endl;
        cout << "║ Space saved: " << (originalBits - encodedBits) << " bits" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
    }
};

int main() {
    
    string text = "mohammed";
    HuffmanCoding huffman(text);
    
    cout << "========================================" << endl;
    cout << "   STANDARD HUFFMAN CODING DEMO" << endl;
    cout << "========================================" << endl;
    cout << "\nOriginal Text: \"" << text << "\"" << endl;
    

    // Encode
    string encoded = huffman.encode();
    cout << "\nEncoded Binary: " << encoded << endl;
    
    // Display codes
    huffman.displayCodes();
    
    // Display tree
    huffman.displayTree();
    
    // Decode
    string decoded = huffman.decode(encoded);
    cout << "\nDecoded Text: \"" << decoded << "\"" << endl;
    
    // Display statistics
    huffman.displayStats(text, encoded);
    
    // Verification
    cout << "\n✓ Verification: " << (text == decoded ? "SUCCESS ✓" : "FAILED ✗") << endl;
    cout << "\n========================================" << endl;
    
    return 0;
}