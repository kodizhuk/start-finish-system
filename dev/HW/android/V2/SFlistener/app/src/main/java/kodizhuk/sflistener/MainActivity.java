package kodizhuk.sflistener;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.AdvertiseData;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
   
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.List;

import static kodizhuk.sflistener.R.id.container;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    private SectionsPagerAdapter mSectionsPagerAdapter;
    private ViewPager mViewPager;

    private BluetoothAdapter adapter;
    private BluetoothLeScanner mBluetoothLeScanner;

    Data data = new Data();

    private ScanCallback mScanCallback = new ScanCallback() {
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
            int numIndex = 4;

            long truNum = data.getTruNum(numIndex);
            int skierNum = data.getSkierNum(numIndex);
            int statusByte;
            statusByte = data.getStatusByte(numIndex);
            int[] timeStart = data.getTimeStart(numIndex);
            int[] timeFinish = data.getTimeFinish(numIndex);
            int[] timeResult = data.getTimeResult(numIndex);
            String txtOut = data.getTxt(numIndex);
//            Log.d(TAG, "tru num ="+truNum);
//            Log.d(TAG, "skier num ="+skierNum);
//            Log.d(TAG, "status byte ="+statusByte);
//            Log.d(TAG, "start "+timeStart[0]+":"+timeStart[1]+":"+timeStart[2]+":"+timeStart[3]);
//            Log.d(TAG, "finish "+timeFinish[0]+":"+timeFinish[1]+":"+timeFinish[2]+":"+timeFinish[3]);
//            Log.d(TAG, "result "+timeResult[0]+":"+timeResult[1]+":"+timeResult[2]+":"+timeResult[3]);
//            Log.d(TAG,"txt-"+txtOut);

            Log.d(TAG,"page - "+mViewPager.getCurrentItem());

            View v = (View)mViewPager.getChildAt(0);
            TextView txt = (TextView)v.findViewById(R.id.section_label);
//            txt.setText(builder.toString());
//            txt.setText(data.getData());
            txt.setText("\ntru num:"+truNum+
                        "\nskier num:"+skierNum+
                        "\nstatusByte:"+statusByte+
                        "\nstart:"+timeStart[0]+":"+timeStart[1]+":"+timeStart[2]+":"+timeStart[3]+
                        "\nfinish:"+timeFinish[0]+":"+timeFinish[1]+":"+timeFinish[2]+":"+timeFinish[3]+
                        "\nresult:"+timeResult[0]+":"+timeResult[1]+":"+timeResult[2]+":"+timeResult[3]+
                        "\ntxt:"+txtOut);
            Log.d(TAG,String.valueOf(mViewPager.getCurrentItem()));
            //Log.d(TAG,builder.toString());
            //mText.setText(builder.toString());
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
        Log.d(TAG, "Create activity");

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(container);
        mViewPager.setAdapter(mSectionsPagerAdapter);

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

//        LayoutInflater ltInflater = getLayoutInflater();
//        RelativeLayout relLayout = (RelativeLayout) findViewById(R.id.fragment_layout);
//        View view = ltInflater.inflate(R.layout.fragment_main, relLayout, false);
//        TextView textView = (TextView) view.findViewById(R.id.start);
//        textView.setText("hello");
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

    public void btnClick(View view) {
        Log.d(TAG, "btn click");
    }
}
