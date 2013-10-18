package de.tuberlin.aes.aespj;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;

/**
 * The class only have the function to convert <code>ImageInBytes</code> into <code>BufferedImage</code>
 *
 */
public class ImageConvertor {
	/**
	 * static function can be used to convert <code>ImageInBytes</code> into <code>BufferedImage</code>
	 * 
	 * @param iB <code>ImageInBytes</code> need to be converted
	 * @return <code>BufferedImage</code>, converted from <code>ImageInBytes</code>
	 */
	public static BufferedImage bytesToBufferdImage(ImageInBytes iB){
		int pixels[] = bytesToPixels(iB);
		BufferedImage img = new BufferedImage(iB.getWidth(), iB.getHeight(), BufferedImage.TYPE_INT_RGB);
		WritableRaster raster = img.getRaster();
		raster.setPixels(0, 0, iB.getWidth(), iB.getHeight(), pixels);
		return img;
	}
	
	/**
	 * Convert <code>ImageInBytes<code> into an array of pixels.
	 * @param iB
	 * @return a array of pixels
	 */
	private static int[] bytesToPixels(ImageInBytes iB){
		int imageSize = iB.getHeight() * iB.getWidth();
		int pixels[] = new int[imageSize * 3];
		byte imageBytes[] = iB.getImage();
		
		for(int i=0; i<imageSize; i++){
			byte b1 = imageBytes[2*i];
			byte b2 = imageBytes[2*i+1];
			
			int r = (b1 & 0xF8)<<3;
			int b = (b2 &0x1F)<<3; 
			
			b1 = imageBytes[2*i];
			b2 = imageBytes[2*i + 1];
			
			int g =  (((b1 & 0x07) << 5) | ((b2 & 0xE0)>>3));
			
			pixels[i*3] = r;
			pixels[i*3 + 1] = g;
			pixels[i*3 + 2] = b;
	
		}
		return pixels;
	}
	
}
