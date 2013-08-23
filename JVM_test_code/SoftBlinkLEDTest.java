public class SoftBlinkLEDTest implements Runnable{
    private int x,y;
    
    public SoftBlinkLEDTest(int bit_num, int sleep_time_ms){
        
        x = bit_num;
        y = sleep_time_ms;
       
    }
    
    public static void main(String[] args){
        
        SoftBlinkLEDTest LED1 = new SoftBlinkLEDTest(7, 40);       // PIO0_7, half-cycle = 40msec
        SoftBlinkLEDTest LED2 = new SoftBlinkLEDTest(16, 1000);    // PIO0_16, half-cycle = 1000msec
        
        Thread th1 = new Thread(LED1);
        Thread th2 = new Thread(LED2);
        
        th1.start();
        th2.start();
    }
    
    public void run(){
        
        int port_bit = x, time = y;
        
        while(true){
            try{
                Thread.sleep(time);
            }catch(Exception e){}
            
            lpc800.portWrite(port_bit, 1);
            System.out.println("LED_on");
            
            try{
                Thread.sleep(time);
            }catch(Exception e){}
            
            lpc800.portWrite(port_bit, 0);
            System.out.println("LED_off");
        }
    }
}


