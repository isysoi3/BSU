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
        try {
            ServerHandler serverHandler = new ServerHandler();
            serverHandler.work();
        } catch (ServerException e) {
            logger.error(e);
        }
    }

    /**
     * class of server handler that handling connections
     *
     * @author Ilya Sysoi
     * @version 1.0
     */
    private static class ServerHandler {
        private ServerSocketChannel serverSocketChannel;
        private Selector selector;


        ServerHandler() throws ServerException {
            try {
                serverSocketChannel = ServerSocketChannel.open();
                serverSocketChannel.configureBlocking(false);
                serverSocketChannel.socket().bind(new InetSocketAddress(InetAddress.getLocalHost(), 9001));

            } catch (IOException e) {
                throw new ServerException("Server socket chanel problems", e);
            }

            try {
                selector = Selector.open();
                int ops = serverSocketChannel.validOps();
                serverSocketChannel.register(selector, ops, null);
            } catch (IOException e) {
                throw new ServerException("Selector problems", e);
            }
        }


        private void acceptNewClient() throws IOException {
            logger.info("Client try to connect") ;
            SocketChannel client = serverSocketChannel.accept();
            client.configureBlocking(false);

            client.register(selector, SelectionKey.OP_READ);

            ByteBuffer buffer = ByteBuffer.allocate(8192);
            buffer.put("SUBMIT_NAME".getBytes());
            buffer.flip();

            client.write(buffer);
        }


        private void readMessage(SelectionKey key) throws IOException {
            SocketChannel client = (SocketChannel) key.channel();
            ByteBuffer buffer = ByteBuffer.allocate(8192);
            client.read(buffer);

            String input = new String(buffer.array()).trim();
            buffer.clear();

            if (input.length() > 0) {
                if (input.startsWith("NAME")) {
                    String[] rez = input.split("NAME ");
                    if (rez.length < 2) {
                        buffer.put("SUBMIT_NAME".getBytes());
                    } else {
                        String name = rez[1];
                        synchronized (clients) {
                            if (clients.containsKey(name)) {
                                logger.info("Client with name ( " + name + " ) is already connected");
                                buffer.put("SUBMIT_NAME".getBytes());
                            } else {
                                logger.info("Client with name ( " + name + " ) is connected!");
                                clients.put(name, client);
                                buffer.put("NAME_ACCEPTED".getBytes());
                            }
                        }
                    }
                    buffer.flip();
                    client.write(buffer);
                } else if (input.startsWith("EXIT")) {
                    String[] rez = input.split("EXIT ");
                    String name = rez[1];
                    try {
                        synchronized (clients) {
                            clients.remove(name);
                        }

                        key.channel().close();
                        logger.info("Client ( " + name + " ) removed");
                    } catch (IOException e) {

                    }
                } else {
                    String[] rez = input.split(" image: ");
                    synchronized (clients) {
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

        public void work() throws ServerException {
            while (true) {
                try {
                    selector.select();
                } catch (IOException e) {
                    throw new ServerException("Selector selec", e);
                }

                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    if (key.isAcceptable()) {
                        try {
                            acceptNewClient();
                        } catch (IOException e) {
                            throw new ServerException("New client accept exception", e);
                        }
                    } else if (key.isReadable()) {
                        try {
                            readMessage(key);
                        } catch (IOException e) {
                            throw new ServerException("Client read exception", e);
                        }
                    }
                    iterator.remove();
                }

            }

        }
    }
}
