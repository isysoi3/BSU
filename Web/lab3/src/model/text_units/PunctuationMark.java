package model.text_units;

import java.util.regex.Pattern;

public class PunctuationMark extends TextPart{
    
    public static final String PATTERN = "(" + Sentence.DIVIDERS_PATTERN + "|" +
            Word.DIVIDERS_PATTERN + ")";
    
    public PunctuationMark( String value ){
        super( value, Type.PUNCTUATION_MARK );
    }
    
    @Override
    protected boolean isCorrect( String value ){
        return Pattern.compile( PATTERN ).matcher( value ).matches();
    }
}
