/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Example.h"
#include <iostream>
//Hello

Example::Example() {}

void Example::HelloWorld(int value) {
    std::cout << "Hello World! " << value << " is the parameter" << std::endl;
}