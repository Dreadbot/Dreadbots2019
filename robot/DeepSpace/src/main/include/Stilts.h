#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>

class Stilts
{
    public:
        Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor);
        void setFrontToHeight(float height);//Height in inches
        void setBackToHeight(float height);//Height in inches
        void driveWheels(float speed);//Speed from -1 to 1
        void teleopStilts(bool frontUpButton, bool frontDownButton, bool backUpButton, bool backDownButton, double stiltsDriveAxis, double frontSpeed, double backSpeed);
        int getFrontHeight();
        int getBackHeight();
        int getDrivePosition();
        TalonSRX& m_driveMotor;
        TalonSRX& m_backMotor;
        TalonSRX& m_frontMotor;
        double defaultFrontSpeed = 0.8;
        double defaultBackSpeed = 0.4;
};