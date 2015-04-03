#include "WPILib.h"
#include <Relay.h>
#include "Encoder.h"

// Integer globals
float shooterSpeed = 0.0;
float loaderSpeed = 0.0;
float shooterPower = -0.67; // Full power shot
bool shooterPowerFlag = false;
int printCounter;
const float shootingDelay = 4.0; // Time for shooting wheel to spin up to speed.

// Autonomous variables
// const float turningTime = 1.0; // Time to turn 90 degrees
const float forwardTime = 4.0; // Time to move forward to the place we want

class RobotDemo : public IterativeRobot {
	// Drive system motor controllers
    Talon *rightFront;
    Talon *leftFront;
    Talon *rightBack;
    Talon *leftBack;

    // Loader and shooter motor controllers
    Victor *loader;
    Talon *shooter;

    // Shooter timer
    Timer *timer;

    // Joysticks
//    Joystick *controllerLeft;
//    Joystick *controllerRight;

    Joystick *gamepadController;

    // Encoder for the shooter wheel
    // Encoder *shooterEncoder;

public:
    RobotDemo(void) {
  		printf("RobotDemo Constructor Started\n");

  		rightFront = new Talon(1);
  		leftFront  = new Talon(3);
  		rightBack  = new Talon(2);
  		leftBack   = new Talon(4);

  		loader     = new Victor(6);
  		shooter    = new Talon(5);

  		timer = new Timer();
//
//  		controllerLeft  = new Joystick(1);
//  		controllerRight = new Joystick(2);

  		gamepadController = new Joystick(1);

  		// shooterEncoder = new Encoder(1,2);

  		// Acquire the Driver Station object
  		m_ds = DriverStation::GetInstance();

  	    printf("RobotDemo Constructor Completed\n");
  	}

  	/********************************** Init Routines *************************************/

  	void RobotInit(void) {}
  	void DisabledInit(void) {}

  	void AutonomousInit(void) {
  		// Set all motor controllers to be not moving.
		leftFront->SetSpeed(0.0);
		rightFront->SetSpeed(0.0);
		leftBack->SetSpeed(0.0);
		rightBack->SetSpeed(0.0);

		timer->Reset(); // Set timer back to 0
		timer->Start(); // Start timer for autonomous code
  	}

  	void TeleopInit(void) {
  		// Set all motor controllers to be not moving.
  		leftFront->SetSpeed(0.0);
  		rightFront->SetSpeed(0.0);
  		leftBack->SetSpeed(0.0);
  		rightBack->SetSpeed(0.0);

  		shooter->SetSpeed(0.0);
  		loader->SetSpeed(0.0);

		timer->Reset(); // Set timer back to 0

  		// shooterEncoder->Start();
  	}

  	void motorControlLeft(float speed) {
		leftFront->SetSpeed(speed);
		leftBack->SetSpeed(speed);
	}

	void motorControlRight(float speed) {
		rightFront->SetSpeed(speed);
		rightBack->SetSpeed(speed);
	}

  	/********************************** Periodic Routines *************************************/

  	void DisabledPeriodic(void) {}
  	void AutonomousPeriodic(void) {
  		// Autonomous Code

		if((timer->Get() < forwardTime)) { // Move forward after robot has finished turning sequence.
			motorControlLeft(0.77);
			motorControlRight(-1.0);
		} else {
			motorControlLeft(0.0);
			motorControlRight(0.0);

//			if((timer->Get() > (forwardTime + shootingDelay)) && (timer->Get() < (shootingDelay + forwardTime + 1.5))) { // Threshold when disk will have been launched
//				loaderSpeed = -1.0; // (-) means loading to the shooter
//			} else if(timer->Get() >= (forwardTime + shootingDelay + 1.5)) { // Threshold when shooter will be going near max speed
//				shooter->SetSpeed(0.0);
//				loader->SetSpeed(0.0);
//				timer->Stop();
//				timer->Reset(); // Set timer back to 0
//			}

			timer->Stop();
		}
  	}

  	void TeleopPeriodic(void) {

  		float leftDrive  = gamepadController->GetRawAxis(1);  // Drive system
  		float rightDrive = gamepadController->GetRawAxis(3); // Drive system
  		bool moveLeft  = gamepadController->GetRawButton(5);  // Trigger to slide left
  		bool moveRight = gamepadController->GetRawButton(6); // Trigger to slide right
//  		bool moveHalfLeft  = controllerLeft->GetRawButton(2);  // Half speed slide left
//  		bool moveHalfRight = controllerRight->GetRawButton(2); // Half speed slide right
//  		bool loadButton = controllerLeft->GetRawButton(3);   // Loader
//  		bool shootButton = controllerRight->GetRawButton(3); // Shooter
//  		bool decreaseShooterSpeed = controllerLeft->GetRawButton(4) || controllerRight->GetRawButton(4);
//  		bool increaseShooterSpeed = controllerLeft->GetRawButton(5) || controllerRight->GetRawButton(5);

  		// loaderSpeed = 0.25;  // Keeps the disk in the robot by spinning the loader back all the time

  		// Shooter control (toggle button with timer)
//		if(shootButton) {
//			timer->Reset(); // Set timer back to 0
//			timer->Start();
//		} else if(timer->Get() > 0) {
//			shooterSpeed = shooterPower; // (-) means shooting
//
//			if((timer->Get() > shootingDelay) && (timer->Get() < (shootingDelay + 1.5))) { // Threshold when disk will have been launched
//				loaderSpeed = -1.0; // (-) means loading to the shooter
//			} else if(timer->Get() > (shootingDelay + 1.5)) { // Threshold when shooter will be going near max speed
//				shooterSpeed = 0.0;
//				loaderSpeed = 0.0;
//				timer->Stop();
//				timer->Reset(); // Set timer back to 0
//			}
//		} else {
//	  		// Loader control (hold down button)
//	  		if(loadButton) {
//				shooterSpeed = 0.7; // Load disks into under the loader wheel using the shooter
//			} else {
//				shooterSpeed = 0.0;
//			}
//		}
//
//		// Adjust shooter speed
//		if (decreaseShooterSpeed && !shooterPowerFlag) {
//			if (shooterPower <= -0.55) shooterPower += 0.01;
//			printf("%f\n", shooterPower);
//		} else if (increaseShooterSpeed && !shooterPowerFlag) {
//			if (shooterPower >= -0.85) shooterPower -= 0.01;
//			printf("%f\n", shooterPower);
//		}
//
//		if (decreaseShooterSpeed || increaseShooterSpeed) {
//			shooterPowerFlag = true;
//		} else {
//			shooterPowerFlag = false;
//		}

  		// Drive system deadzone
  		if(leftDrive < 0.2 && leftDrive > -0.2) {
  			leftDrive = 0.0;
  		}
  		if(rightDrive < 0.2 && rightDrive > -0.2) {
  			rightDrive = 0.0;
  		}

  		// Motor speed declarations done at the end to ensure watchdog is continually updated.
  		if (moveLeft) {
  			leftFront->SetSpeed(1.0); // backwards
  			leftBack->SetSpeed(-1.0);
  			rightFront->SetSpeed(1.0);
  			rightBack->SetSpeed(-1.0);
  		} else if (moveRight) {
  			leftFront->SetSpeed(-1.0);
  			leftBack->SetSpeed(1.0);
  			rightFront->SetSpeed(-1.0);
  			rightBack->SetSpeed(1.0);
//  		} else if (moveHalfLeft) {
//			leftFront->SetSpeed(0.5); // backwards
//			leftBack->SetSpeed(-0.5);
//			rightFront->SetSpeed(0.5);
//			rightBack->SetSpeed(-0.5);
//		} else if (moveHalfRight) {
//			leftFront->SetSpeed(-0.5);
//			leftBack->SetSpeed(0.5);
//			rightFront->SetSpeed(-0.5);
//			rightBack->SetSpeed(0.5);
  		} else {
  			motorControlLeft(-leftDrive);
  			motorControlRight(rightDrive);
  		}

  		// Print values (rate limited to 1/20)
//  		if(printCounter % 20 == 0) {
//  			printf("Encoder Motor 1: %d\n", shooterEncoder->Get());
//  		}
//  		printCounter++;

  		shooter->SetSpeed(shooterSpeed);
  		loader->SetSpeed(loaderSpeed);
  	}

  	void DisabledContinuous(void) {}
  	void AutonomousContinuous(void) {}
  	void TeleopContinuous(void) {}
  };

  START_ROBOT_CLASS(RobotDemo)
