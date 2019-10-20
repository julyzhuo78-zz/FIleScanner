//
//  main.cc
//  FileScanner
//
//  Created by July Zhuo on 2019-02-01.
//  Copyright © 2019 July Zhuo. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ScanningFile.h"
#include "ScanningFailure.h"

using namespace std;

int main(int argc, const char * argv[]) {
    (void)argc;
    (void)argv;
    cout << "Please enter the name of the file: " << endl;
    string s;
    cin >> s;
    ScanningFile scanningFile = ScanningFile(s);
    vector<pair<LineType, int> > lines;
    try {
        lines = scanningFile.startScanning();
    } catch (ScanningFailure &f) {
        std::cerr << f.what() << std::endl;
        return 1;
    }

    scanningFile.processScanningResults(lines);
    scanningFile.printScanningResults();
    return 0;
}
