package com.example.pirobot_v3;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AbsListView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import com.gcssloop.widget.RockerView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.Charset;

public class MainActivity extends AppCompatActivity {

    private WebView webView;
    private RockerView rocker;
    private ListView listView;
    private Button button_left;
    private Button button_right;
    private Button button_up;
    private Button button_down;
    private Button button_stop;
    int count = 0;

    //Socket
    private String send_buff=null;
    private String recv_buff=null;

    private Handler handler = null;

    Socket socket = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        //----------------------------------------------------
        // WebView Init
        //----------------------------------------------------
        webView = (WebView) findViewById(R.id.webView);
        webView.loadUrl("http://172.20.10.9:5000");        //webView.loadUrl("http://www.google.com");
        //webView.loadUrl("http://www.google.com");
        // make the webview adapt to the screen
        WebSettings settings = webView.getSettings();
        settings.setUseWideViewPort(true);
        settings.setLoadWithOverviewMode(true);
        // display the video
        webView.setWebViewClient(new WebViewClient());
        webView.getSettings().setJavaScriptEnabled(true);
        webView.getSettings().setDomStorageEnabled(true);
        webView.setOverScrollMode(WebView.OVER_SCROLL_NEVER);
        //----------------------------------------------------

        //----------------------------------------------------
        // Rocker Init
        //----------------------------------------------------
        rocker = (RockerView) findViewById(R.id.rocker);

        if (null != rocker){
            rocker.setListener(new RockerView.RockerListener() {

                @Override
                public void callback(int eventType, int currentAngle, float currentDistance) {
                    switch (eventType) {
                        case RockerView.EVENT_ACTION:
                            // 触摸事件回调
                            count++;
                            if(currentAngle>70 && currentAngle<120 && count >10){
                                new Thread(new ClientThread("Move1")).start();
                                count = 0;
                            }else if (currentAngle>210 && currentAngle<280 &&count>10){
                                new Thread(new ClientThread("Move2")).start();
                                count = 0;
                            }
                            Log.e("EVENT_ACTION-------->", "angle="+currentAngle+" - distance"+currentDistance);

                            break;
                        case RockerView.EVENT_CLOCK:
                            // 定时回调
                            //Log.e("EVENT_CLOCK", "angle="+currentAngle+" - distance"+currentDistance);
                            break;
                    }
                }
            });
        }
        //----------------------------------------------------
        // Button Init
        //----------------------------------------------------
        button_down = (Button) findViewById(R.id.button_down);
        button_up = (Button) findViewById(R.id.button_up);
        button_left = (Button) findViewById(R.id.button_left);
        button_right = (Button) findViewById(R.id.button_right);
        button_stop = (Button) findViewById(R.id.button_stop);


        button_down.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                //Toast toast = Toast.makeText( MainActivity.this, "button_down被点击了", Toast.LENGTH_SHORT);
                //toast.show();

                new Thread(new ClientThread("Down")).start();



            }
        });
        button_up.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                //Toast toast = Toast.makeText( MainActivity.this, "Button_up被点击了", Toast.LENGTH_SHORT);
                //toast.show();
                new Thread(new ClientThread("Up")).start();

            }
        });
        button_left.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                //Toast toast = Toast.makeText( MainActivity.this, "button_left被点击了", Toast.LENGTH_SHORT);
                //toast.show();
                new Thread(new ClientThread("Left")).start();
                //Sender sender = new Sender();
                //sender.msg = "Left";
                //sender.execute();

            }
        });
        button_right.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                //Toast toast = Toast.makeText( MainActivity.this, "button_right被点击了", Toast.LENGTH_SHORT);
                //toast.show();
                new Thread(new ClientThread("Right")).start();
            }
        });

        button_stop.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                //Toast toast = Toast.makeText( MainActivity.this, "stop!", Toast.LENGTH_SHORT);
                //toast.show();
                new Thread(new ClientThread("Stop")).start();
            }
        });
        //690519

        //----------------------------------------------------
        // Socket Init
        //----------------------------------------------------





    }//Oncreate


    class ClientThread implements Runnable {
        private String msg;
        Socket s;
        PrintWriter pw;
        String type;
        BufferedReader bufferedReader;

        ClientThread(String msg) {
            this.msg = msg;
        }

        public void run() {
            try {
                s = new Socket("172.20.10.9", 7654);
                pw = new PrintWriter(s.getOutputStream());
                pw.write(msg);
                pw.flush();
                bufferedReader = new BufferedReader(new InputStreamReader(s.getInputStream()));
                String msg2 = bufferedReader.readLine();


                bufferedReader.close();
                pw.close();
                s.close();
            } catch (UnknownHostException e) {
                System.out.println("Fail");

                e.printStackTrace();
            } catch (IOException e) {
                System.out.println("Fail");
                e.printStackTrace();
            }
        }
    }

    /*class Sender extends AsyncTask<Void,Void,Void> {
        Socket s;
        PrintWriter pw;
        String msg;
        String type;
        BufferedReader bufferedReader;
        @SuppressLint("SetTextI18n")
        @Override
        protected Void doInBackground(Void...params){
            try {
                s = new Socket("172.20.10.2", 7654);
                pw = new PrintWriter(s.getOutputStream());
                pw.write(msg);
                pw.flush();
                bufferedReader = new BufferedReader(new InputStreamReader(s.getInputStream()));
                String msg2 = bufferedReader.readLine();



                bufferedReader.close();
                pw.close();
                s.close();
            } catch (UnknownHostException e) {
                System.out.println("Fail");

                e.printStackTrace();
            } catch (IOException e) {
                System.out.println("Fail");
                e.printStackTrace();
            }
            return null;
        }
    }*/

}