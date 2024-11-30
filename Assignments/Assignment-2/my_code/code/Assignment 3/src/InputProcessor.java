//Başar Temiz,2022400132,07.05.2023
//This class is for processing input data

import javax.xml.crypto.dsig.keyinfo.KeyValue;
import java.io.File;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;

public class InputProcessor {
    public static  ArrayList<ArrayList<Integer>> matrix=new ArrayList<>();
    public static  ArrayList<ArrayList<Integer>> modifications=new ArrayList<>();
    public static int width ;
    public static int line;
    private int count=0;
    public static String lake;

    InputProcessor(File file){

        try {
            Scanner scanner = new Scanner(file);
            String dimensions = scanner.nextLine();
            line = Integer.parseInt((dimensions).split(" ")[1]);
            width = Integer.parseInt((dimensions).split(" ")[0]);


            //taking the terrain as input
            while (count < line) {
                if (scanner.hasNext()) {
                    String string=scanner.nextLine();
                    ArrayList<Integer> line1=new ArrayList<>();
                    for(String c :string.split(" ")){
                        line1.add(Integer.parseInt(c));
                    }
                    matrix.add(line1);
                }
                count+=1;
            }


            //taking the modification inputs
            scanner.nextLine();
            scanner.nextLine();
            while(scanner.hasNext()){
                String string=scanner.nextLine();
                String [] coordinates=string.split("");
                char char1=coordinates[0].charAt(0);
                int char2='a';
                int x=(int)(char1)-char2;
                int y=Integer.parseInt(coordinates[1]);
                ArrayList<Integer> coors=new ArrayList<>();
                coors.add(y);
                coors.add(x);
                modifications.add(coors);
            }




        }
        catch(Exception e){
            System.out.println("exception");
        }
    }

    //prints matrix
    public static void printMatrix(ArrayList<ArrayList<Integer>> matrix,boolean f){
        int count1=0;
        for (ArrayList<Integer> list:matrix){
            printerWithSpaces(count1);
            for (Integer a:list){
                printerWithSpaces(a);
            }
            if(f) {
                if (count1 != 0) {
                    System.out.println(" ");
                } else {
                    System.out.println();
                }

            }
            else{
                System.out.println(" ");
            }
            count1 += 1;
        }

        int char1='a';
        System.out.print("   ");
        for(int i =0;i<width;i++){
            char char2=(char)char1;

            printerWithSpaces(ChartoString(char2));
            char1+=1;
        }
        System.out.println(" ");
    }
    public static void printMatrix(Integer [] []matrix){
        int count1=0;
        for (Integer [] list:matrix){
            printerWithSpaces(count1);
            for (Integer a:list){
               printerWithSpaces(a);

            }
            System.out.println(" ");
            count1+=1;
        }

        int char1='a';
        System.out.print(" ");
        for(int i =0;i<width;i++){
            char char2=(char)char1;

            System.out.print(" "+char2);
            char1+=1;
        }
        System.out.println(" ");
    }
    public static void printMatrix(String [] []matrix){
        int count1=0;
        for (String [] list:matrix){
            printerWithSpaces(count1);
            for (String a:list){
                printerWithSpaces(a);

            }

            System.out.println(" ");
            count1+=1;
        }

        int char1='a';
        System.out.print("   ");
        for(int i =0;i<width;i++){
            char char2=(char)char1;

            printerWithSpaces(ChartoString(char2));
            char1+=1;
        }
        System.out.println(" ");
    }

    //prints with spaces according to the length of the given input
    public static void printerWithSpaces(int a){
        if(a<10)
            System.out.print("  "+a);
        else
            System.out.print(" "+a);
    }
    public static void printerWithSpaces(String s){
        if(s.length()==1){
            System.out.print("  "+s);
        }
        else{
            System.out.print(" "+s);
        }
    }
    public static String ChartoString(char c){
        int dif=c-'z';
        String s="";
        if(dif>0){
             charCleaner(c,0);

        }
        else{
             lake=(c)+"";
        }
        return lake;
    }

    //used for printing strings like 'aa','ab' etc.
    public static void charCleaner(char c,int a){
        int dif='z'-'a'+1;
        String s="";
        if(c>'z'){
            charCleaner((char)(c-dif),a+1);
        }
        else{
             lake=((char)(a+'a'-1)+""+(char)(c));
        }
        ;
    }
}
