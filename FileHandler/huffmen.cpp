#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include "readfile.hpp"

// Node structure for Huffman Tree
struct HuffmanNode
{
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare
{
    bool operator()(HuffmanNode *l, HuffmanNode *r)
    {
        return l->freq > r->freq;
    }
};

// Function to build the frequency table
std::unordered_map<char, int> buildFrequencyTable(const std::vector<std::string> &lines)
{
    std::unordered_map<char, int> frequency;
    for (const auto &line : lines)
    {
        for (char ch : line)
        {
            frequency[ch]++;
        }
    }
    return frequency;
}
// Recursive function to generate the Huffman Codes from the tree
void generateHuffmanCodes(HuffmanNode *root, std::unordered_map<char, std::string> &huffmanCode, std::string str)
{
    if (!root)
        return;

    // If the node is a leaf, store the code for this character
    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }

    generateHuffmanCodes(root->left, huffmanCode, str + "0");
    generateHuffmanCodes(root->right, huffmanCode, str + "1");
}

// Build the Huffman Tree and return the root
HuffmanNode *buildHuffmanTree(const std::unordered_map<char, int> &frequency)
{
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare> pq;

    // Create leaf nodes for each character
    for (const auto &pair : frequency)
    {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build the tree
    while (pq.size() != 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        HuffmanNode *node = new HuffmanNode('\0', sum);
        node->left = left;
        node->right = right;
        pq.push(node);
    }

    return pq.top();
}

// Encode the input using the Huffman Codes
std::string encode(const std::vector<std::string> &lines, const std::unordered_map<char, std::string> &huffmanCode)
{
    std::string encodedString = "";
    for (const auto &line : lines)
    {
        for (char ch : line)
        {
            // Check if the character exists in the huffmanCode map
            if (huffmanCode.find(ch) != huffmanCode.end())
            {
                encodedString += huffmanCode.at(ch); // Add Huffman code for the character
            }
            else
            {
                std::cerr << "Error: Character '" << ch << "' not found in Huffman code map." << std::endl;
            }
        }
        // Add newline as well if you want to preserve lines
        if (huffmanCode.find('\n') != huffmanCode.end())
        {
            encodedString += huffmanCode.at('\n');
        }
    }
    return encodedString;
}

// Write the encoded string to the file
void writeToFile(const std::string &filename, const std::string &encodedString)
{
    std::ofstream outFile(filename + "Encoded.txt", std::ios::out);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    outFile << encodedString;
    outFile.close();
}

// Main Huffman Encoding process
void huffmanEncodingProcess(const std::vector<std::string> &lines, const std::string &filename)
{
    // 1. Build the frequency table
    std::unordered_map<char, int> frequency = buildFrequencyTable(lines);

    // 2. Build the Huffman Tree
    HuffmanNode *root = buildHuffmanTree(frequency);

    // 3. Generate Huffman codes
    std::unordered_map<char, std::string> huffmanCode;
    generateHuffmanCodes(root, huffmanCode, "");

    // 4. Encode the text
    std::string encodedString = encode(lines, huffmanCode);

    // 5. Write to the encoded file
    writeToFile(filename, encodedString);
}

int main()
{
    // Input vector containing lines from a file
    ReadFile reader("../myfile.txt");
    std::vector<std::string> lines = reader.readLines();

    // Call Huffman encoding process with a filename
    huffmanEncodingProcess(lines, "example");

    std::cout << "File compressed and written to 'exampleEncoded.txt'" << std::endl;
    reader.close();

    return 0;
}