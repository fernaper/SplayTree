import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Random;

public class Test {

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        SplayTree<Integer> b = new SplayTree<>();
        SplayTree<Integer> a = new SplayTree<>();
        Random randomGenerator = new Random();
        long  time_start, time_end, total;
        PrintWriter insert = new PrintWriter("insert.txt", "UTF-8");
        PrintWriter search = new PrintWriter("search.txt", "UTF-8");
        PrintWriter remove = new PrintWriter("remove.txt", "UTF-8");
        ArrayList<Integer> l = new ArrayList<>();
        ArrayList<Integer> la = new ArrayList<>();

        for(int i = 0 ; i < 1000; ++i){
            int randomInt = randomGenerator.nextInt(1000);
            l.add(randomInt);
        }

        for(int i = 0 ; i < 1000; ++i){
            int num = l.get(i);
            double resultado;
            time_start = System.nanoTime();
            b.insert(num);
            time_end = System.nanoTime();
            total = time_end - time_start;
            resultado = ((double) total)/1000000;
            System.out.println(resultado);
            insert.println(resultado);
        }
        insert.close();

        for(int i = 0 ; i < 1000; ++i){
            int num = l.get(i);
            double resultado;
            time_start = System.nanoTime();
            b.search(num);
            time_end = System.nanoTime();
            total = (time_end - time_start);
            resultado = ((double) total)/1000000;
            System.out.println(resultado);
            search.println(resultado);
        }
        search.close();

        for(int i = 0 ; i < 1000; ++i){
            int randomInt = randomGenerator.nextInt(50000);
            la.add(randomInt);
        }

        for(int i = 0 ; i < 1000; ++i){
            a.insert(la.get(i));
        }

        for(int i = 0 ; i < 1000; ++i){
            int num = la.get(i);
            double resultado;
            time_start = System.nanoTime();
            a.remove(num);
            time_end = System.nanoTime();
            total = time_end - time_start;
            resultado = ((double) total)/1000000;
            System.out.println(resultado);
            remove.println(resultado);
        }
        remove.close();
    }

}
