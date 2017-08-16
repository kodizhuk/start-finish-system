package kodizhuk.sflistener;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
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
  
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    private SectionsPagerAdapter mSectionsPagerAdapter;
    private ViewPager mViewPager;

    private BluetoothAdapter adapter;
    private BluetoothLeScanner mBluetoothLeScanner;
    private Handler mHandler = new Handler();

    private ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            super.onScanResult(callbackType, result);
            BluetoothDevice device = adapter.getRemoteDevice(result.getDevice().getAddress());
//            mText.setText("name -"+device.getName());
            Log.i("callbackType", String.valueOf(callbackType));
            Log.i("result", result.toString());
            if( result == null
                    || result.getDevice() == null
                    || TextUtils.isEmpty(result.getDevice().getName()) )
                return;

            StringBuilder builder = new StringBuilder( result.getDevice().getName() );

            builder.append("\n").append(new String(result.getScanRecord().getBytes()));

            //mText.setText(builder.toString());
        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {
            super.onBatchScanResults(results);
            Log.e("LO", "Scan result on butch");
            //mText.setText("on batch results");
        }

        @Override
        public void onScanFailed(int errorCode) {
            Log.e( "LO", "Discovery onScanFailed: " + errorCode );
            super.onScanFailed(errorCode);
            //mText.setText("scan filed code-"+errorCode);
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.container);
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
    }

    @Override
    protected void onResume() {
        mBluetoothLeScanner.startScan(mScanCallback);
        super.onResume();
    }

    @Override
    protected void onPause() {
        mBluetoothLeScanner.stopScan(mScanCallback);
        super.onPause();
    }

}
