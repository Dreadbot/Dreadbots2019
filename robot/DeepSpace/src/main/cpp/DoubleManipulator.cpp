/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DoubleManipulator.h"

#include "ctre/Phoenix.h"
#include "frc/WPILib.h"
#include "Robot.h"

const int WRIST_ID = 0;
const int WHEEL_ID = 1;
double positions[] = {0.0, 5.0, 10.0};
TalonSRX wrist = {WRIST_ID};
TalonSRX intakeWheels = {WHEEL_ID};

DoubleManipulator::DoubleManipulator() {}

void DoubleManipulator::Init()
{
    wrist.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

    wrist.SetSensorPhase(true);
    wrist.SetSelectedSensorPosition(0);

    //intakeWheels.SetSensorPhase(true);
    //intakeWheels.SetSelectedSensorPosition(0);
    //intakeWheels.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
}

void DoubleManipulator::RotateWrist(int position)
{ //0 = lowest, 1 = 45 degrees, 2 = 90 degrees
    //Must raise lift in order to get to 0
    std::cout << "moving to position: " << (positions[position] * TALON_TICKS_PER_ROTATION) << std::endl;
    std::cout << "Motor Position: " << wrist.GetSelectedSensorPosition() << std::endl;
    wrist.Set(ControlMode::Position, (positions[position] * TALON_TICKS_PER_ROTATION));
}

void DoubleManipulator::SpinWheels(double motorSpeed)
{
    intakeWheels.Set(ControlMode::PercentOutput, motorSpeed);
}

void DoubleManipulator::GrabPanel()
{
    //uses 1 solenoid
}

void DoubleManipulator::ReleasePanel()
{
    //uses 1 solenoid
}

void DoubleManipulator::SetBallPickup(bool value)
{
    pickingUp = value;
}

bool DoubleManipulator::CheckBallPickup()
{
    return pickingUp;
}