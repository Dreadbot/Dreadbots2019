#pragma once

#include <ctre/Phoenix.h>

class Drive 
{
    public:
        Drive(WPI_TalonSRX *lFront_in, WPI_TalonSRX *lBack_in, WPI_TalonSRX *rFront_in, WPI_TalonSRX *rBack_in);

        void MecDrive2(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton);

        void MecDrive(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton);

        void DriveStraight(double speed, double currentAngle);
       
        void RotateToAngle(double speed, double targetAngle, double currentAngle);

        void Strafe(std::string side);
        void StrafeStraight(std::string side);

        enum StrafeDirection{LEFT, RIGHT};
        void StrafeToDistance(StrafeDirection direction, int strafeDistance);

        int CalculateDistance(float inches);

        void RampUpSpeed(double currentSpeed, double targetSpeed);
    private:
        WPI_TalonSRX *lFront;
        WPI_TalonSRX *lBack;
        WPI_TalonSRX *rFront;
        WPI_TalonSRX *rBack;

        //AHRS *gyro;

        double teleMaxSpeed = 0.5;

        double leftDifference;
        double rightDifference;
		float slop = 3;
};
