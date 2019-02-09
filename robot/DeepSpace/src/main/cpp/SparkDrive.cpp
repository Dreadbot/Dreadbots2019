#include "SparkDrive.h"
double const inchesToRotations = 1;
SparkDrive::SparkDrive(rev::CANSparkMax *lFront_in, rev::CANSparkMax *lBack_in, rev::CANSparkMax *rFront_in, rev::CANSparkMax *rBack_in)
{
    lFront = lFront_in;
    lBack = lBack_in;
    rFront = rFront_in;
    rBack = rBack_in;

	rev::CANEncoder lFrontEncoder = lFront -> GetEncoder();
	rev::CANEncoder rFrontEncoder = rFront -> GetEncoder();
	rev::CANEncoder lBackEncoder = lBack -> GetEncoder();
	rev::CANEncoder rBackEncoder = rBack -> GetEncoder();

	rev::CANPIDController lFrontPID = lFront -> GetPIDController();
	rev::CANPIDController rFrontPID = rFront -> GetPIDController();
	rev::CANPIDController lBackPID = lBack -> GetPIDController();
	rev::CANPIDController rBackPID = rBack -> GetPIDController();

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
	void SparkDrive::pidDrive(double inches)
	{
		lFrontPID -> SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		rFrontPID -> SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		lBackPID -> SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
		rBackPID -> SetReference(inches * inchesToRotations, rev::ControlType::kPosition);
	}
	double SparkDrive::getRotations()
	{
		double rotations[4] = {lFrontEncoder -> GetPosition(), rFrontEncoder -> GetPosition(), lBackEncoder -> GetPosition(), rBackEncoder -> GetPosition()};
	}