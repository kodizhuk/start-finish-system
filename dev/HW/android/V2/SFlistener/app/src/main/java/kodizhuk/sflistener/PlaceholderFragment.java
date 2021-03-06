package kodizhuk.sflistener;

import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.List;

/**
 * A placeholder fragment containing a simple view.
 */
public class PlaceholderFragment extends Fragment {

    private static final String ARG_SECTION_NUMBER = "section_number";
    private final String TAG = "PlaceholderFragment";

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
            int numIndex = 4;

            long truNum = data.getTruNum(numIndex);
            int skierNum = data.getSkierNum(numIndex);
            int statusByte;
            statusByte = data.getStatusByte(numIndex);
            int[] timeStart = data.getTimeStart(numIndex);
            int[] timeFinish = data.getTimeFinish(numIndex);
            int[] timeResult = data.getTimeResult(numIndex);
            String txtOut = data.getTxt(numIndex);
            Log.d(TAG, "tru num ="+truNum);
            Log.d(TAG, "skier num ="+skierNum);
            Log.d(TAG, "status byte ="+statusByte);
            Log.d(TAG, "start "+timeStart[0]+":"+timeStart[1]+":"+timeStart[2]+":"+timeStart[3]);
            Log.d(TAG, "finish "+timeFinish[0]+":"+timeFinish[1]+":"+timeFinish[2]+":"+timeFinish[3]);
            Log.d(TAG, "result "+timeResult[0]+":"+timeResult[1]+":"+timeResult[2]+":"+timeResult[3]);
            Log.d(TAG,"txt-"+txtOut);

//            Log.d(TAG,"page - "+mViewPager.getCurrentItem());

//            View v = (View)mViewPager.getChildAt(0);
//            TextView txt = (TextView)v.findViewById(R.id.section_label);
//            txt.setText(builder.toString());
//            txt.setText(data.getData());
//            txt.setText("\ntru num:"+truNum+
//                    "\nskier num:"+skierNum+
//                    "\nstatusByte:"+statusByte+
//                    "\nstart:"+timeStart[0]+":"+timeStart[1]+":"+timeStart[2]+":"+timeStart[3]+
//                    "\nfinish:"+timeFinish[0]+":"+timeFinish[1]+":"+timeFinish[2]+":"+timeFinish[3]+
//                    "\nresult:"+timeResult[0]+":"+timeResult[1]+":"+timeResult[2]+":"+timeResult[3]+
//                    "\ntxt:"+txtOut);
//            Log.d(TAG,String.valueOf(mViewPager.getCurrentItem()));

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


    public static PlaceholderFragment newInstance(int sectionNumber) {
        PlaceholderFragment fragment = new PlaceholderFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_SECTION_NUMBER, sectionNumber);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_main, container, false);
        TextView textView = (TextView) rootView.findViewById(R.id.section_label);
        textView.setText(getString(R.string.section_format, getArguments().getInt(ARG_SECTION_NUMBER)));
        return rootView;
    }
}
