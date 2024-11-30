//Başar Temiz,2022400132,07.05.2023
//The class that contains methods used to solve  algorithmic problems



import java.util.ArrayList;

public class MatrixSolver {
    private ArrayList<ArrayList<Integer>> matrix;
    private int width,length;
    private Integer [][] floodedwater;
    private Integer [][]  addedwater;
    private Integer [][] waterlakes;
    private String [][] waterlakes_alpha;
    private char char1='a';

    private double totalvolume;
    private int tempsum;
    private int biggest_number;
    MatrixSolver(ArrayList<ArrayList<Integer>> matrix,int width,int lenght){
        this.matrix=matrix;
        this.width=width;
        this.length=lenght;
    }




    //derives the terrain as if the water is not fluid
    public void deriveFloodedMatrix(){
        int a=0;
        //find the biggest number in the matrix
        for(ArrayList<Integer> list:matrix){
            for(int b:list){
                if(b>a){
                    a=b;

                }
            }
        }
        biggest_number=a;

        //create the flooded matrix
        floodedwater=new Integer[length][];

        for(int i=0;i<length;i++){
            floodedwater[i]=new Integer[width];
            for(int c=0;c<width;c++){
                floodedwater[i][c]=a;
            }

        }
    }

    //derives the terrain with added water to the normal terrain when creating flooded terrain
    public void deriveTheAddedWater(){
        addedwater=new Integer[length][];
        for(int i=0;i<length;i++){
            addedwater[i]=new Integer[width];
            for(int c=0;c<width;c++){
                addedwater[i][c]=floodedwater[i][c]-matrix.get(i).get(c);
            }

        }
    }

    //now we think the water is fluid and we make the water flow
    public void solveMatrix(){
        for(int i=0;i<width;i++){
           while(addedwater[length-1][i]>0){
               eliminatewater(length-1,i,floodedwater[length-1][i]);
           }

        }
        for(int i=0;i<width;i++){
            while(addedwater[0][i]>0){
                eliminatewater(0,i,floodedwater[0][i]);
            }

        }
        for(int i=0;i<length;i++){
            while(addedwater[i][0]>0){
                eliminatewater(i,0,floodedwater[i][0]);
            }

        }
        for(int i=0;i<length;i++){
            while(addedwater[i][width-1]>0){
                eliminatewater(i,width-1,floodedwater[i][width-1]);
            }

        }





    }


    // this method is for erasing the water at the same heights that connects , this method used in the solveMatrix method
    public void eliminatewater(int y,int x,int height){
        if(addedwater[y][x]>0){
            int hegihtdif=floodedwater[y][x]-height;
            int deletedwater=hegihtdif+1;
            if(deletedwater>addedwater[y][x]){
                deletedwater=addedwater[y][x];
            }
            floodedwater[y][x]-=deletedwater;
            addedwater[y][x]-=deletedwater;

        }
        Integer [] addedy={1,0,-1};
        Integer [] addedx={1,0,-1};

        for(int addy:addedy){
            for(int addx:addedx){
                if(addx==0&&addy==0){
                    continue;
                }
                if(y+addy<0 || y +addy>length-1 || x+addx<0 || x +addx>width-1){
                    continue;
                }
                if(floodedwater[y+addy][x+addx]>=height && addedwater[y+addy][x+addx]>0){
                    eliminatewater(y+addy,x+addx,height);
                }




            }
        }


    }

    //this methods used for calculating the volume of the left water  with wanted mathematical formulas .
    public void calculateVolume(){


        //create the water lake array
        waterlakes=new Integer[length][];
        for(int i=0;i<length;i++){
            waterlakes[i]=new Integer[width];
            for(int c=0;c<width;c++){
                waterlakes[i][c]=addedwater[i][c];
            }

        }

        //create the alphabetical waterlake array
        waterlakes_alpha=new String[length][];
        for(int i=0;i<length;i++){
            waterlakes_alpha[i]=new String[width];
            for(int c=0;c<width;c++){
                waterlakes_alpha[i][c]="0";
            }

        }

       for(int i=0;i<length;i++){
           for(int c=0;c<width;c++){
               if(waterlakes[i][c]!=0){
                   eliminatelake(i,c);
                   totalvolume+=Math.sqrt(tempsum);
                   char1+=1;
                   tempsum=0;

               }
           }
       }






    }

    public void eliminatelake(int y,int x){
        tempsum+=waterlakes[y][x];
        waterlakes[y][x]=0;
        waterlakes_alpha[y][x]=InputProcessor.ChartoString(char1).toUpperCase();

        Integer [] addedy={1,0,-1};
        Integer [] addedx={1,0,-1};

        for(int addy:addedy){
            for(int addx:addedx){
                if(addx==0&&addy==0){
                    continue;
                }
                if(y+addy<0 || y +addy>length-1 || x+addx<0 || x +addx>width-1){
                    continue;
                }
               if(waterlakes[y+addy][x+addx]!=0){
                   eliminatelake(y+addy,x+addx);
               }
            }
        }
    }


    public void printFloodedWater(){
        InputProcessor.printMatrix(floodedwater);
    }
    public void printAddedWater(){
        InputProcessor.printMatrix(addedwater);

    }
    public void printScore(){
        System.out.print(String.format("Final score: %.2f",totalvolume));
    }

    public void printwaterlakes(){
        InputProcessor.printMatrix(waterlakes_alpha);

    }
    public void printFinalMatrix(){
        String [] [] matrix_string=new String[length][];
        for(int i=0;i<length;i++){
            matrix_string[i]=new String[width];
            for(int c=0;c<width;c++){
                if(!waterlakes_alpha[i][c].equals("0")){
                    matrix_string[i][c]=waterlakes_alpha[i][c];
                }
                else{
                    matrix_string[i][c]=String.valueOf(matrix.get(i).get(c));
                }
            }
        }


        InputProcessor.printMatrix(matrix_string);
    }


}
