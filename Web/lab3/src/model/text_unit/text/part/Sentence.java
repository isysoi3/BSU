package model.text_unit.text.part;

import localization.LocaleHelper;
import model.exception.SwapFirstAndLastWordsException;
import model.text_unit.code.CodeBlock;
import model.text_unit.text.TextUnitTypeEnum;
import model.text_unit.text.TextUnit;

import java.util.ArrayList;

/**
 * Sentence
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Sentence extends TextUnit {

    public static final String SENTENCE_NAME = "SENTENCE";
    public static final String DIVIDER = "\\.!\\?";
    public static final String DELIM_FOR_COMBINING = " ";
    public static final String SPLITTING_REGEX = "[^" + DIVIDER + "]+([" + DIVIDER + "]+|\\z)";
    private ArrayList<TextUnit> sentence;


    /**
     * constructor
     * @param text text sentence value
     *
     */
    public Sentence(String text) {
        super(text, TextUnitTypeEnum.SENTENCE);
        sentence = new ArrayList<>();
    }

    /**
     * add word to sentence
     * @param word word
     *
     */
    public void addWord(Word word) {
        sentence.add(word);
    }

    public ArrayList<Word> getWords() {
        ArrayList<Word> words = new ArrayList<>();
        for (TextUnit textUnit : sentence) {
            if (textUnit.getClass() == Word.class)
                words.add((Word)textUnit);
        }
        return words;
    }

    /**
     * add  punctuation mark
     * @param punctuationMark punctuation mark
     *
     */
    public void addPunctuationMark(PunctuationMark punctuationMark) {
        sentence.add(punctuationMark);
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder();
        for (TextUnit textUnit : sentence) {
            if (textUnit.getClass() != PunctuationMark.class && sentence.indexOf(textUnit) != 0)
                textToString.append(DELIM_FOR_COMBINING);
            textToString.append(textUnit.toString());

        }
        return textToString.toString();
    }

    /**
     * swap to words in sentence
     *
     */
    public void swapFirstAndLastWords()  throws SwapFirstAndLastWordsException {
        int sentenceSize = sentence.size();

        if (sentenceSize < 3) {
            throw new SwapFirstAndLastWordsException(LocaleHelper.getLocalizedString(LocaleHelper.SWAP_ERROR));
        }

        TextUnit firstWord = sentence.remove(0),
                lastWord = sentence.remove(sentenceSize -3);
        sentence.add(0, lastWord);
        sentence.add(sentenceSize-2, firstWord);
    }

}
