#pragma config(Motor,  motor6,          RightBack,     tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor10,         HDrive,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor12,         LeftBack,      tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{ while(true)

{
setMotorSpeed(RightBack, getJoystickValue(ChA));
setMotorSpeed(LeftBack, getJoystickValue(ChD));
setMotorSpeed(HDrive, getJoystickValue(ChB));
}


}
