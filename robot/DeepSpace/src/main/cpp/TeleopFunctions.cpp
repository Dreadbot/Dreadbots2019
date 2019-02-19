#include "Robot.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "DoubleManipulator.h"
#include <Stilts.h>
#include <string.h>

void Robot::TeleopLifterControl()
{
  //lifter->TesterLift(0);
  //std::cout << lifter->GetEncoderPosition() << std::endl;
  if (js2->GetRawButton(manualOverrideButton))
  {
    if (js2->GetRawButton(upButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() < 6)
    {
      buttonTimer = 0;
      lifter->IncreaseCurrentLevel();
      //std::cout << "UpButton Pressed" << std::endl;
      lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
    if (js2->GetRawButton(downButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() > 0)
    {
      buttonTimer = 0;
      lifter->DecreaseCurrentLevel();
      lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
  }
  else
  {
    if (js2->GetRawButton(upButton))
    {
      lifter->MoveLift(0.5);
    }
    else if (js2->GetRawButton(downButton))
    {
      lifter->MoveLift(-0.5);
    }
    else
    {
      lifter->MoveLift(0);
    }
  }
}

void Robot::TeleopManipulatorControl()
{ std::cout << wrist->GetSelectedSensorPosition() << std::endl;
  //std::cout<<"Button timer: " << (buttonTimer >= BUTTON_TIMEOUT) << std::endl;
  //std::cout<<"Picking up: " << manipulator->CheckPickup() <<std::endl;
  if (js2->GetRawButton(manualOverrideButton))
  {/*
    if (js2->GetRawButton(lowerManipulator) && buttonTimer >= BUTTON_TIMEOUT && Robot::manipulator->GetCurrentPosition() < 3)
    {
      
      if(manipulator->GetCurrentPosition() == 2){
        std::cout << "shruged" << std::endl;
        Robot::lifter->Shrug();
        manipulator->RotateWrist(manipulator->GetCurrentPosition() + 1);
      } else{
        std::cout << "button pressed" << std::endl;
        buttonTimer = 0;
        manipulator->RotateWrist(manipulator->GetCurrentPosition() + 1);
        manipulator->SetBallPickup(true);
        manipulator->SpinWheels(0.5);
      }
    }
    if (js2->GetRawButton(raiseManipulator) && buttonTimer >= BUTTON_TIMEOUT && Robot::manipulator->GetCurrentPosition() > 0)
    {
        buttonTimer = 0;
        manipulator->RotateWrist(manipulator->GetCurrentPosition() - 1);
        manipulator->SetBallPickup(false);
        //manipulator->SpinWheels(0);
    }
    if(js2->GetRawButton(ballPickup) && buttonTimer >= BUTTON_TIMEOUT){
      manipulator->SpinWheels(0.4);
    }
    else if(js2->GetRawButton(shootBall) && buttonTimer >= BUTTON_TIMEOUT){
      manipulator->SpinWheels(-0.4);
    }
    else{
      manipulator->SpinWheels(0);
    }*/
  }
  else {
    if(js2->GetRawButton(raiseManipulator))
    {
      wrist->Set(ControlMode::PercentOutput, 0.7);
    }
    else if(js2->GetRawButton(lowerManipulator))
    {
      wrist->Set(ControlMode::PercentOutput, -0.7);
    }
    else
    {
      wrist->Set(ControlMode::PercentOutput, 0);
    }
  }
}

//Fully autonomous level 3 climb using ultrasonics and encoders
void Robot::Climb()
{
  if (js2->GetRawButton(climbButton))
  {
    climbState = 1;
    while (climbState != 6 && !js2->GetRawButton(manualOverrideButton))
    {

      if (climbState == 1 && stilts->getFrontHeight() >= LEVEL_3_HEIGHT && stilts->getBackHeight() >= LEVEL_3_HEIGHT)
      {
        climbState = 2; //Drive the stilt wheel
      }
      else if (climbState == 2 && ultra->getDistanceLeftFront() <= 5)
      {
        climbState = 3; //Retract front
      }
      else if (climbState == 3 && stilts->getFrontHeight() == 0)
      {
        climbState = 4; //drive the stilt wheel
      }
      else if (climbState == 4)
      {
        climbState = 5; //retract back wheel
      }
      else if (climbState == 5 && stilts->getBackHeight() == 0)
      {
        climbState = 6; //finished
      }

      if (climbState = 1)
      {
        stilts->setFrontToHeight(LEVEL_3_HEIGHT);
        stilts->setBackToHeight(LEVEL_3_HEIGHT);
      }
      if (climbState == 2)
      {
        stilts->driveWheels(0.2);
      }
      if (climbState == 3)
      {
        stilts->setFrontToHeight(0);
      }
      if (climbState == 4)
      {
        stilts->driveWheels(0.2);
      }
      if (climbState == 5)
      {
        stilts->setBackToHeight(0);
      }
    }
  }
}
void Robot::ElectricSolenoidTest(frc::Solenoid *solenoid)
{
  //toggle function for button "X" to fire solenoid
  /*if (js1->GetRawButton(solButton) && isSolOut == false && Robot::isXDown == false)
  {
    solenoid->Set(true);
    isSolOut = true;
    isXDown = true;
  }
  
  else if (!js1->GetRawButton(solButton) && isSolOut == true)
    isXDown = false;

  else if (js1->GetRawButton(solButton) && isSolOut == true && isXDown == false)
  {
    solenoid->Set(false);
    isSolOut = false;
    isXDown = true;
  }

  else if (!js1->GetRawButton(solButton) && isSolOut == false)
    isXDown = false;
    */
  if(js1->GetRawButton(engageSol))
    solenoid->Set(true);
  
  if(js1->GetRawButton(disengageSol))
    solenoid->Set(false);

}

void Robot::DefenseMode()
{
  //toggle function for button "A" to retract all appendages and lock them in place
  if (js1->GetRawButton(defenseButton) && defenseMode == false && Robot::isSolButtonDown == false)
  {
    defenseMode = true;
    isSolButtonDown = true;
  }

  else if (!js1->GetRawButton(defenseButton) && isSolOut == true)
    isADown = false;

  else if (js1->GetRawButton(defenseButton) && defenseMode == true && isSolButtonDown == false)
  {
    defenseMode = false;
    isSolButtonDown = true;
  }

  else if (!js1->GetRawButton(defenseButton) && isSolOut == false)
    isADown = false;


  if(defenseMode)
  {
    solenoid->Set(false);
    lifter->SetLift(0);
  }
}

void Robot::CameraSwap()
{
  //code to swap the camera feed from one camera to another by pressing "Back" on controller 1
  if (js1->GetRawButton(cameraButton) && currentCamera == 0 && Robot::isBackDown == false)
  {
    currentCamera = 1;
    isBackDown = true;
  }

  else if (!js1->GetRawButton(cameraButton))
    isBackDown = false;

  if (js1->GetRawButton(cameraButton) && currentCamera == 1 && Robot::isBackDown == false)
  {
    currentCamera = 0;
    isBackDown = true;
  }

  else if (!js1->GetRawButton(cameraButton))
    isBackDown = false;

  SmartDashboard::PutNumber("Current Camera", currentCamera);

  /*if (js1->GetRawButton(cameraButton) && currentCamera == 2 && Robot::isBackDown == false)
  {
    currentCamera = 0;
    isBackDown = true;
  }

  else if (!js1->GetRawButton(cameraButton))
    isBackDown = false;
  */
}

void Robot::StrafeToAlign (std::string direction)
{
  if(js1->GetRawButton(alignMacro))
  {
    if(direction == "correct")
    {
      drive->MecDrive(0, 0, 0, false, false);
    }
    else if (direction == "right")
    {
      drive->MecDrive(.4, 0, 0, true, false);
    }
    else if(direction == "left")
    {
      drive->MecDrive(-0.4, 0, 0, true, false);
    }
  }
  else{
    drive->MecDrive(0, 0, 0, false, false);
  }
}

void Robot::BallPickup(bool in, bool out)
{
  if(in)
    intakeWheels->Set(-.5);
  else if(out)
    intakeWheels->Set(1);
  else 
    intakeWheels->Set(0);
}