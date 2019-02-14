#include "SparkDrive.h"
#include <iostream>
double const inchesToRotations = .4134152;

SparkDrive::SparkDrive(rev::CANSparkMax *lFront_in, rev::CANSparkMax *lBack_in, rev::CANSparkMax *rFront_in, rev::CANSparkMax *rBack_in) 
: lFrontEncoder(lFront_in->GetEncoder()), rFrontEncoder(rFront_in->GetEncoder()), lBackEncoder(lBack_in->GetEncoder()), rBackEncoder(rBack_in->GetEncoder()), lFrontPID(lFront_in->GetPIDController()), rFrontPID(rFront_in->GetPIDController()), lBackPID(lBack_in->GetPIDController()), rBackPID(rBack_in->GetPIDController())
{
    lFront = lFront_in;
    lBack = lBack_in;
    rFront = rFront_in;
    rBack = rBack_in;
	
	lFrontPID.SetP(0.2);
    lFrontPID.SetI(1e-4);
    lFrontPID.SetD(1);
    lFrontPID.SetIZone(0.1);
    lFrontPID.SetFF(0);
    lFrontPID.SetOutputRange(-1, 1);

	rFrontPID.SetP(0.2);
    rFrontPID.SetI(1e-4);
    rFrontPID.SetD(1);
    rFrontPID.SetIZone(0.1);
    rFrontPID.SetFF(0);
    rFrontPID.SetOutputRange(-1, 1);

	lBackPID.SetP(0.2);
    lBackPID.SetI(1e-4);
    lBackPID.SetD(1);
    lBackPID.SetIZone(0.1);
    lBackPID.SetFF(0);
    lBackPID.SetOutputRange(-1, 1);

	rBackPID.SetP(0.2);
    rBackPID.SetI(1e-4);
    rBackPID.SetD(1);
    rBackPID.SetIZone(0.1);
    rBackPID.SetFF(0);
    rBackPID.SetOutputRange(-1, 1);
}

void SparkDrive::MecDrive(double xAxis, double yAxis, double rot, bool turboButton, bool slowButton) //homemade mecanum drive!
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

		lFront -> Set(lFrontSpeed*maxSpeed);
		lBack -> Set(lBackSpeed*maxSpeed);
		rFront -> Set(rFrontSpeed*maxSpeed);
		rBack -> Set(rBackSpeed*maxSpeed);
	}

	void SparkDrive::DriveStraight(double speed, double currentAngle)
	{
		leftDifference = currentAngle*.05;
		rightDifference = currentAngle*.05;

		if(currentAngle < 0 - slop)
		{
			lFront -> Set(-speed);
			rFront -> Set(speed+leftDifference);
			lBack -> Set(-speed);
			rBack -> Set(speed+leftDifference);
		}

		else if(currentAngle > 0 + slop)
		{
			lFront -> Set(-speed+rightDifference);
			rFront -> Set(speed);
			lBack -> Set(-speed+rightDifference);
			rBack -> Set(speed);
		}

		else
		{
			rFront -> Set(speed);
			lFront -> Set(-speed);
			lBack -> Set(-speed);
			rBack -> Set(speed);
		}
	}
	
	 void SparkDrive::RotateToAngle(double speed, double targetAngle, double currentAngle){
		double rotSpeed = speed;
		double angleSlop = 3;
		double remainingAngle = targetAngle - currentAngle;
		//targetAngle / fabs(currentAngle);

				if (fabs(remainingAngle) > angleSlop)
				{
					if (remainingAngle > 20){
						rotSpeed = 1;
						rFront -> Set(rotSpeed);
						lFront -> Set(-rotSpeed);
						lBack -> Set(-rotSpeed);
						rBack -> Set(rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					else if (remainingAngle <= 20 && remainingAngle > angleSlop){
						rotSpeed = 0.5;
						rFront -> Set(rotSpeed);
						lFront -> Set(-rotSpeed);
						lBack -> Set(-rotSpeed);
						rBack -> Set(rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					else if (remainingAngle < -20){
						rotSpeed = 1;
						rFront -> Set(-rotSpeed);
						lFront -> Set(rotSpeed);
						lBack -> Set(rotSpeed);
						rBack -> Set(-rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					} 
					else if (remainingAngle >= -20 && remainingAngle < -angleSlop){
						rotSpeed = 0.5;
						rFront -> Set(-rotSpeed);
						lFront -> Set(rotSpeed);
						lBack -> Set(rotSpeed);
						rBack -> Set(-rotSpeed);
						remainingAngle = (targetAngle - currentAngle);
					}
					
				}
				else {
					rFront -> Set(0);
					lFront -> Set(0);
					lBack -> Set(0);
					rBack -> Set(0);
				}
				//else if goToTarget
				// add different function where we travel to the vison target
	 }


	void SparkDrive::StrafeStraight(double speed, SparkDrive::StrafeDirection dir) {
		switch(dir)
		{
		case SparkDrive::StrafeDirection::left:
			lFront -> Set(-speed);
			rFront -> Set(speed);
			lBack -> Set(speed);
			rBack -> Set(-speed);
			break;
		case SparkDrive::StrafeDirection::right:
			lFront -> Set(speed);
			rFront -> Set(-speed);
			lBack -> Set(-speed);
			rBack -> Set(speed);
			break;
		default:
			break;
		}
	}

	void SparkDrive::pidDrive(double inches)
	{
		lFrontPID.SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		rFrontPID.SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		lBackPID.SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		rBackPID.SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
	}
	double SparkDrive::getlFrontRotations()
	{
		double rotations = lFrontEncoder.GetPosition();
		return rotations;
	}
	double SparkDrive::getrfrontRotations()
	{
		double rotations = rFrontEncoder.GetPosition();
		return rotations;
	}
	double SparkDrive::getlBackRotations()
	{
		double rotations = lBackEncoder.GetPosition();
		return rotations;
	}
	double SparkDrive::getrBackRotations()
	{
		double rotations = rBackEncoder.GetPosition();
		return rotations;
	}
