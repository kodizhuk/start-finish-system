package kodizhuk.sflistener;

import android.bluetooth.le.ScanResult;
import android.util.Log;
import android.util.Xml;

import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Created by Petro on 21.08.2017.
 */

public class Data {
    private final static String TAG = "Data";

    private final static int  ADV_PACKET_UUID_LSB = 5;
    private final static int ADV_PACKET_UUID_MSB = 6;

    private final static int ADV_PACKET_TRY_NUM_B1 = 7;
    private final static int ADV_PACKET_TRY_NUM_B0 = 8;

    private final static int ADV_PACKET_SKIER_NUM = 9;
    private final static int  ADV_PACKET_STATUS_BYTE = 10;

    private final static int ADV_PACKET_TIME_START_B3 = 11;
    private final static int ADV_PACKET_TIME_START_B2 = 12;
    private final static int ADV_PACKET_TIME_START_B1 = 13;
    private final static int ADV_PACKET_TIME_START_B0 = 14;

    private final static int ADV_PACKET_TIME_FINISH_B3 = 15;
    private final static int ADV_PACKET_TIME_FINISH_B2 = 16;
    private final static int ADV_PACKET_TIME_FINISH_B1 = 17;
    private final static int ADV_PACKET_TIME_FINISH_B0 = 18;

    private final static int ADV_PACKET_TIME_RESULT_B3 = 19;
    private final static int ADV_PACKET_TIME_RESULT_B2 = 20;
    private final static int ADV_PACKET_TIME_RESULT_B1 = 21;
    private final static int ADV_PACKET_TIME_RESULT_B0 = 22;

    private final static int ADV_PACKET_TXT_START_B3 = 23;
    private final static int ADV_PACKET_TXT_START_B2 = 24;
    private final static int ADV_PACKET_TXT_START_B1 = 25;
    private final static int ADV_PACKET_TXT_START_B0 = 26;

    Buffer buffer = new Buffer();
    StringBuilder builder = new StringBuilder();

    public void addData(ScanResult data){
//        Log.d(TAG,"add data");

        /*add to cyclic buffer*/
        //перевірити чи такий елемент вже існує, якщо існує - то нічого не робити, інакше - закинути в буффер
        buffer.add(data.getScanRecord().getBytes());


//        inData = data.getScanRecord().getBytes();
//        builder.append("0x");
//        for(int i=0; i<28;i++){
//            builder.append(String.format("%02x ",inData[i]));
//        }
//        Log.d(TAG, builder.toString());
    }

    public String getData(){
//        return builder.toString();
        StringBuilder build = new StringBuilder();
        for(int j=0;j<5;j++) {
            byte[] data = buffer.get(j);
            build.append("\n\r0x");
            for (int i = 0; i < 28; i++) {
                build.append(String.format("%02x ", data[i]));
            }
        }
        return build.toString();
    }

    public long getTruNum(int index){
        byte[] data = buffer.get(index);
        long truNum =
                ((data[ADV_PACKET_TRY_NUM_B0] & 0xFF) <<  0) |
                ((data[ADV_PACKET_TRY_NUM_B1] & 0xFF) <<  16) ;

//        Log.d(TAG, "tru num ="+truNum);
        return truNum;
    }
    public int getSkierNum(int index){
        byte[] data = buffer.get(index);
         int skierNum =
                ((data[ADV_PACKET_SKIER_NUM] & 0xFF) <<  0) ;

//        Log.d(TAG, "skier num ="+skierNum);
        return skierNum;
    }
    public int getStatusByte(int index){
        byte[] data = buffer.get(index);
        int statusByte =
                ((data[ADV_PACKET_STATUS_BYTE] & 0xFF) <<  0) ;

//        Log.d(TAG, "status byte ="+statusByte);
        return statusByte;
    }
    public int[] getTimeStart(int index){
        byte[] data = buffer.get(index);
        int[] time = new int[4];
        time[0] = ((data[ADV_PACKET_TIME_START_B3] & 0xFF) <<  0) ;
        time[1] = ((data[ADV_PACKET_TIME_START_B2] & 0xFF) <<  0) ;
        time[2] = ((data[ADV_PACKET_TIME_START_B1] & 0xFF) <<  0) ;
        time[3] = ((data[ADV_PACKET_TIME_START_B0] & 0xFF) <<  0) ;
//        Log.d(TAG, "start "+time[0]+":"+time[1]+":"+time[2]+":"+time[3]);
        return time;
    }
    public int[] getTimeFinish(int index){
        byte[] data = buffer.get(index);
        int[] time = new int[4];
        time[0] = ((data[ADV_PACKET_TIME_FINISH_B3] & 0xFF) <<  0) ;
        time[1] = ((data[ADV_PACKET_TIME_FINISH_B2] & 0xFF) <<  0) ;
        time[2] = ((data[ADV_PACKET_TIME_FINISH_B1] & 0xFF) <<  0) ;
        time[3] = ((data[ADV_PACKET_TIME_FINISH_B0] & 0xFF) <<  0) ;
//        Log.d(TAG, "finish "+time[0]+":"+time[1]+":"+time[2]+":"+time[3]);
        return time;
    }
    public int[] getTimeResult(int index){
        byte[] data = buffer.get(index);
        int[] time = new int[4];
        time[0] = ((data[ADV_PACKET_TIME_RESULT_B3] & 0xFF) <<  0) ;
        time[1] = ((data[ADV_PACKET_TIME_RESULT_B2] & 0xFF) <<  0) ;
        time[2] = ((data[ADV_PACKET_TIME_RESULT_B1] & 0xFF) <<  0) ;
        time[3] = ((data[ADV_PACKET_TIME_RESULT_B0] & 0xFF) <<  0) ;
//        Log.d(TAG, "result "+time[0]+":"+time[1]+":"+time[2]+":"+time[3]);
        return time;
    }
    public String getTxt(int index){
        byte[] txtByte = Arrays.copyOfRange(buffer.get(index),
                ADV_PACKET_TXT_START_B3,ADV_PACKET_TXT_START_B0+1);
        String txt  = new String(txtByte);
//        Log.d(TAG,"txt-"+txt);
        return txt;
    }


    private class Buffer{
        private final int SIZE_BUFFER = 5;
        private final int NUM_DATA = 28;

        private int index = 0;
        private boolean dataExist = false;

        byte[][] buffer = new byte[SIZE_BUFFER][NUM_DATA];

        public void add(byte[] inData){
            if(inData.length >= NUM_DATA){
                /*check are avalable*/
                dataExist = false;
                for(int i=0;i<SIZE_BUFFER;i++){
                    if(Arrays.equals(inData,buffer[i])==true){
                        dataExist = true;
                    }
                }

                if(dataExist == false) {
                    if (index + 1 < SIZE_BUFFER) {
//                        Log.d(TAG,"index="+index);
//                    Log.d(TAG,"data-"+inData);
                        buffer[index] = Arrays.copyOf(inData, inData.length);
                        index++;
                    } else {
                        /*delete the oldest data*/
                        for (int i = 0; i < SIZE_BUFFER - 1; i++) {
                            buffer[i] = Arrays.copyOf(buffer[i+1], buffer[i+1].length);
                        }
//                        Log.d(TAG,"index="+index);
//                    Log.d(TAG,"data-"+inData);
                        /*add new data*/
                        buffer[index] = Arrays.copyOf(inData, inData.length);
                    }
                }
            }
        }

        public byte[] get(int num){
            if(num < SIZE_BUFFER) {
//                Log.d(TAG, "get index "+num);
//                StringBuilder b = new StringBuilder();
//                b.append("0x");
//                for (int i = 0; i < 28; i++) {
//                    b.append(String.format("%02x ", buffer[num][i]));
//                }
//                Log.d(TAG,"data-"+b.toString());

                return buffer[num];
            }else{
//                Log.d(TAG, "error or empty "+num);
                byte[] empty = new byte[28];
                return empty;
            }
        }

        public int getSizeBuffer(){
            return SIZE_BUFFER;
        }
    }
}
