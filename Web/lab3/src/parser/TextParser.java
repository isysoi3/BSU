package parser;

import model.Text;
import model.text_unit.code.CodeBlock;
import model.text_unit.text.TextUnit;
import model.text_unit.text.part.Paragraph;
import model.text_unit.text.part.Sentence;

import java.util.ArrayList;

/**
 * paragraph text splitter parser
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class TextParser {

    /**
     * next splitter
     */
    private ParagraphTextParser nextSplitter;


    public TextParser() {
        nextSplitter = new ParagraphTextParser();
    }

    /**
     * split text codeBlock and paragraph
     * @param textString text
     * @return return Text object
     */
    public Text splitText(String textString){
        Text text = new Text();
        ArrayList<TextUnit> result = nextSplitter.split(trim(textString));
        for (TextUnit textUnit: result){
            if (textUnit.getClass() == Paragraph.class) {
                text.addParagraph((Paragraph)textUnit);
            } else if (textUnit.getClass() == CodeBlock.class) {
                text.addCode((CodeBlock)textUnit);
            } else if (textUnit.getClass() == Sentence.class) {
                text.addSentence((Sentence) textUnit);
            }
        }
        return text;
    }

    /**
     * replace tabs
     * @param text text
     * @return replaced text
     */
    protected String trim(String text){
        text = text.trim();
        text = text.replaceAll( "[\t ]+", " ");
        return text;
    }

}
