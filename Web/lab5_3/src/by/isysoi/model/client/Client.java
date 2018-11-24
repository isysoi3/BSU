package by.isysoi.model.client;

import io.netty.bootstrap.Bootstrap;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelOption;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.*;
import java.awt.*;
import java.net.InetAddress;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

/**
 * Class of client that choose image and send it to another client by name
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Client implements ClientInterface {

    private static final Logger logger = LogManager.getLogger();

    private JFrame frame;
    private JList<ImageIcon> imageList;
    private List<ImageIcon> myImages;

    /**
     * Runs the client as an application with a closeable frame.
     * @param args args of comand line
     */
    public static void main(String[] args)  {
        Client client = new Client();
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.setVisible(true);

        try {
            client.run();
        } catch (ClientConnectionException e) {
            logger.error(e);
            client.frame.dispose();
        }
    }

    public JList<ImageIcon> getImageList() {
        return imageList;
    }

    public List<ImageIcon> getMyImages() {
        return myImages;
    }

    private Client() {
        myImages = getAllImages();
        imageList = new JList(new Vector<>(myImages));
        JScrollPane scroll = new JScrollPane(imageList);
        scroll.setPreferredSize(new Dimension(200, 400));
        imageList.setVisible(false);

        frame = new JFrame("Images");
        frame.add(scroll);
        frame.pack();
    }

    public JFrame getFrame() {
        return frame;
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
    public String getName() {
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
    public String getAnotherClientName() {
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
     */
    private void run() throws ClientConnectionException {

        EventLoopGroup group = new NioEventLoopGroup();
        try {
            Bootstrap clientBootstrap = new Bootstrap();
            clientBootstrap.group(group)
                    .channel(NioSocketChannel.class)
                    .remoteAddress(InetAddress.getLocalHost(), 9001)
                    .option(ChannelOption.TCP_NODELAY, true)
                    .handler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        public void initChannel(SocketChannel socketChannel) {
                            socketChannel.pipeline().addLast(new ClientHandler(Client.this));
                        }
                    });

            ChannelFuture channelFuture = clientBootstrap.connect().sync();
            channelFuture.channel().closeFuture().sync();
        } catch (Exception e) {
            throw new ClientConnectionException("cant connect to server", e);
        } finally {
            group.shutdownGracefully();
        }

        logger.info("Connected to server");
    }


}
