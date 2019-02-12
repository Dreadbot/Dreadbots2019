#include "Robot.h"
#include "frc/WPILib.h"
#include "frc/shuffleboard/Shuffleboard.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::AutoAlign()
{
    x1 = SmartDashboard::GetNumber("x1", 0);
    y1 = SmartDashboard::GetNumber("y1", 0);
    x2 = SmartDashboard::GetNumber("x2", 0);
    y2 = SmartDashboard::GetNumber("y2", 0);
    cameraAngle = SmartDashboard::GetNumber("angle", 0);
    cameraLength = SmartDashboard::GetNumber("length", 0);

    drive->RotateToAngle(.2, 90, cameraAngle);

    if(x1 < 310)
    {
        //strafeDirection = RIGHT;
    }

    if(x1 > 330)
    {

    }

    drive->StrafeToDistance(strafeDirection, 5);
}