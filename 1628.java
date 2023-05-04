package org.example;
import java.util.*;

public class Main {
    public static int not_single = 0;
    public static int single = 0;
    public static class aboba{
        int parent;
        TreeSet<Integer> childrens;
        aboba(int parent){
            this.parent = parent;

        }

    }
    public static TreeSet<Integer> counter(TreeSet<Integer> childrens, int amount){ // pomenyala
        TreeSet<Integer> singles = new TreeSet<>();
        int prev = 0;
        int cnt_tmp = 0;
        for (int curr : childrens){
            if (curr - prev > 2){
                cnt_tmp += 1;
                not_single += 1;
            } else if (curr - prev == 2) {
                singles.add(curr - 1);
            }
            prev = curr;
        }
        if (amount - prev > 1) {
            cnt_tmp+=1;
            not_single += 1;
        }
        else if (amount - prev == 1) {
            singles.add(amount);
        }
        return singles;

    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int m = sc.nextInt();
        int n = sc.nextInt();
        int k = sc.nextInt();
        sc.nextLine();
        List<aboba> rows = new ArrayList<>();
        while (rows.size() < m)
            rows.add(null);
        List<aboba> cols = new ArrayList<>();
        while (cols.size() < n)
            cols.add(null);
        int[][] mass = new int[k][2] ;
        for (int i = 0; i < k; i++){
            int x = sc.nextInt();
            int y = sc.nextInt();
            mass[i][0] = x;
            mass[i][1] = y;
        }
        for (int i = 0; i < k; i++){
            int x = mass[i][0];
            int y = mass[i][1];
            aboba abobus;
            if (rows.get(x - 1) == null){
                abobus = new aboba(x - 1);
            }
            else{
                abobus = rows.get(x - 1);
            }
            if (abobus.childrens != null) {
                abobus.childrens.add(y);
            }
            else{
                TreeSet<Integer> deti = new TreeSet<>();
                deti.add(y);
                abobus.childrens = deti;
            }
            rows.set(x - 1, abobus);
            if (cols.get(y - 1) == null){
                abobus = new aboba(y - 1);
            }
            else{
                abobus = cols.get(y - 1);
            }
            if (abobus.childrens != null)
                abobus.childrens.add(x);
            else{
                TreeSet<Integer> deti = new TreeSet<>();
                deti.add(x);
                abobus.childrens = deti;
            }
            cols.set(y - 1, abobus);
        }

        for (int i = 0; i < rows.size(); i++){
            if (rows.get(i) == null){
                aboba abobus = new aboba(i);
                TreeSet<Integer> deti = new TreeSet<>();
                deti.add(0);
                deti.add(n + 1);
                abobus.childrens = counter(deti, n);
                rows.set(i, abobus);
            }
            else{
                rows.get(i).childrens = counter(rows.get(i).childrens, n);
            }
        }
        for (int i = 0; i < cols.size(); i++){
            if (cols.get(i) == null){
                aboba abobus = new aboba(i);
                TreeSet<Integer> deti = new TreeSet<>();
                deti.add(0);
                deti.add(m + 1);
                abobus.childrens = counter(deti, m);
                cols.set(i, abobus);
            }
            else{
                cols.get(i).childrens = counter(cols.get(i).childrens, m);
            }
        }

        for (int i = 0; i < m; i++){
            aboba abobus_row = rows.get(i);
            if (abobus_row.childrens.size() > 0){
                for (int child : abobus_row.childrens){ //proverka kolonok
                    if (cols.get(child - 1).childrens.contains(abobus_row.parent + 1)){
                        single += 1;
                    }
                }
            }
        }
        System.out.println(not_single + single);
    }
}
