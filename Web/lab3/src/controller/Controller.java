package controller;

import localization.LocaleHelper;
import logger.LoggerWrapper;
import model.Text;
import model.exception.FileException;
import model.text_unit.text.part.Word;
import parser.TextParser;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDate;
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
    public String loadText(String path) throws FileException {
        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.FILE_LOADING));

        try {
            byte[] encoded = Files.readAllBytes(Paths.get(path));
            textString = new String(encoded, Charset.forName("windows-1251"));
        } catch (IOException e) {
            throw new FileException(LocaleHelper.getLocalizedString(LocaleHelper.INVALID_ARGS));
        }

        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.FILE_LOADED));

        return textString;
    }

    /**
     * parse text string to text object
     * @return text object
     *
     */
    public Text parseTextStringToText() {
        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.START_TEXT_PARSING));

        TextParser textParser = new TextParser();
        Text parsedText = textParser.splitText(textString);

        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.FINISH_TEXT_PARSING));
        return parsedText;
    }

    /**
     * swap last and first words and text
     * @param text text object
     * @return swapped text object
     *
     */
    public Text swapFirstAndLastWordInText(Text text) {
        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.START_WORDS_SWAPPING));

        Text swapedWordsText = text.swapFirstAndLastWords();

        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.FINISH_WORDS_SWAPPING));
        return swapedWordsText;
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

        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.START_WORDS_SORTING));

        List<Word> sortedWords = words.stream()
                .filter(word -> word.getText().toLowerCase().matches(vowelsPattern)
                        && !word.getText().toLowerCase().replaceAll(noVowel, "").isEmpty())
                .sorted((w1, w2) -> {
                    String w1OnlyConsonants = w1.getText().toLowerCase().replaceAll(noVowel, "");
                    String w2OnlyConsonants = w2.getText().toLowerCase().replaceAll(noVowel, "");
                    return w1OnlyConsonants.compareTo(w2OnlyConsonants);
                })
                .collect(Collectors.toList());

        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.FINISH_WORDS_SORTING));
        return sortedWords;
    }

}
