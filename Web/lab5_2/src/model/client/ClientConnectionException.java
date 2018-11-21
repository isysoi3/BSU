package model.client;

/**
 * Class representing client exception
 * @author Ilya Sysoi
 */
public class ClientConnectionException extends Exception {


    /**
     * Constructor with specified string
     * @param message string
     */
    public ClientConnectionException(String message) {
        super(message);
    }

    /**
     * Constructor with specified string and exception
     * @param message string
     * @param e error covered
     */
    public ClientConnectionException(String message, Throwable e){
        super(message, e);
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }

}
