package com.example.waterinspect;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;


import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import android.content.Context;
import android.os.Vibrator;

import android.widget.CompoundButton;
import android.widget.RadioGroup;

import android.media.MediaPlayer;
import android.content.ContextWrapper;
import android.view.View;
import android.view.View.OnClickListener;




public class MainActivity extends AppCompatActivity {
    private ScheduledExecutorService scheduler;
    private Button btn_1;
    private Button btn_2;
    private Button btn_3;
    private Button btn_4;
    private ImageView image_1;
    private TextView tx_1;
    private TextView tx_2;
    private TextView tx_3;
    private TextView tx_4;
    private TextView tx_5;
    private EditText ed_1;
    private EditText ed_2;
    private EditText ed_3;
    private EditText ed_4;
    private CheckBox Cb_1;
    private MqttClient client;
    private MqttConnectOptions options;
    private Handler handler;
    private String userName = "android";
    private String passWord = "android";
    private String mqtt_id = "ESP82"; //
    private String mqtt_sub_topic = "temp2";
    private String mqtt_pub_topic = "attain";
    private String temp;
    private boolean tur_flag=false;;
    private boolean tem_flag=false;;
    private boolean ph_flag=false;;
    private boolean warring=false;
    private boolean warring1=false;
    private int tur_number=0;
    private int tem_number=0;
    private int ph_number=0;
    private MediaPlayer mediaPlayer;
    private Vibrator vibrator;

    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        //这里是界面打开后 最先运行的地方
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // 对应界面UI
        //一般先用来进行界面初始化 控件初始化  初始化一些参数和变量。。。。。
        //不恰当比方    类似于 单片机的   main函数
        Cb_1 = findViewById(R.id.Cb_1); // 寻找xml里面真正的id  与自己定义的id绑定
        btn_1 = findViewById(R.id.bu_1); // 寻找xml里面真正的id  与自己定义的id绑定
        btn_2 = findViewById(R.id.bu_2); // 温度
        btn_3 = findViewById(R.id.bu_3); // PH
        btn_4 = findViewById(R.id.bu_4); // 浊度
        tx_1 = findViewById(R.id.tx_1); // 寻找xml里面真正的id  与自己定义的id绑定
        tx_2 = findViewById(R.id.tx_2);
        tx_3 = findViewById(R.id.tx_3); // 寻找xml里面真正的id  与自己定义的id绑定
        tx_4 = findViewById(R.id.tx_4);
        tx_5 = findViewById(R.id.tx_5); // 寻找xml里面真正的id  与自己定义的id绑定
        ed_1 = findViewById(R.id.ed_1); // 寻找xml里面真正的id  与自己定义的id绑定
        ed_2 = findViewById(R.id.ed_2); // 温度
        ed_3 = findViewById(R.id.ed_3); // PH
        ed_4 = findViewById(R.id.ed_4); // 浊
        publishmessageplus(mqtt_pub_topic,mqtt_pub_topic);
        Cb_1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    warring=true;
                }else{
                    warring=false;
                }
            }
        });

        btn_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                temp= ed_2.getText().toString();
                tem_number = Integer.parseInt(temp)*10;
                temp= ed_3.getText().toString();
                ph_number = Integer.parseInt(temp)*10;
                temp= ed_4.getText().toString();
                tur_number = Integer.parseInt(temp);
                Mqtt_init();
                startReconnect();
                handler.post(runnable);
            }
        });

        btn_2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                temp= ed_2.getText().toString();
                tem_number = Integer.parseInt(temp)*10;
            }
        });

        btn_3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                temp= ed_3.getText().toString();
                ph_number = Integer.parseInt(temp)*10;
            }
        });

        btn_4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                temp= ed_4.getText().toString();
                tur_number = Integer.parseInt(temp);
            }
        });

        handler = new Handler() {
            @SuppressLint("SetTextI18n")
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 1: //开机校验更新回传
                        break;
                    case 2:  // 反馈回传
                        break;
                    case 3:  //MQTT 收到消息回传   UTF8Buffer msg=new UTF8Buffer(object.toString());
                        //Toast.makeText(MainActivity.this,msg.obj.toString() ,Toast.LENGTH_SHORT).show();
                        String tur = msg.obj.toString().substring(msg.obj.toString().indexOf("Tur:") + 4, msg.obj.toString().indexOf("--Tem"));
                        if(Integer.parseInt(tur)>tur_number){
                            tur_flag=true;
                        }else{
                           tur_flag=false;
                        }
                        tx_1.setText("浊度:" + tur+"%");

                        String tem = msg.obj.toString().substring(msg.obj.toString().indexOf("Tem:") + 4, msg.obj.toString().indexOf("--Ele"));
                        if(Integer.parseInt(tem)>tem_number){
                            tem_flag=true;
                        }else{
                            tem_flag=false;
                        }
                        float tem_f=(float)Integer.parseInt(tem)/10;
                        tx_2.setText("水温:" + tem_f+"°C");

                        String Ele = msg.obj.toString().substring(msg.obj.toString().indexOf("Ele:") + 4, msg.obj.toString().indexOf("--Ph"));
                        tx_3.setText("Tds:" + Ele);


                        String PH = msg.obj.toString().substring(msg.obj.toString().indexOf("Ph:") + 3, msg.obj.toString().indexOf("--Wael"));
                        if(Integer.parseInt(PH)>ph_number){
                            ph_flag=true;
                        }else{
                            ph_flag=false;
                        }
                        float ph_f=(float)Integer.parseInt(PH)/10;
                        tx_4.setText("Ph值:" + ph_f);

                        String Wael = msg.obj.toString().substring(msg.obj.toString().indexOf("Wael:") + 5);
                        tx_5.setText("水位:" + Wael);



                        break;
                    case 30:  //连接失败
                        Toast.makeText(MainActivity.this, "连接失败", Toast.LENGTH_SHORT).show();
                        break;
                    case 31:   //连接成功
                        Toast.makeText(MainActivity.this, "连接成功", Toast.LENGTH_SHORT).show();
                        try {
                            client.subscribe(mqtt_sub_topic, 1);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                        break;
                    default:
                        break;
                }
            }
        };
    }
    public void playMusic() {
        if (mediaPlayer != null) {
            if (mediaPlayer.isPlaying()) {
                mediaPlayer.stop();
            }
            mediaPlayer.release();
            mediaPlayer = null;
        }
        mediaPlayer = MediaPlayer.create(this, R.raw.warring);
        // 确保 mediaPlayer 已正确创建再播放音乐
        if (mediaPlayer != null) {
            mediaPlayer.start();
        }
    }

    private final Handler handler1 = new Handler();
    private final Runnable runnable = new Runnable() {
        @Override
        public void run() {
            // 在这里执行你的函数
            if(warring&&(tur_flag||tem_flag||ph_flag)){
                vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
                vibrator.vibrate(500);
                playMusic();
                warring1=true;
            }
            if(warring==false&&warring1==true){
                vibrator.cancel();
                mediaPlayer.stop();
                mediaPlayer.release();
                mediaPlayer = null;
                warring1=false;
            }
            // 在指定的延迟后再次执行
            handler.postDelayed(this, 1000); // 1000毫秒后再次执行
        }
    };


    private void Mqtt_init() {
        try {
            //host为主机名，test为clientid即连接MQTT的客户端ID，一般以客户端唯一标识符表示，MemoryPersistence设置clientid的保存形式，默认为以内存保存
            client = new MqttClient("tcp://" + ed_1.getText(), mqtt_id,
                    new MemoryPersistence());
            //MQTT的连接设置
            options = new MqttConnectOptions();
            //设置是否清空session,这里如果设置为false表示服务器会保留客户端的连接记录，这里设置为true表示每次连接到服务器都以新的身份连接
            options.setCleanSession(true);
            //设置连接的用户名
            options.setUserName(userName);
            //设置连接的密码
            options.setPassword(passWord.toCharArray());
            // 设置超时时间 单位为秒
            options.setConnectionTimeout(10);
            // 设置会话心跳时间 单位为秒 服务器会每隔1.5*20秒的时间向客户端发送个消息判断客户端是否在线，但这个方法并没有重连的机制
            options.setKeepAliveInterval(20);
            //设置回调
            client.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    //连接丢失后，一般在这里面进行重连
                    System.out.println("connectionLost----------");
                    //startReconnect();
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    //publish后会执行到这里
                    System.out.println("deliveryComplete---------"
                            + token.isComplete());
                }

                @Override
                public void messageArrived(String topicName, MqttMessage message)
                        throws Exception {
                    //subscribe后得到的消息会执行到这里面
                    System.out.println("messageArrived----------");
                    Message msg = new Message();
                    msg.what = 3;   //收到消息标志位
                    msg.obj = topicName + "---" + message.toString();
                    handler.sendMessage(msg);    // hander 回传
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void Mqtt_connect() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (!(client.isConnected()))  //如果还未连接
                    {
                        client.connect(options);
                        Message msg = new Message();
                        msg.what = 31;
                        handler.sendMessage(msg);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    Message msg = new Message();
                    msg.what = 30;
                    handler.sendMessage(msg);
                }
            }
        }).start();
    }

    private void startReconnect() {
        scheduler = Executors.newSingleThreadScheduledExecutor();
        scheduler.scheduleAtFixedRate(new Runnable() {
            @Override
            public void run() {
                if (!client.isConnected()) {
                    Mqtt_connect();
                }
            }
        }, 0 * 1000, 10 * 1000, TimeUnit.MILLISECONDS);
    }

    private void publishmessageplus(String topic, String message2) {
        if (client == null || !client.isConnected()) {
            return;
        }
        MqttMessage message = new MqttMessage();
        message.setPayload(message2.getBytes());
        try {
            client.publish(topic, message);
        } catch (MqttException e) {

            e.printStackTrace();
        }
    }






}









