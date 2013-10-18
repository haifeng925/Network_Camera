package de.tuberlin.aes.aespj;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * UDPServer is implemented as thread, created and started by <code>ServerGUI</code>
 * 
 *
 */
public class UDPServer implements Runnable{
	/**
	 * indicate if the Thread is runnable
	 * 
	 */
    private  boolean runThread;
    /**
     * the port, the udp server is listening at
     */
	private  int PORT = 50000;
	/**
	 * socket used by udp server
	 */
	private DatagramSocket serverSocket;
	/**
	 * buffer to keep the received bytes
	 */
	private byte[] buff;
	/**
	 * image buffer to store images
	 */
	private ImageBuffer imageBuffer;
	/**
	 * object to keep the image data with the same image number.
	 */
	private ImageInBytes imgInBytes;
		
	public UDPServer(ImageBuffer imageBuffer) throws IOException{
		if(!imageBuffer.isBufferEmpty()){
			imageBuffer.cleanBuffer();
		}
		runThread = true;
	
		serverSocket = new DatagramSocket(PORT);
		 buff = new byte[8192];
	    this.imageBuffer = imageBuffer;
		System.out.println("udpserver starting...");
		imgInBytes = null;
	}
	
	/**
	 * 
	 * @param pkt the <code>DatagramPacket</code> received by udpserver
	 */
	private void itpAnalye(DatagramPacket pkt){
		ImageTransferProtocol itp = new ImageTransferProtocol(pkt);

		if(imgInBytes == null ){
			
			imgInBytes = new ImageInBytes(itp);
			System.out.println("0 image");
			return;
		}
		
		
	

		if(itp.getImageNumber() != imgInBytes.getImageNumber()){
			if(imgInBytes.isImageAcceptable()){
				imageBuffer.pushImage(imgInBytes);
				imgInBytes = new ImageInBytes(itp);

			}else{

				imgInBytes = new ImageInBytes(itp);


			}
		}else{
			
			imgInBytes.addBytes(itp.getImageData(), itp.getDataOffset(), itp.getDataLength());
			if(imgInBytes.getImageNumber() == itp.getCurrentPacketNumber() && imgInBytes.isImageAcceptable()){
				imageBuffer.pushImage(imgInBytes);
			}
		}		
		
	}

	@Override
	public void run(){
		while(runThread){
			DatagramPacket packet = new DatagramPacket(buff, 8192);
			try{
				serverSocket.receive(packet);
	//			System.out.println("RECEIVED: ");
				itpAnalye(packet);

			}catch(Exception e){
			//	System.out.println("transaction is finished");
				serverSocket.close();
				break;
			}		
		}
	}
	/**
	 * stop UDP-Server
	 */
	public void stopServer() throws IOException{
		serverSocket.close();
		System.out.println("socket close");
		System.out.println("file buffer close");
		runThread = false;
	}
	

}
