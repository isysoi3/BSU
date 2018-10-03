package model.text_units;

import java.util.regex.Pattern;

public class CodeLexeme extends TextPart{
    
    public static final String DIVIDERS = " ";
    public static final String DIVIDERS_PATTERN = "[" + DIVIDERS + "]+";
    
    public CodeLexeme( String value ){
        super( value, Type.CODE_LEXEME );
    }
    
    @Override
    public boolean isCorrect( String value ){
        return !Pattern.compile( "(" + DIVIDERS_PATTERN + "|" + CodeLine.DIVIDERS_PATTERN + ")").matcher( value ).find();
    }
}
