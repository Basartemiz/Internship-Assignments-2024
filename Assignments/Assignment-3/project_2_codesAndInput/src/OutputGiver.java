import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class OutputGiver {
    private final String OUTPUT_FILE;
    private ArrayList<String[]> secondInputs;
    private HashTable<Branch> branches;
    public static  StringBuilder output=new StringBuilder();
    public OutputGiver(String OUTPUT_FILE, ArrayList<String[]> secondInputs, HashTable<Branch> branches) {
        this.OUTPUT_FILE = OUTPUT_FILE;
        this.secondInputs = secondInputs;
        this.branches = branches;
        processSecondInput();
        printOutput();
    }

    private void processSecondInput(){
        for(String[] input:secondInputs){
            switch(input[0]){
                case "PERFORMANCE_UPDATE"->{
                    Branch branch=branches.get(input[1]+input[2]);
                    Employee employee=branch.getEmployee(input[3]);
                    if(employee!=null){
                        performanceUpdate(employee,branch,Integer.parseInt(input[4]));
                    }
                    else{
                        output.append("There is no such employee.\n");
                    }
                }


                case "ADD" ->{
                    Branch branch=branches.get(input[1]+input[2]);
                    Employee employee=new Employee(input[3],InputTaker.processJob(input[4]));
                    add(branch,employee);
                }


                case "LEAVE"->{
                    Branch branch=branches.get(input[1]+input[2]);
                    Employee employee=branch.getEmployee(input[3]);
                    ;if(employee!=null){
                        leave(branch,employee);
                    }
                    else{
                        output.append("There is no such employee.\n");
                    }
                }

                case "PRINT_MONTHLY_BONUSES"->{
                    Branch branch=branches.get(input[1]+input[2]);
                    printMonthlyBonuses(branch);
                }


                case "PRINT_OVERALL_BONUSES"->{
                    Branch branch=branches.get(input[1]+input[2]);
                    printTotalBonuses(branch);
                }

                case "PRINT_MANAGER"->{
                    Branch branch=branches.get(input[1]+input[2]);
                    printManager(branch);
                }
                case ""->{
                    continue;
                }
                default->{
                    changeMonth();
                }
            }
        }
    }



    private void performanceUpdate(Employee e,Branch b,int performance){
        b.setMonthlyScore(e,performance);
    }
    private void add(Branch b, Employee e){
        b.addEmployee(e);
    }
    private void leave(Branch b, Employee e){
        b.leftEmployee(e);
    }
    private void printMonthlyBonuses(Branch b){
        output.append("Total bonuses for the ");output.append(b.getDistrict());output.append(" branch this month are: ");output.append(b.getMonthlyBonus());
        output.append("\n");
    }
    private void printTotalBonuses(Branch b){
        output.append("Total bonuses for the ");output.append(b.getDistrict());output.append(" branch are: ");output.append(b.getTotalBonus());
        output.append("\n");
    }
    private void printManager(Branch b){
        output.append("Manager of the ");output.append(b.getDistrict());output.append(" branch is ");output.append(b.getManager());
        output.append(".\n");

    }

    private void changeMonth(){
        for(List<Branch> branches_list:branches.getLists()){
            for(Branch branch:branches_list){
                branch.changeMonth();
            }
        }
    }
    private void printOutput(){
        try {
            PrintWriter writer=new PrintWriter(new File(OUTPUT_FILE));
            writer.print(output);
            writer.close();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }




}
