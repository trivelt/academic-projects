package pl.trivelt.mytranslate;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.ArrayList;

public class FlashcardsActivity extends AppCompatActivity {

    private Button knowButton;
    private Button dontKnowButton;
    private Button showButton;
    private TextView textView;
    private ArrayList<TranslationHistoryObject> phrasesToLearn;
    private int currentIndex;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_flashcards);

        Bundle b = this.getIntent().getExtras();
//        final ArrayList<TranslationHistoryObject> history = b.getParcelableArrayList("history");
        phrasesToLearn = b.getParcelableArrayList("history");

        knowButton = (Button) findViewById(R.id.knowButton);
        dontKnowButton = (Button) findViewById(R.id.dontKnowButton);
        showButton = (Button) findViewById(R.id.showTranslationButton);
        textView = (TextView) findViewById(R.id.textView);

        if(phrasesToLearn.size() > 0) {
            currentIndex = 0;
            TranslationHistoryObject currentObject = phrasesToLearn.get(currentIndex);
            String text = "[";
            text += currentObject.getSourceLanguageName() + "->" + currentObject.getTargetLanguageName() + "] ";
            text += currentObject.getTextToTranslate();

            textView.setText(text);

            knowButton.setEnabled(false);
            dontKnowButton.setEnabled(false);
            showButton.setEnabled(true);
        }

        knowButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("Flashcards::KnowButton", "Removing currentIndex=" + currentIndex);
                phrasesToLearn.remove(currentIndex);
                if(phrasesToLearn.size() > 0) {
                    if(currentIndex >= phrasesToLearn.size()) {
                        currentIndex = 0;
                    }

                    TranslationHistoryObject currentObject = phrasesToLearn.get(currentIndex);
                    String text = "[";
                    text += currentObject.getSourceLanguageName() + "->" + currentObject.getTargetLanguageName() + "] ";
                    text += currentObject.getTextToTranslate();

                    textView.setText(text);
                } else {
                    textView.setText("Congratulations! You have learned all phrases from translation history!");
                    knowButton.setVisibility(View.GONE);
                    showButton.setVisibility(View.GONE);
                    dontKnowButton.setVisibility(View.GONE);
                }
                knowButton.setEnabled(false);
                dontKnowButton.setEnabled(false);
                showButton.setEnabled(true);
            }
        });

        dontKnowButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                currentIndex++;
                if(currentIndex >= phrasesToLearn.size()) {
                    currentIndex = 0;
                }
                Log.d("Flashcards::dontKnowBtn", "currentIndex (after incrementation=" + currentIndex);
                TranslationHistoryObject currentObject = phrasesToLearn.get(currentIndex);
                String text = "[";
                text += currentObject.getSourceLanguageName() + "->" + currentObject.getTargetLanguageName() + "] ";
                text += currentObject.getTextToTranslate();

                textView.setText(text);

                knowButton.setEnabled(false);
                dontKnowButton.setEnabled(false);
                showButton.setEnabled(true);
            }
        });

        showButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d("Flashcards::showButton", "currentIndex=" + currentIndex);
                TranslationHistoryObject currentObject = phrasesToLearn.get(currentIndex);
                String text = "[";
                text += currentObject.getTargetLanguageName() + "] ";
                text += currentObject.getTranslatedText();

                textView.setText(text);

                knowButton.setEnabled(true);
                dontKnowButton.setEnabled(true);
                showButton.setEnabled(false);
            }
        });


    }
}
