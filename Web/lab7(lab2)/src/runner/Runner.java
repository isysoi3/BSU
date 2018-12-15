package runner;

import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Runner class which contains pharmacy
 * * @author Ilya Sysoi
 * * @version 1.0.0
 */
public class Runner {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

    public static final String FILE_XML = "medicines.xml";
    public static final String FILE_XSD = "xsd_schema.xsd";

    /**
     * The Client method
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        logger.info("Start work");

        var controller = new Controller(new Pharmacy(new PharmacyManager()));

        controller.validate(FILE_XML, FILE_XSD);

        logger.info("Create pharmacy");

    }

}
