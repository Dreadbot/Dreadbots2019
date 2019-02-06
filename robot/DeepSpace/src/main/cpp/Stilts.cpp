
#include <Stilts.h>
#include <ctre/Phoenix.h>
#include <iostream>

double inchesToTicks = 153184;//We need to find this value
double ticksToInches = 0.000006571;
double defaultStiltsSpeed = 0.2;
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
    std::cout << "Front stilts set to: " << height*inchesToTicks << " inches" << std::endl;
} 

void Stilts::setBackToHeight(float height)//sets the back stilts to height in inches using encoders
{
    m_backMotor.Set(ControlMode::Position, height*inchesToTicks);
    std::cout << "Back stilts set to: " << height*inchesToTicks << " inches" << std::endl;
}

void Stilts::driveWheels(float speed)// turns the drive stilts at a set speed
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
    std::cout << "Stilt wheels set to: " << speed << "%" << std::endl;
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
void Stilts::teleopStilts(bool upButton, bool downButton, double speed)//Teleoperated stilts control, button for raising and lowering the stilts at a given speed
{
    if(upButton)
    {
        m_frontMotor.Set(ControlMode::PercentOutput, speed);
        m_backMotor.Set(ControlMode::PercentOutput, speed);
    }
    else if(downButton)
    {
        m_frontMotor.Set(ControlMode::PercentOutput, -speed);
        m_backMotor.Set(ControlMode::PercentOutput, -speed);
    }
    else
    {
        m_frontMotor.Set(ControlMode::PercentOutput, 0);
        m_backMotor.Set(ControlMode::PercentOutput, 0);
    }
}