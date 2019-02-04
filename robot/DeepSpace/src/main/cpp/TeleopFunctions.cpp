#include "Robot.h"
#include "Lifter.h"
#include "frc/WPILib.h"
#include "DoubleManipulator.h"

void Robot::TeleopLifterControl()
{
  std::cout << lifter->GetEncoderPosition() << std::endl;
  if(!js2->GetRawButton(manualOverrideButton)){
    if(js2->GetRawButton(upButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() < 6){
      buttonTimer = 0;
      lifter->IncreaseCurrentLevel();
      std::cout << "UpButton Pressed" << std::endl;
      lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
    if(js2->GetRawButton(downButton) && buttonTimer >= BUTTON_TIMEOUT && lifter->GetCurrentLevel() > 0){
      buttonTimer = 0;
      lifter->DecreaseCurrentLevel();
      lifter->SetLift(lifter->GetCurrentLevel());
      frc::SmartDashboard::PutNumber("Wanted level", lifter->GetCurrentLevel()); //needs to be changed to Shuffleboard
    }
    buttonTimer++;
  }
  else
  {
    if(js2->GetRawButton(upButton))
    {
      lifter->MoveLift(0.5);
    }
    else if(js2->GetRawButton(downButton))
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
{
  if (!js2->GetRawButton(manualOverrideButton)){
    if(js2->GetRawButton(ballPickup) && buttonTimer >= BUTTON_TIMEOUT && manipulator->CheckPickup()){
      std::cout << "button pressed" << std::endl;
      buttonTimer = 0;
      manipulator->RotateWrist(1);
      manipulator->SpinWheels(0.5);
      manipulator->SetPickup(true);
    }
    if(js2->GetRawButton(ballPickup) && buttonTimer >= BUTTON_TIMEOUT && !manipulator->CheckPickup()){
      buttonTimer = 0;
      manipulator->RotateWrist(2);
      manipulator->SetPickup(false);
      manipulator->SpinWheels(0);
    }
  }
}

void Robot::ElectricSolenoidTest(frc::Solenoid *solenoid)
{
  //toggle function for button "X" to fire solenoid
  	if(js1->GetRawButton(solButton) && isSolOut == false && isXDown == false) 
		{
			solenoid->Set(true);
			isSolOut = true;
			isXDown = true;
		}
		else if(!js1->GetRawButton(solButton) && isSolOut == true)
			isXDown = false;

		else if(js1->GetRawButton(solButton) && isSolOut == true && isXDown == false)
		{
			solenoid->Set(false);
			isSolOut = false;
			isXDown = true;
		}
		else if(!js1->GetRawButton(solButton) && isSolOut == false)
			isXDown = false;

}