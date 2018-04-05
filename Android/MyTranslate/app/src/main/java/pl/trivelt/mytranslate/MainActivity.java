package pl.trivelt.mytranslate;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Parcelable;
import android.os.StrictMode;
import android.preference.PreferenceManager;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import org.json.JSONObject;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

public class MainActivity extends AppCompatActivity {

    private ArrayAdapter<String> adapter;
    private Spinner sourceLangSpinner;
    private Spinner targetLangSpinner;
    private EditText textToTranslateEdit;
    private EditText translatedTextEdit;
    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        textToTranslateEdit = (EditText) findViewById(R.id.textToTranslateEdit);
        translatedTextEdit = (EditText) findViewById(R.id.translatedTextEdit);

        sourceLangSpinner = (Spinner) findViewById(R.id.sourceLangSpinner);
        targetLangSpinner = (Spinner) findViewById(R.id.destinationLangSpinner);


        URL url;
        String translatorKey = "trnsl.1.1.20160222T215739Z.9a88db99ac938902.58b5c247a946caa3b4a36a7ea22f65b1f2ebeba2";
        final String translateQuery = "https://translate.yandex.net/api/v1.5/tr/translate?key=" + translatorKey + "&text=";

        String[] languagesNames = getResources().getStringArray(R.array.languages_names);
        String[] languagesCodes = getResources().getStringArray(R.array.languages_codes);

        final Map<String, String> languagesMap = new HashMap<String, String>();

        if(languagesNames.length == languagesCodes.length){
            for(int index = 0; index < languagesNames.length; index++){
                languagesMap.put(languagesNames[index], languagesCodes[index]);
            }
        }

        String[] arr = languagesMap.keySet().toArray(new String[0]);
        List<String> arrList = Arrays.asList(arr);
        Collections.sort(arrList, new Comparator<String>() {
            @Override
            public int compare(String text1, String text2) {
                return text1.compareToIgnoreCase(text2);
            }
        });


//        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
        adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_spinner_item, arrList);
        sourceLangSpinner.setAdapter(adapter);
        targetLangSpinner.setAdapter(adapter);


        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        final String defaultSourceLangName = sharedPreferences.getString("source_language", "Polish");
        final String defaultTargetLangName = sharedPreferences.getString("target_language", "English");

        int sourceSpinnerPosition = adapter.getPosition(defaultSourceLangName);
        int targetSpinnerPosition = adapter.getPosition(defaultTargetLangName);

        sourceLangSpinner.setSelection(sourceSpinnerPosition);
        targetLangSpinner.setSelection(targetSpinnerPosition);



        Button translateButton = (Button) findViewById(R.id.translateButton);
        if (translateButton != null) {
            translateButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String textToTranslate = textToTranslateEdit.getText().toString();

                    String sourceLanguageName = sourceLangSpinner.getSelectedItem().toString();
                    String targetLanguageName = targetLangSpinner.getSelectedItem().toString();

                    String sourceLangCode = languagesMap.get(sourceLanguageName);
                    String targetLangCode = languagesMap.get(targetLanguageName);

                    String query = translateQuery + textToTranslate + "&lang=" + sourceLangCode + "-" + targetLangCode + "&format=plain";

                    try {
                        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
                        DocumentBuilder db = dbf.newDocumentBuilder();

                        URLConnection urlConnection;
                        URL url = new URL(query);
                        urlConnection = (HttpURLConnection) url.openConnection();
                        InputStream in = urlConnection.getInputStream();

                        Document doc = db.parse(new InputSource(in));
                        doc.getDocumentElement().normalize();
                        in.close();

                        NodeList allNodes = doc.getElementsByTagName("Translation");
                        if(allNodes.getLength() > 0) {
                            Node translationNode = allNodes.item(0);
                            Element translationElement = (Element) translationNode;
                            String errorCode = translationElement.getAttribute("code");
                            if(errorCode.equals("200")) {
                                NodeList textNodes = doc.getElementsByTagName("text");
                                if(textNodes.getLength() > 0) {
                                    Node textNode = textNodes.item(0);
                                    String translatedText = textNode.getTextContent();
                                    translatedTextEdit.setText(translatedText);



                                    boolean historyEnabled = sharedPreferences.getBoolean("history_switch", false);
                                    if(historyEnabled) {
                                        String historyText = readFile("translation-history.json");
                                        List<TranslationHistoryObject> history = TranslationHistoryObject.parseJsonString(historyText);
                                        int maxHistorySize = Integer.valueOf(sharedPreferences.getString("history_size", "25"));
                                        TranslationHistoryObject translationObject = new TranslationHistoryObject(sourceLanguageName, targetLanguageName, textToTranslate, translatedText);
                                        history.add(translationObject);
                                        List<TranslationHistoryObject> truncatedList;
                                        if(history.size() > maxHistorySize) {
                                            int diff = history.size() - maxHistorySize;
                                            truncatedList = history.subList(diff, history.size());
                                        } else {
                                            truncatedList = history;
                                        }

                                        JSONObject allHistory = new JSONObject();
                                        for (int i=0; i<truncatedList.size(); i++) {
                                            JSONObject historyObjectJson = truncatedList.get(i).makeJson();
                                            allHistory.put(Integer.toString(i), historyObjectJson);
                                        }
                                        writeFile("translation-history.json", allHistory.toString());
                                    }
                                }
                            } else {
                                Toast.makeText(MainActivity.this, "Internal error occurred (status code != 200)", Toast.LENGTH_LONG).show();
                            }
                        } else {
                            Toast.makeText(MainActivity.this, "Internal error occurred (no Translation node)", Toast.LENGTH_LONG).show();
                        }


                    } catch (Exception e) {
                        Toast.makeText(MainActivity.this, "Connection error occurred", Toast.LENGTH_LONG).show();
                        e.printStackTrace();
                    }

                }
            });
        }

        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_HIDDEN);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        boolean historyEnabled = sharedPreferences.getBoolean("history_switch", false);
        MenuItem flashcardsItem = menu.findItem(R.id.action_flashcards);
        MenuItem historyItem = menu.findItem(R.id.action_history);
        flashcardsItem.setEnabled(historyEnabled);
        historyItem.setEnabled(historyEnabled);

        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent settingIntent = new Intent(MainActivity.this, SettingsActivity.class);
            MainActivity.this.startActivity(settingIntent);
            return true;
        } else if(id == R.id.action_history) {
            Intent historyIntent = new Intent(MainActivity.this, HistoryActivity.class);
            String historyText = readFile("translation-history.json");
            List<TranslationHistoryObject> history = TranslationHistoryObject.parseJsonString(historyText);

            Bundle b = new Bundle();
            b.putParcelableArrayList("history", (ArrayList<? extends Parcelable>) history);
            historyIntent.putExtras(b);
            MainActivity.this.startActivityForResult(historyIntent, 0);
            return true;
        } else if(id == R.id.action_flashcards) {
            Intent flashcardsIntent = new Intent(MainActivity.this, FlashcardsActivity.class);

            String historyText = readFile("translation-history.json");
            List<TranslationHistoryObject> history = TranslationHistoryObject.parseJsonString(historyText);

            Bundle b = new Bundle();
            b.putParcelableArrayList("history", (ArrayList<? extends Parcelable>) history);
            flashcardsIntent.putExtras(b);
            MainActivity.this.startActivity(flashcardsIntent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == 0 && resultCode == Activity.RESULT_OK) {
            TranslationHistoryObject historyObject = (TranslationHistoryObject) data.getParcelableExtra("historyObject");
            EditText textToTranslateEdit = (EditText) findViewById(R.id.textToTranslateEdit);
            EditText translatedTextEdit = (EditText) findViewById(R.id.translatedTextEdit);
            final Spinner sourceLangSpinner = (Spinner) findViewById(R.id.sourceLangSpinner);
            final Spinner targetLangSpinner = (Spinner) findViewById(R.id.destinationLangSpinner);

            int sourceSpinnerPosition = adapter.getPosition(historyObject.getSourceLanguageName());
            int targetSpinnerPosition = adapter.getPosition(historyObject.getTargetLanguageName());

            sourceLangSpinner.setSelection(sourceSpinnerPosition);
            targetLangSpinner.setSelection(targetSpinnerPosition);

            textToTranslateEdit.setText(historyObject.getTextToTranslate());
            translatedTextEdit.setText(historyObject.getTranslatedText());
        }
    }

    String readFile(String filename) {
        String filepath = "MyFileStorage";
        ContextWrapper contextWrapper = new ContextWrapper(this);
        File directory = contextWrapper.getDir(filepath, Context.MODE_PRIVATE);
        File myInternalFile = new File(directory, filename);
        String myData = "";
        try {
            FileInputStream fis = new FileInputStream(myInternalFile);
            DataInputStream in = new DataInputStream(fis);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            String strLine;
            while ((strLine = br.readLine()) != null)
                myData = myData + strLine;
            in.close();
        } catch (FileNotFoundException e) {
            return null;
        } catch (IOException e) {
            e.printStackTrace();
            myData = "Błąd odczytu pliku";
        }
        return myData;
    }

    public void writeFile(String filename, String strToSave)
    {
        String filepath = "MyFileStorage";
        ContextWrapper contextWrapper = new ContextWrapper(this);
        File directory = contextWrapper.getDir(filepath, Context.MODE_PRIVATE);
        File myInternalFile = new File(directory, filename);
        try {
            FileOutputStream fos = new FileOutputStream(myInternalFile);
            fos.write(strToSave.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
