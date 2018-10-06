package controller;

import localization.LocaleWrapper;
import model.Text;
import model1231.util.Splitter;

import java.io.IOException;
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


    public String loadController(String path, String fileLocale, String programLocale){
        try {
            String text = new String( Files.readAllBytes( Paths.get( path ) ) );
            this.text = new Text(text);
            LocaleWrapper.setLocale(programLocale);
            wc = new VowelComparator(LocaleWrapper.getVowels(fileLocale));
        } catch (IOException e) {
            return LocaleWrapper.getLocalizedString(LocaleWrapper.INVALID_ARGS);
        }
        return LocaleWrapper.getLocalizedString(LocaleWrapper.FILE_LOADED);
    }

   public String printTextPart(Splitter sp){
        String res=LocaleWrapper.getLocalizedString(LocaleWrapper.DIVIDING_LEVEL) +
                ": " + sp.getLevel() + "\n_________________________________________\n";
        for (TextPart tp: sp.getTextParts())
            res+=tp.getType().toString() + ": " + tp.getValue()+"\n";
        return res+"\n\n";
   }


}
