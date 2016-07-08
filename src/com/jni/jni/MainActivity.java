package com.jni.jni;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

	private TextView test;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		test = (TextView) findViewById(R.id.tst);
		String stTst = Jni.stTst();
		Jni j = new Jni();
		test.setText("静态方法:" + stTst + "\n非静态方法:" + j.tst());

	}

}
