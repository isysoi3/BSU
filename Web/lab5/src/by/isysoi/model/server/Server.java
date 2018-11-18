package by.isysoi.model.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;


public class Server {

    private static final int PORT = 9001;

    private static Map<String, PrintWriter> clients = new HashMap<>();

    public static void main(String[] args) throws Exception {
        System.out.println("The chat server is running.");
        try (ServerSocket listener = new ServerSocket(PORT)) {
            while (true) {
                new ServerHandler(listener.accept()).start();
            }
        }
    }


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
                            continue;
                        } else {
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
                    } else {
                        out.println("FAIL_USER");
                    }

                }
            } catch (IOException e) {
                System.out.println(e);
            } finally {
                if (name != null) {
                    clients.remove(name);
                }
                try {
                    socket.close();
                } catch (IOException e) {
                }
            }
        }
    }
}