//
//  ScanningFailure.cc
//  FileScanner
//
//  Created by July Zhuo on 2019-02-02.
//  Copyright © 2019 July Zhuo. All rights reserved.
//

#include "ScanningFailure.h"

ScanningFailure::ScanningFailure(std::string message): message(std::move(message)) {}

const std::string &ScanningFailure::what() const { return message; }


