public class App {
    public static void main(String[] args) throws Exception {
        int[] num = {1,2,3};
        int sum = 5;
        coin c = new coin(num, num.length, sum);
        
        System.out.printf("all combinations : " + c.entry2() + "\n");
        c.combinationsTostring();
    }

    
}

//3, 5, 11, 17, 29, 41, 59, 71, 101, 107, 137, 149, 179, 191, 197, 227, 239, 269, 281, 311, 347, 419, 431, 461, 521, 569, 599, 617, 641, 659, 809, 821, 827, 857, 881, 1031, 1049, 1061, 1091, 1151, 1229, 1277, 1289, 1301, 1319, 1427, 1451, 1481, 1487, 1607, 1619, 1667, 1697, 1721, 1787, 1871, 1877, 1931, 1949, 1997, 2027, 2081, 2087, 2111, 2129, 2141, 2237, 2267, 2309, 2339, 2381, 2549, 2591, 2657, 2687, 2711, 2729, 2789, 2801, 2969, 2999, 3119, 3167, 3251, 3257, 3299, 3329, 3359, 3371, 3389, 3461, 3467, 3527, 3539, 3557, 3581, 3671, 3767, 3821, 3851, 3917, 3929, 4001, 4019, 4049, 4091, 4127, 4157, 4217, 4519, 4229, 4241, 4259, 4271, 4337, 4421, 4481, 4517, 4547, 4637, 4649, 4721, 4787, 4799, 4931, 4967, 5009, 5021, 5099, 5231, 5279, 5417, 5441, 5477, 5501, 5519, 5639, 5651, 5657, 5741, 5867, 5879, 6089, 6131, 6197, 6269, 6299, 6359, 6449, 6551, 6569, 6659, 6689, 6701, 6761, 6779, 6791, 6827, 6869, 6947, 6959, 7127, 7211, 7307, 7331, 7349, 7457

/*
{1,1,1,1,1}
{1,1,1,2}
{1,2,2},
{1,1,3}
{2,3}
 */

