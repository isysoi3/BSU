package model.util;

import model.text_units.*;

import java.util.ArrayList;
public class Combiner {
    private int level;
    private ArrayList<TextPart> parts;

    public int getLevel(){
        return level;
    }

    public ArrayList<TextPart> getTextParts(){
        return parts;
    }

    public static Splitter combine(Splitter sp) throws IllegalAccessException {
        switch (sp.getLevel()){
            case 2: {
                ArrayList<TextPart> parts = new ArrayList<>();
                String nextLevelTextPart = "";
                for (TextPart tp : sp.getTextParts()) {
                    if (tp.getType() == TextPart.Type.CODE_LEXEME) {
                        nextLevelTextPart += CodeLexeme.DIVIDERS + tp.getValue();
                        if (tp.isEnd(1)) {
                            CodeLine add = new CodeLine(nextLevelTextPart.trim());
                            if (tp.isEnd(2))
                                add.setEndLevel(2);
                            parts.add(add);
                            nextLevelTextPart = "";
                        }
                    }else {
                        if (tp.getType() == TextPart.Type.WORD)
                            nextLevelTextPart += " " + tp.getValue();
                        if (tp.getType() == TextPart.Type.PUNCTUATION_MARK)
                            nextLevelTextPart += tp.getValue();
                        if (tp.isEnd(1)) {
                            Sentence add = new Sentence(nextLevelTextPart.trim());
                            if (tp.isEnd(2))
                                add.setEndLevel(2);
                            parts.add(add);
                            nextLevelTextPart = "";
                        }
                    }
                }
                return new Splitter(new Combiner(parts, 1));
            }
            case 1: {
                ArrayList<TextPart> parts = new ArrayList<>();
                String nextLevelTextPart = "";
                for (TextPart tp : sp.getTextParts()) {
                    if (tp.getType() == TextPart.Type.CODE_LINE) {
                        nextLevelTextPart += CodeLine.DIVIDERS + tp.getValue();
                        if (tp.isEnd(2)) {
                            parts.add(new Code(nextLevelTextPart.trim()));
                            nextLevelTextPart = "";
                        }
                    } else {
                        if (tp.getType() == TextPart.Type.SENTENCE) {
                            nextLevelTextPart += " " + tp.getValue();
                            if (tp.isEnd(2)) {
                                parts.add(new Paragraph(nextLevelTextPart.trim()));
                                nextLevelTextPart = "";
                            }
                        }
                    }
                }
                return new Splitter(new Combiner(parts, 0));
            }
            default:
                throw new IllegalAccessException("Trying to combine to text(use combineToText())");
        }
    }

    public static Text combineToText(Splitter sp) throws IllegalAccessException {
        String str = "";
        if (sp.getLevel() != 0)
            throw new IllegalAccessException("Cant combine from non zero level(use compine(Splitter) func)");
        for (TextPart tp: sp.getTextParts()){
            if (tp.getType() == TextPart.Type.CODE){
                str+=Code.DIVIDER + "\n";
                str+=tp.getValue() + "\n";
                str+=Code.DIVIDER+"\n";
            }
            if (tp.getType() == TextPart.Type.PARAGRAPH){
                str+=tp.getValue() + "\n";
            }
        }
        return new Text(str);
    }

    private Combiner(ArrayList<TextPart> textParts, int level){
        this.level = level;
        this.parts = textParts;
    }

}
