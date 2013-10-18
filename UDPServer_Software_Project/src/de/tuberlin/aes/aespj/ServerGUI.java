package de.tuberlin.aes.aespj;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.BorderLayout;
import java.io.File;
import java.io.IOException;
import javax.swing.JButton;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.awt.FlowLayout;
import javax.swing.JTextArea;


public class ServerGUI {

	private JFrame frmCameraServer;
	private JLabel imageLabel;
	private JButton startButton;
	private boolean isServerRun;
	private Thread serverThread;
	private Thread previewThread;
	private JPanel panel;
	private JButton btnCaputure;
	private JButton btnStop;
	
	private UDPServer udpServer;
	private PreviewThread previewer;
	private ImageBuffer iBuffer;
	private JPanel panel_1;
	private JTextArea textArea;
/**
 * create the GUI for Camera Application 
 * @param iBuffer
 * @param udpServer
 * @param previewer
 * @throws IOException
 */
	public ServerGUI(ImageBuffer iBuffer, UDPServer udpServer, PreviewThread previewer) throws IOException {
		this.udpServer = udpServer;
		this.previewer = previewer;
		this.iBuffer = iBuffer;
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 * @throws IOException 
	 */
	private void initialize() throws IOException {
		isServerRun = false;
		frmCameraServer = new JFrame();
		frmCameraServer.setTitle("Camera Server");
		frmCameraServer.setBounds(100, 100, 450, 300);
		frmCameraServer.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		imageLabel = new JLabel("The Server is not Started yet");
		imageLabel.setAutoscrolls(true);
		frmCameraServer.getContentPane().add(imageLabel, BorderLayout.CENTER);
		//imageServer = new UDPServer(textArea, imageLabel);
		
		panel = new JPanel();
		frmCameraServer.getContentPane().add(panel, BorderLayout.SOUTH);
		panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		startButton = new JButton("Start");
		panel.add(startButton);
		
		btnCaputure = new JButton("Capture");
		btnCaputure.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				try {
					storeImage();
				} catch (IOException e) {
					
					e.printStackTrace();
				}
			}
		});
		btnCaputure.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
			}
		});
		panel.add(btnCaputure);
		
		btnStop = new JButton("Stop");
		btnStop.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(isServerRun){
					try {
						udpServer.stopServer();
						previewer.stopThread();
						imageLabel.setText("Server is topped");
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					isServerRun = false;
					System.out.println("server is stopping now "+ isServerRun);
				}
			}
		});
		panel.add(btnStop);
		
		panel_1 = new JPanel();
		frmCameraServer.getContentPane().add(panel_1, BorderLayout.EAST);
		panel_1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.setColumns(10);
		textArea.setText("Digital Network Camera\n For AES Project \n\n\n Authors:\n\n Haifeng Gao\n Le Li\n Farid Rosli \n Marco Taubmann");
		textArea.setRows(20);
		panel_1.add(textArea);
		//textField.setColumns(10);
		
		startButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
			}
		});
		startButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
					if(!isServerRun){
						System.out.println("server start...");
						try {
							iBuffer = new ImageBuffer();
							udpServer = new UDPServer(iBuffer);
							previewer = new PreviewThread(imageLabel,iBuffer);
							
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						serverThread = new Thread(udpServer);
						serverThread.start();
						previewThread = new Thread(previewer);
						previewThread.start();
						imageLabel.setText("Server is starting now...");
						isServerRun = true;
					}

			}
		});
		frmCameraServer.setVisible(true);
		//udpServer.startServer();
	}
	

	private void storeImage() throws IOException{
		if(iBuffer.getCurrentImage() == null){
			System.out.println("---------no image in ImageBuffer "+iBuffer.toString());
			return; 
		}
		ImageInBytes currImage 	= iBuffer.getCurrentImage();
		BufferedImage bufferedImage = ImageConvertor.bytesToBufferdImage(currImage);
		
		JFrame parentFrame = new JFrame();
		JFileChooser fChooser = new JFileChooser();
		fChooser.setDialogTitle("Save the Image");
		fChooser.setDialogType(JFileChooser.SAVE_DIALOG);
		FileNameExtensionFilter fileFilter = new FileNameExtensionFilter("*.bmp", "bmp");
		fChooser.addChoosableFileFilter(fileFilter);
		//int i = fChooser.showDialog(null, "Save the Image");
		int i = fChooser.showDialog(parentFrame, "Save the Image");
		if(i == JFileChooser.APPROVE_OPTION){
			//File f = fChooser.getSelectedFile();
			String path = fChooser.getSelectedFile().getAbsolutePath().trim().concat(".bmp");
			System.out.println(path);
			File imageFile = new File(path);
			ImageIO.write(bufferedImage, "bmp", imageFile);
			
		}
		
		
	}
}
