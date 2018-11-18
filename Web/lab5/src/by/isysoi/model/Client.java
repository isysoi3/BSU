package by.isysoi.model;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

/**
 * Class of client that choose image and send it
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Client {

    private BufferedReader in;
    private PrintWriter out;
    private JFrame frame;
    private JList<ImageIcon> imageList;
    private List<ImageIcon> myImages;

    private Client() {
        myImages = getAllImages();
        imageList = new JList(new Vector<>(myImages));
        JScrollPane scroll = new JScrollPane(imageList);
        scroll.setPreferredSize(new Dimension(300, 400));
        imageList.setVisible(false);

        imageList.addListSelectionListener(event -> {
            if (!event.getValueIsAdjusting()) {
                String anotherClient = getAnotherClientName();
                JList source = (JList)event.getSource();
                if (anotherClient != null) {
                    String image = source.getSelectedValue().toString();
                    out.println(anotherClient + " image: " + image);
                }
                source.removeSelectionInterval(source.getSelectedIndex(), source.getSelectedIndex() + 1);
            }

        });

        frame = new JFrame("Images");
        frame.add(scroll);
        frame.pack();
    }


    /**
     * get some images
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
     * Prompt for and return the desired screen name.
     */
    private String getName() {
        return JOptionPane.showInputDialog(
                frame,
                "Enter you name:",
                "Name",
                JOptionPane.PLAIN_MESSAGE);
    }

    private String getAnotherClientName() {
        return JOptionPane.showInputDialog(
                frame,
                "Choose another client by name:",
                "Name",
                JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * Connects to the server then enters the processing loop.
     */
    private void run() throws IOException {

        Socket socket = new Socket(InetAddress.getLocalHost(), 9001);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        String name = null;
        while (true) {
            String line = in.readLine();
            if (line.startsWith("SUBMIT_NAME")) {
                name = null;
                while (name == null) {
                    name = getName();
                }
                out.println(name);
            } else if (line.startsWith("NAME_ACCEPTED")) {
                imageList.setVisible(true);
                frame.setTitle(frame.getTitle() + ": " + name);
            } else if (line.startsWith("FAIL_USER")) {
                JOptionPane.showMessageDialog(
                        frame,
                        "User not found",
                        "Fail",
                        JOptionPane.PLAIN_MESSAGE);
            } else if (line.startsWith("IMAGE")) {
                JOptionPane.showMessageDialog(
                        frame,
                        "You got image",
                        "New image",
                        JOptionPane.PLAIN_MESSAGE);
                String imageURL = line.substring(5);
                myImages.add(new ImageIcon(new URL(imageURL)));
                imageList.setListData(new Vector<>(myImages));
            }
        }
    }

    /**
     * Runs the client as an application with a closeable frame.
     */
    public static void main(String[] args)  {
        Client client = new Client();
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.setVisible(true);
        try {
            client.run();
        } catch (Exception e) {
            e.printStackTrace();
            client.frame.dispose();
        }
    }
}