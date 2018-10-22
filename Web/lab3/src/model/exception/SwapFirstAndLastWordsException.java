package model.exception;

/**
 * Class representing invalid sentence
 * @author Ilya Sysoi
 */
public class SwapFirstAndLastWordsException extends Exception {

    /**
     * Constructor with specified string
     * @param message string
     */
    public SwapFirstAndLastWordsException(String message) {
        super(message);
    }

    public SwapFirstAndLastWordsException(String message, Throwable e) {
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
