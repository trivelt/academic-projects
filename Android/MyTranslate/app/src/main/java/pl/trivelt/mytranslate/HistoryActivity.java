package pl.trivelt.mytranslate;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.Arrays;

public class HistoryActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_history);

        ArrayList<String> historyArrayList = new ArrayList<>();
        Bundle b = this.getIntent().getExtras();
        final ArrayList<TranslationHistoryObject> history = b.getParcelableArrayList("history");
        for(int i = 0; i<history.size(); i++) {
            TranslationHistoryObject historyObject = history.get(i);

            String text = "";
            String sourceText = historyObject.getTextToTranslate();
            String sourceLanguageName = historyObject.getSourceLanguageName();
            String targetLanguageName = historyObject.getTargetLanguageName();

            text += "[" + sourceLanguageName + "->" + targetLanguageName + "] " + sourceText;
            historyArrayList.add(text);
        }

        ListView list = (ListView) findViewById(R.id.listView);
        String historyArray[] = historyArrayList.toArray(new String[0]);

        ArrayList<String> carL = new ArrayList<String>();
        carL.addAll( Arrays.asList(historyArray) );

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.list_row, carL);
        list.setAdapter(adapter);
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                TranslationHistoryObject historyObject = history.get(position);
                Log.d("CCCCCCCCCCCCCCCCCC", "Clicked on object=" + historyObject.getTextToTranslate());

                setResult(Activity.RESULT_OK, new Intent().putExtra("historyObject", historyObject));
                finish();
//                finish();
            }
        });
    }
}
