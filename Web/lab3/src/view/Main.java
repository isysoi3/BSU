package view;

import controller.Controller;
import localization.LocaleWrapper;
import model.Text;

import static localization.LocaleWrapper.START_COMBINE;
import static localization.LocaleWrapper.SWAP_FIRST_AND_LAST_WORDS;

public class Main {

    public static void main(String[] args) {
        try {
            Controller controller = new Controller();
            String result = controller.loadText(args[0]);
            System.out.println(result);
            System.out.println(controller.getTextString());
            System.out.println();
            System.out.println();

            System.out.print((LocaleWrapper.getLocalizedString(START_COMBINE)));
            Text text = controller.parseTextStringToText();
            System.out.println(text.toString());

            System.out.println((LocaleWrapper.getLocalizedString(SWAP_FIRST_AND_LAST_WORDS)));
            System.out.println(controller.swapFirstAndLastWordInText(text).toString());
        } catch (Exception ex) {
            System.out.println(ex.toString());
            ex.printStackTrace();
        }
    }
}
