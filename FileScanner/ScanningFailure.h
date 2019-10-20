//
//  ScanningFailure.h
//  FileScanner
//
//  Created by July Zhuo on 2019-02-02.
//  Copyright © 2019 July Zhuo. All rights reserved.
//

#ifndef ScanningFailure_h
#define ScanningFailure_h

#include <stdio.h>
#include <string>

class ScanningFailure {
    std::string message;
    
public:
    ScanningFailure(std::string message);
    
    // Returns the message associated with the exception.
    const std::string &what() const;
};

#endif /* ScanningFailure_h */
