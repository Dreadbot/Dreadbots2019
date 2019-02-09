#include <Drive.h>
#include <AHRS.h>

Drive::Drive(WPI_TalonSRX *lFront_in, WPI_TalonSRX *lBack_in, WPI_TalonSRX *rFront_in, WPI_TalonSRX *rBack_in)
{
    lFront = lFront_in;
    lBack = lBack_in;
    rFront = rFront_in;
    rBack = rBack_in;
}
//Mec drive with ramp up or down speed
void Drive::MecDrive2(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton) //homemade mecanum drive!
	{
		double noMove = 0.2; //Dead area of the axes
		double maxSpeed = .5; //normal (not turbo)
		double rampUpFactor = 1.2; //how fast to increment speed
		double currentSpeed = rFront->GetMotorOutputPercent(); //how fast are we going right now

		if (fabs(xAxis) < noMove)
		{	
			xAxis = 0.0;
		}
		if (fabs(yAxis) < noMove)
		{ 
			yAxis = 0.0;
		}
		if (fabs(rot) < noMove)
		{
			rot = 0.0;
		}	
		if (turboButton)
		{	
			maxSpeed = 1;
		}
		else if (slowButton)
		{
			maxSpeed = .3;
		}
		else
		{	
			maxSpeed = .5;
		}

		//Set our target speed. If the current speed is 
		//less than max speed, increment current speed by ramp
		if(currentSpeed < maxSpeed)
		{
			targetSpeed = currentSpeed * rampUpFactor
		}


		double lFrontSpeed = -yAxis - xAxis - rot;
		double rFrontSpeed = +yAxis - xAxis - rot;
		double rBackSpeed = +yAxis + xAxis - rot;
		double lBackSpeed = -yAxis + xAxis - rot;

		if (fabs(lFrontSpeed) > 1)
		{
			lFrontSpeed = fabs(lFrontSpeed) / lFrontSpeed;
		}	
		if (fabs(lBackSpeed) > 1)
		{
			lBackSpeed = fabs(lBackSpeed) / lBackSpeed;
		}	
		if (fabs(rFrontSpeed) > 1)
		{
			rFrontSpeed = fabs(rFrontSpeed) / rFrontSpeed;
		}	
		if (fabs(rBackSpeed) > 1)
		{
			rBackSpeed = fabs(rBackSpeed) / rBackSpeed;
		}	
		
		lFront -> Set(ControlMode::PercentOutput, lFrontSpeed*targetSpeed);
		lBack -> Set(ControlMode::PercentOutput, lBackSpeed*targetSpeed);
		rFront -> Set(ControlMode::PercentOutput, rFrontSpeed*targetSpeed);
		rBack -> Set(ControlMode::PercentOutput, rBackSpeed*targetSpeed);
		
	}

	void Drive::DriveStraight(double speed, double currentAngle)
	{
		leftDifference = currentAngle*.05;
		rightDifference = currentAngle*.05;

		if(currentAngle < 0 - slop)
		{
			lFront -> Set(ControlMode :: PercentOutput, -speed);
			rFront -> Set(ControlMode :: PercentOutput, speed+leftDifference);
			lBack -> Set(ControlMode :: PercentOutput, -speed);
			rBack -> Set(ControlMode :: PercentOutput, speed+leftDifference);
		}

		else if(currentAngle > 0 + slop)
		{
			lFront -> Set(ControlMode :: PercentOutput, -speed+rightDifference);
			rFront -> Set(ControlMode :: PercentOutput, speed);
			lBack -> Set(ControlMode :: PercentOutput, -speed+rightDifference);
			rBack -> Set(ControlMode :: PercentOutput, speed);
		}

		else
		{
			rFront -> Set(ControlMode :: PercentOutput, speed);
			lFront -> Set(ControlMode :: PercentOutput, -speed);
			lBack -> Set(ControlMode :: PercentOutput, -speed);
			rBack -> Set(ControlMode :: PercentOutput, speed);
		}
	} 
void Drive::MecDrive(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton) //homemade mecanum drive!
	{
		double noMove = 0.2; //Dead area of the axes
		double maxSpeed = .5; //normal speed (not turbo)

		if (fabs(xAxis) < noMove)
			xAxis = 0.0;

		if (fabs(yAxis) < noMove)
			yAxis = 0.0;

		if (fabs(rot) < noMove)
			rot = 0.0;

		if (turboButton)
			maxSpeed = 1;

		else if (slowButton)
			maxSpeed = .3;

		else
			maxSpeed = .5;

		double lFrontSpeed = -yAxis - xAxis - rot;
		double rFrontSpeed = +yAxis - xAxis - rot;
		double rBackSpeed = +yAxis + xAxis - rot;
		double lBackSpeed = -yAxis + xAxis - rot;

		if (fabs(lFrontSpeed) > 1)
			lFrontSpeed = fabs(lFrontSpeed) / lFrontSpeed;

		if (fabs(lBackSpeed) > 1)
			lBackSpeed = fabs(lBackSpeed) / lBackSpeed;

		if (fabs(rFrontSpeed) > 1)
			rFrontSpeed = fabs(rFrontSpeed) / rFrontSpeed;

		if (fabs(rBackSpeed) > 1)
			rBackSpeed = fabs(rBackSpeed) / rBackSpeed;

		lFront -> Set(ControlMode::PercentOutput, lFrontSpeed*maxSpeed);
		lBack -> Set(ControlMode::PercentOutput, lBackSpeed*maxSpeed);
		rFront -> Set(ControlMode::PercentOutput, rFrontSpeed*maxSpeed);
		rBack -> Set(ControlMode::PercentOutput, rBackSpeed*maxSpeed);
	}

	void Drive::DriveStraight(double speed, double currentAngle)
	{
		leftDifference = currentAngle*.05;
		rightDifference = currentAngle*.05;

		if(currentAngle < 0 - slop)
		{
			lFront -> Set(ControlMode :: PercentOutput, -speed);
			rFront -> Set(ControlMode :: PercentOutput, speed+leftDifference);
			lBack -> Set(ControlMode :: PercentOutput, -speed);
			rBack -> Set(ControlMode :: PercentOutput, speed+leftDifference);
		}

		else if(currentAngle > 0 + slop)
		{
			lFront -> Set(ControlMode :: PercentOutput, -speed+rightDifference);
			rFront -> Set(ControlMode :: PercentOutput, speed);
			lBack -> Set(ControlMode :: PercentOutput, -speed+rightDifference);
			rBack -> Set(ControlMode :: PercentOutput, speed);
		}

		else
		{
			rFront -> Set(ControlMode :: PercentOutput, speed);
			lFront -> Set(ControlMode :: PercentOutput, -speed);
			lBack -> Set(ControlMode :: PercentOutput, -speed);
			rBack -> Set(ControlMode :: PercentOutput, speed);
		}
	} 
	 void Drive::RotateToAngle(double speed, double targetAngle, double currentAngle){
		double rotSpeed = speed;
		double angleSlop = 3;
		double remainingAngle = targetAngle - currentAngle;
		//targetAngle / fabs(currentAngle);

				if (fabs(remainingAngle) > angleSlop)
				{
					if (remainingAngle > 20){
						rotSpeed = 1;
						rFront -> Set(ControlMode :: PercentOutput, rotSpeed);
						lFront -> Set(ControlMode :: PercentOutput, -rotSpeed);
						lBack -> Set(ControlMode :: PercentOutput, -rotSpeed);
						rBack -> Set(ControlMode :: PercentOutput, rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					else if (remainingAngle <= 20 && remainingAngle > angleSlop){
						rotSpeed = 0.5;
						rFront -> Set(ControlMode :: PercentOutput, rotSpeed);
						lFront -> Set(ControlMode :: PercentOutput, -rotSpeed);
						lBack -> Set(ControlMode :: PercentOutput, -rotSpeed);
						rBack -> Set(ControlMode :: PercentOutput, rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					else if (remainingAngle < -20){
						rotSpeed = 1;
						rFront -> Set(ControlMode :: PercentOutput, -rotSpeed);
						lFront -> Set(ControlMode :: PercentOutput, rotSpeed);
						lBack -> Set(ControlMode :: PercentOutput, rotSpeed);
						rBack -> Set(ControlMode :: PercentOutput, -rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					} 
					else if (remainingAngle >= -20 && remainingAngle < -angleSlop){
						rotSpeed = 0.5;
						rFront -> Set(ControlMode :: PercentOutput, -rotSpeed);
						lFront -> Set(ControlMode :: PercentOutput, rotSpeed);
						lBack -> Set(ControlMode :: PercentOutput, rotSpeed);
						rBack -> Set(ControlMode :: PercentOutput, -rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					
				}
				else {
					rFront -> Set(ControlMode :: PercentOutput, 0);
					lFront -> Set(ControlMode :: PercentOutput, 0);
					lBack -> Set(ControlMode :: PercentOutput, 0);
					rBack -> Set(ControlMode :: PercentOutput, 0);
				}
				//else if goToTarget
				// add different function where we travel to the vison target
	 }
void Drive::StrafeToDistance(StrafeDirection direction, int strafeDistance)
{
	switch(direction)
	{
		case LEFT:
			lFront->Set(ControlMode::Position, -strafeDistance);
			rFront->Set(ControlMode::Position, strafeDistance);
			lBack->Set(ControlMode::Position, strafeDistance);
			rBack->Set(ControlMode::Position, -strafeDistance);
		case RIGHT:
			lFront->Set(ControlMode::Position, strafeDistance);
			rFront->Set(ControlMode::Position, -strafeDistance);
			lBack->Set(ControlMode::Position, -strafeDistance);
			rBack->Set(ControlMode::Position, strafeDistance);
	}
}
void Drive::RampUpSpeed(double currentSpeed, double targetSpeed)
{
	if(currentSpeed = 0)
	{
		currentSpeed = 0.3;//how do we know if we want to go forwards or backwords
		if(currentSpeed < targetSpeed)
		{
		currentSpeed = currentSpeed * 1.2;
		}
		else if (currentSpeed >= targetSpeed)
		{
		currentSpeed = targetSpeed;
		}
	}
	else
	{
		if(currentSpeed < targetSpeed)
		{
		currentSpeed = currentSpeed * 1.2;
		}
		else if (currentSpeed >= targetSpeed)
		{
		currentSpeed = targetSpeed;
		}
	}
	
}

const float driveGearRatio = 5;
const float driveGearDiameter = 3.5;
const double pi = 3.1415;
const  int ticksPerRotation = 4096;
const float inchesPerRotation = 1; //dummy value, pls change later (NOTE: THIS IS SPECIFIC TO THE DRIVE GEARS)

int strafeDistance(float rotations) //finding rotations to inches - comment once THIS mystery has been solved
{
	int driveTicks = (int) (rotations * ticksPerRotation * driveGearRatio);
	return driveTicks;
}

// int strafeDistance(float inches) //actual strafeDistance - uncomment when able to use
// {
// 	int driveTicks = (int) ((inches / inchesPerRotation) * ticksPerRotation * driveGearRatio);
// 	return driveTicks;
// }