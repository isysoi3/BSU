package logger;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.SimpleFormatter;

/**
 * Class representing logger wrapper
 *
 * @author Ilya Sysoi
 */
public class LoggerWrapper {
    private static final java.util.logging.Logger logger = java.util.logging.Logger.getLogger(LoggerWrapper.class.getName());

    static {
        logger.setUseParentHandlers(false);
        Handler fileHandler;
        try {
            fileHandler = new FileHandler("logger", 1000000, 10);
            fileHandler.setFormatter(new SimpleFormatter());
            logger.addHandler(fileHandler);
            fileHandler.setLevel(Level.ALL);
            logger.setLevel(Level.ALL);
            logger.config("Configuration done.");
        } catch (IOException exception) {
            logger.log(Level.SEVERE, "Error occur in FileHandler.", exception);
        }
    }


    /**
     * Message with level SEVERE
     *
     * @param message message string
     */
    public static void severe(String message) {
        logger.severe(message);
    }

    /**
     * Message ingo
     *
     * @param message message string
     */
    public static void info(String message) {
        logger.info(message);
    }

}
