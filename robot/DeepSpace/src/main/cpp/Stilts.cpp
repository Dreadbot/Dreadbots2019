
#include <Stilts.h>
#include <ctre/Phoenix.h>
#include <iostream>
double backCoefficientP = 0.2;
double frontCoefficientP = 0.2;
double inchesToTicks = 57444;//153184
double ticksToInches = 0.000017408;
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

    m_frontMotor.Config_kP(0, frontCoefficientP);
    m_frontMotor.Config_kI(0, 1e-4);
    m_frontMotor.Config_kD(0, 1);
    m_frontMotor.Set(ControlMode::Position, 0);
    m_frontMotor.Set(ControlMode::PercentOutput, 0);

    
    m_backMotor.Config_kP(0, backCoefficientP);
    m_backMotor.Config_kI(0, 1e-4);
    m_backMotor.Config_kD(0, 1);
    m_backMotor.Set(ControlMode::Position, 0);
    m_backMotor.Set(ControlMode::PercentOutput, 0);

    
    m_driveMotor.Config_kP(0, backCoefficientP);
    m_driveMotor.Config_kI(0, 1e-4);
    m_driveMotor.Config_kD(0, 1);
    m_driveMotor.Set(ControlMode::Position, 0);
    m_driveMotor.Set(ControlMode::PercentOutput, 0);

    
}
void Stilts::setFrontToHeight(float height)//sets the front stilt to height in inches using encoders
{//Practice Robot-------------------------------------------
/*
    m_frontMotor.Set(ControlMode::Position, -1*height*inchesToTicks);
    std::cout << "Front stilts set to: " << -1*height*inchesToTicks << std::endl;
    //this value flipped to account for the encoder flipped*/
//Comp Robot------------------------------------------------
    m_frontMotor.Set(ControlMode::Position, height*inchesToTicks);
    std::cout << "Front stilts set to: " << height*inchesToTicks << std::endl;
} 
void Stilts::setBackToHeight(float height)//sets the back stilts to height in inches using encoders
{
    m_backMotor.Set(ControlMode::Position, height*inchesToTicks);
    std::cout << "Back stilts set to: " << height*inchesToTicks << std::endl;
}
void Stilts::driveWheels(float speed)// turns the drive stilts at a set speed
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
    std::cout << "Stilt wheels set to: " << speed << "%" << std::endl;
}
void Stilts::ThreeStageHeight(float height)
{
    std::cout << "Three Stage Height started" << std::endl;
    int state = 1;
    
    while(state != 4)
    {
        if(getFrontHeight() >= height * -0.25 && getBackHeight() >= height * 0.25)
            state = 2;
        else if(getFrontHeight() >= height * -0.5 && getBackHeight() >= height * 0.5)
            state = 3;
        else if(getFrontHeight() >= height * -0.95 && getBackHeight() >= height * 0.95)
            state = 4;

        if(state == 1)
        {
            setFrontToHeight(height / 3);
            setBackToHeight(height / 3);
        }
        if(state == 2)
        {
            setFrontToHeight(height * 2/3);
            setBackToHeight(height * 2/3);
        }
        if(state == 3)
        {
            setFrontToHeight(height);
            setBackToHeight(height);
        }

        std::cout << "State: " << state << " Inches: " << getFrontHeight() << ", " << getBackHeight() << " Trigger: " << height * 0.25 << " Target: " << height / 3 << std::endl;
        
    }
    //The difference between the state triggers and what the PID is trying to get to exists to make it less precise.
}
double Stilts::getFrontHeight()//returns the front stilt encoder value in inches
{
    return m_frontMotor.GetSelectedSensorPosition() * ticksToInches;
}
double Stilts::getBackHeight()// returns the back stilt encoder value in inches
{
    return m_backMotor.GetSelectedSensorPosition() * ticksToInches;
}
double Stilts::getDrivePosition()//returns the stilt drive encoder value in inches
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
        m_frontMotor.Set(ControlMode::PercentOutput, 0);
        //m_frontMotor.Set(ControlMode::Position, m_frontMotor.GetSelectedSensorPosition());
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