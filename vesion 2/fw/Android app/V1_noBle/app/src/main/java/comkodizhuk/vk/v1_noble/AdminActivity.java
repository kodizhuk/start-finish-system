package comkodizhuk.vk.v1_noble;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.AdminOnly.ADMIN_NO_ONLY;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.AdminOnly.ADMIN_ONLY;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.IDskier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.maxSkierOnWay;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.numSkierOnWay;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.systemStatus;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeFinishSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeResultSkier;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.timeStartSkier;
import static comkodizhuk.vk.v1_noble.ScanActivity.EXTRAS_BLE_ADDRESS;

public class AdminActivity extends AppCompatActivity {

    private static final String TAG = "MyLogs";

    private static final int HOUR = 0;
    private static final int MIN = 1;
    private static final int SEC = 2;
    private static final int MS = 3;

    private static final int STATUS = 0;
    private static final int NETWORK = 1;
    private static final int SD = 2;

    ImageView imageViewStatus;
    ImageView imageViewNetwork;
    ImageView imageViewSD;

    TextView textViewNumSkierOnWay;

    ListView skierListItems;
    SimpleAdapter sAdapter;
    ArrayList<Map<String, Object>> data;
    Map<String, Object> m;

    private static String mDeviceAddress;
    private static PSoCBleSFsystemService mPSoCBleSFsystemService;

    ArrayList<String> idSkier = new ArrayList<>();
    ArrayList<String> startSkier = new ArrayList<>();
    ArrayList<String> finishSkier = new ArrayList<>();
    ArrayList<String> resultSkier = new ArrayList<>();

    final String ATTRIBUTE_ID_TEXT = "id";
    final String ATTRIBUTE_START_TEXT = "start";
    final String ATTRIBUTE_FINISH_TEXT = "finish";
    final String ATTRIBUTE_RESULT_TEXT = "result";
    private  int IDoldSkier = -1;

    /**
     * This manages the lifecycle of the BLE service.
     * When the service starts we get the service object, initialize the service, and connect.
     */
    private final ServiceConnection mServiceConnection = new ServiceConnection() {

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
        setContentView(R.layout.activity_admin);

        imageViewStatus = (ImageView)findViewById(R.id.imageViewStatus);
        imageViewSD = (ImageView)findViewById(R.id.imageViewSD);
        imageViewNetwork = (ImageView)findViewById(R.id.imageViewNetwork);
        textViewNumSkierOnWay = (TextView)findViewById(R.id.textViewNumSkierOnWay);

        final Intent intent = getIntent();
        mDeviceAddress = intent.getStringExtra(EXTRAS_BLE_ADDRESS);

        //--------------------------------------------------
        data = new ArrayList<Map<String, Object>>(idSkier.size());

        for (int i = 0; i < idSkier.size(); i++) {
            m = new HashMap<String, Object>();
            m.put(ATTRIBUTE_ID_TEXT, idSkier.get(i));
            m.put(ATTRIBUTE_START_TEXT, startSkier.get(i));
            m.put(ATTRIBUTE_FINISH_TEXT, finishSkier.get(i));
            m.put(ATTRIBUTE_RESULT_TEXT, resultSkier.get(i));
            data.add(m);
        }

        String[] from = {ATTRIBUTE_ID_TEXT, ATTRIBUTE_START_TEXT, ATTRIBUTE_FINISH_TEXT, ATTRIBUTE_RESULT_TEXT};
        int[] to = {R.id.tvSkierID, R.id.tvSkierStart, R.id.tvSkierFinish, R.id.tvSkierResult};

        sAdapter = new SimpleAdapter(this, data, R.layout.skier_result_list, from, to);

        skierListItems = (ListView) findViewById(R.id.skierListItems);
        skierListItems.setAdapter(sAdapter);
        registerForContextMenu(skierListItems);
        //---------------------------------------------------------------

        Intent SFsystemServiceIntent = new Intent(this, PSoCBleSFsystemService.class);
        bindService(SFsystemServiceIntent, mServiceConnection, Context.BIND_AUTO_CREATE);
    }


    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(mSFsystemUpdateReceiver, makeSFsystemUpdateIntentFilter());
        Log.i(TAG, "Admin Activity On resume");

        if (mPSoCBleSFsystemService != null) {
            final boolean result = mPSoCBleSFsystemService.connect(mDeviceAddress);
            Log.i(TAG, "Connect request result=" + result);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mSFsystemUpdateReceiver);

//        mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_NO_ONLY);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Admin Activity Destroy Activity");
        unbindService(mServiceConnection);
        mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_NO_ONLY);
        mPSoCBleSFsystemService = null;


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.admin_menu, menu);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        Intent intent;

        switch (id) {
            case R.id.action_user:
                intent = new Intent(AdminActivity.this, MainActivity.class);
                Toast.makeText(this, "User", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
            case R.id.action_settings:
                intent = new Intent(AdminActivity.this, SettingsActivity.class);
                intent.putExtra(EXTRAS_BLE_ADDRESS, mDeviceAddress);
                Toast.makeText(this, "Settings", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
            default:
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
                    //mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_ONLY);
                    break;
                case PSoCBleSFsystemService.ACTION_DISCONNECTED:
                    Log.i(TAG, "ACTION_DISCONNECTED");
                    mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_NO_ONLY);
                    mPSoCBleSFsystemService.close();
                    break;
                case PSoCBleSFsystemService.ACTION_DATA_AVAILABLE:
                    Log.i(TAG, "ACTION_DATA_AVAILABLE");

                    if(timeResultSkier[HOUR] ==0 && timeResultSkier[MIN]==0 && timeResultSkier[SEC]==0 && timeResultSkier[MS]==0){
                        //do nothing
                    }else {
                        /*if new receive new skier*/
                        if(IDskier != IDoldSkier) {
                        /*add new time skier on diaplay*/
                            m = new HashMap<String, Object>();
                            m.put(ATTRIBUTE_ID_TEXT, String.format("%d", IDskier));
                            m.put(ATTRIBUTE_START_TEXT,
                                    String.format("%02d:%02d:%02d:%03d", timeStartSkier[HOUR], timeStartSkier[MIN], timeStartSkier[SEC], timeStartSkier[MS]));
                            m.put(ATTRIBUTE_FINISH_TEXT,
                                    String.format("%02d:%02d:%02d:%03d", timeFinishSkier[HOUR], timeFinishSkier[MIN], timeFinishSkier[SEC], timeFinishSkier[MS]));
                            m.put(ATTRIBUTE_RESULT_TEXT,
                                    String.format("%02d:%02d:%02d:%03d", timeResultSkier[HOUR], timeResultSkier[MIN], timeResultSkier[SEC], timeResultSkier[MS]));

                            data.add(m);
                            sAdapter.notifyDataSetChanged();
                            IDoldSkier = IDskier;
                        }
                    }

                    Log.i(TAG,"status -" + systemStatus[STATUS]+" network -"  + systemStatus[NETWORK]+" SD -"  +
                            systemStatus[SD]+"  "  + numSkierOnWay+'/'+maxSkierOnWay);

                    /*read status*/
                    /*status system*/
                    if(systemStatus[STATUS] == 1){
                        imageViewStatus.setImageDrawable(getResources().getDrawable(R.drawable.status));
                    }else{
                        imageViewStatus.setImageDrawable(getResources().getDrawable(R.drawable.status_error));
                    }

                    /*SD card*/
                    if(systemStatus[SD] > 0){
                        imageViewSD.setImageDrawable(getResources().getDrawable(R.drawable.sdcard));
                    }else{
                        imageViewSD.setImageDrawable(getResources().getDrawable(R.drawable.sdcard_error));
                    }

                    /*network connect*/
                    if(systemStatus[NETWORK] > 0){
                        imageViewNetwork.setImageDrawable(getResources().getDrawable(R.drawable.network));
                    }else{
                        imageViewNetwork.setImageDrawable(getResources().getDrawable(R.drawable.connect_error));
                    }

                    /*nummer skier on way*/
                    textViewNumSkierOnWay.setText(String.format("%d/%d",numSkierOnWay,maxSkierOnWay));

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

    public void onClickSD(View view) {
        mPSoCBleSFsystemService.setFalgAdminOnly(ADMIN_ONLY);
    }
}
