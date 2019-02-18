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
#include <array>


int const ENCODER_ID = 8;

WPI_TalonSRX liftMotor = {ENCODER_ID};
double levels [] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
double slop = 0.5;
double motorSpeed = 0;
double MAXLIFTROTATION = 1000000000;
double MINLIFTROTATION = -10000000; //set to just under zero for actual lift
float const LIFT_GEAR_RATIO = 175;
float const DIAMETER_LIFT = 1.5;
float const PI = 3.14159265358979823846264288;


Lifter::Lifter() {
    liftMotor.ConfigNominalOutputForward(0,0);
    liftMotor.ConfigNominalOutputReverse(0,0);
    liftMotor.ConfigPeakOutputForward(1,0);
    liftMotor.ConfigPeakOutputReverse(-1,0);

    liftMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    liftMotor.SetSensorPhase(true);

    liftMotor.SetSafetyEnabled(false);
    liftMotor.SetSelectedSensorPosition(0);

    liftMotor.Config_kP(0, 0.5);
    liftMotor.Config_kI(0, 1e-4);
    liftMotor.Config_kD(0, 1);
    liftMotor.Set(ControlMode::Position, 0);
    liftMotor.Set(ControlMode::PercentOutput, 0);
}

void Lifter::TesterLift(double position)
{
    std::cout << "Currently at: " << liftMotor.GetSelectedSensorPosition() << std::endl;
    //std::cout << "going to: " << position << std::endl;
}
void Lifter::SetLift(int level) 
{
    /* std::cout << "Raised lift to ";
     std::cout << level <<std::endl;
     std::cout << levels[level] << std::endl;
     std::cout << TALON_TICKS_PER_ROTATION << std::endl;
     std::cout << levels[level]*TALON_TICKS_PER_ROTATION << std::endl;
    liftMotor.Set(ControlMode::Position, levels[level]*TALON_TICKS_PER_ROTATION);*/
    liftMotor.Set(ControlMode::Position, InchesLift(levels[level]));
   // std::cout << "Lift Encoder Position: " << liftMotor.GetSelectedSensorPosition() << std::endl;
    std::cout << "Being set to: " << InchesLift(levels[level]) << std::endl;
    std::cout << "Level: " << level << std::endl;
    //liftMotor.SetSafetyEnabled(false);
    // // liftMotor.StopMotor();
    // liftMotor.SetExpiration(1);
    
}

void Lifter::Shrug(){
    liftMotor.Set(ControlMode::Position, TALON_TICKS_PER_ROTATION * 1);
    SetCurrentLevel(0);
}

void Lifter::MoveLift(double motorSpeed)
{
    //std::cout << "Position: " << liftMotor.GetSelectedSensorPosition() << std::endl;
    //std::cout <<"Velocity: "<< liftMotor.GetSelectedSensorVelocity() << std::endl;
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

    for (int i = 0; i < (sizeof(levels))/8; i++) {
        if(currentRotation > levels[i] - slop && currentRotation < levels[i] + slop){
            currentHeight = i;
        }
    }
    frc::SmartDashboard::PutNumber("Current level", currentHeight); //needs to be changed to Shuffleboard
    return currentHeight;
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
    return ticks/31;//fudge factor based on observation of Test Robit, not set in stone
}

void Lifter::SetCurrentLevel(int level){
    currentLiftLevel = level;
}