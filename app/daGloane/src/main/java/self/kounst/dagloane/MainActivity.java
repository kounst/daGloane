package self.kounst.dagloane;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.app.Activity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends Activity {

    private static final int REQUEST_ENABLE_BT = 1;

    Button button_connectToDev;
    TextView textView_device;
    EditText editText_BTmsg;
    EditText editText_cobs;
    ListView listview_btdev;
    ArrayList<String> arrayListpaired;
    ArrayAdapter<String> adapter;
    BluetoothAdapter BTadapter;
    private BluetoothSocket btSocket = null;

    private String btMAC = "undefined";

    private BTmsg btmsg = new BTmsg(" ");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Intent enableBtIntent = null;

        button_connectToDev = (Button) findViewById(R.id.button_connectToDev);
        textView_device = (TextView) findViewById(R.id.textView_device);
        listview_btdev = (ListView) findViewById(R.id.listView_btdev);

        button_connectToDev.setEnabled(false);

        arrayListpaired = new ArrayList<String>();
        adapter= new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_list_item_1, arrayListpaired);
        listview_btdev.setAdapter(adapter);


        // Get local Bluetooth adapter
        BTadapter = BluetoothAdapter.getDefaultAdapter();

        if(BTadapter == null){

            Toast.makeText(getApplicationContext(),"Bluetooth not available",Toast.LENGTH_SHORT).show();
            finish();
            return;
        }


        if (!BTadapter.isEnabled()) {
            enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        else
        {
            setupBTDeviceList();
        }



        listview_btdev.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                String selectedFromList =(String) (listview_btdev.getItemAtPosition(i));
                textView_device.setText(selectedFromList);
                btMAC = textView_device.getText().toString().split("\n")[1];

                button_connectToDev.setEnabled(true);
            }
        });



        button_connectToDev.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent intent_cockpit=new Intent(MainActivity.this,cockpit_activity.class );
                intent_cockpit.putExtra("bluetooth_mac", btMAC);

                startActivity(intent_cockpit);
            }
        });
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == REQUEST_ENABLE_BT){
            if (resultCode == RESULT_OK){
                Toast.makeText(getApplicationContext(), "Bluetooth is now enabled", Toast.LENGTH_LONG).show();
                setupBTDeviceList();

            }
            if(resultCode == RESULT_CANCELED){
                Toast.makeText(getApplicationContext(), "Error occured while enabling.Leaving the application..", Toast.LENGTH_LONG).show();
                finish();
                return;
            }
        }
    }//onActivityResult


    private void setupBTDeviceList(){
        Set<BluetoothDevice> pairedDevices = BTadapter.getBondedDevices();
        // If there are paired devices
        if (pairedDevices.size() > 0) {
            // Loop through paired devices
            for (BluetoothDevice device : pairedDevices) {
                // Add the name and address to an array adapter to show in a ListView
                adapter.add(device.getName() + "\n" + device.getAddress());
            }
        }
    }



    @Override
    protected void onResume() {
        super.onResume();

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if(btSocket != null)
        {
            try {
                btSocket.close();
            } catch (IOException e2) {
                Log.e("daGloane",
                        "button_connectToDev_ClickLister: Unable to close socket during connection failure", e2);
            }
        }

        //BTadapter.disable();
    }
    
}
