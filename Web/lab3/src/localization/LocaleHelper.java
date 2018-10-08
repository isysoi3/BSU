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
     * @param string localized string
     */
    public static String getLocalizedString( String string ){
        return bundle.getString( string );
    }

}
