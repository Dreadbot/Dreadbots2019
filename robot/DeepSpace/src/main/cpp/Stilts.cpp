
#include <Stilts.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
double inchesToTicks = 153184;//We need to find this value
double ticksToInches = 0.000006571;
Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{
    m_frontMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_frontMotor.SetSensorPhase(true);
    m_backMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_backMotor.SetSensorPhase(true);
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_driveMotor.SetSensorPhase(true);
}
void Stilts::setFrontToHeight(float height)//sets the front stilt to height in inches using encoders
{
    m_frontMotor.Set(ControlMode::Position, height*inchesToTicks);
} 

void Stilts::setBackToHeight(float height)//sets the back stilts to height in inches using encoders
{
    m_backMotor.Set(ControlMode::Position, height*inchesToTicks);
}

void Stilts::driveWheels(float speed)// turns the drive stilts at a set speed
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
}
int Stilts::getFrontHeight()//returns the front stilt encoder value in inches
{
    return m_frontMotor.GetSelectedSensorPosition() * ticksToInches;
}
int Stilts::getBackHeight()// returns the back stilt encoder value in inches
{
    return m_backMotor.GetSelectedSensorPosition() * ticksToInches;
}
int Stilts::getDrivePosition()//returns the stilt drive encoder value in inches
{
    return m_driveMotor.GetSelectedSensorPosition() * ticksToInches;
}