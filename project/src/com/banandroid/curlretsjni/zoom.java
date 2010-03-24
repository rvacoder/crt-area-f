package com.banandroid.curlretsjni;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnLongClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

public class zoom extends Activity {
    /** Called when the activity is first created. */
	TextView header;
	TextView details;
	boolean picbig = true;
	String detailstring;
	String id;
	String address;
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        
        //GET NEW DATA
        Bundle b = getIntent().getExtras();
        //id = b.containsKey("com.banandroid.curlretsjni.ListingID") + "";
        id = b.getString("com.banandroid.curlretsjni.ListingID");
        detailstring = b.getString("com.banandroid.curlretsjni.DetailString");
        address = b.getString("com.banandroid.curlretsjni.Address");
        Log.i("EXTRA", id);
        Log.i("EXTRA", detailstring);
        Log.i("EXTRA", address);
        
        //DO VIEW STUFF
        
        //HEADER
        setContentView(R.layout.zoom);
        header=(TextView)findViewById(R.id.selection);
        header.setText("Listing ID " + id);
        
        //DETAILS
        details=(TextView)findViewById(R.id.details);
        details.setText(detailstring);

        //IMAGE
        ImageView icon=(ImageView)findViewById(R.id.icon);
		try {
			FileInputStream Fis = new FileInputStream("/data/data/com.banandroid.curlretsjni/photo" + id + ".jpg");
			Bitmap bm = BitmapFactory.decodeStream(Fis);
			icon.setImageBitmap(bm);
			} catch(Exception e) {
				Log.i("exc", e.toString());
			}
		//icon.setOnLongClickListener(onIconLongClickListener);

		//BUTTONS
		Button map = (Button)findViewById(R.id.map);
		map.setText("Show on Map");
		map.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	//Toast.makeText(v.getContext(), "you click map", 3).show();
            	mapper(address);
            }
        });
		Button email = (Button)findViewById(R.id.email);
		email.setText("Email Listing");
		email.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	//Toast.makeText(v.getContext(), "you click email", 3).show();
            	emailer(detailstring, id);
            }
        });
    }
	
	// Create an anonymous implementation of OnLongClickListener
	private OnLongClickListener onIconLongClickListener = new OnLongClickListener() {
	    public boolean onLongClick(View v) {
	    	//THIS METHOD CRASHES PROGRAM LOOK INTO LATER
	    	Toast.makeText(v.getContext(), "you click long on pic", 3).show();
	    	ImageView icon=(ImageView)findViewById(R.id.icon);
	    	icon.setAdjustViewBounds(true);
	    	if(picbig) {
		    	icon.setMaxHeight(40);
		    	icon.setMaxWidth(30);
		    	picbig = false;
	    	} else {
		    	icon.setMaxHeight(160);
		    	icon.setMaxWidth(120);
		    	picbig = true;	    		
	    	}
	    	setContentView(R.id.icon);
	    	return true;
	    }
	};

	private void emailer(String content, String id) {
		Intent sendIntent = new Intent(Intent.ACTION_SEND);
		sendIntent.putExtra(Intent.EXTRA_TEXT, "Hi!  This is a listing I thought you might be interested in, the details are below: \n\n" + content);
		sendIntent.putExtra(Intent.EXTRA_SUBJECT, "Listing Info (Listing ID: " + id +")" );
		sendIntent.putExtra(Intent.EXTRA_STREAM, Uri.parse("file:///data/data/com.banandroid.curlretsjni/photo"+id+".jpg"));
		sendIntent.setType("jpeg/image"); 
		//sendIntent.setType("text/plain");
		startActivity(Intent.createChooser(sendIntent, "Send Listing Email")); 
	}
	private void mapper(String address) {
		try {
			//Toast.makeText(this, "geo:0,0?q="+address.replace(" ", "+"), 3).show();
		String uri = "geo:0,0?q="+address.replace(" ", "+");  
		startActivity(new Intent(android.content.Intent.ACTION_VIEW, Uri.parse(uri)));
		} catch(Exception e) {
			Log.i("MARK", e.toString());
		}
		}
}