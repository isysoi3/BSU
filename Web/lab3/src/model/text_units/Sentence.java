package model.text_units;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Sentence extends TextPart{
    
    public static final String DIVIDERS = "\\.\\?!";
    public static final String DIVIDERS_PATTERN = "[" + DIVIDERS + "]+";
    public static final String PATTERN = "[^" + DIVIDERS + "]+";
    
    public Sentence( String value ){
        super( value, Type.SENTENCE );
    }
    
    @Override
    protected boolean isCorrect( String value ){
        if( Pattern.compile( Paragraph.DIVIDERS_PATTERN ).matcher( value ).find() ){
            return false;
        }
        
        Matcher matcher = Pattern.compile( DIVIDERS_PATTERN ).matcher( value );
        int count = 0 ;
        
        while( matcher.find() ){
            ++count;
        }
        return count <= 1;
    }
}
