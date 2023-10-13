package com.example.test1;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.android.service.MqttAndroidClient;
/*import org.videolan.libvlc.LibVLC;
import org.videolan.libvlc.Media;
import org.videolan.libvlc.MediaPlayer;
import org.videolan.libvlc.util.VLCVideoLayout;*/

import java.lang.reflect.Field;

public class MainActivity extends AppCompatActivity {

    MqttAndroidClient client;
    View constraintLayout;
    MqttHellper mqttHellper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mqttHellper = new MqttHellper("tcp://m4.wqtt.ru:5140", "u_50UPHV", "DRvhTF7K");
        String[] subscribedTopics = {"servoesp", "led", "temp", "label", "rkot", "rkon", "umsvet", "umkon", "umkot",
        "ikot", "isvet", "ikon", "hum", "tempotkl", "water", "flame", "vibr", "pir", "door", "servo"};
        mqttHellper.SetArrayTopics(subscribedTopics);
        mqttHellper.Connect(this);

        WidjetManager widjetManager = new WidjetManager(mqttHellper);
        widjetManager.StartInit(findViewById(R.id.TopView));
        mqttHellper.widjetManager = widjetManager;
    }

    public void OnConectedToMqtt() {

    }
}









    /*private LibVLC libVlc;
    private MediaPlayer mediaPlayer;
    private VLCVideoLayout videoLayout;*/
/*libVlc = new LibVLC(this);
        mediaPlayer = new MediaPlayer(libVlc);
        videoLayout = findViewById(R.id.videoLayout);
        mediaPlayer.attachViews(videoLayout, null, false, false);
        Media media = new Media(libVlc, Uri.parse("rtsp://192.168.74.101:8554/mjpeg/1"));
        media.setHWDecoderEnabled(true, false);
        media.addOption(":network-caching=600");
        mediaPlayer.setMedia(media);
        media.release();
        mediaPlayer.play();*/
    /*@Override
    protected void onDestroy()
    {
        super.onDestroy();

        mediaPlayer.release();
        libVlc.release();
    }*/

    /*<org.videolan.libvlc.util.VLCVideoLayout
        android:id="@+id/videoLayout"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:rotation="0" />*/