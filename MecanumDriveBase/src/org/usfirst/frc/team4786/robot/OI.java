package org.usfirst.frc.team4786.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.Button;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	public Joystick arcadeDriveJoy;
	
	public OI(){
		arcadeDriveJoy = new Joystick(RobotMap.arcadeDriveJoyPort);
	}
	
}