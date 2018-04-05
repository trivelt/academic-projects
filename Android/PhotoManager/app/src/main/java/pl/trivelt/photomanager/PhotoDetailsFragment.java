package pl.trivelt.photomanager;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.Random;

public class PhotoDetailsFragment extends Fragment {
    private final String mDataFilename = "galleryDataFile";
    private ImageView mImageView;
    private Bitmap mPhotoBitmap;
    private boolean editing = false;
    private String editedFilename = "";

    public interface PhotoEdited {
        public void refreshGallery();
    }

    PhotoEdited mCallback;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_photo_details, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        try {
            mImageView = (ImageView) getView().findViewById(R.id.imageView);
        } catch (NullPointerException e) {}

        Button rejectButton = (Button) getView().findViewById(R.id.rejectButton);
        rejectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(editing) {
                    File f = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM) + File.separator + editedFilename);
                    f.delete();

                    String currentJsonString = readFile(mDataFilename);
                    try {
                        JSONObject currentJson = new JSONObject(currentJsonString);
                        currentJson.remove(editedFilename);
                        writeFile(mDataFilename, currentJson.toString());

                    } catch (JSONException e) {e.printStackTrace();}
                }


                EditText titleEdit = (EditText) getView().findViewById(R.id.titleEdit);
                titleEdit.setText("Photo");
                EditText authorEdit = (EditText) getView().findViewById(R.id.authorEdit);
                authorEdit.setText("");
                TextView date = (TextView) getView().findViewById(R.id.dateTextView);
                date.setText("");
                TextView location = (TextView) getView().findViewById(R.id.locationTextView);
                location.setText("");
                EditText ratingEdit = (EditText) getView().findViewById(R.id.ratingEdit);
                ratingEdit.setText("");
                mImageView.setImageBitmap(null);
                mPhotoBitmap = null;

                Toast.makeText(getActivity(), "Photo removed", Toast.LENGTH_LONG).show();

                mCallback.refreshGallery();
                ViewPager pager = ((MainActivity) getActivity()).getViewPager();
                if(editing)
                    pager.setCurrentItem(1);
                else
                    pager.setCurrentItem(0);
            }
        });

        Button acceptButton = (Button) getView().findViewById(R.id.acceptButton);
        acceptButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mPhotoBitmap == null) {
                    Toast.makeText(getActivity(), "You are not editing any photo!", Toast.LENGTH_LONG).show();
                    return;
                }

                String filename = filenameOfCurrentPhoto();
                savePicture(filename);

                EditText titleEdit = (EditText) getView().findViewById(R.id.titleEdit);
                String title = titleEdit.getText().toString();

                EditText authorEdit = (EditText) getView().findViewById(R.id.authorEdit);
                String author = authorEdit.getText().toString();

                TextView dateView = (TextView) getView().findViewById(R.id.dateTextView);
                String date = dateView.getText().toString();

                TextView locationView = (TextView) getView().findViewById(R.id.locationTextView);
                String location = locationView.getText().toString();

                EditText ratingEdit = (EditText) getView().findViewById(R.id.ratingEdit);
                String rating = ratingEdit.getText().toString();

                try {
                    JSONObject photoDetailsJson = new JSONObject()
                            .put("title", title)
                            .put("author", author)
                            .put("date", date)
                            .put("location", location)
                            .put("rating", rating);

                    String currentJsonString = readFile(mDataFilename);
                    if(currentJsonString != null) {
                        JSONObject currentJson = new JSONObject(currentJsonString);
                        currentJson.put(filename, photoDetailsJson);
                        writeFile(mDataFilename, currentJson.toString());
                    } else {
                        JSONObject photoJson = new JSONObject()
                                .put(filename, photoDetailsJson);
                        writeFile(mDataFilename, photoJson.toString());
                    }


                } catch (JSONException e) { e.printStackTrace();}

                titleEdit.setText("Photo");
                authorEdit.setText("");
                dateView.setText("");
                locationView.setText("");
                ratingEdit.setText("");
                mPhotoBitmap = null;

                mCallback.refreshGallery();
                mImageView.setImageBitmap(null);
            }
        });
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        mCallback = (PhotoEdited) activity;
    }

    public void setPhoto(Bitmap photo) {
        editing = false;
        mPhotoBitmap = photo;
        mImageView.setImageBitmap(mPhotoBitmap);
    }

    public void editPhoto(Bitmap photo, String filename) {
        editing = true;
        editedFilename = filename;
        mPhotoBitmap = photo;
        mImageView.setImageBitmap(mPhotoBitmap);

        String currentJsonString = readFile(mDataFilename);
        try {
            JSONObject currentJson = new JSONObject(currentJsonString);
            JSONObject photoJson =currentJson.getJSONObject(filename);

            EditText titleEdit = (EditText) getView().findViewById(R.id.titleEdit);
            titleEdit.setText(photoJson.getString("title"));

            EditText authorEdit = (EditText) getView().findViewById(R.id.authorEdit);
            authorEdit.setText(photoJson.getString("author"));

            TextView dateView = (TextView) getView().findViewById(R.id.dateTextView);
            dateView.setText(photoJson.getString("date"));

            TextView locationView = (TextView) getView().findViewById(R.id.locationTextView);
            locationView.setText(photoJson.getString("location"));

            EditText ratingEdit = (EditText) getView().findViewById(R.id.ratingEdit);
            ratingEdit.setText(photoJson.getString("rating"));
        } catch (JSONException e) {e.printStackTrace();}
    }

    void savePicture(String photoName) {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        mPhotoBitmap.compress(Bitmap.CompressFormat.JPEG, 100, bytes);
        File f = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM) + File.separator + photoName);
        try {
            f.createNewFile();
            FileOutputStream fo = new FileOutputStream(f);
            fo.write(bytes.toByteArray());
            fo.close();
            Toast.makeText(getActivity(), "Zdjecie poprawnie zapisano w pliku " + f.getAbsolutePath(), Toast.LENGTH_LONG).show();
        } catch (IOException e) {
            e.printStackTrace();
            Toast.makeText(getActivity(), "Error", Toast.LENGTH_LONG).show();
        }
    }

    String readFile(String filename) {
        String filepath = "MyFileStorage";
        ContextWrapper contextWrapper = new ContextWrapper(getContext());
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
        ContextWrapper contextWrapper = new ContextWrapper(getContext());
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

    String filenameOfCurrentPhoto() {
        if(editing) {
            return editedFilename;
        } else {
            EditText titleEdit = (EditText) getView().findViewById(R.id.titleEdit);
            SecureRandom random = new SecureRandom();
            BigInteger bi = new BigInteger(130, random);
            String randomString = bi.toString(32);
            String title = titleEdit.getText().toString();
            String filename = randomString + "_" + title + ".jpg";
            return filename;
        }
    }

}