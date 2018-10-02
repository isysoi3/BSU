package model.text_units;

public class Code extends TextPart{
    
    public static final String DIVIDER = "<code>";
    public static final String DIVIDERS_PATTERN = DIVIDER;
    
    public Code( String value ){
        super( value, Type.CODE );
    }

    @Override
    protected boolean isCorrect(String value) {
        return true;
    }
    
    
}
