import java.util.LinkedList;
import java.util.List;

public class Branch {

    private int courierSize;
    private int cashierSize;
    private int cookSize;
    private Employee manager;
    private HashTable<Employee> employees;
    private LinkedList<Employee> promotableCooks;
    private Employee removableCashier,removableCourier,removableCook,removableManager;
    private Employee promotableCashier;
    private int monthlyBonus,totalBonus;
    private String City,District;
    StringBuilder output=OutputGiver.output;
    Branch(String City,String District){
        employees=new HashTable<>();
        courierSize=0;
        cashierSize=0;
        cookSize=0;
        monthlyBonus=0;
        totalBonus=0;
        promotableCooks=new LinkedList<>();
        this.City=City;
        this.District=District;
    }

    public void addEmployee(Employee e){
        if(employees.contains(e))
            output.append("Existing employee cannot be added again.\n");
        else {
            employees.insert(e);
            switch (e.getJob()) {
                case 0 -> addCourier(e);
                case 1 -> addCashier(e);
                case 2 -> addCook(e);
                case 3 -> manager = e;
            }
        }
    }

    public void removeEmployee(Employee e){
        if(removable(e)) {
            switch (e.getJob()) {

                case 0 -> {
                    removeCourier(e);
                }
                case 1 -> {
                    removeCashier(e);
                }
                case 2 -> {
                    removeCook(e);
                }
                case 3 -> {
                    removeManager(e);
                }
            }
        }

    }

    public void leftEmployee(Employee e){
            switch (e.getJob()) {

                case 0 -> {
                    if(courierSize>1) {
                        courierSize--;
                        employees.remove(e);
                        output.append(e.getName());output.append(" is leaving from branch: ");output.append(this.getDistrict());
                        output.append(".\n");
                    }
                    else{
                        if(!removable(e)) {
                            this.monthlyBonus += 200;
                            this.totalBonus += 200;
                        }

                    }

                }
                case 1 -> {
                    if(cashierSize>1) {
                        cashierSize--;
                        employees.remove(e);
                        output.append(e.getName());output.append(" is leaving from branch: ");output.append(this.getDistrict());
                        output.append(".\n");
                    }
                    else{
                        if(!removable(e)) {
                            this.monthlyBonus += 200;
                            this.totalBonus += 200;
                        }

                    }
                }
                case 2 -> {
                    if(cookSize>1) {
                        cookSize--;
                        employees.remove(e);
                        output.append(e.getName());output.append(" is leaving from branch: ");output.append(this.getDistrict());
                        output.append(".\n");
                        promotableCooks.remove(e);
                    }
                    else{
                        if(!removable(e)) {
                            this.monthlyBonus += 200;
                            this.totalBonus += 200;
                        }

                    }
                }
                case 3 -> {
                    if(promotableCooks.size()>0 &&cookSize>1 ) {
                        output.append(e.getName());output.append(" is leaving from branch: ");output.append(this.getDistrict());
                        output.append(".\n");

                        manager = e;
                        employees.remove(e);
                        cookSize--;
                        promotableCooks.get(0).promote(-10);
                        manager = promotableCooks.get(0);
                        promotableCooks.remove(0);

                        output.append(manager.getName());output.append(" is promoted from Cook to Manager.");output.append("\n");
                    }
                    else{
                        if(!removable(e)) {
                            this.monthlyBonus += 200;
                            this.totalBonus += 200;
                        }
                    }
                }
            }
    }

    private boolean removable(Employee e){
        int promotionPoint=e.getPromotionPoint();
        return promotionPoint <= -5;
    }

    private void removeCourier(Employee e){
        if(courierSize>1){
            courierSize--;
            employees.remove(e);
            output.append(e.getName());output.append(" is dismissed from branch: ");output.append(getDistrict());
            output.append(".\n");
        }
        else{
            removableCourier=e;
        }
    }
    private void removeCashier(Employee e){
        if(cashierSize>1){
            cashierSize--;
            employees.remove(e);
            output.append(e.getName());output.append(" is dismissed from branch: ");output.append(getDistrict());
            output.append(".\n");
        }
        else{
            removableCashier=e;
        }
    }
    private void removeCook(Employee e){
        promotableCooks.remove(e);
        if(cookSize>1){
            cookSize--;
            employees.remove(e);
            output.append(e.getName());output.append(" is dismissed from branch: ");output.append(getDistrict());
            output.append(".\n");
        }
        else{
            removableCook=e;
        }
    }
    private void removeManager(Employee e){
        if(promotableCooks.size()>0 && cookSize>1){

            output.append(e.getName());output.append(" is dismissed from branch: ");output.append(getDistrict());
            output.append(".\n");

            manager=e;
            cookSize--;
            employees.remove(e);
            manager=promotableCooks.get(0);
            promotableCooks.remove(0);
            removableManager=null;
            manager.promote(-10);


            output.append(manager.getName());output.append(" is promoted from Cook to Manager.");output.append("\n");

        }
        else{
            removableManager=e;
        }
    }

    private void addCourier(Employee e){
        employees.insert(e);
        courierSize++;
        if(removableCourier!=null){
            removeCourier(e);
            removableCourier=null;
        }
    }
    private void addCashier(Employee e){
        employees.insert(e);
        cashierSize++;
        if(removableCashier!=null){
            removeEmployee(removableCashier);
            removableCashier=null;
        }
        if(promotableCashier!=null){
            promote(promotableCashier);
            promotableCashier=null;
        }
    }
    private void addCook(Employee e){
        employees.insert(e);
        cookSize++;
        if(removableCook!=null){
            removeCook(e);
            removableCook=null;
        }
        if(promotableCooks.size()>0){
            promoteCook(promotableCooks.get(0));
        }
    }

    public void setMonthlyScore(Employee e , int monthlyPoint){
        e.setMonthlyPoint(monthlyPoint);
        monthlyBonus+=e.getMonthlyBonus();
        totalBonus+=e.getMonthlyBonus();

        int promotionPoint=e.getPromotionPoint();
        if(promotionPoint>0)
            promote(e);
        else
            removeEmployee(e);
    }

    public Employee getEmployee(String name){
        return employees.get(name);
    }
    public int getMonthlyBonus(){
        return monthlyBonus;
    }
    public int getTotalBonus(){
        return totalBonus;
    }
    public String getDistrict(){
        return District;
    }
    public String getManager(){
        return manager.getName();
    }


    private void promote(Employee e){
        switch(e.getJob()){
            case 1->promoteCashier(e);
            case 2->promoteCook(e);
        }
    }


    private void promoteCashier(Employee e){
        int promotionPoint=e.getPromotionPoint();
        if(promotionPoint>=3){
            if(cashierSize>1){

                cashierSize--;
                addCook(e);
                e.promote(-3);
                if(promotionPoint>=10)
                    promote(e);

                output.append(e.getName());output.append(" is promoted from Cashier to Cook.");
                output.append("\n");

            }
            else{
                promotableCashier=e;
            }
        }
    }

    private void promoteCook(Employee e){

        int promotionPoint=e.getPromotionPoint();
        if(promotionPoint>=10){

            if(!promotableCooks.contains(e)){
                promotableCooks.add(e);
            }

            if(removableManager!=null){
                removeManager(manager);
            }



        }
        else{
            promotableCooks.remove(e);
        }
    }


    public void changeMonth(){
        monthlyBonus=0;
        for(List<Employee> employeeList:employees.getLists() ){
            for(Employee e :employeeList){
                e.changeMonth();
            }
        }
    }

    @Override
    public int hashCode() {
        return (City+District).hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return this.getDistrict().equals(((Branch) obj).getDistrict());
    }
}
