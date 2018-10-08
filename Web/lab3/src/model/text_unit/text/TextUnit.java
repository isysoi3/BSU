package model.text_unit.text;

public abstract class TextUnit {

    protected TextUnitTypeEnum type;

    public String getValue() {
        return value;
    }

    protected String value;

    public TextUnitTypeEnum getType() {
        return type;
    }

    protected TextUnit(String value, TextUnitTypeEnum type){
        if( type == null){
            throw new IllegalArgumentException( "Illegal argument type" );
        }
        this.type = type;
        this.value = value;
    }

}