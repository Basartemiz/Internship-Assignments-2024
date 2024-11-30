import java.util.List;

public class Employee {

    private int monthlyPoint;
    private int promotionPoint;
    private int monthlyBonus;
    private String name;
    private int job;
    /*
    courier 0
    cashier 1
    cook 2
    manager 3
    */

    Employee(String name,int job){
        this.name=name;
        this.job=job;
    }

    public int getJob(){
        return job;
    }

    public void promote(int promotionPoint){
        this.promotionPoint+=promotionPoint;
        job++;
    }
    public void giveBonus(int bonus){
        this.monthlyBonus+=bonus;
    }



    public void setMonthlyPoint(int point){
        if(point>=200){
            while(point>=200){
                promotionPoint++;
                point-=200;
            }
            monthlyBonus=point;

        }
        else if(point >0){
            monthlyBonus=point;
        }
        else{
            while(point<=-200){
                point+=200;
                promotionPoint--;
            }
        }

    }

    public int getPromotionPoint(){
        return promotionPoint;
    }
    public int getMonthlyBonus(){
        return monthlyBonus;

    }
    public String getName(){
        return name;
    }
    public void changeMonth(){
        monthlyBonus=0;
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return this.getName().equals(((Employee) obj).getName());
    }
}
