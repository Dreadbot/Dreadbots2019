#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>

class Stilts
{
    public:
        Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor, bool prototypeRobot = true);
        void setFrontToHeight(float height);//Height in inches
        void setBackToHeight(float height);//Height in inches
        void driveWheels(float speed);//Speed from -1 to 1
        void setBothToHeight(float height);
        void teleopStilts(bool frontUpButton, bool frontDownButton, bool backUpButton, bool backDownButton, double stiltsDriveAxis, double frontSpeed, double backSpeed);
        void fiveStageHeight(float height);
        float stagedClimb(float height, float slop, float s, int stages);
        double getFrontHeight();
        double getBackHeight();
        double getDrivePosition();
        TalonSRX& m_driveMotor;
        TalonSRX& m_backMotor;
        TalonSRX& m_frontMotor;
        double defaultFrontSpeed = 0.8;
        double defaultBackSpeed = 0.8;
        int currentFront;
        int currentBack;
};