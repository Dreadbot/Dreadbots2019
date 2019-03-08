#include "Robot.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "DoubleManipulator.h"
#include <Stilts.h>
#include <string.h>

void Robot::TeleopLifterControl()
{

  std::cout << " Lifter: " << lifter->GetEncoderPosition() << std::endl;
  if (!js1->GetRawButton(liftOverrideButton))
  {
    if (js1->GetRawButton(upButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() < 6)
    {
      buttonTimer = 0;
      lifter->IncreaseCurrentLevel();
      //std::cout << "UpButton Pressed" << std::endl;
      //lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
    if (js1->GetRawButton(downButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() > 0)
    {
      buttonTimer = 0;
      lifter->DecreaseCurrentLevel();
      //lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
  }
  else
  {
    if (js1->GetRawButton(upButton))
    {
      lifter->MoveLift(1);
    }
    else if (js1->GetRawButton(downButton))
    {
      lifter->MoveLift(-1);
    }
    else
    {
      lifter->MoveLift(0);
    }
  }
}

void Robot::TeleopManipulatorControl()
 { 
   //std::cout << "Manipulator Encoder Value:" << wrist->GetSelectedSensorPosition() << std::endl;
   //std::cout << "Manipulator Encoder Position:" << manipulator->GetCurrentPosition() << std::endl;
  //std::cout << wrist->GetSelectedSensorPosition() << std::endl;
  //std::cout<<"Button timer: " << (buttonTimer >= BUTTON_TIMEOUT) << std::endl;
  //std::cout<<"Picking up: " << manipulator->CheckPickup() <<std::endl;
  if (!js2->GetRawButton(manipulatorOverrideButton))
  {
    std::cout << "Manipulator Encoder Value:" << wrist->GetSelectedSensorPosition() << std::endl;
    if (js2->GetRawButton(lowerManipulator) && buttonTimer >= BUTTON_TIMEOUT && Robot::manipulator->GetCurrentPosition() < 3)
    {
      manipulator->wrist.ConfigClosedLoopPeakOutput(0, 0.5);
      if(manipulator->GetCurrentPosition() == 2){
        std::cout << "shrugged" << std::endl;
        lifter->Shrug();

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
        manipulator->wrist.ConfigClosedLoopPeakOutput(0, 0.9);
        buttonTimer = 0;
        manipulator->RotateWrist(manipulator->GetCurrentPosition() - 1);
        manipulator->SetBallPickup(false);
        //manipulator->SpinWheels(0);
    }
    if(js2->GetRawButton(ballPickup) && buttonTimer >= BUTTON_TIMEOUT){
      manipulator->SpinWheels(0.6);
    }
    else if(js2->GetRawButton(shootBall) && buttonTimer >= BUTTON_TIMEOUT){
      manipulator->SpinWheels(-1);
    }
    else{
      manipulator->SpinWheels(0);
    }
  }
  else {
    if(js2->GetRawButton(raiseManipulator))
    {
      wrist->Set(ControlMode::PercentOutput, -0.7);
    }
    else if(js2->GetRawButton(lowerManipulator))
    {
      wrist->Set(ControlMode::PercentOutput, 0.5);
    }
    else
    {
      wrist->Set(ControlMode::PercentOutput, 0);
    }
  }
}

//Fully autonomous level 3 climb using ultrasonics and encoders
void Robot::Climb(int level)
{
  float slop = .1;
  //std::cout<< "Climb State: " << climbState;
  //std::cout << " Front Height: " << stilts->getFrontHeight();
  //std::cout << " Back Height: " << stilts->getBackHeight();
    if (climbState != 8 && level == 3)
    {
      if (climbState == 1 && stilts->getFrontHeight() >= LEVEL_3_HEIGHT - slop && stilts->getBackHeight() >= LEVEL_3_HEIGHT - slop)
      {
        climbTimeout = 0;
        climbState = 2; //Drive the stilt wheel
        //std::cout << "Changed to state 2, climb State = " << climbState << std::endl;
      }
      else if (climbState == 2 && ultra->getDistanceLeftFront() <= 5 && ultra->getDistanceLeftFront() >= 1 && ultra->getDistanceRightFront() <= 5 && ultra->getDistanceRightFront() >= 1)
      {
        climbState = 3; //Retract front
      }
      else if (climbState == 3 && stilts->getFrontHeight() <= 0 + slop)
      {
        climbState = 4; //drive the stilt wheel
      }
      else if (climbState == 4 && ultra->getDistanceLeftBack() <= 5 && ultra->getDistanceLeftBack() >= 1 && ultra->getDistanceRightBack() <= 5 && ultra->getDistanceRightBack() >= 1 && climbTimeout >= 100)
      {
        climbState = 5; //retract back wheel
      }
      else if (climbState == 5 && stilts->getBackHeight() <= 0 + slop)
      {
        climbState = 6; //drives to alliance wall
      }
      else if (climbState == 6 && climbTimeout >= 20)
      {
        climbState = 7; //stops movement
        climbTimeout = 0;
      }
      else if (climbState == 7 && climbTimeout >= 10)
      {
        climbState = 8;
        climbTimeout = 0;
      }

      if (climbState == 1)
      {
        stagedClimbState = stilts->stagedClimb(LEVEL_3_HEIGHT, .1, stagedClimbState, 10);
      }
      if (climbState == 2)
      {
        stilts->driveWheels(-driveStiltsSpeed);
      }
      if (climbState == 3)
      {
        stilts->driveWheels(0.0);
        stilts->setFrontToHeight(0);
      }
      if (climbState == 4)
      {
        stilts->driveWheels(-driveStiltsSpeed);
        climbTimeout++;
      }
      if (climbState == 5)
      {
        stilts->driveWheels(0);
        stilts->setBackToHeight(0);
        climbTimeout = 0;
      }
      if (climbState == 6)
      {
        sparkDrive->MecDrive(0, .25, 0, false, false); //doesn't drive forward for some reason, even though it's in state 6
        climbTimeout++;
      }
      if (climbState == 7)
      {
        sparkDrive->MecDrive(0, -.15, 0, false, false);
        climbTimeout++;
      }
      if(climbState == 8)
      {
        sparkDrive->MecDrive(0, 0, 0, false, false);
      }
    }
    else if(climbState != 8 && level == 2)
    {
      if (climbState == 1 && stilts->getFrontHeight() >= LEVEL_2_HEIGHT - slop && stilts->getBackHeight() >= LEVEL_2_HEIGHT - slop)
      {
        climbTimeout = 0;
        climbState = 2; //Drive the stilt wheel
        //std::cout << "Changed to state 2, climb State = " << climbState << std::endl;
      }
      else if (climbState == 2 && ultra->getDistanceLeftFront() <= 5 && ultra->getDistanceLeftFront() >= 1 && ultra->getDistanceRightFront() <= 5 && ultra->getDistanceRightFront() >= 1)
      {
        climbState = 3; //Retract front
      }
      else if (climbState == 3 && stilts->getFrontHeight() <= 0 + slop)
      {
        climbState = 4; //drive the stilt wheel
      }
      else if (climbState == 4 && ultra->getDistanceLeftBack() <= 5 && ultra->getDistanceLeftBack() >= 1 && ultra->getDistanceRightBack() <= 5 && ultra->getDistanceRightBack() >= 1 && climbTimeout >= 100)
      {
        climbState = 5; //retract back wheel
      }
      else if (climbState == 5 && stilts->getBackHeight() <= 0 + slop)
      {
        climbState = 6; //drives to alliance wall
      }
      else if (climbState == 6 && climbTimeout >= 20)
      {
        climbState = 7; //stops movement
        climbTimeout = 0;
      }
      else if (climbState == 7 && climbTimeout >= 10)
      {
        climbState = 8;
        climbTimeout = 0;
      }

      if (climbState == 1)
      {
        stagedClimbState = stilts->stagedClimb(LEVEL_2_HEIGHT, .1, stagedClimbState, 5);
      }
      if (climbState == 2)
      {
        stilts->driveWheels(-driveStiltsSpeed);
      }
      if (climbState == 3)
      {
        stilts->driveWheels(0.0);
        stilts->setFrontToHeight(0);
      }
      if (climbState == 4)
      {
        stilts->driveWheels(-driveStiltsSpeed);
        climbTimeout++;
      }
      if (climbState == 5)
      {
        stilts->driveWheels(0);
        stilts->setBackToHeight(0);
        sparkDrive->MecDrive(0, .25, 0, false, false); 
        climbTimeout = 0;
      }
      if (climbState == 6)
      {
        climbTimeout++;
      }
      if (climbState == 7)
      {
        sparkDrive->MecDrive(0, -.15, 0, false, false);
        climbTimeout++;
      }
      if(climbState == 8)
      {
        sparkDrive->MecDrive(0, 0, 0, false, false);
      }
    }
}
/*void Robot::ElectricSolenoidTest(frc::Solenoid *solenoid)
{
  //toggle function for button "X" to fire solenoid
  if (js1->GetRawButton(solButton) && isSolOut == false && Robot::isXDown == false)
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
    
  if(js2->GetRawButton(engageSol))
    solenoid->Set(true);
  
  if(js2->GetRawButton(disengageSol))
    solenoid->Set(false);

}
*/
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
      sparkDrive->MecDrive(0, 0, 0, false, false);
    }
    else if (direction == "right")
    {
      //std::cout<<"haha"<<std::endl;
      sparkDrive->MecDrive(.2, 0, 0, true, false);
    }
    else if(direction == "left")
    {
      sparkDrive->MecDrive(-0.4, 0, 0, true, false);
    }
  }
  else{
    sparkDrive->MecDrive(0, 0, 0, false, false);
  }
}

void Robot::BallPickup(bool in, bool out)
{
  if(in)
    intakeWheels->Set(.5);
  else if(out)
    intakeWheels->Set(-1);
  else 
    intakeWheels->Set(0);
}