#include "Robot.h"
#include "Lifter.h"
#include "frc/WPILib.h"

void Robot::TeleopLifterControl(){
std::cout << lifter->GetLiftPosition() << std::endl;
  if(!js1->GetRawButton(manualOverrideButton)){
    if(js1->GetRawButton(upButton) && buttonTimer >= 75 && currentLevel < 6){
      buttonTimer = 0;
      currentLevel++;
      std::cout << "UpButton Pressed" << std::endl;
      lifter->SetLift(currentLevel);
    }
    if(js1->GetRawButton(downButton) && buttonTimer >= 75 && currentLevel > 0){
      buttonTimer = 0;
      currentLevel--;
      lifter->SetLift(currentLevel);
    }
    buttonTimer++;
  }
  else{
    if(js1->GetRawButton(upButton)){
      lifter->MoveLift(0.5);
    }
    else if(js1->GetRawButton(downButton)){
      lifter->MoveLift(-0.5);
    }
    else{
      lifter->MoveLift(0);
    }
  }
}