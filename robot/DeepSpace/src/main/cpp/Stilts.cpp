
#include <Stilts.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <frc/Joystick.h>
double backCoefficientP = 0.2;
double frontCoefficientP = 0.4;
double inchesToTicks = 57444;//153184
double ticksToInches = 0.000017408;
Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor, bool prototypeRobot) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{
    m_frontMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    m_frontMotor.SetSensorPhase(false);
    m_backMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    //Prototype bot is true, competition bot is false
    if(prototypeRobot)
    {
        m_backMotor.SetSensorPhase(true);
    }
    else
    {
        m_backMotor.SetSensorPhase(false);
    }
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
    currentFront = 0;
    currentBack = 0;
    
}
void Stilts::setFrontToHeight(float height)//sets the front stilt to height in inches using encoders
{
    currentFront = m_frontMotor.GetSelectedSensorPosition();
    m_frontMotor.Set(ControlMode::Position, -1*height*inchesToTicks);
    //std::cout << "Front stilts set to: " << -1*height*inchesToTicks << std::endl;
} 
void Stilts::setBackToHeight(float height)//sets the back stilts to height in inches using encoders
{
    currentBack = m_backMotor.GetSelectedSensorPosition();
    m_backMotor.Set(ControlMode::Position, height*inchesToTicks);
    //std::cout << "Back stilts set to: " << height*inchesToTicks << std::endl;
}
void Stilts::driveWheels(float speed)// turns the drive stilts at a set speed
{
    m_driveMotor.Set(ControlMode::PercentOutput, speed);
    //std::cout << "Stilt wheels set to: " << speed << "%" << std::endl;
}
void Stilts::setBothToHeight(float height)
{
    setFrontToHeight(height);
    setBackToHeight(height);
}
void Stilts::fiveStageHeight(float height)//Prototype for a staged stilts, used for testing, replaced with stagedLift()
{
    //std::cout << "Five Stage Height started" << std::endl;
    int state = 1;
    
    while(state != 6)
    {
        if(state == 1 && getFrontHeight() >= height * 0.15 && getBackHeight() >= height * 0.15)
            state = 2;
        else if(state == 2 && getFrontHeight() >= height * 0.35 && getBackHeight() >= height * 0.35)
            state = 3;
        else if(state == 3 && getFrontHeight() >= height * 0.55 && getBackHeight() >= height * 0.55)
            state = 4;
        else if(state == 4 && getFrontHeight() >= height * 0.75 && getBackHeight() >= height * 0.75)
            state = 5;
        else if(state == 5 && getFrontHeight() >= height * 0.95 && getBackHeight() >= height * 0.95)
            state == 6;

        if(state == 1)
        {
            setBothToHeight(height / 5);
        }
        if(state == 2)
        {
            setBothToHeight(height * 2 / 5);
        }
        if(state == 3)
        {
            setBothToHeight(height * 3 / 5);
        }
        if(state == 4)
        {
            setBothToHeight(height * 4 / 5);
        }
        if(state == 5)
        {
            setBothToHeight(height);
        }
        //std::cout << "State: " << state << " Inches: " << getFrontHeight() << ", " << getBackHeight() << std::endl;
        
    }
    //The difference between the state triggers and what the PID is trying to get to exists to make it less precise.
}
float Stilts::stagedClimb(float height, float slop, float s, int stages = 10)//Lifts the robot to a height in stages, waiting for each leg to reach a height to move to the next stage
{
    //std::cout << s << std::endl;
    if(s != stages + 1) 
    {
        setBothToHeight(height * s / stages);
        //std::cout << "I: " << i << " State: " << state << " Front Stilts: " << getFrontHeight() << " Back Stilts: " << getBackHeight()<< " Trying for: " << (((height * state) / stages) - slop) << std::endl;
        if((getFrontHeight() >= (((height * s) / stages) - slop)) && (getBackHeight() >= ((height * s) / stages) - slop))
        {
            //std::cout << "Changed state from " << s << std::endl;
            s = s + 1;         
        } 

        return s;
    }
}
double Stilts::getFrontHeight()//returns the front stilt encoder value in inches
{
    return m_frontMotor.GetSelectedSensorPosition() * -1*ticksToInches;
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
        currentFront = m_frontMotor.GetSelectedSensorPosition();
        
    }
    else if(frontDown)
    {
        m_frontMotor.Set(ControlMode::PercentOutput, -frontSpeed);
        currentFront = m_frontMotor.GetSelectedSensorPosition();
    }
    else
    {
        //m_frontMotor.Set(ControlMode::PercentOutput, 0);
        m_frontMotor.Set(ControlMode::Position, currentFront);
    }
    if(backUp)
    {
        m_backMotor.Set(ControlMode::PercentOutput, backSpeed);
        currentBack = m_backMotor.GetSelectedSensorPosition();
    }
    else if(backDown)
    {
        m_backMotor.Set(ControlMode::PercentOutput, -backSpeed);
        currentBack = m_backMotor.GetSelectedSensorPosition();
    }
    else
    {
       // m_backMotor.Set(ControlMode::PercentOutput, 0);
        m_backMotor.Set(ControlMode::Position, currentBack);
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
// I'm leaving this older version of stagedLift() here for debugging purposes - Kyle
/*
        if(state == 1 && getFrontHeight() >= (height / 10) - slop && getBackHeight() >= (height / 10) - slop)
        {
            state = 2;
        }
        else if(state == 2 && getFrontHeight() >= (height * 2 / 10) - slop && getBackHeight() >= (height * 2 / 10) - slop)
        {
            state = 3;
        }
        else if(state == 3 && getFrontHeight() >= (height * 3 / 10) - slop  && getBackHeight() >= (height * 3 / 10) - slop)
        {
            state == 4;
        }
        else if(state == 4 && getFrontHeight() >= (height * 4 / 10) - slop && getBackHeight() >= (height * 4 / 10) - slop)
        {
            state == 5;
        }
        else if(state == 5 && getFrontHeight() >= (height * 5 / 10) - slop && getBackHeight() >= (height * 5 / 10) - slop)
        {
            state == 6;
        }
        else if(state == 6 && getFrontHeight() >= (height * 6 / 10) - slop && getBackHeight() >= (height * 6 / 10) - slop)
        {e
            state == 7;
        }
        else if(state == 7 && getFrontHeight() >= (height * 7 / 10) - slop && getBackHeight() >= (height * 7 / 10) - slop)
        {
            state == 8;
        }
        else if(state == 8 && getFrontHeight() >= (height * 8 / 10) - slop && getBackHeight() >= (height * 8 / 10) - slop)
        {
            state == 9;
        }
        else if(state == 9 && getFrontHeight() >= (height * 9 / 10) - slop && getBackHeight() >= (height * 9 / 10) - slop)
        {
            state == 10;
        }
        else if(state == 10 && getFrontHeight() >= height - slop && getBackHeight() >= height - slop)
        {
            state == 11; 
        }*/