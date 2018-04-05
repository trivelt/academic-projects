package pl.trivelt.photomanager;


import android.graphics.Bitmap;

public class ImageItem {
    private String filename;
    private Bitmap image;

    public ImageItem(Bitmap image, String filename) {
        super();
        this.image = image;
        this.filename = filename;
    }

    public Bitmap getImage() {
        return image;
    }

    public void setImage(Bitmap image) {
        this.image = image;
    }

    public String getFilename() {
        return filename;
    }


//    public void setTitle(String title) {
//        this.title = title;
//    }
}