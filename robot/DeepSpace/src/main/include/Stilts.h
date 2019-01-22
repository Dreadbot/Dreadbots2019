#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class Stilts
{
    public:
        Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor);
        void setFrontToHeight(float height);//Height in inches
        void setBackToHeight(float height);//Height in inches
        void driveWheels(float speed);//Speed from -1 to 1
        TalonSRX& m_driveMotor;
        TalonSRX& m_backMotor;
        TalonSRX& m_frontMotor;
};