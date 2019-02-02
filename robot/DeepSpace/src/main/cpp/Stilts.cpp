#pragma once

#include <Stilts.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
double inchesToTicks = 153184;//We need to find this value
double ticksToInches = 0.000006571;
Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{

}
void Stilts::setFrontToHeight(float height)
{
    m_frontMotor.Set(ControlMode::Position, height*inchesToTicks);
}

void Stilts::setBackToHeight(float height)
{
    m_backMotor.Set(ControlMode::Position, height*inchesToTicks);
}

void Stilts::driveWheels(float speed)
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
}
int Stilts::getFrontHeight()//returns the encoder value in inches
{
    return m_frontMotor.GetSelectedSensorPosition() * ticksToInches;
}
int Stilts::getBackHeight()
{
    return m_backMotor.GetSelectedSensorPosition() * ticksToInches;
}
int Stilts::getDrivePosition()
{
    return m_driveMotor.GetSelectedSensorPosition() * ticksToInches;
}