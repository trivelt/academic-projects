package pl.trivelt.mytranslate;

import android.os.Parcel;
import android.os.Parcelable;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by maciej on 21.01.17.
 */
public class TranslationHistoryObject implements Parcelable {

    public TranslationHistoryObject(String pSourceLanguageName, String pTargetLanguageName, String pTextToTranslate, String pTranslatedText) {
        sourceLanguageName = pSourceLanguageName;
        targetLanguageName = pTargetLanguageName;
        textToTranslate = pTextToTranslate;
        translatedText = pTranslatedText;
    }

    protected TranslationHistoryObject(Parcel in) {
        sourceLanguageName = in.readString();
        targetLanguageName = in.readString();
        textToTranslate = in.readString();
        translatedText = in.readString();
    }

    public static final Creator<TranslationHistoryObject> CREATOR = new Creator<TranslationHistoryObject>() {
        @Override
        public TranslationHistoryObject createFromParcel(Parcel in) {
            return new TranslationHistoryObject(in);
        }

        @Override
        public TranslationHistoryObject[] newArray(int size) {
            return new TranslationHistoryObject[size];
        }
    };

    public JSONObject makeJson() {
        JSONObject translationJson = new JSONObject();
        try {
            translationJson
                    .put("sourceLang", sourceLanguageName)
                    .put("targetLang", targetLanguageName)
                    .put("sourceText", textToTranslate)
                    .put("targetText", translatedText);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return translationJson;
    }

    public String getSourceLanguageName() {
        return sourceLanguageName;
    }

    public String getTargetLanguageName() {
        return targetLanguageName;
    }

    public String getTextToTranslate() {
        return textToTranslate;
    }

    public String getTranslatedText() {
        return translatedText;
    }

    static List<TranslationHistoryObject> parseJsonString(String text) {
        List<TranslationHistoryObject> history = new ArrayList<>();
        try {
            JSONObject jsonObj = new JSONObject(text);

            Iterator<String> iter = jsonObj.keys();
            while (iter.hasNext()) {
                String key = iter.next();
                JSONObject value = jsonObj.getJSONObject(key);
                TranslationHistoryObject historyObj = new TranslationHistoryObject(
                        value.getString("sourceLang"),
                        value.getString("targetLang"),
                        value.getString("sourceText"),
                        value.getString("targetText"));
                history.add(historyObj);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }


        return history;
    }

    private String sourceLanguageName;
    private String targetLanguageName;
    private String textToTranslate;
    private String translatedText;

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(sourceLanguageName);
        dest.writeString(targetLanguageName);
        dest.writeString(textToTranslate);
        dest.writeString(translatedText);
    }
}