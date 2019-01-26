#pragma once

#include <Stilts.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{

}
void Stilts::setFrontToHeight(float height)
{

}

void Stilts::setBackToHeight(float height)
{

}

void Stilts::driveWheels(float speed)
{
    
}