package model.text_units;

public abstract class TextPart {

    public enum Type{
        WORD(3),
        PUNCTUATION_MARK(3),
        CODE_LEXEME(3),
        SENTENCE(2),
        CODE_LINE(2),
        PARAGRAPH(1),
        CODE(1),
        TEXT(0);

        private int level;

        Type( int level ){
            this.level = level;
        }


        public int getLevel() {
            return level;
        }
    }
    
    private final Type type;

    public Type getType(){
        return this.type;
    }

    private void checkType( Type type ){
        if( type == null){
            throw new IllegalArgumentException( "Illegal argument type" );
        }
    }
    
    private final String value;

    public String getValue(){
        return this.value;
    }
    
    private int endLevel;

    public void setEndLevel(int level){
        if (level > endLevel)
            this.endLevel = level;
    }

    public int getEndLevel(){
        return endLevel;
    }

    public boolean isEnd(int level){
        return level<=endLevel;
    }

    public TextPart( String value, Type type ){
        if( value == null || !isCorrect( value ) ){
            throw new IllegalArgumentException("The value: " + value + " doesn't match type " + type);
        }
        checkType( type );
        this.value = value;
        this.type = type;
        this.endLevel = 0;
    }

    protected abstract boolean isCorrect( String value );

    @Override
    public int hashCode() {
        int result = value.hashCode();
        result = 31 * result + type.hashCode();
        result = 31 * result + endLevel;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if( this == obj ) 
            return true;
        if( obj == null || getClass() != obj.getClass() )
            return false;
        
        TextPart textPart = ( TextPart ) obj;
        
        if( endLevel != textPart.endLevel )
            return false;
        if( !value.equals( textPart.value ) )
            return false;
        
        return type == textPart.type;
    }
    
    @Override
    public String toString(){
        return value;
    }
}
