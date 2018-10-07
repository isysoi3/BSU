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
        text.add(codeBlock);
    }

    public ArrayList<Sentence> getSentences() {
        ArrayList<Sentence> sentences = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == Sentence.class)
                sentences.add((Sentence)textUnit);
        }
        return sentences;
    }

    public ArrayList<Paragraph> getParagraphs() {
        ArrayList<Paragraph> paragraphs = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == Paragraph.class)
                paragraphs.add((Paragraph)textUnit);
        }
        return paragraphs;
    }

    public ArrayList<CodeBlock> getCodeBlocks() {
        ArrayList<CodeBlock> codeBlocks = new ArrayList<>();
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == CodeBlock.class)
                codeBlocks.add((CodeBlock)textUnit);
        }
        return codeBlocks;
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder();
        for (TextUnit textUnit : text) {
            textToString.append(textUnit.toString());
            if (textUnit.getClass() == Sentence.class)
                textToString.append(" ");
        }
        return textToString.toString();
    }

    public Text swapFirstAndLastWords() {
        for (TextUnit textUnit : text) {
            if (textUnit.getClass() == Sentence.class)
                ((Sentence)textUnit).swapFirstAndLastWords();
        }
        return this;
    }

}
