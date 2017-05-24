package org.usfirst.frc.team4786.robot;

import com.ctre.CANTalon;
import com.ctre.CANTalon.TalonControlMode;

import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Robot extends IterativeRobot {
	
	private Joystick kLeftJoystick = new Joystick(0);
	private Joystick kRightJoystick = new Joystick(1);
	private CANTalon kLeftTalon = new CANTalon(13);
	private CANTalon kRightTalon = new CANTalon(14);
	private final double scaling = 1;
	
	private void drive(double leftInput, double rightInput) {
		kLeftTalon.changeControlMode(TalonControlMode.PercentVbus);
		kRightTalon.changeControlMode(TalonControlMode.PercentVbus);
		kLeftTalon.set(leftInput);
		kRightTalon.set(rightInput);
		
	}
	
	@Override
	public void robotInit() {
		kLeftTalon.enable();
		kRightTalon.enable();
		kLeftTalon.setInverted(true);
		
	}
	
	@Override
	public void autonomousInit() {
		
	}

	@Override
	public void autonomousPeriodic() {
		drive(1,1);
		
	}

	@Override
	public void teleopPeriodic() {
		SmartDashboard.putNumber("Left Joystick", kLeftJoystick.getY());
		SmartDashboard.putNumber("Right Joystick", kRightJoystick.getY());
		double leftInput = kLeftJoystick.getY() * scaling;
		double rightInput = kRightJoystick.getY() * scaling;
		drive(leftInput,rightInput);
		
	}

	@Override
	public void testPeriodic() {
	}
}

