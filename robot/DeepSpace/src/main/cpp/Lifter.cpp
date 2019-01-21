/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Lifter.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

TalonSRX liftMotor = {0};

Lifter::Lifter() {}

void Lifter::Lift (int height){
    
}

//this stuff is from Abbie and Clara's code

void Lifter::RaiseLift() 
{
    double motorSpeed = 0.5;
    liftMotor.Set(ControlMode::PercentOutput, motorSpeed);  
}

void Lifter::LiftInit()
{
    liftMotor.SetSelectedSensorPosition(0, 0, 0);
}

int Lifter::GetLiftPosition()
{
    int currentLift;
    currentLift = liftMotor.GetSelectedSensorPosition(0);
    return currentLift;
}