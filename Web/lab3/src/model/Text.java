package model;

import model.text_unit.code.CodeBlock;
import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;
import model.text_unit.text.part.Paragraph;
import model.text_unit.text.part.Sentence;

import java.util.ArrayList;

public class Text extends TextUnit {

    public static final String TEXT_NAME = "TEXT";
    private ArrayList<TextUnit> text;


    public Text() {
        super("",TextUnitTypeEnum.TEXT);
        text = new ArrayList<>();
    }

    public void addSentence(Sentence sentence) {
        text.add(sentence);
    }

    public void addParagraph(Paragraph paragraph) {
        text.add(paragraph);
    }

    public void addCode(CodeBlock codeBlock) {
        //text.add(codeBlock);
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder();
        for (TextUnit textUnit : text) {
            textToString.append(textUnit.toString());
        }
        return textToString.toString();
    }

}
