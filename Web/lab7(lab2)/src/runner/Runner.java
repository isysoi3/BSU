package runner;

import controller.Controller;
import model.ParsingModeEnum;
import exception.ParserException;
import exception.XMLValidatorException;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;
import java.util.Objects;

/**
 * Runner class which show work with parsers
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Runner {

    private static final String FILE_XML = "medicines.xml";
    private static final String FILE_XSD = "xsd_schema.xsd";

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

    /**
     * The Client method
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        logger.info("Start work");
        if (args.length < 1) {
            logger.warn("No parsing mode argument");
            return;
        }

        var controller = new Controller(new Pharmacy(new PharmacyManager()));
        logger.info("Create pharmacy");

        boolean result = false;
        try {
            result = controller.validate(FILE_XML, FILE_XSD);
        } catch (XMLValidatorException e) {
            logger.warn(e);
        }
        if (result) {
            logger.info("Valid xml");
        } else {
            logger.info("Failed to validate xml");
            return;
        }

        ParsingModeEnum mode = null;
        switch (args[0]) {
            case "-d":
                mode = ParsingModeEnum.DOM;
                break;
            case "-s":
                mode = ParsingModeEnum.SAX;
                break;
            case "-st":
                mode = ParsingModeEnum.StAX;
                break;
        }

        List<Medicine> medicines;
        logger.info("Try to parse xml");
        try {
            medicines = controller.parseMedicinesList(FILE_XML, mode);
        } catch (ParserException e) {
            logger.warn(e);
            return;
        }
        logger.info("Add parsed medicines to pharmacy");
        for (Medicine medicine : Objects.requireNonNull(medicines)) {
            controller.addMedicine(medicine);
        }

        printMedicineList("Just list of medicine in pharmacy", controller.getPharmacyMedicines());
        logger.info("Finish work");
    }


    public static void printMedicineList(String textBefore, List<Medicine> list) {
        logger.info("\n" + "-----------" + textBefore + "---------");
        if (list.size() > 0) {
            for (Medicine medicine : list) {
                logger.info("\n" + medicine);
            }
        } else {
            logger.info("No items");
        }
    }

}
