/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DoubleManipulator.h"

#include "ctre/Phoenix.h"
#include "frc/WPILib.h"

const int WRIST_ID = 0;
const int WHEEL_ID = 1;
TalonSRX wrist = {WRIST_ID};
TalonSRX intakeWheels = {WHEEL_ID};

DoubleManipulator::DoubleManipulator() {}

void DoubleManipulator::Init(){

}

void DoubleManipulator::RotateWrist(int position){ //0 = lowest, 1 = 45 degrees, 2 = 90 degrees
    //Must raise lift in order to get to 0
    
}

void DoubleManipulator::SpinWheels(double motorSpeed){

}

void DoubleManipulator::GrabPanel(){
//uses 1 solenoid
}

void DoubleManipulator::ReleasePanel(){
//uses 1 solenoid
}