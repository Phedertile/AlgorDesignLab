public class sol2 {
    private String text;
    private int dist;
    private int[] g_is_available;
    private int[] p_is_available;

    public sol2(String text, int k){
        this.text = text;
        this.dist = k;
        g_is_available = new int[text.length()];
        p_is_available = new int[text.length()];
        for (int i = 0; i < text.length(); i++) {
            if(text.charAt(i) == 'G'){
                g_is_available[i] = 1;
                p_is_available[i] = -1;
            }else{
                g_is_available[i] = -1;
                p_is_available[i] = 1;
            }
        }
    }

    public int getAllGrab(){
        int co = 0;
        for (int i = 0; i < text.length(); i++) {
            if(text.charAt(i) == 'G'){
                co++;
            }
        }
        return co;
    }
    public int getMaxPassenger(){
        reset();
        int max = 0;

        for (int i = 0; i < text.length(); i++) {
            char character = text.charAt(i);
            int is_available = g_is_available[i];

            if(character == 'G' & is_available == 1){
                int furthest_passenger = getFurthestPassenger(i);
                if(furthest_passenger == -1){
                    continue;
                }

                p_is_available[furthest_passenger] = 0;
                g_is_available[i] = 0;

                max++;
            }
        }
        return max;
    }

    public int getMaxPassengerV2(){
        reset();
        int max = 0;

        for (int i = 0; i < text.length(); i++) {
            char character = text.charAt(i);
            int is_available = g_is_available[i];

            if(character == 'G' & is_available == 1){
                int furthest_passenger = getFurthestPassengerV2(i);
                if(furthest_passenger == -1){
                    continue;
                }

                p_is_available[furthest_passenger] = 0;
                g_is_available[i] = 0;

                max++;
            }
        }
        return max;
    }

    public int getMaxPassengerByNearest(){
        reset();
        int max = 0;

        for (int i = 0; i < text.length(); i++) {
            char character = text.charAt(i);
            int is_available = g_is_available[i];

            if(character == 'G' & is_available == 1){
                int Nearest_passenger = getNearestPassenger(i);
                if(Nearest_passenger == -1){
                    continue;
                }

                p_is_available[Nearest_passenger] = 0;
                g_is_available[i] = 0;

                max++;
            }
        }
        return max;
    }

    private int getNearestPassenger(int pos){
        // String result = (time < 18) ? "Good day." : "Good evening.";
        int left_bound = (pos - dist < 0) ? 0 : pos - dist;
        int right_bound = (pos + dist > text.length()-1) ? text.length()-1 : pos + dist;
        int interval = right_bound - left_bound + 1;
        int curr_left = (pos-1 < left_bound) ? left_bound : pos-1;
        int curr_right = (pos+1 > right_bound) ? right_bound : pos+1;
        int i = 1;
        while(curr_left >= left_bound || curr_right <= right_bound){
            // System.out.println("left : " + curr_left);
            // System.out.println("right : " + curr_right);
            if(i % 2 == 1 && curr_left >= left_bound){

                if(!isGrab(curr_left)){
                    if(p_is_available[curr_left] == 1){
                        p_is_available[curr_left] = 0;
                        return curr_left;
                    }
                    
                }
                curr_left--;
            }else if(i % 2 == 0 && curr_right <= right_bound){

                if(!isGrab(curr_right)){
                    if(p_is_available[curr_right] == 1){
                        p_is_available[curr_right] = 0;
                        return curr_right;
                    }
                    
                }
                curr_right++;
            }
            i++;
        }
       
        return -1;
    }

    private int getFurthestPassenger(int pos){
        // String result = (time < 18) ? "Good day." : "Good evening.";
        int left_bound = (pos - dist < 0) ? 0 : pos - dist;
        int right_bound = (pos + dist > text.length()-1) ? text.length()-1 : pos + dist;
        int interval = right_bound - left_bound + 1;

        for (int i = left_bound; i <= right_bound; i++) {
            
             if(!isGrab(i)){
                if(p_is_available[i] == 1){
                    p_is_available[i] = 0;
                    return i;
                }
            }
        }
        return -1;
    }

    private int getFurthestPassengerV2(int pos){
        // String result = (time < 18) ? "Good day." : "Good evening.";
        int left_bound = (pos - dist < 0) ? 0 : pos - dist;
        int right_bound = (pos + dist > text.length()-1) ? text.length()-1 : pos + dist;
        int interval = right_bound - left_bound + 1;

        int curr_left = left_bound;
        int curr_right = right_bound;
        int i = 1;

        while(curr_left < pos || curr_right > pos){
            // System.out.println("left : " + curr_left);
            // System.out.println("right : " + curr_right);
            if(i % 2 == 1 && curr_left >= left_bound & curr_left < pos){

                if(!isGrab(curr_left)){
                    if(p_is_available[curr_left] == 1){
                        p_is_available[curr_left] = 0;
                        return curr_left;
                    }
                    
                }
                curr_left++;
            }else if(i % 2 == 0 && curr_right <= right_bound & curr_right > pos){

                if(!isGrab(curr_right)){
                    if(p_is_available[curr_right] == 1){
                        p_is_available[curr_right] = 0;
                        return curr_right;
                    }
                    
                }
                curr_right--;
            }
            i++;
        }
        return -1;
    }

    private boolean isGrab(int i){
        if(text.charAt(i) == 'G'){
            return true;
        }
        return false;
    }

    private void reset(){
        for (int i = 0; i < g_is_available.length; i++) {
            if(g_is_available[i] == 0){
                g_is_available[i] = 1;
            }
            if(p_is_available[i] == 0){
                p_is_available[i] = 1;
            }
        }
    }
}
