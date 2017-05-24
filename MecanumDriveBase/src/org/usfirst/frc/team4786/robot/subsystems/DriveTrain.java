package org.usfirst.frc.team4786.robot.subsystems;

import org.usfirst.frc.team4786.robot.RobotMap;
import org.usfirst.frc.team4786.robot.commands.DriveMecanumCartesian;

import com.ctre.CANTalon;
import com.ctre.CANTalon.TalonControlMode;

import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *The DriveTrainMecanum is a subsystem for a mecanum drive base. It uses the RobotDrive wpilib class
 */
public class DriveTrain extends Subsystem {

	//instance fields
	
	//Drive base cantalons
    private CANTalon frontLeft = new CANTalon(RobotMap.frontLeftPort);
    private CANTalon frontRight = new CANTalon(RobotMap.frontRightPort);
    private CANTalon backLeft = new CANTalon(RobotMap.backLeftPort);
    private CANTalon backRight = new CANTalon(RobotMap.backRightPort);
    private RobotDrive mecanum;


    public DriveTrain(){
    	frontLeft.enable();
		frontRight.enable();		
		frontLeft.setInverted(true);
		backLeft.setInverted(true);
		
		mecanum = new RobotDrive(frontLeft, backLeft, frontRight, backRight);
    }
    
    /**
     * Drives the mecanum base through the robotDrive method
     */    
    public void driveCartesianMecanum(double x, double y, double twist){
    	mecanum.mecanumDrive_Cartesian(x, y, twist, 0);
    }
    
    public void initDefaultCommand() {
        setDefaultCommand(new DriveMecanumCartesian());
    }
}

