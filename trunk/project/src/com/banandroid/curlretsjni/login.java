package com.banandroid.curlretsjni;

import java.io.FileInputStream;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.GestureDetector.OnGestureListener;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewFlipper;

public class login extends Activity {
	ViewFlipper vf;
    /** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TextView  tv = new TextView(this);
        tv.setText( "Native Library Call" );
        ScrollView sv = new ScrollView(this);
        sv.addView(tv);
        setContentView(sv);
        tv.setText( curlretsjni.stringFromJNI().replaceAll("\r", "") );
        
	}






    	
}

