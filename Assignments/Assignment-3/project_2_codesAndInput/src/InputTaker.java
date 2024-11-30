import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class InputTaker {
    private final String filename1;
    private final String filename2;
    private final ArrayList<String[]> firstInputs;
    private final ArrayList<String[]> secondInputs;
    private final HashTable<Branch> branches;
    InputTaker(String filename1,String filename2){
        this.filename1=filename1;
        this.filename2=filename2;
        firstInputs=new ArrayList<>();secondInputs=new ArrayList<>();
        branches=new HashTable<>();
        getInput1();getInput2();processInput1();

    }

    public HashTable<Branch> getBranches(){
        return branches;
    }

    public ArrayList<String[]> getSecondInputs() {
        return secondInputs;
    }

    private void getInput1(){
        try{
            Scanner scanner1 = new Scanner(new File(filename1));
            while(scanner1.hasNextLine()){
                firstInputs.add(scanner1.nextLine().split(", "));
            }

        }
        catch(Exception ignored){}
    }
    private void getInput2(){
        try{
            Scanner scanner2 = new Scanner(new File(filename2));
            while(scanner2.hasNextLine()){
                secondInputs.add(processInput2(scanner2.nextLine().split(", ")));
            }
        }
        catch(Exception e){
            System.out.println("exc");
        }
    }
    private String[] processInput2(String[] input) {
        if(input.length==1)
        {
            if(input[0].length()==0)
                return input;
            String s=input[0].substring(0, input[0].length()-1);
            input[0]=s;
            return input;
        }
        String[] output = new String[input.length + 1];
        output[0] = input[0].split(": ")[0];
        output[1] = input[0].split(": ")[1];
        System.arraycopy(input, 1, output, 2, input.length - 1);
        return output;
    }


    private void processInput1(){
        for(String[] list:firstInputs){
            Branch branch=new Branch(list[0],list[1]);
            Employee e=new Employee(list[2],processJob(list[3]));
            if(branches.contains(branch))
               branch=branches.get(list[0]+list[1]);
            else
                branches.insert(branch);
            branch.addEmployee(e);

        }
    }

    public static int processJob(String job){
        return switch (job) {
            case "COURIER" -> 0;
            case "CASHIER" -> 1;
            case "COOK" -> 2;
            default -> 3;
        };
    }



}
