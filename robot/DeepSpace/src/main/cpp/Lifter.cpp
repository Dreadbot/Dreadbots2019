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
#include "Robot.h"


int const ENCODER_ID = 8;

WPI_TalonSRX liftMotor = {ENCODER_ID};
double levels [] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
double motorSpeed = 0;
double MAXLIFTROTATION = 1000000000;
double MINLIFTROTATION = -10000000; //set to just under zero for actual lift
float const LIFT_GEAR_RATIO = 175;
float const DIAMETER_LIFT = 1.5;
float const PI = 3.14159265;


Lifter::Lifter() {

}

    
void Lifter::SetLift(int level) 
{
    /* std::cout << "Raised lift to ";
     std::cout << level <<std::endl;
     std::cout << levels[level] << std::endl;
     std::cout << TALON_TICKS_PER_ROTATION << std::endl;
     std::cout << levels[level]*TALON_TICKS_PER_ROTATION << std::endl;
    liftMotor.Set(ControlMode::Position, levels[level]*TALON_TICKS_PER_ROTATION);*/
    liftMotor.Set(ControlMode::Position, InchesLift(levels[level]) );
    liftMotor.SetSafetyEnabled(false);
    // // liftMotor.StopMotor();
    // liftMotor.SetExpiration(1);
    std::cout << InchesLift(levels[level]) << std::endl;
}

void Lifter::Shrug(){
    liftMotor.Set(ControlMode::Position, TALON_TICKS_PER_ROTATION * 1);
    SetCurrentLevel(0);
}

void Lifter::MoveLift(double motorSpeed)
{
    double speed = 0;
    double liftPosition = GetEncoderPosition();

    if(liftPosition < MAXLIFTROTATION && liftPosition > MINLIFTROTATION)
    {
       speed = motorSpeed;
    }
    else if(liftPosition <= MINLIFTROTATION) //if too low
    {
        speed = fmax(motorSpeed, 0);
    }
    else if(liftPosition >= MAXLIFTROTATION) //if too high
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

int Lifter::GetEncoderPosition()
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
    currentRotation = liftMotor.GetSelectedSensorPosition()/TALON_TICKS_PER_ROTATION;

    if(currentRotation > -0.5 && currentRotation < 0.5)
    {
        currentHeight = 0;
    }

    else if(currentRotation > 0.5 && currentRotation < 1.5)
    {
        currentHeight = 1;
    }

    else if(currentRotation > 1.5 && currentRotation < 2.5)
    {
        currentHeight = 2;
    }

    else if(currentRotation > 2.5 && currentRotation < 3.5)
    {
        currentHeight = 3;
    }

    else if(currentRotation > 3.5 && currentRotation < 4.5)
    {
        currentHeight = 4;
    }

    else if(currentRotation > 4.5 && currentRotation < 5.5)
    {
        currentHeight = 5;
    }

    else if(currentRotation > 5.5 && currentRotation < 6.5)
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

void Lifter::IncreaseCurrentLevel()
{
    currentLiftLevel++;
    SetLift(currentLiftLevel);
}

void Lifter::DecreaseCurrentLevel()
{
    currentLiftLevel--;
    SetLift(currentLiftLevel);
}

int Lifter::GetCurrentLevel()
{
    return currentLiftLevel;
}

int Lifter::InchesLift(float inches)
{
    int ticks = (int) ( inches * ( ( TALON_TICKS_PER_ROTATION * LIFT_GEAR_RATIO ) / ( DIAMETER_LIFT * PI ) ) );
    return ticks;
}

void Lifter::SetCurrentLevel(int level){
    currentLiftLevel = level;
}