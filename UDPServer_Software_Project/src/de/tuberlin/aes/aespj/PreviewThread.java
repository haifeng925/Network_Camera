package de.tuberlin.aes.aespj;
import java.awt.image.BufferedImage;

import javax.swing.ImageIcon;
import javax.swing.JLabel;


public class PreviewThread implements Runnable{
	private boolean runThread;
	private JLabel imageLabel;
	private ImageBuffer iBuffer;
	public PreviewThread(JLabel label, ImageBuffer iBuffer){
		imageLabel = label;
		this.iBuffer = iBuffer;
	}
	
	@Override
	public void run() {
		runThread = true;
		while(runThread){
			try {
			//System.out.println("print by preview thread- sleep-------- "+iBuffer.getImageNumber());;
			Thread.sleep(10);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(!iBuffer.isBufferEmpty()){
				//System.out.println("imageBuffer "+iBuffer.toString());
				ImageInBytes imgB = iBuffer.getImage();
				
				BufferedImage bufferdImage = ImageConvertor.bytesToBufferdImage(imgB);
				imageLabel.setText("Frame Number: " + imgB.getImageNumber());
				imageLabel.setIcon(new ImageIcon(bufferdImage));
			
			}

		}

	}
	
	public void stopThread(){
		runThread = false;
	}
}
