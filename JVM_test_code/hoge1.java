public class hoge1 implements Runnable{
    private int x,y;
    
    public hoge1(int sleep_time_ms,int bit_num){
        x = sleep_time_ms;
        y = bit_num;
    }
    
    public static void main(String[] args){
        
        hoge1 LED1 = new hoge1(40,7);       // PIO0_7
        hoge1 LED2 = new hoge1(1000,16);    // PIO0_16
        
        Thread th1 = new Thread(LED1);
        Thread th2 = new Thread(LED2);
        
        th1.start();
        th2.start();
    }
    
    public void run(){
        int time = x, port_bit=y;
        while(true){
            try{
                Thread.sleep(time);
            }catch(Exception e){}
            
            lpc800.portWrite(port_bit,1);
            System.out.println("LED_on");
            
            try{
                Thread.sleep(time);
            }catch(Exception e){}
            
            lpc800.portWrite(port_bit,0);
            System.out.println("LED_off");
        }
    }
}


