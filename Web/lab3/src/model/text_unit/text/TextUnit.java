package model.text_unit.text;

public abstract class TextUnit {

    protected TextUnitTypeEnum type;

    public TextUnitTypeEnum getType() {
        return type;
    }

    protected TextUnit(TextUnitTypeEnum type){
        if( type == null){
            throw new IllegalArgumentException( "Illegal argument type" );
        }
        this.type = type;
    }

}