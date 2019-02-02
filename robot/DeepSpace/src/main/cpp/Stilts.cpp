
#include <Stilts.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
float rotationsToInches = 123;
Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{

}
void Stilts::setFrontToHeight(float height)
{
    m_frontMotor.Set(ControlMode::Position, height*rotationsToInches);
}

void Stilts::setBackToHeight(float height)
{
    m_backMotor.Set(ControlMode::Position, height*rotationsToInches);
}

void Stilts::driveWheels(float speed)
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
}