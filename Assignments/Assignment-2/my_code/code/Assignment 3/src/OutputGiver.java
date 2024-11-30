//Başar Temiz,2022400132,07.05.2023
//This class contains methods for taking input and giving inputs accordingly


import java.util.ArrayList;
import java.util.Scanner;

public class OutputGiver {
    public ArrayList<ArrayList<Integer>> matrix;
    public ArrayList<ArrayList<Integer>> modifications;
    OutputGiver(){
        matrix=new ArrayList<>();
        for (ArrayList<Integer> list:InputProcessor.matrix){
            matrix.add((ArrayList<Integer>)list.clone());
        }
        modifications=InputProcessor.modifications;
    }

    //used for testing
    public void startOutputs(){
        int count=1;
        for(ArrayList<Integer> modification:modifications){
            ArrayList<Integer> list=matrix.get(modification.get(0));
            list.set(modification.get(1),(list.get(modification.get(1))+1));
            printTerrain(count);
            count+=1;
        }



    }

    //takes outputs and prints the terrain
    public void takeOutputs(int a){
        if(a<=10){
            Scanner scanner=new Scanner(System.in);
            System.out.print("Add stone " + a+" / 10 to coordinate: ");
            String c=scanner.next();
            try{
                String [] coordinates=c.split("");
                String x=coordinates[0];
                String y=coordinates[1];
                char char1=x.charAt(0);
                int coor_x=char1-'a';
                int coor_y=Integer.parseInt(y);
                if(coor_x<0 && coor_x>InputProcessor.width &&coor_y<0 && coor_y>InputProcessor.line){
                    System.out.println();
                    System.out.println("Wrong Input!");
                    System.out.println();
                    takeOutputs(a);
                }
                ArrayList<Integer> list=matrix.get(coor_y);
                list.set(coor_x, list.get(coor_x)+1);
                InputProcessor.printMatrix(matrix,false);
                System.out.println("---------------");
                takeOutputs(a+1);
            }
            catch(Exception e){
                System.out.println();
                System.out.println("Wrong Input!");
                System.out.println();
                takeOutputs(a);

            }
        }

    }
    public void printTerrain(int a){
        System.out.println("Add stone "+a+" / 10 to coordinate:");
        InputProcessor.printMatrix(matrix,false);

        System.out.println("---------------");
    }




}
