#include "WPILib.h"
#include "MyRobot.h"
#include <CanJaguar.h>

double limit(double val, double min = -1, double max = 1)
{
	if (val > max)
		return max;
	if (val < min)
		return min;
	
	return val;
}

MyRobot::MyRobot(void)
	: m_pscLeft1(new CANJaguar (11))
	, m_pscLeft2(new CANJaguar (12))
	, m_pscRight1(new CANJaguar (13))
	, m_pscRight2(new CANJaguar (14))
	, m_pscLowerPickup(new CANJaguar(15, CANJaguar::kSpeed))
	, m_pscUpperPickup(new CANJaguar(16, CANJaguar::kSpeed))
	, joystick1(new Joystick(1))
	, joystick2(new Joystick(2))
{
	m_pscLeft1->ConfigMaxOutputVoltage(12.0);
	m_pscLeft1->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	
	m_pscLeft2->ConfigMaxOutputVoltage(12.0);
	m_pscLeft2->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	
	m_pscRight1->ConfigMaxOutputVoltage(12.0);
	m_pscRight1->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	
	m_pscRight2->ConfigMaxOutputVoltage(12.0);
	m_pscRight2->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	
	m_pscLowerPickup->ConfigMaxOutputVoltage(12.0);
	m_pscUpperPickup->ConfigMaxOutputVoltage(12.0);
}

MyRobot::~MyRobot(void)
{
	delete m_pscLeft1;
	delete m_pscLeft2;
	delete m_pscRight1;
	delete m_pscRight2;
	delete m_pscLowerPickup;
	delete m_pscUpperPickup;
	delete joystick1;
	delete joystick2;
}

void MyRobot::Autonomous(void)
{
	
}

#define LOWER_PICKUP_BUTTON 1
#define UPPER_PICKUP_BUTTON 2
#define BOTH_PICKUP_BUTTON  3
#define BALL_DRIVE_SPEED 1.0

void MyRobot::OperatorControl(void)
{
	GetWatchdog().SetEnabled(true);
	
	while(IsOperatorControl() && IsEnabled())
	{
		GetWatchdog().Feed();
		
		//Initializing x and y position variables
		float x, y;
		x = joystick1->GetX();
		if (x < 0.05 && x > -0.05)
			x = 0;
		x = (x>0) ? x * x : x * x * -1;
		
		y = joystick1->GetY();
		if (y < 0.05 && y > -0.05)
			y = 0;
		y = (y>0) ? y * y * -1: y * y;
		
		float fLeft = (y + x);
		float fRight = (y - x);
		
		Drive(fLeft, fRight);
		
		if (joystick2->GetRawButton(LOWER_PICKUP_BUTTON)) {
			m_pscLowerPickup->Set(BALL_DRIVE_SPEED);
		} else {
			m_pscLowerPickup->Set(0.0);
        }

		if (joystick2->GetRawButton(UPPER_PICKUP_BUTTON)) {
			m_pscUpperPickup->Set(BALL_DRIVE_SPEED);
		} else {
            m_pscUpperPickup->Set(0.0);
        }

		if (joystick2->GetRawButton(BOTH_PICKUP_BUTTON)) {
			m_pscLowerPickup->Set(BALL_DRIVE_SPEED);
			m_pscUpperPickup->Set(BALL_DRIVE_SPEED);
		} else {
			m_pscLowerPickup->Set(0.0);
			m_pscUpperPickup->Set(0.0);
        }
	}
}

void MyRobot::Drive(float left, float right)
{
	m_pscLeft1->Set(limit(left));
	m_pscLeft2->Set(limit(left));
	
	m_pscRight1->Set(limit(-right));
	m_pscRight2->Set(limit(-right));
	
}


START_ROBOT_CLASS(MyRobot);

