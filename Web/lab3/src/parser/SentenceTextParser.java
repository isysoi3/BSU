package parser;

import model.text_unit.code.CodeBlock;
import model.text_unit.code.CodeLine;
import model.text_unit.text.TextUnit;
import model.text_unit.text.part.Paragraph;
import model.text_unit.text.part.Sentence;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * sentence text parser
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class SentenceTextParser {

    /**
     * next splitter
     */
    private WordTextParser nextSplitter;

    public SentenceTextParser() {
        nextSplitter = new WordTextParser();
    }

    public ArrayList<TextUnit> split(ArrayList<TextUnit> textUnits) {
        ArrayList<TextUnit> result = new ArrayList<>();
        for (TextUnit textUnit : textUnits) {
            if (textUnit.getClass() == CodeBlock.class) {
                String[] lines = textUnit.getValue().split(CodeLine.DIVIDER);
                CodeLine currentLine = null;
                CodeBlock codeBlock = new CodeBlock(textUnit.getValue());
                for (String line : lines) {
                    line = trim(line);
                    if (line.length() > 0) {
                        currentLine = new CodeLine((line));
                        codeBlock.addCodeLine(currentLine);
                    }
                }
                result.add(codeBlock);
            } else if (textUnit.getClass() == Paragraph.class) {
                Sentence sentence = null;
                Matcher matcher = Pattern.compile(Sentence.SPLITTING_REGEX).matcher(textUnit.getValue());
                result.add(textUnit);
                while (matcher.find()) {
                    sentence = new Sentence(trim(matcher.group()));
                    result.add(sentence);
                }
            }
        }
        return nextSplitter.split(result);
    }

    /**
     * replace tabs
     * @param text text
     * @return replaced text
     */
    protected String trim(String text) {
        text = text.trim();
        text = text.replaceAll("[\t ]+", " ");
        return text;
    }

    @Override
    public String toString() {
        return "Splitting into sentences and code lines";
    }
}
