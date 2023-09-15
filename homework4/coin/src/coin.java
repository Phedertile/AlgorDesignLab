import java.util.ArrayList;

public class coin {
    private int[] num;
    private int n;
    private int sum;
    private long[][] mem;
    private int total;
    private ArrayList<ArrayList<String>> result;


    public coin (int[] num, int n, int sum){
        this.num = num.clone();

        this.n = n;

        this.sum = sum;

        this.result = new ArrayList<>();

        this.mem = new long[n+1][sum+1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= sum; j++) {
                mem[i][j] = -1;
            }
        }

       
        this.total = sum;
    }
      
    
    /* 
    ------without dynamic table approach-------
    */ 

    // public int entry(){
    //     return sol(n, sum);
    // }

    // private int sol(int n, int sum){
        
    //     // System.out.printf("n : %d, sum : %d ", n, sum);
    //     // System.out.println();
    //     // can't add more coin
    //     if(sum < 0){
    //         // System.out.println();
    //         return 0;
    //     }

    //     // finish and get 1 more way
    //     if(sum == 0){
    //         // System.out.println();
    //         return 1;
    //     }

    //     // no more coin but sum is still not = 0
    //     // no solution
    //     if(n <= 0){
    //         // System.out.println();
    //         return 0;
    //     }

    //     return sol(n, sum-num[n-1]) + sol(n-1, sum);
    // }

    /*
    ------------with dynamic table------------
     */

    public long entry2(){
        ArrayList<String> all = new ArrayList<>();
        return sol2(n, sum, all);
    }

    private long sol2(int n, int sum, ArrayList<String> subset){
        
        // finish and get 1 more way
        if(sum == 0){

            ArrayList<String> toAdd = new ArrayList<>();
            for (String i : subset) {
                toAdd.add(i);
            }
            // System.out.println(toAdd.toString());
            result.add(toAdd);
            return mem[n][sum] = 1;
        }

        // can't add more coin
        if(sum < 0){

            return 0;
        }
        
        // no more coin but sum is still not = 0
        // no solution
        if(n <= 0){
            
            return 0;
        }

        if(mem[n][sum] != -1){
            
            // เก็บตกบางเซตที่อาจไม่ได้เก็บ
            ArrayList<String> toAdd = new ArrayList<>();
            int time = sum / num[n-1];
            int sub_sum = 0;
            for (int i = 0; i < time; i++) {
                subset.add(Integer.toString(num[n-1]));
            }
            for (String i : subset) {
                toAdd.add(i);
                sub_sum += Integer.parseInt(i);
            }

            // อาจมีบางเซตที่ค่าเกินเพราะ if นี้ไม่ได้เช็คว่า sum == 0 เลยต้องเช็คก่อนที่จะใส่เซตนี้เข้าไป
            if(sub_sum == total ){

                result.add(toAdd);
            }

            return mem[n][sum];
        }

        // copy ค่าของเซตก่อนที่จะใส่เลขที่เลือกเข้าไป
        ArrayList<String> temp = new ArrayList<>(subset);
    
        // insert selected coin 
        subset.add(Integer.toString(num[n-1]));

        // select this coin
        long x = sol2(n, sum-num[n-1], subset);

        // not select this coin and send temp as the subset before changing
        long y = sol2(n-1, sum, temp);

        return mem[n][sum] = x+y;
    }

    public void memTostring(){
        for (int i = 0; i <= sum; i++) {
            System.out.print(i + "\t");
        }
        System.out.println();
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= sum; j++) {
                System.out.print(mem[i][j] + "\t");
            }
            System.out.println();
        }
    }

    public void combinationsTostring(){
        for (int i = 0; i < result.size(); i++) {
            System.out.print(result.get(i).toString());
            System.out.println();
        }
    }
}
