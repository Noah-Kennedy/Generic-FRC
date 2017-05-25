package core;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

public class Sender {
	public static void main(String[] args){
		NetworkTable.setServerMode();
		NetworkTable.setIPAddress("10.47.86.1");
		NetworkTable table = NetworkTable.getTable("testTable");
		while(true){
			table.putString("Test", "Recieved");
		}
	}
}
