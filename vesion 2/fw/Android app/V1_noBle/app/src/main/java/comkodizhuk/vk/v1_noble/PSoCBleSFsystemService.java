package comkodizhuk.vk.v1_noble;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.UUID;

import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.AdminOnly.ADMIN_NO_ONLY;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.AdminOnly.ADMIN_ONLY;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.DataSkier.ID;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.DataSkier.TIME_FINISH;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.DataSkier.TIME_RESULT;
import static comkodizhuk.vk.v1_noble.PSoCBleSFsystemService.DataSkier.TIME_START;

/**
 * Created by Petro on 08.11.2016.
 */

public class PSoCBleSFsystemService extends Service {
    private final static String TAG = "MyLog";

    public enum DataSkier {ID, TIME_START, TIME_FINISH, TIME_RESULT}
    public enum AdminOnly {ADMIN_ONLY, ADMIN_NO_ONLY}

    private static final int HOUR = 0;
    private static final int MIN = 1;
    private static final int SEC = 2;
    private static final int MS = 3;

    private static final int STATUS = 0;
    private static final int NETWORK = 1;
    private static final int SD = 2;

    private static BluetoothManager mBluetoothManager;
    private static BluetoothAdapter mBluetoothAdapter;
    private static String mBluetoothDeviceAddress;
    private static BluetoothGatt mBluetoothGatt;

    private static BluetoothGattService mService;
    public static ArrayList<BluetoothGattCharacteristic> mCharacteristics =
            new ArrayList<BluetoothGattCharacteristic>();

    //  Queue for BLE events
    //  This is needed so that rapid BLE events don't get dropped
    private static final Queue<Object> BleQueue = new LinkedList<>();

    // UUID for the custom motor characteristics
    private static final String baseUUID = "00000000-0000-1000-8000-00805f9b34f";
    private static final String SFsystemUUID = baseUUID + "0";
    private static final String ID_UUID = baseUUID + "1";
    private static final String timeStartUUID = baseUUID + "2";
    private static final String timeFinishUUID = baseUUID + "3";
    private static final String timeResultUUID = baseUUID + "4";
    private static final String systemStatusUUID = baseUUID + "5";
    private static final String unixTimeUUID = baseUUID + "6";
    private static final String adminIsOnlyUUID = baseUUID + "7";
    private static final String CCCD_UUID = "00002902-0000-1000-8000-00805f9b34fb";

    // Bluetooth Characteristics that we need to read/write
    private static BluetoothGattCharacteristic mID_Characteristic;
    private static BluetoothGattCharacteristic mTimeStartCharacteristic;
    private static BluetoothGattCharacteristic mTimeFinishCharacteristic;
    private static BluetoothGattCharacteristic mTimeResultCharacteristic;
    private static BluetoothGattCharacteristic mSystemStatusCharacteristic;
    private static BluetoothGattCharacteristic mUnixTimeCharacteristic;
    private static BluetoothGattCharacteristic mAdminIsOnlyCharacteristic;


    public static int IDskier;
    public static int[] timeStartSkier = new int[4];
    public static int[] timeFinishSkier = new int[4];
    public static int[] timeResultSkier = new int[4];
    public static int[] systemStatus = new int[3];
    public static int numSkierOnWay;
    public static int maxSkierOnWay;
    private static int unixTimeSystem;
    private static int adminIsOnly;

    //enableAllGlucoseCharacteristic in class bluetooth ble service
    //

    // Actions used during broadcasts to the activity
    public static final String ACTION_CONNECTED =
            "com.cypress.academy.ble101_robot.ACTION_GATT_CONNECTED";
    public static final String ACTION_DISCONNECTED =
            "com.cypress.academy.ble101_robot.ACTION_GATT_DISCONNECTED";
    public static final String ACTION_DATA_AVAILABLE =
            "com.cypress.academy.ble101_robot.ACTION_DATA_AVAILABLE";

    /**
     * This is a binder for the BluetoothLeService
     */
    public class LocalBinder extends Binder {
        PSoCBleSFsystemService getService() {
            return PSoCBleSFsystemService.this;
        }
    }


    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "onBind Service");
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        // Disconnect from the GATT database and close the connection
        disconnect();
        close();
        return super.onUnbind(intent);
    }

    private final IBinder mBinder = new PSoCBleSFsystemService.LocalBinder();

    /**
     * Implements callback methods for GATT events.
     */
    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        /**
         * This is called on a connection state change (either connection or disconnection)
         * @param gatt The GATT database object
         * @param status Status of the event
         * @param newState New state (connected or disconnected)
         */
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                broadcastUpdate(ACTION_CONNECTED);
                Log.i(TAG, "Connected to GATT server.");
                // Attempts to discover services after successful connection.
                Log.i(TAG, "Attempting to start service discovery:" +
                        mBluetoothGatt.discoverServices());

            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                Log.i(TAG, "Disconnected from GATT server.");
                broadcastUpdate(ACTION_DISCONNECTED);
            }
        }

        /**
         * This is called when service discovery has completed.
         *
         * It broadcasts an update to the main activity.
         *
         * @param gatt The GATT database object
         * @param status Status of whether the discovery was successful.
         */
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                new Handler(Looper.getMainLooper()).post(new Runnable() {
                    @Override
                    public void run() {
                        // Get the characteristics for the motor service
                        BluetoothGattService gattService = mBluetoothGatt.getService(UUID.fromString(SFsystemUUID));
                        if (gattService == null) return; // return if the motor service is not supported

                        mID_Characteristic = gattService.getCharacteristic(UUID.fromString(ID_UUID));
                        mTimeStartCharacteristic = gattService.getCharacteristic(UUID.fromString(timeStartUUID));
                        mTimeFinishCharacteristic = gattService.getCharacteristic(UUID.fromString(timeFinishUUID));
                        mTimeResultCharacteristic = gattService.getCharacteristic(UUID.fromString(timeResultUUID));
                        mSystemStatusCharacteristic = gattService.getCharacteristic(UUID.fromString(systemStatusUUID));
                        mUnixTimeCharacteristic = gattService.getCharacteristic(UUID.fromString(unixTimeUUID));
                        mAdminIsOnlyCharacteristic = gattService.getCharacteristic(UUID.fromString(adminIsOnlyUUID));

                        Log.i(TAG, "getAllCharacteristic");

                        setCharacteristicNotification(mID_Characteristic, true);
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        setCharacteristicNotification(mTimeStartCharacteristic, true);
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        setCharacteristicNotification(mTimeFinishCharacteristic, true);
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        setCharacteristicNotification(mTimeResultCharacteristic, true);
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        setCharacteristicNotification(mSystemStatusCharacteristic, true);
                    }
                });
            } else {
                //Log.w(TAG, "onServicesDiscovered received: " + status);
            }
        }

//        /**
//         * Method to get all Characteristic with report reference
//         */
//        private void getAllCharacteristic() {
//            List<BluetoothGattCharacteristic> gattCharacteristics = mService.getCharacteristics();
//
//            for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
//                    PSoCBleSFsystemService.mCharacteristics.add(gattCharacteristic);
//            }
//            enableAllGlucoseCharacteristics();
//        }
//
//        public  void enableAllGlucoseCharacteristics() {
//            if (mCharacteristics.size() > 0) {
//                BluetoothGattCharacteristic bluetoothGattCharacteristic = mCharacteristics.get(0);
//                setCharacteristicNotification(bluetoothGattCharacteristic, true);
//            }
//        }

        /**
         * This handles the BLE Queue. If the queue is not empty, it starts the next event.
         */
        private void handleBleQueue() {
            if (BleQueue.size() > 0) {
                // Determine which type of event is next and fire it off
                if (BleQueue.element() instanceof BluetoothGattDescriptor) {
                    mBluetoothGatt.writeDescriptor((BluetoothGattDescriptor) BleQueue.element());
                } else if (BleQueue.element() instanceof BluetoothGattCharacteristic) {
                    mBluetoothGatt.writeCharacteristic((BluetoothGattCharacteristic) BleQueue.element());
                }
            }
        }

        /**
         * This is called when a characteristic write has completed. Is uses a queue to determine if
         * additional BLE actions are still pending and launches the next one if there are.
         *
         * @param gatt The GATT database object
         * @param characteristic The characteristic that was written.
         * @param status Status of whether the write was successful.
         */
        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt,
                                          BluetoothGattCharacteristic characteristic,
                                          int status) {
            // Pop the item that was written from the queue
            BleQueue.remove();
            // See if there are more items in the BLE queues
            handleBleQueue();
        }

        /**
         * This is called when a CCCD write has completed. It uses a queue to determine if
         * additional BLE actions are still pending and launches the next one if there are.
         *
         * @param gatt The GATT database object
         * @param descriptor The CCCD that was written.
         * @param status Status of whether the write was successful.
         */
        @Override
        public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor,
                                      int status) {
            // Pop the item that was written from the queue
            BleQueue.remove();
            // See if there are more items in the BLE queues
            handleBleQueue();
        }

        /**
         * This is called when a characteristic with notify set changes.
         * It broadcasts an update to the main activity with the changed data.
         * зчитуємо тут всі потрібні значення
         *
         * @param gatt The GATT database object
         * @param characteristic The characteristic that was changed
         */
        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt,
                                            BluetoothGattCharacteristic characteristic) {
            // Get the UUID of the characteristic that changed
            String uuid = characteristic.getUuid().toString();

            // Update the appropriate variable with the new value.
            switch (uuid) {
                case ID_UUID:
                    IDskier = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0);
                    //Log.i(TAG,"IDskier -" + IDskier);
                    break;
                case timeStartUUID:
                    timeStartSkier[HOUR] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0);
                    timeStartSkier[MIN] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 2);
                    timeStartSkier[SEC] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 4);
                    timeStartSkier[MS] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 6);
                    break;
                case timeFinishUUID:
                    timeFinishSkier[HOUR] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0);
                    timeFinishSkier[MIN] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 2);
                    timeFinishSkier[SEC] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 4);
                    timeFinishSkier[MS] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 6);
                    break;
                case timeResultUUID:
                    timeResultSkier[HOUR] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 0);
                    timeResultSkier[MIN] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 2);
                    timeResultSkier[SEC] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 4);
                    timeResultSkier[MS] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT16, 6);
                    broadcastUpdate(ACTION_DATA_AVAILABLE);
                    break;
                case systemStatusUUID:
                    systemStatus[STATUS] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8, 0);
                    systemStatus[NETWORK] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8, 1);
                    systemStatus[SD] = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8, 2);
                    numSkierOnWay = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8, 4);
                    maxSkierOnWay = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8, 6);
                    //Log.i(TAG,"status -" + systemStatus[STATUS]+'-' + systemStatus[NETWORK]+'-' +
                    //        systemStatus[SD]+'-' + numSkierOnWay+'-'+maxSkierOnWay);

                    broadcastUpdate(ACTION_DATA_AVAILABLE);
                    break;
            }
        }
    };


    /**
     * Sends a broadcast to the listener in the main activity.
     *
     * @param action The type of action that occurred.
     */
    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }


    /**
     * Initialize a reference to the local Bluetooth adapter.
     *
     * @return Return true if the initialization is successful.
     */
    public boolean initialize() {
        // For API level 18 and above, get a reference to BluetoothAdapter through
        // BluetoothManager.
        if (mBluetoothManager == null) {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null) {
                Log.e(TAG, "Unable to initialize BluetoothManager.");
                return false;
            }
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null) {
            Log.e(TAG, "Unable to obtain a BluetoothAdapter.");
            return false;
        }

        return true;
    }

    /**
     * Connects to the GATT server hosted on the Bluetooth LE device.
     *
     * @param address The device address of the destination device.
     * @return Return true if the connection is initiated successfully. The connection result
     * is reported asynchronously through the
     * {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     * callback.
     */
    public boolean connect(final String address) {
        if (mBluetoothAdapter == null || address == null) {
            Log.w(TAG, "BluetoothAdapter not initialized or unspecified address.");
            return false;
        }

        // Previously connected device.  Try to reconnect.
        if (mBluetoothDeviceAddress != null && address.equals(mBluetoothDeviceAddress)
                && mBluetoothGatt != null) {
            Log.i(TAG, "Trying to use an existing mBluetoothGatt for connection.");
            return mBluetoothGatt.connect();
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        if (device == null) {
            Log.w(TAG, "Device not found.  Unable to connect.");
            return false;
        }
        // We want to directly connect to the device, so we are setting the autoConnect
        // parameter to false.
        mBluetoothGatt = device.connectGatt(this, false, mGattCallback);
        Log.i(TAG, "Trying to create a new connection.");
        mBluetoothDeviceAddress = address;
        return true;
    }

    /**
     * Disconnects an existing connection or cancel a pending connection. The disconnection result
     * is reported asynchronously through the
     * {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     * callback.
     */
    public void disconnect() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        Log.w(TAG, "BluetoothAdapter is disconected");
        mBluetoothGatt.disconnect();
    }

    /**
     * After using a given BLE device, the app must call this method to ensure resources are
     * released properly.
     */
    public void close() {
        if (mBluetoothGatt == null) {
            return;
        }
        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }


    /**
     * Update the unix time in the GATT database or turn off motor.
     *
     * @param unixTime
     */
    private void updateGattUnixTime(int unixTime) {
        Log.i(TAG, "in undateGattUnixTime");
        Log.i(TAG, "mUnixTimeCharacteristic = " + mUnixTimeCharacteristic);

        if (mUnixTimeCharacteristic != null) {
            mUnixTimeCharacteristic.setValue(unixTime, BluetoothGattCharacteristic.FORMAT_UINT32, 0);
            Log.i(TAG, "update gatt unix time");
            writeCharacteristic(mUnixTimeCharacteristic);
        }
    }

    private void updateGattFlagAdminOnly(int adminIsOnly){
        if (mAdminIsOnlyCharacteristic != null) {
            mAdminIsOnlyCharacteristic.setValue(adminIsOnly, BluetoothGattCharacteristic.FORMAT_UINT8, 0);
            Log.i(TAG, "update admin only");
            writeCharacteristic(mAdminIsOnlyCharacteristic);
        }
    }

    /**
     * Request a write on a given {@code BluetoothGattCharacteristic}.
     *
     * @param characteristic The characteristic to write.
     */
    private void writeCharacteristic(BluetoothGattCharacteristic characteristic) {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        Log.i(TAG, "BleQueue.sise = " + BleQueue.size());
        BleQueue.add(characteristic);
        if (BleQueue.size() == 1) {
            mBluetoothGatt.writeCharacteristic(characteristic);
            Log.i(TAG, "Writing Characteristic");
        }
    }

    /**
     * Enables or disables notification on a give characteristic.
     *
     * @param characteristic Characteristic to act on.
     * @param enabled        If true, enable notification.  False otherwise.
     */
    private void setCharacteristicNotification(BluetoothGattCharacteristic characteristic,
                                               boolean enabled) {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.i(TAG, "BluetoothAdapter not initialized");
            return;
        }

        /* Enable or disable the callback notification on the phone */
        mBluetoothGatt.setCharacteristicNotification(characteristic, enabled);

        /* Set CCCD value locally and then write to the device to register for notifications */
        BluetoothGattDescriptor descriptor = characteristic.getDescriptor(
                UUID.fromString(CCCD_UUID));
        if (enabled) {
            descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
        } else {
            descriptor.setValue(BluetoothGattDescriptor.DISABLE_NOTIFICATION_VALUE);
        }
        // Put the descriptor into the write queue
        BleQueue.add(descriptor);
        // If there is only 1 item in the queue, then write it. If more than one, then the callback
        // will handle it
        if (BleQueue.size() == 1) {
            mBluetoothGatt.writeDescriptor(descriptor);
            Log.i(TAG, "Writing Notification");
            Toast.makeText(getApplicationContext(), "Sync bluetooth okey", Toast.LENGTH_SHORT).show();
        }
    }


    public void setUnixTime(long unixTime) {

        unixTimeSystem = (int) unixTime;
        Log.i(TAG, "on set unix time");
        updateGattUnixTime(unixTimeSystem);
    }

    public void setFalgAdminOnly(AdminOnly adminOnly){
        if(adminOnly == ADMIN_ONLY){
            adminIsOnly = 1;
            Log.i(TAG, "on set setFalgAdminOnly = 1");
        }else {
            adminIsOnly = 0;
            Log.i(TAG, "on set setFalgAdminOnly = 0");
        }

        updateGattFlagAdminOnly(adminIsOnly);
    }

    /**
     * Get the tach reading for one of the motors
     *
     * @param data to operate on
     * @return data value
     */
    public static int getDataSkier(DataSkier data) {

        if (data == ID) {
            return IDskier;
        } else if (data == TIME_START) {
            return timeStartSkier[0];
        } else if (data == TIME_FINISH) {
            return timeFinishSkier[0];
        } else if (data == TIME_RESULT) {
            return timeResultSkier[0];
        } else {
            return 0;
        }
    }

    /**
     * This function returns the UUID of the motor service
     *
     * @return the motor service UUID
     */
    public static UUID getSFsystemServiceUUID() {
        return UUID.fromString(PSoCBleSFsystemService.SFsystemUUID);
    }


}
