#include "./CommandProcess.h"

void CommandProcess(int argc, char** argv) {
    if (strcmp(argv[1], "make") == 0) {
        string name = argv[2];

        vector<int> arr;
        for (int i = 4; i < argc; ++i)
            arr.push_back(atoi(argv[i]));

        SparseTable* st;
        if (strcmp(argv[3], "MIN") == 0)
            st = new SparseTable(name, arr, TYPE_MIN);
        if (strcmp(argv[3], "MAX") == 0)
            st = new SparseTable(name, arr, TYPE_MAX);
        if (strcmp(argv[3], "GCD") == 0)
            st = new SparseTable(name, arr, TYPE_GCD);

        string fileName = argv[2];
        fileName += ".txt";
        ofstream writer(fileName, ios::out);
        writer << *st;
        writer.close();

        cout << *st;

        delete st;
    }

    if (strcmp(argv[1], "query") == 0) {
        string name = argv[2];

        int lower = atoi(argv[3]), upper = atoi(argv[4]);

        SparseTable* st = new SparseTable(name);
        cout << st->query(lower, upper) << endl;

        delete st;
    }
}