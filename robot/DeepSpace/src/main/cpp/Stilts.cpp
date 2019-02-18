
#include <Stilts.h>
#include <ctre/Phoenix.h>
#include <iostream>
double coefficientP = 0.3;
double inchesToTicks = 57444;//153184
double ticksToInches = 0.000006571;
Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{
    m_frontMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_frontMotor.SetSensorPhase(false);
    m_backMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_backMotor.SetSensorPhase(true);
    m_driveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_driveMotor.SetSensorPhase(true);

    m_frontMotor.SetSelectedSensorPosition(0);
    m_backMotor.SetSelectedSensorPosition(0);
    m_driveMotor.SetSelectedSensorPosition(0);

    m_frontMotor.ConfigNominalOutputForward(0,0);
    m_frontMotor.ConfigNominalOutputReverse(0,0);
    m_frontMotor.ConfigPeakOutputForward(1,0);
    m_frontMotor.ConfigPeakOutputReverse(-1,0);

    m_backMotor.ConfigNominalOutputForward(0,0);
    m_backMotor.ConfigNominalOutputReverse(0,0);
    m_backMotor.ConfigPeakOutputForward(1,0);
    m_backMotor.ConfigPeakOutputReverse(-1,0);

    m_driveMotor.ConfigNominalOutputForward(0,0);
    m_driveMotor.ConfigNominalOutputReverse(0,0);
    m_driveMotor.ConfigPeakOutputForward(1,0);
    m_driveMotor.ConfigPeakOutputReverse(-1,0);

    m_frontMotor.Config_kP(0, coefficientP);
    m_frontMotor.Config_kI(0, 1e-4);
    m_frontMotor.Config_kD(0, 1);
    m_frontMotor.Set(ControlMode::Position, 0);
    m_frontMotor.Set(ControlMode::PercentOutput, 0);

    
    m_backMotor.Config_kP(0, coefficientP);
    m_backMotor.Config_kI(0, 1e-4);
    m_backMotor.Config_kD(0, 1);
    m_backMotor.Set(ControlMode::Position, 0);
    m_backMotor.Set(ControlMode::PercentOutput, 0);

    
    m_driveMotor.Config_kP(0, coefficientP);
    m_driveMotor.Config_kI(0, 1e-4);
    m_driveMotor.Config_kD(0, 1);
    m_driveMotor.Set(ControlMode::Position, 0);
    m_driveMotor.Set(ControlMode::PercentOutput, 0);

    
}
void Stilts::setFrontToHeight(float height)//sets the front stilt to height in inches using encoders
{
    m_frontMotor.Set(ControlMode::Position, -1*height*inchesToTicks);
    std::cout << "Front stilts set to: " << height*inchesToTicks << " inches" << std::endl;
    //this value flipped to account for the encoder flipped
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
void Stilts::teleopStilts(bool frontUp, bool frontDown, bool backUp, bool backDown, double stiltsDriveAxis, double frontSpeed, double backSpeed)
//Teleoperated stilts control, buttons for raising and lowering the stilts at a given speed, as well as driving the wheel
{
    std::cout<<"manual stilts"<<std::endl;
    std::cout<< "front up:" << frontUp << std::endl;
    if(frontUp)
    {
        std::cout << "Speed:" << frontSpeed << ", " << backSpeed << std::endl;
        m_frontMotor.Set(ControlMode::PercentOutput, frontSpeed);
    }
    else if(frontDown)
    {
        m_frontMotor.Set(ControlMode::PercentOutput, -frontSpeed);
    }
    else
    {
        m_frontMotor.Set(ControlMode::Position, m_frontMotor.GetSelectedSensorPosition());
    }
    if(backUp)
    {
        m_backMotor.Set(ControlMode::PercentOutput, backSpeed);
    }
    else if(backDown)
    {
        m_backMotor.Set(ControlMode::PercentOutput, -backSpeed);
    }
    else
    {
        m_backMotor.Set(ControlMode::Position, m_backMotor.GetSelectedSensorPosition());
    }
    if(stiltsDriveAxis >= 0.1 || stiltsDriveAxis <= -0.1)
    {
        m_driveMotor.Set(ControlMode::PercentOutput, stiltsDriveAxis * 0.5);
    }
    else
    {
        m_driveMotor.Set(ControlMode::PercentOutput, 0);
    }
}