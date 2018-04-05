package pl.trivelt.photomanager;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.content.ContextCompat;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity implements CameraFragment.PhotoTaken, GalleryFragment.PhotoClicked, PhotoDetailsFragment.PhotoEdited{

    private ViewPager mViewPager;
    private PhotoDetailsFragment mDetailsFragment;
    private GalleryFragment mGalleryFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mDetailsFragment = new PhotoDetailsFragment();
        mGalleryFragment = new GalleryFragment();

        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(new SamplePagerAdapter(getSupportFragmentManager()));
        mViewPager.setCurrentItem(1);
        }

    public ViewPager getViewPager() {
        if(mViewPager == null) {
            mViewPager = (ViewPager) findViewById(R.id.pager);
        }
        return mViewPager;
    }

    @Override
    public void setPhoto(Bundle photo) {
        Bitmap rlPhoto = (Bitmap) photo.get("data");
        mDetailsFragment.setPhoto(rlPhoto);

        Calendar c = Calendar.getInstance();
        SimpleDateFormat df = new SimpleDateFormat("dd MMM yyyy H:m:s");
        String formattedDate = df.format(c.getTime());
        TextView dateView = (TextView) findViewById(R.id.dateTextView);
        dateView.setText("Date : " + formattedDate);

        EditText titleEdit = (EditText) findViewById(R.id.titleEdit);
        titleEdit.setText("Photo");

        EditText authorEdit = (EditText) findViewById(R.id.authorEdit);
        authorEdit.setText("");

        EditText ratingEdit = (EditText) findViewById(R.id.ratingEdit);
        ratingEdit.setText("");

        LocationManager locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
        Criteria crit = new Criteria();
        String provider = locationManager.getBestProvider(crit, true);
        boolean isGpsEnabled = locationManager.isProviderEnabled(provider);
        if(ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED
                && ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED
                && isGpsEnabled) {
            Location location = locationManager.getLastKnownLocation(provider);
            TextView locationView = (TextView) findViewById(R.id.locationTextView);
            if(location != null) {
                String latitude = Double.toString(location.getLatitude());
                String longitude = Double.toString(location.getLongitude());

                locationView.setText("Lat: " + latitude + ", Lng: " + longitude);
            } else {
                locationView.setText("Location unknown");
            }
        }

    }

    @Override
    public void setClickedPhoto(Bitmap photo, String filename) {
        mDetailsFragment.editPhoto(photo, filename);
    }

    @Override
    public void refreshGallery() {
        mGalleryFragment.refreshAdapter();
    }

    public class SamplePagerAdapter extends FragmentPagerAdapter {

        public SamplePagerAdapter(FragmentManager fm) {
                super(fm);
            }

        @Override
        public Fragment getItem(int position) {
            if (position == 0) {
                return new CameraFragment();
            } else if(position == 1)
                return mGalleryFragment;
            else
                return mDetailsFragment;
        }

        @Override
        public int getCount() {
            return 3;
        }
    }

}