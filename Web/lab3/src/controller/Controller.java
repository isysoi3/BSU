package controller;

import localization.LocaleWrapper;
import model.Text;
import splitters.TextSplitter;

import java.io.IOException;
import java.lang.module.InvalidModuleDescriptorException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Controller {

    private String textString;

    public String getTextString() {
        return textString;
    }

    public String loadText(String path){
        try {
            byte [] encoded = Files.readAllBytes(Paths.get(path));
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


}
