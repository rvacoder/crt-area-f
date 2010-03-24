package com.banandroid.curlretsjni;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.ScrollView;
import android.widget.TextView;

public class metadata extends Activity {
    /** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TextView  tv = new TextView(this);
        tv.setText( "Native Library Call" );
        ScrollView sv = new ScrollView(this);
        sv.addView(tv);
        setContentView(sv);
        tv.setText( curlretsjni.stringFromJNI2().replaceAll("\r", "") );
    }

}