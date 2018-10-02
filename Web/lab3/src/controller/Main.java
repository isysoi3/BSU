package controller;

import localization.LocaleWrapper;
import model.text_units.Text;
import model.util.Combiner;
import model.util.Splitter;

public class Main {
    private static int splitLevel;
    //file_name fileLocal programLocale
    public static void main( String[] args ){
        try{
            Controller controller = new Controller();
            System.out.println(controller.loadController(args[0], args[1], args[2]));

            System.out.println(controller.findMaxSubStr());

            Splitter lvl1 = new Splitter(controller.getText());
            System.out.println(controller.printTextPart(lvl1));
            Splitter lvl2 = new Splitter(lvl1);
            System.out.println(controller.printTextPart(lvl2));
            Splitter lvl3 = new Splitter(lvl2);
            System.out.println(controller.printTextPart(lvl3));
            System.out.println(controller.sortByVolwes(lvl3.getTextParts()));
            System.out.println(LocaleWrapper.getLocalizedString(LocaleWrapper.START_COMBINE));
            Splitter cb2 = Combiner.combine(lvl3);
            System.out.println(controller.printTextPart(cb2));
            Splitter cb1 = Combiner.combine(cb2);
            System.out.println(controller.printTextPart(cb1));
            Text text = Combiner.combineToText(cb1);
            System.out.println(text.getValue());
        }
        catch( Exception ex ){
            System.out.println( LocaleWrapper.getLocalizedString( LocaleWrapper.getLocalizedString(LocaleWrapper.INVALID_ARGS) ) );
            ex.printStackTrace();
            return;
        }

    }
}
