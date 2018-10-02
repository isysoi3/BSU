package controller;

import localization.LocaleWrapper;
import model.text_units.Text;
import model.text_units.TextPart;
import model.text_units.Word;
import model.util.Splitter;
import model.util.VowelComparator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by lenovo on 17.10.2017.
 */
public class Controller {
    Text text;
    VowelComparator wc;
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

    public String findMaxSubStr(){
        Pattern pattern = Pattern.compile("[^a-zA-Z\\u0430-\\u044F\\u0410-\\u042F]+");
        Matcher matcher = pattern.matcher(text.getValue());
        int max_length = 0;
        String max_str = "";
        while (matcher.find()) {
            String str = matcher.group();
            if (str.length() > max_length){
                max_length = str.length();
                max_str = str;
            }
        }
        max_str = max_str.replaceAll("[\\n]", "\\\\n");
        max_str = max_str.replaceAll("[\\r]", "\\\\r");
        max_str = max_str.replaceAll("[\"]", "\\\\\"");
        return LocaleWrapper.getLocalizedString(LocaleWrapper.MAX_SUB_STR) + " \"" + max_str + "\"";
    }

    public String sortByVolwes(List<TextPart> ltp){
        ArrayList<Word> slw= new ArrayList<>();
        for (TextPart tp: ltp)
            if (tp instanceof Word)
                slw.add((Word)tp);
        String res = LocaleWrapper.getLocalizedString(LocaleWrapper.SORTED_WORDS) +
                 ":\n____________________________________________________________________\n";
        slw.sort(wc);
        for (Word w: slw)
            res+=w.getValue() + "\n";
        return res+"\n___________________________________________________________________\n";
    }

    public Text getText(){
        return text;
    }
}
