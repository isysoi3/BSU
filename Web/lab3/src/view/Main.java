package view;

import controller.Controller;
import localization.LocaleWrapper;
import model.Text;
import splitters.TextSplitter;

public class Main {

    public static void main( String[] args ){
        try{
            Controller controller = new Controller();
            String text = controller.loadText(args[0], null, null);
            controller.parseTextStringToText(text);
            TextSplitter textSplitter = new TextSplitter();
            Text text1 = textSplitter.splitText(text);
            System.out.println(text1.toString());
        }
        catch( Exception ex ){
            System.out.println( LocaleWrapper.getLocalizedString( LocaleWrapper.getLocalizedString(LocaleWrapper.INVALID_ARGS) ) );
            ex.printStackTrace();
        }
    }
}
