package pl.trivelt.photomanager;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

public class CameraFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        return inflater.inflate(R.layout.fragment_camera, container, false);
    }


    public interface PhotoTaken {
        public void setPhoto(Bundle photo);
    }

    PhotoTaken mCallback;


    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        Button takePhotoButton = (Button) getView().findViewById(R.id.takePhotoButton);
        takePhotoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent action = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                startActivityForResult(action, 1);
            }
        });
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            mCallback = (PhotoTaken) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement PhotoTaken");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mCallback = null;
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        // TODO: RESULT_CANCELED
        if(requestCode == 1 ) {
            if (resultCode == Activity.RESULT_OK) {
                Bundle b = data.getExtras();
                Bitmap bt = (Bitmap) b.get("data");
                ViewPager pager = ((MainActivity) getActivity()).getViewPager();
                pager.setCurrentItem(2);
                mCallback.setPhoto(b);
            }
            else if (resultCode == Activity.RESULT_CANCELED) {
                ViewPager pager = ((MainActivity) getActivity()).getViewPager();
                pager.setCurrentItem(2);
            }
        }
//        FragmentManager fm = getFragmentManager();
//        FragmentTransaction ft = fm.beginTransaction();
//        ft.remove(this);
//        ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_CLOSE);
//        ft.commit();
    }
}