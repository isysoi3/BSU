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
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Class of server that connect clinets and send images
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Server {

    private static final Logger logger = LogManager.getLogger();

    private static final int PORT = 9001;

    private static Map<String, SocketChannel> clientToSocketChannel = new HashMap<>();
    private static Map<SocketChannel, String> socketChannelToClient = new HashMap<>();

    private static Lock clientLock = new ReentrantLock();

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
                    clientLock.lock();
                        if (clientToSocketChannel.containsKey(rez[1])) {
                            logger.info("Client with name ( " + rez[1] + " ) is already connected");
                            buffer.put("SUBMIT_NAME".getBytes());
                        } else {
                            logger.info("Client with name ( " + rez[1] + " ) is connected!");
                            clientToSocketChannel.put(rez[1], client);
                            socketChannelToClient.put(client, rez[1]);
                            buffer.put("NAME_ACCEPTED".getBytes());
                        }
                    clientLock.unlock();

                    buffer.flip();
                    client.write(buffer);
                } else {
                    String[] rez = input.split(" image: ");
                    clientLock.lock();
                    if (clientToSocketChannel.containsKey(rez[0])) {
                        clientLock.unlock();
                        buffer.put(("IMAGE " + rez[1]).getBytes());
                        buffer.flip();

                        clientToSocketChannel.get(rez[0]).write(buffer);
                        logger.info("Send image to ( " + rez[0] + " )");
                    } else {
                        clientLock.unlock();
                        buffer.put("FAIL_USER".getBytes());
                        buffer.flip();

                        client.write(buffer);
                        logger.info("Client with name ( " + rez[0] + " ) doesn`t exists!");
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
                    if(!key.channel().isOpen()) {
                        try {
                            clientLock.lock();
                            String name = socketChannelToClient.get(key.channel());
                            clientToSocketChannel.remove(name);
                            socketChannelToClient.remove(key.channel());
                            clientLock.unlock();

                            key.channel().close();
                            logger.info("SClient ( " + name + " ) removed");
                        } catch (IOException e) {

                        }
                    }
                    iterator.remove();
                }

            }

        }
    }
}
