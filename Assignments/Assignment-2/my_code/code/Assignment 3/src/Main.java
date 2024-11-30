
//Başar Temiz,2022400132,07.05.2023
//Main code used to execute the program
import java.io.File;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {


        //Input Processor methods
        File file =new File("input3.txt");
        InputProcessor inputProcessor=new InputProcessor(file);
        InputProcessor.printMatrix(InputProcessor.matrix,true);



        //Output Giver methods
        OutputGiver giver =new OutputGiver();
        giver.takeOutputs(1);


        //matrix solver methods
        MatrixSolver solver=new MatrixSolver(giver.matrix,InputProcessor.width,InputProcessor.line);
        solver.deriveFloodedMatrix();
        solver.deriveTheAddedWater();
        //solver.printFloodedWater();
        //solver.printAddedWater();
        solver.eliminatewater(2,3,7);
        //solver.printAddedWater();
        solver.solveMatrix();
       // solver.printAddedWater();
        solver.calculateVolume();
        //solver.printwaterlakes();
        solver.printFinalMatrix();
        solver.printScore();

    }
}