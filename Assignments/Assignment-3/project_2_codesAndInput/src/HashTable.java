import java.util.LinkedList;
import java.util.List;

public class HashTable<Type>{

    private static final int DEFAULTSIZE=101;
    private List<Type>[] lists;
    private int currentSize;

    HashTable(){
        this(DEFAULTSIZE);
    }
    HashTable(int size){
        lists=new List[nextPrime(size)];
        for(int i=0;i<lists.length;i++){
            lists[i]=new LinkedList<>();
        }
        currentSize=0;
    }



    private int hash(Type value){
        int hashCode=value.hashCode();
        hashCode=hashCode% lists.length;
        if(hashCode<0){
            hashCode+= lists.length;;
        }
        return hashCode;
    }


    public void insert(Type data){
        List<Type> list=lists[hash(data)];
        if(!list.contains(data)){
            list.add(data);
            currentSize++;
            if(currentSize> lists.length){
                rehash();
            }
        }
    }

    public Type get(String data){
        int hashCode=data.hashCode()%lists.length;
        if(hashCode<0)
            hashCode+= lists.length;
        List<Type> list=lists[hashCode];
        for(Type type:list){
            if(type.hashCode()==data.hashCode())
                return type;
        }
        return null;
    }


    public void remove(Type data){
        List<Type> list=lists[hash(data)];
        if(list.contains(data)){
            list.remove(data);
            currentSize--;
        }
    }

    public boolean contains(Type data){
        List<Type> list=lists[hash(data)];
        return list.contains(data);
    }

    public void clear(){
        for (List<Type> list : lists) {
            list.clear();
        }
        currentSize=0;
    }
    private void rehash(){
        List<Type>[] oldlist=lists;
        lists=new List[nextPrime(lists.length*2)];
        for(int i=0;i< lists.length;i++){
            lists[i]=new LinkedList<>();
        }
        currentSize=0;
        for(List<Type> list:oldlist){
            for(Type item:list){
                insert(item);
            }
        }
    }


    private boolean isPrime(int n){
        if(n==2|| n==3)
            return true;
        if(n==1|| n%2==0)
            return false;
        for(int i=3;i*i<=n;i+=2){
            if(n%i==0)
                return false;
        }
        return true;
    }

    private int nextPrime(int number){
        if(number%2==0){number++;}
        while(!isPrime(number)){
            number+=2;
        }
        return number;
    }

    public List<Type>[] getLists(){
        return lists;
    }

}
