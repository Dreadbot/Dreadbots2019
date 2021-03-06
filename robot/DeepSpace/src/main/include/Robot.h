/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string.h>
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
#include <SparkDrive.h>
double const TALON_TICKS_PER_ROTATION = 4096;
float const LEVEL_3_HEIGHT = 21;
float const LEVEL_2_HEIGHT = 8.5;

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
  void AutonBall(int position);
  void AutonHatch(int position);
  void AutonHatch(int startPosition, int targetPosition);
  int AutonPositionDecider();
  int AutonGamePieceDecider();
  void RunAuton();
  void Climb(int level);
  void ElectricSolenoidTest(frc::Solenoid *solenoid);
  void DefenseMode();
  void CameraSwap();
  void AutoAlign();
  bool IsVisionTargetFound();
  void StrafeToAlign(std::string direction);
  void BallPickup(bool in, bool out);
//----------USB Controllers--------
frc::Joystick *js1; //Driver 1
frc::Joystick *js2; //Driver 2
frc::Joystick *js3; //Backup Manual Controls

bool isSolButtonDown = false;
bool isADown = false;
bool isBackDown = false;
bool prototypeRobot = false;

int currentCamera = 0;

//js1
int const turboButton = 8;
int const slowButton = 6;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
int const defenseButton = 2;
int const liftOverrideButton = 3;
int const cameraButton = 9;
int const alignMacro = 5;
int const downButton = 7;
int const upButton = 5;
//js2
int const lowerManipulator = 7;
int const raiseManipulator = 5;
int const engageSol = 6;
int const disengageSol = 8;
int const manipulatorOverrideButton = 3;
int const climbButton = 10;
int const level2Climb = 9;
int const ballPickup = 1;
int const shootBall = 2;
//js3
int const frontStiltsUpButton = 5;
int const frontStiltsDownButton = 7;
int const backStiltsUpButton = 8;
int const backStiltsDownButton = 6;
int const stiltsDriveStick = 3;
//---------------------------------

//-----------Solenoid--------------

//If you comment these out, please uncomment them before pushing to avoid compilation errors for other people
frc::Compressor *compressor = new frc::Compressor(0);
frc::Solenoid *solenoid = new frc::Solenoid(0);
bool isSolOut = false;

//-------------Talons-------------------
WPI_TalonSRX *lFront; //left front
WPI_TalonSRX *rFront; //right front
WPI_TalonSRX *lBack; //left rear
WPI_TalonSRX *rBack; //right rear
rev::CANSparkMax *lFrontSpark;
rev::CANSparkMax *rFrontSpark;
rev::CANSparkMax *lBackSpark;
rev::CANSparkMax *rBackSpark;
WPI_TalonSRX *frontStilts; //motor that pushes down the front stilts
WPI_TalonSRX *backStilts; //motor that pushes down the back stilts
WPI_TalonSRX *driveStilts; //motor that drives the wheels on the stilts
WPI_TalonSRX *wrist; 
WPI_TalonSRX *intakeWheels;
//----------------------------------------//

int buttonTimer = 0;
int const BUTTON_TIMEOUT = 25;


frc::SendableChooser<int> strafeDir;

//------------Auton Variables-------
double currentAngle;
double x1, y1, x2, y2, cameraAngle, cameraLength;
Drive::StrafeDirection strafeDirection;

int autoState;
frc::SendableChooser<int> positionDecider;
frc::SendableChooser<int> gamePieceDecider;

int climbTimeout = 0;
double strafeDifference;
   
//-----------TeleopVariables---------
int climbState;
int stagedClimbState;
bool defenseMode = false;
bool level3Climbing = false;
bool level2Climbing = false;
bool teleopClimbing = false;

float const driveStiltsSpeed = 0.4;
float const sparksClimbSpeed = 0.2;
//-----------Objects----------------
Lifter *lifter;
Drive *drive;
SparkDrive *sparkDrive;
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
