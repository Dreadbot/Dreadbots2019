/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Lifter.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

int const ENCODER_ID = 0;
int const TICKS_PER_ROTATION = 4096;
TalonSRX liftMotor = {ENCODER_ID};
double levels [] = {0.0, 1.0, 3.5, 5.0, 6.4, 7.0, 10.0};

Lifter::Lifter() {
}

//this stuff is from Abbie and Clara's code

void Lifter::RaiseLift(int level) 
{
    liftMotor.Set(ControlMode::Position, levels[level]*TICKS_PER_ROTATION);
}

void Lifter::LiftInit()
{
    liftMotor.SetSelectedSensorPosition(0);
}

int Lifter::GetLiftPosition()
{
    int currentPosition;
    currentPosition = liftMotor.GetSelectedSensorPosition();
    return currentPosition;
}