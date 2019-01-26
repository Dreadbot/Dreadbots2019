#include "SparkDrive.h"

SparkDrive::SparkDrive(rev::CANSparkMax *lFront_in, rev::CANSparkMax *lBack_in, rev::CANSparkMax *rFront_in, rev::CANSparkMax *rBack_in)
{
    lFront = lFront_in;
    lBack = lBack_in;
    rFront = rFront_in;
    rBack = rBack_in;
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