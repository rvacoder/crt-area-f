//DEPRECATED - see zoom

package com.banandroid.curlretsjni;

import java.io.FileInputStream;
import java.util.Arrays;

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
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewFlipper;

public class combo extends ListActivity {

	
	
	//ViewFlipper vf;
	listingRecord lrs[] = null;
    /** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        
    	
    	String loginresponse = curlretsjni.stringFromJNI();
    	String searchresponse = curlretsjni.stringFromJNI3();
    	String logoutresponse = curlretsjni.stringFromJNI5();
	
    	
    	int ct = 0; 
    	int recordcount = 0;
    	lrs = parsesearch(searchresponse);
    	//get recordcount
    	while(lrs[ct++] != null)
    		recordcount++;
    	ct = 0;
    	String[] salrs = new String[recordcount];
    	searchresponse = "";
    	while(lrs[ct]!=null) 
    	{
    		salrs[ct] = lrs[ct].print();
    		ct++;
    	}


        ArrayAdapter a;
        a = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1, salrs);
        setListAdapter(a);
        getListView().setTextFilterEnabled(true); 


   /* FLIP STUFF 	
    	TextView  tv = new TextView(this);
        TextView  tv2 = new TextView(this);
        TextView  tv3 = new TextView(this);
        tv.setText( loginresponse );
        tv2.setText( searchresponse );
        tv3.setText( logoutresponse );
        
        ScrollView sv = new ScrollView(this);
        ScrollView sv2 = new ScrollView(this);
        ScrollView sv3 = new ScrollView(this);
        sv.addView(tv);
        sv2.addView(tv2);
        sv3.addView(tv3);
        
        //Flipper setup
        vf = new ViewFlipper(this);
        vf.addView(sv);
        vf.addView(sv2);
        vf.addView(sv3);

 
        vf.setOnClickListener(mCorkyListener); 
        vf.setOnLongClickListener(myLCListener);
        setContentView(vf);
  */      
}

public void onListItemClick(ListView l, View v, int position, long id) {
	Intent actionIntent;
	switch(position) {
	default:
		actionIntent = new Intent(this, detail.class);
		actionIntent.putExtra("com.banandroid.curlretsjni.ListingID", this.lrs[position].ListingID);
		startActivity(actionIntent);
		//Toast.makeText(this,"item: " + position + this.lrs[position].ListingID,3).show();
		break;
	}
}
/*	
public boolean onKeyUp(int keyCode, KeyEvent event) {


                Log.i("MARK", "key pressed " + keyCode);
                if(keyCode==20 || keyCode==19)
                	return true; //up or downn, allow vertical scrolling
               if(keyCode<30) 
            	   vf.showPrevious();
               else
            	   vf.showNext();
                return true;


} 

	// Create an anonymous implementation of OnClickListener
	private OnClickListener mCorkyListener = new OnClickListener() {
	    public void onClick(View v) {
	    	Log.i("MARK", "onClick");
	    	vf.showNext();
	    }
	};
	// Create an anonymous implementation of OnLongClickListener
	private OnLongClickListener myLCListener = new OnLongClickListener() {
	    public boolean onLongClick(View v) {
	    	Log.i("MARK", "onLongClick");
	    	//emailer();
	    	mapper();
	    	return false;
	    }
	};
	
*/
	private void emailer() {
		/*
		final Intent emailIntent = new Intent(android.content.Intent.ACTION_SEND);
		emailIntent .setType("plain/text");
		emailIntent .putExtra(android.content.Intent.EXTRA_EMAIL, new String[]{"webmaster@website.com"});
		emailIntent .putExtra(android.content.Intent.EXTRA_SUBJECT, "SUBJECT");
		emailIntent .putExtra(android.content.Intent.EXTRA_TEXT, "Body Text");
		this.startActivity(Intent.createChooser(emailIntent, "Send mail..."));
		*/
		Intent sendIntent = new Intent(Intent.ACTION_SEND);
		sendIntent.putExtra(Intent.EXTRA_TEXT, "2 bed 2 bath property at 123 Mellow Lane");
		sendIntent.putExtra(Intent.EXTRA_SUBJECT, "Listing Info");
		sendIntent.setType("text/plain");
		startActivity(Intent.createChooser(sendIntent, "Send Listing Email")); 
	}
	private void mapper() {
		try {
		String uri = "geo:0,0?q=3309+s+pontiac+st+80224";  
		startActivity(new Intent(android.content.Intent.ACTION_VIEW, Uri.parse(uri)));
		} catch(Exception e) {
			Log.i("MARK", e.toString());
		}
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

