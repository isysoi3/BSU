package controller;

import localization.LocaleWrapper;
import model.Text;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by lenovo on 17.10.2017.
 */
public class Controller {

    private Text text;

    public Text getText(){
        return text;
    }


    public String loadText(String path, String fileLocale, String programLocale){
        try {
            byte [] encoded = Files.readAllBytes(Paths.get(path));
            String text = new String(encoded, Charset.forName("windows-1251"));
            return text;
            //LocaleWrapper.setLocale(programLocale);
        } catch (IOException e) {
            return LocaleWrapper.getLocalizedString(LocaleWrapper.INVALID_ARGS);
        }
        //return LocaleWrapper.getLocalizedString(LocaleWrapper.FILE_LOADED);
    }

   public String printTextPart(){
        return text.toString();
   }

    public void parseTextStringToText(String text) {

    }


}
