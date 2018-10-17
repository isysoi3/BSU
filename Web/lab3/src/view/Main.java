package view;

import controller.Controller;
import localization.LocaleHelper;
import logger.LoggerWrapper;
import model.Text;
import model.text_unit.text.part.Word;

import java.util.List;

import static localization.LocaleHelper.*;

/**
 * Main class which run controller's demonstrate method
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Main {


    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RESET = "\u001B[0m";

    /**
     * main method
     * @param args argument lines
     */
    public static void main(String[] args) {
        try {
            LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.CONTROLLER_INIT));
            Controller controller = new Controller();

            String result = controller.loadText(args[0]);
            System.out.println(ANSI_GREEN + "------" + LocaleHelper.getLocalizedString(LocaleHelper.FILE_LOADED) + "------" + ANSI_RESET);
            System.out.println(result);
            System.out.println();
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(START_COMBINE)) + "------" + ANSI_RESET);
            Text text = controller.parseTextStringToText();
            System.out.println(text.toString());
            System.out.println();

            System.out.print(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(SWAP_FIRST_AND_LAST_WORDS)) + "------" + ANSI_RESET);
            System.out.println(controller.swapFirstAndLastWordInText(text).toString());
            System.out.println();

            System.out.println(ANSI_GREEN + "------" + (LocaleHelper.getLocalizedString(SORT)) + "------" + ANSI_RESET);
            List<Word> sorted = controller.sortWordsWithStartedVowelByConsonantInText(text);
            for (Word word :
                    sorted) {
                System.out.println(word.toString());
            }
        } catch (Exception ex) {
            LoggerWrapper.severe(ex.getMessage());
            ex.printStackTrace();
        }
        LoggerWrapper.info(LocaleHelper.getLocalizedString(LocaleHelper.SHUTDOWN));
    }
}
