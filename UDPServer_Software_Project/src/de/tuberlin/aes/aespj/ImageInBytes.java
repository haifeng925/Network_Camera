package de.tuberlin.aes.aespj;

public class ImageInBytes {
	
	//public static final int IMAGE_SIZE = 614*480;
	private int IMAGE_SIZE;
	private byte[] image;
	private int offset;
	private int totalImagePackets;
	private int imageNumber;
	private int width;
	private int height;
	private int addedImageNumber;
	

	public ImageInBytes(ImageTransferProtocol itp){
		addedImageNumber= 0;
		width = itp.getWidth();
		height = itp.getHeight();
		IMAGE_SIZE = width * height;
		image = new byte[IMAGE_SIZE * 2];
		totalImagePackets = itp.getTotalImagePackets();
		imageNumber = itp.getImageNumber();
		//System.out.println("init Image InBytes...");

		addBytes(itp.getImageData(), itp.getDataOffset(), itp.getDataLength());

	//	System.out.println("add immap...");
	}
	
	public void addBytes(byte[] bs, int len){
		if(offset + len >= IMAGE_SIZE){
			System.out.println("no more space to add bytes");
		}
		
		System.arraycopy(bs, 0, image, offset, len);
		offset += len;
	}
	
	public void addBytes(byte[] bs, int offsetInImage, int len){
		System.arraycopy(bs, 0, image, offsetInImage, len);
		addedImageNumber ++;
	}
	
	public byte[] getImage(){
		return image;
	}

	public int getTotalImagePackets(){
		return totalImagePackets;
	}
	
	public int getImageNumber(){
		return imageNumber;
	}
	public int getWidth(){
		return width;
	}
	
	public int getHeight(){
		return height;
	}
	
	public boolean isImageAcceptable(){
		if((addedImageNumber/totalImagePackets) > 0.5){
			return true;
		}else{
			return false;
		}
	}

}
