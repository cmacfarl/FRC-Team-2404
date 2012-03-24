#ifndef _MyRobot_h_
#define _MyRobot_h_

#define Jaguar 1	1

class MyRobot : public SimpleRobot
{
    private :
		CANJaguar *m_pscLeft1;
		CANJaguar *m_pscLeft2;
		CANJaguar *m_pscRight1;
		CANJaguar *m_pscRight2;
		CANJaguar *m_pscLowerPickup;
		CANJaguar *m_pscUpperPickup;
		
		Joystick *joystick1;
		Joystick *joystick2;
		
    public:
        MyRobot(void);
        ~MyRobot(void);
        void Autonomous(void);
        void OperatorControl(void);
        void Drive(float, float);
};

#endif
