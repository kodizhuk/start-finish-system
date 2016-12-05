package comkodizhuk.vk.v1_noble;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.icu.text.SimpleDateFormat;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.sql.Time;
import java.text.DateFormat;
import java.util.Date;

import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.IDskier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeFinishSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeResultSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeStartSkier;
import static comkodizhuk.vk.v1_noble.ScanActivity.EXTRAS_BLE_ADDRESS;

public class SettingsActivity extends AppCompatActivity {
    private static final String TAG = "MyLogs";

    private static PSoCBleSFsystemService mPSoCBleSFsystemService;
    private static String mDeviceAddress;

    /**
     * This manages the lifecycle of the BLE service.
     * When the service starts we get the service object, initialize the service, and connect.
     */
    public final ServiceConnection mServiceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            Log.i(TAG, "onServiceConnected");
            mPSoCBleSFsystemService = ((PSoCBleSFsystemService.LocalBinder) service).getService();
            if (!mPSoCBleSFsystemService.initialize()) {
                Log.e(TAG, "Unable to initialize Bluetooth");
                finish();
            }
            // Automatically connects to the  database upon successful start-up initialization.
            mPSoCBleSFsystemService.connect(mDeviceAddress);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mPSoCBleSFsystemService = null;
            Log.i(TAG, "onServiceDisConnected");
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        final Intent intent = getIntent();
        mDeviceAddress = intent.getStringExtra(EXTRAS_BLE_ADDRESS);

        // Bind to the BLE service
        Log.i(TAG, "Binding Service");
        Log.w(TAG, "mBle adress: " + mDeviceAddress);

        Intent SFsystemServiceIntent = new Intent(this, PSoCBleSFsystemService.class);
        bindService(SFsystemServiceIntent, mServiceConnection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(mSFsystemUpdateReceiver, makeSFsystemUpdateIntentFilter());
        Log.i(TAG, "On resume");
        if (mPSoCBleSFsystemService != null) {
            final boolean result = mPSoCBleSFsystemService.connect(mDeviceAddress);
            Log.i(TAG, "Connect request result=" + result);
        }


    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mSFsystemUpdateReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Destroy Activity");
        unbindService(mServiceConnection);
        mPSoCBleSFsystemService = null;
    }


    public void onClickSave(View view) {
        Log.i(TAG, " system time" + System.currentTimeMillis() / 1000L);

        long unixTime = System.currentTimeMillis() / 1000L;

        mPSoCBleSFsystemService.setUnixTime(unixTime);
        Toast.makeText(this, "time updated ", Toast.LENGTH_SHORT).show();
    }


    private final BroadcastReceiver mSFsystemUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            switch (action) {
                case PSoCBleSFsystemService.ACTION_CONNECTED:
                    // No need to do anything here. Service discovery is started by the service.
                    Log.i(TAG, "ACTION_CONNECTED");
                    break;
                case PSoCBleSFsystemService.ACTION_DISCONNECTED:
                    Log.i(TAG, "ACTION_DISCONNECTED");
                    mPSoCBleSFsystemService.close();
                    break;
                case PSoCBleSFsystemService.ACTION_DATA_AVAILABLE:
                    Log.i(TAG, "ACTION_DATA_AVAILABLE");
                    break;
            }
        }
    };

    /**
     * This sets up the filter for broadcasts that we want to be notified of.
     * This needs to match the broadcast receiver cases.
     *
     * @return intentFilter
     */
    private static IntentFilter makeSFsystemUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();

        intentFilter.addAction(PSoCBleSFsystemService.ACTION_CONNECTED);
        intentFilter.addAction(PSoCBleSFsystemService.ACTION_DISCONNECTED);
        intentFilter.addAction(PSoCBleSFsystemService.ACTION_DATA_AVAILABLE);

        return intentFilter;
    }

}
