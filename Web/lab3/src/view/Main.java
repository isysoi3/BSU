package view;

import controller.Controller;
import localization.LocaleWrapper;
import model.Text;

import static localization.LocaleWrapper.START_COMBINE;
import static localization.LocaleWrapper.SWAP_FIRST_AND_LAST_WORDS;

public class Main {

    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RESET = "\u001B[0m";

    public static void main(String[] args) {
        try {
            Controller controller = new Controller();
            String result = controller.loadText(args[0]);
            System.out.println(ANSI_GREEN + "------" + result + "------" + ANSI_RESET);
            System.out.println(controller.getTextString());
            System.out.println();
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleWrapper.getLocalizedString(START_COMBINE)) + "------" + ANSI_RESET);
            Text text = controller.parseTextStringToText();
            System.out.println(text.toString());
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleWrapper.getLocalizedString(SWAP_FIRST_AND_LAST_WORDS)) + "------" + ANSI_RESET);
            System.out.println(controller.swapFirstAndLastWordInText(text).toString());
        } catch (Exception ex) {
            System.out.println(ex.toString());
            ex.printStackTrace();
        }
    }
}
