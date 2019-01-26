/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Lifter.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include <iostream>
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>

int const ENCODER_ID = 0;
double const TICKS_PER_ROTATION = 4096;
TalonSRX liftMotor = {ENCODER_ID};
double levels [] = {0.0, 1.0, 3.5, 5.0, 6.4, 7.0, 15.0};
double motorSpeed = 0;
double MAXLIFTROTATION = 10000;
double MINLIFTROTATION = -500;

Lifter::Lifter() {}

    
void Lifter::SetLift(int level) 
{
    std::cout << "Raised lift to ";
    std::cout << level <<std::endl;
    std::cout << levels[level] << std::endl;
    std::cout << TICKS_PER_ROTATION << std::endl;
    std::cout << levels[level]*TICKS_PER_ROTATION << std::endl;
    liftMotor.Set(ControlMode::Position, levels[level]*TICKS_PER_ROTATION);
}

void Lifter::MoveLift(double motorSpeed)
{
    double speed = 0;

    if(GetLiftPosition() < MAXLIFTROTATION && GetLiftPosition() > MINLIFTROTATION)
    {
       speed = motorSpeed;
    }
    else if(GetLiftPosition() < MINLIFTROTATION) //if too low
    {
        speed = fmax(motorSpeed, 0);
    }
    else if(GetLiftPosition() > MAXLIFTROTATION) //if too high
    {
        speed = fmin(motorSpeed, 0);
    }
    liftMotor.Set(ControlMode::PercentOutput, speed);
}

void Lifter::LiftInit()
{
    liftMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    liftMotor.SetSensorPhase(true);

//    liftMotor.ConfigClosedLoopPeakOutput(0, .1);

    liftMotor.SetSelectedSensorPosition(0);
}

int Lifter::GetLiftPosition()
{
    int currentPosition;
    currentPosition = liftMotor.GetSelectedSensorPosition();
    return currentPosition;
}

int Lifter::CheckHeight()
{
    //0.0, 1.0, 3.5, 5.0, 6.4, 7.0, 15.0 
    //these are the current rotations for the different levels, once we have a bot they will need to be changed
    int currentHeight;
    int currentRotation;
    currentRotation = liftMotor.GetSelectedSensorPosition()/TICKS_PER_ROTATION;
    if(currentRotation > -0.5 && currentRotation < 0.5)
    {
        currentHeight = 0;
    }
    else if(currentRotation > 0.5 && currentRotation < 1.5)
    {
        currentHeight = 1;
    }
    else if(currentRotation > 3.0 && currentRotation < 4.0)
    {
        currentHeight = 2;
    }
    else if(currentRotation > 4.5 && currentRotation < 5.5)
    {
        currentHeight = 3;
    }
    else if(currentRotation > 5.9 && currentRotation < 6.9)
    {
        currentHeight = 4;
    }
    else if(currentRotation > 6.5 && currentRotation < 7.5)
    {
        currentHeight = 5;
    }
    else if(currentRotation > 14.5 && currentRotation < 15.5)
    {
        currentHeight = 6;
    }
    else
    {
        currentHeight = -100;
    }
    return currentHeight;
    frc::SmartDashboard::PutNumber("Current level", currentHeight); //needs to be changed to Shuffleboard
}