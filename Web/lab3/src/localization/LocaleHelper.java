package localization;

import java.util.Locale;
import java.util.ResourceBundle;

/**
 * Locale Wrapper
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class LocaleHelper {
    public static final String DEFAULT_LANGUAGE = "ru";
    private static Locale locale = new Locale(DEFAULT_LANGUAGE);

    private static final String BUNDLE_PATH = "localization/locales/locale";
    private static ResourceBundle bundle = ResourceBundle.getBundle(BUNDLE_PATH, locale);

    public static String INVALID_ARGS = "InvalidArgs";
    public static String FILE_LOADED = "FileLoaded";
    public static String START_COMBINE = "StartCombine";
    public static String SWAP_FIRST_AND_LAST_WORDS = "SwapFirstAndLastWords";
    public static String SORT = "Sort";
    public static String FILE_LOADING = "FileLoading";
    public static String START_TEXT_PARSING = "StartTextParsing";
    public static String FINISH_TEXT_PARSING = "FinishTextParsing";
    public static String START_WORDS_SWAPPING = "StartWordsSwapping";
    public static String FINISH_WORDS_SWAPPING = "FinishWordsSwapping";
    public static String START_WORDS_SORTING = "StartWordsSorting";
    public static String FINISH_WORDS_SORTING = "FinishWordsSorting";
    public static String CONTROLLER_INIT = "ControllerInit";
    public static String SWAP_ERROR = "SwapError";
    public static String SORT_WORDS_NOT_FOUND= "SortWordsNotFound";
    public static String SHUTDOWN = "Shutdown";

    public static Locale getDefaultLocale(){
        return new Locale(DEFAULT_LANGUAGE);
    }

    public static Locale getCurrentLocale(){
        return locale;
    }

    /**
     * set new locale
     * @param localeStr new loacle string
     */
    public static void setLocale( String localeStr ){
        locale = new Locale(localeStr);
        bundle = ResourceBundle.getBundle(BUNDLE_PATH, locale);
    }

    /**
     * get localized string
     * @param string localized string key
     * @return localized string
     */
    public static String getLocalizedString( String string ){
        return bundle.getString( string );
    }

}
