#include "Robot.h"
#include "Lifter.h"
#include "frc/WPILib.h"

void Robot::TeleopLifterControl()
{
  std::cout << lifter->GetLiftPosition() << std::endl;
  if(!js2->GetRawButton(manualOverrideButton)){
    if(js2->GetRawButton(upButton) && buttonTimer >= 75 && currentLevel < 6){
      buttonTimer = 0;
      currentLevel++;
      std::cout << "UpButton Pressed" << std::endl;
      lifter->SetLift(currentLevel);
      frc::SmartDashboard::PutNumber("Wanted level", currentLevel);
    }
    if(js2->GetRawButton(downButton) && buttonTimer >= 75 && currentLevel > 0){
      buttonTimer = 0;
      currentLevel--;
      lifter->SetLift(currentLevel);
      frc::SmartDashboard::PutNumber("Wanted level", currentLevel);
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