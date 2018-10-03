package model.text_units;

import java.util.regex.Pattern;

public class Word extends TextPart {
    
    public static final String DIVIDERS = ",;:'\"";
    public static final String DIVIDERS_PATTERN = "[" + DIVIDERS + "]";
    public static final String PATTERN = "[^ " + Paragraph.DIVIDERS + Sentence.DIVIDERS + DIVIDERS +  "]+";
    
    public Word( String value ){
        super( value, Type.WORD);
    }
    
    @Override
    protected boolean isCorrect( String value ){
        return Pattern.compile( PATTERN ).matcher( value ).matches();
    }
}
