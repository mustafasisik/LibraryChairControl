package iot.chaircontrol;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    ImageView chair; // current chair image
    RequestQueue queue;
    private ArrayList<Entry> entries = new ArrayList<>(); // get last data from cloud as arraylist Entry is a new type to store read data.
    private boolean isEmpty = true; // chair is empty
    private int averageLight; // average light of room
    private int lastValue = 1000; // read last value read from cloud


    private Spinner spinner;
    private String[] minutes = {"1", "3", "5", "10", "20"};
    private int lastpostcount = 3; // default

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        queue = Volley.newRequestQueue(this); // using volley library
        chair = findViewById(R.id.chair);

        spinner = findViewById(R.id.spinnerMinute);
        spinner.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, minutes)); // spinner used to control to check last x minutes if chair is empty
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                lastpostcount = Integer.parseInt(minutes[position])*3; // average post interval is 20 sec in 1 minute 3 post sent from arduino.
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        refresh(); // it works every 2 second and get result and refresh page.
    }

    private void getResults() {
        // get Status
        isEmpty = true;
        entries.clear();
        String URL = "https://api.thingspeak.com/channels/454333/feeds.json?api_key=JTJJR3SFUAXE4S22&results=" + lastpostcount; // get request from thinkspeak server.
        StringRequest jsonObjReq = new StringRequest(Request.Method.GET, URL,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            JSONObject jo = new JSONObject(response);
                            JSONArray jsonArray = jo.getJSONArray("feeds");
                            for (int i = 0; i < jsonArray.length(); i++) {
                                JSONObject jsonObject = jsonArray.getJSONObject(i);
                                String time = jsonObject.getString("created_at"); // get post time
                                lastValue = jsonObject.getInt("field1"); // get chair light
                                averageLight = jsonObject.getInt("field2")/10; // get average 10% of room light
                                if (lastValue < averageLight){ // if last valur is smaller than average at the end user may be stand up or may leave chair.
                                    isEmpty = false;
                                }
                                entries.add(new Entry(time, lastValue));
                            }

                            if (!isEmpty){
                                if (lastValue < averageLight){
                                    chair.setImageDrawable(getResources().getDrawable(R.drawable.full)); // if last value smaller than %10 average light there is a person using chair
                                }else {
                                    chair.setImageDrawable(getResources().getDrawable(R.drawable.busy)); // if lastvalue bigger than %10 average light but in lastpostcount any of field1(chair light) is smaller than field2(room light) for any time.
                                }
                            }else {
                                chair.setImageDrawable(getResources().getDrawable(R.drawable.empty)); // chair is empty because any time in lastpostcount post chair light is not smaller than %10 of average ligth
                            }

                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {

            }
        }) {

            @Override
            protected Map<String, String> getParams() {
                Map<String, String> params = new HashMap<String, String>();
                params.put("type", "get"); // make get request to tkinkspeak server.
                return params;
            }
        };
        // Add the request to the RequestQueue.
        queue.add(jsonObjReq);
    }

    public void refresh(){
        new Handler().postDelayed(new Runnable() {

            @Override
            public void run() {
                getResults(); // get result again and again for every 2 seconds
                refresh(); // reset function for every 2 seconds.
            }
        }, 2000);
    }
}
