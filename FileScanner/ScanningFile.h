//
//  ScanningFile.h
//  FileScanner
//
//  Created by July Zhuo on 2019-02-01.
//  Copyright © 2019 July Zhuo. All rights reserved.
//

#ifndef ScanningFile_h
#define ScanningFile_h

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Type of lines
enum LineType {
    SingleLineComment, // slash comment "//"
    HashComment,       // # comment
    BlockCommentStart,
    BlockCommentEnd,
    ToDoComment,       // //TODO:
    HashToDoComment,   // # TODO:
    NormalLine
};

class ScanningFile {
    string fileName;
    int totalNoOfLines, noOfCommentLines, noOfSingleLineComments,
    noOfCommentLinesInBlockComments, noOfBlockLineComments, noOfToDos;
    
public:
    //constructor
    ScanningFile(string fileName);
    
    //accessors:
    int getTotalNoOfLines();
    int getNoOfCommentLines();
    int getNoOfSingleLineComments();
    int getNoOfCommentLinesInBlockComments();
    int getNoOfBlockLineComments();
    int getNoOfToDos();
    
    //Identify the type of each line and store it in a vector of LineType-Int pairs
    vector<pair<LineType, int> > startScanning();
    
    //Go through the store data once to get useful results
    void processScanningResults(vector<pair<LineType,int> > lines);
    
    //Print the result to the screen
    void printScanningResults();
};

#endif /* ScanningFile_h */
