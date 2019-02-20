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

int currentLevel = 0;
int buttonTimer = 0;

//js1
int const slowButton = 7;
int const turboButton = 8;
int const joystickX = 0;
int const joystickY = 1;
int const joystickRot = 2;
int const alignMacro = 5;
//js2
int const upButton = 6; 
int const downButton = 8;
int const lowerManipulator = 7;
int const raiseManipulator = 5;
int const ballPickup = 1;
int const shootBall = 2;
//---------------------------------
//When pushing code, these should be true so everyone else's code works when they pull
bool const DRIVE_ENABLED = true;
bool const LIFTER_ENABLED = true;
bool const MANIPULATOR_ENABLED = false;
bool const TURN_TO_ANGLE_ENABELED = false;
bool const SOLENOID_TEST_ENABLED = true;
bool const CLIMB_ENABLED = true;
bool const VISION_ENABLED = false;
bool const BALL_PICKUP_ENABLED = true;

//-------------Talons-------------------
// WPI_TalonSRX *lFront = new WPI_TalonSRX(4); //left front
// WPI_TalonSRX *rFront = new WPI_TalonSRX(1); //right front
// WPI_TalonSRX *lBack = new WPI_TalonSRX(2);  //left rear
// WPI_TalonSRX *rBack = new WPI_TalonSRX(3);  //right rear
//----------------------------------------

//Lifter *lifter = new Lifter();

//AHRS *gyro;

void Robot::RobotInit()
{
    //CameraServer::GetInstance()->StartAutomaticCapture();

    positionDecider.SetDefaultOption("Left", 0);
    positionDecider.AddOption("Center", 1);
    positionDecider.AddOption("Right", 2);

    gamePieceDecider.SetDefaultOption("Hatch", 0);
    gamePieceDecider.AddOption("Ball", 1);

  //---------Joysticks---------------------
  js1 = new frc::Joystick(0);        //Driver 1
  js2 = new frc::Joystick(1);        //Driver 2
  js3 = new frc::Joystick(2);        //Backup Manual Controls
                                     //-------------Talons-------------------
  lFront = new WPI_TalonSRX(0);      //left front
  rFront = new WPI_TalonSRX(1);      //right front
  lBack = new WPI_TalonSRX(2);       //left rear
  rBack = new WPI_TalonSRX(3);       //right rear
                                     //-------------Sparks-------------------
  lFrontSpark = new rev::CANSparkMax(0, rev::CANSparkMax::MotorType::kBrushless);
  rFrontSpark = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  lBackSpark = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
  rBackSpark = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
                                     //-------Talons pt.2: Electric Boogaloo-----
  wrist = new WPI_TalonSRX(4);       //motor that rotates the manipulator wrist
  intakeWheels = new WPI_TalonSRX(5);//motor that spins the intake wheels on the manipulator
  backStilts = new WPI_TalonSRX(6);  //motor that pushes down the back stilts
  driveStilts = new WPI_TalonSRX(7); //motor that drives the wheels on the stilts
  frontStilts = new WPI_TalonSRX(9); //motor that pushes down the front stilts
  //-----------Other Objects---------------
  gyro = new AHRS(SPI::Port::kMXP);
  lifter = new Lifter();
  drive = new Drive(lFront, lBack, rFront, rBack);
  sparkDrive = new SparkDrive(lFrontSpark, lBackSpark, rFrontSpark, rBackSpark);
  stilts = new Stilts(*driveStilts, *backStilts, *frontStilts);
  gyro->ZeroYaw();
  ultra = new Ultra();
  manipulator = new DoubleManipulator(*wrist, *intakeWheels);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating
 */
void Robot::RobotPeriodic() 
{

}

void Robot::AutonomousInit() 
{
  gyro->ZeroYaw();
  lifter->SetLift(0);
}

void Robot::AutonomousPeriodic() 
{
  currentAngle = gyro->GetYaw();

  //drive->DriveStraight(.3, currentAngle);
  //drive->StrafeStraight(currentAngle, 0, 0.5);
}

void Robot::TeleopInit()
{
  std::cout << "TeleopInit" << std::endl;
  SmartDashboard::PutNumber("Target Angle", 0);
  SmartDashboard::PutBoolean("Vision Target Found", false);
  autoClimbing = true;
  if(LIFTER_ENABLED) {
    lifter->LiftInit();
  }
  buttonTimer = 0;

  if(MANIPULATOR_ENABLED) {
    manipulator->Init();
    //manipulator->SetBallPickup(true);
  }
}

void Robot::TeleopPeriodic() 
{ 
  std::cout << "Back: " << backStilts->GetSelectedSensorPosition() << std::endl;
  std::cout << "Front: " << frontStilts->GetSelectedSensorPosition() << std::endl;
  if(VISION_ENABLED)
  {
    std::string direction = frc::SmartDashboard::GetString("StrafeToAlign", "correct");
    std::cout << "direction: " << direction << std::endl;
    StrafeToAlign(direction);
  }
  lifter->TesterLift(0);
  double targetAngle = 0.0;
  double currentAngle = gyro->GetYaw();
  targetAngle = SmartDashboard::GetNumber("Target Angle", 50.0);
  currentAngle = SmartDashboard::PutNumber("Current Angle", currentAngle);
  double currentSpeed = rFront->GetMotorOutputPercent();
  SmartDashboard::PutNumber("Current Speed", currentSpeed);
  SmartDashboard::PutBoolean("Vision Target Found", IsVisionTargetFound());
  SmartDashboard::PutNumber("Ultra LF Distance", ultra->getDistanceLeftFront());
  SmartDashboard::PutNumber("Ultra RF Distace", ultra->getDistanceRightFront());
  SmartDashboard::PutNumber("Ultra LB Distance", ultra->getDistanceLeftBack());
  SmartDashboard::PutNumber("Ultra RB Distance", ultra->getDistanceRightBack());
  SmartDashboard::GetNumber("Strafe Difference", strafeDifference);
  
  // if (IsVisionTargetFound())
  // {
  //   SmartDashboard::PutBoolean("Vision Target Found", true);
  // }
  // else
  // {
  //   SmartDashboard::PutBoolean("Vision Target Found", false);
  // }

  if (TURN_TO_ANGLE_ENABELED)
  {
     double targetAngle = 0.0;
     double currentAngle = gyro->GetYaw();
     drive->RotateToAngle(0.5, targetAngle, currentAngle);
     targetAngle = SmartDashboard::GetNumber("Target Angle", 50.0);
     currentAngle = SmartDashboard::PutNumber("Current Angle", currentAngle);
  }
  
  if(!defenseMode)
  { 
    if(CLIMB_ENABLED)
    {
      //Climb();
    }
    if(LIFTER_ENABLED)
    {
      TeleopLifterControl();
     /* if(js2->GetRawButton(upButton))
      {
        lifter->TesterLift(50);
      }gbButton(downButton))
      {
        lifter->TesterLift(50);
      }
      else{
        lifter->TesterLift(0);
      }*/
    }
    if(MANIPULATOR_ENABLED)
    {
      TeleopManipulatorControl();
    }
    if(SOLENOID_TEST_ENABLED)
    {
      //ElectricSolenoidTest(solenoid);
      if(js1->GetRawButton(engageSol)) 
      {
      std::cout << "engaging sol" << std::endl;
      manipulator->GrabPanel(solenoid);
      }
      else if(js1->GetRawButton(disengageSol))
      {
      std::cout << "disengaging sol" << std::endl;
      manipulator->ReleasePanel(solenoid); 
      } 
    }
    if(BALL_PICKUP_ENABLED)
      BallPickup(js2->GetRawButton(ballPickup), js2->GetRawButton(shootBall));
  }
 if (DRIVE_ENABLED)
  {
    //MecDrive2 DOES NOT WORK with rotating right
    //drive->MecDrive2(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)),
    drive->MecDrive(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)),

    //sparkDrive->MecDrive(js1->GetRawAxis(joystickX), -(js1->GetRawAxis(joystickY)),
              js1->GetRawAxis(joystickRot), js1->GetRawButton(turboButton), js1->GetRawButton(slowButton));
    
  }


  if(CLIMB_ENABLED) {
    if(!autoClimbing)
    {
      stilts->teleopStilts(js3->GetRawButton(frontStiltsUpButton), js3->GetRawButton(frontStiltsDownButton), js3->GetRawButton(backStiltsUpButton), js3->GetRawButton(backStiltsDownButton),
       js3->GetRawAxis(stiltsDriveStick), stilts->defaultFrontSpeed, stilts->defaultBackSpeed);
       std::cout << "Front Encoder Position: " << frontStilts->GetSelectedSensorPosition() << ", ";
       std::cout << stilts->getFrontHeight() << std::endl;
       std::cout << "Back Encoder Position: " << backStilts->GetSelectedSensorPosition() << ", ";
       std::cout << stilts->getBackHeight() << std::endl;
    }
    if(js3->GetRawButton(10))
    {
      autoClimbing = false;
    }
    if(autoClimbing)
    {
       if(js3->GetRawButton(2))
       {
         stilts->setFrontToHeight(6);
         stilts->setBackToHeight(6);
       }
       else if(js3->GetRawButton(3))
       {
         stilts->setFrontToHeight(0);
         stilts->setBackToHeight(0);
       }
       else if(js3->GetRawButton(4))
       {
          stilts->ThreeStageHeight(-3);
          stilts->ThreeStageHeight(-3);
       }
    }
  }
  // always increment buttonTimer - regardless of what functionality is Enabled or not
  
  CameraSwap();

  buttonTimer++;
}

bool Robot::IsVisionTargetFound()
{
  return true;
}

void Robot::TestPeriodic() 
{
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
