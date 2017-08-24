package comkodizhuk.vk.viewpager;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.content.Context;
import android.content.Intent;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import static comkodizhuk.vk.viewpager.R.id.none;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter adapter;
    private BluetoothLeScanner mBluetoothLeScanner;
    private final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ViewPager viewPager = (ViewPager)findViewById(R.id.viewPager);
        viewPager.setAdapter(new CustomPageAdapter(this));

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

        mBluetoothLeScanner.startScan(new CustomPageAdapter(this).mScanCallback);
    }

    @Override
    protected void onResume() {
        mBluetoothLeScanner.startScan(new CustomPageAdapter(this).mScanCallback);
        Log.d(TAG, "start ble scan");
        super.onResume();
    }

    @Override
    protected void onPause() {
        mBluetoothLeScanner.startScan(new CustomPageAdapter(this).mScanCallback);
        Log.d(TAG, "stop ble scan");
        super.onPause();
    }
}
