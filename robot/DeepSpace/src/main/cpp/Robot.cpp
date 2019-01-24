/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "Example.h"
#include <frc/Joystick.h>
#include <AHRS.h>
#include "rev/CANSparkMax.h"

#include "ctre/Phoenix.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "Drive.h"
#include "Stilts.h"



int currentLevel = 0;
int buttonTimer = 0;

//----------USB Controllers--------
frc::Joystick *js1 = new frc::Joystick(0);
frc::Joystick *js2 = new frc::Joystick(1); //Driver 2


int const upButton = 6;
int const downButton = 8;
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
//---------------------------------

//-------------Talons-------------------
WPI_TalonSRX *lFront = new WPI_TalonSRX(0); //left front
WPI_TalonSRX *rFront = new WPI_TalonSRX(1); //right front
WPI_TalonSRX *lBack = new WPI_TalonSRX(2); //left rear
WPI_TalonSRX *rBack = new WPI_TalonSRX(3); //right rear
//----------------------------------------

Lifter *lifter = new Lifter();
Drive *drive = new Drive(lFront, lBack, rFront, rBack);

void Robot::RobotInit() 
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Example *example;
  // example = new Example();
  // example->HelloWorld(4);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() 
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() 
{
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit()
{
  lifter->LiftInit();
}

void Robot::TeleopPeriodic() 
{
  //I believe not all the code for these functions was pushed. Check with Abbie

  /*std::cout << lifter->GetLiftPosition() << std::endl;
  if(js1->GetRawButton(upButton) && buttonTimer >= 75 && currentLevel < 7){
    buttonTimer = 0;
    currentLevel++;
    std::cout << "UpButton Pressed" << std::endl;
    lifter->RaiseLift(currentLevel); 
  }
  if(js1->GetRawButton(downButton) && buttonTimer >= 75 && currentLevel > 0){
    buttonTimer = 0;
    currentLevel--;
    lifter->RaiseLift(currentLevel);
  }
  buttonTimer++;
  TeleopLifterControl();
*/
  drive->MecDrive(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)), js1->GetRawAxis(joystickRot), js1->GetRawButton(turboButton));
}

void Robot::TestPeriodic() 
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
