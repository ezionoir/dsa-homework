// https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
#include "./LZW.h"

// Notation: We call a "character" is for a string that is added to the current dictionary, character is for a single character ('a', 'b', ...)

vector<int> encode(string input) {
    // We map a "character" with its ID (the order that it is added to the dictionary/table)
    // Use unorder map for faster look up
    unordered_map<string, int> table;

    // Every single character is added first
    for (int i = 0; i < 256; ++i)
        table[string(1, char(i))] = i;

    string prefix(1, char(input[0])), appChar = "";
    vector<int> output;
    int code = 256; // The current ID for next "character"

    for (int i = 1; i < input.length(); ++i) {
        appChar += input[i];

        // Look up the "character" generate by prefix + the next character in input
        // If it appears in table, then we continue to build longer "character" (current "character" becomes a prefix and we append it with the next character in input)
        if (table.find(prefix + appChar) != table.end())
            prefix += appChar;
        // If it does not appear in table, then it is a new "character"
        else {
            // Since it's new, we can just output the prefix (old "character")
            output.push_back(table[prefix]);
            // Add the new "character" to table
            table[prefix + appChar] = code++;
            // Reset the prefix (set it by the new character)
            prefix = appChar;
        }
        appChar = "";
    }
    output.push_back(table[prefix + ""]);

    return output;
}

string decode(vector<int> input) {
    unordered_map<int, string> table;
    // Every single character is added first
    for (int i = 0; i < 256; ++i)
        table[i] = string(1, char(i));

    int oldID = input[0], newID;
    string output = table[oldID];
    string s = table[oldID], c(1, s[0]);
    int count = 256;

    for (int i = 1; i < input.size(); ++i) {
        newID = input[i];

        // If the newID correspond to a "character" added, we just output it
        if (table.find(newID) != table.end())
            s = table[newID];
        else
            s = table[oldID] + c;
            
        output += s;
        c = string(1, s[0]);
        // New "character" = previous "character" + next character in input
        table[count++] = table[oldID] + c;
        oldID = newID;
    }

    return output;
}