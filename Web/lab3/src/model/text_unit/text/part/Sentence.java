package model.text_unit.text.part;

import model.text_unit.text.TextUnitTypeEnum;
import model.text_unit.text.TextUnit;

import java.util.ArrayList;

public class Sentence extends TextUnit {

    public static final String SENTENCE_NAME = "SENTENCE";
    public static final String DIVIDER = "\\.!\\?";
    public static final String DELIM_FOR_COMBINING = " ";
    public static final String SPLITTING_REGEX = "[^" + DIVIDER + "]+([" + DIVIDER + "]+|\\z)";
    private ArrayList<TextUnit> sentence;


    public Sentence() {
        super(TextUnitTypeEnum.SENTENCE);
        sentence = new ArrayList<>();
    }

    public void addWord(Word word) {
        sentence.add(word);
    }

    public void addPunctuationMark(PunctuationMark punctuationMark) {
        sentence.add(punctuationMark);
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder();
        for (TextUnit textUnit : sentence) {
            textToString.append(textUnit.toString());
            if (sentence.indexOf(textUnit) != 0)
                textToString.append(" ");
        }
        return SENTENCE_NAME;
    }
}
