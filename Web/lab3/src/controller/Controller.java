package controller;

import localization.LocaleWrapper;
import model.Text;
import model.text_unit.text.part.Word;
import splitters.TextSplitter;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Controller {

    private String textString;

    public String getTextString() {
        return textString;
    }

    public String loadText(String path) {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get(path));
            textString = new String(encoded, Charset.forName("windows-1251"));
            return LocaleWrapper.getLocalizedString(LocaleWrapper.FILE_LOADED);
        } catch (IOException e) {
            throw new IllegalArgumentException(LocaleWrapper.getLocalizedString(LocaleWrapper.INVALID_ARGS));
        }
    }

    public Text parseTextStringToText() {
        TextSplitter textSplitter = new TextSplitter();
        return textSplitter.splitText(textString);

    }

    public Text swapFirstAndLastWordInText(Text text) {
        return text.swapFirstAndLastWords();
    }

    public List<Word> sortWordsWithStartedVowelByConsonantInText(Text text) {
        ArrayList<Word> words = text.getAllTextWords();
        String vowelsPattern = "(?i)^[aeiouyàóå¸îÿèþ].*$";
        String noVowel = "[^aeiouyàóå¸îÿèþ]+";

        return words.stream()
                .filter(word -> word.getText().toLowerCase().matches(vowelsPattern) && !word.getText().toLowerCase().replaceAll("[aeiouyàóå¸îÿèþ]", "").isEmpty())
                .sorted((w1, w2) -> {
                    String w1OnlyConsonants = w1.getText().toLowerCase().replaceAll("[aeiouyàóå¸îÿèþ]", "");
                    String w2OnlyConsonants = w2.getText().toLowerCase().replaceAll("[aeiouyàóå¸îÿèþ]", "");
                    return w1OnlyConsonants.equals(w2OnlyConsonants) ? 1 : 0;
                })
                .collect(Collectors.toList());
    }

}
