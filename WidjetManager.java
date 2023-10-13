package com.example.test1;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import androidx.constraintlayout.widget.ConstraintLayout;

import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.HashMap;
import java.util.Map;

import pl.pawelkleczkowski.customgauge.CustomGauge;

public class WidjetManager {
    MqttHellper mqttHellper;
    Map<String, ImageButton> imageButtons;
    Map<String, CustomGauge> customGauges;
    Map<String, TextView> textViews;
    Map<String, SeekBar> seekBars;
    Map<String, ImageView> imageViews;
    public void StartInit(ConstraintLayout layout){
        imageButtons = new HashMap<String, ImageButton>();
        customGauges = new HashMap<String, CustomGauge>();
        textViews = new HashMap<String, TextView>();
        seekBars = new HashMap<String, SeekBar>();
        imageViews = new HashMap<String, ImageView>();

        for (int i = 0; i < layout.getChildCount(); i++) {
            View view = layout.getChildAt(i);

            if(view instanceof ImageButton) {
                ImageButton imageButton = (ImageButton) view;
                SetImageViewCallback(imageButton);
                imageButtons.put((String) imageButton.getTag(), imageButton);
            }else if(view instanceof CustomGauge){
                CustomGauge customGauge = (CustomGauge) view;
                customGauges.put((String) customGauge.getTag(), customGauge);
            }else if(view instanceof TextView){
                TextView textView = (TextView) view;
                textViews.put((String) textView.getTag(), textView);
            }else if(view instanceof SeekBar){
                SeekBar seekBar = (SeekBar) view;
                seekBars.put((String) view.getTag(), seekBar);
                SetSeekBarCallback((seekBar));
            }
            else if(view instanceof ImageView){
                ImageView imageView = (ImageView) view;
                imageViews.put((String) view.getTag(), imageView);
            }
        }
    }

    public void MqttMessageArrived(String topic, MqttMessage message){
        Log.i("MqttHellper", topic + ": " + new String(message.getPayload()));
        String messageValue = new String(message.getPayload());

        if(imageButtons.get(topic) != null) {
            ImageButton imageButton = imageButtons.get(topic);
            imageButton.setAlpha((messageValue).equals("1") ? 1f : 0.05f);
        }

        if(imageViews.get(topic) != null){
            ImageView imageView = imageViews.get(topic);
            imageView.setAlpha((messageValue).equals("1") ? 1f : 0.05f);
        }

        if(customGauges.get(topic) != null){
            CustomGauge customGauge = customGauges.get(topic);
            int value = Integer.parseInt(messageValue);
            int endValue = customGauge.getEndValue();
            int startValue = customGauge.getStartValue();

            float minValue = endValue - (endValue - startValue) * 0.2f;
            float maxValue = (startValue - (endValue - startValue)) + (endValue - startValue) * 0.2f;

            if(minValue <  value)
                value = (int)(minValue);
            else if(maxValue >  value)
                value = (int)maxValue;
            customGauge.setValue(value);
        }

        if(textViews.get(topic) != null){
            TextView textView = textViews.get(topic);
            textView.setText(messageValue);
        }

        if(seekBars.get(topic) != null){
            SeekBar seekBar = seekBars.get(topic);
            seekBar.setProgress(Integer.parseInt(messageValue));
        }
    }

    void SetSeekBarCallback(SeekBar seekBar){
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            int value;

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                value = progress;
                textViews.get((String) seekBar.getTag()).setText(Integer.toString((value)));
            }

            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                mqttHellper.Publish((String) seekBar.getTag(), Integer.toString(value));
            }
        });
    }

    void SetImageViewCallback(ImageButton imageButton){
        imageButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
                if (imageButton.getAlpha() == 0.05f)
                {
                    mqttHellper.Publish((String) view.getTag(), "1");
                    imageButton.setAlpha(1f);
                } else {
                    mqttHellper.Publish((String) view.getTag(), "0");
                    imageButton.setAlpha(0.05f);
                }
            }
        });
    }

    WidjetManager(MqttHellper mqttHellper1){
        mqttHellper = mqttHellper1;
    }
}
