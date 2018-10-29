package view;

import controller.Controller;
import localization.LocaleHelper;
import model.Text;
import model.exception.FileException;
import model.exception.InvalidParsingException;
import model.exception.SwapFirstAndLastWordsException;
import model.text_unit.text.part.Word;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;

import static localization.LocaleHelper.*;

/**
 * Main class which run controller's demonstrate method
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Main {

    private static final Logger logger = LogManager.getLogger();
    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";

    /**
     * main method
     * @param args argument lines
     */
    public static void main(String[] args) {
        logger.info(LocaleHelper.getLocalizedString(LocaleHelper.CONTROLLER_INIT));
        Controller controller = new Controller();
        try {
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
            if (sorted.isEmpty()) {
                System.out.println(ANSI_RED + LocaleHelper.getLocalizedString(LocaleHelper.SORT_WORDS_NOT_FOUND) + ANSI_RESET);
            } else {
                for (Word word :
                        sorted) {
                    System.out.println(word.toString());
                }
            }
        } catch (FileException | InvalidParsingException | SwapFirstAndLastWordsException | ArrayIndexOutOfBoundsException ex) {
            logger.error(ex.getMessage(), ex);
            System.out.println();
            ex.printStackTrace();
        }
        logger.info(LocaleHelper.getLocalizedString(LocaleHelper.SHUTDOWN));
    }
}
