//DEPRECATED - see zoom

package com.banandroid.curlretsjni;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

public class detail extends Activity {
    /** Called when the activity is first created. */
	ScrollView sv;
	


	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        Bundle b = getIntent().getExtras();
        String s = b.containsKey("com.banandroid.curlretsjni.ListingID") + "";
        s = b.getString("com.banandroid.curlretsjni.ListingID");
        Log.i("EXTRA", s);
        
        TextView  tv = new TextView(this);
        tv.setText( "The file downloaded by the NDK will be displayable in a future version.  You can access it now with the SDK Tools in the application directory/photo.jpg");
        ImageView iv = new ImageView(this);
        try {
        //login
        curlretsjni.stringFromJNI();
        //getObject
        String t = curlretsjni.stringFromJNI4(Integer.parseInt(s));
        //search
        String searchresponse = curlretsjni.stringFromJNI6(Integer.parseInt(s));
        //logout
        curlretsjni.stringFromJNI5();
        FileInputStream Fis = new FileInputStream("/data/data/com.banandroid.curlretsjni/photo" + s + ".jpg");
        Bitmap bm = BitmapFactory.decodeStream(Fis);
        iv.setImageBitmap(bm);
        iv.setMinimumHeight(200);
        
        sv = new ScrollView(this);
        sv.addView(iv);
        tv.setText(searchresponse);
        //sv.addView(tv);
        setContentView(sv);
        


        } catch (Exception E) {
        	Log.i("MARK", E.toString());
        	//Toast.makeText(this, E.toString(), 3).show();
        	//tv.setText("The file downloaded by the NDK will be displayable in a future version.  You can access it now with the SDK Tools in the application directory/photo.jpg");
        	//sv.addView(tv);
        	//tv.setText("Error retrieving photo.");
        	//setContentView(sv);
        }
        

    }

}