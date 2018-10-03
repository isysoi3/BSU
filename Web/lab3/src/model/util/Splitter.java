package model.util;

import model.text_units.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Splitter {
    protected String trim( String str ){
        str = str.trim();
        str = str.replaceAll( "[\t ]+", " ");
        return str;
    }

    ArrayList<TextPart> parts;
    int level;

    public int getLevel(){
        return level;
    }

    public List<TextPart> getTextParts(){
        return Collections.unmodifiableList(parts);
    }

    public Splitter (Text text){
        level = 0;
        parts = new ArrayList<>();
        String[] splitted = text.getValue().split( Code.DIVIDERS_PATTERN );
        for( int i = 0; i < splitted.length; ++i ) {
            if ((i & 1) == 1) {
                String code = trim(splitted[i]);
                if (code.length() > 0) {
                    parts.add(new Code(code));
                }
            } else {
                String[] paragraphs = splitted[i].split(Paragraph.DIVIDERS_PATTERN);
                for (String originParagraph : paragraphs) {
                    String paragraph = trim(originParagraph);
                    if (paragraph.length() > 0) {
                        parts.add(new Paragraph(paragraph));
                    }
                }
            }
        }
    }

    public Splitter (Splitter sp) throws IllegalAccessException {
        this.level = sp.getLevel() + 1;
        switch (level){
            case 1:
                parts = new ArrayList<>();
                for (TextPart textPart: sp.getTextParts()) {
                    ArrayList<TextPart> all = split1(textPart);
                    all.get(all.size() - 1).setEndLevel(2);
                    parts.addAll(all);
                }
                break;
            case 2:
                parts = new ArrayList<>();
                for (TextPart textPart: sp.getTextParts()) {
                    ArrayList<TextPart> all = split2(textPart);
                    all.get(all.size() - 1).setEndLevel(textPart.getEndLevel());
                    all.get(all.size() - 1).setEndLevel(1);
                    parts.addAll(all);
                }
                break;
            case 3:
                throw new IllegalAccessException("Trying to split min level");
        }
    }

    public Splitter(Splitter sp, int pos) throws IllegalAccessException {
        this.level = sp.getLevel() + 1;
        switch (level) {
            case 1:
                parts = split1(sp.getTextParts().get(pos));
                break;
            case 2:
                parts = split2(sp.getTextParts().get(pos));
                break;
            case 3:
                throw new IllegalAccessException("Trying to split min level");
        }
    }

    private ArrayList<TextPart> split1(TextPart textPart){
        ArrayList<TextPart> parts = new ArrayList<>();
        switch( textPart.getType() ) {
            case PARAGRAPH:
                Matcher matcher = Pattern.compile(Sentence.PATTERN + "(" +
                        Sentence.DIVIDERS_PATTERN + "|\\z)").matcher(textPart.getValue());
                while (matcher.find()) {
                    parts.add(new Sentence(trim(matcher.group())));
                }
                break;
            case CODE:
                String[] codeLines = textPart.getValue().split(CodeLine.DIVIDERS_PATTERN);

                for (String originLine : codeLines) {
                    String line = trim(originLine);

                    if (line.length() > 0) {
                        parts.add(new CodeLine(line));
                    }
                }
                break;
        }
        return parts;
    }

    private ArrayList<TextPart> split2(TextPart textPart) {
        ArrayList<TextPart> parts = new ArrayList<>();
        switch( textPart.getType() ) {
            case SENTENCE:
                Matcher matcher = Pattern.compile( "(" + Word.PATTERN + "|" +
                        PunctuationMark.PATTERN + ")" ).matcher(textPart.getValue());
                while (matcher.find()) {
                    if (Pattern.compile(PunctuationMark.PATTERN).matcher(matcher.group()).matches()) {
                        parts.add(new PunctuationMark(trim(matcher.group())));
                    } else {
                        parts.add(new Word(trim(matcher.group())));
                    }
                }
                break;
            case CODE_LINE:
                String[] lexemes = textPart.getValue().split(CodeLexeme.DIVIDERS_PATTERN);
                for (String lexeme : lexemes) {
                    parts.add(new CodeLexeme(trim(lexeme)));
                }
                break;
        }
        return parts;
    }

    public Splitter(Combiner cb){
        this.level = cb.getLevel();
        this.parts = cb.getTextParts();
    }
}
