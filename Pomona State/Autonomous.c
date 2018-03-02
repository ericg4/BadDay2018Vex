#pragma config(Sensor, port5,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port8,  distanceSensor,  sensorVexIQ_Distance)
#pragma config(Motor,  motor1,  leftMotor,     tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,  rightMotor,    tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor10, armMotor,      tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void moveWithCorrection(int degrees, int speed, int correctionInterval) {
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	int originalGyroVal = getGyroDegrees(gyroSensor);
	int turnSpeed = 40;
	int count = 1;

	while(abs(getMotorEncoder(leftMotor)) < (degrees) &&
		abs(getMotorEncoder(rightMotor)) < (degrees))
	{
		setMotorSpeed(leftMotor, speed);
		setMotorSpeed(rightMotor, speed);
		//straight correction
		if(getMotorEncoder(leftMotor) >= count * correctionInterval ||
			getMotorEncoder(rightMotor) >= count * correctionInterval)
		{
			count++;
			int currentGyroVal = getGyroDegrees(gyroSensor);
			int straightCorrection = originalGyroVal - currentGyroVal;
			writeDebugStream("Starting Correction. Counter = %d Current Gyro Value = %d\n",count, currentGyroVal);


			while(getGyroDegrees(gyroSensor) != originalGyroVal) {
				eraseDisplay();
				displayTextLine(1, "Starting Correction.");
				displayTextLine(2, "Counter = %d",count);
				displayTextLine(3, "Gyro Value = %d",currentGyroVal);

				if(currentGyroVal < originalGyroVal) {
					setMotorSpeed(leftMotor, turnSpeed);
					setMotorSpeed(rightMotor, speed);
				}
				else if(currentGyroVal > originalGyroVal) {
					setMotorSpeed(leftMotor, speed);
					setMotorSpeed(rightMotor, turnSpeed);
				}
			}
		}
	}
	//normal
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	sleep(100);
}

void moveForwardWithSpeed(float rotations, int speed)
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	//We set the measuring scale to rotations since degrees were not accurate, and they were not working for us
	setMotorEncoderUnits(encoderRotations);
	//moveforward
	moveMotorTarget(rightMotor, rotations, speed - 1);
	moveMotorTarget(leftMotor, rotations, speed);
	//stop motors
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}
void moveForward(float rotations)
{
	moveForwardWithSpeed(rotations, 75);
}

void moveForwardSlowly(float rotations)
{
	moveForwardWithSpeed(rotations, 55);
}
int noOfLefts = 0;
void adjustAngle()
{

	float target = 89.0 * (noOfLefts);

	while (getGyroDegreesFloat(gyroSensor) <(target - 1.0))
	{
		setMotorSpeed(leftMotor, 5);
		setMotorSpeed(rightMotor, -5);
	}
	while (getGyroDegreesFloat(gyroSensor) >(target + 1.0))
	{
		setMotorSpeed(leftMotor, -5);
		setMotorSpeed(rightMotor, 5);
	}
	setMotorSpeed(rightMotor, 0);
	setMotorSpeed(leftMotor, 0);

}

void turnLeft ()
{
	//increasing the number of lefts for another
	noOfLefts =noOfLefts + 1;
	//We used 89 degress since, 90 always made it turn more or make it turn less
	float target = 89.0 * noOfLefts;

	//This is used to turn left
	setMotorSpeed(leftMotor, 40);
	setMotorSpeed(rightMotor, -40);

	//It is saying if it is less than 79 degress continue to try
	while (getGyroDegreesFloat(gyroSensor) <(target - 10.0))
	{
	}
	//turning to the left slower, at speed of 10
	setMotorSpeed(leftMotor, 10);
	setMotorSpeed(rightMotor, -10);
	//same thing as other angle
	while (getGyroDegreesFloat(gyroSensor) <(target - 8.0))
	{
	}
	setMotorSpeed(leftMotor, 5);
	setMotorSpeed(rightMotor, -5);
	//different angle
	while (getGyroDegreesFloat(gyroSensor) <(target - 3.0))
	{

	}
	//stopping the motors
	setMotorSpeed(rightMotor, 0);
	setMotorSpeed(leftMotor, 0);

}

void lowerToPegs()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorEncoderUnits(encoderRotations);
	//go down onto the post
	moveMotorTarget(armMotor, 0.27, 65);
	//stop the arm motor
	waitUntilMotorStop(armMotor);
	//arm motor lowering, and the robot going back at the same time
	moveMotorTarget(armMotor, 1.3, 65);
	moveMotorTarget(leftMotor, 0.5, 25);
	moveMotorTarget(rightMotor, 0.5, 25);
	//stop the motors now that the on the post
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);

	waitUntilMotorStop(armMotor);

	//releasing the rings from the claw to the post
	moveMotorTarget(leftMotor, 0.83, 60);
	moveMotorTarget(rightMotor,0.83, 60);

	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

void raiseArm (float rotations)
{
	//raising arm to any degree
	float degrees = rotations * 360;

	setMotorEncoderUnits(encoderDegrees);
	setMotorTarget(armMotor, degrees, 90);

	waitUntilMotorStop(armMotor);

}
//places the arm will be
float groundToPost = -4.18;
float groundToStarter = -1.06;

void raiseToPost ()
{
	raiseArm(groundToPost);

}
void raiseToPostFromPegs ()
{
	raiseArm(groundToPost);
}
void raiseToPostFromGround ()
{
	//raiseArm(groundToPost);

	//raising arm to any degree
	float degrees = groundToStarter * 360;
	float rotations = -3.95;
	int speed = 80;
	setMotorEncoderUnits(encoderDegrees);
	setMotorTarget(armMotor, degrees, 65);


	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);

	//We set the measuring scale to rotations since degress were not accurate, and they were not working for us
	setMotorEncoderUnits(encoderRotations);
	//moveforward
	moveMotorTarget(rightMotor, rotations, speed);
	moveMotorTarget(leftMotor, rotations, speed);
	//stop motors
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
	waitUntilMotorStop(armMotor);
}
void lowerToStarter ()
{
	raiseArm(groundToStarter);
}

task main()
{

	int i =0;
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	resetGyro(gyroSensor);
	//motor arm is held because typically it reduces the height without the motorHold function
	if(getMotorBrakeMode(armMotor) != motorHold)
	{
		setMotorBrakeMode(armMotor, motorHold);
	}
	if(getMotorBrakeMode(leftMotor) != motorHold)
	{
		setMotorBrakeMode(leftMotor, motorHold);
	}
	if(getMotorBrakeMode(rightMotor) != motorHold)
	{
		setMotorBrakeMode(rightMotor, motorHold);
	}

	for (i=0; i<1; i++) {

		raiseToPostFromGround();
		//moveForward(-3.95);
		turnLeft();

		lowerToStarter();
		//more move forward because it wasn't working
		if (i==2) {
			moveForward(-1.328);
			} else {
			moveForward(-1.325);
		}
		raiseToPost();
		turnLeft();

		moveForward(-1);
		turnLeft();
		//less and again without adjustAngle
		if (i==2) {
			moveForwardSlowly(-2.209);
			} else {
			moveForwardSlowly(-2.206);
		}

		moveForwardSlowly(0.65);
		//if (i!=2) {
		//we are not doing adjustAngle since it is really far off when the adjustAngle
		adjustAngle();
		//}
		moveForwardSlowly(-0.64);
		lowerToPegs();
		turnLeft();
		moveForwardSlowly(-0.19);
	}
	delay(10000);
}
