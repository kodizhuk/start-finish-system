package comkodizhuk.vk.viewpager;

import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.text.TextUtils;
import android.util.Log;
import android.view.Display;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.List;

/**
 * Created by Petro on 23.08.2017.
 */

public class CustomPageAdapter extends PagerAdapter {
    private Context mContext;
    private final String TAG = "CustomPageAdapter";

    Data data = new Data();

    public CustomPageAdapter(Context context){
        mContext = context;
    }

    @Override
    /*добавлення екранів*/
    public Object instantiateItem(ViewGroup collection, int position){
        ModelObject modelObject = ModelObject.values()[position];
        LayoutInflater inflater = LayoutInflater.from(mContext);
        ViewGroup layout = (ViewGroup)inflater.inflate(modelObject.getLayoutResId(), collection, false);
        TextView t = (TextView)layout.findViewById(R.id.textView);
        t.setText("tru number:"+data.getTruNum(0)+"\nposition:"+position);
        Log.d(TAG,"tru Num"+data.getTruNum(0));
        collection.addView(layout);
        return layout;
    }

    @Override
    /*видалення екранів*/
    public void destroyItem(ViewGroup collection,int position, Object view ){
        collection.removeView((View)view);
    }

    @Override
    public int getCount(){
        return ModelObject.values().length;
    }

    @Override
    public boolean isViewFromObject(View view, Object object){
        return view == object;
    }

    @Override
    public CharSequence getPageTitle(int position){
        ModelObject customPageEnum = ModelObject.values()[position];
        return mContext.getString(customPageEnum.getTitleResId());
    }

    public int getItemPosition(Object object){
        return PagerAdapter.POSITION_NONE;
    }

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
            CustomPageAdapter.this.notifyDataSetChanged();

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
}
