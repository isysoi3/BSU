package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import util.pharmacy.builder.MedicineBuilder;
import util.pharmacy.director.MedicineDirector;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

/**
 * SAX parser of XML
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public class SAXParser implements MedicinesParser {

    private static final Logger logger = LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Medicine> parse(String fileName) throws ParserException {
        logger.info("Starting SAX parsing");
        List<Medicine> medicines;

        try {
            File inputFile = new File(fileName);
            SAXParserFactory factory = SAXParserFactory.newInstance();
            javax.xml.parsers.SAXParser saxParser = factory.newSAXParser();
            Handler handler = new Handler();
            saxParser.parse(inputFile, handler);
            medicines = handler.getMedicines();
        } catch (IOException | SAXException | ParserConfigurationException e) {
            throw new ParserException("Configuration SAX parser error", e);
        }

        logger.info("Finish SAX parsing");
        return medicines;
    }

    /**
     * Tags handler
     */
    private class Handler extends DefaultHandler {

        private MedicineDirector director = new MedicineDirector();

        private MedicineBuilder builder = new MedicineBuilder();

        private List<Medicine> medicines = new ArrayList<>();

        private boolean parsed = true;
        private String currentElement;

        private String name;
        private double price;
        private Date manufactureDate;
        private Date expirationDate;
        private boolean isWarming;
        private double fluidityPercent;
        private double maxDailyDoseInMg;
        private boolean isRecipeRequired ;
        private boolean isCooling;
        private int doseInMg;
        private ColorEnum color;

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            currentElement = qName;
            if (qName.equals("name") ||
                    qName.equals("price") ||
                    qName.equals("manufactureDate") ||
                    qName.equals("expirationDate") ||
                    qName.equals("fluidityPercent") ||
                    qName.equals("isWarming") ||
                    qName.equals("maxDailyDoseInMg") ||
                    qName.equals("isRecipeRequired") ||
                    qName.equals("isCooling") ||
                    qName.equals("doseInMg") ||
                    qName.equals("color")) {
                parsed = false;
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            switch (qName) {
                case "pill":
                    medicines.add(director.manufacturePill(builder,
                            name,
                            price,
                            manufactureDate,
                            expirationDate,
                            maxDailyDoseInMg,
                            doseInMg));
                    break;
                case "syrup":
                    medicines.add(director.manufactureSyrup(builder,
                            name,
                            price,
                            manufactureDate,
                            expirationDate,
                            maxDailyDoseInMg,
                            color));
                    break;
                case "ointment":
                    medicines.add(director.manufactureOintment(builder,
                            name,
                            price,
                            manufactureDate,
                            expirationDate,
                            fluidityPercent,
                            isWarming));
                    break;
                case "antibiotic":
                    medicines.add(director.manufactureAntibiotic(builder,
                            name,
                            price,
                            manufactureDate,
                            expirationDate,
                            maxDailyDoseInMg,
                            isRecipeRequired));
                    break;
                case "gell":
                    medicines.add(director.manufactureGell(builder,
                            name,
                            price,
                            manufactureDate,
                            expirationDate,
                            fluidityPercent,
                            isCooling));
                    break;
            }
            builder.reset();
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            String value = new String(ch, start, length);
            if (!parsed) {
                switch (currentElement) {
                    case "name":
                        name = value;
                        break;
                    case "price":
                        price = Double.parseDouble(value);
                        break;
                    case "manufactureDate":
                        try {
                            manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(value);
                        } catch (ParseException e) {
                            e.printStackTrace();
                        }
                        break;
                    case "expirationDate":
                        try {
                            expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(value);
                        } catch (ParseException e) {
                            e.printStackTrace();
                        }
                        break;
                    case "isCooling":
                        isCooling = Boolean.parseBoolean(value);
                        break;
                    case "fluidityPercent":
                        fluidityPercent = Double.parseDouble(value);
                        break;
                    case "doseInMg":
                        doseInMg = Integer.parseInt(value);
                        break;
                    case "maxDailyDoseInMg":
                        maxDailyDoseInMg = Double.parseDouble(value);
                        break;
                    case "color":
                        color = ColorEnum.valueOf(value.toUpperCase());
                        break;
                    case "isWarming":
                        isWarming = Boolean.parseBoolean(value);
                        break;
                    case "isRecipeRequired":
                        isRecipeRequired = Boolean.parseBoolean(value);
                        break;
                }

                parsed = true;
            }


        }


        public List<Medicine> getMedicines() {
            return medicines;
        }
    }
}

