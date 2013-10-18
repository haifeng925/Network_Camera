package de.tuberlin.aes.aespj;
import java.net.DatagramPacket;


public class ImageTransferProtocol {
	//private DatagramPacket packet;
	private int udpLength;
	private byte[] itp;
	private int width;
	private int height;
	private int totalImagePackets;
	private int currentPacketNumber;
	private int dataOffset;
	private int dataLength;
	private int imageNumber;
	private byte[] imageData;
	
	public ImageTransferProtocol(DatagramPacket dp){
		itp = dp.getData();
		udpLength = dp.getLength();
		parseITP();
		//System.out.println("ImageTransferProtocal init finished ....");
	}
	
	private void parseITP(){
		byte b[] = new byte[4];
		imageData = new byte[udpLength-28];
		System.arraycopy(itp, 0, b,0, 4);
		width = byteToInt(b);
		System.arraycopy(itp, 4, b, 0, 4);
		height = byteToInt(b);
		System.arraycopy(itp, 8, b, 0, 4);
		totalImagePackets = byteToInt(b);
		System.arraycopy(itp, 12, b, 0, 4);
		currentPacketNumber = byteToInt(b);
		System.arraycopy(itp, 16, b, 0, 4);
		dataOffset = byteToInt(b);
		System.arraycopy(itp, 20, b, 0, 4);
		dataLength = byteToInt(b);
		System.arraycopy(itp, 24, b, 0, 4);
		imageNumber = byteToInt(b);
		
		System.arraycopy(itp, 28, imageData, 0, udpLength - 28);
	/*	System.out.println("width:"+ width);
		System.out.println("H: "+height);
		System.out.println("totalImagePackets: "+totalImagePackets);
		System.out.println("currentPacketNumber: "+currentPacketNumber);
		System.out.println("dataOffset: "+dataOffset);
		System.out.println("dataLength: "+dataLength);
		System.out.println("imageNumber: "+imageNumber);
		System.out.println("image: "+ (imageData[0]&0xFF)+" "+ (imageData[1]&0xFF));

*/

	}
	
	private int byteToInt(byte[] b){
		int result = 0;
		for (int i=0; i<4; i++){
			
			result <<= 8;
		    result |= b[i] & 0xFF;
		}
		return result;
	}
	
	public int getWidth(){
		return width;
	}
	
	public int getHeight(){
		return height;
	}
	public int getTotalImagePackets(){
		return totalImagePackets;
	}
	public int getCurrentPacketNumber(){
		return currentPacketNumber;
	}
	
	public int getDataOffset(){
		return dataOffset;
	}
	public int getDataLength(){
		return dataLength;
	}
	public int getImageNumber(){
		return imageNumber;
	}
	public byte[] getImageData(){
		return imageData;
	}
}
