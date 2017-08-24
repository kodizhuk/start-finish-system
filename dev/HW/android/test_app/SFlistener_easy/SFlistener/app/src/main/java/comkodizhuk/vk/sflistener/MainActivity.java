package comkodizhuk.vk.sflistener;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";

    TextView textViewId1 ;
    TextView textViewId2 ;
    TextView textViewId3 ;
    TextView textViewId4 ;
    TextView textViewId5 ;

    TextView textViewStart1 ;
    TextView textViewStart2 ;
    TextView textViewStart3 ;
    TextView textViewStart4 ;
    TextView textViewStart5 ;

    TextView textViewFinish1 ;
    TextView textViewFinish2 ;
    TextView textViewFinish3 ;
    TextView textViewFinish4 ;
    TextView textViewFinish5 ;

    TextView textViewResult1;
    TextView textViewResult2;
    TextView textViewResult3;
    TextView textViewResult4;
    TextView textViewResult5;

    private BluetoothAdapter adapter;
    private BluetoothLeScanner mBluetoothLeScanner;
    Data data = new Data();

    public ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            super.onScanResult(callbackType, result);
//            BluetoothDevice device = adapter.getRemoteDevice(result.getDevice().getAddress());
//            mText.setText("name -"+device.getName());
            Log.i("callbackType", String.valueOf(callbackType));
            Log.i("result", result.toString());
            if( result == null
                    || result.getDevice() == null
                    || TextUtils.isEmpty(result.getDevice().getName()) )
                return;

//            StringBuilder builder = new StringBuilder( result.getDevice().getName() );
//
//            builder.append("\n").append(new String(result.getScanRecord().getBytes()));

            data.addData(result);
//            int numIndex = 4;
//
//            long truNum = data.getTruNum(numIndex);
//            int skierNum = data.getSkierNum(numIndex);
//            int statusByte;
//            statusByte = data.getStatusByte(numIndex);
//            int[] timeStart =data.getTimeStart(numIndex);
//            int[] timeFinish = data.getTimeFinish(numIndex);
//            int[] timeResult = data.getTimeResult(numIndex);
//            String txtOut = data.getTxt(numIndex);
//            Log.d(TAG, "tru num ="+truNum);
//            Log.d(TAG, "skier num ="+skierNum);
//            Log.d(TAG, "status byte ="+statusByte);
//            Log.d(TAG, "start "+timeStart[0]+":"+timeStart[1]+":"+timeStart[2]+":"+timeStart[3]);
//            Log.d(TAG, "finish "+timeFinish[0]+":"+timeFinish[1]+":"+timeFinish[2]+":"+timeFinish[3]);
//            Log.d(TAG, "result "+timeResult[0]+":"+timeResult[1]+":"+timeResult[2]+":"+timeResult[3]);
//            Log.d(TAG,"txt-"+txtOut);

            textViewId1.setText(toString().valueOf(data.getSkierNum(0)));
            textViewId2.setText(toString().valueOf(data.getSkierNum(1)));
            textViewId3.setText(toString().valueOf(data.getSkierNum(2)));
            textViewId4.setText(toString().valueOf(data.getSkierNum(3)));
            textViewId5.setText(toString().valueOf(data.getSkierNum(4)));

            int[] time;
            time = data.getTimeStart(0);
            textViewStart1.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeStart(1);
            textViewStart2.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeStart(2);
            textViewStart3.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeStart(3);
            textViewStart4.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeStart(4);
            textViewStart5.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));

            time = data.getTimeFinish(0);
            textViewFinish1.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeFinish(1);
            textViewFinish2.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeFinish(2);
            textViewFinish3.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeFinish(3);
            textViewFinish4.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeFinish(4);
            textViewFinish5.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));

            time = data.getTimeResult(0);
            textViewResult1.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeResult(1);
            textViewResult2.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeResult(2);
            textViewResult3.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeResult(3);
            textViewResult4.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));
            time = data.getTimeResult(4);
            textViewResult5.setText(String.format("%02d:%02d:%02d:%02d",time[0],time[1],time[2],time[3]));

        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {
            super.onBatchScanResults(results);
            Log.e(TAG, "Scan result on butch");
            //mText.setText("on batch results");
        }

        @Override
        public void onScanFailed(int errorCode) {
            Log.e( TAG, "Discovery onScanFailed: " + errorCode );
            super.onScanFailed(errorCode);
            //mText.setText("scan filed code-"+errorCode);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textViewId1 = (TextView)findViewById(R.id.textViewId0);
        textViewId2 = (TextView)findViewById(R.id.textViewId1);
        textViewId3 = (TextView)findViewById(R.id.textViewId2);
        textViewId4 = (TextView)findViewById(R.id.textViewId3);
        textViewId5 = (TextView)findViewById(R.id.textViewId4);

        textViewStart1 = (TextView)findViewById(R.id.textViewStart0);
        textViewStart2 = (TextView)findViewById(R.id.textViewStart1);
        textViewStart3 = (TextView)findViewById(R.id.textViewStart2);
        textViewStart4 = (TextView)findViewById(R.id.textViewStart3);
        textViewStart5 = (TextView)findViewById(R.id.textViewStart4);

        textViewFinish1 = (TextView)findViewById(R.id.textViewFinish0);
        textViewFinish2 = (TextView)findViewById(R.id.textViewFinish1);
        textViewFinish3 = (TextView)findViewById(R.id.textViewFinish2);
        textViewFinish4 = (TextView)findViewById(R.id.textViewFinish3);
        textViewFinish5 = (TextView)findViewById(R.id.textViewFinish4);

        textViewResult1 = (TextView)findViewById(R.id.textViewResult0);
        textViewResult2 = (TextView)findViewById(R.id.textViewResult1);
        textViewResult3 = (TextView)findViewById(R.id.textViewResult2);
        textViewResult4 = (TextView)findViewById(R.id.textViewResult3);
        textViewResult5 = (TextView)findViewById(R.id.textViewResult4);

        /*start bluetooth*/
        BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        if (bluetoothManager == null){
            //Handle this issue. Report to the user that the device does not support BLE
        } else {
            adapter = bluetoothManager.getAdapter();
        }

        if(adapter != null && !adapter.isEnabled()){
            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(intent, 1);
        }else{
            Toast.makeText( this, "BLE on", Toast.LENGTH_SHORT ).show();
            //do BLE stuff
        }
        mBluetoothLeScanner = adapter.getBluetoothLeScanner();
        if( !adapter.isMultipleAdvertisementSupported() ) {
            Toast.makeText( this, "Multiple advertisement not supported", Toast.LENGTH_SHORT ).show();
        }
    }

    @Override
    protected void onResume() {
        mBluetoothLeScanner.startScan(mScanCallback);
        Log.d(TAG, "start ble scan");
        super.onResume();
    }

    @Override
    protected void onPause() {
        mBluetoothLeScanner.stopScan(mScanCallback);
        Log.d(TAG, "stop ble scan");
        super.onPause();
    }
}
