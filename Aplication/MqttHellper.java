package com.example.test1;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MqttHellper {
    MqttAndroidClient client;
    MainActivity mainActivity;
    WidjetManager widjetManager;
    String uri;
    String user;
    String pass;
    String topics[];

    public void Connect(MainActivity mainAct) {
        mainActivity = mainAct;
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setAutomaticReconnect(true);
        mqttConnectOptions.setCleanSession(true);
        mqttConnectOptions.setUserName(user);
        mqttConnectOptions.setPassword(new String(pass).toCharArray());

        try {
            String clientId = MqttClient.generateClientId();
            client = new MqttAndroidClient(mainActivity.getApplicationContext(), uri, clientId);
            client.connect(mqttConnectOptions, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    mainActivity.OnConectedToMqtt();
                    Subscribe(topics);
                    Log.d("MqttHellper", "onSuccess");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    Log.e("MqttHellper", exception.getMessage());
                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                widjetManager.MqttMessageArrived(topic, message);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });
    }

    public void SetArrayTopics(String[] Topics){
        topics = Topics;
    }

    public void Publish(String topic, String value){
        try {
            client.publish(topic, value.getBytes(), 0, false);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public void Subscribe(String topic){
        try{
            client.subscribe(topic,0);
        }catch (MqttException e){
            e.printStackTrace();
        }
    }

    public void Subscribe(String Topics[]){
        try{
            for(int i = 0; i < Topics.length; i++)
                client.subscribe(Topics[i],0);
        }catch (MqttException e){
            e.printStackTrace();
        }
    }

    public MqttHellper(String Uri, String User, String Pass){
        uri = Uri;
        user = User;
        pass = Pass;
    }

}
