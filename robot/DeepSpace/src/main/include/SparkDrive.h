#pragma once

#include "rev/CANSparkMax.h"

class SparkDrive 
{
    public:
        SparkDrive(rev::CANSparkMax *lFront_in, rev::CANSparkMax *lBack_in, rev::CANSparkMax *rFront_in, rev::CANSparkMax *rBack_in);

        void MecDrive(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton);

        void DriveStraight(double speed, double currentAngle);

        void pidDrive(double inches);

        double getRotations();
    private:
        rev::CANSparkMax *lFront;
        rev::CANSparkMax *lBack;
        rev::CANSparkMax *rFront;
        rev::CANSparkMax *rBack;

        rev::CANEncoder *lFrontEncoder;
        rev::CANEncoder *rFrontEncoder;
        rev::CANEncoder *lBackEncoder;
        rev::CANEncoder*rBackEncoder;

        rev::CANPIDController *lFrontPID;
        rev::CANPIDController *lBackPID;
        rev::CANPIDController *rFrontPID;
        rev::CANPIDController *rBackPID;
        double teleMaxSpeed = 0.5;

        double leftDifference;
        double rightDifference;
		float slop = 3;
};