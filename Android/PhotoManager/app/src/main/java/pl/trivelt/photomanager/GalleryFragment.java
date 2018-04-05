package pl.trivelt.photomanager;

import android.app.Activity;
import android.content.res.TypedArray;
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
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.TextView;

import java.io.File;
import java.util.ArrayList;

public class GalleryFragment extends Fragment {
    private GridView mGridView;
    private GridViewAdapter mGridViewAdapter;

    public interface PhotoClicked {
        public void setClickedPhoto(Bitmap photo, String filename);
    }

    PhotoClicked mCallback;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_gallery, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        mGridView = (GridView) getView().findViewById(R.id.gridView);
//        mGridView.setNumColumns(2);
        mGridViewAdapter = new GridViewAdapter(getActivity(), R.layout.grid_item_layout, getData());
        mGridView.setAdapter(mGridViewAdapter);

        mGridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                ImageItem item = (ImageItem) parent.getItemAtPosition(position);

                ViewPager pager = ((MainActivity) getActivity()).getViewPager();
                pager.setCurrentItem(2);

                mCallback.setClickedPhoto(item.getImage(), item.getFilename());

            }
        });

    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        mCallback = (PhotoClicked) activity;
    }

    private ArrayList<ImageItem> getData() {
        File directory = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM);
        File[] files = directory.listFiles();

        int numberOfImages = 0;

        ArrayList<ImageItem> imageItems = new ArrayList<>();
        for (int i = 0; i < files.length; i++) {
            if(!files[i].getAbsolutePath().endsWith(".jpg"))
                continue;

            Bitmap bitmap = BitmapFactory.decodeFile(files[i].getAbsolutePath());
            ImageItem item = new ImageItem(bitmap, files[i].getName());
            imageItems.add(item);
            numberOfImages++;
//            imageItems.add(new ImageItem(bitmap, "Image#" + i));
        }

        TextView infoView = (TextView) getView().findViewById(R.id.textView);
        if(numberOfImages == 0)
            infoView.setText("Gallery is empty");
        else
            infoView.setText("");

        return imageItems;
    }

    public void refreshAdapter() {
        mGridViewAdapter = new GridViewAdapter(getActivity(), R.layout.grid_item_layout, getData());
        mGridView.setAdapter(mGridViewAdapter);
    }
}