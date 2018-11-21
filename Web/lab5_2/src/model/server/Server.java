package model.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * Class of server that connect clinets and send images
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Server {

    private static final Logger logger = LogManager.getLogger();

    private static final int PORT = 9001;

    private static Map<String, SocketChannel> clients = new HashMap<>();

    /**
     * Runs the server as an application
     * @param args args of comand line
     */
    public static void main(String[] args) {
        logger.info("The server is running on port: " + PORT) ;
        new ServerHandler().start();
    }

    /**
     * class of server handler that handling connections
     *
     * @author Ilya Sysoi
     * @version 1.0
     */
    private static class ServerHandler extends Thread {
        private String name;
        private ServerSocketChannel serverSocketChannel;
        private Selector selector;


        ServerHandler() {
            try {
                selector = Selector.open();
                serverSocketChannel = ServerSocketChannel.open();
                serverSocketChannel.configureBlocking(false);
                serverSocketChannel.socket().bind(new InetSocketAddress(InetAddress.getLocalHost(), 9001));

                int ops = serverSocketChannel.validOps();
                serverSocketChannel.register(selector, ops, null);
            } catch (IOException e) {

            }
        }


        public void run() {
            try {
                while (true) {
                    selector.select();

                    Set<SelectionKey> selectedKeys = selector.selectedKeys();
                    Iterator<SelectionKey> iterator = selectedKeys.iterator();

                    while (iterator.hasNext()) {
                        SelectionKey key = iterator.next();
                        if (key.isAcceptable()) {
                            processAcceptEvent(serverSocketChannel, key);
                        } else if (key.isReadable()) {
                            processReadEvent(key);
                        }
                        iterator.remove();
                    }

                }
            } catch (IOException e) {
            }
        }


        private void processAcceptEvent(ServerSocketChannel mySocket,
                                        SelectionKey key) throws IOException {
            logger.info("Client try to connect") ;
            SocketChannel client = mySocket.accept();
            client.configureBlocking(false);

            client.register(selector, SelectionKey.OP_READ);

            ByteBuffer buffer = ByteBuffer.allocate(8192);
            buffer.put("SUBMIT_NAME".getBytes());
            buffer.flip();

            client.write(buffer);
        }


        private void processReadEvent(SelectionKey key)
                throws IOException {
            SocketChannel client = (SocketChannel) key.channel();
            ByteBuffer buffer = ByteBuffer.allocate(8192);
            client.read(buffer);

            String input = new String(buffer.array()).trim();
            buffer.clear();

            if (input.length() > 0) {
                if (input.startsWith("NAME")) {
                    String[] rez = input.split("NAME ");
                    synchronized (clients) {
                        if (clients.containsKey(rez[1])) {
                            logger.info("Client with name ( " + rez[1] + " ) is already connected");
                            buffer.put("SUBMIT_NAME".getBytes());
                        } else {
                            logger.info("Client with name ( " + rez[1] + " ) is connected!");
                            clients.put(rez[1], client);
                            buffer.put("NAME_ACCEPTED".getBytes());
                        }
                    }
                    buffer.flip();
                    client.write(buffer);
                } else {
                    String[] rez = input.split(" image: ");
                    if (clients.containsKey(rez[0])) {
                        buffer.put(("IMAGE " + rez[1]).getBytes());
                        buffer.flip();

                        clients.get(rez[0]).write(buffer);
                        logger.info("Send image to ( " + rez[0] + " )");
                    } else {
                        buffer.put("FAIL_USER".getBytes());
                        buffer.flip();

                        client.write(buffer);
                        logger.info("Client with name ( " + rez[0] + " ) doesn`t exists!");
                    }
                }

            }
        }

    }
}


//
//        while (true) {
//        String input = in.readLine();
//        if (input == null) {
//        return;
//        }
//        String[] rez = input.split(" image: ");
//        if (clients.containsKey(rez[0])) {
//        clients.get(rez[0]).println("IMAGE " + rez[1]);
//        logger.info("Send image from ( " + name + " ) to ( " + rez[0] + " )");
//        } else {
//        out.println("FAIL_USER");
//        logger.info("Client with name ( " + name +" ) doesn`t exists!");
//        }
//
//        }
//        } catch (IOException e) {
//        System.out.println(e);
//        } finally {
//        if (name != null) {
//        clients.remove(name);
//        logger.info("SClient ( " + name + " ) removed");
//        }
//        try {
//        serverSocketChannel.close();
