#include "./LZW.h"

vector<int> encode(string input) {
    unordered_map<string, int> table;
    for (int i = 0; i < 256; ++i)
        table[string(1, char(i))] = i;

    string prefix(1, char(input[0])), appChar = "";
    vector<int> output;
    int code = 256;

    for (int i = 1; i < input.length(); ++i) {
        appChar += input[i];

        if (table.find(prefix + appChar) != table.end())
            prefix += appChar;
        else {
            output.push_back(table[prefix]);
            table[prefix + appChar] = code++;
            prefix = appChar;
        }
        appChar = "";
    }
    output.push_back(table[prefix + ""]);

    return output;
}

string decode(vector<int> input) {
    unordered_map<int, string> table;
    for (int i = 0; i < 256; ++i)
        table[i] = string(1, char(i));

    int oldID = input[0], newID;
    string output = table[oldID];
    string s = table[oldID], c(1, s[0]);
    int count = 256;

    for (int i = 1; i < input.size(); ++i) {
        newID = input[i];

        if (table.find(newID) != table.end())
            s = table[newID];
        else
            s = table[oldID] + c;
            
        output += s;
        c = string(1, s[0]);
        table[count++] = table[oldID] + c;
        oldID = newID;
    }

    return output;
}