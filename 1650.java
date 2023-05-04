//1650 спизженно (рефактор есть)
package org.example;
import java.io.*;
import java.util.*;
import java.util.Map.Entry;

import static java.util.Arrays.sort;

public class Main {
    public static BufferedReader in;
    public static PrintWriter out;
    public static StringTokenizer st = new StringTokenizer("");

    public static int billion_num = 0;
    public static int city_num = 0;
    public static long[] money;
    public static Map<String, Integer> billioners = new HashMap<>();
    public static Map<String, Integer> cities = new HashMap<>();

    public static int[] destination;

    public static int days;
    public static Trip[] events;
    public static CityDays[] res_cities;
    public static long[] init;
    public static RMQ rmq;
    public static int get_bill_ind(String name) {
        if (!billioners.containsKey(name))
            billioners.put(name, billion_num++);
        return billioners.get(name);
    }

    public static int get_city_ind(String name) {
        if (!cities.containsKey(name))
            cities.put(name, city_num++);
        return cities.get(name);
    }

    public static class Trip {
        int day;
        int bills;
        int dest;

        Trip(int day, int bills, int dest) {
            this.day = day;
            this.bills = bills;
            this.dest = dest;
        }
    }

    public static class CityDays implements Comparable<CityDays> {
        String city;
        int cnt = 0;

        CityDays(String city) {
            this.city = city;
        }

        void increment(int add) {
            cnt += add;
        }

        @Override
        public int compareTo(CityDays item) {
            return city.compareTo(item.city);
        }

        @Override
        public String toString() {
            return city + " " + cnt;
        }
    }

    public static class RMQ {
        int n;
        long[] val;
        int[] ind;

        RMQ(long[] a) {
            n = a.length;
            val = new long [2 * n];
            ind = new int [2 * n];
            for (int i = 0; i < n; i++) {
                val[n + i] = a[i];
                ind[n + i] = i;
            }
            build();
        }

        void build() {
            for (int i = n - 1; i > 0; i--) {
                int lt = 2 * i;
                int rt = lt + 1;
                if (val[lt] > val[rt]) {
                    val[i] = val[lt];
                    ind[i] = ind[lt];
                } else {
                    val[i] = val[rt];
                    ind[i] = ind[rt];
                }
            }
        }

        long get(int ind) {
            return val[n + ind];
        }

        int maxInd() {
            return ind[1];
        }

        boolean unique(int ind) {
            for (int v = (n + ind) >> 1; v > 0; v >>= 1) {
                int lt = 2 * v;
                int rt = lt + 1;
                if (val[lt] == val[rt]) {
                    return false;
                }
            }
            return true;
        }

        void inc(int ind, long add) {
            set(ind, get(ind) + add);
        }

        void set(int i, long nval) {
            int v = n + i;
            val[v] = nval;
            for (v >>= 1; v > 0; v >>= 1) {
                int lt = 2 * v;
                int rt = lt + 1;
                if (val[lt] > val[rt]) {
                    val[v] = val[lt];
                    ind[v] = ind[lt];
                } else {
                    val[v] = val[rt];
                    ind[v] = ind[rt];
                }
            }
        }
    }

    public static String nextToken() throws IOException {
        while (!st.hasMoreTokens())
            st = new StringTokenizer(in.readLine());
        return st.nextToken();
    }

    public static int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public static long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException{
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);

        int BN = nextInt();
        money = new long [BN];
        destination = new int [BN];

        for (int i = 0; i < BN; i++) {
            int bills = get_bill_ind(nextToken());
            int dest = get_city_ind(nextToken());
            long sugar = nextLong();
            money[bills] = sugar;
            destination[bills] = dest;
        }

        days = nextInt();

        int MN = nextInt();
        events = new Trip [MN];
        for (int i = 0; i < MN; i++)
            events[i] = new Trip(nextInt(), get_bill_ind(nextToken()), get_city_ind(nextToken()));

        res_cities = new CityDays[city_num];
        for (Entry<String, Integer> e : cities.entrySet()) {
            res_cities[e.getValue()] = new CityDays(e.getKey());
        }

        init = new long [city_num];
        for (int i = 0; i < BN; i++)
            init[destination[i]] += money[i];
        rmq = new RMQ(init);

        int maxCity;
        int prevDay = 1;
        int curDay = 1;

        for (int i = 0; i < MN;) {
            curDay = events[i].day;
            maxCity = rmq.maxInd();
            if (rmq.unique(maxCity))
                res_cities[maxCity].increment(curDay - prevDay + 1);
            prevDay = curDay + 1;
            while (i < MN && curDay == events[i].day) {
                int bills = events[i].bills;
                int dest = events[i].dest;
                rmq.inc(destination[bills], -money[bills]);
                rmq.inc(dest, money[bills]);
                destination[bills] = dest;
                i++;
            }
        }

        curDay = days;
        maxCity = rmq.maxInd();
        if (rmq.unique(maxCity))
            res_cities[maxCity].increment(curDay - prevDay + 1);
        sort(res_cities);

        for (CityDays city : res_cities)
            if (city.cnt > 0)
                out.println(city);

        out.close();

    }
}
