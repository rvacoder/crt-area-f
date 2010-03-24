package com.banandroid.curlretsjni;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class curlretsjni extends ListActivity {
    /** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.action_row);
        //setContentView(R.layout.main);
        //tv.setText( stringFromJNI() );
        //tv.setText( stringFromJNI2() );
        //tv.setText( stringFromJNI3() );
        //setContentView(tv);
       /* try {
        File f = new File("/data/data/com.banandroid.curlretsjni/files/test.txt");
        f.createNewFile();
        FileOutputStream fOut = new FileOutputStream("/data/data/com.banandroid.curlretsjni/filestest.txt");
        OutputStreamWriter osw = new OutputStreamWriter(fOut);
        osw.write("Mark was here");
        osw.flush();
        osw.close();
        } catch (Exception e) {
        	Log.i("MARK",e.toString());
        	///data Log.i("MARK",Environment.getDataDirectory().toString());
        	///system Log.i("MARK", Environment.getRootDirectory().toString());
        	Log.i("MARK", getFilesDir().toString());
        	///data/data/com.banandroid.curlretsjni/files
        }
        */
        ArrayAdapter a;
        a = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1, ACTIONS);
        setListAdapter(a);
        getListView().setTextFilterEnabled(true); 

    }
    public void onListItemClick(ListView l, View v, int position, long id) {
    	Intent actionIntent;
    	switch(position) {
    	case 0:
    		actionIntent = new Intent(this, layout.class);
    		startActivity(actionIntent);
    		break;
    	case 1:
    		actionIntent = new Intent(this, login.class);
    		startActivity(actionIntent);
    		break;
    	case 2:
    		actionIntent = new Intent(this, metadata.class);
    		startActivity(actionIntent);
    		break;
    	case 3:
    		actionIntent = new Intent(this, search.class);
    		startActivity(actionIntent);
    		break;
    	case 4:
    		actionIntent = new Intent(this, getobj.class);
    		startActivity(actionIntent);
    		break;
    	case 5:
    		actionIntent = new Intent(this, logout.class);
    		startActivity(actionIntent);
    		break;
    	default:
    		Toast.makeText(curlretsjni.this, "action" + position, 3).show();

    	}
    }
    
    static final String[] ACTIONS = new String[]{"Prototype","Login","Get Metadata","Search","GetObject","Logout"};
    public native static String  stringFromJNI();
    public native static String  stringFromJNI2();
    public native static String  stringFromJNI3();
    public native static String  stringFromJNI5();
    public native static String  stringFromJNI4(int id);
    public native static String  stringFromJNI6(int id);
    
    static {
        System.loadLibrary("curlretsjni");       
    }
}