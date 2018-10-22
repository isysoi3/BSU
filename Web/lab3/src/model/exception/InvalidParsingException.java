package model.exception;


/**
 * Class representing invalid split or combine exception
 * @author Ilya Sysoi
 */
public class InvalidParsingException extends Exception {

    /**
     * Constructor with specified string
     * @param message string
     */
    public InvalidParsingException(String message) {
        super(message);
    }

    public InvalidParsingException(String message, Throwable e) {
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
