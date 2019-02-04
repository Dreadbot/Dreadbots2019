/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <AHRS.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "frc/WPILib.h"
#include "Lifter.h"
#include <iostream>
#include "Drive.h"
#include "DoubleManipulator.h"
#include <Stilts.h>
#include <Ultra.h>
#include "AutoHatchPanel.h"
#include <AHRS.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h> //not needed once Abbie's stuff is changed

double const TALON_TICKS_PER_ROTATION = 4096;
float const LEVEL_3_HEIGHT = 21.5;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void TeleopLifterControl();
  void TeleopManipulatorControl();
  void Climb();
  void ElectricSolenoidTest(frc::Solenoid *solenoid);

//----------USB Controllers--------
frc::Joystick *js1; //Driver 1
frc::Joystick *js2; //Driver 2


Ultra *frontUltra;
Ultra *backUltra;

bool isXDown = false;

//js1
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
int const solButton = 1;
//js2
int const upButton = 6; 
int const downButton = 8; 
int const ballPickup = 1;
int const manualOverrideButton = 3;
int const climbButton = 10;
//---------------------------------

//-----------Solenoid--------------
frc::Compressor *compressor = new frc::Compressor(0);
frc::Solenoid *solenoid = new frc::Solenoid(4);
bool isSolOut = false;

//-------------Talons-------------------
WPI_TalonSRX *lFront; //left front
WPI_TalonSRX *rFront; //right front
WPI_TalonSRX *lBack; //left rear
WPI_TalonSRX *rBack; //right rear
WPI_TalonSRX *frontStilts; //motor that pushes down the front stilts
WPI_TalonSRX *backStilts; //motor that pushes down the back stilts
WPI_TalonSRX *driveStilts; //motor that drives the wheels on the stilts
//----------------------------------------//

int buttonTimer = 0;
int const BUTTON_TIMEOUT = 75;

//-----------Teleop Variables-------
int climbState;

//------------Auton Variables-------
double currentAngle;

//-----------Objects----------------
Lifter *lifter;
Drive *drive;
DoubleManipulator *manipulator;
Stilts *stilts;
Ultra *ultra;
AHRS *gyro;
 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
