#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// List of 32 C keywords
const std::vector<std::string> c_keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
    "union", "unsigned", "void", "volatile", "while"
};

// Function to check if a word is a keyword
bool is_keyword(const std::string& word) {
    return std::find(c_keywords.begin(), c_keywords.end(), word) != c_keywords.end();
}

int main() {
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error: input.txt file not found!" << std::endl;
        return 1;
    }

    std::string line, program_code;
    std::unordered_map<std::string, int> keyword_count;

    // Read the file and store its contents
    while (std::getline(infile, line)) {
        program_code += line + "\n";

        // Extract words from the line
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Check if the word is a keyword and update its count
            if (is_keyword(word)) {
                keyword_count[word]++;
            }
        }
    }

    infile.close();

    // Output the C program read from the file
    std::cout << "Program read from input.txt:\n";
    std::cout << program_code << std::endl;

    // Output the keywords and their frequencies
    std::cout << "Keywords and their frequencies:\n";
    for (const auto& pair : keyword_count) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
