package comkodizhuk.vk.v1_noble;

import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final String TAG  = "MyLogs";

    EditText editText;
    Button btSave, btLoad;

    SharedPreferences sPref;
    final String SAVED_TEXT = "saved_text";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.main_menu, menu);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        switch (item.getItemId()){
            case R.id.action_admin:
                Intent intent = new Intent(MainActivity.this, AdminActivity.class);
                Toast.makeText(this, "Admin", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
        }

        return super.onOptionsItemSelected(item);
    }

    public void onClickButton(View v) {
        switch (v.getId()){
            case R.id.btSave:
                saveText();
                break;
            case R.id.btLoad:
                loadText();
                break;
        }
    }
}
