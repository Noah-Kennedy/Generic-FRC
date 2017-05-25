package core;
import edu.wpi.first.wpilibj.networktables.*;
import edu.wpi.first.wpilibj.networktables2.type.*;
import edu.wpi.first.wpilibj.*;

public class Driver {
	public static void main(String[] args){
		NetworkTable.setClientMode();
		NetworkTable.setIPAddress("10.47.86.2");
		NetworkTable table = NetworkTable.getTable("testTable");
		while(true){
			System.out.println(table.getString("Test", "Not Recieved"));
		}
	}
}
