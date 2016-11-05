package comkodizhuk.vk.v1_noble;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

public class AdminActivity extends AppCompatActivity {

    private static final String TAG = "MyLogs";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.admin_menu, menu);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        int id = item.getItemId();
        Intent intent;

        switch (id){
            case R.id.action_user:
                intent = new Intent(AdminActivity.this, MainActivity.class);
                Toast.makeText(this, "User", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
            case R.id.action_settings:
                intent = new Intent(AdminActivity.this, SettingsActivity.class);
                Toast.makeText(this, "Settings", Toast.LENGTH_SHORT).show();
                startActivity(intent);
                break;
            default:
                break;
        }

        return super.onOptionsItemSelected(item);
    }
}
