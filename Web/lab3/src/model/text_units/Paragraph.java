package model.text_units;

import java.util.regex.Pattern;

public class Paragraph extends TextPart{
    
    public static final String DIVIDERS = "\n";
    public static final String DIVIDERS_PATTERN = "[" + DIVIDERS + "]";
    
    public Paragraph( String value ){
        super( value, Type.PARAGRAPH );
    }
    
    @Override
    protected boolean isCorrect( String value ){
        return !Pattern.compile( DIVIDERS_PATTERN ).matcher( value ).find();
    }
}
