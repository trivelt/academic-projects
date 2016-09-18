import java.util.*;
import java.io.*;

class ImageCompression implements ImageCompressionInterface {
int kolorTla;
int kolorPedzla;
int dlBoku;
int[][]tab;

	public void setBackgroundBrightness( int b ){
	if(b<0 || b>255){ //ignore
			}
	else {
		{
		kolorTla = b;
		tab=new int[dlBoku][dlBoku];
		for(int y=0;y<dlBoku;y++)
			{
			for(int x=0;x<dlBoku;x++)
				{
				tab[x][y]=kolorTla;
				}
			}
		}}
	}
	
	public void setSize( int s ){
	dlBoku = s;
	}

	public void setPenBrightness( int b ){
	if(b<0 || b>255)
		{
		//ignore
		}
	else
		{
		kolorPedzla = b;
		}
	}

	public void setPixel( int x, int y ){
	if(x>=dlBoku || y>=dlBoku) 
		{
		//ignore
		}
	else
		{
		tab[x][y]=kolorPedzla;
		}
	}
	public void saveImage( String file )
	{
	java.io.FileWriter wyjsciowy;
		try{
	wyjsciowy = new FileWriter(file);
	String tmp = Integer.toString(dlBoku) + "\n";
	wyjsciowy.write(tmp);	
	int prevKolor=tab[0][0];
	int licznikKol=0;
	for(int y=0;y<dlBoku;y++)
	{
	for(int x=0;x<dlBoku;x++)
		{
		if(tab[x][y]==prevKolor)
			{
			licznikKol=licznikKol+1;
			}
		else
			{
			tmp=(prevKolor+" "+licznikKol+"\n");
			wyjsciowy.write(tmp);
			licznikKol=1;
			}
		prevKolor=tab[x][y];
		}

	}
	tmp=(prevKolor+" "+licznikKol);
	wyjsciowy.write(tmp);

	wyjsciowy.close();
		}
		catch(IOException e){}
	}
}
