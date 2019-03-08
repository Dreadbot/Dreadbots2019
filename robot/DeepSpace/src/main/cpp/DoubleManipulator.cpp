/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "DoubleManipulator.h"

#include "ctre/Phoenix.h"
#include "frc/WPILib.h"


//WRIST MUST BE TILTED FORWARDS ~10 DEGREES TO PICKUP FROM LOADING STATION AND ~99 DEGREES FROM THE FLOOR (0 DEGREES = STARTING POSITION)
//ASK ABBIE ABOUT IT


//const int WRIST_ID = 0;
//const int WHEEL_ID = 1;
const int SAFETY_TIMEOUT_SECONDS = 3;
const int GEAR_RATIO = 514;
double positions[] = {0, 24, 57, 114};//Angles of the manipulator, where 0 is straight up, flush with the lift, and -90 is facing the ground
int actualPositions[] = {0, 122795, 317190, 578940}; //actual encoder values of where we want to go (without math)
//TalonSRX wrist = {WRIST_ID};
//TalonSRX intakeWheels = {WHEEL_ID};

DoubleManipulator::DoubleManipulator (WPI_TalonSRX & wrist_in, WPI_TalonSRX &intakeWheels_in):wrist(wrist_in), intakeWheels(intakeWheels_in) {}

void DoubleManipulator::Init()
{
    wrist.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

    wrist.SetSensorPhase(true);
    wrist.ConfigClosedLoopPeakOutput(0, 0.7);
    currentPosition = 0;
    wrist.SetSelectedSensorPosition(0);

    wrist.SetSafetyEnabled(false);
    // liftMotor.StopMotor();
    wrist.SetExpiration(SAFETY_TIMEOUT_SECONDS);
    wrist.Config_kP(0, 0.7);
    wrist.Config_kI(0, 1e-4);
    wrist.Config_kD(0, 1);
    wrist.Set(ControlMode::Position, 0);
    wrist.Set(ControlMode::PercentOutput, 0);

    //intakeWheels.SetSensorPhase(true);
    //intakeWheels.SetSelectedSensorPosition(0);
    //intakeWheels.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
}

void DoubleManipulator::RotateWrist(int position)
{ //0 = lowest, 1 = 45 degrees, 2 = 90 degrees, 3 = a little past 90 for rocket
    //Must raise lift in order to get to 0
    std::cout << "moving to position: " << (((positions[position] / 360) * TALON_TICKS_PER_ROTATION)*GEAR_RATIO) << std::endl;
    std::cout << "Motor Position: " << wrist.GetSelectedSensorPosition() << std::endl;
    currentPosition = position;
    wrist.Set(ControlMode::Position, ((positions[position] / 360) * TALON_TICKS_PER_ROTATION)*GEAR_RATIO);
    //wrist.Set(ControlMode::Position, actualPositions[position]); //just sets the wrist to pre-set values
}

void DoubleManipulator::SpinWheels(double motorSpeed)
{
    intakeWheels.Set(ControlMode::PercentOutput, motorSpeed);
}

void DoubleManipulator::GrabPanel(Solenoid *sol)
{
    sol->Set(false);
}

void DoubleManipulator::ReleasePanel(Solenoid *sol)
{
    sol->Set(true);
}

void DoubleManipulator::SetBallPickup(bool value)
{
    pickingUp = value;
}

bool DoubleManipulator::CheckBallPickup()
{
    return pickingUp;
}

int DoubleManipulator::GetCurrentPosition(){
    return currentPosition;
}

void DoubleManipulator::SetCurrentPosition(int position){
    currentPosition = position;
}