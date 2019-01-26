#pragma once

#include <ctre/Phoenix.h>

class Drive 
{
    public:
        Drive(WPI_TalonSRX *lFront_in, WPI_TalonSRX *lBack_in, WPI_TalonSRX *rFront_in, WPI_TalonSRX *rBack_in);

        void MecDrive(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton);

        void DriveStraight(double speed, double currentAngle);

    private:
        WPI_TalonSRX *lFront;
        WPI_TalonSRX *lBack;
        WPI_TalonSRX *rFront;
        WPI_TalonSRX *rBack;

        double teleMaxSpeed = 0.5;

        double leftDifference;
        double rightDifference;
		float slop = 3;
};
