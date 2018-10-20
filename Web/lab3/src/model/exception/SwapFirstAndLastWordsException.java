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

    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }

}
