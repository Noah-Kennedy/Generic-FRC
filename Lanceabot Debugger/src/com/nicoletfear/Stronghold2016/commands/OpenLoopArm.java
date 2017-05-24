package com.nicoletfear.Stronghold2016.commands;

import com.ctre.CANTalon.TalonControlMode;
import com.nicoletfear.Stronghold2016.OI;
import com.nicoletfear.Stronghold2016.Robot;

import edu.wpi.first.wpilibj.GenericHID;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class OpenLoopArm extends Command {

    public OpenLoopArm() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.arm);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.arm.positionMotor.changeControlMode(TalonControlMode.PercentVbus);


    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(OI.gameMech.getY(GenericHID.Hand.kRight) > .1 || OI.gameMech.getY(GenericHID.Hand.kRight) < -.1){
    		Robot.arm.positionMotor.changeControlMode(TalonControlMode.PercentVbus);
    		Robot.arm.openLoopArmControl(OI.gameMech.getY(GenericHID.Hand.kRight));
    	}else{
    		Robot.arm.positionMotor.changeControlMode(TalonControlMode.Position);
    		Robot.arm.armHold();
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.arm.positionMotor.changeControlMode(TalonControlMode.PercentVbus);
    	Robot.arm.positionMotor.set(0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	end();
    }
}
