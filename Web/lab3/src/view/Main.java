package view;

import controller.Controller;
import localization.LocaleWrapper;
import model.Text;
import splitters.TextSplitter;

import static localization.LocaleWrapper.START_COMBINE;

public class Main {

    public static void main( String[] args ){
        try{
            Controller controller = new Controller();
            String result = controller.loadText(args[0]);
            System.out.println(result);
            System.out.println(controller.getTextString());
            System.out.println();
            System.out.println();

            System.out.print((LocaleWrapper.getLocalizedString(START_COMBINE)));
            System.out.println(controller.parseTextStringToText().toString());
        }
        catch( Exception ex ){
            System.out.println(ex.toString());
            ex.printStackTrace();
        }
    }
}
