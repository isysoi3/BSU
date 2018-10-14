package controller;

import localization.LocaleHelper;
import model.Text;
import model.text_unit.text.part.Word;
import parser.TextParser;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * word text splitter parser
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    private String textString;

    public String getTextString() {
        return textString;
    }

    /**
     * load text
     * @param path path to file
     * @throws IllegalArgumentException if no file
     * @return text string
     *
     */
    public String loadText(String path) {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get(path));
            textString = new String(encoded, Charset.forName("windows-1251"));
            return LocaleHelper.getLocalizedString(LocaleHelper.FILE_LOADED);
        } catch (IOException e) {
            throw new IllegalArgumentException(LocaleHelper.getLocalizedString(LocaleHelper.INVALID_ARGS));
        }
    }

    /**
     * parse text string to text object
     * @return text object
     *
     */
    public Text parseTextStringToText() {
        TextParser textParser = new TextParser();
        return textParser.splitText(textString);

    }

    /**
     * swap last and first words and text
     * @param text text object
     * @return swapped text object
     *
     */
    public Text swapFirstAndLastWordInText(Text text) {
        return text.swapFirstAndLastWords();
    }

    /**
     * sort words with started vowel by consonant in text
     * @param text text object
     * @return sorted words
     *
     */
    public List<Word> sortWordsWithStartedVowelByConsonantInText(Text text) {
        ArrayList<Word> words = text.getAllTextWords();
        String vowelsPattern = "(?i)^[aeiouyаоиеёэыуюя].*$";
        String noVowel = "[aeiouyаоиеёэыуюя]+";

        return words.stream()
                .filter(word -> word.getText().toLowerCase().matches(vowelsPattern)
                        && !word.getText().toLowerCase().replaceAll(noVowel, "").isEmpty())
                .sorted((w1, w2) -> {
                    String w1OnlyConsonants = w1.getText().toLowerCase().replaceAll(noVowel, "");
                    String w2OnlyConsonants = w2.getText().toLowerCase().replaceAll(noVowel, "");
                    return w1OnlyConsonants.compareTo(w2OnlyConsonants);
                })
                .collect(Collectors.toList());
    }

}
