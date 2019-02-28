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
        //strafeDirection = LEFT;
    }

    drive->StrafeToDistance(strafeDirection, 5);
}

void Robot::AutonHatch(int startPosition, int targetPosition)
{
    double angle = gyro->GetYaw();
    double targetAngle = 90;
    static bool stopped = false;
    double const inchesToRotations = .4134152;
    double distance = sparkDrive->getlFrontRotations()/inchesToRotations;
    double targetDistance = 20;
    double motorDistance = 5;
    //get angle and distance from starting position 
    if(targetPosition == 0)
    {
        targetDistance = 20;
    }
    std::cout << "Auto State: " << autoState << std::endl;
    std::cout << "Distance: " << distance << " Motor Distance:" << motorDistance << std::endl;
    std::cout << "Front Rotations: " << sparkDrive->getlFrontRotations() << std::endl;
    //idle state 0 
    //drive forward x distance state 1 
    if (autoState == 0 )
    {
        motorDistance = distance - targetDistance; //motors driving reverse, should make it go 20 from current
        autoState = 1;
    }
    //stop state 2
    if (autoState == 1 && distance > targetDistance-2)
    {
        autoState = 2;
    }
    //rotate to angle state 3
    if (autoState == 2 && stopped == true)
    {
        autoState = 3;
    }
    //auto align state 4
    if(autoState == 3 && fabs(angle-targetAngle) < 3)
    {
        autoState = 4;
    }
    //drive forward x distance state 5
    //stop state 6

    //code for action 
    if(autoState == 1)
    {
        sparkDrive->pidDrive(targetDistance);
    }

    if(autoState == 2)
    {
        sparkDrive->MecDrive(0,0,0,0,0);
        stopped = true;
    }

    if(autoState == 3)
    {
        sparkDrive->RotateToAngle(0.5, targetAngle, currentAngle);
    }

    if(autoState == 4)
    {
        sparkDrive->MecDrive(0,0,0,0,0);
    }

    if(autoState == 5)
    {
        sparkDrive->pidDrive(targetDistance);
    }
    
}

void Robot::AutonHatch(int position)
{
    if(position > 3)
    {
        std::cout << "invalid position number" <<  std::endl;
    }

    else if(position == 0)
    {
        if(autoState == 1 && sparkDrive->getlFrontRotations() >= 1)
        {
            autoState = 2;
        }
        else if(autoState == 2 && sparkDrive->getlFrontRotations() >= 2)
        {
            autoState = 3;
        }
        else if(autoState == 3)
        {
            autoState = 4;
        }
        else if(autoState == 4)
        {
            autoState == 5;
        }

        if(autoState == 1)
        {
            sparkDrive->pidDrive(3);
        }
        if(autoState == 2)
        {  
            sparkDrive->RotateToAngle(0.5, 90, gyro->GetYaw());
        }
        if(autoState == 3)
        {
            sparkDrive->pidDrive(4);
        }
        if(autoState == 4)
        {
            solenoid->Set(false);
        }
    }
}
void Robot::AutonBall(int position)
{
    
}
int Robot::AutonPositionDecider()
{
    return positionDecider.GetSelected();
}
int Robot::AutonGamePieceDecider()
{
    return gamePieceDecider.GetSelected();
}
void Robot::RunAuton()
{
    if(AutonGamePieceDecider() == 0)
    {
        AutonHatch(AutonPositionDecider());        
    }
    if(AutonGamePieceDecider() == 1)
    {
        AutonBall(AutonPositionDecider());
    }
}