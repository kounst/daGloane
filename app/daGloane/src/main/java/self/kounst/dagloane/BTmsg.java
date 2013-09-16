package self.kounst.dagloane;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by konstantin on 08.09.13.
 */
public class BTmsg {

    //private List<Byte> msg;
    //private List<Byte> cobs_msg;

    private byte[] msg;
    private byte[] cobs_msg;

    public BTmsg(byte[] msg){
        setMsg(msg);
    }

    public BTmsg(String msg){
        setMsg(msg);
    }

    public void setMsg(byte[] msg) {
        this.msg = new byte[msg.length+2];
        for(int i = 0; i< msg.length; i++)
        {
            this.msg[i] = msg[i];
        }
        appendCRC();
        COBSencode();
    }

    public void setMsg(String msg){
        //char[] msg_charray = msg.toCharArray();
        this.msg = new byte[msg.length()+2];
        for(int i = 0; i< msg.length(); i++)
        {
            this.msg[i] = ((byte)msg.charAt(i));
        }
        appendCRC();
        COBSencode();
    }

    public byte[] getCobs_msg() {
        return cobs_msg;
    }

    public String getCobs_msgS() {
        return msg.toString();
    }


    private void appendCRC() {

        int crc = 0;
        for(int i = 0; i < msg.length-2; i++)
        {
            crc = crc ^ (msg[i] << 8);
            crc = crc & 0xffff;
            for (int j=0; j<8; j++)
            {
                if ((crc & 0x8000) > 0)

                    crc = ((crc << 1) & 0xffff) ^ 0x1021;
                else
                    crc <<= 1;
                crc = crc & 0xffff;
            }
        }

        msg[msg.length-2] = ((byte)((crc >> 8) & 0xFF));
        msg[msg.length-1] = ((byte)(crc & 0xFF));

    }


    private void COBSencode(){

        int read_index = 0;
        int write_index = 1;
        int code_index = 0;
        char code = 1;

        cobs_msg = new byte[msg.length+2];

        while(read_index < msg.length)
        {
            if(msg[read_index] == 0)
            {
                cobs_msg[code_index] = (byte)code;
                code = 1;
                code_index = write_index++;
                read_index++;
            }
            else
            {
                cobs_msg[write_index++] = msg[read_index++];
                code++;
                if(code == 0xFF)
                {
                    cobs_msg[code_index] = (byte)code;
                    //[code_index] = code;
                    code = 1;
                    code_index = write_index++;
                }
            }
        }

        cobs_msg[code_index] = (byte) code;
        cobs_msg[write_index] = 0;
    }

}
