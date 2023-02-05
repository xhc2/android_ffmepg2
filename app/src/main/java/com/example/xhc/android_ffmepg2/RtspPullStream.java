package com.example.xhc.android_ffmepg2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InterruptedIOException;
import java.io.OutputStreamWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import okhttp3.Call;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

/**
 * rtsp 拉流实战
 * 1.就使用java 处理，主要是对协议的理解，先简单走走rtsp 流程，
 * 2.拿到rtp端口后，开始对rtp进行读，写入h264文件，和aac文件
 * 3.然后再简单分析下rtcp，和sdp，这个毕竟后续的webrtc 都会慢慢用上
 * https://blog.csdn.net/shaosunrise/article/details/80374523
 */
public class RtspPullStream extends AppCompatActivity {

    private String ip = "192.168.98.154";
    private int rtspPort = 554;
    private String options = "OPTIONS rtsp://192.168.98.154:554/test RTSP/1.0\\r\\n " +
            "Method: OPTIONS " +
            "URL: rtsp://192.168.98.154:554/test " +
            "CSeq: 1\\r\\n \\r\\n";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rtsp_pull_stream);
//        getSyn("http://"+ip+":"+rtspPort);
        new threadRtsp().start();
    }

    private static final int TIMEOUT = 5000;  //设置接收数据的超时时间
    private static final int MAXNUM = 5;      //设置重发数据的最多次数

    class threadRtp extends Thread {
        @Override
        public void run() {
            super.run();


            String str_send = "Hello";
            byte[] buf = new byte[1024];
            //客户端在9000端口监听接收到的数据
            DatagramSocket ds = null;
            try {
                ds = new DatagramSocket(9000);

                InetAddress loc = InetAddress.getByAddress(ip.getBytes());
                //定义用来发送数据的DatagramPacket实例
                DatagramPacket dp_send = new DatagramPacket(str_send.getBytes(), str_send.length(), loc, 10506);
                //定义用来接收数据的DatagramPacket实例
                DatagramPacket dp_receive = new DatagramPacket(buf, 1024);
                //数据发向本地3000端口
                ds.setSoTimeout(TIMEOUT);              //设置接收数据时阻塞的最长时间
                int tries = 0;                         //重发数据的次数
                boolean receivedResponse = false;     //是否接收到数据的标志位
                //直到接收到数据，或者重发次数达到预定值，则退出循环
                while (!receivedResponse && tries < MAXNUM) {
                    //发送数据
                    ds.send(dp_send);
                    try {
                        //接收从服务端发送回来的数据
                        ds.receive(dp_receive);
                        //如果接收到的数据不是来自目标地址，则抛出异常
                        if (!dp_receive.getAddress().equals(loc)) {
                            throw new IOException("Received packet from an umknown source");
                        }
                        //如果接收到数据。则将receivedResponse标志位改为true，从而退出循环
                        receivedResponse = true;
                    } catch (InterruptedIOException e) {
                        //如果接收数据时阻塞超时，重发并减少一次重发的次数
                        tries += 1;
                        System.out.println("Time out," + (MAXNUM - tries) + " more tries...");
                    }
                }
                if (receivedResponse) {
                    //如果收到数据，则打印出来
                    System.out.println("client received data from server：");
                    String str_receive = new String(dp_receive.getData(), 0, dp_receive.getLength()) +
                            " from " + dp_receive.getAddress().getHostAddress() + ":" + dp_receive.getPort();
                    System.out.println(str_receive);
                    //由于dp_receive在接收了数据之后，其内部消息长度值会变为实际接收的消息的字节数，
                    //所以这里要将dp_receive的内部消息长度重新置为1024
                    dp_receive.setLength(1024);
                } else {
                    //如果重发MAXNUM次数据后，仍未获得服务器发送回来的数据，则打印如下信息
                    System.out.println("No response -- give up.");
                }
                ds.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    class threadRtsp extends Thread {
        @Override
        public void run() {
            super.run();

            try {
                Socket s = new Socket(ip, rtspPort);

                BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));

                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));

                bw.write(options);
                bw.flush();

                int count = 100;
                while (count-- > 0) {
                    Log.e("xhc", "readline:" + br.readLine() + " isconnect " + s.isConnected());
                    Thread.sleep(100);
                }


            } catch (Exception e) {
                e.printStackTrace();
                Log.e("xhc", "e" + e.getMessage());
            }

        }
    }


}