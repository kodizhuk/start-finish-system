package comkodizhuk.vk.v1_noble;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Handler;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import org.w3c.dom.Text;

import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.AdminOnly.ADMIN_NO_ONLY;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.IDskier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.maxSkierOnWay;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.numSkierOnWay;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeFinishSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeResultSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeStartSkier;
import static comkodizhuk.vk.v1_noble.ScanActivity.EXTRAS_BLE_ADDRESS;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MyLogs";
    private static final int HOUR = 0;
    private static final int MIN = 1;
    private static final int SEC = 2;
    private static final int MS = 3;

    private static String mDeviceAddress;
    private static PSoCBleSFsystemService mPSoCBleSFsystemService;

    private static TextView textViewHourStart;
    private static TextView textViewSecStart;
    private static TextView textViewMinStart;
    private static TextView textViewMsStart;
    private static TextView textViewID;

    private static TextView textViewHourFinish;
    private static TextView textViewSecFinish;
    private static TextView textViewMinFinish;
    private static TextView textViewMsFinish;

    private static TextView textViewSecResult;
    private static TextView textViewMinResult;
    private static TextView textViewMsResult;

    private static TextView textViewNumSkier;

    /*for Timer*/
    int currentMs, currentSec, currentMin, currentHour;
    Handler handler = new Handler();

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
        setContentView(R.layout.activity_main);

        textViewMsStart = (TextView) findViewById(R.id.textViewMsStart);
        textViewSecStart = (TextView) findViewById(R.id.textViewSecStart);
        textViewMinStart = (TextView) findViewById(R.id.textViewMinStart);
        textViewHourStart = (TextView) findViewById(R.id.textViewHourStart);

        textViewMsFinish = (TextView) findViewById(R.id.textViewMsFinish);
        textViewSecFinish = (TextView) findViewById(R.id.textViewSecFinish);
        textViewMinFinish = (TextView) findViewById(R.id.textViewMinFinish);
        textViewHourFinish = (TextView) findViewById(R.id.textViewHourFinish);

        textViewMsResult = (TextView) findViewById(R.id.textViewMsResult);
        textViewSecResult = (TextView) findViewById(R.id.textViewSecResult);
        textViewMinResult = (TextView) findViewById(R.id.textViewMinResult);

        textViewID = (TextView) findViewById(R.id.textViewID);
        textViewNumSkier = (TextView)findViewById(R.id.textViewNumSkier);


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
        Log.i(TAG, "User Activity On resume");
        if (mPSoCBleSFsystemService != null) {
            mPSoCBleSFsystemService.connect(mDeviceAddress);
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
        Log.i(TAG, "User Activity Destroy Activity");
        unbindService(mServiceConnection);
        mPSoCBleSFsystemService = null;
        /*stop timer updater*/
        handler.removeCallbacks(updater);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_admin:
                Intent intent = new Intent(MainActivity.this, AdminActivity.class);
                intent.putExtra(EXTRAS_BLE_ADDRESS, mDeviceAddress);
                Toast.makeText(this, "Admin", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
        }

        return super.onOptionsItemSelected(item);
    }


    /**
     * Handle broadcasts from the Car service object. The events are:
     * ACTION_CONNECTED: connected to the car.
     * ACTION_DISCONNECTED: disconnected from the car.
     * ACTION_DATA_AVAILABLE: received data from the car.  This can be a result of a read
     * or notify operation.
     */
    private final BroadcastReceiver mSFsystemUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            switch (action) {
                case PSoCBleSFsystemService.ACTION_CONNECTED:
                    // No need to do anything here. Service discovery is started by the service.
                    Log.i(TAG, "ACTION_CONNECTED");
                    //mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_NO_ONLY);
                    break;
                case PSoCBleSFsystemService.ACTION_DISCONNECTED:
                    Log.i(TAG, "ACTION_DISCONNECTED");
                    unbindService(mServiceConnection);
                    handler.removeCallbacks(updater);

                    mPSoCBleSFsystemService.close();
                    break;
                case PSoCBleSFsystemService.ACTION_DATA_AVAILABLE:
                    Log.i(TAG, "ACTION_DATA_AVAILABLE");

                    // This is called after a Notify completes

                    textViewID.setText(String.format("%d", IDskier));
                    textViewNumSkier.setText(String.format("%d/%d",numSkierOnWay,maxSkierOnWay));

                    textViewHourStart.setText(String.format("%02d", timeStartSkier[HOUR]));
                    textViewMinStart.setText(String.format("%02d", timeStartSkier[MIN]));
                    textViewSecStart.setText(String.format("%02d", timeStartSkier[SEC]));
                    textViewMsStart.setText(String.format("%03d", timeStartSkier[MS]));

                    if (timeResultSkier[HOUR] == 0 && timeResultSkier[MIN] == 0 && timeResultSkier[SEC] == 0 && timeResultSkier[MS] == 0) {
                        currentHour = timeStartSkier[HOUR];
                        currentMin = timeStartSkier[MIN];
                        currentSec = timeStartSkier[SEC];
                        currentMs = timeStartSkier[MS];

                        /* start timer updater*/
                        handler.post(updater);
                    } else {
                        /*stop timer updater*/
                        handler.removeCallbacks(updater);

                        textViewHourFinish.setText(String.format("%02d", timeFinishSkier[HOUR]));
                        textViewMinFinish.setText(String.format("%02d", timeFinishSkier[MIN]));
                        textViewSecFinish.setText(String.format("%02d", timeFinishSkier[SEC]));
                        textViewMsFinish.setText(String.format("%03d", timeFinishSkier[MS]));

                        textViewMinResult.setText(String.format("%02d", timeResultSkier[MIN]));
                        textViewSecResult.setText(String.format("%02d", timeResultSkier[SEC]));
                        textViewMsResult.setText(String.format("%03d", timeResultSkier[MS]));
                        //textViewMinResult.setText(String.format("%d", PSoCBleSFsystemService.getDataSkier(PSoCBleSFsystemService.DataSkier.TIME_RESULT)));
                    }
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

    /*Timer */
    private Runnable updater = new Runnable() {
        @Override
        public void run() {
            currentMs += 31;
            if (currentMs >= 1000) {
                currentMs = 0;
                currentSec++;
                if (currentSec >= 60) {
                    currentSec = 0;
                    currentMin++;
                    if (currentMin >= 60) {
                        currentMin = 0;
                        currentHour++;
                        if (currentHour >= 24) {
                            currentHour = 0;
                        }
                    }
                }
            }

            int[] tmpTime = new int[4];
            tmpTime[MS] = currentMs - timeStartSkier[MS];
            tmpTime[SEC] = currentSec - timeStartSkier[SEC];
            tmpTime[MIN] = currentMin - timeStartSkier[MIN];
            tmpTime[HOUR] = currentHour - timeStartSkier[HOUR];

            if (tmpTime[MS] < 0) {
                tmpTime[MS] += 1000;
                    tmpTime[SEC] -= 1;
            }
            if (tmpTime[SEC] < 0) {
                tmpTime[SEC] += 60;
                tmpTime[MIN] -= 1;
            }
            if (tmpTime[MIN] < 0) {
                tmpTime[MIN] += 60;
                tmpTime[HOUR] -= 1;
            }

            textViewHourFinish.setText(String.format("%02d", currentHour));
            textViewMinFinish.setText(String.format("%02d", currentMin));
            textViewSecFinish.setText(String.format("%02d", currentSec));
            textViewMsFinish.setText(String.format("%03d", currentMs));

            textViewMinResult.setText(String.format("%02d", tmpTime[MIN]));
            textViewSecResult.setText(String.format("%02d", tmpTime[SEC]));
            textViewMsResult.setText(String.format("%03d", tmpTime[MS]));

            handler.postDelayed(this, 31);
        }
    };
}