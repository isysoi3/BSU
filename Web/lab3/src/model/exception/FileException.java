package model.exception;

/**
 * Class representing file not found exception
 * @author Ilya Sysoi
 */
public class FileException extends Exception {

    public FileException(String message){
        super("File is incorrect, " + message);
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
