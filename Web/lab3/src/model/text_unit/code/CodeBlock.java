package model.text_unit.code;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

import java.util.ArrayList;

public class CodeBlock extends TextUnit {

    public static final String DIVIDER = "<code>";

    private ArrayList<CodeLine> code;

    public ArrayList<CodeLine> getCode() {
        return code;
    }

    public CodeBlock(String value) {
        super(value, TextUnitTypeEnum.CODE_BLOCK);
        code = new ArrayList<>();
    }

    public void addCodeLine(CodeLine codeLine) {
        code.add(codeLine);
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder("\n" + DIVIDER);
        for (CodeLine codeLine : code) {
            textToString.append("\n" + codeLine.toString());
        }
        textToString.append("\n" + DIVIDER);
        return textToString.toString();
    }
}
