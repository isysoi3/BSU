package model.util;

import localization.LocaleWrapper;
import model.text_units.Word;

import java.util.Comparator;

public class VowelComparator implements Comparator<Word>{

    final private char[] vowels;

    public VowelComparator(char[] vowels){
        this.vowels = vowels;
    }


    public double getProportionOfVowels(String word){
        if (word.length() == 0)
            return 0;
        int vowelCount = 0;
        word = word.toLowerCase();
        for (int i =0; i < word.length(); ++i){
            boolean isVowel = false;
            for (int j = 0; j < vowels.length; ++j)
                if (word.charAt(i) == vowels[j])
                    isVowel = true;
            if (isVowel)
                vowelCount += 1;
        }
        return (double)vowelCount/word.length();
    }


    @Override
    public int compare(Word o1, Word o2) {
        return Double.compare(getProportionOfVowels(o2.getValue()), getProportionOfVowels(o1.getValue()));
    }
}
