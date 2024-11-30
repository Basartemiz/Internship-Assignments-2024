import java.io.File;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String input1="large_initial5.txt";
        String input2="large5.txt";
        String output1="output.txt";
        InputTaker taker=new InputTaker(input1,input2);
        OutputGiver giver=new OutputGiver(output1,taker.getSecondInputs(),taker.getBranches());
    }
}