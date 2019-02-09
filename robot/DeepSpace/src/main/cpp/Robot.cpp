/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------
             ???$$                               ?ZZ?                         
              ~??$$$$                             ZZZZZZ                        
              ???$$$$$$.                        $ZZZZZZZZZ.                     
              ???$$$$$$$$.                    .ZZZZZZZZZZZZ.                    
              ???$$$$$$$$$.                  ZZZZZZZ??ZZZZZZZ                   
             ???$$$$$$$$$$$$     ???????????ZZZZZZ??????ZZZZZZZ                 
             ???$$$$$??$$$$$$$????????????ZZZZZZZ???   ???ZZZZZZ                
             ???$$$$? :??$$$$$$??       .ZZZZZZ???      ???ZZZZZZZ              
            =??$$$$$.   ??I$$$$$$.     ZZZZZZZ????.       ???ZZZZZZZ            
            ???$$$$$     .??$$$$$$$   ZZZZZZ??? .??         ??IZZZZZZ           
            ???$$$$$      ????$$$$$$ZZZZZZZ???    ?          ??ZZZZZZZ          
            ???$$$$.         ???$$$$??ZZZZZZZ.               .ZZZZZZ??          
           ???$$$$$.         ????$$$$???ZZZZZZ.        ?    ZZZZZZZ??           
           ???$$$$$  ?     ??$$$$$$$$$???ZZZZZZZ.      ?  ,ZZZZZZ???            
           ???$$$$.  ??     .$$$$$$$$$. ???ZZZZZ      ? .ZZZZZZZ??              
          ???$$$$$??????       .$$        ??7.       ???ZZZZZZ???               
          ???$$$$$?$$$$???                        .???ZZZZZZ$??                 
          ???$$$$$$$$$$$????                    =????ZZZZZZ???                  
          ???$$$$$$$$$$7  ??????             ??????ZZZZZZZ??                    
         ???$$$$$$$$.       ???????????????????????ZZZZZ???                     
         ???$$$$..              ?????????????     ???Z$??                       
        .???$                                      ?????                        
                                                     ?                          
                                                                                
                                                              
    DDDDDDDDDDDDDD $DDDDDDD IDDDDDDDDDDDDDDD    .DDDDDDDDDDDZ DDDDDDDDDDDDDDDDD 
   DDDDDDDDDDDDDD  DDDDDDD  DDDDDDDDDDDDDDDDD  DDDDDDDDDDDDD DDDDDDDDDDDDDDDDDD 
   DDDDDDDDDDDDDD  DDDDDDD  DDDDDDDDDDDDDDDDD DDDDDDDDDDNDDD DDDDDDDDDDDDDDDDDI 
   DDDDDDD        DDDDDDDO DDDDDDD    DDDDDDD DDDDDDD             DDDDDDD       
  DDDDDDD+        DDDDDDD  DDDDDDD    DDDDDDD DDDDDDDDDD         +DDDDDDD       
  DDDDDDDDDDDDDD  DDDDDDD .DDDDDDD DDDDDDDDD   DDDDDDDDDDDD      DDDDDDD        
  DDDDDDDDDDDDDD DDDDDDD  DDDDDDDDDDDDDDDDD     IDDDDDDDDDDD     DDDDDDD        
 DDDDDDDDDDDDDD .DDDDDDD  DDDDDDDDDDDDD?           7DDDDDDDD    DDDDDDDZ        
 DDDDDDD        .DDDDDDD  DDDDDDIDDDDDDD     D       DDDDDDD    DDDDDDD         
~DDDDDDD        DDDDDDD  DDDDDDD  DDDDDDD    DDDDDDDDDDDDDD     DDDDDDD         
DDDDDDD         DDDDDDD. DDDDDDD  DDDDDDDD  7DDDDDDDDDDDDD     DDDDDDD   
DDDDDDD        DDDDDDDD DDDDDDD   .DDDDDDDD DDDDDDDDDDDD       DDDDDDD*/

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h> 
#include "Example.h"
#include <frc/Joystick.h>
#include <AHRS.h>
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "Drive.h"
#include "Stilts.h"

#include "SparkDrive.h"

#include "DoubleManipulator.h"
#include <Ultra.h>
#include <frc/Ultrasonic.h>
#include <Ultrasonic.h>

int currentLevel = 0;
int buttonTimer = 0;

//js1
int const slowButton = 7;
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
//js2
int const upButton = 6; 
int const downButton = 8;
int const ballPickup = 1;
int const hatchPickup = 4;
//---------------------------------
bool const DRIVE_ENABLED = true;
bool const LIFTER_ENABLED = false;
bool const MANIPULATOR_ENABLED = false;
bool const TURN_TO_ANGLE_ENABELED = false;
bool const SOLENOID_TEST_ENABLED = true;
bool const CLIMB_ENABLED = false;

//-------------Talons-------------------
//WPI_TalonSRX *lFront = new WPI_TalonSRX(4); //left front
//WPI_TalonSRX *rFront = new WPI_TalonSRX(1); //right front
//WPI_TalonSRX *lBack = new WPI_TalonSRX(2);  //left rear
//WPI_TalonSRX *rBack = new WPI_TalonSRX(3);  //right rear
//----------------------------------------

//Lifter *lifter = new Lifter();

//AHRS *gyro;
//Drive *drive = new Drive(lFront, lBack, rFront, rBack);

void Robot::RobotInit()
{
  //---------Joysticks---------------------
  js1 = new frc::Joystick(0);        //Driver 1
  js2 = new frc::Joystick(1);        //Driver 2
  js3 = new frc::Joystick(3);        //Backup Manual Controls
                                     //-------------Talons-------------------
  lFront = new WPI_TalonSRX(0);      //left front
  rFront = new WPI_TalonSRX(1);      //right front
  lBack = new WPI_TalonSRX(2);       //left rear
  rBack = new WPI_TalonSRX(3);       //right rear
  frontStilts = new WPI_TalonSRX(4); //motor that pushes down the front stilts
  backStilts = new WPI_TalonSRX(5);  //motor that pushes down the back stilts
  driveStilts = new WPI_TalonSRX(6); //motor that drives the wheels on the stilts
  //-----------Other Objects---------------
  gyro = new AHRS(SPI::Port::kMXP);


  lifter = new Lifter();
  drive = new Drive(lFront, lBack, rFront, rBack);
  stilts = new Stilts(*driveStilts, *backStilts, *frontStilts);
  gyro->ZeroYaw();
  ultra = new Ultra();
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

void Robot::AutonomousInit() 
{
  gyro->ZeroYaw();
}

void Robot::AutonomousPeriodic() 
{
  currentAngle = gyro->GetYaw();

  drive->DriveStraight(.3, currentAngle);
}

void Robot::TeleopInit()
{
  SmartDashboard::PutNumber("Target Angle", 0);
  if(LIFTER_ENABLED) {
    lifter->LiftInit();
  }
  if(MANIPULATOR_ENABLED) {
    manipulator->Init();
    manipulator->SetBallPickup(false);
  }
  buttonTimer = 0;
}

void Robot::TeleopPeriodic() 
{ 
  double targetAngle = 0.0;
  double currentAngle = gyro->GetYaw();
  targetAngle = SmartDashboard::GetNumber("Target Angle", 50.0);
  currentAngle = SmartDashboard::PutNumber("Current Angle", currentAngle);
  drive->RotateToAngle(0.5, targetAngle, currentAngle);
  
  if(!defenseMode)
  {
    Climb();
    TeleopLifterControl();
    TeleopManipulatorControl();
  }

  if (DRIVE_ENABLED)
  {
    drive->MecDrive(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)),
              js1->GetRawAxis(joystickRot), js1->GetRawButton(turboButton), js1->GetRawButton(slowButton));
  }

  if(SOLENOID_TEST_ENABLED) {
    ElectricSolenoidTest(solenoid);
  }

  if(CLIMB_ENABLED) {
    stilts->teleopStilts(js3->GetRawButton(frontStiltsUpButton), js3->GetRawButton(frontStiltsDownButton), js3->GetRawButton(backStiltsUpButton), js3->GetRawButton(backStiltsDownButton),
       js3->GetRawAxis(stiltsDriveStick), stilts->defaultStiltsSpeed);
  }
  // always increment buttonTimer - regardless of what functionality is Enabled or not
  buttonTimer++;
}

void Robot::TestPeriodic() 
{
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
