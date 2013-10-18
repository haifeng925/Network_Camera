package de.tuberlin.aes.aespj;
import java.io.IOException;
/**
 * The class include the main method to start a Camera Application
 */

public class CameraApp {
	
	public static void main(String[] args) throws IOException {

		ImageBuffer imageBuffer = new ImageBuffer();
		UDPServer udpServer = null;
		PreviewThread previewer = null;
		ServerGUI cameraApp = new ServerGUI(imageBuffer, udpServer, previewer);
	}
}
