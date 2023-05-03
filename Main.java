package org.example;
import java.util.*;
import java.util.regex.Pattern;

public class Main {
    public static class directory{
        String parent;
        LinkedList<directory> childrens;
        directory(String parent){
            this.parent = parent;
        }
    }
    public static directory set_dir(String parent, LinkedList<directory> childrens){
        directory res_dir = new directory(parent);
        ListIterator<directory> iterator = childrens.listIterator();
        int flag = 0;
        while(iterator.hasNext()){
            directory cur_dir = iterator.next();
            int comparator = cur_dir.parent.compareTo(parent);
            if (comparator > 0){
                iterator.previous();
                iterator.add(res_dir);
                flag = 1;
                break;
            }
            else if (comparator == 0){
                res_dir = cur_dir;
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            childrens.add(res_dir);
        }

        return res_dir;
    }

    public static void split_and_add(String path, LinkedList<directory> childrens){
        String sep = "\\";
        path = path.replaceAll(Pattern.quote(sep), "\\\\");
        //System.out.println(path);
        String [] dirs = path.split("\\\\", 2);
        if (dirs.length == 1){
            set_dir(path, childrens);
        }
        else{
            String first = dirs[0];
            String second = dirs[1];

            directory to_add = set_dir(first, childrens);
            if (to_add.childrens == null){
                to_add.childrens = new LinkedList<directory>();
            }
            split_and_add(second, to_add.childrens);
        }
    }
    public static void printer(int spaces, LinkedList<directory> childrens){
        if (childrens != null){
         for (directory child : childrens){
             for (int i = 0; i < spaces; i++){
                 System.out.append(" ");
             }
             System.out.println(child.parent);
             printer(spaces + 1, child.childrens);
         }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        LinkedList<directory> childrens = new LinkedList<directory>();
        sc.nextLine();
        for (int i = 0; i < n; i++){
            String path = sc.nextLine();
            split_and_add(path, childrens);
        }
        printer(0, childrens);
    }
}