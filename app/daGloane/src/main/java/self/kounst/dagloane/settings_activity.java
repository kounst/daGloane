package self.kounst.dagloane;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.method.TextKeyListener;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;

import java.io.IOException;
import java.io.OutputStream;
import java.util.UUID;

/**
 * Created by konstantin on 22.10.13.
 */
public class settings_activity extends Activity{

    TextView textView_bin, textView_hex, textView_dec;
    Button button_send;
    Button button_clear;

    EditText editText1, editText2, editText3, editText4, editText5, editText6, editText7, editText8;
    CheckBox checkBox0, checkBox1, checkBox2, checkBox3, checkBox4, checkBox5, checkBox6, checkBox7;

    int bits = 0;


    BluetoothSocket bluetooth_socket = null;
    BluetoothAdapter bluetooth_adapter = null;
    BluetoothDevice device = null;
    private OutputStream outStream = null;
    BTmsg btmsg = new BTmsg(" ");
    byte[] BTmsgbytes = new byte[11];


    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        BTmsgbytes[0] = 2;  //message type
        BTmsgbytes[1] = 13; //msg length
        String btmac = getIntent().getStringExtra("bluetooth_mac");

        textView_bin = (TextView) findViewById(R.id.textView_bin);
        textView_hex = (TextView) findViewById(R.id.textView_hex);
        textView_dec = (TextView) findViewById(R.id.textView_dec);

        button_clear = (Button) findViewById(R.id.button_clear);
        button_clear.setOnClickListener(ClearButtonClickHandler);
        button_send = (Button) findViewById(R.id.button_send);
        button_send.setOnClickListener(SendButtonClickHandler);

        editText1 = (EditText) findViewById(R.id.editText1);
        editText2 = (EditText) findViewById(R.id.editText2);
        editText3 = (EditText) findViewById(R.id.editText3);
        editText4 = (EditText) findViewById(R.id.editText4);
        editText5 = (EditText) findViewById(R.id.editText5);
        editText6 = (EditText) findViewById(R.id.editText6);
        editText7 = (EditText) findViewById(R.id.editText7);
        editText8 = (EditText) findViewById(R.id.editText8);
        editText1.setText("0");
        editText2.setText("0");
        editText3.setText("0");
        editText4.setText("0");
        editText5.setText("0");
        editText6.setText("0");
        editText7.setText("0");
        editText8.setText("0");
        checkBox0 = (CheckBox) findViewById(R.id.checkBox0);
        checkBox1 = (CheckBox) findViewById(R.id.checkBox1);
        checkBox2 = (CheckBox) findViewById(R.id.checkBox2);
        checkBox3 = (CheckBox) findViewById(R.id.checkBox3);
        checkBox4 = (CheckBox) findViewById(R.id.checkBox4);
        checkBox5 = (CheckBox) findViewById(R.id.checkBox5);
        checkBox6 = (CheckBox) findViewById(R.id.checkBox6);
        checkBox7 = (CheckBox) findViewById(R.id.checkBox7);

        checkBox0.setOnClickListener(CheckBoxClickHandler);
        checkBox1.setOnClickListener(CheckBoxClickHandler);
        checkBox2.setOnClickListener(CheckBoxClickHandler);
        checkBox3.setOnClickListener(CheckBoxClickHandler);
        checkBox4.setOnClickListener(CheckBoxClickHandler);
        checkBox5.setOnClickListener(CheckBoxClickHandler);
        checkBox6.setOnClickListener(CheckBoxClickHandler);
        checkBox7.setOnClickListener(CheckBoxClickHandler);


        updateTextViews();

        // Get local Bluetooth adapter
        bluetooth_adapter = BluetoothAdapter.getDefaultAdapter();

        if(bluetooth_socket == null)
        {
            try{
                device = bluetooth_adapter.getRemoteDevice(btmac);
            } catch(IllegalArgumentException e ) {
                Log.e("daGloane", "btadabpter.getremotedevice failed: illegal argument", e);
                finish();
                return;
            }

            try {
                bluetooth_socket = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
                Log.e("daGloane", "button_connectToDev_ClickLister: Socket creation failed.", e);
                finish();
                return;
            }

            try {
                bluetooth_socket.connect();
                Log.e("daGloane", "button_connectToDev_ClickLister: BT connection established, data transfer link open.");

            } catch (IOException e) {
                try {
                    bluetooth_socket.close();
                    finish();
                    return;
                } catch (IOException e2) {
                    Log.e("daGloane","button_connectToDev_ClickLister: Unable to close socket during connection failure", e2);
                    finish();
                    return;
                }
            }



            // Create a data stream so we can talk to server.

            try {
                outStream = bluetooth_socket.getOutputStream();
            } catch (IOException e) {
                Log.e("daGloane", "button_connectToDev_ClickLister: Output stream creation failed.", e);
                finish();
                return;
            }


        }
        else
        {
            try {
                bluetooth_socket.close();
                bluetooth_socket = null;
            } catch (IOException e2) {
                Log.e("daGloane","button_connectToDev_ClickLister: Unable to close socket during connection failure", e2);
                finish();
                return;
            }
        }


    }


    View.OnClickListener SendButtonClickHandler = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            BTmsgbytes[2] = (byte)bits;
            BTmsgbytes[3] = (byte)Integer.parseInt(editText1.getText().toString());
            BTmsgbytes[4] = (byte)Integer.parseInt(editText2.getText().toString());
            BTmsgbytes[5] = (byte)Integer.parseInt(editText3.getText().toString());
            BTmsgbytes[6] = (byte)Integer.parseInt(editText4.getText().toString());
            BTmsgbytes[7] = (byte)Integer.parseInt(editText5.getText().toString());
            BTmsgbytes[8] = (byte)Integer.parseInt(editText6.getText().toString());
            BTmsgbytes[9] = (byte)Integer.parseInt(editText7.getText().toString());
            BTmsgbytes[10] =(byte)Integer.parseInt(editText8.getText().toString());

            btmsg.setMsg(BTmsgbytes);

            try {
                outStream.write(btmsg.getCobs_msg());
            } catch (IOException e) {
                Log.e("daGloane", "Exception during write.", e);
                finish();
                return;
            }
        }
    };


    View.OnClickListener ClearButtonClickHandler = new View.OnClickListener() {
        @Override
        public void onClick(View view) {

            editText1.setText("0");
            editText2.setText("0");
            editText3.setText("0");
            editText4.setText("0");
            editText5.setText("0");
            editText6.setText("0");
            editText7.setText("0");
            editText8.setText("0");

            checkBox0.setChecked(false);
            checkBox1.setChecked(false);
            checkBox2.setChecked(false);
            checkBox3.setChecked(false);
            checkBox4.setChecked(false);
            checkBox5.setChecked(false);
            checkBox6.setChecked(false);
            checkBox7.setChecked(false);

            updateTextViews();
        }
    };

    public void updateTextViews(){
        bits = 0;
        if(checkBox0.isChecked())
        {
            bits += 1;
        }
        if(checkBox1.isChecked())
        {
            bits += 2;
        }
        if(checkBox2.isChecked())
        {
            bits += 4;
        }
        if(checkBox3.isChecked())
        {
            bits += 8;
        }
        if(checkBox4.isChecked())
        {
            bits += 16;
        }
        if(checkBox5.isChecked())
        {
            bits += 32;
        }
        if(checkBox6.isChecked())
        {
            bits += 64;
        }
        if(checkBox7.isChecked())
        {
            bits += 128;
        }

        //textView_bin.setText('b' + Integer.toBinaryString(bits));
        textView_bin.setText(String.format("b%8s", Integer.toBinaryString(bits)).replace(' ','0'));
        textView_dec.setText(Integer.toString(bits));
        //textView_hex.setText("0x" + Integer.toHexString(bits));
        textView_hex.setText(String.format("0x%02X",bits));

    }

    View.OnClickListener CheckBoxClickHandler = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            updateTextViews();
        }
    };

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if(bluetooth_socket != null)
        {
            try {
                bluetooth_socket.close();
            } catch (IOException e2) {
                Log.e("daGloane",
                        "button_connectToDev_ClickLister: Unable to close socket during connection failure", e2);
            }
        }
    }
}
