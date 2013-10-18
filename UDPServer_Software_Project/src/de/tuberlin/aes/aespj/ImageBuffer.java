package de.tuberlin.aes.aespj;
import java.util.LinkedList;
import java.util.List;

/**
 * Class ImageBuffer as First In First Out buffer to keep the image received from
 * UDPServer. Preview Thread also use the same buffer to get the first image of this
 * Buffer. 
 *
 */
public class ImageBuffer {
	public static int BUFFER_SIZE = 20;
	private ImageInBytes currentImage = null;
	private List<ImageInBytes> buffer = new LinkedList<ImageInBytes>();
	public ImageBuffer(){
	
	}
	
	public void pushImage(ImageInBytes img){
		while(buffer.size()>=BUFFER_SIZE){
			buffer.remove(0);
		}
		//System.out.println("print by ImageBuffer: add one image, total images:  "+ buffer.size());
		buffer.add(img);
	}
	
	public ImageInBytes getImage(){
		if(buffer.size() == 0){
			return null;
		}
		ImageInBytes img = buffer.get(0);
		currentImage = img;
		
		buffer.remove(0);
		
		return img;
	}
	
	public boolean isBufferEmpty(){
		return buffer.isEmpty();
	}
	
	public void cleanBuffer(){
		buffer.clear();
	}
	
	public int getImageNumber(){
		return buffer.size();
	}
	
	public ImageInBytes getCurrentImage(){
		return currentImage;
	}
	public void setCurrentImage(ImageInBytes img){
		currentImage = img;
	}
	
}
