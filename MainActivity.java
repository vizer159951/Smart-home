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
import java.lang.reflect.Field;

public class MainActivity extends AppCompatActivity {

    MqttAndroidClient client;
    View constraintLayout;
    MqttHellper mqttHellper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mqttHellper = new MqttHellper("tcp://*****.**:****", "************", "*********");
        String[] subscribedTopics = {************************************************
        **************************************************************};
        mqttHellper.SetArrayTopics(subscribedTopics);
        mqttHellper.Connect(this);

        WidjetManager widjetManager = new WidjetManager(mqttHellper);
        widjetManager.StartInit(findViewById(R.id.TopView));
        mqttHellper.widjetManager = widjetManager;
    }

    public void OnConectedToMqtt() {

    }
}
