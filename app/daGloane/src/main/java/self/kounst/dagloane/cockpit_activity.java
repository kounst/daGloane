package self.kounst.dagloane;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Timer;
import java.util.TimerTask;
import java.util.UUID;

/**
 * Created by konstantin on 09.09.13.
 */
public class cockpit_activity extends Activity implements SensorEventListener{

    VerticalSeekBar verticalSeekBar=null;
    Button button_arm=null;

    BluetoothSocket bluetooth_socket = null;
    BluetoothAdapter bluetooth_adapter = null;
    BluetoothDevice device = null;
    private OutputStream outStream = null;
    byte[] msgBuffer;
    BTmsg btmsg = new BTmsg(" ");
    byte[] BTmsgbytes = new byte[11];

    SensorManager sensorManager;
    Sensor accelerometer;
    Sensor magnetometer;

    float[] mGravity;
    float[] mGeomagnetic;
    float[] orientation = new float[3];

    Timer t = null;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cockpit);

        verticalSeekBar=(VerticalSeekBar)findViewById(R.id.vertical_Seekbar);

        button_arm = (Button)findViewById(R.id.button_arm);
        button_arm.setText("arm");

        sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magnetometer = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        BTmsgbytes[0] = 1;
        BTmsgbytes[1] = 13;

        String btmac = getIntent().getStringExtra("bluetooth_mac");

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


        button_arm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(button_arm.getText() == "arm")
                {
                    verticalSeekBar.setProgress(0);     //set throttle to zero
                    BTmsgbytes[10] |= 0x80;             //set arm bit
                    button_arm.setText("disarm");
                }
                else
                {
                    verticalSeekBar.setProgress(0);     //set throttle to zero
                    BTmsgbytes[10] &= ~0x80;             //reset arm bit
                    button_arm.setText("arm");
                }
            }
        });


        int time = 0;

        //Declare the timer
        t = new Timer();
        //Set the schedule function and rate
        t.scheduleAtFixedRate(new TimerTask() {
            int time = 0;
            int seekbar;
            @Override
            public void run() {

                //Called each time when 100 milliseconds (the period parameter)
                runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        time++;

                        //String message = String.valueOf(time) + '\n';
                        //btmsg.setMsg(String.valueOf(time));
                        seekbar = verticalSeekBar.getProgress();
                        if(button_arm.getText() == "arm")
                        {
                            BTmsgbytes[0] = 0;
                            BTmsgbytes[1] = 0;
                            BTmsgbytes[2] = 0;
                            BTmsgbytes[3] = 0;
                            BTmsgbytes[4] = 0;
                            BTmsgbytes[5] = 0;
                            BTmsgbytes[6] = 0;
                            BTmsgbytes[7] = 0;
                        }
                        else
                        {
                            BTmsgbytes[8] = IntToByte(seekbar)[0];
                            BTmsgbytes[9] = IntToByte(seekbar)[1];
                            BTmsgbytes[4] = IntToByte((int)(orientation[1]*1000))[0];
                            BTmsgbytes[5] = IntToByte((int)(orientation[1]*1000))[1];
                            BTmsgbytes[2] = IntToByte((int)(orientation[2]*1000))[0];
                            BTmsgbytes[3] = IntToByte((int)(orientation[2]*1000))[1];
                        }

                        btmsg.setMsg(BTmsgbytes);


                        try {
                            outStream.write(btmsg.getCobs_msg());
                        } catch (IOException e) {
                            Log.e("daGloane", "Exception during write.", e);
                            finish();
                            return;
                        }


                        /*textview_pitch.setText(String.valueOf(orientation[0]));
                        textview_roll.setText(String.valueOf(orientation[1]));
                        textview_yaw.setText(String.valueOf(orientation[2]));*/
                    }

                });

            }

        },
        //Set how long before to start calling the TimerTask (in milliseconds)
        0,
        //Set the amount of time between each execution (in milliseconds)
        100);

    }

    private byte[] IntToByte(int value){
        return new byte[] {
                (byte)(value >>> 8),
                (byte)value};
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        if (sensorEvent.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
            mGravity = sensorEvent.values;
        if (sensorEvent.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD)
            mGeomagnetic = sensorEvent.values;
        if (mGravity != null && mGeomagnetic != null) {
            float R[] = new float[9];
            //float I[] = new float[9];
            boolean success = SensorManager.getRotationMatrix(R, null/*I*/, mGravity, mGeomagnetic);
            if (success) {

                SensorManager.getOrientation(R, orientation);
                //azimut = orientation[0]; // orientation contains: azimut, pitch and roll
            }
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_FASTEST);
    }

    @Override
    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(this);
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();

        sensorManager.unregisterListener(this);
        if(bluetooth_socket != null)
        {
            try {
                bluetooth_socket.close();
            } catch (IOException e2) {
                Log.e("daGloane",
                        "button_connectToDev_ClickLister: Unable to close socket during connection failure", e2);
            }
        }
        if(t != null)
            t.cancel();

        //BTadapter.disable();
    }

}