#include "./CommandProcess.h"

// Convert a non-negative integer into binary string with nbits bits
string ToBinary(int x, int nbits) {
    stringstream writer;
    for (int i = nbits - 1; i >= 0; --i) {
        if (x & (1 << i)) writer << "1";
        else writer << "0";
    }
    return writer.str();
}

void CommandProcess(int argc, char** argv) {
    // Compress
    if (strcmp(argv[1], "-c") == 0) {
        string input = argv[2];
        vector<int> output = encode(input);

        // Print the output
        for (int i = 0; i < output.size(); ++i)
            cout << output[i] << " ";
        cout << endl;

        for (int i = 0; i < output.size(); ++i)
            cout << ToBinary(output[i], CHAR_SIZE) << " ";
        cout << endl;

        // Print compress rate
        long long int N = sizeof(char) * 8 * input.length();
        long long int n = CHAR_SIZE * output.size();
        double compressRate = (double(N) - double(n)) / double(N) * 100;
        cout << fixed << setprecision(2) << compressRate << endl;

        return;
    }

    // Extract
    if (strcmp(argv[1], "-e") == 0) {
        vector<int> input;
        for (int i = 2; i < argc; ++i)
            input.push_back(atoi(argv[i]));

        // Print the output
        string output = decode(input);
        cout << output << endl;

        // Print compress rate
        long long int N = sizeof(char) * 8 * output.length();
        long long int n = CHAR_SIZE * input.size();
        double compressRate = (double(N) - double(n)) / double(N) * 100;
        cout << fixed << setprecision(2) << compressRate << endl;

        return;
    }
}
