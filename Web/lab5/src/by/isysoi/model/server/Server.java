package by.isysoi.model.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

/**
 * Class of server that connect clinets and send images
 *
 * @author Ilya Sysoi
 * @version 1.0
 */
public class Server {

    private static final Logger logger = LogManager.getLogger();

    private static final int PORT = 9001;

    private static Map<String, PrintWriter> clients = new HashMap<>();

    /**
     * Runs the server as an application
     * @param args args of comand line
     */
    public static void main(String[] args) {
        logger.info("The server is running on port: " + PORT) ;
        try (ServerSocket listener = new ServerSocket(PORT)) {
            while (true) {
                new ServerHandler(listener.accept()).start();
            }
        }
        catch (IOException e) {
            logger.error(e);
        }
    }

    /**
     * class of server handler that handling connections
     *
     * @author Ilya Sysoi
     * @version 1.0
     */
    private static class ServerHandler extends Thread {
        private String name;
        private Socket socket;
        private BufferedReader in;
        private PrintWriter out;


        ServerHandler(Socket socket) {
            this.socket = socket;
        }


        public void run() {
            try {

                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out = new PrintWriter(socket.getOutputStream(), true);

                while (true) {
                    out.println("SUBMIT_NAME");
                    name = in.readLine();
                    if (name == null) {
                        continue;
                    }
                    synchronized (clients) {
                        if (clients.containsKey(name)) {
                            logger.info("Client with name ( " + name +" ) is already connected");
                        } else {
                            logger.info("Client with name ( " + name +" ) is connected!");
                            break;
                        }
                    }
                }

                out.println("NAME_ACCEPTED");
                clients.put(name, out);

                while (true) {
                    String input = in.readLine();
                    if (input == null) {
                        return;
                    }
                    String[] rez = input.split(" image: ");
                    if (clients.containsKey(rez[0])) {
                        clients.get(rez[0]).println("IMAGE " + rez[1]);
                        logger.info("Send image from ( " + name + " ) to ( " + rez[0] + " )");
                    } else {
                        out.println("FAIL_USER");
                        logger.info("Client with name ( " + name +" ) doesn`t exists!");
                    }

                }
            } catch (IOException e) {
                System.out.println(e);
            } finally {
                if (name != null) {
                    clients.remove(name);
                    logger.info("SClient ( " + name + " ) removed");
                }
                try {
                    socket.close();
                } catch (IOException e) {
                }
            }
        }
    }
}