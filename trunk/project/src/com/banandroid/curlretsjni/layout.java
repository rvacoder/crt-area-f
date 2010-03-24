package com.banandroid.curlretsjni;

import java.io.FileInputStream;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.GestureDetector.OnGestureListener;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewFlipper;

public class layout extends ListActivity {

	TextView selection;
	String ActionLog = "";
	listingRecord lrs[] = null;
	String[] salrs;
	String[] salrs2;
	
    /** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
    try {
    	super.onCreate(savedInstanceState);
    
        setContentView(R.layout.main);
        selection=(TextView)findViewById(R.id.selection);
        ActionLog("Loading Native RETS Engine");
        //DO RETS STUFF
        //LOGIN
        ActionLog("Begin LOGIN");
    	String loginresponse = curlretsjni.stringFromJNI();
    	ActionLog("Complete LOGIN");
    	//SEARCH - RES UNDER 500000
    	ActionLog("SEARCH for properties");
    	String searchresponse = curlretsjni.stringFromJNI3();
    	ActionLog("SEARCH complete");
    	int ct = 0; 
    	int recordcount = 0;
    	//PARSE XML RESPONSE
    	ActionLog("PARSE XML Record Set");
    	lrs = parsesearch(searchresponse);
    	ActionLog("PARSE Complete");
    	ActionLog("RETRIEVE PHOTOS");
    	//GET PHOTOS FOR ALL RECORDS AND COUNT RECORDS
    	while(lrs[ct] != null) {
    		//POSSIBLE FUTURE OPTIMIZATION - CHECK FOR LOCAL FILE AND AVOID PHOTO DOWNLOAD IF DETECTED
    		String t = curlretsjni.stringFromJNI4(Integer.parseInt(lrs[ct].ListingID));
    		recordcount++;
    		ct++;
    	}
    	ActionLog("DOWNLOAD COMPLETE - " + recordcount + " RECORDS AND PHOTOS");
    	ct = 0;
    	//SALRS stands for String Array (of) Listing Records
    	salrs = new String[recordcount];
    	//SALRS2 has second line of listing details
    	salrs2 = new String[recordcount];
    	searchresponse = "";
    	while(lrs[ct]!=null) 
    	{
    		salrs[ct] = lrs[ct].print();
    		salrs2[ct] = lrs[ct].print2();
    		ct++;
    	}
    	ActionLog("LOGOUT");
    	//LOGOUT
    	String logoutresponse = curlretsjni.stringFromJNI5();    	
    	//END RETS STUFF
    	ActionLog("LOGOUT COMPLETE");
        //CUSTOM LIST VIEW CREATION
    	setListAdapter(new durdenAdapter());
        ActionLog(recordcount + " listings displayed in summary mode");
        selection.setText(recordcount + " listings displayed");

        //WIRE UP CLICK OF TOP TEXT TO TOAST OF ACTIONS
        selection.setOnLongClickListener(onSelectionLongClickListener);
    } catch(Exception e) {
    	Log.i("exc", e.toString());
    }
}

// Create an anonymous implementation of OnLongClickListener
private OnLongClickListener onSelectionLongClickListener = new OnLongClickListener() {
    public boolean onLongClick(View v) {
    	Toast t = Toast.makeText(v.getContext(), ActionLog, 3);
    	t.setDuration(Toast.LENGTH_LONG);
    	t.show();
    	return true;
    }
};

public void onListItemClick(ListView l, View v, int position, long id) {
	Intent actionIntent;
	switch(position) {
	default:
		Log.i("INTENT",this.lrs[position].ListingID);
		actionIntent = new Intent(this, zoom.class);
		actionIntent.putExtra("com.banandroid.curlretsjni.ListingID", this.lrs[position].ListingID);
		actionIntent.putExtra("com.banandroid.curlretsjni.DetailString", this.lrs[position].printDetails());
		actionIntent.putExtra("com.banandroid.curlretsjni.Address", this.lrs[position].Address);		
		startActivity(actionIntent);
		break;
	}
}

class durdenAdapter extends ArrayAdapter {
	durdenAdapter() {
		super(layout.this, R.layout.row, salrs);
	}
	
	public View getView(int position, View convertView, ViewGroup parent) {
		LayoutInflater inflater=getLayoutInflater();
		View row=inflater.inflate(R.layout.row, parent, false);
		TextView label=(TextView)row.findViewById(R.id.label);
		TextView label2=(TextView)row.findViewById(R.id.label2);
		
		label.setText(salrs[position]);
		label2.setText(salrs2[position]);
		
		//alternate row color - dark gray
		if(position % 2 == 0) {
			row.setBackgroundColor(0x30808080);
		}
		
		ImageView icon=(ImageView)row.findViewById(R.id.icon);
		String id = lrs[position].ListingID;
		try {
		FileInputStream Fis = new FileInputStream("/data/data/com.banandroid.curlretsjni/photo" + id + ".jpg");
		Bitmap bm = BitmapFactory.decodeStream(Fis);
		icon.setImageBitmap(bm);
		} catch(Exception e) {
			Log.i("exc", e.toString());
		}

		return(row);
			
	}
}

public void ActionLog(String note) {
	Date todaysDate = new java.util.Date();
	SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");

	String formattedDate = formatter.format(todaysDate);
	
	ActionLog += formattedDate + " " + note + "\n";
	
	return;
}


private listingRecord[] parsesearch(String input)
{
    String StreetNumber;
    String StreetDirection;
    String StreetName;
    String City;
    String State;
    String ZipCode;
	String output = "";

	listingRecord[] lrs = new listingRecord[10];

	try {
	String[] fieldnames;
	String[][] fieldvalues = null;
	
	//parse fieldnames
	String[] a = input.split("<COLUMNS>");
	Log.i("a",Arrays.toString(a));
	String[] b = a[1].split("</COLUMNS>");
	Log.i("b",Arrays.toString(b));
	//There is a leading tab we need to remove, thus the replace method on next line
	String[] c = b[0].replaceFirst("\t", "").split("\t");
	Log.i("c",Arrays.toString(c));
	
	fieldnames = c;
	
	//parse fieldvalues
	a = null;
	a = input.split("<DATA>");
	Log.i("a",Arrays.toString(a));
    int ct = 0, ct2 = 0;
    //a is [junk,record,record ...]
    for(String s : a) {
            if (ct == 0) {
            	ct++;
            	continue;
            }
           b = null;
           b = s.split("</DATA>")[0].replaceFirst("\t","").split("\t");
           Log.i(ct+"",Arrays.toString(b));

           ct++;
           
           //b has values for record ct, lets print it using fieldnames

           ct2 = 0;
           StreetNumber = "";
           StreetDirection = ""; 
           StreetName = "";
           City = "";
           State = "";
           ZipCode = "";
           
    		listingRecord lr = new listingRecord();
    		for(String t : b) {
    			if(fieldnames[ct2].equals("ListPrice"))
    				lr.ListPrice = t;
    			if(fieldnames[ct2].equals("ListingID"))
    				lr.ListingID = t;
    			if(fieldnames[ct2].equals("Bedrooms"))
    				lr.Bedrooms = t;
    			if(fieldnames[ct2].equals("Baths"))
    				lr.Baths = t;
    			if(fieldnames[ct2].equals("YearBuilt"))
    				lr.YearBuilt = t;
    			if(fieldnames[ct2].equals("LivingArea"))
    				lr.LivingArea = t;
    			if(fieldnames[ct2].equals("AgentID"))
    				lr.AgentID = t;
    			if(fieldnames[ct2].equals("SqFt"))
    				lr.SqFt = t;
    			if(fieldnames[ct2].equals("County"))
    				lr.County = t;
    			if(fieldnames[ct2].equals("Garage"))
    				lr.Garage = t;
    			
    			if(fieldnames[ct2].equals("StreetNumber"))
    				StreetNumber = t;
    			if(fieldnames[ct2].equals("StreetDirection"))
    				StreetDirection = t;
    			if(fieldnames[ct2].equals("StreetName"))
    				StreetName = t;
    			if(fieldnames[ct2].equals("City"))
    				City = t;
    			if(fieldnames[ct2].equals("State"))
    				State = t;
    			if(fieldnames[ct2].equals("ZipCode"))
    				ZipCode = t;
    			
    			lr.Address = StreetNumber + " " + StreetDirection + " " + StreetName + " " + City + " " + State + " " + ZipCode;

    			output += fieldnames[ct2] + ": " + t + "\n";
    			ct2++;
    		}
			Log.i("" + (ct-2), lr.print());
			lrs[ct-2] = lr;
    		output+="\n";
            //max 10 records
            if(ct == 9)
         	   break;
    }


	} catch(Exception e) {
		Log.i("MARK", e.toString());
	}
	return lrs;

}



    	
}

