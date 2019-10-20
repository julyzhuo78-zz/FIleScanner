//
//  ScanningFile.c
//  FileScanner
//
//  Created by July Zhuo on 2019-02-01.
//  Copyright © 2019 July Zhuo. All rights reserved.
//

#include "ScanningFile.h"
#include "ScanningFailure.h"
#include <vector>
#include <iostream>

ScanningFile::ScanningFile(string fileName): fileName(fileName) {
    totalNoOfLines = 0;
    noOfCommentLines = 0;
    noOfSingleLineComments = 0;
    noOfBlockLineComments = 0;
    noOfCommentLinesInBlockComments = 0;
    noOfToDos = 0;
}

int ScanningFile::getTotalNoOfLines() {
    return totalNoOfLines;
}

int ScanningFile::getNoOfCommentLines() {
    return noOfCommentLines;
}

int ScanningFile::getNoOfSingleLineComments() {
    return noOfSingleLineComments;
}

int ScanningFile::getNoOfCommentLinesInBlockComments() {
    return noOfCommentLinesInBlockComments;
}

int ScanningFile::getNoOfBlockLineComments() {
    return noOfBlockLineComments;
}

int ScanningFile::getNoOfToDos() {
    return noOfToDos;
}

vector<pair<LineType, int> > ScanningFile::startScanning() {
    ifstream file;
    vector<pair<LineType, int> > lines;
    file.open(fileName);
    int lineNo = 0;
    if (file.fail()) {
        throw ScanningFailure("Fail to scan due to invalid file");
    }
    
    if (file) {
        string line;
        while(getline(file, line)) {
            if (line.find("# TODO:") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(HashToDoComment, lineNo));
            } else if (line.find("TODO:") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(ToDoComment, lineNo));
            } else if (line.find("//") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(SingleLineComment, lineNo));
            } else if (line.find("/*") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(BlockCommentStart, lineNo));
                if (line.find("*/") != string::npos) {
                    lines.__emplace_back(pair<LineType, int>(BlockCommentEnd, lineNo));
                }
            } else if (line.find("*/") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(BlockCommentEnd, lineNo));
                if (line.find("/*") != string::npos) {
                    lines.__emplace_back(pair<LineType, int>(BlockCommentStart, lineNo));
                }
            } else if (line.find("#") != string::npos) {
                lines.__emplace_back(pair<LineType, int>(HashComment, lineNo));
            } else {
                lines.__emplace_back(pair<LineType, int>(NormalLine, lineNo));
            }
            lineNo += 1;
        }
    }
    totalNoOfLines = lineNo;
    return lines;
}


void ScanningFile::processScanningResults(vector<pair<LineType,int> > lines) {
    int currBlockStartLineNo = 0;
    for (unsigned i = 0; i < lines.size();) {
        pair<LineType,int> line = lines.at(i);
        switch (line.first) {
            case SingleLineComment:
                noOfSingleLineComments++;
                i++;
                break;
            case HashToDoComment:
                noOfToDos++;
                line.first = HashComment;
            case HashComment: {
                pair<LineType,int> nextLine = lines.at(line.second+1);
                if (nextLine.first != HashComment) {
                    noOfSingleLineComments++;
                    i++;
                    continue;
                }
                noOfBlockLineComments++;
                while (nextLine.first == HashComment) {
                    nextLine = lines.at(nextLine.second+1);
                    
                }
                noOfCommentLinesInBlockComments += nextLine.second - line.second;
                i = nextLine.second;
                break;
            }
            case BlockCommentStart:
                noOfBlockLineComments++;
                currBlockStartLineNo = line.second;
                i++;
                break;
            case BlockCommentEnd:
                if (line.second == currBlockStartLineNo) {
                    noOfCommentLinesInBlockComments++;
                } else {
                    noOfCommentLinesInBlockComments += line.second - currBlockStartLineNo + 1;
                }
                i++;
                break;
            case ToDoComment:
                noOfToDos++;
                noOfSingleLineComments++;
                i++;
                break;
            case NormalLine:
                i++;
                break;
            default:
                break;
        }
    }
    noOfCommentLines = noOfSingleLineComments + noOfCommentLinesInBlockComments;
}


void ScanningFile::printScanningResults() {
    cout << "Total # of lines: " << getTotalNoOfLines() << endl;
    cout << "Total # of comment lines: " << getNoOfCommentLines() << endl;
    cout << "Total # of single line comments: " << getNoOfSingleLineComments() << endl;
    cout << "Total # of comment lines within block comments: " << getNoOfCommentLinesInBlockComments() << endl;
    cout << "Total # of block line comments: " << getNoOfBlockLineComments() << endl;
    cout << "Total # of TODO’s: " << getNoOfToDos() << endl;
}


