package model.text_units;

import java.util.regex.Pattern;

public class CodeLine extends TextPart {
    
    public static final String DIVIDERS = "\n";
    public static final String DIVIDERS_PATTERN = "[" + DIVIDERS + "]";
    
    public CodeLine( String value ){
        super( value, Type.CODE_LINE);
    }
    
    @Override
    protected boolean isCorrect( String value ){
        return !Pattern.compile( DIVIDERS_PATTERN ).matcher( value ).find();
    }
}
