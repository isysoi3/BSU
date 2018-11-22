package model.client;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.URL;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

/**
 * Class of client that choose image and send it to another client by name
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Client {

    private static final Logger logger = LogManager.getLogger();

    private boolean isRunning;
    private String name;
    private JFrame frame;
    private JList<ImageIcon> imageList;
    private List<ImageIcon> myImages;
    private SocketChannel socket;

    /**
     * Runs the client as an application with a closeable frame.
     * @param args args of comand line
     */
    public static void main(String[] args)  {
        Client client = new Client();

        try {
            client.run();
        } catch (IOException | ClientConnectionException e) {
            logger.error(e);
            client.frame.dispose();
        }
    }


    private Client() {
        myImages = getAllImages();
        imageList = new JList(new Vector<>(myImages));
        JScrollPane scroll = new JScrollPane(imageList);
        scroll.setPreferredSize(new Dimension(200, 400));
        imageList.setVisible(false);

        imageList.addListSelectionListener(event -> {
            if (!event.getValueIsAdjusting()) {
                String anotherClient = getAnotherClientName();
                JList source = (JList)event.getSource();
                if (anotherClient != null) {
                    source.getSelectedValue();
                    String image = source.getSelectedValue().toString();

                    ByteBuffer buffer = ByteBuffer.allocate(8192);
                    buffer.put((anotherClient + " image: " + image).getBytes());
                    buffer.flip();

                    try {
                        socket.write(buffer);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    logger.info("Send image");
                }
            }

        });

        frame = new JFrame("Images");
        frame.add(scroll);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                if (JOptionPane.showConfirmDialog(frame,
                        "Are you sure you want to close this window?", "Close Window?",
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION){
                    logger.info("Close client");
                    ByteBuffer buffer = ByteBuffer.allocate(8192);
                    buffer.put(("EXIT " + name).getBytes());
                    buffer.flip();

                    try {
                        socket.write(buffer);
                        isRunning = false;
                        socket.close();
                    } catch (IOException  e) {
                        logger.error(e);
                    }
                    System.exit(0);
                }
            }
        });

        frame.setVisible(true);
    }

    /**
     * get some images
     *
     * @return list of images
     */
    private List<ImageIcon> getAllImages() {
        List<ImageIcon> list = new ArrayList<>();
        try {
            list.add(new ImageIcon(new URL("http://i.stack.imgur.com/NCsHu.png")));
            list.add(new ImageIcon(new URL("http://i.stack.imgur.com/UvHN4.png")));
            list.add(new ImageIcon(new URL("http://i.stack.imgur.com/s89ON.png")));
            list.add(new ImageIcon(new URL("http://i.stack.imgur.com/QEK2o.png")));
            list.add(new ImageIcon(new URL("http://i.stack.imgur.com/f4T4l.png")));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return list;
    }

    /**
     * enter name of client
     *
     * @return client name
     */
    private String getName() {
        return JOptionPane.showInputDialog(
                frame,
                "Enter you name:",
                "Name",
                JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * enter name of client to send image
     *
     * @return client name
     */
    private String getAnotherClientName() {
        return JOptionPane.showInputDialog(
                frame,
                "Choose another client by name:",
                "Name",
                JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * Connects to the server then enters the processing loop.
     *
     * @throws ClientConnectionException if cant start server
     * @throws IOException if some problems with IO
     */
    private void run() throws ClientConnectionException, IOException {

        try {
            socket = SocketChannel.open(new InetSocketAddress(InetAddress.getLocalHost(), 9001));
            socket.configureBlocking(false);
        } catch (IOException e) {
            throw new ClientConnectionException("Server isn`t started", e);
        }

        logger.info("Connected to server");

        isRunning = true;
        String name = null;
        while (isRunning) {
            ByteBuffer buffer = ByteBuffer.allocate(8192);
            socket.read(buffer);
            String input = new String(buffer.array()).trim();

            buffer.clear();

            if (input.length() > 0) {
                if (input.startsWith("SUBMIT_NAME")) {
                    name = null;
                    while (name == null) {
                        name = getName();
                    }
                    buffer.put(("NAME " + name).getBytes());
                    buffer.flip();

                    socket.write(buffer);
                    logger.info("Try register name:" + name);
                } else if (input.startsWith("NAME_ACCEPTED")) {
                    this.name = name;
                    imageList.setVisible(true);
                    frame.setTitle(frame.getTitle() + ": " + name);
                    logger.info("Show client images:" + name);
                } else if (input.startsWith("FAIL_USER")) {
                    JOptionPane.showMessageDialog(
                            frame,
                            "User not found",
                            "Fail",
                            JOptionPane.PLAIN_MESSAGE);
                    logger.info("User not found server answer");
                    } else if (input.startsWith("IMAGE")) {
                        JOptionPane.showMessageDialog(
                                frame,
                                "You got image",
                                "New image",
                                JOptionPane.PLAIN_MESSAGE);
                        String imageURL = input.substring(5);
                        myImages.add(new ImageIcon(new URL(imageURL)));
                        imageList.setListData(new Vector<>(myImages));
                        logger.info("Accept new image");
                    }
                }

            }
    }

}